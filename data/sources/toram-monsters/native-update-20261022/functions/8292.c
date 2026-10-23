
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float MobBattleStatus_get_NecessaryFleePercent(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  float fVar4;
  
  if (*(longlong *)(self + 0x18) == 0) {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    fVar4 = (float)(*pcVar1)();
    return fVar4;
  }
  cVar2 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),7);
  if (cVar2 == '\0') {
    return _DAT_7ffe9c049b18;
  }
  bVar3 = MobStatusMasterEx_CheckMultiFlag
                    (*(undefined **)(self + 0x10),(undefined *)0x4,(undefined *)0x0);
  if (bVar3 != 0) {
    return _DAT_7ffe9c049e54;
  }
  return _DAT_7ffe9c049cc4;
}

