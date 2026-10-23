
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * UIEquipCristaPanel_GetAllPowerUpCristaList(undefined *self,undefined *methodInfo)

{
  uint uVar1;
  code *pcVar2;
  longlong lVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined *puVar8;
  
  if (DAT_7ffe9cadb47a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9040d8);
    FUN_7ffe9996d590(&DAT_7ffe9c9041a8);
    FUN_7ffe9996d590(&DAT_7ffe9c904008);
    FUN_7ffe9996d590(&DAT_7ffe9c8f56c0);
    DAT_7ffe9cadb47a = '\x01';
  }
  lVar3 = func_0x7ffe99940040(_DAT_7ffe9c8f56c0);
  FUN_7ffe9af8a010(lVar3,_DAT_7ffe9c904008);
  lVar4 = _DAT_7ffe9c9040d8;
  if (lVar3 != 0) {
    *(int *)(lVar3 + 0x1c) = *(int *)(lVar3 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar3 + 0x10);
    uVar1 = *(uint *)(lVar3 + 0x18);
    if (lVar7 == 0) goto LAB_7ffe99dd1e0c;
    if (uVar1 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar3 + 0x18) = uVar1 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar1) goto LAB_7ffe99dd1e12;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar1 * 4) = 0x24;
    }
    else {
      FUN_7ffe9afc6d40(lVar3,0x24,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar7 = _DAT_7ffe9c9040d8;
    *(int *)(lVar3 + 0x1c) = *(int *)(lVar3 + 0x1c) + 1;
    lVar4 = *(longlong *)(lVar3 + 0x10);
    uVar1 = *(uint *)(lVar3 + 0x18);
    if (lVar4 == 0) goto LAB_7ffe99dd1e0c;
    if (uVar1 < *(uint *)(lVar4 + 0x18)) {
      *(uint *)(lVar3 + 0x18) = uVar1 + 1;
      if (*(uint *)(lVar4 + 0x18) <= uVar1) goto LAB_7ffe99dd1e12;
      *(undefined4 *)(lVar4 + 0x20 + (longlong)(int)uVar1 * 4) = 0x3d;
    }
    else {
      FUN_7ffe9afc6d40(lVar3,0x3d,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x70));
    }
    lVar7 = _DAT_7ffe9c9040d8;
    *(int *)(lVar3 + 0x1c) = *(int *)(lVar3 + 0x1c) + 1;
    lVar4 = *(longlong *)(lVar3 + 0x10);
    uVar1 = *(uint *)(lVar3 + 0x18);
    if (lVar4 == 0) goto LAB_7ffe99dd1e0c;
    if (uVar1 < *(uint *)(lVar4 + 0x18)) {
      *(uint *)(lVar3 + 0x18) = uVar1 + 1;
      if (*(uint *)(lVar4 + 0x18) <= uVar1) goto LAB_7ffe99dd1e12;
      *(undefined4 *)(lVar4 + 0x20 + (longlong)(int)uVar1 * 4) = 0x3e;
    }
    else {
      FUN_7ffe9afc6d40(lVar3,0x3e,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x70));
    }
    lVar7 = _DAT_7ffe9c9040d8;
    *(int *)(lVar3 + 0x1c) = *(int *)(lVar3 + 0x1c) + 1;
    lVar4 = *(longlong *)(lVar3 + 0x10);
    uVar1 = *(uint *)(lVar3 + 0x18);
    if (lVar4 == 0) goto LAB_7ffe99dd1e0c;
    if (uVar1 < *(uint *)(lVar4 + 0x18)) {
      *(uint *)(lVar3 + 0x18) = uVar1 + 1;
      if (*(uint *)(lVar4 + 0x18) <= uVar1) goto LAB_7ffe99dd1e12;
      *(undefined4 *)(lVar4 + 0x20 + (longlong)(int)uVar1 * 4) = 0x3f;
    }
    else {
      FUN_7ffe9afc6d40(lVar3,0x3f,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x70));
    }
    lVar7 = _DAT_7ffe9c9040d8;
    *(int *)(lVar3 + 0x1c) = *(int *)(lVar3 + 0x1c) + 1;
    lVar4 = *(longlong *)(lVar3 + 0x10);
    uVar1 = *(uint *)(lVar3 + 0x18);
    if (lVar4 == 0) goto LAB_7ffe99dd1e0c;
    if (uVar1 < *(uint *)(lVar4 + 0x18)) {
      *(uint *)(lVar3 + 0x18) = uVar1 + 1;
      if (*(uint *)(lVar4 + 0x18) <= uVar1) goto LAB_7ffe99dd1e12;
      *(undefined4 *)(lVar4 + 0x20 + (longlong)(int)uVar1 * 4) = 0x40;
    }
    else {
      FUN_7ffe9afc6d40(lVar3,0x40,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x70));
    }
    lVar7 = _DAT_7ffe9c9040d8;
    *(int *)(lVar3 + 0x1c) = *(int *)(lVar3 + 0x1c) + 1;
    lVar4 = *(longlong *)(lVar3 + 0x10);
    uVar1 = *(uint *)(lVar3 + 0x18);
    if (lVar4 != 0) {
      if (uVar1 < *(uint *)(lVar4 + 0x18)) {
        *(uint *)(lVar3 + 0x18) = uVar1 + 1;
        if (*(uint *)(lVar4 + 0x18) <= uVar1) {
LAB_7ffe99dd1e12:
          FUN_7ffe9996d790();
          pcVar2 = (code *)swi(3);
          puVar8 = (undefined *)(*pcVar2)();
          return puVar8;
        }
        *(undefined4 *)(lVar4 + 0x20 + (longlong)(int)uVar1 * 4) = 0x41;
      }
      else {
        FUN_7ffe9afc6d40(lVar3,0x41,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x70));
      }
      if (*(longlong *)(self + 0x158) != 0) {
        lVar4 = FUN_7ffe9a47fce0(*(longlong *)(self + 0x158),0);
        uVar5 = FUN_7ffe9af89d20(lVar3,_DAT_7ffe9c9041a8);
        if (lVar4 != 0) {
          if (DAT_7ffe9cade557 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c8fc9f8,uVar5,0);
            FUN_7ffe9996d590(&DAT_7ffe9c9232f0);
            FUN_7ffe9996d590(&DAT_7ffe9c923480);
            FUN_7ffe9996d590(&DAT_7ffe9c9281d8);
            FUN_7ffe9996d590(&DAT_7ffe9c93c8a8);
            FUN_7ffe9996d590(&DAT_7ffe9c951d60);
            FUN_7ffe9996d590(&DAT_7ffe9c963d10);
            DAT_7ffe9cade557 = '\x01';
          }
          lVar3 = func_0x7ffe99940040(_DAT_7ffe9c963d10);
          func_0x7ffe999c3920(lVar3,0);
          uVar5 = FUN_7ffe9ab7b790(uVar5,_DAT_7ffe9c8fc9f8);
          uVar5 = FUN_7ffe9ab926e0(uVar5,_DAT_7ffe9c9232f0);
          if (lVar3 == 0) {
            FUN_7ffe9996d7a0();
            pcVar2 = (code *)swi(3);
            puVar8 = (undefined *)(*pcVar2)();
            return puVar8;
          }
          *(undefined8 *)(lVar3 + 0x10) = uVar5;
          il2cpp_write_barrier_0();
          uVar5 = *(undefined8 *)(lVar4 + 0x18);
          uVar6 = func_0x7ffe99940040(_DAT_7ffe9c93c8a8);
          FUN_7ffe9af13420(uVar6,lVar3,_DAT_7ffe9c951d60,0);
          lVar3 = FUN_7ffe9ab93080(uVar5,uVar6,_DAT_7ffe9c9281d8);
          lVar4 = _DAT_7ffe9c923480;
          if (*(longlong *)(_DAT_7ffe9c923480 + 0x38) == 0) {
            FUN_7ffe998cedc0(_DAT_7ffe9c923480);
          }
          if (lVar3 != 0) {
            lVar7 = *(longlong *)(*(longlong *)(lVar4 + 0x38) + 8);
            if ((*(byte *)(lVar7 + 0x135) & 1) == 0) {
              lVar7 = FUN_7ffe998ced40(lVar7);
            }
            puVar8 = (undefined *)func_0x7ffe99940040(lVar7);
            FUN_7ffe9afe3710(puVar8,lVar3,*(undefined8 *)(*(longlong *)(lVar4 + 0x38) + 0x10));
            return puVar8;
          }
          uVar5 = func_0x7ffe9996d5b0(0x7ffe9c94f360);
          uVar5 = FUN_7ffe9b661bf0(uVar5,0);
          FUN_7ffe9996d760(uVar5,lVar4);
          pcVar2 = (code *)swi(3);
          puVar8 = (undefined *)(*pcVar2)();
          return puVar8;
        }
      }
    }
  }
LAB_7ffe99dd1e0c:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  puVar8 = (undefined *)(*pcVar2)();
  return puVar8;
}

