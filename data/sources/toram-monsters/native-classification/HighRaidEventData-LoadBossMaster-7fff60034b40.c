
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidEventData_LoadBossMaster(undefined *self,undefined *binary,undefined *methodInfo)

{
  int iVar1;
  uint uVar2;
  longlong lVar3;
  code *pcVar4;
  longlong lVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined2 uVar11;
  undefined2 uVar12;
  short sVar13;
  undefined4 uVar14;
  longlong lVar15;
  longlong *plVar16;
  undefined8 uVar17;
  int iVar18;
  longlong *plStack_90;
  undefined4 uStack_88;
  undefined4 uStack_84;
  int iStack_80;
  undefined4 uStack_7c;
  int iStack_78;
  longlong alStack_70 [2];
  longlong **pplStack_60;
  undefined8 uStack_58;
  longlong *plStack_50;
  
  if (DAT_7fff625e5a57 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b500);
    FUN_7fff5f47d450(&DAT_7fff62432018);
    FUN_7fff5f47d450(&DAT_7fff62432570);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff6242a0d8);
    FUN_7fff5f47d450(&DAT_7fff6242ad58);
    FUN_7fff5f47d450(0x7fff6242a1a0);
    FUN_7fff5f47d450(0x7fff6242ae20);
    FUN_7fff5f47d450(&DAT_7fff624717c0);
    DAT_7fff625e5a57 = '\x01';
  }
  iVar18 = 0;
  plStack_90 = (longlong *)0x0;
  if (binary == (undefined *)0x0) {
    return;
  }
  lVar15 = *(longlong *)(self + 0x28);
  if (lVar15 != 0) {
    *(int *)(lVar15 + 0x1c) = *(int *)(lVar15 + 0x1c) + 1;
    iVar1 = *(int *)(lVar15 + 0x18);
    *(undefined4 *)(lVar15 + 0x18) = 0;
    if (0 < iVar1) {
      FUN_7fff61022d30(*(undefined8 *)(lVar15 + 0x10),0,iVar1,0);
    }
    lVar15 = *(longlong *)(self + 0x38);
    if (lVar15 != 0) {
      *(int *)(lVar15 + 0x1c) = *(int *)(lVar15 + 0x1c) + 1;
      iVar1 = *(int *)(lVar15 + 0x18);
      *(undefined4 *)(lVar15 + 0x18) = 0;
      if (0 < iVar1) {
        FUN_7fff61022d30(*(undefined8 *)(lVar15 + 0x10),0,iVar1,0);
      }
      lVar15 = func_0x7fff5f44ff00(_DAT_7fff624717c0);
      FUN_7fff60fcae90(lVar15,binary,0);
      uStack_58 = 0;
      plStack_50 = alStack_70;
      alStack_70[0] = lVar15;
      plVar16 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6244b500);
      FUN_7fff60fd77f0(plVar16,lVar15,0);
      alStack_70[1] = 0;
      pplStack_60 = &plStack_90;
      plStack_90 = plVar16;
      if (plVar16 != (longlong *)0x0) {
        (**(code **)(*plVar16 + 0x1d8))(plVar16,*(undefined8 *)(*plVar16 + 0x1e0));
        if (plStack_90 != (longlong *)0x0) {
          iStack_78 = (**(code **)(*plStack_90 + 0x228))
                                (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
          while( true ) {
            iStack_80 = iVar18;
            if (iStack_78 <= iVar18) {
              if (plStack_90 != (longlong *)0x0) {
                FUN_7fff5f253010(0,_DAT_7fff624413c0);
              }
              if (alStack_70[0] == 0) {
                return;
              }
              FUN_7fff5f253010(0,_DAT_7fff624413c0);
              return;
            }
            if (plStack_90 == (longlong *)0x0) break;
            uVar6 = (**(code **)(*plStack_90 + 0x1d8))
                              (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
            if (plStack_90 == (longlong *)0x0) {
LAB_7fff600351b3:
              FUN_7fff5f47d660();
              break;
            }
            uStack_84 = (**(code **)(*plStack_90 + 0x228))
                                  (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
            if (plStack_90 == (longlong *)0x0) {
LAB_7fff600351ae:
              FUN_7fff5f47d660();
              goto LAB_7fff600351b3;
            }
            uVar7 = (**(code **)(*plStack_90 + 0x1d8))
                              (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
            if (plStack_90 == (longlong *)0x0) {
LAB_7fff600351a9:
              FUN_7fff5f47d660();
              goto LAB_7fff600351ae;
            }
            uVar8 = (**(code **)(*plStack_90 + 0x1d8))
                              (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
            if (plStack_90 == (longlong *)0x0) {
LAB_7fff600351a4:
              FUN_7fff5f47d660();
              goto LAB_7fff600351a9;
            }
            uStack_88 = (**(code **)(*plStack_90 + 0x228))
                                  (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
            if (plStack_90 == (longlong *)0x0) {
LAB_7fff6003519f:
              FUN_7fff5f47d660();
              goto LAB_7fff600351a4;
            }
            uVar14 = (**(code **)(*plStack_90 + 0x228))
                               (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
            if (plStack_90 == (longlong *)0x0) {
LAB_7fff6003519a:
              FUN_7fff5f47d660();
              goto LAB_7fff6003519f;
            }
            uVar11 = (**(code **)(*plStack_90 + 0x208))
                               (plStack_90,*(undefined8 *)(*plStack_90 + 0x210));
            if (plStack_90 == (longlong *)0x0) {
LAB_7fff60035195:
              FUN_7fff5f47d660();
              goto LAB_7fff6003519a;
            }
            uVar12 = (**(code **)(*plStack_90 + 0x208))
                               (plStack_90,*(undefined8 *)(*plStack_90 + 0x210));
            lVar15 = *(longlong *)(self + 0x28);
            uVar17 = func_0x7fff5f44ff00(_DAT_7fff62432018);
            FUN_7fff60362ac0(uVar17,uVar6,uStack_84,uVar7,uVar8,uStack_88,uVar14,uVar11,uVar12,0);
            lVar5 = _DAT_7fff6242a0d8;
            if (lVar15 == 0) {
LAB_7fff60035190:
              FUN_7fff5f47d660();
              goto LAB_7fff60035195;
            }
            *(int *)(lVar15 + 0x1c) = *(int *)(lVar15 + 0x1c) + 1;
            lVar3 = *(longlong *)(lVar15 + 0x10);
            uVar2 = *(uint *)(lVar15 + 0x18);
            if (lVar3 == 0) {
LAB_7fff6003518b:
              FUN_7fff5f47d660();
              goto LAB_7fff60035190;
            }
            if (uVar2 < *(uint *)(lVar3 + 0x18)) {
              *(uint *)(lVar15 + 0x18) = uVar2 + 1;
              if (uVar2 < *(uint *)(lVar3 + 0x18)) {
                *(undefined8 *)(lVar3 + ((longlong)(int)uVar2 + 4) * 8) = uVar17;
                thunk_FUN_7fff5f491fd0();
                goto LAB_7fff60034f06;
              }
              FUN_7fff5f47d650();
LAB_7fff60035163:
              FUN_7fff5f47d660();
LAB_7fff60035168:
              FUN_7fff5f47d660();
LAB_7fff6003516d:
              FUN_7fff5f47d660();
LAB_7fff60035172:
              FUN_7fff5f47d660();
LAB_7fff60035177:
              FUN_7fff5f47d660();
LAB_7fff6003517c:
              FUN_7fff5f47d660();
LAB_7fff60035181:
              FUN_7fff5f47d660();
LAB_7fff60035186:
              FUN_7fff5f47d660();
              goto LAB_7fff6003518b;
            }
            FUN_7fff60adfc70(lVar15,uVar17,
                             *(undefined8 *)
                              (*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
LAB_7fff60034f06:
            if (plStack_90 == (longlong *)0x0) goto LAB_7fff60035186;
            sVar13 = (**(code **)(*plStack_90 + 0x208))
                               (plStack_90,*(undefined8 *)(*plStack_90 + 0x210));
            uStack_88 = CONCAT22(uStack_88._2_2_,sVar13);
            for (iVar18 = 0; uVar7 = (undefined1)((ushort)uVar11 >> 8), iVar18 < sVar13;
                iVar18 = iVar18 + 1) {
              if (plStack_90 == (longlong *)0x0) goto LAB_7fff60035181;
              uVar8 = (**(code **)(*plStack_90 + 0x1d8))
                                (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
              if (plStack_90 == (longlong *)0x0) goto LAB_7fff6003517c;
              uStack_7c = (**(code **)(*plStack_90 + 0x228))
                                    (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
              if (plStack_90 == (longlong *)0x0) goto LAB_7fff60035177;
              uVar9 = (**(code **)(*plStack_90 + 0x1d8))
                                (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
              if (plStack_90 == (longlong *)0x0) goto LAB_7fff60035172;
              uStack_84 = (**(code **)(*plStack_90 + 0x228))
                                    (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
              if (plStack_90 == (longlong *)0x0) goto LAB_7fff6003516d;
              uVar14 = (**(code **)(*plStack_90 + 0x228))
                                 (plStack_90,*(undefined8 *)(*plStack_90 + 0x230));
              if (plStack_90 == (longlong *)0x0) goto LAB_7fff60035168;
              uVar10 = (**(code **)(*plStack_90 + 0x1d8))
                                 (plStack_90,*(undefined8 *)(*plStack_90 + 0x1e0));
              lVar15 = *(longlong *)(self + 0x38);
              uVar17 = func_0x7fff5f44ff00(_DAT_7fff62432570);
              uVar11 = CONCAT11(uVar7,uVar10);
              FUN_7fff60362c10(uVar17,uVar6,uVar8,uStack_7c,uVar9,uStack_84,uVar14,uVar11,0);
              if (lVar15 == 0) goto LAB_7fff60035163;
              FUN_7fff5f253100(lVar15,uVar17,_DAT_7fff6242ad58);
              sVar13 = (short)uStack_88;
            }
            iVar18 = iStack_80 + 1;
          }
          FUN_7fff5f47d660();
        }
        FUN_7fff5f47d660();
      }
      FUN_7fff5f47d660();
      FUN_7fff5f40a410();
      FUN_7fff5f40a410();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
  }
  FUN_7fff5f47d660();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

