
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RecoveryAction_OnInitialize(undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  undefined8 *puVar1;
  ulonglong *puVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  code *pcVar5;
  bool bVar6;
  char cVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  undefined8 uVar11;
  longlong *plVar12;
  undefined *puVar13;
  longlong lVar14;
  longlong *plVar15;
  longlong *plVar16;
  
  if (DAT_7ffe9cadf8ab == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c929de0);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf8ab = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    *(undefined4 *)(thisObject + 0x20) = 0x42400000;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    plVar15 = (longlong *)0x0;
    *(undefined4 *)(thisObject + 0x20) = 0x42400000;
    plVar16 = plVar15;
    if (bVar6) {
      plVar16 = (longlong *)actarAction;
    }
    if (plVar16 != (longlong *)0x0) {
      uVar11 = (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
      uVar8 = FUN_7ffe9a4aabb0(uVar11,0);
      *(undefined4 *)(thisObject + 0x78) = uVar8;
      uVar11 = (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
      uVar8 = FUN_7ffe9a4a7fe0(thisObject,0,uVar11,0);
      *(undefined4 *)(thisObject + 0x24) = uVar8;
      plVar12 = (longlong *)
                (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
      if ((plVar12 != (longlong *)0x0) &&
         (puVar13 = (undefined *)
                    (**(code **)(*plVar12 + 0x218))(plVar12,*(undefined8 *)(*plVar12 + 0x220)),
         puVar13 != (undefined *)0x0)) {
        puVar13 = GemCartBufferManager_GetGemCartBuffer(puVar13,0x3ee,(undefined *)0x0);
        if (puVar13 != (undefined *)0x0) {
          plVar12 = (longlong *)func_0x7ffe9a7fb2b0(0xe4,0);
          if (plVar12 != (longlong *)0x0) {
            if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7ffe9c929de0 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar12 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c929de0 + 0x130) * 8) != _DAT_7ffe9c929de0)) {
              bVar6 = false;
            }
            else {
              bVar6 = true;
            }
            if (bVar6) {
              plVar15 = plVar12;
            }
          }
          cVar7 = FUN_7ffe9a8fecd0(plVar15,0,0);
          if (cVar7 != '\0') {
            plVar12 = (longlong *)
                      (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
            if (plVar12 == (longlong *)0x0) goto LAB_7ffe9a8365a8;
            lVar14 = (**(code **)(*plVar12 + 0x1b8))(plVar12,*(undefined8 *)(*plVar12 + 0x1c0));
            if (lVar14 == 0) goto LAB_7ffe9a8365a8;
            uVar9 = FUN_7ffe9a7fd580(lVar14,0xe4,1,0);
            if (0 < (int)uVar9) {
              if (plVar15 == (longlong *)0x0) goto LAB_7ffe9a8365a8;
              FUN_7ffe9a8fe290(plVar15,actarAction,uVar9 & 0xff,0);
              lVar14 = plVar15[0x24];
              iVar10 = GemCartBufferBase_GetValue(puVar13,(undefined *)0x2,(undefined *)0x0);
              iVar10 = (iVar10 * (int)lVar14) / 100;
              *(int *)(thisObject + 0x120) = iVar10;
              *(int *)(thisObject + 0x104) = iVar10;
            }
          }
        }
        FUN_7ffe9a4aacd0(thisObject,plVar16,0);
        uVar11 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar11,0x1bd50,0);
        *(undefined8 *)(thisObject + 0x58) = uVar11;
        il2cpp_write_barrier_0();
        lVar14 = *(longlong *)(thisObject + 0x58);
        uVar11 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar11,0x9ebcc2,0);
        if (lVar14 != 0) {
          puVar1 = (undefined8 *)(lVar14 + 0x20);
          *puVar1 = uVar11;
          if (_DAT_7ffe9caee1a8 != 0) {
            uVar9 = (uint)((ulonglong)puVar1 >> 0xc);
            puVar2 = (ulonglong *)((ulonglong)((uVar9 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
            do {
              uVar4 = *puVar2;
              LOCK();
              uVar3 = *puVar2;
              if (uVar4 == uVar3) {
                *puVar2 = uVar4 | 1L << (uVar9 & 0x3f);
              }
              UNLOCK();
            } while (uVar4 != uVar3);
          }
          return;
        }
      }
    }
  }
LAB_7ffe9a8365a8:
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

