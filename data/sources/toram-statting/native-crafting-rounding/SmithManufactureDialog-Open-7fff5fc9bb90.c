
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithManufactureDialog_Open(undefined *self,int createId,undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 uVar9;
  uint uVar10;
  uint uVar11;
  undefined4 uVar12;
  
  if (DAT_7fff625e42d3 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b618);
    FUN_7fff5f47d450(&DAT_7fff62411ec0);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    DAT_7fff625e42d3 = '\x01';
  }
  uVar9 = *(undefined8 *)(self + 0x30);
  if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  cVar3 = FUN_7fff618ab2e0(uVar9,0,0);
  if (cVar3 != '\0') {
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5fc9bea1;
    lVar4 = FUN_7fff618a1ae0(*(longlong *)(self + 0x30),0);
    if (lVar4 == 0) goto LAB_7fff5fc9bea1;
    FUN_7fff618a4510(lVar4,0,0);
  }
  uVar9 = *(undefined8 *)(self + 0x48);
  if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  cVar3 = FUN_7fff618ab2e0(uVar9,0,0);
  if (cVar3 != '\0') {
    if (*(longlong *)(self + 0x48) == 0) goto LAB_7fff5fc9bea1;
    lVar4 = FUN_7fff618a1ae0(*(longlong *)(self + 0x48),0);
    if (lVar4 == 0) goto LAB_7fff5fc9bea1;
    FUN_7fff618a4510(lVar4,0,0);
  }
  uVar9 = *(undefined8 *)(self + 0x38);
  if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  cVar3 = FUN_7fff618ab2e0(uVar9,0,0);
  if (cVar3 != '\0') {
    if (*(longlong *)(self + 0x38) == 0) goto LAB_7fff5fc9bea1;
    lVar4 = FUN_7fff618a1ae0(*(longlong *)(self + 0x38),0);
    if (lVar4 == 0) goto LAB_7fff5fc9bea1;
    FUN_7fff618a4510(lVar4,1,0);
    if (*(longlong *)(self + 0x38) == 0) goto LAB_7fff5fc9bea1;
    FUN_7fff5fc309f0(*(longlong *)(self + 0x38),1,0);
    if (*(longlong *)(self + 0x38) == 0) goto LAB_7fff5fc9bea1;
    lVar4 = FUN_7fff60678610(*(longlong *)(self + 0x38),_DAT_7fff6244b618);
    plVar5 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
    plVar7 = *(longlong **)(self + 0x68);
    if (plVar7 == (longlong *)0x0) goto LAB_7fff5fc9bea1;
    lVar6 = func_0x7fff5f47d0d0(*(undefined8 *)
                                 (*plVar7 +
                                 ((ulonglong)*(ushort *)(_DAT_7fff62411ec0 + 0x50) + 0x14) * 0x10));
    plVar7 = (longlong *)(**(code **)(lVar6 + 8))(plVar7,createId,lVar6);
    if (plVar7 == (longlong *)0x0) goto LAB_7fff5fc9bea1;
    lVar6 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
    if (plVar5 == (longlong *)0x0) goto LAB_7fff5fc9bea1;
    if (lVar6 != 0) {
      lVar8 = func_0x7fff5f47c7e0(lVar6,*(undefined8 *)(*plVar5 + 0x40));
      if (lVar8 == 0) {
        uVar9 = func_0x7fff5f47d0b0();
        FUN_7fff5f47d620(uVar9,0);
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
    }
    if ((int)plVar5[3] == 0) {
LAB_7fff5fc9beb7:
      FUN_7fff5f47d650();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    plVar5[4] = lVar6;
    thunk_FUN_7fff5f491fd0();
    if (lVar4 == 0) goto LAB_7fff5fc9bea1;
    FUN_7fff5f55c500(lVar4,plVar5,0);
    if (*(longlong *)(self + 0x38) == 0) goto LAB_7fff5fc9bea1;
    func_0x7fff5fc30c60(*(longlong *)(self + 0x38),createId,0);
  }
  lVar4 = *(longlong *)(self + 0x20);
  uVar10 = 0;
  uVar11 = 0;
  if (lVar4 != 0) {
    for (; (int)uVar11 < *(int *)(lVar4 + 0x18); uVar11 = uVar11 + 1) {
      if (*(uint *)(lVar4 + 0x18) <= uVar11) goto LAB_7fff5fc9beb7;
      lVar6 = *(longlong *)(lVar4 + 0x20 + (longlong)(int)uVar11 * 8);
      if (lVar6 == 0) goto LAB_7fff5fc9bea1;
      FUN_7fff618a4510(lVar6,0,0);
    }
    lVar4 = *(longlong *)(self + 0x28);
    if (lVar4 != 0) {
      for (; (int)uVar10 < *(int *)(lVar4 + 0x18); uVar10 = uVar10 + 1) {
        if (*(uint *)(lVar4 + 0x18) <= uVar10) goto LAB_7fff5fc9beb7;
        lVar6 = *(longlong *)(lVar4 + 0x20 + (longlong)(int)uVar10 * 8);
        if (lVar6 == 0) goto LAB_7fff5fc9bea1;
        FUN_7fff618a4510(lVar6,1,0);
      }
      lVar4 = *(longlong *)(self + 0x50);
      if (lVar4 != 0) {
        FUN_7fff5f51e8c0(lVar4,0);
        lVar6 = *(longlong *)(lVar4 + 0x40);
        uVar12 = *(undefined4 *)(lVar4 + 0x28);
        uVar1 = *(undefined4 *)(lVar4 + 0x2c);
        if (lVar6 != 0) {
          *(ulonglong *)(lVar6 + 0x44) =
               CONCAT44(*(float *)(lVar4 + 0x24) -
                        (float)((ulonglong)*(undefined8 *)(lVar6 + 0x50) >> 0x20),
                        *(float *)(lVar4 + 0x20) - (float)*(undefined8 *)(lVar6 + 0x50));
          *(float *)(lVar6 + 0x4c) = 0.0 - *(float *)(lVar6 + 0x58);
          *(undefined4 *)(lVar6 + 0x68) = uVar12;
          *(undefined4 *)(lVar6 + 0x70) = uVar1;
          uVar12 = FUN_7fff618b0ec0(0);
          *(undefined4 *)(lVar6 + 0x74) = uVar12;
          *(undefined8 *)(lVar6 + 0x5c) = *(undefined8 *)(lVar6 + 0x50);
          *(undefined4 *)(lVar6 + 100) = *(undefined4 *)(lVar6 + 0x58);
          *(undefined4 *)(lVar6 + 0x6c) = 0;
          *(undefined1 *)(lVar6 + 0x41) = 1;
          if (*(int *)(lVar4 + 0x34) == 1) {
            FUN_7fff5f51ea50(lVar4,0);
          }
          return;
        }
        FUN_7fff5f47d660();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
    }
  }
LAB_7fff5fc9bea1:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

