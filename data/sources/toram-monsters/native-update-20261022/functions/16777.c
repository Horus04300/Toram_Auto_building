
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidEventData_LoadBossMaster(undefined *self,undefined *binary,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  longlong lVar4;
  byte no;
  byte bVar5;
  byte bVar6;
  byte flag;
  short sVar7;
  short minLevel;
  int iVar8;
  int iVar9;
  longlong lVar10;
  longlong *plVar11;
  undefined *puVar12;
  longlong *plStack_90;
  int iStack_88;
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  longlong alStack_70 [2];
  longlong **pplStack_60;
  undefined8 uStack_58;
  longlong *plStack_50;
  
  if (DAT_7ffe9cade2ff == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943bb8);
    FUN_7ffe9996d590(&DAT_7ffe9c92a790);
    FUN_7ffe9996d590(&DAT_7ffe9c92acf0);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c923158);
    FUN_7ffe9996d590(&DAT_7ffe9c923dd8);
    FUN_7ffe9996d590(0x7ffe9c923220);
    FUN_7ffe9996d590(0x7ffe9c923ea0);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    DAT_7ffe9cade2ff = '\x01';
  }
  iVar8 = 0;
  plStack_90 = (longlong *)0x0;
  if (binary == (undefined *)0x0) {
    return;
  }
  lVar10 = *(longlong *)(self + 0x28);
  if (lVar10 != 0) {
    *(int *)(lVar10 + 0x1c) = *(int *)(lVar10 + 0x1c) + 1;
    iVar9 = *(int *)(lVar10 + 0x18);
    *(undefined4 *)(lVar10 + 0x18) = 0;
    if (0 < iVar9) {
      FUN_7ffe9b518970(*(undefined8 *)(lVar10 + 0x10),0,iVar9,0);
    }
    lVar10 = *(longlong *)(self + 0x38);
    if (lVar10 != 0) {
      *(int *)(lVar10 + 0x1c) = *(int *)(lVar10 + 0x1c) + 1;
      iVar9 = *(int *)(lVar10 + 0x18);
      *(undefined4 *)(lVar10 + 0x18) = 0;
      if (0 < iVar9) {
        FUN_7ffe9b518970(*(undefined8 *)(lVar10 + 0x10),0,iVar9,0);
      }
      lVar10 = func_0x7ffe99940040(_DAT_7ffe9c969f48);
      FUN_7ffe9b4c0ad0(lVar10,binary,0);
      uStack_58 = 0;
      plStack_50 = alStack_70;
      alStack_70[0] = lVar10;
      plVar11 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c943bb8);
      FUN_7ffe9b4cd430(plVar11,lVar10,0);
      alStack_70[1] = 0;
      pplStack_60 = &plStack_90;
      plStack_90 = plVar11;
      if (plVar11 != (longlong *)0x0) {
        (**(code **)(*plVar11 + 0x1d8))(plVar11,*(undefined8 *)(*plVar11 + 0x1e0));
        if (plStack_90 != (longlong *)0x0) {
          iStack_78 = (**(code **)(*plStack_90 + 0x228))
                                (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
          while( true ) {
            iStack_80 = iVar8;
            if (iStack_78 <= iVar8) {
              if (plStack_90 != (longlong *)0x0) {
                FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
              }
              if (alStack_70[0] == 0) {
                return;
              }
              FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
              return;
            }
            if (plStack_90 == (longlong *)0x0) break;
            no = (**(code **)(*plStack_90 + 0x1d8))(plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0))
            ;
            if (plStack_90 == (longlong *)0x0) {
LAB_7ffe9a52a6c3:
              FUN_7ffe9996d7a0();
              break;
            }
            iStack_84 = (**(code **)(*plStack_90 + 0x228))
                                  (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
            if (plStack_90 == (longlong *)0x0) {
LAB_7ffe9a52a6be:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9a52a6c3;
            }
            bVar5 = (**(code **)(*plStack_90 + 0x1d8))
                              (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
            if (plStack_90 == (longlong *)0x0) {
LAB_7ffe9a52a6b9:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9a52a6be;
            }
            bVar6 = (**(code **)(*plStack_90 + 0x1d8))
                              (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
            if (plStack_90 == (longlong *)0x0) {
LAB_7ffe9a52a6b4:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9a52a6b9;
            }
            iStack_88 = (**(code **)(*plStack_90 + 0x228))
                                  (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
            if (plStack_90 == (longlong *)0x0) {
LAB_7ffe9a52a6af:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9a52a6b4;
            }
            iVar8 = (**(code **)(*plStack_90 + 0x228))
                              (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
            if (plStack_90 == (longlong *)0x0) {
LAB_7ffe9a52a6aa:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9a52a6af;
            }
            sVar7 = (**(code **)(*plStack_90 + 0x208))
                              (plStack_90,*(undefined8 *)(*plStack_90 + 0x210));
            if (plStack_90 == (longlong *)0x0) {
LAB_7ffe9a52a6a5:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9a52a6aa;
            }
            minLevel = (**(code **)(*plStack_90 + 0x208))
                                 (plStack_90,*(undefined8 *)(*plStack_90 + 0x210));
            lVar10 = *(longlong *)(self + 0x28);
            puVar12 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c92a790);
            ScoreAttackBossMasterData__ctor
                      (puVar12,no,iStack_84,(uint)bVar5,bVar6,iStack_88,iVar8,sVar7,minLevel,
                       (undefined *)0x0);
            lVar4 = _DAT_7ffe9c923158;
            if (lVar10 == 0) {
LAB_7ffe9a52a6a0:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9a52a6a5;
            }
            *(int *)(lVar10 + 0x1c) = *(int *)(lVar10 + 0x1c) + 1;
            lVar2 = *(longlong *)(lVar10 + 0x10);
            uVar1 = *(uint *)(lVar10 + 0x18);
            if (lVar2 == 0) {
LAB_7ffe9a52a69b:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9a52a6a0;
            }
            if (uVar1 < *(uint *)(lVar2 + 0x18)) {
              *(uint *)(lVar10 + 0x18) = uVar1 + 1;
              if (uVar1 < *(uint *)(lVar2 + 0x18)) {
                *(undefined **)(lVar2 + ((longlong)(int)uVar1 + 4) * 8) = puVar12;
                il2cpp_write_barrier_0();
                goto LAB_7ffe9a52a416;
              }
              FUN_7ffe9996d790();
LAB_7ffe9a52a673:
              FUN_7ffe9996d7a0();
LAB_7ffe9a52a678:
              FUN_7ffe9996d7a0();
LAB_7ffe9a52a67d:
              FUN_7ffe9996d7a0();
LAB_7ffe9a52a682:
              FUN_7ffe9996d7a0();
LAB_7ffe9a52a687:
              FUN_7ffe9996d7a0();
LAB_7ffe9a52a68c:
              FUN_7ffe9996d7a0();
LAB_7ffe9a52a691:
              FUN_7ffe9996d7a0();
LAB_7ffe9a52a696:
              FUN_7ffe9996d7a0();
              goto LAB_7ffe9a52a69b;
            }
            FUN_7ffe9afd58b0(lVar10,puVar12,
                             *(undefined8 *)
                              (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
LAB_7ffe9a52a416:
            if (plStack_90 == (longlong *)0x0) goto LAB_7ffe9a52a696;
            sVar7 = (**(code **)(*plStack_90 + 0x208))
                              (plStack_90,*(undefined8 *)(*plStack_90 + 0x210));
            iStack_88 = CONCAT22(iStack_88._2_2_,sVar7);
            for (iVar8 = 0; iVar8 < sVar7; iVar8 = iVar8 + 1) {
              if (plStack_90 == (longlong *)0x0) goto LAB_7ffe9a52a691;
              bVar5 = (**(code **)(*plStack_90 + 0x1d8))
                                (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
              if (plStack_90 == (longlong *)0x0) goto LAB_7ffe9a52a68c;
              iStack_7c = (**(code **)(*plStack_90 + 0x228))
                                    (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
              if (plStack_90 == (longlong *)0x0) goto LAB_7ffe9a52a687;
              bVar6 = (**(code **)(*plStack_90 + 0x1d8))
                                (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
              if (plStack_90 == (longlong *)0x0) goto LAB_7ffe9a52a682;
              iStack_84 = (**(code **)(*plStack_90 + 0x228))
                                    (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
              if (plStack_90 == (longlong *)0x0) goto LAB_7ffe9a52a67d;
              iVar9 = (**(code **)(*plStack_90 + 0x228))
                                (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
              if (plStack_90 == (longlong *)0x0) goto LAB_7ffe9a52a678;
              flag = (**(code **)(*plStack_90 + 0x1d8))
                               (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
              lVar10 = *(longlong *)(self + 0x38);
              puVar12 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c92acf0);
              HighRaidRewardData__ctor
                        (puVar12,no,bVar5,iStack_7c,bVar6,iStack_84,iVar9,flag,(undefined *)0x0);
              if (lVar10 == 0) goto LAB_7ffe9a52a673;
              FUN_7ffe99743100(lVar10,puVar12,_DAT_7ffe9c923dd8);
              sVar7 = (short)iStack_88;
            }
            iVar8 = iStack_80 + 1;
          }
          FUN_7ffe9996d7a0();
        }
        FUN_7ffe9996d7a0();
      }
      FUN_7ffe9996d7a0();
      FUN_7ffe998fa550();
      FUN_7ffe998fa550();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

