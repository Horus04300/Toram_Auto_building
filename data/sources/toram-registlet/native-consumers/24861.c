
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicImpactAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  byte bVar3;
  char cVar4;
  char extraout_AH;
  longlong *plVar5;
  undefined *thisObject_00;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  int iVar9;
  undefined4 uVar10;
  float fVar11;
  float fVar12;
  double dVar13;
  longlong lStackX_10;
  
  if (DAT_7ffe9cadeeb5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c92d500);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadeeb5 = '\x01';
  }
  lStackX_10 = 0;
  if (actarAction == (undefined *)0x0) goto LAB_7ffe9a6c4280;
  if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
     (*(longlong *)
       (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
       (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720))
  goto LAB_7ffe9a6c4280;
  plVar5 = (longlong *)
           (**(code **)(*(longlong *)actarAction + 0x298))
                     (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  if (plVar5 == (longlong *)0x0) goto LAB_7ffe9a6c4280;
  thisObject_00 =
       (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220));
  if (thisObject_00 == (undefined *)0x0) goto LAB_7ffe9a6c4280;
  bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x193,(undefined *)0x0);
  thisObject[0x149] = bVar3;
  *(undefined4 *)(thisObject + 0x30) = 7;
  *(undefined4 *)(thisObject + 0xfc) = 0;
  cVar4 = FUN_7ffe9a4ad740(actarAction,0xe,0);
  if (cVar4 == '\0') {
    cVar4 = FUN_7ffe9a4ad740(actarAction,0xf,0);
    if (cVar4 != '\0') {
      *(undefined4 *)(thisObject + 0xfc) = 0xf;
    }
  }
  else {
    *(undefined4 *)(thisObject + 0xfc) = 0xe;
  }
  uVar10 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar10;
  plVar5 = (longlong *)
           (**(code **)(*(longlong *)actarAction + 0x298))
                     (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  if (plVar5 == (longlong *)0x0) goto LAB_7ffe9a6c4280;
  lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0));
  if (lVar6 == 0) goto LAB_7ffe9a6c4280;
  cVar4 = FUN_7ffe9a7c6d00(lVar6,0x69);
  fVar11 = _DAT_7ffe9c049df8;
  bVar3 = thisObject[0x14];
  iVar2 = ((uint)bVar3 + (uint)bVar3 * 4) * 2;
  if (cVar4 == '\0') {
    iVar9 = (uint)bVar3 + (uint)bVar3 * 4;
    *(int *)(thisObject + 0x130) = iVar2 + 100;
    *(int *)(thisObject + 0x134) = iVar9 + 0xf;
    fVar12 = (float)((uint)bVar3 * 0x19);
    *(float *)(thisObject + 300) = fVar12;
    if (*(int *)(thisObject + 0xfc) == 0xf) {
      *(float *)(thisObject + 300) = fVar12 + fVar11;
    }
    else if (*(int *)(thisObject + 0xfc) == 0xe) {
      *(int *)(thisObject + 0x134) = iVar9 + 0x28;
    }
    lVar6 = FUN_7ffe9a47bac0(0);
    if (lVar6 == 0) goto LAB_7ffe9a6c4280;
    lVar6 = FUN_7ffe9a47f670(lVar6,0);
    if (lVar6 == 0) goto LAB_7ffe9a6c4280;
    cVar4 = FUN_7ffe9ab94d80(lVar6,0x77,&lStackX_10,_DAT_7ffe9c92d500);
    if (cVar4 != '\0') {
      if (lStackX_10 == 0) goto LAB_7ffe9a6c4280;
      FUN_7ffe9a5212c0(lStackX_10,0x69);
      if (extraout_AH != '\0') {
        fVar12 = *(float *)(thisObject + 0x138) + _DAT_7ffe9c049b18;
        *(int *)(thisObject + 0x134) = *(int *)(thisObject + 0x134) + 0x23;
        fVar11 = *(float *)(thisObject + 300) + fVar11;
        *(float *)(thisObject + 0x138) = fVar12;
        goto LAB_7ffe9a6c401a;
      }
    }
  }
  else {
    *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 1;
    fVar11 = (float)iVar2;
    *(int *)(thisObject + 0x130) = iVar2 + 100;
    thisObject[0x148] = 1;
    *(uint *)(thisObject + 0x134) = (uint)bVar3;
LAB_7ffe9a6c401a:
    *(float *)(thisObject + 300) = fVar11;
  }
  uVar10 = func_0x7ffe99a4d6a0();
  bVar3 = thisObject[0x14];
  *(undefined4 *)(thisObject + 0x138) = uVar10;
  if (DAT_7ffe9cad9e25 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cad9e25 = '\x01';
  }
  fVar11 = (float)bVar3 * _DAT_7ffe9c049c7c + _DAT_7ffe9c049b4c;
  if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  dVar13 = (double)func_0x7ffe99997768((double)fVar11);
  fVar11 = _DAT_7ffe9c049b74 - (float)(int)dVar13;
  *(float *)(thisObject + 0x24) = fVar11;
  uVar7 = (**(code **)(*(longlong *)actarAction + 0x298))
                    (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  uVar10 = FUN_7ffe9a4a7fe0(thisObject,fVar11,uVar7,0);
  *(undefined4 *)(thisObject + 0x24) = uVar10;
  uVar7 = (**(code **)(*(longlong *)actarAction + 0x298))
                    (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  uVar10 = FUN_7ffe9a4aabb0(uVar7,0);
  *(undefined4 *)(thisObject + 0x78) = uVar10;
  FUN_7ffe9a4aacd0(thisObject,actarAction,0);
  *(int *)(thisObject + 0x104) = (int)(*(float *)(thisObject + 0x138) * _DAT_7ffe9c049ce4);
  if (0.0 < *(float *)(thisObject + 0x24)) {
    uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
    uVar8 = 0x1bd55;
  }
  else {
    thisObject[0x13c] = 0;
    uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
    uVar8 = 0x1bd51;
  }
  FUN_7ffe9a9002e0(uVar7,uVar8,0);
  *(undefined8 *)(thisObject + 0x58) = uVar7;
  il2cpp_write_barrier_0();
  if ((*(longlong *)(thisObject + 0x58) != 0) &&
     (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
    FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
    lVar6 = *(longlong *)(thisObject + 0x58);
    uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
    FUN_7ffe9a9002e0(uVar7,0x134de50,0);
    if (lVar6 != 0) {
      *(undefined8 *)(lVar6 + 0x20) = uVar7;
      il2cpp_write_barrier_0();
      if (((*(longlong *)(thisObject + 0x58) != 0) &&
          (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar6 != 0)) &&
         (lVar6 = *(longlong *)(lVar6 + 0x50), lVar6 != 0)) {
        FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
        if ((*(longlong *)(thisObject + 0x58) != 0) &&
           (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar6 != 0)) {
          lVar6 = *(longlong *)(lVar6 + 0x50);
          fVar11 = (float)func_0x7ffe99a4d6b0();
          if (lVar6 != 0) {
            FUN_7ffe9ad10e00(lVar6,6,(int)(fVar11 * _DAT_7ffe9c04a778),_DAT_7ffe9c949490);
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a6c4280:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

