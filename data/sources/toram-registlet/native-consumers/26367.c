
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void WaterStyleAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  bool bVar3;
  byte bVar4;
  undefined8 uVar5;
  longlong *plVar6;
  undefined *thisObject_00;
  undefined4 uVar7;
  double dVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined8 extraout_XMM0_Qb;
  
  if (DAT_7ffe9cadf17c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf17c = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar6 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar6 = (longlong *)0x0;
    if (bVar3) {
      plVar6 = (longlong *)actarAction;
    }
  }
  uVar7 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar7;
  uVar7 = FUN_7ffe9a7b7a30(thisObject,700,plVar6,0);
  *(undefined4 *)(thisObject + 0x134) = uVar7;
  FUN_7ffe9a4aacd0(thisObject,plVar6,0);
  if (plVar6 != (longlong *)0x0) {
    uVar5 = (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    uVar7 = FUN_7ffe9a4aabb0(uVar5,0);
    *(undefined4 *)(thisObject + 0x78) = uVar7;
    uVar5 = (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    FUN_7ffe9a7b7ae0(thisObject,_DAT_7ffe9c049dc4,uVar5,0);
    auVar9._0_8_ = func_0x7ffe99997964((float)(byte)thisObject[0x14] * _DAT_7ffe9c049b4c);
    auVar9._8_8_ = extraout_XMM0_Qb;
    auVar10._4_12_ = auVar9._4_12_;
    auVar10._0_4_ = (float)auVar9._0_8_ * _DAT_7ffe9c049b4c + _DAT_7ffe9c049dc4;
    *(float *)(thisObject + 0x138) = auVar10._0_4_;
    uVar7 = func_0x7ffe99a4d6a0(auVar10._0_8_,0);
    *(undefined4 *)(thisObject + 0x138) = uVar7;
    *(undefined4 *)(thisObject + 0x13c) = 10;
    uVar5 = (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    bVar4 = FUN_7ffe9a7b7c00(thisObject,uVar5,0);
    iVar1 = *(int *)(thisObject + 0x13c);
    thisObject[0x150] = bVar4;
    if (DAT_7ffe9cad9c12 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c968830);
      DAT_7ffe9cad9c12 = '\x01';
    }
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    dVar8 = (double)func_0x7ffe999978b4((double)(bVar4 + 1 >> 1));
    *(int *)(thisObject + 0x13c) = (int)dVar8 + iVar1;
    plVar6 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    if (plVar6 != (longlong *)0x0) {
      thisObject_00 =
           (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
      if (thisObject_00 != (undefined *)0x0) {
        bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x19a,(undefined *)0x0);
        if (bVar4 != 0) {
          thisObject[0x140] = 1;
        }
        *(uint *)(thisObject + 0x104) =
             -(uint)(thisObject[0x140] != '\0') & 0x100 | (uint)(byte)thisObject[0x14] << 0x10 |
             (uint)(byte)thisObject[0x150];
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

