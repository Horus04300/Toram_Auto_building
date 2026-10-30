
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicWallAction_InitializeEnchantedSpell
               (undefined *thisObject,undefined *actarAction,byte isPlayer,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  code *pcVar4;
  bool bVar5;
  char cVar6;
  undefined4 uVar7;
  int iVar8;
  longlong lVar9;
  longlong *plVar10;
  longlong *plVar11;
  undefined *puVar12;
  undefined8 uVar13;
  uint uVar14;
  float fVar15;
  undefined2 auStackX_18 [4];
  
  if (DAT_7ffe9cadef0c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c8fee40);
    DAT_7ffe9cadef0c = '\x01';
  }
  plVar11 = (longlong *)0x0;
  auStackX_18[0] = 0;
  func_0x7ffe9af709e0(auStackX_18,0,0,_DAT_7ffe9c8fee40);
  *(undefined2 *)(thisObject + 0x150) = auStackX_18[0];
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
      plVar11 = (longlong *)0x0;
      if (bVar5) {
        plVar11 = (longlong *)actarAction;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar6 = FUN_7ffe9bda2160(plVar11,0,0);
    if (cVar6 != '\0') {
      if ((plVar11 == (longlong *)0x0) ||
         (lVar9 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
         lVar9 == 0)) goto LAB_7ffe9a6d3dd4;
      uVar7 = FUN_7ffe9a4a1fb0(lVar9,0);
      *(undefined4 *)(thisObject + 0x30) = uVar7;
    }
    *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 0x400;
    *(undefined4 *)(thisObject + 0x24) = 0xbf800000;
    *(undefined4 *)(thisObject + 0xfc) = 0;
    cVar6 = FUN_7ffe9a4ad740(plVar11,0xf);
    if (cVar6 != '\0') {
      *(undefined4 *)(thisObject + 0xfc) = 0xf;
    }
    fVar15 = (float)(byte)thisObject[0x14] * _DAT_7ffe9c049d14 + _DAT_7ffe9c049de0;
    *(float *)(thisObject + 0x134) = fVar15;
    if (*(int *)(thisObject + 0xfc) == 0xf) {
      if (((plVar11 == (longlong *)0x0) ||
          (plVar10 = (longlong *)
                     (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
          plVar10 == (longlong *)0x0)) ||
         (lVar9 = (**(code **)(*plVar10 + 0x188))(plVar10,*(undefined8 *)(*plVar10 + 400)),
         lVar9 == 0)) goto LAB_7ffe9a6d3dd4;
      *(float *)(thisObject + 0x134) = (float)(*(int *)(lVar9 + 0x18) / 10) + fVar15;
    }
    else if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a6d3dd4;
    plVar11 = (longlong *)(**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0))
    ;
    if ((plVar11 == (longlong *)0x0) ||
       (puVar12 = (undefined *)
                  (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
       puVar12 == (undefined *)0x0)) {
LAB_7ffe9a6d3dd4:
      FUN_7ffe9996d7a0();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    puVar12 = GemCartBufferManager_GetGemCartBuffer(puVar12,0x6a,(undefined *)0x0);
    if (puVar12 != (undefined *)0x0) {
      fVar15 = *(float *)(thisObject + 0x134);
      iVar8 = GemCartBufferBase_GetValue(puVar12,(undefined *)0x4,(undefined *)0x0);
      *(float *)(thisObject + 0x134) = (float)iVar8 + fVar15;
    }
    *(undefined4 *)(thisObject + 0x130) = 0x3fc00000;
    *(uint *)(thisObject + 0x138) = ((byte)thisObject[0x14] + 0xc) * 10;
    if (*(int *)(thisObject + 0xfc) == 0xf) {
      *(undefined4 *)(thisObject + 0x130) = 0x40200000;
    }
    uVar7 = func_0x7ffe99a4d6a0();
    *(undefined4 *)(thisObject + 0x130) = uVar7;
    iVar8 = 5 - (int)((float)(byte)thisObject[0x14] * _DAT_7ffe9c049e04);
    *(int *)(thisObject + 0x120) = iVar8;
    *(int *)(thisObject + 0x28) = iVar8;
    FUN_7ffe9a6d48f0(thisObject,0);
  }
  uVar13 = FUN_7ffe9a6d36d0(thisObject,0);
  *(undefined8 *)(thisObject + 0x58) = uVar13;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar14 = (uint)((ulonglong)(thisObject + 0x58) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar14 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
    do {
      uVar3 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar3 == uVar2) {
        *puVar1 = uVar3 | 1L << (uVar14 & 0x3f);
      }
      UNLOCK();
    } while (uVar3 != uVar2);
  }
  return;
}

