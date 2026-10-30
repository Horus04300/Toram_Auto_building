
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void OneWheelAction_OnInitialize(undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  ulonglong *puVar1;
  float fVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  longlong lVar5;
  code *pcVar6;
  bool bVar7;
  int iVar8;
  undefined4 uVar9;
  longlong *plVar10;
  undefined *puVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  longlong *plVar14;
  uint uVar15;
  
  if (DAT_7ffe9cadf263 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf263 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar14 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar7 = false;
    }
    else {
      bVar7 = true;
    }
    plVar14 = (longlong *)0x0;
    if (bVar7) {
      plVar14 = (longlong *)actarAction;
    }
  }
  iVar8 = FUN_7ffe9a4ae0a0(plVar14,0);
  *(int *)(thisObject + 0xfc) = iVar8;
  if (1 < iVar8 - 0xcU) {
    uVar9 = FUN_7ffe9a4ade20(plVar14,0);
    *(undefined4 *)(thisObject + 0xfc) = uVar9;
  }
  uVar9 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar9;
  *(float *)(thisObject + 0x120) = (float)(((byte)thisObject[0x14] + 5) * 5);
  if (((plVar14 != (longlong *)0x0) &&
      (plVar10 = (longlong *)
                 (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0)),
      plVar10 != (longlong *)0x0)) &&
     (puVar11 = (undefined *)
                (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220)),
     puVar11 != (undefined *)0x0)) {
    puVar11 = GemCartBufferManager_GetGemCartBuffer(puVar11,0x68,(undefined *)0x0);
    if (puVar11 != (undefined *)0x0) {
      fVar2 = *(float *)(thisObject + 0x120);
      iVar8 = GemCartBufferBase_GetValue(puVar11,(undefined *)0x4,(undefined *)0x0);
      *(float *)(thisObject + 0x120) = (float)iVar8 + fVar2;
    }
    *(uint *)(thisObject + 0x124) = (uint)(byte)thisObject[0x14] * 4 + 0x1e;
    lVar5 = *(longlong *)(thisObject + 0x128);
    if (lVar5 != 0) {
      if (*(int *)(lVar5 + 0x18) != 0) {
        *(undefined4 *)(lVar5 + 0x20) = 0;
        lVar5 = *(longlong *)(thisObject + 0x128);
        if (lVar5 == 0) goto LAB_7ffe9a755f72;
        if (1 < *(uint *)(lVar5 + 0x18)) {
          *(uint *)(lVar5 + 0x24) = (uint)(byte)thisObject[0x14] << 2;
          lVar5 = *(longlong *)(thisObject + 0x128);
          if (lVar5 == 0) goto LAB_7ffe9a755f72;
          if (2 < *(uint *)(lVar5 + 0x18)) {
            *(uint *)(lVar5 + 0x28) = (uint)(byte)thisObject[0x14] << 3;
            uVar12 = (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
            uVar9 = FUN_7ffe9a4aabb0(uVar12,0);
            *(undefined4 *)(thisObject + 0x78) = uVar9;
            FUN_7ffe9a4aacd0(thisObject,plVar14,0);
            iVar8 = *(int *)(thisObject + 0xfc);
            uVar12 = 0x64960;
            if (iVar8 == 0xc) {
              *(float *)(thisObject + 0x120) = *(float *)(thisObject + 0x120) + _DAT_7ffe9c049f04;
            }
            else {
              if (iVar8 == 0xd) {
                lVar5 = *(longlong *)(thisObject + 0x128);
                uVar12 = 0x7d000;
                if (lVar5 == 0) goto LAB_7ffe9a755f72;
                if (1 < *(uint *)(lVar5 + 0x18)) {
                  *(int *)(lVar5 + 0x24) = *(int *)(lVar5 + 0x24) + 10;
                  lVar5 = *(longlong *)(thisObject + 0x128);
                  if (lVar5 == 0) goto LAB_7ffe9a755f72;
                  if (2 < *(uint *)(lVar5 + 0x18)) {
                    *(int *)(lVar5 + 0x28) = *(int *)(lVar5 + 0x28) + 0x14;
                    goto il2cpp_write_barrier_0;
                  }
                }
                goto LAB_7ffe9a755f78;
              }
              if (iVar8 == 0x13) {
                uVar12 = 0x1dc94;
              }
            }
il2cpp_write_barrier_0:
            uVar13 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            FUN_7ffe9a9002e0(uVar13,uVar12,0);
            *(undefined8 *)(thisObject + 0x58) = uVar13;
            if (_DAT_7ffe9caee1a8 != 0) {
              uVar15 = (uint)((ulonglong)(thisObject + 0x58) >> 0xc);
              puVar1 = (ulonglong *)((ulonglong)((uVar15 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
              do {
                uVar4 = *puVar1;
                LOCK();
                uVar3 = *puVar1;
                if (uVar4 == uVar3) {
                  *puVar1 = uVar4 | 1L << (uVar15 & 0x3f);
                }
                UNLOCK();
              } while (uVar4 != uVar3);
            }
            return;
          }
        }
      }
LAB_7ffe9a755f78:
      FUN_7ffe9996d790();
      pcVar6 = (code *)swi(3);
      (*pcVar6)();
      return;
    }
  }
LAB_7ffe9a755f72:
  FUN_7ffe9996d7a0();
  pcVar6 = (code *)swi(3);
  (*pcVar6)();
  return;
}

