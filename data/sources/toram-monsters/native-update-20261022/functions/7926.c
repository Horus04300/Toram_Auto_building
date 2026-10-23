
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidBossBattleStatus__ctor
               (undefined *self,undefined *statusMaster,undefined *abnormalStateManager,
               undefined *buffManager,int level,undefined *methodInfo)

{
  undefined8 uVar1;
  
  if (DAT_7ffe9cadd543 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff130);
    FUN_7ffe9996d590(&DAT_7ffe9c912c08);
    DAT_7ffe9cadd543 = '\x01';
  }
  uVar1 = func_0x7ffe99940040(_DAT_7ffe9c912c08);
  FUN_7ffe9ad214a0(uVar1,_DAT_7ffe9c8ff130);
  *(undefined8 *)(self + 0x38) = uVar1;
  il2cpp_write_barrier_0();
  func_0x7ffe999c3920(self,0);
  *(undefined **)(self + 0x10) = statusMaster;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 0x18) = abnormalStateManager;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 0x20) = buffManager;
  il2cpp_write_barrier_0();
  *(int *)(self + 0x30) = level;
  return;
}

