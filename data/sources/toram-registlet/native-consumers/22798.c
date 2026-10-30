
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SwordTempestAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  code *pcVar4;
  byte bVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined *thisObject_00;
  undefined8 uVar8;
  longlong lVar9;
  undefined8 uVar10;
  uint uVar11;
  undefined4 uVar12;
  double dVar13;
  float fVar14;
  
  if (DAT_7ffe9cadebb5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadebb5 = '\x01';
  }
  uVar12 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar12;
  if (actarAction != (undefined *)0x0) {
    if (((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
        (*(longlong *)
          (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) &&
       (lVar6 = (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0)),
       lVar6 != 0)) {
      uVar12 = FUN_7ffe9a4a1cc0(lVar6,0);
      *(undefined4 *)(thisObject + 0x30) = uVar12;
      lVar6 = (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (lVar6 != 0) {
        lVar6 = FUN_7ffe9a4a21b0(lVar6,1);
        uVar12 = 0;
        if (lVar6 != 0) {
          uVar12 = *(undefined4 *)(lVar6 + 0x38);
        }
        *(undefined4 *)(thisObject + 0xfc) = uVar12;
        fVar14 = (float)(((byte)thisObject[0x14] + 0xf) * 10);
        *(float *)(thisObject + 0x128) = fVar14;
        if (*(int *)(thisObject + 0xfc) == 0xb) {
          plVar7 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if ((plVar7 == (longlong *)0x0) ||
             (lVar6 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400)),
             lVar6 == 0)) goto LAB_7ffe9a65d38f;
          *(float *)(thisObject + 0x128) = (float)(*(int *)(lVar6 + 0x14) / 5 + 100) + fVar14;
        }
        *(float *)(thisObject + 0x128) = *(float *)(thisObject + 0x128) / _DAT_7ffe9c049cfc;
        fVar14 = (float)(byte)thisObject[0x14] * _DAT_7ffe9c049ce0 + _DAT_7ffe9c049cf4;
        *(float *)(thisObject + 300) = fVar14;
        if (*(int *)(thisObject + 0xfc) == 10) {
          plVar7 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if ((plVar7 == (longlong *)0x0) ||
             (lVar6 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400)),
             lVar6 == 0)) goto LAB_7ffe9a65d38f;
          *(float *)(thisObject + 300) = (float)(*(int *)(lVar6 + 0x24) / 5) + fVar14;
        }
        fVar14 = *(float *)(thisObject + 300) / _DAT_7ffe9c049cfc;
        bVar5 = thisObject[0x14];
        *(undefined4 *)(thisObject + 0x138) = 0x50;
        *(float *)(thisObject + 300) = fVar14;
        if (DAT_7ffe9cad9c12 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9c12 = '\x01';
        }
        fVar14 = (float)bVar5 * _DAT_7ffe9c04a294 + _DAT_7ffe9c049b70;
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        dVar13 = (double)func_0x7ffe999978b4((double)fVar14);
        *(float *)(thisObject + 0x124) = (float)(int)dVar13;
        uVar12 = func_0x7ffe99a4d6a0();
        bVar5 = thisObject[0x14];
        *(undefined4 *)(thisObject + 0x124) = uVar12;
        if (DAT_7ffe9cad9c12 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9c12 = '\x01';
        }
        fVar14 = (float)bVar5 * _DAT_7ffe9c049b4c + _DAT_7ffe9c049b4c;
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        dVar13 = (double)func_0x7ffe999978b4((double)fVar14);
        *(int *)(thisObject + 0x120) = (int)dVar13 + 1;
        plVar7 = (longlong *)
                 (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if ((plVar7 != (longlong *)0x0) &&
           (thisObject_00 =
                 (undefined *)
                 (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220)),
           thisObject_00 != (undefined *)0x0)) {
          bVar5 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x12d,(undefined *)0x0);
          if (bVar5 != 0) {
            *(int *)(thisObject + 0x120) = *(int *)(thisObject + 0x120) + 1;
          }
          *(uint *)(thisObject + 0x28) = (uint)(byte)thisObject[0x14];
          uVar8 = (**(code **)(*(longlong *)actarAction + 0x298))
                            (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          uVar12 = FUN_7ffe9a4aabb0(uVar8,0);
          *(undefined4 *)(thisObject + 0x78) = uVar12;
          FUN_7ffe9a4aacd0(thisObject,actarAction,0);
          if (*(int *)(thisObject + 0xfc) == 10) {
            uVar8 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            uVar10 = 0x33839;
          }
          else {
            uVar8 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            uVar10 = 0x4bed9;
          }
          FUN_7ffe9a9002e0(uVar8,uVar10,0);
          *(undefined8 *)(thisObject + 0x58) = uVar8;
          il2cpp_write_barrier_0();
          if ((*(longlong *)(thisObject + 0x58) != 0) &&
             (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
            FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
            lVar6 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            FUN_7ffe9a900240(lVar6,0x9eeb98,0x9eeb9b,0);
            if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x50) != 0)) {
              FUN_7ffe9ad10e00(*(longlong *)(lVar6 + 0x50),7,*(undefined4 *)(thisObject + 0x30),
                               _DAT_7ffe9c949490);
              lVar9 = *(longlong *)(lVar6 + 0x50);
              fVar14 = (float)func_0x7ffe99a4d6b0();
              if (lVar9 != 0) {
                FUN_7ffe9ad10e00(lVar9,6,(int)(fVar14 * _DAT_7ffe9c04a778),_DAT_7ffe9c949490);
                lVar9 = FUN_7ffe9a900070(lVar6,0x9eeb99,0x9eeb9b,0);
                if ((lVar9 != 0) && (*(longlong *)(lVar9 + 0x50) != 0)) {
                  FUN_7ffe9ad10e00(*(longlong *)(lVar9 + 0x50),7,*(undefined4 *)(thisObject + 0x30),
                                   _DAT_7ffe9c949490);
                  if (*(longlong *)(lVar9 + 0x50) != 0) {
                    FUN_7ffe9ad10e00(*(longlong *)(lVar9 + 0x50),1,
                                     *(undefined4 *)(thisObject + 0x120),_DAT_7ffe9c949490);
                    lVar9 = FUN_7ffe9a900160(lVar9,0x9eeb9b,0);
                    if ((lVar9 != 0) && (*(longlong *)(lVar9 + 0x50) != 0)) {
                      FUN_7ffe9ad10e00(*(longlong *)(lVar9 + 0x50),7,
                                       *(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
                      if (*(longlong *)(thisObject + 0x58) != 0) {
                        plVar7 = (longlong *)(*(longlong *)(thisObject + 0x58) + 0x20);
                        *plVar7 = lVar6;
                        if (_DAT_7ffe9caee1a8 != 0) {
                          uVar11 = (uint)((ulonglong)plVar7 >> 0xc);
                          puVar1 = (ulonglong *)
                                   ((ulonglong)((uVar11 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
                          do {
                            uVar3 = *puVar1;
                            LOCK();
                            uVar2 = *puVar1;
                            if (uVar3 == uVar2) {
                              *puVar1 = uVar3 | 1L << (uVar11 & 0x3f);
                            }
                            UNLOCK();
                          } while (uVar3 != uVar2);
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
  }
LAB_7ffe9a65d38f:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

