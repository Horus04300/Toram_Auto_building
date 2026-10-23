
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * EnemyTextManager_GetName(undefined *self,int uid,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  longlong *plStackX_8;
  
  if (DAT_7fff625e14f7 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62410650);
    FUN_7fff5f47d450(&DAT_7fff624408b0);
    DAT_7fff625e14f7 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  if (*(longlong *)(self + 0x18) != 0) {
    cVar2 = FUN_7fff60862d70(*(longlong *)(self + 0x18),uid,&plStackX_8,_DAT_7fff62410650);
    if (cVar2 == '\0') {
      return _DAT_7fff624408b0;
    }
    if (plStackX_8 != (longlong *)0x0) {
      puVar3 = (undefined *)
               (**(code **)(*plStackX_8 + 0x178))(plStackX_8,*(undefined8 *)(*plStackX_8 + 0x180));
      return puVar3;
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar1)();
  return puVar3;
}

