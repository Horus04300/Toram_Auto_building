
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicStormAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  char cVar3;
  undefined2 uVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined4 uVar11;
  float fVar12;
  float fVar13;
  longlong lStackX_20;
  
  if (DAT_7ffe9cadeeeb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c92d500);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadeeeb = '\x01';
  }
  lStackX_20 = 0;
  lVar6 = FUN_7ffe9a47bac0(0);
  if (lVar6 != 0) {
    lVar6 = FUN_7ffe9a47f670(lVar6,0);
    if (lVar6 != 0) {
      cVar3 = FUN_7ffe9ab94d80(lVar6,0x77,&lStackX_20,_DAT_7ffe9c92d500);
      if (cVar3 != '\0') {
        if (lStackX_20 == 0) goto LAB_7ffe9a6d23cb;
        uVar4 = FUN_7ffe9a5212c0(lStackX_20,0x6a,0);
        *(undefined2 *)(thisObject + 0x154) = uVar4;
      }
      uVar11 = func_0x7ffe99a4d6a0();
      *(undefined4 *)(thisObject + 0x20) = uVar11;
      if (actarAction != (undefined *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
          lVar6 = (**(code **)(*(longlong *)actarAction + 0x298))
                            (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (lVar6 != 0) {
            uVar11 = FUN_7ffe9a4a1cc0(lVar6,0);
            *(undefined4 *)(thisObject + 0x30) = uVar11;
            *(undefined4 *)(thisObject + 0xfc) = 0;
            cVar3 = FUN_7ffe9a4ad740(actarAction,0xe);
            if (cVar3 == '\0') {
              cVar3 = FUN_7ffe9a4ad740(actarAction,0xf);
              if (cVar3 != '\0') {
                *(undefined4 *)(thisObject + 0xfc) = 0xf;
              }
            }
            else {
              *(undefined4 *)(thisObject + 0xfc) = 0xe;
            }
            fVar13 = (float)(byte)thisObject[0x14];
            fVar12 = fVar13 + fVar13 + _DAT_7ffe9c049b1c;
            *(float *)(thisObject + 0x130) = fVar12;
            if (thisObject[0x154] != '\0') {
              *(float *)(thisObject + 0x130) = fVar12 + fVar12;
            }
            iVar1 = *(int *)(thisObject + 0xfc);
            if (iVar1 == 0xe) {
              *(float *)(thisObject + 0x130) = *(float *)(thisObject + 0x130) + _DAT_7ffe9c049cfc;
            }
            fVar13 = fVar13 * _DAT_7ffe9c049c7c;
            *(undefined4 *)(thisObject + 0x134) = 0x1a4;
            fVar12 = (float)(int)fVar13 + _DAT_7ffe9c04a124;
            *(float *)(thisObject + 300) = fVar12;
            if (iVar1 == 0xf) {
              *(float *)(thisObject + 300) = fVar12 + _DAT_7ffe9c049b70;
            }
            if (thisObject[0x154] != '\0') {
              *(float *)(thisObject + 300) = *(float *)(thisObject + 300) * _DAT_7ffe9c049b4c;
            }
            uVar11 = func_0x7ffe99a4d6a0(iVar1,0);
            *(undefined4 *)(thisObject + 300) = uVar11;
            FUN_7ffe9a6d28c0(thisObject,0);
            fVar12 = (float)func_0x7ffe99997964((float)(byte)thisObject[0x14] * _DAT_7ffe9c049b4c);
            *(int *)(thisObject + 0x128) = (int)(fVar12 + _DAT_7ffe9c049b18);
            plVar7 = (longlong *)
                     (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            if (plVar7 != (longlong *)0x0) {
              puVar8 = (undefined *)
                       (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
              if (puVar8 != (undefined *)0x0) {
                puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x134,(undefined *)0x0);
                if (puVar8 != (undefined *)0x0) {
                  iVar1 = *(int *)(thisObject + 0x128);
                  *(float *)(thisObject + 0x130) =
                       *(float *)(thisObject + 0x130) - _DAT_7ffe9c049cf4;
                  iVar5 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
                  *(int *)(thisObject + 0x128) = iVar5 + iVar1;
                }
                *(undefined4 *)(thisObject + 0x28) = *(undefined4 *)(thisObject + 0x128);
                (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
                uVar11 = FUN_7ffe9a4a7fe0(thisObject);
                *(undefined4 *)(thisObject + 0x24) = uVar11;
                uVar9 = (**(code **)(*(longlong *)actarAction + 0x298))
                                  (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
                uVar11 = FUN_7ffe9a4aabb0(uVar9,0);
                *(undefined4 *)(thisObject + 0x78) = uVar11;
                FUN_7ffe9a4aacd0(thisObject,actarAction,0);
                if (*(int *)(thisObject + 0xfc) == 0xe) {
                  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                  uVar10 = 0x952b8;
                }
                else if (*(int *)(thisObject + 0xfc) == 0xf) {
                  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                  uVar10 = 0xad958;
                }
                else {
                  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                  uVar10 = 0x1d0d8;
                }
                FUN_7ffe9a9002e0(uVar9,uVar10,0);
                *(undefined8 *)(thisObject + 0x58) = uVar9;
                il2cpp_write_barrier_0();
                if ((*(longlong *)(thisObject + 0x58) != 0) &&
                   (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
                  FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
                  lVar6 = *(longlong *)(thisObject + 0x58);
                  uVar9 = FUN_7ffe9a6d16f0(thisObject,0);
                  if (lVar6 != 0) {
                    *(undefined8 *)(lVar6 + 0x20) = uVar9;
                    il2cpp_write_barrier_0();
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
LAB_7ffe9a6d23cb:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

