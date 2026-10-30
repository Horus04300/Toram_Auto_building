
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerActionManager_OnRespawn(undefined *thisObject,byte orbRespawn,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  longlong *plStackX_8;
  ulonglong uVar11;
  ulonglong in_stack_ffffffffffffffd0;
  
  if (DAT_7ffe9caddcb0 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94e108);
    FUN_7ffe9996d590(&DAT_7ffe9c933e28);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c95dac8);
    DAT_7ffe9caddcb0 = '\x01';
  }
  lVar6 = *(longlong *)(thisObject + 0x90);
  plStackX_8 = (longlong *)0x0;
  if (lVar6 == 0) goto LAB_7ffe9a450a2f;
  lVar1 = *(longlong *)(lVar6 + 0x70);
  uVar4 = FUN_7ffe9a47fef0(lVar6,0);
  if (lVar1 == 0) goto LAB_7ffe9a450a2f;
  cVar3 = FUN_7ffe99a231d0(lVar1,0xe,uVar4,&plStackX_8,0);
  if (cVar3 != '\0') {
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar6 == 0) goto LAB_7ffe9a450a2f;
    in_stack_ffffffffffffffd0 = 0;
    FUN_7ffe9a8d8390(lVar6,0x57,0,0xe,1,0);
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a450a2f;
    if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c933e28 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_8 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c933e28 + 0x130) * 8) != _DAT_7ffe9c933e28)) ||
       (plStackX_8 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_8);
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    FUN_7ffe99cfbc40(plStackX_8,1,0);
  }
  lVar6 = *(longlong *)(thisObject + 0x90);
  if (lVar6 == 0) goto LAB_7ffe9a450a2f;
  lVar1 = *(longlong *)(lVar6 + 0x70);
  uVar4 = FUN_7ffe9a47fef0(lVar6,0);
  if (lVar1 == 0) goto LAB_7ffe9a450a2f;
  cVar3 = FUN_7ffe99a231d0(lVar1,0xf,uVar4,&plStackX_8,0);
  if (cVar3 != '\0') {
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar6 == 0) goto LAB_7ffe9a450a2f;
    in_stack_ffffffffffffffd0 = 0;
    FUN_7ffe9a8d8390(lVar6,0x46b,0,0xf,1,0);
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a450a2f;
    if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c95dac8 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_8 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c95dac8 + 0x130) * 8) != _DAT_7ffe9c95dac8)) ||
       (plStackX_8 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_8);
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    FUN_7ffe9a4f2e30(plStackX_8,1,0);
  }
  lVar6 = *(longlong *)(thisObject + 0x90);
  if (lVar6 == 0) goto LAB_7ffe9a450a2f;
  lVar1 = *(longlong *)(lVar6 + 0x70);
  uVar4 = FUN_7ffe9a47fef0(lVar6,0);
  if (lVar1 == 0) goto LAB_7ffe9a450a2f;
  uVar11 = 0;
  cVar3 = FUN_7ffe99a231d0(lVar1,0x10,uVar4,&plStackX_8,0);
  if (cVar3 != '\0') {
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar6 == 0) goto LAB_7ffe9a450a2f;
    in_stack_ffffffffffffffd0 = 0;
    uVar11 = CONCAT71((int7)(uVar11 >> 8),1);
    FUN_7ffe9a8d8390(lVar6,0x241,0,0x10,uVar11,0);
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a450a2f;
    if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c94e108 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_8 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c94e108 + 0x130) * 8) != _DAT_7ffe9c94e108)) ||
       (plStackX_8 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_8);
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    FUN_7ffe99b1c4d0(plStackX_8,1,0);
  }
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)thisObject + 0x298))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a450a2f;
  lVar6 = (**(code **)(*plVar7 + 0x1e8))(plVar7,*(undefined8 *)(*plVar7 + 0x1f0));
  if (lVar6 == 0) goto LAB_7ffe9a450a2f;
  FUN_7ffe9a4da870(lVar6,0);
  if (*(longlong *)(thisObject + 0x108) == 0) goto LAB_7ffe9a450a2f;
  FUN_7ffe99aae9f0(*(longlong *)(thisObject + 0x108),0);
  if (*(longlong *)(thisObject + 0x90) == 0) goto LAB_7ffe9a450a2f;
  FUN_7ffe9a47ec80(*(longlong *)(thisObject + 0x90),0);
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)thisObject + 0x298))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a450a2f;
  puVar8 = (undefined *)(**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
  if (puVar8 == (undefined *)0x0) goto LAB_7ffe9a450a2f;
  puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x28,(undefined *)0x0);
  if (puVar8 == (undefined *)0x0) {
LAB_7ffe9a45093e:
    uVar9 = FUN_7ffe9bd98960(thisObject,0);
    uVar10 = 0x19;
  }
  else {
    iVar5 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
    if (iVar5 == 0) goto LAB_7ffe9a45093e;
    uVar9 = FUN_7ffe9bd98960(thisObject,0);
    uVar10 = 0x1b;
  }
  (**(code **)(*(longlong *)thisObject + 0x238))
            (thisObject,uVar9,uVar10,_DAT_7ffe9c049ce4,uVar11 & 0xffffffff00000000,
             in_stack_ffffffffffffffd0 & 0xffffffff00000000,0,1,
             *(undefined8 *)(*(longlong *)thisObject + 0x240));
  plVar7 = *(longlong **)(thisObject + 0x98);
  if (plVar7 != (longlong *)0x0) {
    (**(code **)(*plVar7 + 0x388))(plVar7,*(undefined8 *)(*plVar7 + 0x390));
    if (*(longlong *)(thisObject + 0x28) != 0) {
      FUN_7ffe99b1dd90(*(longlong *)(thisObject + 0x28),0);
      if (*(longlong *)(thisObject + 0x28) != 0) {
        *(undefined1 *)(*(longlong *)(thisObject + 0x28) + 0x138) = 1;
        if (*(longlong *)(thisObject + 0x28) != 0) {
          *(undefined1 *)(*(longlong *)(thisObject + 0x28) + 0x13b) = 1;
          if (*(longlong *)(thisObject + 0x28) != 0) {
            *(undefined1 *)(*(longlong *)(thisObject + 0x28) + 0x13a) = 0;
            (**(code **)(*(longlong *)thisObject + 0x448))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x450));
            lVar6 = FUN_7ffe9a4565c0(thisObject,0);
            if (lVar6 != 0) {
              func_0x7ffe9a7e03f0(lVar6,orbRespawn,0);
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a450a2f:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

