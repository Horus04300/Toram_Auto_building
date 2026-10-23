
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIItemProperty_ItemDBProperty(undefined *self,int itemId,undefined *methodInfo)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  longlong lVar4;
  longlong *plVar5;
  bool isColor;
  code *pcVar6;
  byte bVar7;
  char cVar8;
  int iVar9;
  longlong lVar10;
  undefined *puVar11;
  undefined *puVar12;
  longlong lVar13;
  longlong lVar14;
  longlong lVar15;
  undefined8 uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  int iVar22;
  longlong lStackX_20;
  
  if (DAT_7ffe9cadbb1f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948908);
    FUN_7ffe9996d590(&DAT_7ffe9c9540a0);
    FUN_7ffe9996d590(&DAT_7ffe9c953710);
    FUN_7ffe9996d590(&DAT_7ffe9c91ef20);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee100);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3b08);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7318);
    FUN_7ffe9996d590(&DAT_7ffe9c920640);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    DAT_7ffe9cadbb1f = '\x01';
  }
  lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c953710);
  if (lVar10 != 0) {
    lVar10 = FUN_7ffe9a57a320(lVar10,itemId,0);
    lStackX_20 = _DAT_7ffe9c8f1820;
    if (lVar10 != 0) {
      lVar4 = *(longlong *)(lVar10 + 0x18);
      iVar20 = 0;
      lVar10 = *(longlong *)(lVar10 + 0x10);
      uVar21 = 0;
      iVar22 = 0;
      lVar14 = _DAT_7ffe9c8f1820;
      do {
        isColor = iVar20 < 1;
        iVar19 = iVar20 + -1;
        if (iVar20 < 1) {
          iVar19 = iVar20;
        }
        iVar20 = iVar19;
        if (lVar10 == 0) goto LAB_7ffe99ec5b16;
        if (*(uint *)(lVar10 + 0x18) <= uVar21) goto LAB_7ffe99ec5b1c;
        lVar13 = (longlong)(int)uVar21 * 2 + 0x20;
        sVar1 = *(short *)(lVar13 + lVar10);
        if (*(int *)(_DAT_7ffe9c948908 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        bVar7 = BonusManager_CheckEquipLimitBonusId(sVar1,(undefined *)0x0);
        if (bVar7 == 0) {
          if (*(uint *)(lVar10 + 0x18) <= uVar21) {
LAB_7ffe99ec5b1c:
            FUN_7ffe9996d790();
            pcVar6 = (code *)swi(3);
            (*pcVar6)();
            return;
          }
          sVar1 = *(short *)(lVar13 + lVar10);
          if (lVar4 == 0) goto LAB_7ffe99ec5b16;
          if (*(uint *)(lVar4 + 0x18) <= uVar21) goto LAB_7ffe99ec5b1c;
          sVar2 = *(short *)(lVar13 + lVar4);
          puVar11 = (undefined *)FUN_7ffe99ec99c0(self,0);
          puVar12 = *(undefined **)(self + 0x70);
          if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          puVar12 = UIItemProperty_AddCapProperty
                              (isColor,sVar1,sVar2,puVar11,puVar12,(undefined *)0x0);
          iVar19 = 0;
          if (puVar12 == (undefined *)0x0) goto LAB_7ffe99ec5b16;
          lVar13 = FUN_7ffe9b370940(puVar12);
          uVar18 = 0;
          while( true ) {
            if (lVar13 == 0) goto LAB_7ffe99ec5b16;
            if ((int)*(uint *)(lVar13 + 0x18) <= (int)uVar18) break;
            if (*(uint *)(lVar13 + 0x18) <= uVar18) goto LAB_7ffe99ec5b1c;
            uVar3 = *(ushort *)(lVar13 + 0x20 + (longlong)(int)uVar18 * 2);
            uVar17 = uVar3 - 0x25;
            if ((((ushort)uVar17 < 0x39) &&
                ((0x17ffffff01ff941U >> ((ulonglong)uVar17 & 0x3f) & 1) != 0)) ||
               (iVar9 = 2, (ushort)(uVar3 - 0x61) < 0x1a)) {
              iVar9 = 1;
            }
            uVar18 = uVar18 + 1;
            iVar19 = iVar19 + iVar9;
          }
          iVar19 = iVar19 + -0x10;
          if (iVar20 == 0) {
            if ((iVar22 < 1) || (iVar19 + iVar22 <= *(int *)(self + 0x98))) {
              lStackX_20 = FUN_7ffe9b366c90(lStackX_20,lVar14,puVar12,_DAT_7ffe9c920640,0);
            }
            else {
              lVar13 = func_0x7ffe9996c990(_DAT_7ffe9c91ef20,5);
              if (lVar13 == 0) goto LAB_7ffe99ec5b16;
              if (*(int *)(lVar13 + 0x18) == 0) goto LAB_7ffe99ec5b1c;
              *(longlong *)(lVar13 + 0x20) = lStackX_20;
              il2cpp_write_barrier_0();
              if (*(uint *)(lVar13 + 0x18) < 2) goto LAB_7ffe99ec5b1c;
              *(longlong *)(lVar13 + 0x28) = lVar14;
              il2cpp_write_barrier_0();
              if (*(uint *)(lVar13 + 0x18) < 3) goto LAB_7ffe99ec5b1c;
              *(undefined8 *)(lVar13 + 0x30) = _DAT_7ffe9c8f3b08;
              il2cpp_write_barrier_0();
              if (*(uint *)(lVar13 + 0x18) < 4) goto LAB_7ffe99ec5b1c;
              *(undefined **)(lVar13 + 0x38) = puVar12;
              il2cpp_write_barrier_0();
              if (*(uint *)(lVar13 + 0x18) < 5) goto LAB_7ffe99ec5b1c;
              *(undefined8 *)(lVar13 + 0x40) = _DAT_7ffe9c920640;
              il2cpp_write_barrier_0();
              lStackX_20 = FUN_7ffe9b366f30(lVar13);
            }
            iVar20 = 0;
            lVar14 = _DAT_7ffe9c8f1820;
          }
          else {
            if (*(int *)(self + 0x98) < iVar19 + iVar22) {
              lStackX_20 = FUN_7ffe9b367290(lStackX_20,lVar14,_DAT_7ffe9c8f3b08,0);
              iVar22 = 0;
              lVar14 = _DAT_7ffe9c8f1820;
            }
            iVar22 = iVar22 + iVar19;
            lVar14 = FUN_7ffe9b367290(lVar14,puVar12,_DAT_7ffe9c8f7318,0);
          }
        }
        else {
          if (lVar14 == 0) goto LAB_7ffe99ec5b16;
          if (0 < *(int *)(lVar14 + 0x10)) {
            lStackX_20 = FUN_7ffe9b367290(lStackX_20,lVar14,_DAT_7ffe9c8f3b08,0);
          }
          lVar14 = **(longlong **)(_DAT_7ffe9c9590b8 + 0xb8);
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c9540a0);
          if ((lVar15 == 0) || (*(longlong *)(lVar15 + 0x28) == 0)) goto LAB_7ffe99ec5b16;
          uVar16 = FUN_7ffe99a873c0(*(longlong *)(lVar15 + 0x28),0);
          if (*(uint *)(lVar10 + 0x18) <= uVar21) goto LAB_7ffe99ec5b1c;
          sVar1 = *(short *)(lVar13 + lVar10);
          if (lVar4 == 0) goto LAB_7ffe99ec5b16;
          if (*(uint *)(lVar4 + 0x18) <= uVar21) goto LAB_7ffe99ec5b1c;
          sVar2 = *(short *)(lVar13 + lVar4);
          puVar11 = (undefined *)FUN_7ffe99ec99c0(self,0);
          puVar12 = *(undefined **)(self + 0x70);
          if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          puVar12 = UIItemProperty_AddCapProperty(0,sVar1,sVar2,puVar11,puVar12,(undefined *)0x0);
          lStackX_20 = FUN_7ffe9b366c90(lStackX_20,uVar16,puVar12,_DAT_7ffe9c8f3b08,0);
          if (*(uint *)(lVar4 + 0x18) <= uVar21) goto LAB_7ffe99ec5b1c;
          iVar20 = (int)*(short *)(lVar13 + lVar4);
        }
        uVar21 = uVar21 + 1;
      } while ((int)uVar21 < 10);
      if (0 < iVar22) {
        lStackX_20 = FUN_7ffe9b367290(lStackX_20,lVar14,_DAT_7ffe9c8f3b08,0);
      }
      plVar5 = *(longlong **)(self + 0x28);
      if (plVar5 != (longlong *)0x0) {
        if (DAT_7ffe9caddb08 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c906b90,lStackX_20,0);
          FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
          DAT_7ffe9caddb08 = '\x01';
        }
        cVar8 = func_0x7ffe9b36bcd0(lStackX_20,0);
        if (cVar8 == '\0') {
          cVar8 = FUN_7ffe9b3715b0(plVar5[0x23],lStackX_20,0);
          if (cVar8 != '\0') {
            plVar5[0x23] = lStackX_20;
            il2cpp_write_barrier_0();
            *(undefined1 *)(plVar5 + 0xb) = 1;
            *(undefined1 *)((longlong)plVar5 + 0x161) = 1;
            lVar10 = plVar5[0x22];
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar8 = FUN_7ffe9bda2160(lVar10,0,0);
            if (cVar8 != '\0') {
              if (plVar5[0x22] == 0) {
                FUN_7ffe9996d7a0();
                pcVar6 = (code *)swi(3);
                (*pcVar6)();
                return;
              }
              FUN_7ffe9a3fbc80(plVar5[0x22],lStackX_20,0);
            }
            if (*(int *)((longlong)plVar5 + 0x14c) == 0) {
                    /* WARNING: Could not recover jumptable at 0x7ffe9a404403. Too many branches */
                    /* WARNING: Treating indirect jump as call */
              (**(code **)(*plVar5 + 0x2b8))(plVar5,*(undefined8 *)(*plVar5 + 0x2c0));
              return;
            }
          }
        }
        else {
          cVar8 = func_0x7ffe9b36bcd0(plVar5[0x23],0);
          if (cVar8 == '\0') {
            plVar5[0x23] = _DAT_7ffe9c8f1820;
            il2cpp_write_barrier_0();
          }
          *(undefined1 *)(plVar5 + 0xb) = 1;
          *(undefined1 *)((longlong)plVar5 + 0x161) = 1;
        }
        return;
      }
    }
  }
LAB_7ffe99ec5b16:
  FUN_7ffe9996d7a0();
  pcVar6 = (code *)swi(3);
  (*pcVar6)();
  return;
}

