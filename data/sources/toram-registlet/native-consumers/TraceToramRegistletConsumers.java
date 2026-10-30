// Selected-function analysis of the saved module; never attaches to the game.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Parameter;
import ghidra.program.model.listing.ParameterImpl;
import ghidra.program.model.data.*;
import ghidra.program.model.symbol.SourceType;
import com.google.gson.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class TraceToramRegistletConsumers extends GhidraScript {
    DataType type(JsonObject value) {
        String name = value.has("exact_byval_name") && !value.get("exact_byval_name").isJsonNull() ? value.get("exact_byval_name").getAsString() : "";
        return switch (name) {
            case "System.Void" -> VoidDataType.dataType;
            case "System.Single" -> FloatDataType.dataType;
            case "System.Double" -> DoubleDataType.dataType;
            case "System.Boolean", "System.Byte" -> ByteDataType.dataType;
            case "System.SByte" -> SignedByteDataType.dataType;
            case "System.Int16" -> ShortDataType.dataType;
            case "System.UInt16", "System.Char" -> UnsignedShortDataType.dataType;
            case "System.Int32", "System.MidpointRounding", "Toram.Common.Bonus.BonusType" -> IntegerDataType.dataType;
            case "System.UInt32" -> UnsignedIntegerDataType.dataType;
            case "System.Int64" -> LongLongDataType.dataType;
            case "System.UInt64" -> UnsignedLongLongDataType.dataType;
            default -> PointerDataType.dataType;
        };
    }
    @Override public void run() throws Exception {
        String[] args = getScriptArgs();
        
        if (args.length != 2) throw new IllegalArgumentException("method-map.json and new output directory required");
        JsonObject map = JsonParser.parseString(Files.readString(Path.of(args[0]))).getAsJsonObject();
        if (!map.get("snapshotSha256").getAsString().equals(currentProgram.getExecutableSHA256())) throw new IllegalStateException("PE snapshot hash mismatch");
        Path output = Path.of(args[1]);
        Files.createDirectories(output);
        long expectedBase = Long.parseUnsignedLong(map.get("image_base").getAsString().replace("0x", ""), 16);
        if (currentProgram.getImageBase().getOffset() != expectedBase) throw new IllegalStateException("Image base mismatch");
        Set<String> names = Set.of("GetBonusTime", "CheckEquipLimitBonusId", "GetCalcBonusValue", ".cctor", "CreateItemData",
            "SetItemDataProperty", "ReadItemData", "ReadItemProperty", "Initialize", "AddCapPropertyNoColor",
            "AddCapProperty", "ItemText", "ItemDBProperty", "GetItemPropertysTextData", "ItemPropertysData", "AssetDecrypt", "GetAssetDecryptData");
        JsonArray methods = map.getAsJsonArray("methods");
        // The captured write-barrier helper consumes its return address; define its boundary
        // so the decompiler does not merge its body into callers as a PIC construction.
        int helperIndex = 0;
        for (JsonElement helper : map.getAsJsonArray("helperAddresses")) {
            Address address = toAddr(helper.getAsString());
            disassemble(address);
            Function barrier = createFunction(address, "il2cpp_write_barrier_" + helperIndex++);
            if (barrier != null) {
                barrier.setReturnType(VoidDataType.dataType, SourceType.USER_DEFINED);
                barrier.setNoReturn(false);
            }
        }
        // Labels give called methods meaningful identities without whole-program auto-analysis.
        JsonArray declarations = methods.deepCopy();
        for (JsonElement callee : map.getAsJsonArray("callees")) declarations.add(callee);
        for (JsonElement entry : declarations) {
            JsonObject method = entry.getAsJsonObject();
            if (!method.get("status").getAsString().equals("mapped")) continue;
            Address address = toAddr(method.get("runtime_va").getAsString());
            String label = method.get("class").getAsString() + "_" + method.get("name").getAsString();
            createLabel(address, label.replaceAll("[^A-Za-z0-9_]", "_"), false, SourceType.USER_DEFINED);
            disassemble(address);
            Function f = getFunctionAt(address);
            if (f == null) f = createFunction(address, null);
            if (f == null) continue;
            ArrayList<Parameter> parameters = new ArrayList<>();
            int flags = Integer.parseInt(method.get("method_flags_raw").getAsString().replace("0x", ""), 16);
            if ((flags & 0x10) == 0) parameters.add(new ParameterImpl("thisObject", PointerDataType.dataType, currentProgram));
            for (JsonElement p : method.getAsJsonArray("parameters")) {
                JsonObject param = p.getAsJsonObject();
                parameters.add(new ParameterImpl(param.get("name").getAsString(), type(param), currentProgram));
            }
            parameters.add(new ParameterImpl("methodInfo", PointerDataType.dataType, currentProgram));
            f.setReturnType(type(method.getAsJsonObject("return_type")), SourceType.USER_DEFINED);
            f.replaceParameters(parameters, Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS, true, SourceType.USER_DEFINED);
        }
        DecompInterface decompiler = new DecompInterface();
        if (!decompiler.openProgram(currentProgram)) throw new IllegalStateException(decompiler.getLastMessage());
        JsonArray index = new JsonArray();
        try {
            for (JsonElement entry : methods) {
                JsonObject method = entry.getAsJsonObject();
                if (!method.get("status").getAsString().equals("mapped")) continue;
                Address address = toAddr(method.get("runtime_va").getAsString());
                if (!currentProgram.getMemory().contains(address)) throw new IllegalStateException("Address outside snapshot");
                disassemble(address);
                Function function = getFunctionAt(address);
                if (function == null) function = createFunction(address, null);
                if (function == null) throw new IllegalStateException("Cannot create function " + address);
                DecompileResults result = decompiler.decompileFunction(function, 120, monitor);
                JsonObject record = method.deepCopy();
                record.addProperty("decompileCompleted", result.decompileCompleted());
                record.addProperty("error", result.getErrorMessage());
                String filename = method.get("oldIndex").getAsString() + ".c";
                record.addProperty("pseudocodeFile", filename);
                if (result.decompileCompleted()) Files.writeString(output.resolve(filename), result.getDecompiledFunction().getC(), StandardCharsets.UTF_8);
                index.add(record);
                println("TORAM " + filename + " completed=" + result.decompileCompleted());
                Files.writeString(output.resolve("index.json"), new GsonBuilder().setPrettyPrinting().create().toJson(index));
            }
        } finally { decompiler.dispose(); }
        if (index.size() == 0) throw new IllegalStateException("No selected methods");
    }
}
