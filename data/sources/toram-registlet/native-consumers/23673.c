
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void CannonSpearAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  longlong lVar4;
  undefined1 uVar5;
  char cVar6;
  undefined4 uVar7;
  int iVar8;
  longlong *plVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  undefined *puVar13;
  int aiStackX_8 [2];
  undefined4 auStackX_10 [2];
  undefined8 in_stack_ffffffffffffff98;
  undefined4 uVar14;
  undefined8 in_stack_ffffffffffffffa0;
  undefined4 uVar15;
  ulonglong in_stack_ffffffffffffffa8;
  
  uVar14 = (undefined4)((ulonglong)in_stack_ffffffffffffff98 >> 0x20);
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffffa0 >> 0x20);
  if (DAT_7ffe9cadeceb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c958b28);
    FUN_7ffe9996d590(&DAT_7ffe9c958cc0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    DAT_7ffe9cadeceb = '\x01';
  }
  auStackX_10[0] = 0;
  uVar7 = FUN_7ffe9a4adee0(thisObject,playerAction,mobAction,0);
  *(undefined4 *)(thisObject + 0x30) = uVar7;
  if ((((playerAction != (undefined *)0x0) &&
       (plVar9 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
       plVar9 != (longlong *)0x0)) &&
      (lVar10 = (**(code **)(*plVar9 + 0x1a8))(plVar9,*(undefined8 *)(*plVar9 + 0x1b0)),
      mobAction != (undefined *)0x0)) &&
     (lVar11 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction), lVar10 != 0)) {
    uVar7 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,lVar10);
    uVar5 = FUN_7ffe9a4b33f0(thisObject,uVar7,mobAction,0);
    lVar10 = *(longlong *)(thisObject + 0x148);
    aiStackX_8[0] = 0;
    uVar12 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,mobAction);
    if (lVar10 == 0) goto LAB_7ffe9a6786ee;
    cVar6 = FUN_7ffe9adb0c10(lVar10,uVar12,aiStackX_8,_DAT_7ffe9c958cc0);
    if (cVar6 == '\0') {
      if (lVar11 == 0) goto LAB_7ffe9a6786ee;
      aiStackX_8[0] = FUN_7ffe99742ec0(0x11,_DAT_7ffe9c93ed20,lVar11);
      lVar10 = *(longlong *)(thisObject + 0x148);
      uVar12 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,mobAction);
      uVar7 = FUN_7ffe99742ec0(0x11,_DAT_7ffe9c93ed20,lVar11);
      if (lVar10 == 0) goto LAB_7ffe9a6786ee;
      FUN_7ffe9ada6d20(lVar10,uVar12,uVar7,_DAT_7ffe9c958b28);
    }
    uVar12 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
    FUN_7ffe9a6596c0(uVar12,0);
    uVar7 = (**(code **)(*(longlong *)thisObject + 0x198))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
    if ((*(longlong *)(thisObject + 0xb8) == 0) ||
       (lVar10 = FUN_7ffe9a4b1c10(thisObject,uVar12,playerAction,mobAction,CONCAT44(uVar14,uVar7),
                                  CONCAT44(uVar15,*(undefined4 *)
                                                   (*(longlong *)(thisObject + 0xb8) + 0x1c)),
                                  in_stack_ffffffffffffffa8 & 0xffffffff00000000,uVar5,0),
       lVar10 == 0)) goto LAB_7ffe9a6786ee;
    FUN_7ffe9a659510(lVar10,0x17,(float)aiStackX_8[0] / _DAT_7ffe9c049cfc);
    lVar11 = *(longlong *)(thisObject + 0x120);
    if (thisObject[0x130] == '\0') {
      if (lVar11 == 0) goto LAB_7ffe9a6786ee;
      if (*(uint *)(lVar11 + 0x18) < 2) goto LAB_7ffe9a6786f4;
    }
    else {
      if (lVar11 == 0) goto LAB_7ffe9a6786ee;
      if (*(int *)(lVar11 + 0x18) == 0) goto LAB_7ffe9a6786f4;
    }
    FUN_7ffe9a657c40(lVar10,0x12);
    FUN_7ffe9a657a50(lVar10,8);
    FUN_7ffe9a4b0320(thisObject,lVar10,2);
    uVar12 = func_0x7ffe99940040(_DAT_7ffe9c920098);
    FUN_7ffe9a8f6350(uVar12,mobAction,0);
    lVar10 = FUN_7ffe9a4b4370(thisObject,uVar12,lVar10,*(undefined4 *)(thisObject + 300),0);
    if (lVar10 != 0) {
      if (((*(int *)(lVar10 + 0x1c) != 0) && (*(int *)(lVar10 + 0x34) != 1)) &&
         (thisObject[0x130] != '\0')) {
        plVar9 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar9 == (longlong *)0x0) ||
           (puVar13 = (undefined *)
                      (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220)),
           puVar13 == (undefined *)0x0)) goto LAB_7ffe9a6786ee;
        puVar13 = GemCartBufferManager_GetGemCartBuffer(puVar13,0x70,(undefined *)0x0);
        if (puVar13 != (undefined *)0x0) {
          iVar8 = GemCartBufferBase_GetValue(puVar13,(undefined *)0x2,(undefined *)0x0);
          cVar6 = FUN_7ffe9a4b2fb0(thisObject,1,iVar8,playerAction,mobAction,auStackX_10,0);
          if (cVar6 != '\0') {
            if (*(longlong *)(lVar10 + 0x38) == 0) goto LAB_7ffe9a6786ee;
            FUN_7ffe9a8ffe30(*(longlong *)(lVar10 + 0x38),1);
          }
        }
      }
      lVar4 = _DAT_7ffe9c913488;
      lVar11 = *(longlong *)(thisObject + 0x80);
      if (lVar11 != 0) {
        *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
        lVar2 = *(longlong *)(lVar11 + 0x10);
        uVar1 = *(uint *)(lVar11 + 0x18);
        if (lVar2 != 0) {
          if (uVar1 < *(uint *)(lVar2 + 0x18)) {
            *(uint *)(lVar11 + 0x18) = uVar1 + 1;
            if (*(uint *)(lVar2 + 0x18) <= uVar1) {
LAB_7ffe9a6786f4:
              FUN_7ffe9996d790();
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            *(longlong *)(lVar2 + 0x20 + (longlong)(int)uVar1 * 8) = lVar10;
            il2cpp_write_barrier_0();
          }
          else {
            FUN_7ffe9afd58b0(lVar11,lVar10,
                             *(undefined8 *)
                              (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
          }
          return;
        }
      }
    }
  }
LAB_7ffe9a6786ee:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

