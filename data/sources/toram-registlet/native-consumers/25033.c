
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicWallAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  undefined2 uVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  longlong *plVar11;
  undefined4 uVar12;
  float fVar13;
  longlong lStackX_10;
  
  if (DAT_7ffe9cadef00 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c92d500);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadef00 = '\x01';
  }
  lStackX_10 = 0;
  if (actarAction == (undefined *)0x0) {
    plVar11 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    plVar11 = (longlong *)0x0;
    if (bVar2) {
      plVar11 = (longlong *)actarAction;
    }
  }
  lVar6 = FUN_7ffe9a47bac0(0);
  if (lVar6 == 0) goto LAB_7ffe9a6d457d;
  lVar6 = FUN_7ffe9a47f670(lVar6,0);
  if (lVar6 == 0) goto LAB_7ffe9a6d457d;
  cVar3 = FUN_7ffe9ab94d80(lVar6,0x77,&lStackX_10,_DAT_7ffe9c92d500);
  if (cVar3 != '\0') {
    if (lStackX_10 == 0) goto LAB_7ffe9a6d457d;
    uVar4 = FUN_7ffe9a5212c0(lStackX_10,99);
    *(undefined2 *)(thisObject + 0x150) = uVar4;
  }
  uVar12 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar12;
  if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a6d457d;
  lVar6 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
  if (lVar6 == 0) goto LAB_7ffe9a6d457d;
  uVar12 = FUN_7ffe9a4a1cc0(lVar6,0);
  *(undefined4 *)(thisObject + 0x30) = uVar12;
  *(undefined4 *)(thisObject + 0xfc) = 0;
  cVar3 = FUN_7ffe9a4ad740(plVar11,0xe);
  if (cVar3 == '\0') {
    cVar3 = FUN_7ffe9a4ad740(plVar11,0xf);
    if (cVar3 != '\0') {
      *(undefined4 *)(thisObject + 0xfc) = 0xf;
    }
  }
  else {
    *(undefined4 *)(thisObject + 0xfc) = 0xe;
  }
  fVar13 = (float)(byte)thisObject[0x14] * _DAT_7ffe9c049d14 + _DAT_7ffe9c049de0;
  *(float *)(thisObject + 0x134) = fVar13;
  if (*(int *)(thisObject + 0xfc) == 0xe) {
    plVar7 = (longlong *)(**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
    if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a6d457d;
    lVar6 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
    if (lVar6 == 0) goto LAB_7ffe9a6d457d;
    iVar5 = *(int *)(lVar6 + 0x18) / 10 + 0x1e;
LAB_7ffe9a6d4342:
    *(float *)(thisObject + 0x134) = (float)iVar5 + fVar13;
  }
  else if (*(int *)(thisObject + 0xfc) == 0xf) {
    plVar7 = (longlong *)(**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
    if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a6d457d;
    lVar6 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
    if (lVar6 == 0) goto LAB_7ffe9a6d457d;
    iVar5 = *(int *)(lVar6 + 0x18) / 10;
    goto LAB_7ffe9a6d4342;
  }
  plVar7 = (longlong *)(**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
  if (plVar7 != (longlong *)0x0) {
    puVar8 = (undefined *)(**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
    if (puVar8 != (undefined *)0x0) {
      puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x6a,(undefined *)0x0);
      if (puVar8 != (undefined *)0x0) {
        fVar13 = *(float *)(thisObject + 0x134);
        iVar5 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x4,(undefined *)0x0);
        *(float *)(thisObject + 0x134) = (float)iVar5 + fVar13;
      }
      *(undefined4 *)(thisObject + 0x130) = 0x3fc00000;
      *(uint *)(thisObject + 0x138) = ((byte)thisObject[0x14] + 0xc) * 10;
      if (*(int *)(thisObject + 0xfc) == 0xf) {
        *(undefined4 *)(thisObject + 0x130) = 0x40200000;
      }
      uVar12 = func_0x7ffe99a4d6a0();
      *(undefined4 *)(thisObject + 0x130) = uVar12;
      iVar5 = 5 - (int)((float)(byte)thisObject[0x14] * _DAT_7ffe9c049e04);
      *(int *)(thisObject + 0x120) = iVar5;
      if (thisObject[0x151] != '\0') {
        *(int *)(thisObject + 0x120) = iVar5 * 3;
      }
      *(undefined4 *)(thisObject + 0x28) = *(undefined4 *)(thisObject + 0x120);
      (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      uVar12 = FUN_7ffe9a4a7fe0(thisObject);
      *(undefined4 *)(thisObject + 0x24) = uVar12;
      uVar9 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      uVar12 = FUN_7ffe9a4aabb0(uVar9,0);
      *(undefined4 *)(thisObject + 0x78) = uVar12;
      FUN_7ffe9a4aacd0(thisObject,plVar11,0);
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
        uVar9 = FUN_7ffe9a6d36d0(thisObject,0);
        if (lVar6 != 0) {
          *(undefined8 *)(lVar6 + 0x20) = uVar9;
          il2cpp_write_barrier_0();
          FUN_7ffe9a6d48f0(thisObject,0);
          return;
        }
      }
    }
  }
LAB_7ffe9a6d457d:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

