
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
RecipeDBDataManager_GetData
          (undefined *self,int category,int proficiency,byte isShop,byte isSmith,
          undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined *puVar4;
  
  if (DAT_7fff625e42c3 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62473180);
    FUN_7fff5f47d450(&DAT_7fff62473318);
    FUN_7fff5f47d450(&DAT_7fff62450cc8);
    FUN_7fff5f47d450(&DAT_7fff62424348);
    DAT_7fff625e42c3 = '\x01';
  }
  if (*(longlong *)(self + 0x28) != 0) {
    cVar2 = FUN_7fff6082f170(*(longlong *)(self + 0x28),category,_DAT_7fff62473180);
    if (cVar2 == '\0') {
      puVar4 = (undefined *)func_0x7fff5f47c850(_DAT_7fff62424348,0);
      return puVar4;
    }
    if ((*(longlong *)(self + 0x28) != 0) &&
       (lVar3 = FUN_7fff6083faa0(*(longlong *)(self + 0x28),category,_DAT_7fff62473318), lVar3 != 0)
       ) {
      puVar4 = (undefined *)FUN_7fff60a940e0(lVar3,_DAT_7fff62450cc8);
      puVar4 = RecipeDBDataManager_getData(self,puVar4,proficiency,isShop,isSmith,(undefined *)0x0);
      return puVar4;
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar4 = (undefined *)(*pcVar1)();
  return puVar4;
}

