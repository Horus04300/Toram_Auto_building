
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidBossBattleStatus_get_MaxHp(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  undefined *apuStackX_8 [4];
  
  apuStackX_8[0] = (undefined *)0x0;
  if (DAT_7ffe9cadd548 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c929b20);
    DAT_7ffe9cadd548 = '\x01';
  }
  if ((*(longlong *)(self + 0x10) == 0) ||
     (lVar1 = *(longlong *)(*(longlong *)(self + 0x10) + 0xa0), lVar1 == 0)) goto LAB_7ffe9a32397d;
  cVar3 = FUN_7ffe9abb86e0(lVar1,0x20,apuStackX_8,_DAT_7ffe9c929b20);
  if (cVar3 != '\0') {
    if (apuStackX_8[0] == (undefined *)0x0) goto LAB_7ffe9a32397d;
    bVar4 = MobPropertyHighRaidCalcExceptionFlag_FixedHpFlag(apuStackX_8[0],(undefined *)0x0);
    if (bVar4 != 0) {
      if (*(longlong *)(self + 0x10) != 0) {
        return *(int *)(*(longlong *)(self + 0x10) + 0x30);
      }
      goto LAB_7ffe9a32397d;
    }
  }
  if (*(longlong *)(self + 0x10) != 0) {
    iVar5 = *(int *)(self + 0x30);
    fVar7 = (float)*(int *)(*(longlong *)(self + 0x10) + 0x30) / _DAT_7ffe9c049cfc;
    fVar6 = ((float)(iVar5 + 0x51) + (float)(iVar5 * iVar5) / _DAT_7ffe9c049ef0) *
            ((float)iVar5 / _DAT_7ffe9c049ce4 + _DAT_7ffe9c049e64);
    if (0x95 < iVar5) {
      return (int)(fVar7 * fVar6 * _DAT_7ffe9c049cd8);
    }
    return (int)(fVar7 * fVar6 * _DAT_7ffe9c049b18);
  }
LAB_7ffe9a32397d:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

