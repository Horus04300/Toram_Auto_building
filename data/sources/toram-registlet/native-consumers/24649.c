
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicArrowAction_InitializeEnchantedSpell
               (undefined *thisObject,undefined *actarAction,byte isPlayer,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  byte bVar3;
  int iVar4;
  ulonglong uVar5;
  code *pcVar6;
  bool bVar7;
  char cVar8;
  undefined4 uVar9;
  int iVar10;
  longlong lVar11;
  longlong *plVar12;
  undefined *puVar13;
  undefined8 uVar14;
  uint uVar15;
  float fVar16;
  undefined2 auStackX_18 [4];
  
  if (DAT_7ffe9cadee5c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c8fee40);
    DAT_7ffe9cadee5c = '\x01';
  }
  plVar12 = (longlong *)0x0;
  auStackX_18[0] = 0;
  func_0x7ffe9af709e0(auStackX_18,0,0,_DAT_7ffe9c8fee40);
  *(undefined2 *)(thisObject + 0x138) = auStackX_18[0];
  if (isPlayer != 0) {
    *(undefined4 *)(thisObject + 0x28) = *(undefined4 *)(thisObject + 0x120);
    if (actarAction != (undefined *)0x0) {
      if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
        bVar7 = false;
      }
      else {
        bVar7 = true;
      }
      plVar12 = (longlong *)0x0;
      if (bVar7) {
        plVar12 = (longlong *)actarAction;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar8 = FUN_7ffe9bda2160(plVar12,0,0);
    if (cVar8 != '\0') {
      if ((plVar12 == (longlong *)0x0) ||
         (lVar11 = (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0)),
         lVar11 == 0)) goto LAB_7ffe9a6b5b95;
      uVar9 = FUN_7ffe9a4a1fb0(lVar11,0);
      *(undefined4 *)(thisObject + 0x30) = uVar9;
    }
    *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 0x400;
    *(undefined4 *)(thisObject + 0x24) = 0xbf800000;
    *(undefined4 *)(thisObject + 0xfc) = 0;
    cVar8 = FUN_7ffe9a4ad740(plVar12,0xf);
    if (cVar8 != '\0') {
      *(undefined4 *)(thisObject + 0xfc) = 0xf;
    }
    bVar3 = thisObject[0x14];
    *(uint *)(thisObject + 0x128) = (bVar3 + 0x12) * 5;
    fVar16 = (float)bVar3 * _DAT_7ffe9c049b78;
    *(int *)(thisObject + 0x120) = (int)(bVar3 - 1) / 2 + 2;
    *(float *)(thisObject + 0x124) = fVar16 + _DAT_7ffe9c049cf8;
    if (((plVar12 == (longlong *)0x0) ||
        (plVar12 = (longlong *)
                   (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0)),
        plVar12 == (longlong *)0x0)) ||
       (puVar13 = (undefined *)
                  (**(code **)(*plVar12 + 0x218))(plVar12,*(undefined8 *)(*plVar12 + 0x220)),
       puVar13 == (undefined *)0x0)) {
LAB_7ffe9a6b5b95:
      FUN_7ffe9996d7a0();
      pcVar6 = (code *)swi(3);
      (*pcVar6)();
      return;
    }
    puVar13 = GemCartBufferManager_GetGemCartBuffer(puVar13,0x69,(undefined *)0x0);
    if (puVar13 != (undefined *)0x0) {
      iVar4 = *(int *)(thisObject + 0x120);
      iVar10 = GemCartBufferBase_GetValue(puVar13,(undefined *)0x2,(undefined *)0x0);
      *(int *)(thisObject + 0x120) = iVar10 + iVar4;
    }
    if (*(int *)(thisObject + 0xfc) == 0xf) {
      *(int *)(thisObject + 0x120) = *(int *)(thisObject + 0x120) + 2;
    }
    *(undefined4 *)(thisObject + 0x28) = *(undefined4 *)(thisObject + 0x120);
  }
  uVar14 = FUN_7ffe9a6b5530(thisObject,0);
  *(undefined8 *)(thisObject + 0x58) = uVar14;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar15 = (uint)((ulonglong)(thisObject + 0x58) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar15 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
    do {
      uVar5 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar5 == uVar2) {
        *puVar1 = uVar5 | 1L << (uVar15 & 0x3f);
      }
      UNLOCK();
    } while (uVar5 != uVar2);
  }
  return;
}

