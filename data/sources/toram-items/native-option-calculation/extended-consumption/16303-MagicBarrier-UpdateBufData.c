
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicBarrier_UpdateBufData(undefined *self,undefined *buf,undefined *methodInfo)

{
  if (DAT_7ffe9cade23f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95d8f0);
    DAT_7ffe9cade23f = '\x01';
  }
  if (buf != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c95d8f0 + 0x130) <= *(byte *)(*(longlong *)buf + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)buf + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c95d8f0 + 0x130) * 8) == _DAT_7ffe9c95d8f0)) {
      *(undefined4 *)(self + 0x1c) = *(undefined4 *)(buf + 0x1c);
      self[0x12] = buf[0x12];
    }
  }
  return;
}

