
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * EnemyTextManager_GetName(undefined *self,int uid,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cad9d77 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c909620);
    FUN_7ffe9996d590(&DAT_7ffe9c93a1c8);
    DAT_7ffe9cad9d77 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  if (*(longlong *)(self + 0x18) != 0) {
    cVar2 = FUN_7ffe9ad589b0(*(longlong *)(self + 0x18),uid,&plStackX_8,_DAT_7ffe9c909620);
    if (cVar2 == '\0') {
      return _DAT_7ffe9c93a1c8;
    }
    if (plStackX_8 != (longlong *)0x0) {
      puVar3 = (undefined *)
               (**(code **)(*plStackX_8 + 0x178))(plStackX_8,*(undefined8 *)(*plStackX_8 + 0x180));
      return puVar3;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar1)();
  return puVar3;
}

