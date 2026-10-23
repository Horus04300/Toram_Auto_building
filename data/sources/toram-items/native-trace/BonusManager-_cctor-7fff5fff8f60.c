
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager__cctor(undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  code *pcVar4;
  undefined4 uVar5;
  longlong lVar6;
  undefined8 uVar7;
  uint uVar8;
  
  if (DAT_7fff625e5889 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450248);
    FUN_7fff5f47d450(&DAT_7fff62419120);
    FUN_7fff5f47d450(&DAT_7fff6244dc98);
    FUN_7fff5f47d450(&DAT_7fff6244d800);
    FUN_7fff5f47d450(&DAT_7fff6244dbd0);
    FUN_7fff5f47d450(&DAT_7fff6244d738);
    FUN_7fff5f47d450(&DAT_7fff6240e988);
    FUN_7fff5f47d450(&DAT_7fff6240ea58);
    FUN_7fff5f47d450(&DAT_7fff6244c0e0);
    DAT_7fff625e5889 = '\x01';
  }
  lVar6 = func_0x7fff5f44ff00(_DAT_7fff6240e988);
  FUN_7fff608789f0(lVar6,_DAT_7fff6244d738);
  if (lVar6 != 0) {
    FUN_7fff6087cab0(lVar6,0xb4,1,_DAT_7fff6244d800);
    FUN_7fff6087cab0(lVar6,0xb5,1,_DAT_7fff6244d800);
    FUN_7fff6087cab0(lVar6,0xb6,1,_DAT_7fff6244d800);
    FUN_7fff6087cab0(lVar6,0xb7,1,_DAT_7fff6244d800);
    FUN_7fff6087cab0(lVar6,0xb8,10,_DAT_7fff6244d800);
    FUN_7fff6087cab0(lVar6,0xb9,10,_DAT_7fff6244d800);
    FUN_7fff6087cab0(lVar6,0xba,10,_DAT_7fff6244d800);
    FUN_7fff6087cab0(lVar6,0xbb,10,_DAT_7fff6244d800);
    FUN_7fff6087cab0(lVar6,0xbc,1,_DAT_7fff6244d800);
    **(longlong **)(_DAT_7fff62450248 + 0xb8) = lVar6;
    thunk_FUN_7fff5f491fd0();
    lVar6 = func_0x7fff5f44ff00(_DAT_7fff6240ea58);
    FUN_7fff608789f0(lVar6,_DAT_7fff6244dbd0);
    if (lVar6 != 0) {
      FUN_7fff6088caa0(lVar6,0xc,_DAT_7fff61b52ce4,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0x6e,_DAT_7fff61b52ce4,_DAT_7fff6244dc98);
      uVar5 = _DAT_7fff61b52b40;
      FUN_7fff6088caa0(lVar6,0xbe,_DAT_7fff61b52b40,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0x89,_DAT_7fff61b52b34,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0x8c,_DAT_7fff61b52b34,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xa6,uVar5,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xa7,uVar5,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xa8,uVar5,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xa9,uVar5,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xaa,uVar5,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xab,uVar5,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xac,uVar5,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xad,uVar5,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xae,uVar5,_DAT_7fff6244dc98);
      FUN_7fff6088caa0(lVar6,0xaf,uVar5,_DAT_7fff6244dc98);
      *(longlong *)(*(longlong *)(_DAT_7fff62450248 + 0xb8) + 8) = lVar6;
      thunk_FUN_7fff5f491fd0();
      uVar7 = func_0x7fff5f47c850(_DAT_7fff62419120,6);
      FUN_7fff60f40820(uVar7,_DAT_7fff6244c0e0,0);
      *(undefined8 *)(*(longlong *)(_DAT_7fff62450248 + 0xb8) + 0x10) = uVar7;
      if (_DAT_7fff625f58f8 != 0) {
        uVar8 = (uint)(*(longlong *)(_DAT_7fff62450248 + 0xb8) + 0x10U >> 0xc);
        puVar1 = (ulonglong *)((ulonglong)((uVar8 & 0x1fffff) >> 6) * 8 + 0x7fff6263d720);
        do {
          uVar3 = *puVar1;
          LOCK();
          uVar2 = *puVar1;
          if (uVar3 == uVar2) {
            *puVar1 = uVar3 | 1L << (uVar8 & 0x3f);
          }
          UNLOCK();
        } while (uVar3 != uVar2);
      }
      return;
    }
  }
  FUN_7fff5f47d660();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

