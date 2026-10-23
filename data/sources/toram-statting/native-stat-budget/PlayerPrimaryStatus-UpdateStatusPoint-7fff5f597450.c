
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerPrimaryStatus_UpdateStatusPoint(undefined *self,int point,undefined *methodInfo)

{
  *(int *)(self + 0x38) = point;
  return;
}

