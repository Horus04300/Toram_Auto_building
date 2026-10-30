
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferBase_InvokeBufEffect(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  
  if (*(float *)(self + 0x10) <= 0.0) {
    uVar1 = (**(code **)(*(longlong *)self + 0x188))(0,*(undefined8 *)(*(longlong *)self + 400));
    *(undefined4 *)(self + 0x10) = uVar1;
  }
  return;
}

