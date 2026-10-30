
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBufferBase_GetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  char cVar1;
  int iVar2;
  
  iVar2 = (**(code **)(*(longlong *)self + 0x1d8))
                    (self,id,*(undefined8 *)(*(longlong *)self + 0x1e0));
  if ((iVar2 != 0) && (*(float *)(self + 0x10) <= 0.0)) {
    cVar1 = (**(code **)(*(longlong *)self + 0x1c8))
                      (self,*(undefined8 *)(*(longlong *)self + 0x1d0));
    if (cVar1 != '\0') {
      return iVar2;
    }
  }
  return 0;
}

