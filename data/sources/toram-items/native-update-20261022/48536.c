
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
ResourceManager_Initialize(undefined *self,undefined *url,undefined *result,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if (DAT_7ffe9cada0d9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c919638);
    DAT_7ffe9cada0d9 = '\x01';
  }
  puVar2 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c919638);
  FUN_7ffe999db770(puVar2,0,0);
  if (puVar2 != (undefined *)0x0) {
    *(undefined **)(puVar2 + 0x20) = self;
    il2cpp_write_barrier_0();
    *(undefined **)(puVar2 + 0x28) = url;
    il2cpp_write_barrier_0();
    *(undefined **)(puVar2 + 0x38) = result;
    il2cpp_write_barrier_0();
    return puVar2;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

