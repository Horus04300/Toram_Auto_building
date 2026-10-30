
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MeteorStrikeAction_InitializeHighFamilia
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  longlong lVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  longlong *plVar6;
  undefined *thisObject_00;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 *puVar9;
  undefined8 uStack_28;
  undefined4 uStack_20;
  undefined1 auStack_18 [16];
  
  if (DAT_7ffe9cadf351 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf351 = '\x01';
  }
  *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 0x100;
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
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(plVar6,0,0);
  if (cVar4 != '\0') {
    if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a77250f;
    plVar6 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a77250f;
    thisObject_00 =
         (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
    if (thisObject_00 == (undefined *)0x0) goto LAB_7ffe9a77250f;
    bVar5 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3fe,(undefined *)0x0);
    thisObject[0x18c] = bVar5;
  }
  uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
  FUN_7ffe9a9002e0(uVar7,0x11e855d7,0);
  *(undefined8 *)(thisObject + 0x58) = uVar7;
  il2cpp_write_barrier_0();
  lVar1 = *(longlong *)(thisObject + 0x58);
  if (target != (undefined *)0x0) {
    lVar8 = FUN_7ffe9bd9b890(target,0);
    if (lVar8 != 0) {
      puVar9 = (undefined8 *)FUN_7ffe9bdbf710(auStack_18,lVar8,0);
      uStack_28 = *puVar9;
      uStack_20 = *(undefined4 *)(puVar9 + 1);
      uVar7 = FUN_7ffe9a771e00(thisObject,&uStack_28,0);
      if (lVar1 != 0) {
        *(undefined8 *)(lVar1 + 0x18) = uVar7;
        il2cpp_write_barrier_0();
        *(uint *)(thisObject + 0x28) = (uint)(byte)thisObject[0x188];
        *(undefined4 *)(thisObject + 0x24) = 0x3f800000;
        return;
      }
    }
  }
LAB_7ffe9a77250f:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

