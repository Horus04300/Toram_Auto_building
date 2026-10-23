
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BossMobActionManager_OnSetStatus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  code *pcVar5;
  byte bVar6;
  char cVar7;
  short sVar8;
  int iVar9;
  undefined *self_00;
  longlong lVar10;
  undefined8 uVar11;
  undefined8 *puVar12;
  longlong *plVar13;
  undefined8 uVar14;
  ushort uVar15;
  longlong *unaff_RSI;
  ulonglong uVar16;
  longlong *unaff_R14;
  undefined4 extraout_XMM0_Da;
  undefined4 uVar17;
  undefined8 uStack_80;
  undefined8 uStack_78;
  ulonglong uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  ulonglong uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  if (DAT_7ffe9cadd1c2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949790);
    FUN_7ffe9996d590(&DAT_7ffe9c9531f8);
    FUN_7ffe9996d590(&DAT_7ffe9c9532c8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f2098);
    FUN_7ffe9996d590(&DAT_7ffe9c8f2988);
    FUN_7ffe9996d590(&DAT_7ffe9c929768);
    FUN_7ffe9996d590(&DAT_7ffe9c929830);
    FUN_7ffe9996d590(0x7ffe9c9298f8);
    FUN_7ffe9996d590(&DAT_7ffe9c936530);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(0x7ffe9c965548);
    FUN_7ffe9996d590(0x7ffe9c965610);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    DAT_7ffe9cadd1c2 = '\x01';
  }
  bVar6 = MobStatusMasterEx_CheckMultiFlag
                    (*(undefined **)(self + 0x70),(undefined *)0x10,(undefined *)0x0);
  if (bVar6 == 0) {
    unaff_R14 = *(longlong **)(self + 0x70);
    uVar3 = *(undefined8 *)(self + 0x80);
    uVar4 = *(undefined8 *)(self + 0x88);
    self_00 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (self_00 != (undefined *)0x0) {
      sVar8 = RoomManager_GetAreaLevel(self_00,(undefined *)0x0);
      lVar10 = func_0x7ffe99940040(_DAT_7ffe9c949790);
      if (DAT_7ffe9cadd1cb == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c8ff130);
        FUN_7ffe9996d590(&DAT_7ffe9c912c08);
        DAT_7ffe9cadd1cb = '\x01';
      }
      uVar11 = func_0x7ffe99940040(_DAT_7ffe9c912c08);
      FUN_7ffe9ad214a0(uVar11,_DAT_7ffe9c8ff130);
      *(undefined8 *)(lVar10 + 0x30) = uVar11;
      il2cpp_write_barrier_0();
      func_0x7ffe999c3920(lVar10,0);
      *(short *)(lVar10 + 0x28) = sVar8;
      *(longlong **)(lVar10 + 0x10) = unaff_R14;
      il2cpp_write_barrier_0();
      *(undefined8 *)(lVar10 + 0x18) = uVar3;
      il2cpp_write_barrier_0();
      *(undefined8 *)(lVar10 + 0x20) = uVar4;
      il2cpp_write_barrier_0();
      plVar1 = (longlong *)(self + 0x158);
      *plVar1 = lVar10;
      il2cpp_write_barrier_0();
      plVar13 = (longlong *)*plVar1;
      unaff_RSI = *(longlong **)(self + 0x78);
      unaff_R14 = plVar1;
      if (plVar13 != (longlong *)0x0) {
        lVar10 = *plVar13;
        if (*(ushort *)(lVar10 + 0x12e) != 0) {
          uVar15 = 0;
          do {
            if (*(longlong *)(*(longlong *)(lVar10 + 0xb0) + (ulonglong)uVar15 * 0x10) ==
                _DAT_7ffe9c93ed20) {
              puVar12 = (undefined8 *)
                        (lVar10 + 0x138 +
                        (longlong)
                        (*(int *)(*(longlong *)(lVar10 + 0xb0) + 8 + (ulonglong)uVar15 * 0x10) +
                        0x14) * 0x10);
              goto LAB_7ffe9a2a53e9;
            }
            uVar15 = uVar15 + 1;
          } while (uVar15 < *(ushort *)(lVar10 + 0x12e));
        }
        puVar12 = (undefined8 *)FUN_7ffe998ce540(plVar13,_DAT_7ffe9c93ed20,0x14);
LAB_7ffe9a2a53e9:
        (*(code *)*puVar12)(plVar13,unaff_RSI,puVar12[1]);
        if (*(longlong *)(self + 0x168) != 0) {
          iVar9 = func_0x7ffe9acd8120(*(longlong *)(self + 0x168),_DAT_7ffe9c9532c8);
          if (0 < iVar9) {
            if (*(longlong *)(self + 0x168) == 0) goto LAB_7ffe9a2a56a3;
            FUN_7ffe9accf860(&uStack_58,*(longlong *)(self + 0x168),_DAT_7ffe9c9531f8);
            uStack_80 = uStack_58;
            uStack_78 = uStack_50;
            uStack_70 = uStack_48;
            uStack_68 = uStack_40;
            uStack_60 = uStack_38;
            while (cVar7 = FUN_7ffe9ae376b0(&uStack_80,_DAT_7ffe9c929830), uVar3 = uStack_68,
                  unaff_RSI = _DAT_7ffe9c936530, cVar7 != '\0') {
              self = (undefined *)*plVar1;
              uVar16 = uStack_70 & 0xff;
              unaff_R14 = plVar1;
              if (self == (undefined *)0x0) goto LAB_7ffe9a2a56a9;
              lVar10 = func_0x7ffe9996c920(self,_DAT_7ffe9c936530);
              unaff_R14 = _DAT_7ffe9c936530;
              uVar17 = extraout_XMM0_Da;
              if (lVar10 == 0) goto LAB_7ffe9a2a56ba;
              plVar13 = (longlong *)func_0x7ffe9996c920(self,_DAT_7ffe9c936530);
              unaff_RSI = (longlong *)0x0;
              if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a2a56af;
              lVar10 = *plVar13;
              if (*(ushort *)(lVar10 + 0x12e) != 0) {
                uVar15 = 0;
                do {
                  if (*(longlong **)(*(longlong *)(lVar10 + 0xb0) + (ulonglong)uVar15 * 0x10) ==
                      _DAT_7ffe9c936530) {
                    puVar12 = (undefined8 *)
                              (lVar10 + 0x138 +
                              (longlong)
                              (*(int *)(*(longlong *)(lVar10 + 0xb0) + 8 + (ulonglong)uVar15 * 0x10)
                              + 1) * 0x10);
                    goto LAB_7ffe9a2a5558;
                  }
                  uVar15 = uVar15 + 1;
                } while (uVar15 < *(ushort *)(lVar10 + 0x12e));
              }
              puVar12 = (undefined8 *)FUN_7ffe998ce540(plVar13,_DAT_7ffe9c936530,1);
LAB_7ffe9a2a5558:
              (*(code *)*puVar12)(plVar13,uVar16,uVar3,puVar12[1]);
            }
            func_0x7ffe999c3920(&uStack_80,_DAT_7ffe9c929768);
          }
          return;
        }
      }
    }
  }
  else {
    lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if ((lVar10 != 0) && (plVar1 = *(longlong **)(lVar10 + 0x28), plVar1 != (longlong *)0x0)) {
      if ((*(byte *)(_DAT_7ffe9c8f2988 + 0x130) <= *(byte *)(*plVar1 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f2988 + 0x130) * 8)
          == _DAT_7ffe9c8f2988)) {
        uVar3 = *(undefined8 *)(self + 0x70);
        uVar4 = *(undefined8 *)(self + 0x80);
        uVar11 = *(undefined8 *)(self + 0x88);
        uVar17 = *(undefined4 *)((longlong)plVar1 + 0x74);
        uVar2 = *(undefined4 *)((longlong)plVar1 + 0x7c);
        lVar10 = plVar1[0xf];
        uVar14 = func_0x7ffe99940040(_DAT_7ffe9c8f2098);
        FUN_7ffe9a30a920(uVar14,uVar3,uVar4,uVar11,uVar17,uVar2,(int)lVar10,0);
        *(undefined8 *)(self + 0x158) = uVar14;
        il2cpp_write_barrier_0();
        return;
      }
      FUN_7ffe9996c950(plVar1);
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
  }
LAB_7ffe9a2a56a3:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2a56a9:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2a56af:
  uVar17 = FUN_7ffe9996c950(self,unaff_R14);
LAB_7ffe9a2a56ba:
  FUN_7ffe9996c950(uVar17,unaff_RSI);
  FUN_7ffe998fa550();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

