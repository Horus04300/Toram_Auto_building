
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ScoreAttackBossMasterData__ctor
               (undefined *self,byte no,int fieldId,int roomId,byte raidFlag,int monsterId,
               int monsterUuid,short baseLevel,short minLevel,undefined *methodInfo)

{
  func_0x7ffe999c3920(self,0);
  self[0x1c] = raidFlag;
  *(int *)(self + 0x20) = monsterId;
  *(int *)(self + 0x24) = monsterUuid;
  *(short *)(self + 0x28) = baseLevel;
  self[0x10] = no;
  *(int *)(self + 0x18) = roomId;
  *(short *)(self + 0x2a) = minLevel;
  *(int *)(self + 0x14) = fieldId;
  return;
}

