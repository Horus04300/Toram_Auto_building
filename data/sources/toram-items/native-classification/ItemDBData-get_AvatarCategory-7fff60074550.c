
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ItemDBData_get_AvatarCategory(undefined *self,undefined *methodInfo)

{
  return (uint)(byte)self[0x41] * 0x100 + (uint)(byte)self[0x42];
}

