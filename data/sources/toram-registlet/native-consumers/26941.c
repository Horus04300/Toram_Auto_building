
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void DecoyShooterAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  code *pcVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined8 uVar9;
  longlong *plVar10;
  longlong lVar11;
  undefined8 *puVar12;
  longlong *plVar13;
  ushort uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  float fVar18;
  double dVar19;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadf242 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf242 = '\x01';
  }
  plVar13 = (longlong *)0x0;
  iVar17 = 0;
  uStackX_8 = 0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar13 = (longlong *)0x0;
    if (bVar3) {
      plVar13 = (longlong *)actarAction;
    }
  }
  uVar4 = FUN_7ffe9a4adfc0(plVar13,&uStackX_8,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar4;
  uVar4 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar4;
  uVar4 = FUN_7ffe9a4adf80(uStackX_8,0);
  *(undefined4 *)(thisObject + 0x130) = uVar4;
  iVar15 = (uint)(byte)thisObject[0x14] * 8 + 0x14;
  *(int *)(thisObject + 300) = iVar15;
  if (((plVar13 != (longlong *)0x0) &&
      (plVar7 = (longlong *)
                (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
      plVar7 != (longlong *)0x0)) &&
     (puVar8 = (undefined *)(**(code **)(*plVar7 + 0x218))(plVar7), puVar8 != (undefined *)0x0)) {
    fVar18 = GemCartBufferManager_GetNormalAttackRate(puVar8,(undefined *)0x0);
    *(int *)(thisObject + 300) = (int)fVar18 + iVar15;
    uVar9 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
    uVar4 = FUN_7ffe9a4a7fe0(thisObject,_DAT_7ffe9c049b18,uVar9,0);
    *(undefined4 *)(thisObject + 0x24) = uVar4;
    plVar7 = (longlong *)(**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
    if (plVar7 != (longlong *)0x0) {
      plVar7 = (longlong *)(**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0));
      plVar10 = (longlong *)
                (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
      if (((plVar10 != (longlong *)0x0) &&
          (lVar11 = (**(code **)(*plVar10 + 0x198))(plVar10,*(undefined8 *)(*plVar10 + 0x1a0)),
          lVar11 != 0)) &&
         (uVar4 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c940d40,lVar11), plVar7 != (longlong *)0x0)) {
        lVar11 = *plVar7;
        uVar14 = 0;
        if (*(ushort *)(lVar11 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar11 + 0xb0) + (ulonglong)uVar14 * 0x10) ==
                _DAT_7ffe9c940d40) {
              puVar12 = (undefined8 *)
                        ((longlong)
                         (*(int *)(*(longlong *)(lVar11 + 0xb0) + 8 + (ulonglong)uVar14 * 0x10) +
                         0x2d) * 0x10 + 0x138 + lVar11);
              goto LAB_7ffe9a741829;
            }
            uVar14 = uVar14 + 1;
          } while (uVar14 < *(ushort *)(lVar11 + 0x12e));
        }
        puVar12 = (undefined8 *)FUN_7ffe998ce540(plVar7,_DAT_7ffe9c940d40,0x2d);
LAB_7ffe9a741829:
        uVar4 = (*(code *)*puVar12)(plVar7,uVar4,puVar12[1]);
        bVar1 = thisObject[0x14];
        iVar16 = 1;
        *(undefined4 *)(thisObject + 0x148) = uVar4;
        fVar18 = _DAT_7ffe9c049b4c;
        iVar15 = 10;
        if (bVar1 != 0) {
          do {
            if (DAT_7ffe9cad9c12 == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c968830);
              DAT_7ffe9cad9c12 = '\x01';
            }
            if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            dVar19 = (double)func_0x7ffe999978b4((double)((float)iVar16 * fVar18));
            iVar16 = iVar16 + 1;
            iVar15 = iVar15 + (int)dVar19 * 2;
          } while (iVar16 <= (int)(uint)bVar1);
        }
        plVar7 = (longlong *)
                 (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
        if ((plVar7 != (longlong *)0x0) &&
           (puVar8 = (undefined *)
                     (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220)),
           puVar8 != (undefined *)0x0)) {
          puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x192,(undefined *)0x0);
          if (puVar8 != (undefined *)0x0) {
            iVar16 = *(int *)(thisObject + 300);
            iVar5 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x4,(undefined *)0x0);
            *(int *)(thisObject + 300) = iVar5 + iVar16;
            iVar15 = iVar15 / 2;
          }
          FUN_7ffe9a4aacd0(thisObject,plVar13,0);
          if (thisObject[0x14] != '\0') {
            fVar18 = _DAT_7ffe9c049b30;
            if (_DAT_7ffe9c049b30 <= *(float *)(thisObject + 0x148)) {
              fVar18 = *(float *)(thisObject + 0x148);
            }
            iVar17 = (int)((float)iVar15 / fVar18);
          }
          uVar4 = *(undefined4 *)(thisObject + 0xfc);
          uVar6 = FUN_7ffe9a4ade20(plVar13,0);
          uVar4 = func_0x7ffe9a741130(thisObject,uVar4,uVar6,0);
          *(undefined4 *)(thisObject + 0x144) = uVar4;
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar9,0x1d0d9,0);
          *(undefined8 *)(thisObject + 0x58) = uVar9;
          il2cpp_write_barrier_0();
          lVar11 = *(longlong *)(thisObject + 0x58);
          uVar4 = *(undefined4 *)(thisObject + 0x144);
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar9,uVar4,0);
          if (lVar11 != 0) {
            *(undefined8 *)(lVar11 + 0x20) = uVar9;
            il2cpp_write_barrier_0();
            if (((*(longlong *)(thisObject + 0x58) != 0) &&
                (lVar11 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar11 != 0)) &&
               (lVar11 = *(longlong *)(lVar11 + 0x50), lVar11 != 0)) {
              FUN_7ffe9ad10e00(lVar11,1,iVar17,_DAT_7ffe9c949490);
              if (((*(longlong *)(thisObject + 0x58) != 0) &&
                  (lVar11 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar11 != 0)) &&
                 (lVar11 = *(longlong *)(lVar11 + 0x50), lVar11 != 0)) {
                FUN_7ffe9ad10e00(lVar11,0x1c,iVar15 * 10,_DAT_7ffe9c949490);
                if (((*(longlong *)(thisObject + 0x58) != 0) &&
                    (lVar11 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar11 != 0))
                   && (lVar11 = *(longlong *)(lVar11 + 0x50), lVar11 != 0)) {
                  FUN_7ffe9ad10e00(lVar11,0xd,
                                   (int)(*(float *)(thisObject + 0x148) * _DAT_7ffe9c049cfc),
                                   _DAT_7ffe9c949490);
                  if (((*(longlong *)(thisObject + 0x58) != 0) &&
                      (lVar11 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar11 != 0)
                      ) && (lVar11 = *(longlong *)(lVar11 + 0x50), lVar11 != 0)) {
                    FUN_7ffe9ad10e00(lVar11,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
                    *(int *)(thisObject + 0x28) = iVar15;
                    plVar13 = (longlong *)
                              (**(code **)(*plVar13 + 0x298))
                                        (plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
                    if ((plVar13 != (longlong *)0x0) &&
                       (lVar11 = (**(code **)(*plVar13 + 0x198))
                                           (plVar13,*(undefined8 *)(*plVar13 + 0x1a0)), lVar11 != 0)
                       ) {
                      iVar17 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c940d40,lVar11);
                      if (1099 < iVar17) {
                        *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 1;
                      }
                      return;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

