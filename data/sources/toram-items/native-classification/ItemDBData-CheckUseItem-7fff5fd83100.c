
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ItemDBData_CheckUseItem(int type,undefined *methodInfo)

{
  return (type == 5 || (type == 0x32 || type == 0x1e)) || type < 3;
}

