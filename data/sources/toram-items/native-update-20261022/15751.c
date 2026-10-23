
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
  
  if (DAT_7ffe9cade131 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948908);
    FUN_7ffe9996d590(&DAT_7ffe9c911590);
    FUN_7ffe9996d590(&DAT_7ffe9c946d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9468a8);
    FUN_7ffe9996d590(&DAT_7ffe9c946c80);
    FUN_7ffe9996d590(&DAT_7ffe9c9467e8);
    FUN_7ffe9996d590(&DAT_7ffe9c906df8);
    FUN_7ffe9996d590(&DAT_7ffe9c906ec8);
    FUN_7ffe9996d590(&DAT_7ffe9c9459f8);
    DAT_7ffe9cade131 = '\x01';
  }
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c906df8);
  FUN_7ffe9ad6e630(lVar6,_DAT_7ffe9c9467e8);
  if (lVar6 != 0) {
    FUN_7ffe9ad726f0(lVar6,0xb4,1,_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xb5,1,_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xb6,1,_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xb7,1,_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xb8,10,_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xb9,10,_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xba,10,_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xbb,10,_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xbc,1,_DAT_7ffe9c9468a8);
    **(longlong **)(_DAT_7ffe9c948908 + 0xb8) = lVar6;
    il2cpp_write_barrier_0();
    lVar6 = func_0x7ffe99940040(_DAT_7ffe9c906ec8);
    FUN_7ffe9ad6e630(lVar6,_DAT_7ffe9c946c80);
    if (lVar6 != 0) {
      FUN_7ffe9ad826e0(lVar6,0xc,_DAT_7ffe9c049ce4,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0x6e,_DAT_7ffe9c049ce4,_DAT_7ffe9c946d40);
      uVar5 = _DAT_7ffe9c049b40;
      FUN_7ffe9ad826e0(lVar6,0xbe,_DAT_7ffe9c049b40,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0x89,_DAT_7ffe9c049b34,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0x8c,_DAT_7ffe9c049b34,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xa6,uVar5,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xa7,uVar5,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xa8,uVar5,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xa9,uVar5,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xaa,uVar5,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xab,uVar5,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xac,uVar5,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xad,uVar5,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xae,uVar5,_DAT_7ffe9c946d40);
      FUN_7ffe9ad826e0(lVar6,0xaf,uVar5,_DAT_7ffe9c946d40);
      *(longlong *)(*(longlong *)(_DAT_7ffe9c948908 + 0xb8) + 8) = lVar6;
      il2cpp_write_barrier_0();
      uVar7 = func_0x7ffe9996c990(_DAT_7ffe9c911590,6);
      FUN_7ffe9b436460(uVar7,_DAT_7ffe9c9459f8,0);
      *(undefined8 *)(*(longlong *)(_DAT_7ffe9c948908 + 0xb8) + 0x10) = uVar7;
      if (_DAT_7ffe9caee1a8 != 0) {
        uVar8 = (uint)(*(longlong *)(_DAT_7ffe9c948908 + 0xb8) + 0x10U >> 0xc);
        puVar1 = (ulonglong *)((ulonglong)((uVar8 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
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
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

