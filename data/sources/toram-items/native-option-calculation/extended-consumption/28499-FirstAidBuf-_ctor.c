
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FirstAidBuf__ctor(undefined *self,byte lv,float time,undefined *methodInfo)

{
  *(undefined4 *)(self + 0x24) = 0xa00;
  FUN_7ffe9a7a2160(self,lv,1,0);
  *(float *)(self + 0x20) = time;
  return;
}

