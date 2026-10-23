
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void Toram_Common_Rooms_BossDifficultyLevelMethods__cctor(undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  uint uVar5;
  
  if (DAT_7fff625ef17d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450e80);
    FUN_7fff5f47d450(&DAT_7fff6241fab8);
    FUN_7fff5f47d450(&DAT_7fff62425478);
    FUN_7fff5f47d450(&DAT_7fff6245b570);
    FUN_7fff5f47d450(&DAT_7fff6245bbc8);
    FUN_7fff5f47d450(&DAT_7fff6245bd60);
    FUN_7fff5f47d450(&DAT_7fff6245c088);
    FUN_7fff5f47d450(&DAT_7fff6245c220);
    FUN_7fff5f47d450(&DAT_7fff6245c6e8);
    FUN_7fff5f47d450(&DAT_7fff6245cbb0);
    FUN_7fff5f47d450(&DAT_7fff6245cee0);
    FUN_7fff5f47d450(&DAT_7fff6245d6d8);
    DAT_7fff625ef17d = '\x01';
  }
  uVar4 = func_0x7fff5f47c850(_DAT_7fff62425478,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245c088,0);
  **(undefined8 **)(_DAT_7fff62450e80 + 0xb8) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f47c850(_DAT_7fff62425478,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245cee0,0);
  *(undefined8 *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 8) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f47c850(_DAT_7fff62425478,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245d6d8,0);
  *(undefined8 *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x10) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f47c850(_DAT_7fff6241fab8,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245c6e8,0);
  *(undefined8 *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x18) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f47c850(_DAT_7fff62425478,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245bd60,0);
  *(undefined8 *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x20) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f47c850(_DAT_7fff62425478,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245c220,0);
  *(undefined8 *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x28) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f47c850(_DAT_7fff62425478,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245b570,0);
  *(undefined8 *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x30) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f47c850(_DAT_7fff62425478,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245c088,0);
  *(undefined8 *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x38) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f47c850(_DAT_7fff62425478,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245cbb0,0);
  *(undefined8 *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x40) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f47c850(_DAT_7fff6241fab8,5);
  FUN_7fff60f40820(uVar4,_DAT_7fff6245bbc8,0);
  *(undefined8 *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x48) = uVar4;
  if (_DAT_7fff625f58f8 != 0) {
    uVar5 = (uint)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x48U >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar5 & 0x1fffff) >> 6) * 8 + 0x7fff6263d720);
    do {
      uVar3 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar3 == uVar2) {
        *puVar1 = uVar3 | 1L << (uVar5 & 0x3f);
      }
      UNLOCK();
    } while (uVar3 != uVar2);
  }
  return;
}

