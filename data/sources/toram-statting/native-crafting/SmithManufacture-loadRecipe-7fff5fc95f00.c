
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
SmithManufacture_loadRecipe
          (undefined *self,undefined *recipeManager,int category,int proficiency,byte isShop,
          undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  undefined *puVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (DAT_7fff625e4284 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242b530);
    FUN_7fff5f47d450(&DAT_7fff62450c08);
    FUN_7fff5f47d450(&DAT_7fff62450cc8);
    FUN_7fff5f47d450(&DAT_7fff62409fe0);
    FUN_7fff5f47d450(&DAT_7fff62418ac8);
    FUN_7fff5f47d450(&DAT_7fff6242ad08);
    DAT_7fff625e4284 = '\x01';
  }
  if (recipeManager != (undefined *)0x0) {
    puVar3 = RecipeDBDataManager_GetData
                       (recipeManager,category,proficiency,isShop,1,(undefined *)0x0);
    if (isShop == 0) {
      lVar4 = FUN_7fff6069cf90(puVar3,_DAT_7fff6242b530);
      if (*(int *)(_DAT_7fff6242ad08 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(_DAT_7fff6242ad08);
      }
      lVar5 = *(longlong *)(*(longlong *)(_DAT_7fff6242ad08 + 0xb8) + 8);
      if (lVar5 == 0) {
        if (*(int *)(_DAT_7fff6242ad08 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(_DAT_7fff6242ad08);
        }
        uVar1 = **(undefined8 **)(_DAT_7fff6242ad08 + 0xb8);
        lVar5 = func_0x7fff5f44ff00(_DAT_7fff62409fe0);
        FUN_7fff60bd9cc0(lVar5,uVar1,_DAT_7fff62418ac8,0);
        *(longlong *)(*(longlong *)(_DAT_7fff6242ad08 + 0xb8) + 8) = lVar5;
        thunk_FUN_7fff5f491fd0();
      }
      if (lVar4 == 0) goto LAB_7fff5fc96097;
      FUN_7fff60ae5b60(lVar4,lVar5,_DAT_7fff62450c08);
      puVar3 = (undefined *)FUN_7fff60a940e0(lVar4,_DAT_7fff62450cc8);
    }
    return puVar3;
  }
LAB_7fff5fc96097:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar2)();
  return puVar3;
}

