
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidBossBattleStatus__ctor
               (undefined *self,undefined *statusMaster,undefined *abnormalStateManager,
               undefined *buffManager,int level,undefined *methodInfo)

{
  undefined8 uVar1;
  short returnCode;
  undefined *methodInfo_00;
  
  returnCode = (short)abnormalStateManager;
  methodInfo_00 = buffManager;
  if (DAT_7fff625e4c9b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406160);
    FUN_7fff5f47d450(&DAT_7fff6241a798);
    DAT_7fff625e4c9b = '\x01';
  }
  uVar1 = func_0x7fff5f44ff00(_DAT_7fff6241a798);
  FUN_7fff6082b860(uVar1,_DAT_7fff62406160);
  *(undefined8 *)(self + 0x38) = uVar1;
  thunk_FUN_7fff5f491fd0();
  HighRaidRoomData_LoadAsset(self,0,returnCode,methodInfo_00);
  *(undefined **)(self + 0x10) = statusMaster;
  thunk_FUN_7fff5f491fd0();
  *(undefined **)(self + 0x18) = abnormalStateManager;
  thunk_FUN_7fff5f491fd0();
  *(undefined **)(self + 0x20) = buffManager;
  thunk_FUN_7fff5f491fd0();
  *(int *)(self + 0x30) = level;
  return;
}

