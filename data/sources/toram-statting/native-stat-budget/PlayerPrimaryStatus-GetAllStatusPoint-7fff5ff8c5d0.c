
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerPrimaryStatus_GetAllStatusPoint(undefined *self,undefined *methodInfo)

{
  return *(int *)(self + 0x14) + -9 +
         *(int *)(self + 0x38) + *(int *)(self + 0x34) + *(int *)(self + 0x30) +
         *(int *)(self + 0x2c) + *(int *)(self + 0x28) + *(int *)(self + 0x24) +
         *(int *)(self + 0x20) + *(int *)(self + 0x1c) + *(int *)(self + 0x18);
}

