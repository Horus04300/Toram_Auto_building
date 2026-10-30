
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * UITreasureHuntEnterManager_WaitRoomData(undefined *self,undefined *methodInfo)

{
  undefined *self_00;
  undefined *in_R8;
  
  if (DAT_7ffe9cadab7b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90ae38);
    DAT_7ffe9cadab7b = '\x01';
  }
  self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c90ae38);
  PhotonListener_OnGmTreasureHuntTrialPointMax(self_00,(undefined *)0x0,in_R8);
  *(undefined **)(self_00 + 0x20) = self;
  *(undefined4 *)(self_00 + 0x10) = 0;
  il2cpp_write_barrier_0();
  return self_00;
}

