
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidBossActionManager_OnSetStatus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  char cVar6;
  ushort uVar7;
  int iVar8;
  longlong lVar9;
  undefined8 uVar10;
  longlong lVar11;
  longlong *plVar12;
  undefined8 *puVar13;
  longlong lVar14;
  ulonglong uVar15;
  undefined4 extraout_XMM0_Da;
  undefined4 uVar16;
  undefined8 uStack_70;
  undefined8 uStack_68;
  ulonglong uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  ulonglong uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  if (DAT_7ffe9cadd535 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9531f8);
    FUN_7ffe9996d590(&DAT_7ffe9c9532c8);
    FUN_7ffe9996d590(&DAT_7ffe9c929768);
    FUN_7ffe9996d590(&DAT_7ffe9c929830);
    FUN_7ffe9996d590(0x7ffe9c9298f8);
    FUN_7ffe9996d590(&DAT_7ffe9c92a6d0);
    FUN_7ffe9996d590(&DAT_7ffe9c936530);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(0x7ffe9c965548);
    FUN_7ffe9996d590(0x7ffe9c965610);
    DAT_7ffe9cadd535 = '\x01';
  }
  lVar14 = *(longlong *)(self + 0x70);
  uVar2 = *(undefined8 *)(self + 0x80);
  uVar3 = *(undefined8 *)(self + 0x88);
  uVar16 = *(undefined4 *)(self + 0x160);
  lVar9 = func_0x7ffe99940040(_DAT_7ffe9c92a6d0);
  if (DAT_7ffe9cadd543 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff130);
    FUN_7ffe9996d590(&DAT_7ffe9c912c08);
    DAT_7ffe9cadd543 = '\x01';
  }
  uVar10 = func_0x7ffe99940040(_DAT_7ffe9c912c08);
  FUN_7ffe9ad214a0(uVar10,_DAT_7ffe9c8ff130);
  *(undefined8 *)(lVar9 + 0x38) = uVar10;
  il2cpp_write_barrier_0();
  func_0x7ffe999c3920(lVar9,0);
  *(longlong *)(lVar9 + 0x10) = lVar14;
  il2cpp_write_barrier_0();
  *(undefined8 *)(lVar9 + 0x18) = uVar2;
  il2cpp_write_barrier_0();
  *(undefined8 *)(lVar9 + 0x20) = uVar3;
  il2cpp_write_barrier_0();
  *(undefined4 *)(lVar9 + 0x30) = uVar16;
  plVar1 = (longlong *)(self + 0x158);
  *plVar1 = lVar9;
  il2cpp_write_barrier_0();
  if (*plVar1 != 0) {
    FUN_7ffe99742c60(0x14,_DAT_7ffe9c93ed20,*plVar1,*(undefined8 *)(self + 0x78));
    if (*(longlong *)(self + 0x168) != 0) {
      iVar8 = func_0x7ffe9acd8120(*(longlong *)(self + 0x168),_DAT_7ffe9c9532c8);
      if (0 < iVar8) {
        if (*(longlong *)(self + 0x168) == 0) goto LAB_7ffe9a321e5b;
        FUN_7ffe9accf860(&uStack_48,*(longlong *)(self + 0x168),_DAT_7ffe9c9531f8);
        uStack_70 = uStack_48;
        uStack_68 = uStack_40;
        uStack_60 = uStack_38;
        uStack_58 = uStack_30;
        uStack_50 = uStack_28;
        while( true ) {
          cVar6 = FUN_7ffe9ae376b0(&uStack_70,_DAT_7ffe9c929830);
          uVar2 = uStack_58;
          lVar9 = _DAT_7ffe9c936530;
          if (cVar6 == '\0') break;
          lVar4 = *plVar1;
          uVar15 = uStack_60 & 0xff;
          if (lVar4 == 0) {
            FUN_7ffe9996d7a0();
LAB_7ffe9a321e41:
            uVar16 = FUN_7ffe9996c950(lVar4,lVar14);
LAB_7ffe9a321e4c:
            FUN_7ffe9996c950(uVar16,lVar9);
            FUN_7ffe998fa550();
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
          lVar11 = func_0x7ffe9996c920(lVar4,_DAT_7ffe9c936530);
          lVar14 = _DAT_7ffe9c936530;
          uVar16 = extraout_XMM0_Da;
          if (lVar11 == 0) goto LAB_7ffe9a321e4c;
          plVar12 = (longlong *)func_0x7ffe9996c920(lVar4,_DAT_7ffe9c936530);
          lVar9 = 0;
          if (plVar12 == (longlong *)0x0) goto LAB_7ffe9a321e41;
          lVar9 = *plVar12;
          uVar7 = 0;
          if (*(ushort *)(lVar9 + 0x12e) != 0) {
            do {
              if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar7 * 0x10) ==
                  _DAT_7ffe9c936530) {
                puVar13 = (undefined8 *)
                          (lVar9 + 0x138 +
                          (longlong)
                          (*(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar7 * 0x10) + 1)
                          * 0x10);
                goto LAB_7ffe9a321db6;
              }
              uVar7 = uVar7 + 1;
            } while (uVar7 < *(ushort *)(lVar9 + 0x12e));
          }
          puVar13 = (undefined8 *)FUN_7ffe998ce540(plVar12,_DAT_7ffe9c936530,1);
LAB_7ffe9a321db6:
          (*(code *)*puVar13)(plVar12,uVar15,uVar2,puVar13[1]);
        }
        func_0x7ffe999c3920(&uStack_70,_DAT_7ffe9c929768);
      }
      return;
    }
  }
LAB_7ffe9a321e5b:
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

