
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_CalcBaseGuardPower(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  byte bVar3;
  int iVar4;
  longlong lVar5;
  undefined *armorItem;
  uint uVar6;
  
  if (DAT_7ffe9cadde1f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cadde1f = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  uVar6 = 0;
  if (plVar1 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if (lVar5 != 0) {
      lVar5 = FUN_7ffe99c08fe0(lVar5,0);
      if (lVar5 != 0) {
        plVar1 = *(longlong **)(self + 0x10);
        if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a482469;
        lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
        if (lVar5 == 0) goto LAB_7ffe9a482469;
        lVar5 = FUN_7ffe99c08fe0(lVar5,0);
        if (lVar5 == 0) goto LAB_7ffe9a482469;
        uVar6 = 0;
        if (*(int *)(lVar5 + 0x38) == 0x11) {
          uVar6 = 0x1d4c;
        }
      }
      plVar1 = *(longlong **)(self + 0x10);
      if (plVar1 != (longlong *)0x0) {
        lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
        if (lVar5 != 0) {
          lVar5 = FUN_7ffe99c090e0(lVar5,0);
          if (lVar5 != 0) {
            plVar1 = *(longlong **)(self + 0x10);
            if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a482469;
            lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
            if (lVar5 == 0) goto LAB_7ffe9a482469;
            lVar5 = FUN_7ffe99c090e0(lVar5,0);
            if (lVar5 == 0) goto LAB_7ffe9a482469;
            if (*(int *)(lVar5 + 0x38) == 0xb) {
              uVar6 = uVar6 + 5000;
            }
          }
          plVar1 = *(longlong **)(self + 0x10);
          if (plVar1 != (longlong *)0x0) {
            lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
            if (lVar5 != 0) {
              lVar5 = FUN_7ffe99c090e0(lVar5,0);
              if (lVar5 != 0) {
                plVar1 = *(longlong **)(self + 0x10);
                if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a482469;
                lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
                if (lVar5 == 0) goto LAB_7ffe9a482469;
                lVar5 = FUN_7ffe99c090e0(lVar5,0);
                if (lVar5 == 0) goto LAB_7ffe9a482469;
                if (*(int *)(lVar5 + 0x38) == 9) {
                  uVar6 = uVar6 + 0x9c4;
                }
              }
              plVar1 = *(longlong **)(self + 0x10);
              if (plVar1 != (longlong *)0x0) {
                lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
                if (lVar5 != 0) {
                  armorItem = (undefined *)FUN_7ffe99c08d90(lVar5,0);
                  bVar3 = ItemDBData_CheckArmorAbility(armorItem,(undefined *)0x2,(undefined *)0x0);
                  if (bVar3 != 0) {
                    uVar6 = uVar6 + 5000;
                  }
                  if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                    func_0x7ffe9996d830();
                  }
                  if (9999 < uVar6) {
                    uVar6 = 10000;
                  }
                  return uVar6;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a482469:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

