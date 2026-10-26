
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MainPlayer_ReduceItemDelay(undefined *self,float time,undefined *methodInfo)

{
  float fVar1;
  
  fVar1 = *(float *)(self + 0xa8);
  *(float *)(self + 0xa8) = fVar1 - time;
  if (fVar1 - time < 0.0) {
    *(undefined4 *)(self + 0xa8) = 0;
  }
  return;
}

