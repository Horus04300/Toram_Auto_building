
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FirstAidBuf_InvalidInvincible(undefined *self,undefined *methodInfo)

{
  *(uint *)(self + 0x24) = *(uint *)(self + 0x24) & 0xffffefff;
  *(uint *)(self + 0x24) = *(uint *)(self + 0x24) | 0x800;
  *(undefined4 *)(self + 0x14) = 0;
  return;
}

