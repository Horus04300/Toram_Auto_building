
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkillBufferManager_UpdateFirstAidBuffer(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined *self_00;
  longlong *plVar4;
  
  if (DAT_7ffe9cadf588 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934040);
    FUN_7ffe9996d590(&DAT_7ffe9c9341c8);
    FUN_7ffe9996d590(&DAT_7ffe9c9345a0);
    FUN_7ffe9996d590(&DAT_7ffe9c903f68);
    DAT_7ffe9cadf588 = '\x01';
  }
  if (*(longlong *)(self + 0x40) != 0) {
    cVar3 = FUN_7ffe9ad5f0a0(*(longlong *)(self + 0x40),9,_DAT_7ffe9c9341c8);
    if (cVar3 == '\0') {
      self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c903f68);
      FirstAidBuf__ctor(self_00,1,_DAT_7ffe9c049ddc,(undefined *)0x0);
      if (*(longlong *)(self + 0x40) != 0) {
        FUN_7ffe9ad82760(*(longlong *)(self + 0x40),9,self_00,_DAT_7ffe9c934040);
        if (*(longlong *)(self + 0x50) != 0) {
          lVar1 = *(longlong *)(*(longlong *)(_DAT_7ffe9c934040 + 0x20) + 0xc0);
          FUN_7ffe9ad90730(*(longlong *)(self + 0x50),9,self_00,
                           CONCAT71((int7)((ulonglong)lVar1 >> 8),2),*(undefined8 *)(lVar1 + 0x118))
          ;
          return;
        }
      }
    }
    else if ((*(longlong *)(self + 0x40) != 0) &&
            (plVar4 = (longlong *)FUN_7ffe9ad723c0(*(longlong *)(self + 0x40),9,_DAT_7ffe9c9345a0),
            plVar4 != (longlong *)0x0)) {
      if ((*(byte *)(_DAT_7ffe9c903f68 + 0x130) <= *(byte *)(*plVar4 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar4 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c903f68 + 0x130) * 8)
          == _DAT_7ffe9c903f68)) {
        *(char *)(plVar4 + 2) = (char)plVar4[2] + '\x01';
        if (*(float *)(plVar4 + 4) == 0.0) {
          *(undefined4 *)(plVar4 + 4) = 0x42700000;
        }
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

