
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RapidAquaVortexAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  longlong *plVar8;
  undefined *thisObject_00;
  undefined4 uVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  float fVar12;
  undefined8 extraout_XMM0_Qb;
  
  if (DAT_7ffe9cadf15e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf15e = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar8 = (longlong *)0x0;
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
    plVar8 = (longlong *)0x0;
    if (bVar2) {
      plVar8 = (longlong *)actarAction;
    }
  }
  uVar9 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar9;
  uVar9 = FUN_7ffe9a4ae0a0(plVar8,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar9;
  if (plVar8 != (longlong *)0x0) {
    lVar6 = (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
    if (lVar6 != 0) {
      uVar9 = FUN_7ffe9a4a1cc0(lVar6,0);
      *(undefined4 *)(thisObject + 0x30) = uVar9;
      uVar9 = FUN_7ffe9a7b7a30(thisObject,300,plVar8,0);
      *(undefined4 *)(thisObject + 0x134) = uVar9;
      FUN_7ffe9a4aacd0(thisObject,plVar8,0);
      uVar7 = (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
      uVar9 = FUN_7ffe9a4aabb0(uVar7,0);
      *(undefined4 *)(thisObject + 0x78) = uVar9;
      uVar7 = (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
      FUN_7ffe9a7b7ae0(thisObject,0,uVar7,0);
      uVar7 = (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
      uVar4 = FUN_7ffe9a7b7c00(thisObject,uVar7,0);
      *(undefined4 *)(thisObject + 0x13c) = 500;
      *(float *)(thisObject + 0x138) = (float)(((byte)thisObject[0x14] + 10) * 10);
      auVar10._0_8_ = func_0x7ffe99997964((float)(byte)thisObject[0x14] * _DAT_7ffe9c049b4c);
      auVar10._8_8_ = extraout_XMM0_Qb;
      auVar11._4_12_ = auVar10._4_12_;
      auVar11._0_4_ = (float)auVar10._0_8_ * _DAT_7ffe9c049b4c + _DAT_7ffe9c049dc4;
      *(float *)(thisObject + 0x140) = auVar11._0_4_;
      uVar9 = func_0x7ffe99a4d6a0(auVar11._0_8_,0);
      fVar12 = *(float *)(thisObject + 0x138);
      *(undefined4 *)(thisObject + 0x140) = uVar9;
      *(undefined4 *)(thisObject + 0x14c) = 10;
      *(uint *)(thisObject + 0x144) =
           ((uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4) * 2;
      uVar7 = (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
      iVar5 = FUN_7ffe9a7b7c00(thisObject,uVar7,0);
      fVar12 = (float)(iVar5 * 10) + fVar12;
      *(float *)(thisObject + 0x138) = fVar12;
      uVar7 = (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
      iVar5 = FUN_7ffe9a7b7d10(thisObject,uVar7,0);
      *(float *)(thisObject + 0x138) = (float)(iVar5 / 2) + fVar12;
      plVar8 = (longlong *)(**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
      if (plVar8 != (longlong *)0x0) {
        thisObject_00 =
             (undefined *)(**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220));
        if (thisObject_00 != (undefined *)0x0) {
          bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x19a,(undefined *)0x0);
          if (bVar3 != 0) {
            thisObject[0x158] = 1;
          }
          *(uint *)(thisObject + 0x104) =
               -(uint)(thisObject[0x158] != '\0') & 0x100 | (uint)(byte)thisObject[0x14] << 0x10 |
               uVar4 & 0xff;
          return;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

