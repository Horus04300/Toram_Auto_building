
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ExclusiveSPBuff_OnGetValue(undefined *thisObject,undefined *id,undefined *methodInfo)

{
  if ((int)id != 2) {
    return 0;
  }
  return *(short *)(thisObject + 0x14) * 3;
}

