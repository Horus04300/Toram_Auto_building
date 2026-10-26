
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EquipPhysicalBarrierBuf_UpdateBufData(undefined *self,undefined *buf,undefined *methodInfo)

{
  if (DAT_7ffe9cadf3c2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f9258);
    DAT_7ffe9cadf3c2 = '\x01';
  }
  if (buf != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c8f9258 + 0x130) <= *(byte *)(*(longlong *)buf + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)buf + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c8f9258 + 0x130) * 8) == _DAT_7ffe9c8f9258)) {
      *(undefined4 *)(self + 0x28) = *(undefined4 *)(buf + 0x28);
      self[0x1c] = buf[0x1c];
    }
  }
  return;
}

