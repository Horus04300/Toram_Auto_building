
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ManaCrystalAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  undefined8 *puVar1;
  ulonglong *puVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  longlong lVar5;
  code *pcVar6;
  bool bVar7;
  undefined4 uVar8;
  int iVar9;
  undefined8 uVar10;
  longlong *plVar11;
  undefined *puVar12;
  longlong *plVar13;
  uint uVar14;
  float fVar15;
  
  if (DAT_7ffe9cadf842 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf842 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    *(undefined4 *)(thisObject + 0x20) = 0xbf800000;
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
    *(undefined4 *)(thisObject + 0x20) = 0xbf800000;
    plVar13 = (longlong *)0x0;
    if (bVar7) {
      plVar13 = (longlong *)actarAction;
    }
    if (plVar13 != (longlong *)0x0) {
      uVar10 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
      uVar8 = FUN_7ffe9a4aabb0(uVar10,0);
      fVar15 = _DAT_7ffe9c049d14;
      *(undefined4 *)(thisObject + 0x78) = uVar8;
      plVar11 = (longlong *)
                (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
      if ((plVar11 != (longlong *)0x0) &&
         (puVar12 = (undefined *)
                    (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
         puVar12 != (undefined *)0x0)) {
        puVar12 = GemCartBufferManager_GetGemCartBuffer(puVar12,0x3eb,(undefined *)0x0);
        if (puVar12 != (undefined *)0x0) {
          iVar9 = GemCartBufferBase_GetValue(puVar12,(undefined *)0x2,(undefined *)0x0);
          fVar15 = ((float)iVar9 * fVar15) / _DAT_7ffe9c049cfc;
        }
        uVar10 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
        uVar8 = FUN_7ffe9a4a7fe0(thisObject,fVar15,uVar10,0);
        *(undefined4 *)(thisObject + 0x24) = uVar8;
        FUN_7ffe9a4aacd0(thisObject,plVar13,0);
        uVar8 = func_0x7ffe99a4d6a0();
        *(undefined4 *)(thisObject + 0x120) = uVar8;
        uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar10,0x1c90b,0);
        *(undefined8 *)(thisObject + 0x58) = uVar10;
        il2cpp_write_barrier_0();
        lVar5 = *(longlong *)(thisObject + 0x58);
        uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar10,0x11e67179,0);
        if (lVar5 != 0) {
          puVar1 = (undefined8 *)(lVar5 + 0x20);
          *puVar1 = uVar10;
          if (_DAT_7ffe9caee1a8 != 0) {
            uVar14 = (uint)((ulonglong)puVar1 >> 0xc);
            puVar2 = (ulonglong *)((ulonglong)((uVar14 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
            do {
              uVar4 = *puVar2;
              LOCK();
              uVar3 = *puVar2;
              if (uVar4 == uVar3) {
                *puVar2 = uVar4 | 1L << (uVar14 & 0x3f);
              }
              UNLOCK();
            } while (uVar4 != uVar3);
          }
          return;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar6 = (code *)swi(3);
  (*pcVar6)();
  return;
}

