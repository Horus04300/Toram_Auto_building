
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MapInfo_GetMobPopPoint(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  undefined8 uVar4;
  
  if (DAT_7ffe9cadfb10 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94dcc8);
    FUN_7ffe9996d590(&DAT_7ffe9c93d1e8);
    FUN_7ffe9996d590(&DAT_7ffe9c93d120);
    FUN_7ffe9996d590(&DAT_7ffe9c96dda8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadfb10 = '\x01';
  }
  uVar4 = *(undefined8 *)(self + 0x20);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar2 = FUN_7ffe9bda20c0(uVar4,0);
  if (cVar2 == '\0') {
    puVar3 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c96dda8);
    FUN_7ffe9af8a010(puVar3,_DAT_7ffe9c93d120);
    return puVar3;
  }
  if (*(longlong *)(self + 0x20) != 0) {
    uVar4 = FUN_7ffe9ab6e530(*(longlong *)(self + 0x20),1,_DAT_7ffe9c94dcc8);
    puVar3 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c96dda8);
    FUN_7ffe9afe3710(puVar3,uVar4,_DAT_7ffe9c93d1e8);
    return puVar3;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar1)();
  return puVar3;
}

