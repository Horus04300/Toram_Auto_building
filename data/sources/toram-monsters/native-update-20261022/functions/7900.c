
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PCChatManager_SetChatType(undefined *self,int level,undefined *methodInfo)

{
  *(int *)(self + 0x160) = level;
  return;
}

