
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HelpMaster_GetParam(undefined *self,undefined *methodInfo)

{
  return (int)*(short *)(self + 0x10);
}

