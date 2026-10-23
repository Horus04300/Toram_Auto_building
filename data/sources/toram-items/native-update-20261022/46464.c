
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkillTextManager_Initialize(undefined *self,undefined *binary,undefined *methodInfo)

{
  code *pcVar1;
  ulonglong uVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  longlong lVar6;
  longlong lVar7;
  ulonglong uVar8;
  longlong lVar9;
  longlong *plVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  int iVar15;
  longlong lStack_f0;
  ulonglong uStack_e8;
  longlong lStack_e0;
  undefined8 uStack_d8;
  longlong *plStack_d0;
  longlong lStack_c8;
  longlong lStack_c0;
  ulonglong uStack_b8;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined *puStack_a8;
  undefined8 uStack_98;
  undefined8 uStack_90;
  ulonglong uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_50;
  undefined8 uStack_48;
  ulonglong uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  
  puStack_a8 = self;
  if (DAT_7ffe9cad9df0 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943bb8);
    FUN_7ffe9996d590(&DAT_7ffe9c905ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c906d80);
    FUN_7ffe9996d590(&DAT_7ffe9c906e50);
    FUN_7ffe9996d590(&DAT_7ffe9c906b10);
    FUN_7ffe9996d590(&DAT_7ffe9c907190);
    FUN_7ffe9996d590(&DAT_7ffe9c905e10);
    FUN_7ffe9996d590(&DAT_7ffe9c907260);
    FUN_7ffe9996d590(&DAT_7ffe9c914058);
    FUN_7ffe9996d590(&DAT_7ffe9c9399c8);
    FUN_7ffe9996d590(&DAT_7ffe9c939a88);
    FUN_7ffe9996d590(0x7ffe9c939b50);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(0x7ffe9c96b808);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    FUN_7ffe9996d590(&DAT_7ffe9c94bf18);
    DAT_7ffe9cad9df0 = '\x01';
  }
  iVar15 = 0;
  lStack_f0 = 0;
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  self[0x11] = 0;
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c914058);
  FUN_7ffe9ad214a0(lVar6,_DAT_7ffe9c906b10);
  lStack_c8 = lVar6;
  lVar7 = func_0x7ffe99940040(_DAT_7ffe9c914058);
  lStack_e0 = lVar7;
  FUN_7ffe9ad214a0(lVar7,_DAT_7ffe9c906b10);
  lStack_c0 = lVar7;
  uVar8 = func_0x7ffe99940040(_DAT_7ffe9c914058);
  uStack_e8 = uVar8;
  FUN_7ffe9ad214a0(uVar8,_DAT_7ffe9c906b10);
  uStack_b8 = uVar8;
  if (*(longlong *)(self + 0x18) != 0) {
    FUN_7ffe9acce330(*(longlong *)(self + 0x18),_DAT_7ffe9c905ad0);
    lVar9 = func_0x7ffe99940040(_DAT_7ffe9c969f48);
    FUN_7ffe9b4c0ad0(lVar9,binary,0);
    uStack_d8 = 0;
    plStack_d0 = &lStack_f0;
    lStack_f0 = lVar9;
    plVar10 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c943bb8);
    FUN_7ffe9b4cd430(plVar10,lVar9,0);
    if (plVar10 == (longlong *)0x0) {
LAB_7ffe99a55e37:
      FUN_7ffe9996d7a0();
      FUN_7ffe998fa550();
LAB_7ffe99a55e43:
      FUN_7ffe9996d7a0();
LAB_7ffe99a55e48:
      FUN_7ffe9996d7a0();
    }
    else {
      iVar4 = (**(code **)(*plVar10 + 0x228))(plVar10,*(undefined8 *)(*plVar10 + 0x230));
      while (iVar15 < iVar4) {
        if (plVar10 == (longlong *)0x0) {
LAB_7ffe99a55e32:
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99a55e37;
        }
        uVar5 = (**(code **)(*plVar10 + 0x228))(plVar10,*(undefined8 *)(*plVar10 + 0x230));
        if (plVar10 == (longlong *)0x0) {
LAB_7ffe99a55e2d:
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99a55e32;
        }
        cVar3 = (**(code **)(*plVar10 + 0x1d8))(plVar10,*(undefined8 *)(*plVar10 + 0x1e0));
        if (plVar10 == (longlong *)0x0) {
LAB_7ffe99a55e28:
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99a55e2d;
        }
        uVar11 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
        if (cVar3 == '\0') {
          if (lVar6 == 0) {
LAB_7ffe99a55e23:
            FUN_7ffe9996d7a0();
            goto LAB_7ffe99a55e28;
          }
          FUN_7ffe9ad5ed00(lVar6,uVar5,uVar11,_DAT_7ffe9c907260);
LAB_7ffe99a55ad4:
          iVar15 = iVar15 + 1;
        }
        else if (cVar3 == '\x01') {
          if (lVar7 == 0) goto LAB_7ffe99a55e1e;
          FUN_7ffe9ad5ed00(lVar7,uVar5,uVar11,_DAT_7ffe9c907260);
          iVar15 = iVar15 + 1;
        }
        else {
          if (cVar3 != '\x02') goto LAB_7ffe99a55ad4;
          if (uVar8 == 0) {
            FUN_7ffe9996d7a0();
LAB_7ffe99a55e1e:
            FUN_7ffe9996d7a0();
            goto LAB_7ffe99a55e23;
          }
          FUN_7ffe9ad5ed00(uVar8,uVar5,uVar11,_DAT_7ffe9c907260);
          iVar15 = iVar15 + 1;
        }
      }
      if (plVar10 != (longlong *)0x0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
      if (lVar6 == 0) goto LAB_7ffe99a55e63;
      FUN_7ffe9accf860(&uStack_50,lVar6,_DAT_7ffe9c906e50);
      uStack_98 = uStack_50;
      uStack_90 = uStack_48;
      uStack_88 = uStack_40;
      uStack_80 = uStack_38;
      uStack_78 = uStack_30;
      while( true ) {
        do {
          cVar3 = FUN_7ffe9ae3f410(&uStack_98,_DAT_7ffe9c939a88);
          if (cVar3 == '\0') {
            func_0x7ffe999c3920(&uStack_98,_DAT_7ffe9c9399c8);
            if (*plStack_d0 != 0) {
              FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
            }
            self[0x10] = 1;
            self[0x12] = 0;
            return;
          }
          uStack_b8 = uStack_88;
          uStack_b0 = (undefined4)uStack_80;
          uStack_ac = uStack_80._4_4_;
          if (lVar7 == 0) goto LAB_7ffe99a55e52;
          cVar3 = FUN_7ffe9ad24db0(lVar7,uStack_88 & 0xffffffff,_DAT_7ffe9c906d80);
          uVar2 = uStack_b8;
        } while (cVar3 == '\0');
        if (uVar8 == 0) break;
        cVar3 = FUN_7ffe9ad24db0(uVar8,uStack_b8 & 0xffffffff,_DAT_7ffe9c906d80);
        lVar9 = *(longlong *)(puStack_a8 + 0x18);
        if (cVar3 == '\0') {
          uVar11 = FUN_7ffe9ad356e0(lVar6,uVar2 & 0xffffffff,_DAT_7ffe9c907190);
          uVar12 = FUN_7ffe9ad356e0(lVar7,uVar2 & 0xffffffff,_DAT_7ffe9c907190);
          uVar13 = func_0x7ffe99940040(_DAT_7ffe9c94bf18);
          FUN_7ffe99a54ee0(uVar13,uVar2 & 0xffffffff,uVar11,uVar12,0);
          if (lVar9 == 0) goto LAB_7ffe99a55e48;
          FUN_7ffe9ad5ed00(lVar9,uVar2 & 0xffffffff,uVar13,_DAT_7ffe9c905e10);
          lVar7 = lStack_e0;
        }
        else {
          uVar11 = FUN_7ffe9ad356e0(lVar6,uVar2 & 0xffffffff,_DAT_7ffe9c907190);
          uVar12 = FUN_7ffe9ad356e0(lVar7,uVar2 & 0xffffffff,_DAT_7ffe9c907190);
          uVar13 = FUN_7ffe9ad356e0(uStack_e8,uVar2 & 0xffffffff,_DAT_7ffe9c907190);
          uVar14 = func_0x7ffe99940040(_DAT_7ffe9c94bf18);
          FUN_7ffe99a54f60(uVar14,uVar2 & 0xffffffff,uVar11,uVar12,uVar13,0);
          if (lVar9 == 0) goto LAB_7ffe99a55e43;
          FUN_7ffe9ad5ed00(lVar9,uVar2 & 0xffffffff,uVar14,_DAT_7ffe9c905e10);
          uVar8 = uStack_e8;
          lVar7 = lStack_e0;
        }
      }
    }
    FUN_7ffe9996d7a0();
LAB_7ffe99a55e52:
    FUN_7ffe9996d7a0();
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe99a55e63:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

