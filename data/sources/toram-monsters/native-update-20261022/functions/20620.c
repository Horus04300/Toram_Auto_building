
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidRoomData_ReceiveBossSymbolData
               (undefined *self,int mobUuid,int currentHpGauge,int maxHpGauge,int battleHp,
               byte element,byte isPractice,undefined *methodInfo)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  float fVar4;
  
  *(int *)(self + 0xa4) = mobUuid;
  *(uint *)(self + 0xa8) = (uint)element;
  self[0xa0] = isPractice;
  *(undefined4 *)(self + 0x98) = 0;
  iVar3 = ((maxHpGauge - currentHpGauge) + 1) / 10;
  if (iVar3 < 1) {
    iVar3 = 1;
  }
  *(int *)(self + 0xbc) = iVar3;
  uVar1 = (undefined2)(currentHpGauge & 0xffU);
  *(undefined2 *)(self + 0xb2) = uVar1;
  *(undefined2 *)(self + 0xb4) = uVar1;
  uVar2 = (currentHpGauge & 0xffU) << 2;
  uVar1 = 0x28;
  if (uVar2 < 0x28) {
    uVar2 = 0x28;
  }
  *(uint *)(self + 0xac) = uVar2;
  *(short *)(self + 0xb6) = (short)maxHpGauge;
  if (0x27 < maxHpGauge * 4) {
    uVar1 = (undefined2)(maxHpGauge * 4);
  }
  *(undefined2 *)(self + 0xb0) = uVar1;
  iVar3 = currentHpGauge * 4;
  fVar4 = (float)FUN_7ffe99744190((float)(currentHpGauge * currentHpGauge) / _DAT_7ffe9c049cfc);
  iVar3 = (int)((fVar4 + _DAT_7ffe9c049cf4) *
               (float)(int)((float)(iVar3 * iVar3) / _DAT_7ffe9c049ef0 + (float)(iVar3 + 0x51)) *
               ((float)iVar3 / _DAT_7ffe9c049ce4 + _DAT_7ffe9c049e64));
  *(float *)(self + 0xb8) = (float)(iVar3 - battleHp) / (float)iVar3;
  return;
}

