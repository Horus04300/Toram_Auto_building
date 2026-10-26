
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GameEventManager_SetOngoingGameEventType
               (undefined *self,undefined *ongoingGameEventType,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  undefined8 uVar3;
  code *pcVar4;
  longlong *plVar5;
  char cVar6;
  undefined1 uVar7;
  int iVar8;
  longlong lVar9;
  undefined8 *puVar10;
  longlong lVar11;
  longlong lVar12;
  ushort uVar13;
  uint uVar14;
  uint uVar15;
  longlong *aplStack_58 [2];
  undefined8 uStack_48;
  longlong **pplStack_40;
  
  if (DAT_7ffe9cade2c1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90a210);
    FUN_7ffe9996d590(0x7ffe9c90a2e0);
    DAT_7ffe9cade2c1 = '\x01';
  }
  lVar2 = *(longlong *)(self + 0x40);
  if (lVar2 != 0) {
    *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
    *(undefined4 *)(lVar2 + 0x18) = 0;
    lVar2 = *(longlong *)(self + 0x40);
    if (lVar2 != 0) {
      uVar15 = *(uint *)(lVar2 + 0x18);
      lVar12 = *(longlong *)(*(longlong *)(*(longlong *)(_DAT_7ffe9c90a210 + 0x20) + 0xc0) + 0x90);
      if (DAT_7ffe9cae1d0c == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c939b40);
        FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
        DAT_7ffe9cae1d0c = '\x01';
      }
      aplStack_58[0] = (longlong *)0x0;
      if (ongoingGameEventType == (undefined *)0x0) {
        FUN_7ffe9b527f80(6,0);
      }
      if (*(uint *)(lVar2 + 0x18) < uVar15) {
        FUN_7ffe9b528100(0);
      }
      lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(lVar12 + 0x20) + 0xc0) + 0x28);
      if ((*(byte *)(lVar9 + 0x135) & 1) == 0) {
        lVar9 = FUN_7ffe998ced40(lVar9);
      }
      lVar9 = func_0x7ffe9996c920(ongoingGameEventType,lVar9);
      if (lVar9 == 0) {
        if ((int)uVar15 < *(int *)(lVar2 + 0x18)) {
          if (ongoingGameEventType == (undefined *)0x0) {
            FUN_7ffe9996d7a0();
            pcVar4 = (code *)swi(3);
            (*pcVar4)();
            return;
          }
          lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(lVar12 + 0x20) + 0xc0) + 0x20);
          if ((*(byte *)(lVar9 + 0x135) & 1) == 0) {
            lVar9 = FUN_7ffe998ced40(lVar9);
          }
          aplStack_58[0] = (longlong *)FUN_7ffe99742ec0(0,lVar9,ongoingGameEventType);
          uStack_48 = 0;
          pplStack_40 = aplStack_58;
          do {
            if (aplStack_58[0] == (longlong *)0x0) {
LAB_7ffe9afaf5a2:
              FUN_7ffe9996d7a0();
              FUN_7ffe998fa550();
              pcVar4 = (code *)swi(3);
              (*pcVar4)();
              return;
            }
            cVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
            plVar5 = aplStack_58[0];
            if (cVar6 == '\0') {
              if (aplStack_58[0] != (longlong *)0x0) {
                FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
              }
              goto LAB_7ffe9afaf57a;
            }
            if (aplStack_58[0] == (longlong *)0x0) {
LAB_7ffe9afaf59d:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9afaf5a2;
            }
            lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(lVar12 + 0x20) + 0xc0) + 0x140);
            if ((*(byte *)(lVar9 + 0x135) & 1) == 0) {
              lVar9 = FUN_7ffe998ced40(lVar9);
            }
            lVar11 = *plVar5;
            uVar13 = 0;
            if (*(ushort *)(lVar11 + 0x12e) != 0) {
              do {
                if (*(longlong *)(*(longlong *)(lVar11 + 0xb0) + (ulonglong)uVar13 * 0x10) == lVar9)
                {
                  puVar10 = (undefined8 *)
                            (lVar11 + 0x138 +
                            (longlong)
                            *(int *)(*(longlong *)(lVar11 + 0xb0) + 8 + (ulonglong)uVar13 * 0x10) *
                            0x10);
                  goto LAB_7ffe9afaf2e7;
                }
                uVar13 = uVar13 + 1;
              } while (uVar13 < *(ushort *)(lVar11 + 0x12e));
            }
            puVar10 = (undefined8 *)FUN_7ffe998ce540(plVar5);
LAB_7ffe9afaf2e7:
            uVar7 = (*(code *)*puVar10)(plVar5,puVar10[1]);
            lVar9 = *(longlong *)(*(longlong *)(*(longlong *)(lVar12 + 0x20) + 0xc0) + 0x158);
            if (*(uint *)(lVar2 + 0x18) < uVar15) {
              FUN_7ffe9b527fb0();
            }
            lVar11 = *(longlong *)(lVar2 + 0x10);
            if (lVar11 == 0) {
LAB_7ffe9afaf598:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9afaf59d;
            }
            if (*(int *)(lVar2 + 0x18) == *(int *)(lVar11 + 0x18)) {
              uVar1 = *(int *)(lVar2 + 0x18) + 1;
              if (*(int *)(lVar11 + 0x18) < (int)uVar1) {
                if (*(longlong *)(lVar11 + 0x18) == 0) {
                  uVar14 = 4;
                }
                else {
                  uVar14 = *(int *)(lVar11 + 0x18) * 2;
                  if (0x7fefffff < uVar14) {
                    uVar14 = 0x7fefffff;
                  }
                }
                if ((int)uVar1 <= (int)uVar14) {
                  uVar1 = uVar14;
                }
                FUN_7ffe997b8720(lVar2,uVar1,
                                 *(undefined8 *)
                                  (*(longlong *)
                                    (*(longlong *)
                                      (*(longlong *)
                                        (*(longlong *)(*(longlong *)(lVar9 + 0x20) + 0xc0) + 0x78) +
                                      0x20) + 0xc0) + 0xf0));
              }
            }
            if ((int)uVar15 < *(int *)(lVar2 + 0x18)) {
              FUN_7ffe9b519180(*(undefined8 *)(lVar2 + 0x10),uVar15,*(undefined8 *)(lVar2 + 0x10),
                               uVar15 + 1,*(int *)(lVar2 + 0x18) - uVar15,0);
            }
            lVar9 = *(longlong *)(lVar2 + 0x10);
            if (lVar9 == 0) {
LAB_7ffe9afaf593:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9afaf598;
            }
            if (*(uint *)(lVar9 + 0x18) <= uVar15) {
              FUN_7ffe9996d790();
              goto LAB_7ffe9afaf593;
            }
            *(undefined1 *)((longlong)(int)uVar15 + 0x20 + lVar9) = uVar7;
            *(int *)(lVar2 + 0x18) = *(int *)(lVar2 + 0x18) + 1;
            *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
            uVar15 = uVar15 + 1;
          } while( true );
        }
        FUN_7ffe9afab210(lVar2,ongoingGameEventType,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar12 + 0x20) + 0xc0) + 0x40))
        ;
      }
      else {
        lVar11 = *(longlong *)(*(longlong *)(*(longlong *)(lVar12 + 0x20) + 0xc0) + 0x28);
        if ((*(byte *)(lVar11 + 0x135) & 1) == 0) {
          lVar11 = FUN_7ffe998ced40(lVar11);
        }
        iVar8 = FUN_7ffe99742ec0(0,lVar11,lVar9);
        if (0 < iVar8) {
          FUN_7ffe997b8260(lVar2,*(int *)(lVar2 + 0x18) + iVar8,
                           *(undefined8 *)
                            (*(longlong *)(*(longlong *)(lVar12 + 0x20) + 0xc0) + 0x78));
          if ((int)uVar15 < *(int *)(lVar2 + 0x18)) {
            FUN_7ffe9b519180(*(undefined8 *)(lVar2 + 0x10),uVar15,*(undefined8 *)(lVar2 + 0x10),
                             iVar8 + uVar15,*(int *)(lVar2 + 0x18) - uVar15,0);
          }
          uVar3 = *(undefined8 *)(lVar2 + 0x10);
          if (lVar2 == lVar9) {
            FUN_7ffe9b519180(uVar3,0,uVar3,uVar15,uVar15,0);
            FUN_7ffe9b519180(*(undefined8 *)(lVar2 + 0x10),iVar8 + uVar15,
                             *(undefined8 *)(lVar2 + 0x10),uVar15 * 2,
                             *(int *)(lVar2 + 0x18) - uVar15,0);
          }
          else {
            lVar12 = *(longlong *)(*(longlong *)(*(longlong *)(lVar12 + 0x20) + 0xc0) + 0x28);
            if ((*(byte *)(lVar12 + 0x135) & 1) == 0) {
              lVar12 = FUN_7ffe998ced40(lVar12);
            }
            FUN_7ffe99757ef0(5,lVar12,lVar9,uVar3,uVar15);
          }
          *(int *)(lVar2 + 0x18) = *(int *)(lVar2 + 0x18) + iVar8;
        }
      }
LAB_7ffe9afaf57a:
      *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

