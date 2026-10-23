
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RecipeDBData__ctor(undefined *self,int recipeId,byte type,short releaseLv,int price,
                       short difficulty,int createId,short createVal,byte category,
                       undefined *materialDatas,undefined *methodInfo)

{
  code *pcVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  if (DAT_7fff625e42bb == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242f248);
    DAT_7fff625e42bb = '\x01';
  }
  SmithManufacture_Update(self,(undefined *)0x0);
  *(int *)(self + 0x18) = price;
  *(short *)(self + 0x1c) = difficulty;
  *(int *)(self + 0x20) = createId;
  *(short *)(self + 0x24) = createVal;
  self[0x26] = category;
  *(int *)(self + 0x10) = recipeId;
  self[0x14] = type;
  *(short *)(self + 0x16) = releaseLv;
  if (materialDatas != (undefined *)0x0) {
    uVar2 = func_0x7fff60f8fd60(materialDatas,0);
    uVar3 = func_0x7fff5f47c7e0(uVar2,_DAT_7fff6242f248);
    *(undefined8 *)(self + 0x28) = uVar3;
    func_0x7fff5f47c7e0(uVar2,_DAT_7fff6242f248);
    thunk_FUN_7fff5f491fd0();
    self[0x27] = 1;
    return;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

