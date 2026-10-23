
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * SkillTextManagerData_GetName(undefined *self,undefined *key,undefined *methodInfo)

{
  char cVar1;
  undefined *puVar2;
  undefined *puStackX_8;
  
  if (DAT_7fff625e1577 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62446dd8);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    FUN_7fff5f47d450(&DAT_7fff624408b0);
    DAT_7fff625e1577 = '\x01';
  }
  if (*(longlong *)(self + 0x28) != 0) {
    puStackX_8 = _DAT_7fff623f7f60;
    cVar1 = FUN_7fff608bb0b0(*(longlong *)(self + 0x28),key,&puStackX_8,_DAT_7fff62446dd8);
    puVar2 = _DAT_7fff624408b0;
    if (cVar1 != '\0') {
      puVar2 = puStackX_8;
    }
    return puVar2;
  }
  return *(undefined **)(self + 0x18);
}

