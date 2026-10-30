
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ArrowRainAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  double dVar11;
  float fVar12;
  
  if (DAT_7ffe9cadf226 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf226 = '\x01';
  }
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      lVar5 = (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (lVar5 != 0) {
        uVar2 = FUN_7ffe9a4a1cc0(lVar5,0);
        *(undefined4 *)(thisObject + 0x30) = uVar2;
        iVar3 = FUN_7ffe9a4ae0a0(actarAction,0);
        *(int *)(thisObject + 0xfc) = iVar3;
        if (1 < iVar3 - 0xcU) {
          uVar2 = FUN_7ffe9a4ade20(actarAction,0);
          *(undefined4 *)(thisObject + 0xfc) = uVar2;
        }
        uVar2 = func_0x7ffe99a4d6a0(_DAT_7ffe9c049fc4,0);
        *(undefined4 *)(thisObject + 0x20) = uVar2;
        if ((byte)thisObject[0x14] < 2) {
          fVar12 = 0.0;
        }
        else {
          fVar12 = (float)(byte)thisObject[0x14] * _DAT_7ffe9c049b4c;
          if (DAT_7ffe9cad9c12 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c968830);
            DAT_7ffe9cad9c12 = '\x01';
          }
          if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          dVar11 = (double)func_0x7ffe999978b4((double)fVar12);
          fVar12 = (float)(int)dVar11 * _DAT_7ffe9c049ce0 + _DAT_7ffe9c049ce0;
        }
        *(float *)(thisObject + 0x128) = fVar12 + _DAT_7ffe9c049cfc;
        fVar12 = (float)(byte)thisObject[0x14] * _DAT_7ffe9c049b4c;
        if (DAT_7ffe9cad9e25 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9e25 = '\x01';
        }
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        dVar11 = (double)func_0x7ffe99997768((double)fVar12);
        *(int *)(thisObject + 300) = ((int)dVar11 + 5) * 10;
        fVar12 = (float)(byte)thisObject[0x14] / _DAT_7ffe9c049b74;
        if (DAT_7ffe9cad9e25 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9e25 = '\x01';
        }
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        dVar11 = (double)func_0x7ffe99997768((double)fVar12);
        *(float *)(thisObject + 0x124) = (float)(int)dVar11 * _DAT_7ffe9c049b4c + _DAT_7ffe9c049b18;
        uVar6 = (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        uVar2 = FUN_7ffe9a4aabb0(uVar6,0);
        *(undefined4 *)(thisObject + 0x78) = uVar2;
        *(uint *)(thisObject + 0x120) = (byte)thisObject[0x14] / 3 + 1;
        plVar7 = (longlong *)
                 (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if (plVar7 != (longlong *)0x0) {
          puVar8 = (undefined *)
                   (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
          if (puVar8 != (undefined *)0x0) {
            puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0xcb,(undefined *)0x0);
            if (puVar8 != (undefined *)0x0) {
              iVar3 = *(int *)(thisObject + 0x120);
              iVar4 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
              *(int *)(thisObject + 0x120) = iVar4 + iVar3;
            }
            *(undefined4 *)(thisObject + 0x28) = *(undefined4 *)(thisObject + 0x120);
            FUN_7ffe9a4aacd0(thisObject,actarAction,0);
            uVar10 = 0x1dc93;
            uVar6 = 0x9ed040;
            if (*(int *)(thisObject + 0xfc) == 0xc) {
              uVar10 = 0x64579;
              uVar6 = 0x1cffd40;
              fVar12 = *(float *)(thisObject + 0x124) + _DAT_7ffe9c049b70;
              *(int *)(thisObject + 0x120) = *(int *)(thisObject + 0x120) * 2;
              *(float *)(thisObject + 0x124) = fVar12;
            }
            else if (*(int *)(thisObject + 0xfc) == 0xd) {
              uVar10 = 0x7cc19;
              *(float *)(thisObject + 0x128) = *(float *)(thisObject + 0x128) + _DAT_7ffe9c049f0c;
            }
            uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            FUN_7ffe9a9002e0(uVar9,uVar10,0);
            *(undefined8 *)(thisObject + 0x58) = uVar9;
            il2cpp_write_barrier_0();
            if ((*(longlong *)(thisObject + 0x58) != 0) &&
               (lVar5 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar5 != 0)) {
              FUN_7ffe9ad10e00(lVar5,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
              lVar5 = *(longlong *)(thisObject + 0x58);
              uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
              FUN_7ffe9a9002e0(uVar10,uVar6,0);
              if (lVar5 != 0) {
                *(undefined8 *)(lVar5 + 0x20) = uVar10;
                il2cpp_write_barrier_0();
                if (((*(longlong *)(thisObject + 0x58) != 0) &&
                    (lVar5 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar5 != 0)) &&
                   (lVar5 = *(longlong *)(lVar5 + 0x50), lVar5 != 0)) {
                  FUN_7ffe9ad10e00(lVar5,1,*(undefined4 *)(thisObject + 0x120),_DAT_7ffe9c949490);
                  if (((*(longlong *)(thisObject + 0x58) != 0) &&
                      (lVar5 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar5 != 0))
                     && (lVar5 = *(longlong *)(lVar5 + 0x50), lVar5 != 0)) {
                    FUN_7ffe9ad10e00(lVar5,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
                    uVar2 = func_0x7ffe99a4d6a0(*(undefined4 *)(thisObject + 0x124),0);
                    *(undefined4 *)(thisObject + 0x124) = uVar2;
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
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

