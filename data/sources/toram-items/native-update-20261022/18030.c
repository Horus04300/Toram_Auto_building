
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

short ItemData_get_Function(undefined *self,undefined *methodInfo)

{
  return *(short *)(self + 0x42);
}

