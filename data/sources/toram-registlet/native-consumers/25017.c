
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicStormAction_InitializeEnchantedSpell
               (undefined *thisObject,undefined *actarAction,byte isPlayer,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  code *pcVar4;
  bool bVar5;
  char cVar6;
  undefined4 uVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined *puVar10;
  undefined8 uVar11;
  uint uVar12;
  float fVar13;
  float fVar14;
  undefined2 auStackX_18 [4];
  
  if (DAT_7ffe9cadeefe == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c8fee40);
    DAT_7ffe9cadeefe = '\x01';
  }
  plVar9 = (longlong *)0x0;
  auStackX_18[0] = 0;
  func_0x7ffe9af709e0(auStackX_18,0,0,_DAT_7ffe9c8fee40);
  *(undefined2 *)(thisObject + 0x154) = auStackX_18[0];
  if (isPlayer != 0) {
    if (actarAction != (undefined *)0x0) {
      if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
        bVar5 = false;
      }
      else {
        bVar5 = true;
      }
      plVar9 = (longlong *)0x0;
      if (bVar5) {
        plVar9 = (longlong *)actarAction;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar6 = FUN_7ffe9bda2160(plVar9,0,0);
    if (cVar6 != '\0') {
      if ((plVar9 == (longlong *)0x0) ||
         (lVar8 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
         lVar8 == 0)) goto LAB_7ffe9a6d1dea;
      uVar7 = FUN_7ffe9a4a1fb0(lVar8,0);
      *(undefined4 *)(thisObject + 0x30) = uVar7;
    }
    *(undefined4 *)(thisObject + 0x24) = 0xbf800000;
    func_0x7ffe9a4b1cd0(thisObject,0x400,0);
    *(undefined4 *)(thisObject + 0xfc) = 0;
    cVar6 = FUN_7ffe9a4ad740(plVar9,0xf);
    if (cVar6 != '\0') {
      *(undefined4 *)(thisObject + 0xfc) = 0xf;
    }
    *(undefined4 *)(thisObject + 0x134) = 0x1a4;
    fVar13 = (float)(byte)thisObject[0x14];
    fVar14 = fVar13 * _DAT_7ffe9c049c7c;
    *(float *)(thisObject + 0x130) = fVar13 + fVar13 + _DAT_7ffe9c049b1c;
    fVar13 = (float)(int)fVar14 + _DAT_7ffe9c04a124;
    *(float *)(thisObject + 300) = fVar13;
    if (*(int *)(thisObject + 0xfc) == 0xf) {
      *(float *)(thisObject + 300) = fVar13 + _DAT_7ffe9c049b70;
    }
    uVar7 = func_0x7ffe99a4d6a0();
    *(undefined4 *)(thisObject + 300) = uVar7;
    FUN_7ffe9a6d28c0(thisObject,0);
    if (((plVar9 == (longlong *)0x0) ||
        (plVar9 = (longlong *)
                  (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
        plVar9 == (longlong *)0x0)) ||
       (puVar10 = (undefined *)
                  (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220)),
       puVar10 == (undefined *)0x0)) {
LAB_7ffe9a6d1dea:
      FUN_7ffe9996d7a0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    puVar10 = GemCartBufferManager_GetGemCartBuffer(puVar10,0x134,(undefined *)0x0);
    if (puVar10 != (undefined *)0x0) {
      *(float *)(thisObject + 0x130) = *(float *)(thisObject + 0x130) - _DAT_7ffe9c049cf4;
    }
  }
  uVar11 = FUN_7ffe9a6d16f0(thisObject,0);
  *(undefined8 *)(thisObject + 0x58) = uVar11;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar12 = (uint)((ulonglong)(thisObject + 0x58) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar12 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
    do {
      uVar3 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar3 == uVar2) {
        *puVar1 = uVar3 | 1L << (uVar12 & 0x3f);
      }
      UNLOCK();
    } while (uVar3 != uVar2);
  }
  return;
}

