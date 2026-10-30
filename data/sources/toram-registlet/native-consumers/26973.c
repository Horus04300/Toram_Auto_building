
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void DecoyShooterPursuitAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  code *pcVar2;
  bool bVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined *puVar8;
  longlong *plVar9;
  undefined8 *puVar10;
  longlong *plVar11;
  ushort uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined4 uVar16;
  float fVar17;
  double dVar18;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadf24d == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf24d = '\x01';
  }
  uStackX_8 = 0;
  if (actarAction == (undefined *)0x0) {
    uVar16 = func_0x7ffe99a4d6a0();
    *(undefined4 *)(thisObject + 0x20) = uVar16;
  }
  else {
    bVar1 = *(byte *)(_DAT_7ffe9c922720 + 0x130);
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < bVar1) ||
       (*(longlong *)(*(longlong *)(*(longlong *)actarAction + 200) + -8 + (ulonglong)bVar1 * 8) !=
        _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar11 = (longlong *)0x0;
    if (bVar3) {
      plVar11 = (longlong *)actarAction;
    }
    uVar16 = func_0x7ffe99a4d6a0((ulonglong)bVar1,0);
    *(undefined4 *)(thisObject + 0x20) = uVar16;
    if (((plVar11 != (longlong *)0x0) &&
        (plVar5 = (longlong *)
                  (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
        plVar5 != (longlong *)0x0)) &&
       (lVar6 = (**(code **)(*plVar5 + 0x1f8))(plVar5,*(undefined8 *)(*plVar5 + 0x200)), lVar6 != 0)
       ) {
      uVar7 = FUN_7ffe99c090e0(lVar6,0);
      uVar16 = FUN_7ffe9a4adf80(uVar7,0);
      *(undefined4 *)(thisObject + 0x130) = uVar16;
      iVar13 = (uint)(byte)thisObject[0x14] * 8 + 0x14;
      *(int *)(thisObject + 300) = iVar13;
      plVar5 = (longlong *)
               (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      if ((plVar5 != (longlong *)0x0) &&
         (puVar8 = (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5), puVar8 != (undefined *)0x0))
      {
        fVar17 = GemCartBufferManager_GetNormalAttackRate(puVar8,(undefined *)0x0);
        *(int *)(thisObject + 300) = (int)fVar17 + iVar13;
        uVar7 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
        uVar16 = FUN_7ffe9a4a7fe0(thisObject,0,uVar7,0);
        *(undefined4 *)(thisObject + 0x24) = uVar16;
        plVar5 = (longlong *)
                 (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
        if (plVar5 != (longlong *)0x0) {
          plVar5 = (longlong *)
                   (**(code **)(*plVar5 + 0x198))(plVar5,*(undefined8 *)(*plVar5 + 0x1a0));
          plVar9 = (longlong *)
                   (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
          if (((plVar9 != (longlong *)0x0) &&
              (lVar6 = (**(code **)(*plVar9 + 0x198))(plVar9,*(undefined8 *)(*plVar9 + 0x1a0)),
              lVar6 != 0)) &&
             (uVar16 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c940d40,lVar6), plVar5 != (longlong *)0x0)) {
            lVar6 = *plVar5;
            uVar12 = 0;
            if (*(ushort *)(lVar6 + 0x12e) != 0) {
              do {
                if (*(longlong *)(*(longlong *)(lVar6 + 0xb0) + (ulonglong)uVar12 * 0x10) ==
                    _DAT_7ffe9c940d40) {
                  puVar10 = (undefined8 *)
                            ((longlong)
                             (*(int *)(*(longlong *)(lVar6 + 0xb0) + 8 + (ulonglong)uVar12 * 0x10) +
                             0x2d) * 0x10 + 0x138 + lVar6);
                  goto LAB_7ffe9a753269;
                }
                uVar12 = uVar12 + 1;
              } while (uVar12 < *(ushort *)(lVar6 + 0x12e));
            }
            puVar10 = (undefined8 *)FUN_7ffe998ce540(plVar5,_DAT_7ffe9c940d40,0x2d);
LAB_7ffe9a753269:
            uVar16 = (*(code *)*puVar10)(plVar5,uVar16,puVar10[1]);
            bVar1 = thisObject[0x14];
            iVar14 = 1;
            *(undefined4 *)(thisObject + 0x144) = uVar16;
            fVar17 = _DAT_7ffe9c049b4c;
            iVar13 = 10;
            iVar15 = 0;
            if (bVar1 != 0) {
              do {
                if (DAT_7ffe9cad9c12 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c968830);
                  DAT_7ffe9cad9c12 = '\x01';
                }
                if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                dVar18 = (double)func_0x7ffe999978b4((double)((float)iVar14 * fVar17));
                iVar14 = iVar14 + 1;
                iVar13 = iVar13 + (int)dVar18 * 2;
              } while (iVar14 <= (int)(uint)bVar1);
            }
            plVar5 = (longlong *)
                     (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
            if ((plVar5 != (longlong *)0x0) &&
               (puVar8 = (undefined *)
                         (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
               puVar8 != (undefined *)0x0)) {
              puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x192,(undefined *)0x0);
              if (puVar8 != (undefined *)0x0) {
                iVar14 = *(int *)(thisObject + 300);
                iVar4 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x4,(undefined *)0x0);
                *(int *)(thisObject + 300) = iVar4 + iVar14;
                iVar13 = iVar13 / 2;
              }
              FUN_7ffe9a4aacd0(thisObject,plVar11,0);
              iVar14 = iVar15;
              if (thisObject[0x14] != '\0') {
                fVar17 = _DAT_7ffe9c049b30;
                if (_DAT_7ffe9c049b30 <= *(float *)(thisObject + 0x144)) {
                  fVar17 = *(float *)(thisObject + 0x144);
                }
                iVar14 = (int)((float)iVar13 / fVar17);
              }
              iVar4 = FUN_7ffe9a4adfc0(plVar11,&uStackX_8,0);
              *(int *)(thisObject + 0xfc) = iVar4;
              if (iVar4 == 0xc) {
                iVar15 = 0xbf1f3f0;
              }
              else if (iVar4 == 0xd) {
                iVar15 = 0xbf37a90;
              }
              *(int *)(thisObject + 0x140) = iVar15;
              uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
              FUN_7ffe9a9002e0(uVar7,iVar15,0);
              *(undefined8 *)(thisObject + 0x58) = uVar7;
              il2cpp_write_barrier_0();
              if ((*(longlong *)(thisObject + 0x58) != 0) &&
                 (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
                FUN_7ffe9ad10e00(lVar6,1,iVar14,_DAT_7ffe9c949490);
                if ((*(longlong *)(thisObject + 0x58) != 0) &&
                   (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
                  FUN_7ffe9ad10e00(lVar6,0x1c,iVar13 * 10,_DAT_7ffe9c949490);
                  if ((*(longlong *)(thisObject + 0x58) != 0) &&
                     (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
                    FUN_7ffe9ad10e00(lVar6,0xd,
                                     (int)(*(float *)(thisObject + 0x144) * _DAT_7ffe9c049cfc),
                                     _DAT_7ffe9c949490);
                    if ((*(longlong *)(thisObject + 0x58) != 0) &&
                       (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0))
                    {
                      FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490)
                      ;
                      *(int *)(thisObject + 0x28) = iVar13;
                      plVar11 = (longlong *)
                                (**(code **)(*plVar11 + 0x298))
                                          (plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
                      if ((plVar11 != (longlong *)0x0) &&
                         (lVar6 = (**(code **)(*plVar11 + 0x198))
                                            (plVar11,*(undefined8 *)(*plVar11 + 0x1a0)), lVar6 != 0)
                         ) {
                        iVar13 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c940d40,lVar6);
                        if (1099 < iVar13) {
                          *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 1;
                        }
                        *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 2;
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
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

