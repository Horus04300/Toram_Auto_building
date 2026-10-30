
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicLancerAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined8 uVar10;
  undefined *puVar11;
  undefined8 uVar12;
  longlong *plVar13;
  float fVar14;
  float fVar15;
  longlong lStackX_10;
  
  if (DAT_7ffe9cadeed5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c92d500);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadeed5 = '\x01';
  }
  plVar13 = (longlong *)0x0;
  lStackX_10 = 0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    plVar13 = (longlong *)0x0;
    if (bVar2) {
      plVar13 = (longlong *)actarAction;
    }
  }
  lVar8 = FUN_7ffe9a47bac0(0);
  if ((lVar8 == 0) || (lVar8 = FUN_7ffe9a47f670(lVar8,0), lVar8 == 0)) goto LAB_7ffe9a6cf0a6;
  cVar3 = FUN_7ffe9ab94d80(lVar8,0x77,&lStackX_10,_DAT_7ffe9c92d500);
  if (cVar3 != '\0') {
    if (lStackX_10 == 0) goto LAB_7ffe9a6cf0a6;
    uVar4 = FUN_7ffe9a5212c0(lStackX_10,0x66);
    *(undefined2 *)(thisObject + 0x140) = uVar4;
  }
  if ((plVar13 == (longlong *)0x0) ||
     (lVar8 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)), lVar8 == 0
     )) goto LAB_7ffe9a6cf0a6;
  uVar5 = FUN_7ffe9a4a1cc0(lVar8,0);
  *(undefined4 *)(thisObject + 0x30) = uVar5;
  *(undefined4 *)(thisObject + 0xfc) = 0;
  cVar3 = FUN_7ffe9a4ad740(plVar13,0xe);
  if (cVar3 == '\0') {
    cVar3 = FUN_7ffe9a4ad740(plVar13,0xf);
    if (cVar3 != '\0') {
      *(undefined4 *)(thisObject + 0xfc) = 0xf;
    }
  }
  else {
    *(undefined4 *)(thisObject + 0xfc) = 0xe;
  }
  uVar5 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar5;
  fVar15 = (float)(byte)thisObject[0x14] * _DAT_7ffe9c049ce8 + _DAT_7ffe9c049df8;
  *(float *)(thisObject + 0x124) = fVar15;
  if (*(int *)(thisObject + 0xfc) == 0xe) {
    plVar9 = (longlong *)(**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
    if ((plVar9 == (longlong *)0x0) ||
       (lVar8 = (**(code **)(*plVar9 + 0x198))(plVar9,*(undefined8 *)(*plVar9 + 0x1a0)), lVar8 == 0)
       ) goto LAB_7ffe9a6cf0a6;
    iVar6 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar8);
    fVar14 = (float)iVar6 / _DAT_7ffe9c049ce0 + _DAT_7ffe9c049d98;
LAB_7ffe9a6cee52:
    *(float *)(thisObject + 0x124) = fVar14 + fVar15;
  }
  else if (*(int *)(thisObject + 0xfc) == 0xf) {
    plVar9 = (longlong *)(**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
    if ((plVar9 == (longlong *)0x0) ||
       (lVar8 = (**(code **)(*plVar9 + 0x198))(plVar9,*(undefined8 *)(*plVar9 + 0x1a0)), lVar8 == 0)
       ) goto LAB_7ffe9a6cf0a6;
    iVar6 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar8);
    fVar14 = (float)iVar6 / _DAT_7ffe9c049ce0;
    goto LAB_7ffe9a6cee52;
  }
  *(uint *)(thisObject + 0x128) = (uint)(byte)thisObject[0x14] * 4 + 300;
  iVar6 = (uint)(byte)thisObject[0x14] * 2 + 10;
  *(int *)(thisObject + 300) = iVar6;
  if (*(int *)(thisObject + 0xfc) - 0xeU < 2) {
    *(int *)(thisObject + 300) = iVar6 * 3;
  }
  if (thisObject[0x141] != '\0') {
    *(undefined4 *)(thisObject + 0x134) = *(undefined4 *)(thisObject + 300);
  }
  uVar10 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
  uVar5 = FUN_7ffe9a4a7fe0(thisObject,_DAT_7ffe9c049b70,uVar10,0);
  *(undefined4 *)(thisObject + 0x24) = uVar5;
  uVar10 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
  uVar5 = FUN_7ffe9a4aabb0(uVar10,0);
  *(undefined4 *)(thisObject + 0x78) = uVar5;
  iVar6 = (int)((byte)thisObject[0x14] - 1) / 5;
  *(int *)(thisObject + 0x120) = iVar6 + 2;
  if (*(int *)(thisObject + 0xfc) == 0xf) {
    *(int *)(thisObject + 0x120) = iVar6 + 4;
  }
  *(undefined4 *)(thisObject + 0x28) = *(undefined4 *)(thisObject + 0x120);
  *(undefined4 *)(thisObject + 0x130) = 0x14;
  plVar9 = (longlong *)(**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
  if ((plVar9 != (longlong *)0x0) &&
     (puVar11 = (undefined *)(**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220))
     , puVar11 != (undefined *)0x0)) {
    puVar11 = GemCartBufferManager_GetGemCartBuffer(puVar11,0xcd,(undefined *)0x0);
    if (puVar11 != (undefined *)0x0) {
      iVar6 = *(int *)(thisObject + 0x130);
      iVar7 = GemCartBufferBase_GetValue(puVar11,(undefined *)0x2,(undefined *)0x0);
      *(int *)(thisObject + 0x130) = iVar6 - iVar7;
    }
    if (thisObject[0x140] != '\0') {
      *(int *)(thisObject + 0x130) = *(int *)(thisObject + 0x130) + -10;
    }
    if (*(int *)(thisObject + 0x130) < 0) {
      *(undefined4 *)(thisObject + 0x130) = 0;
    }
    *(undefined4 *)(thisObject + 0x104) = *(undefined4 *)(thisObject + 0x130);
    FUN_7ffe9a4aacd0(thisObject,plVar13,0);
    if (*(int *)(thisObject + 0xfc) == 0xe) {
      uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
      uVar12 = 0x956a0;
    }
    else if (*(int *)(thisObject + 0xfc) == 0xf) {
      uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
      uVar12 = 0xad958;
    }
    else {
      uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
      uVar12 = 0x1d0d8;
    }
    FUN_7ffe9a9002e0(uVar10,uVar12,0);
    *(undefined8 *)(thisObject + 0x58) = uVar10;
    il2cpp_write_barrier_0();
    if ((*(longlong *)(thisObject + 0x58) != 0) &&
       (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar8 != 0)) {
      FUN_7ffe9ad10e00(lVar8,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
      lVar8 = *(longlong *)(thisObject + 0x58);
      uVar10 = FUN_7ffe9a6ce3e0(thisObject,0);
      if (lVar8 != 0) {
        *(undefined8 *)(lVar8 + 0x20) = uVar10;
        il2cpp_write_barrier_0();
        return;
      }
    }
  }
LAB_7ffe9a6cf0a6:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

