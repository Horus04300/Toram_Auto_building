
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FirstAidBuf_GetParam(undefined *self,int id,undefined *methodInfo)

{
  if ((self[0x1c] != '\0') && (id == 0xe)) {
    return ((byte)self[0x10] + 1) * 100;
  }
  return 0;
}

