
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int AvoidBreaker_GetParam(undefined *self,undefined *methodInfo)

{
  return (int)(byte)self[0x18];
}

