
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
  
  if (DAT_7fff625e4edc == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6241fab8);
    DAT_7fff625e4edc = '\x01';
  }
  _loadFieldData_d__125_System_IDisposable_Dispose(self,(undefined *)0x0);
  lVar6 = func_0x7fff5f47c850(_DAT_7fff6241fab8,5);
  plVar1 = (longlong *)(self + 0x18);
  *plVar1 = lVar6;
  thunk_FUN_7fff5f491fd0();
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
        if (lVar6 == 0) goto LAB_7fff5fe85c8f;
        if (1 < *(uint *)(lVar6 + 0x18)) {
          *(undefined4 *)(lVar6 + 0x24) = uVar5;
          lVar6 = *plVar1;
          uVar5 = (**(code **)(*(longlong *)br + 0x228))
                            (br,*(undefined8 *)(*(longlong *)br + 0x230));
          if (lVar6 == 0) goto LAB_7fff5fe85c8f;
          if (2 < *(uint *)(lVar6 + 0x18)) {
            *(undefined4 *)(lVar6 + 0x28) = uVar5;
            lVar6 = *plVar1;
            uVar5 = (**(code **)(*(longlong *)br + 0x228))
                              (br,*(undefined8 *)(*(longlong *)br + 0x230));
            if (lVar6 == 0) goto LAB_7fff5fe85c8f;
            if (3 < *(uint *)(lVar6 + 0x18)) {
              *(undefined4 *)(lVar6 + 0x2c) = uVar5;
              lVar6 = *plVar1;
              uVar5 = (**(code **)(*(longlong *)br + 0x228))
                                (br,*(undefined8 *)(*(longlong *)br + 0x230));
              if (lVar6 == 0) goto LAB_7fff5fe85c8f;
              if (4 < *(uint *)(lVar6 + 0x18)) {
                *(undefined4 *)(lVar6 + 0x30) = uVar5;
                return;
              }
            }
          }
        }
      }
      FUN_7fff5f47d650();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
  }
LAB_7fff5fe85c8f:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

