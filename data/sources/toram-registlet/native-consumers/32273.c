
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighnessHealAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  code *pcVar4;
  bool bVar5;
  float fVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  longlong *plVar11;
  undefined *puVar12;
  undefined8 uVar13;
  longlong lVar14;
  longlong *plVar15;
  longlong lVar16;
  longlong *plVar17;
  uint uVar18;
  float fVar19;
  
  if (DAT_7ffe9cadf7e7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf7e7 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    uVar7 = FUN_7ffe9a4ae0a0(0,0);
    *(undefined4 *)(thisObject + 0xfc) = uVar7;
    *(undefined4 *)(thisObject + 0x20) = 0xbf800000;
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
    plVar17 = (longlong *)0x0;
    if (bVar5) {
      plVar17 = (longlong *)actarAction;
    }
    uVar7 = FUN_7ffe9a4ae0a0(plVar17,0);
    *(undefined4 *)(thisObject + 0xfc) = uVar7;
    *(undefined4 *)(thisObject + 0x20) = 0xbf800000;
    if (((plVar17 != (longlong *)0x0) &&
        (plVar11 = (longlong *)
                   (**(code **)(*plVar17 + 0x298))(plVar17,*(undefined8 *)(*plVar17 + 0x2a0)),
        plVar11 != (longlong *)0x0)) &&
       (puVar12 = (undefined *)
                  (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
       puVar12 != (undefined *)0x0)) {
      puVar12 = GemCartBufferManager_GetGemCartBuffer(puVar12,0x401,(undefined *)0x0);
      if (puVar12 != (undefined *)0x0) {
        GemCartBufferBase_GetValue(puVar12,(undefined *)0x2,(undefined *)0x0);
      }
      uVar7 = func_0x7ffe99a4d6a0();
      *(undefined4 *)(thisObject + 0x120) = uVar7;
      uVar13 = (**(code **)(*plVar17 + 0x298))(plVar17,*(undefined8 *)(*plVar17 + 0x2a0));
      uVar7 = FUN_7ffe9a4aabb0(uVar13,0);
      *(undefined4 *)(thisObject + 0x78) = uVar7;
      (**(code **)(*plVar17 + 0x298))(plVar17,*(undefined8 *)(*plVar17 + 0x2a0));
      uVar7 = FUN_7ffe9a4a7fe0(thisObject);
      *(undefined4 *)(thisObject + 0x24) = uVar7;
      FUN_7ffe9a4aacd0(thisObject,plVar17,0);
      lVar14 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
      FUN_7ffe9a9002e0(lVar14,0x1c90d,0);
      plVar11 = (longlong *)(thisObject + 0x58);
      *plVar11 = lVar14;
      il2cpp_write_barrier_0();
      lVar14 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
      FUN_7ffe9a900240(lVar14,0x9eef80,0x9eef82,0);
      fVar6 = _DAT_7ffe9c049b18;
      if (lVar14 != 0) {
        lVar16 = *(longlong *)(lVar14 + 0x50);
        fVar19 = (float)func_0x7ffe99a4d6a0();
        if (lVar16 != 0) {
          FUN_7ffe9ad10e00(lVar16,6,(int)(fVar19 * _DAT_7ffe9c049f04),_DAT_7ffe9c949490);
          FUN_7ffe9a900160(lVar14,0x9eef82,0);
          plVar15 = (longlong *)
                    (**(code **)(*plVar17 + 0x298))(plVar17,*(undefined8 *)(*plVar17 + 0x2a0));
          if ((plVar15 != (longlong *)0x0) &&
             (lVar16 = (**(code **)(*plVar15 + 0x198))(plVar15,*(undefined8 *)(*plVar15 + 0x1a0)),
             lVar16 != 0)) {
            iVar8 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar16);
            iVar8 = (int)(((byte)thisObject[0x14] + 5) * iVar8 * 2) / 100 +
                    (uint)(byte)thisObject[0x14] * 500;
            if (puVar12 != (undefined *)0x0) {
              iVar9 = iVar8 / 2;
              plVar17 = (longlong *)
                        (**(code **)(*plVar17 + 0x298))(plVar17,*(undefined8 *)(*plVar17 + 0x2a0));
              if ((plVar17 == (longlong *)0x0) ||
                 (puVar12 = (undefined *)
                            (**(code **)(*plVar17 + 0x218))
                                      (plVar17,*(undefined8 *)(*plVar17 + 0x220)),
                 puVar12 == (undefined *)0x0)) goto LAB_7ffe9a8212de;
              iVar10 = GemCartBufferManager_GetBufferLevel(puVar12,0x47,(undefined *)0x0);
              if (0 < iVar10) {
                iVar9 = (int)((fVar6 - (float)(iVar10 * 10) * _DAT_7ffe9c049b34) * (float)iVar9);
              }
              iVar8 = iVar8 - iVar9;
            }
            if ((*plVar11 != 0) && (lVar16 = *(longlong *)(*plVar11 + 0x50), lVar16 != 0)) {
              FUN_7ffe9ad10e00(lVar16,0xb,iVar8,_DAT_7ffe9c949490);
              if (*plVar11 != 0) {
                plVar17 = (longlong *)(*plVar11 + 0x20);
                *plVar17 = lVar14;
                if (_DAT_7ffe9caee1a8 != 0) {
                  uVar18 = (uint)((ulonglong)plVar17 >> 0xc);
                  puVar1 = (ulonglong *)((ulonglong)((uVar18 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0)
                  ;
                  do {
                    uVar3 = *puVar1;
                    LOCK();
                    uVar2 = *puVar1;
                    if (uVar3 == uVar2) {
                      *puVar1 = uVar3 | 1L << (uVar18 & 0x3f);
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
LAB_7ffe9a8212de:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

