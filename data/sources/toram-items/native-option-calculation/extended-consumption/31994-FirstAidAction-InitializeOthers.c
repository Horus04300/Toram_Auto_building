
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FirstAidAction_InitializeOthers
               (undefined *self,undefined *actarAction,undefined *targetPos,int motionSpeed,
               float castTime,int loopCount,int element,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  undefined8 uVar3;
  
  if (DAT_7ffe9cadf799 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf799 = '\x01';
  }
  *(undefined4 *)(self + 0x20) = 0xbf800000;
  uVar3 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
  FUN_7ffe9a9002e0(uVar3,0x1e078,0);
  *(undefined8 *)(self + 0x58) = uVar3;
  il2cpp_write_barrier_0();
  lVar1 = *(longlong *)(self + 0x58);
  uVar3 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
  FUN_7ffe9a9002e0(uVar3,0x9ebcba,0);
  if (lVar1 != 0) {
    *(undefined8 *)(lVar1 + 0x20) = uVar3;
    il2cpp_write_barrier_0();
    *(int *)(self + 0x78) = motionSpeed;
    *(float *)(self + 0x24) = castTime;
    return;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

