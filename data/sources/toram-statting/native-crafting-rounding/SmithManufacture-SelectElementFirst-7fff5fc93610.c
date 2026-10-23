
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithManufacture_SelectElementFirst(undefined *self,int index,undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  longlong lVar3;
  longlong *methodInfo_00;
  longlong lVar4;
  undefined8 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 auStackX_8 [2];
  
  if (DAT_7fff625e4291 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62473318);
    FUN_7fff5f47d450(&DAT_7fff6246c078);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(0x7fff62425768);
    FUN_7fff5f47d450(&DAT_7fff62450e50);
    FUN_7fff5f47d450(&DAT_7fff623fd630);
    FUN_7fff5f47d450(&DAT_7fff62425830);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff624445f8);
    DAT_7fff625e4291 = '\x01';
  }
  iVar7 = 0;
  lVar3 = *(longlong *)(self + 0x1b8);
  while (lVar3 != 0) {
    if (*(int *)(lVar3 + 0x18) <= iVar7) {
      lVar3 = *(longlong *)(self + 0x150);
      uVar6 = 0;
      uVar1 = *(undefined4 *)(self + 0x160);
      *(int *)(self + 0x168) = index;
      goto joined_r0x7fff5fc93742;
    }
    if (((*(longlong *)(self + 0x1b8) == 0) ||
        (lVar3 = FUN_7fff60a94f50(*(longlong *)(self + 0x1b8),iVar7,_DAT_7fff62425830), lVar3 == 0))
       || (lVar3 = FUN_7fff606a6750(lVar3,_DAT_7fff6246c078), lVar3 == 0)) break;
    FUN_7fff5fc9c590(lVar3,index == iVar7,0);
    iVar7 = iVar7 + 1;
    lVar3 = *(longlong *)(self + 0x1b8);
  }
LAB_7fff5fc938f1:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
joined_r0x7fff5fc93742:
  if ((((lVar3 == 0) || (lVar3 = FUN_7fff60a94f50(lVar3,uVar1,_DAT_7fff623fd630), lVar3 == 0)) ||
      (lVar3 = FUN_7fff6083faa0(lVar3,*(undefined4 *)(self + 0x164),_DAT_7fff62473318), lVar3 == 0))
     || ((lVar3 = FUN_7fff60a94f50(lVar3,*(undefined4 *)(self + 0x168),_DAT_7fff62450e50),
         lVar3 == 0 || (*(longlong *)(lVar3 + 0x28) == 0)))) goto LAB_7fff5fc938f1;
  if (*(int *)(*(longlong *)(lVar3 + 0x28) + 0x18) <= (int)uVar6) {
    return;
  }
  methodInfo_00 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
  if (((*(longlong *)(self + 0x150) == 0) ||
      (lVar3 = FUN_7fff60a94f50(*(longlong *)(self + 0x150),*(undefined4 *)(self + 0x160),
                                _DAT_7fff623fd630), lVar3 == 0)) ||
     ((lVar3 = FUN_7fff6083faa0(lVar3,*(undefined4 *)(self + 0x164),_DAT_7fff62473318), lVar3 == 0
      || ((lVar3 = FUN_7fff60a94f50(lVar3,*(undefined4 *)(self + 0x168),_DAT_7fff62450e50),
          lVar3 == 0 || (lVar3 = *(longlong *)(lVar3 + 0x28), lVar3 == 0))))))
  goto LAB_7fff5fc9390d;
  if (*(uint *)(lVar3 + 0x18) <= uVar6) {
LAB_7fff5fc93907:
    FUN_7fff5f47d650();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  lVar3 = *(longlong *)(lVar3 + 0x20 + (longlong)(int)uVar6 * 8);
  if (lVar3 == 0) {
LAB_7fff5fc9390d:
    FUN_7fff5f47d660();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  auStackX_8[0] = *(undefined4 *)(lVar3 + 0x14);
  lVar3 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,auStackX_8);
  if (methodInfo_00 == (longlong *)0x0) goto LAB_7fff5fc9390d;
  if ((lVar3 != 0) &&
     (lVar4 = func_0x7fff5f47c7e0(lVar3,*(undefined8 *)(*methodInfo_00 + 0x40)), lVar4 == 0)) {
    uVar5 = func_0x7fff5f47d0b0();
    FUN_7fff5f47d620(uVar5,0);
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if ((int)methodInfo_00[3] == 0) goto LAB_7fff5fc93907;
  methodInfo_00[4] = lVar3;
  thunk_FUN_7fff5f491fd0();
  SmithManufacture_Update(_DAT_7fff624445f8,(undefined *)methodInfo_00);
  lVar3 = *(longlong *)(self + 0x150);
  uVar6 = uVar6 + 1;
  uVar1 = *(undefined4 *)(self + 0x160);
  goto joined_r0x7fff5fc93742;
}

