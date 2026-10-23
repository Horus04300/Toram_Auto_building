
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusData__ctor(undefined *self,undefined *bonusLines,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  ushort uVar3;
  undefined8 uVar4;
  longlong *plVar5;
  undefined8 *puVar6;
  longlong lVar7;
  longlong lVar8;
  
  if (DAT_7ffe9cade0f3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9485f8);
    FUN_7ffe9996d590(&DAT_7ffe9c948b58);
    FUN_7ffe9996d590(&DAT_7ffe9c948ce0);
    FUN_7ffe9996d590(&DAT_7ffe9c955940);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c953380);
    FUN_7ffe9996d590(&DAT_7ffe9c958be8);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c908e90);
    FUN_7ffe9996d590(&DAT_7ffe9c9085a0);
    FUN_7ffe9996d590(&DAT_7ffe9c909030);
    FUN_7ffe9996d590(&DAT_7ffe9c94afd8);
    FUN_7ffe9996d590(&DAT_7ffe9c908330);
    FUN_7ffe9996d590(&DAT_7ffe9c908cf0);
    FUN_7ffe9996d590(&DAT_7ffe9c970cc0);
    FUN_7ffe9996d590(&DAT_7ffe9c9644b8);
    FUN_7ffe9996d590(&DAT_7ffe9c964580);
    DAT_7ffe9cade0f3 = '\x01';
  }
  uVar4 = func_0x7ffe99940040(_DAT_7ffe9c964580);
  FUN_7ffe9af8a010(uVar4,_DAT_7ffe9c908cf0);
  *(undefined8 *)(self + 0x18) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe99940040(_DAT_7ffe9c970cc0);
  FUN_7ffe9af8a010(uVar4,_DAT_7ffe9c94afd8);
  *(undefined8 *)(self + 0x20) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe99940040(_DAT_7ffe9c964580);
  FUN_7ffe9af8a010(uVar4,_DAT_7ffe9c908cf0);
  *(undefined8 *)(self + 0x28) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe99940040(_DAT_7ffe9c9644b8);
  FUN_7ffe9af8a010(uVar4,_DAT_7ffe9c908330);
  *(undefined8 *)(self + 0x30) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe99940040(_DAT_7ffe9c9644b8);
  FUN_7ffe9af8a010(uVar4,_DAT_7ffe9c908330);
  *(undefined8 *)(self + 0x38) = uVar4;
  il2cpp_write_barrier_0();
  func_0x7ffe999c3920(self,0);
  uVar4 = func_0x7ffe99940040(_DAT_7ffe9c948ce0);
  FUN_7ffe9a4f6190(uVar4,bonusLines,0);
  *(undefined8 *)(self + 0x10) = uVar4;
  il2cpp_write_barrier_0();
  *(undefined4 *)(self + 0x44) = 0;
  self[0x40] = 0;
  if ((*(longlong *)(self + 0x10) == 0) || (*(longlong *)(*(longlong *)(self + 0x10) + 0x28) == 0))
  {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  plVar5 = (longlong *)FUN_7ffe99742ec0(0,_DAT_7ffe9c953380);
  do {
    if (plVar5 == (longlong *)0x0) {
LAB_7ffe9a4e8106:
      FUN_7ffe9996d7a0();
      FUN_7ffe998fa550();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    cVar2 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
    if (cVar2 == '\0') {
      if (plVar5 != (longlong *)0x0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
      return;
    }
    if (plVar5 == (longlong *)0x0) {
LAB_7ffe9a4e8101:
      FUN_7ffe9996d7a0();
      goto LAB_7ffe9a4e8106;
    }
    lVar7 = *plVar5;
    uVar3 = 0;
    if (*(ushort *)(lVar7 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar7 + 0xb0) + (ulonglong)uVar3 * 0x10) ==
            _DAT_7ffe9c958be8) {
          puVar6 = (undefined8 *)
                   (lVar7 + 0x138 +
                   (longlong)*(int *)(*(longlong *)(lVar7 + 0xb0) + 8 + (ulonglong)uVar3 * 0x10) *
                   0x10);
          goto LAB_7ffe9a4e7cc9;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(ushort *)(lVar7 + 0x12e));
    }
    puVar6 = (undefined8 *)FUN_7ffe998ce540(plVar5,_DAT_7ffe9c958be8,0);
LAB_7ffe9a4e7cc9:
    lVar7 = (*(code *)*puVar6)(plVar5,puVar6[1]);
    if (*(int *)(_DAT_7ffe9c9485f8 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c9485f8);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9485f8 + 0xb8) + 0x30);
    if (lVar8 == 0) {
LAB_7ffe9a4e80fc:
      FUN_7ffe9996d7a0();
      goto LAB_7ffe9a4e8101;
    }
    lVar8 = FUN_7ffe9ad723c0(lVar8,0,_DAT_7ffe9c955940);
    if (lVar7 == 0) {
LAB_7ffe9a4e80f7:
      FUN_7ffe9996d7a0();
      goto LAB_7ffe9a4e80fc;
    }
    if (lVar8 == 0) {
LAB_7ffe9a4e80f2:
      FUN_7ffe9996d7a0();
      goto LAB_7ffe9a4e80f7;
    }
    cVar2 = FUN_7ffe9afc8940(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7ffe9c909030);
    if (cVar2 != '\0') {
      if (*(longlong *)(self + 0x18) != 0) {
        FUN_7ffe99744640(*(longlong *)(self + 0x18),*(undefined4 *)(lVar7 + 0x10),_DAT_7ffe9c908e90)
        ;
        goto LAB_7ffe9a4e7d5d;
      }
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80ac:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80b1:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80b6:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80bb:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80c0:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80c5:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80ca:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80cf:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80d4:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80d9:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80de:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80e3:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80e8:
      FUN_7ffe9996d7a0();
LAB_7ffe9a4e80ed:
      FUN_7ffe9996d7a0();
      goto LAB_7ffe9a4e80f2;
    }
LAB_7ffe9a4e7d5d:
    if (*(int *)(_DAT_7ffe9c9485f8 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c9485f8);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9485f8 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7ffe9a4e80ed;
    lVar8 = FUN_7ffe9ad723c0(lVar8,4,_DAT_7ffe9c955940);
    if (lVar8 == 0) goto LAB_7ffe9a4e80e8;
    cVar2 = FUN_7ffe9afc8940(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7ffe9c909030);
    if (cVar2 != '\0') {
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe9a4e80ac;
      FUN_7ffe99744640(*(longlong *)(self + 0x28),*(undefined4 *)(lVar7 + 0x10),_DAT_7ffe9c908e90);
    }
    if (*(int *)(_DAT_7ffe9c9485f8 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c9485f8);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9485f8 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7ffe9a4e80e3;
    lVar8 = FUN_7ffe9ad723c0(lVar8,1,_DAT_7ffe9c955940);
    if (lVar8 == 0) goto LAB_7ffe9a4e80de;
    cVar2 = FUN_7ffe9afc8940(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7ffe9c909030);
    if (cVar2 != '\0') {
      *(undefined4 *)(self + 0x44) = *(undefined4 *)(lVar7 + 0x10);
    }
    if (*(int *)(_DAT_7ffe9c9485f8 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c9485f8);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9485f8 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7ffe9a4e80d9;
    lVar8 = FUN_7ffe9ad723c0(lVar8,5,_DAT_7ffe9c955940);
    if (lVar8 == 0) goto LAB_7ffe9a4e80d4;
    cVar2 = FUN_7ffe9afc8940(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7ffe9c909030);
    if (cVar2 != '\0') {
      if (*(longlong *)(self + 0x38) == 0) goto LAB_7ffe9a4e80b1;
      FUN_7ffe99743100(*(longlong *)(self + 0x38),lVar7,_DAT_7ffe9c9085a0);
    }
    if (*(int *)(_DAT_7ffe9c9485f8 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c9485f8);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9485f8 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7ffe9a4e80cf;
    lVar8 = FUN_7ffe9ad723c0(lVar8,1,_DAT_7ffe9c955940);
    if (lVar8 == 0) goto LAB_7ffe9a4e80ca;
    cVar2 = FUN_7ffe9afc8940(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7ffe9c909030);
    if (cVar2 == '\0') {
      if (*(int *)(_DAT_7ffe9c9485f8 + 0xe0) == 0) {
        func_0x7ffe9996d830(_DAT_7ffe9c9485f8);
      }
      lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9485f8 + 0xb8) + 0x30);
      if (lVar8 == 0) goto LAB_7ffe9a4e80bb;
      lVar8 = FUN_7ffe9ad723c0(lVar8,2,_DAT_7ffe9c955940);
      if (lVar8 == 0) goto LAB_7ffe9a4e80b6;
      cVar2 = FUN_7ffe9afc8940(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7ffe9c909030);
      if (cVar2 != '\0') goto LAB_7ffe9a4e7f8a;
    }
    else {
LAB_7ffe9a4e7f8a:
      self[0x40] = 1;
    }
    if (*(int *)(_DAT_7ffe9c9485f8 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c9485f8);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9485f8 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7ffe9a4e80c5;
    lVar8 = FUN_7ffe9ad723c0(lVar8,3,_DAT_7ffe9c955940);
    if (lVar8 == 0) goto LAB_7ffe9a4e80c0;
    cVar2 = FUN_7ffe9afc8940(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7ffe9c909030);
    if (cVar2 != '\0') {
      self[0x41] = 1;
    }
    if (*(int *)(lVar7 + 0x10) == 0xbd) {
      self[0x48] = 1;
      uVar4 = func_0x7ffe99940040(_DAT_7ffe9c948b58);
      FUN_7ffe9bc6ab30(uVar4,lVar7,0);
      *(undefined8 *)(self + 0x50) = uVar4;
      il2cpp_write_barrier_0();
    }
  } while( true );
}

