
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * SkillTextManagerData_GetName(undefined *self,undefined *key,undefined *methodInfo)

{
  char cVar1;
  undefined *puVar2;
  undefined *puStackX_8;
  
  if (DAT_7ffe9cad9dfb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c93fe88);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    FUN_7ffe9996d590(&DAT_7ffe9c93a1c8);
    DAT_7ffe9cad9dfb = '\x01';
  }
  if (*(longlong *)(self + 0x28) != 0) {
    puStackX_8 = _DAT_7ffe9c8f1820;
    cVar1 = FUN_7ffe9adb0cf0(*(longlong *)(self + 0x28),key,&puStackX_8,_DAT_7ffe9c93fe88);
    puVar2 = _DAT_7ffe9c93a1c8;
    if (cVar1 != '\0') {
      puVar2 = puStackX_8;
    }
    return puVar2;
  }
  return *(undefined **)(self + 0x18);
}

