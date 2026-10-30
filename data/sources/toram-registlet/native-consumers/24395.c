
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BindStrikeAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  longlong lVar4;
  undefined1 uVar5;
  char cVar6;
  byte bVar7;
  undefined4 uVar8;
  longlong *plVar9;
  longlong lVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  longlong lVar13;
  undefined *thisObject_00;
  undefined4 auStackX_10 [2];
  undefined8 in_stack_ffffffffffffff88;
  undefined4 uVar14;
  undefined8 in_stack_ffffffffffffff90;
  undefined4 uVar15;
  ulonglong in_stack_ffffffffffffff98;
  undefined4 auStack_48 [8];
  
  uVar14 = (undefined4)((ulonglong)in_stack_ffffffffffffff88 >> 0x20);
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffff90 >> 0x20);
  if (DAT_7ffe9cadee02 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadee02 = '\x01';
  }
  auStack_48[0] = 0;
  auStackX_10[0] = 0;
  if (playerAction == (undefined *)0x0) goto LAB_7ffe9a6a033e;
  plVar9 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a6a033e;
  lVar10 = (**(code **)(*plVar9 + 0x1a8))(plVar9,*(undefined8 *)(*plVar9 + 0x1b0));
  if (lVar10 == 0) goto LAB_7ffe9a6a033e;
  uVar8 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,lVar10);
  uVar5 = FUN_7ffe9a4b33f0(thisObject,uVar8,mobAction,0);
  uVar11 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
  FUN_7ffe9a6596c0(uVar11,0);
  uVar8 = (**(code **)(*(longlong *)thisObject + 0x198))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
  if (*(longlong *)(thisObject + 0xb8) == 0) goto LAB_7ffe9a6a033e;
  lVar10 = FUN_7ffe9a4b1c10(thisObject,uVar11,playerAction,mobAction,CONCAT44(uVar14,uVar8),
                            CONCAT44(uVar15,*(undefined4 *)(*(longlong *)(thisObject + 0xb8) + 0x1c)
                                    ),in_stack_ffffffffffffff98 & 0xffffffff00000000,uVar5,0);
  if (thisObject[0x130] != '\0') {
    if (mobAction == (undefined *)0x0) goto LAB_7ffe9a6a033e;
    uVar11 = FUN_7ffe99742ec0(0xd,_DAT_7ffe9c9724e0,mobAction);
    uVar12 = FUN_7ffe9bd98960(playerAction,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar6 = FUN_7ffe9bda1fa0(uVar11,uVar12,0);
    if (cVar6 != '\0') {
      plVar9 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a6a033e;
      lVar13 = (**(code **)(*plVar9 + 0x198))(plVar9,*(undefined8 *)(*plVar9 + 0x1a0));
      if (lVar13 == 0) goto LAB_7ffe9a6a033e;
      FUN_7ffe99742ec0(3,_DAT_7ffe9c940d40,lVar13);
    }
  }
  if (lVar10 == 0) goto LAB_7ffe9a6a033e;
  FUN_7ffe9a657c40(lVar10,0x12);
  FUN_7ffe9a657a50(lVar10,8);
  uVar11 = func_0x7ffe99940040(_DAT_7ffe9c920098);
  FUN_7ffe9a8f6350(uVar11,mobAction,0);
  lVar10 = FUN_7ffe9a4b4370(thisObject,uVar11,lVar10,1,0);
  if (lVar10 == 0) goto LAB_7ffe9a6a033e;
  if (*(int *)(lVar10 + 0x1c) != 0) {
    if (*(int *)(lVar10 + 0x34) != 1) {
      plVar9 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a6a033e;
      thisObject_00 =
           (undefined *)(**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220));
      if (thisObject_00 == (undefined *)0x0) goto LAB_7ffe9a6a033e;
      bVar7 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3fd,(undefined *)0x0);
      if (bVar7 == 0) {
        cVar6 = FUN_7ffe9a4b2fb0(thisObject,0xc,*(undefined4 *)(thisObject + 0x128),playerAction,
                                 mobAction,auStackX_10,0);
        if (cVar6 != '\0') {
          lVar13 = *(longlong *)(lVar10 + 0x38);
          if (lVar13 == 0) goto LAB_7ffe9a6a033e;
          uVar11 = 0xc;
LAB_7ffe9a6a0264:
          FUN_7ffe9a8ffe30(lVar13,uVar11);
        }
      }
      else {
        if (mobAction == (undefined *)0x0) goto LAB_7ffe9a6a033e;
        uVar12 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c9724e0,mobAction);
        uVar11 = *(undefined8 *)(thisObject + 0x138);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar6 = FUN_7ffe9bda1fa0(uVar12,uVar11,0);
        if (cVar6 != '\0') {
          cVar6 = FUN_7ffe9a4b2fb0(thisObject,3,*(undefined4 *)(thisObject + 0x128),playerAction,
                                   mobAction,auStack_48,0);
          if (cVar6 != '\0') {
            lVar13 = *(longlong *)(lVar10 + 0x38);
            if (lVar13 == 0) goto LAB_7ffe9a6a033e;
            uVar11 = 3;
            goto LAB_7ffe9a6a0264;
          }
        }
      }
    }
    lVar13 = *(longlong *)(thisObject + 0x58);
    if (lVar13 == 0) goto LAB_7ffe9a6a033e;
    if (*(longlong *)(lVar13 + 0x20) == 0) {
      uVar11 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
      FUN_7ffe9a9002e0(uVar11,0xa65226,0);
      *(undefined8 *)(lVar13 + 0x20) = uVar11;
      il2cpp_write_barrier_0();
    }
  }
  lVar4 = _DAT_7ffe9c913488;
  lVar13 = *(longlong *)(thisObject + 0x80);
  if (lVar13 != 0) {
    *(int *)(lVar13 + 0x1c) = *(int *)(lVar13 + 0x1c) + 1;
    lVar2 = *(longlong *)(lVar13 + 0x10);
    uVar1 = *(uint *)(lVar13 + 0x18);
    if (lVar2 != 0) {
      if (uVar1 < *(uint *)(lVar2 + 0x18)) {
        *(uint *)(lVar13 + 0x18) = uVar1 + 1;
        if (*(uint *)(lVar2 + 0x18) <= uVar1) {
          FUN_7ffe9996d790();
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        *(longlong *)(lVar2 + 0x20 + (longlong)(int)uVar1 * 8) = lVar10;
        il2cpp_write_barrier_0();
      }
      else {
        FUN_7ffe9afd58b0(lVar13,lVar10,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
      }
      return;
    }
  }
LAB_7ffe9a6a033e:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

