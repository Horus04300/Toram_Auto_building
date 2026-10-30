
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AccelBladeAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  longlong lVar2;
  code *pcVar3;
  uint uVar4;
  bool bVar5;
  char cVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  longlong lVar10;
  longlong *plVar11;
  undefined *puVar12;
  undefined8 uVar13;
  longlong *plVar14;
  float fVar15;
  float fVar16;
  undefined4 uVar17;
  float fVar18;
  
  if (DAT_7ffe9cadeb4c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadeb4c = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    thisObject[0x148] = 0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar5 = false;
    }
    else {
      bVar5 = true;
    }
    thisObject[0x148] = 0;
    plVar14 = (longlong *)0x0;
    if (bVar5) {
      plVar14 = (longlong *)actarAction;
    }
    if (plVar14 != (longlong *)0x0) {
      lVar10 = (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
      if (lVar10 != 0) {
        uVar7 = FUN_7ffe9a4a1cc0(lVar10,0);
        *(undefined4 *)(thisObject + 0x30) = uVar7;
        iVar8 = FUN_7ffe9a4ae0a0(plVar14,0);
        bVar1 = thisObject[0x14];
        *(int *)(thisObject + 0xfc) = iVar8;
        fVar15 = (float)func_0x7ffe9999782c((float)bVar1 / _DAT_7ffe9c049b74);
        fVar16 = _DAT_7ffe9c049d14;
        iVar9 = (uint)bVar1 + (uint)bVar1 * 4;
        fVar15 = fVar15 * _DAT_7ffe9c049d14;
        uVar4 = ((uint)bVar1 + (uint)bVar1 * 4) * 2;
        *(int *)(thisObject + 0x128) = iVar9 + 100;
        *(uint *)(thisObject + 300) = uVar4;
        uVar7 = 0x33451;
        *(undefined4 *)(thisObject + 0x124) = 0x3f800000;
        fVar15 = fVar15 + fVar16;
        *(float *)(thisObject + 0x20) = fVar15;
        fVar18 = (float)iVar9 + _DAT_7ffe9c049cfc;
        *(float *)(thisObject + 0x120) = fVar18;
        if (iVar8 == 10) {
          *(float *)(thisObject + 0x20) = fVar15 + fVar16;
        }
        else if (iVar8 == 0xb) {
          fVar18 = fVar18 + _DAT_7ffe9c049cf4;
          *(undefined4 *)(thisObject + 0x124) = 0x40400000;
          *(float *)(thisObject + 0x120) = fVar18;
          uVar7 = 0x4baf1;
          *(uint *)(thisObject + 300) = uVar4 / 10;
        }
        *(undefined4 *)(thisObject + 0x14c) = 0x40a00000;
        plVar11 = (longlong *)
                  (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
        if (plVar11 != (longlong *)0x0) {
          puVar12 = (undefined *)
                    (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220));
          if (puVar12 != (undefined *)0x0) {
            puVar12 = GemCartBufferManager_GetGemCartBuffer(puVar12,0x66,(undefined *)0x0);
            if (puVar12 != (undefined *)0x0) {
              fVar16 = *(float *)(thisObject + 0x14c);
              iVar8 = GemCartBufferBase_GetValue(puVar12,(undefined *)0x2,(undefined *)0x0);
              *(float *)(thisObject + 0x14c) = (float)iVar8 + fVar16;
            }
            plVar11 = (longlong *)
                      (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
            if (plVar11 != (longlong *)0x0) {
              lVar10 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
              if (lVar10 != 0) {
                cVar6 = FUN_7ffe9a7c6d00(lVar10,0x23);
                if (cVar6 != '\0') {
                  fVar16 = *(float *)(thisObject + 0x124) + _DAT_7ffe9c049b18;
                  thisObject[0x148] = 1;
                  uVar7 = 0x4baf3;
                  if (*(int *)(thisObject + 0xfc) != 0xb) {
                    uVar7 = 0x33455;
                  }
                  *(float *)(thisObject + 0x124) = fVar16;
                }
                uVar17 = func_0x7ffe99a4d6a0();
                *(undefined4 *)(thisObject + 0x20) = uVar17;
                uVar17 = func_0x7ffe99a4d6a0();
                *(undefined4 *)(thisObject + 0x124) = uVar17;
                uVar13 = (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
                uVar17 = FUN_7ffe9a4aabb0(uVar13,0);
                *(undefined4 *)(thisObject + 0x78) = uVar17;
                FUN_7ffe9a4aacd0(thisObject,plVar14,0);
                uVar13 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                FUN_7ffe9a9002e0(uVar13,uVar7,0);
                *(undefined8 *)(thisObject + 0x58) = uVar13;
                il2cpp_write_barrier_0();
                if ((*(longlong *)(thisObject + 0x58) != 0) &&
                   (lVar10 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar10 != 0)) {
                  lVar2 = *(longlong *)(*(longlong *)(_DAT_7ffe9c949490 + 0x20) + 0xc0);
                  FUN_7ffe9ad1fce0(lVar10,7,*(undefined4 *)(thisObject + 0x30),
                                   CONCAT71((int7)((ulonglong)lVar2 >> 8),2),
                                   *(undefined8 *)(lVar2 + 0x118));
                  return;
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

