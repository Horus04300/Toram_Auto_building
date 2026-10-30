
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FireStyleStrengthenBuff_OnGetValue(undefined *thisObject,undefined *id,undefined *methodInfo)

{
  if ((int)id != 2) {
    return 0;
  }
  return *(int *)(thisObject + 0x18);
}

