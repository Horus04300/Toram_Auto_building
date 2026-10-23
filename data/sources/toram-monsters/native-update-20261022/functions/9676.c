
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobPropertyMaster__ctor(undefined *self,undefined *br,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  undefined1 uVar3;
  short sVar4;
  undefined4 uVar5;
  longlong lVar6;
  
  if (DAT_7ffe9cadd784 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c917f28);
    DAT_7ffe9cadd784 = '\x01';
  }
  func_0x7ffe999c3920(self,0);
  lVar6 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,5);
  plVar1 = (longlong *)(self + 0x18);
  *plVar1 = lVar6;
  il2cpp_write_barrier_0();
  if (br != (undefined *)0x0) {
    uVar3 = (**(code **)(*(longlong *)br + 0x1d8))(br,*(undefined8 *)(*(longlong *)br + 0x1e0));
    self[0x10] = uVar3;
    sVar4 = (**(code **)(*(longlong *)br + 0x208))(br,*(undefined8 *)(*(longlong *)br + 0x210));
    *(int *)(self + 0x14) = (int)sVar4;
    lVar6 = *plVar1;
    uVar5 = (**(code **)(*(longlong *)br + 0x228))(br,*(undefined8 *)(*(longlong *)br + 0x230));
    if (lVar6 != 0) {
      if (*(int *)(lVar6 + 0x18) != 0) {
        *(undefined4 *)(lVar6 + 0x20) = uVar5;
        lVar6 = *plVar1;
        uVar5 = (**(code **)(*(longlong *)br + 0x228))(br,*(undefined8 *)(*(longlong *)br + 0x230));
        if (lVar6 == 0) goto LAB_7ffe9a37b0df;
        if (1 < *(uint *)(lVar6 + 0x18)) {
          *(undefined4 *)(lVar6 + 0x24) = uVar5;
          lVar6 = *plVar1;
          uVar5 = (**(code **)(*(longlong *)br + 0x228))
                            (br,*(undefined8 *)(*(longlong *)br + 0x230));
          if (lVar6 == 0) goto LAB_7ffe9a37b0df;
          if (2 < *(uint *)(lVar6 + 0x18)) {
            *(undefined4 *)(lVar6 + 0x28) = uVar5;
            lVar6 = *plVar1;
            uVar5 = (**(code **)(*(longlong *)br + 0x228))
                              (br,*(undefined8 *)(*(longlong *)br + 0x230));
            if (lVar6 == 0) goto LAB_7ffe9a37b0df;
            if (3 < *(uint *)(lVar6 + 0x18)) {
              *(undefined4 *)(lVar6 + 0x2c) = uVar5;
              lVar6 = *plVar1;
              uVar5 = (**(code **)(*(longlong *)br + 0x228))
                                (br,*(undefined8 *)(*(longlong *)br + 0x230));
              if (lVar6 == 0) goto LAB_7ffe9a37b0df;
              if (4 < *(uint *)(lVar6 + 0x18)) {
                *(undefined4 *)(lVar6 + 0x30) = uVar5;
                return;
              }
            }
          }
        }
      }
      FUN_7ffe9996d790();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
  }
LAB_7ffe9a37b0df:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

