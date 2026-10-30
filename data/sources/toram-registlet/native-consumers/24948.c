
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicLancerAction_InitializeEnchantedSpell
               (undefined *thisObject,undefined *actarAction,byte isPlayer,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  byte bVar3;
  ulonglong uVar4;
  code *pcVar5;
  bool bVar6;
  char cVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  longlong lVar11;
  longlong *plVar12;
  longlong *plVar13;
  undefined *puVar14;
  undefined8 uVar15;
  uint uVar16;
  float fVar17;
  undefined2 auStackX_18 [4];
  
  if (DAT_7ffe9cadeedd == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c8fee40);
    DAT_7ffe9cadeedd = '\x01';
  }
  plVar13 = (longlong *)0x0;
  auStackX_18[0] = 0;
  func_0x7ffe9af709e0(auStackX_18,0,0,_DAT_7ffe9c8fee40);
  *(undefined2 *)(thisObject + 0x140) = auStackX_18[0];
  if (isPlayer != 0) {
    if (actarAction != (undefined *)0x0) {
      if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      plVar13 = (longlong *)0x0;
      if (bVar6) {
        plVar13 = (longlong *)actarAction;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar7 = FUN_7ffe9bda2160(plVar13,0,0);
    if (cVar7 != '\0') {
      if ((plVar13 == (longlong *)0x0) ||
         (lVar11 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
         lVar11 == 0)) goto LAB_7ffe9a6cea39;
      uVar8 = FUN_7ffe9a4a1fb0(lVar11,0);
      *(undefined4 *)(thisObject + 0x30) = uVar8;
    }
    *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 0x400;
    *(undefined4 *)(thisObject + 0x24) = 0xbf800000;
    *(undefined4 *)(thisObject + 0xfc) = 0;
    cVar7 = FUN_7ffe9a4ad740(plVar13,0xf);
    if (cVar7 != '\0') {
      *(undefined4 *)(thisObject + 0xfc) = 0xf;
    }
    bVar3 = thisObject[0x14];
    *(uint *)(thisObject + 0x128) = (uint)bVar3 * 4 + 300;
    *(uint *)(thisObject + 300) = (uint)bVar3 * 2 + 10;
    fVar17 = (float)bVar3 * _DAT_7ffe9c049ce8 + _DAT_7ffe9c049df8;
    iVar9 = (int)(bVar3 - 1) / 5 + 2;
    *(float *)(thisObject + 0x124) = fVar17;
    *(int *)(thisObject + 0x120) = iVar9;
    if (*(int *)(thisObject + 0xfc) == 0xf) {
      if (((plVar13 == (longlong *)0x0) ||
          (plVar12 = (longlong *)
                     (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
          plVar12 == (longlong *)0x0)) ||
         (lVar11 = (**(code **)(*plVar12 + 0x198))(plVar12,*(undefined8 *)(*plVar12 + 0x1a0)),
         lVar11 == 0)) goto LAB_7ffe9a6cea39;
      iVar9 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar11);
      *(int *)(thisObject + 0x120) = *(int *)(thisObject + 0x120) + 2;
      *(undefined8 *)(thisObject + 0x130) = 0x14;
      *(int *)(thisObject + 300) = *(int *)(thisObject + 300) * 3;
      *(undefined4 *)(thisObject + 0x28) = *(undefined4 *)(thisObject + 0x120);
      *(float *)(thisObject + 0x124) = (float)iVar9 / _DAT_7ffe9c049ce0 + fVar17;
    }
    else {
      *(int *)(thisObject + 0x28) = iVar9;
      *(undefined8 *)(thisObject + 0x130) = 0x14;
      if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a6cea39;
    }
    plVar13 = (longlong *)(**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0))
    ;
    if ((plVar13 == (longlong *)0x0) ||
       (puVar14 = (undefined *)
                  (**(code **)(*plVar13 + 0x218))(plVar13,*(undefined8 *)(*plVar13 + 0x220)),
       puVar14 == (undefined *)0x0)) {
LAB_7ffe9a6cea39:
      FUN_7ffe9996d7a0();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    puVar14 = GemCartBufferManager_GetGemCartBuffer(puVar14,0xcd,(undefined *)0x0);
    if (puVar14 != (undefined *)0x0) {
      iVar9 = *(int *)(thisObject + 0x130);
      iVar10 = GemCartBufferBase_GetValue(puVar14,(undefined *)0x2,(undefined *)0x0);
      *(int *)(thisObject + 0x130) = iVar9 - iVar10;
    }
    if (*(int *)(thisObject + 0x130) < 0) {
      *(undefined4 *)(thisObject + 0x130) = 0;
    }
    *(undefined4 *)(thisObject + 0x104) = *(undefined4 *)(thisObject + 0x130);
  }
  uVar15 = FUN_7ffe9a6ce3e0(thisObject,0);
  *(undefined8 *)(thisObject + 0x58) = uVar15;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar16 = (uint)((ulonglong)(thisObject + 0x58) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar16 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
    do {
      uVar4 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar4 == uVar2) {
        *puVar1 = uVar4 | 1L << (uVar16 & 0x3f);
      }
      UNLOCK();
    } while (uVar4 != uVar2);
  }
  return;
}

