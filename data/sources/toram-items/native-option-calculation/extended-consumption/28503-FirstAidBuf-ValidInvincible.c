
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FirstAidBuf_ValidInvincible(undefined *self,float time,undefined *methodInfo)

{
  *(uint *)(self + 0x24) = *(uint *)(self + 0x24) & 0xfffff7ff;
  *(uint *)(self + 0x24) = *(uint *)(self + 0x24) | 0x1000;
  *(float *)(self + 0x14) = time;
  return;
}

