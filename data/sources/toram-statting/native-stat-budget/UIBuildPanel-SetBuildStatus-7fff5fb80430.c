
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIBuildPanel_SetBuildStatus(undefined *self,undefined *primaryStatus,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  uint uVar9;
  undefined *text;
  int iVar10;
  int iVar11;
  int aiStackX_18 [2];
  int aiStackX_20 [2];
  
  if (DAT_7fff625e3c1c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62440008);
    FUN_7fff5f47d450(&DAT_7fff6244ae88);
    FUN_7fff5f47d450(&DAT_7fff624211b0);
    FUN_7fff5f47d450(&DAT_7fff62473d98);
    DAT_7fff625e3c1c = '\x01';
  }
  uVar9 = 0;
  *(undefined4 *)(self + 0xe0) = 0;
  do {
    lVar4 = *(longlong *)(self + 0x40);
    if (lVar4 == 0) goto LAB_7fff5fb806f8;
    if (*(uint *)(lVar4 + 0x18) <= uVar9) goto LAB_7fff5fb806fe;
    lVar3 = (longlong)(int)uVar9;
    uVar9 = uVar9 + 1;
    *(undefined4 *)(lVar4 + 0x20 + lVar3 * 4) = 0;
  } while ((int)uVar9 < 6);
  if (primaryStatus == (undefined *)0x0) goto LAB_7fff5fb806f8;
  iVar10 = *(int *)(primaryStatus + 0x14);
  *(int *)(self + 0xe0) = *(int *)(self + 0xe0) + iVar10 + -1;
  lVar4 = *(longlong *)(self + 0x30);
  if (lVar4 == 0) goto LAB_7fff5fb806f8;
  if (*(int *)(lVar4 + 0x18) == 0) goto LAB_7fff5fb806fe;
  if (*(undefined **)(lVar4 + 0x20) == (undefined *)0x0) goto LAB_7fff5fb806f8;
  UIStatusBar_SetParameter(*(undefined **)(lVar4 + 0x20),iVar10,(undefined *)0x0);
  iVar10 = *(int *)(primaryStatus + 0x18);
  *(int *)(self + 0xe0) = *(int *)(self + 0xe0) + iVar10 + -1;
  lVar4 = *(longlong *)(self + 0x30);
  if (lVar4 == 0) goto LAB_7fff5fb806f8;
  if (*(uint *)(lVar4 + 0x18) < 2) goto LAB_7fff5fb806fe;
  if (*(undefined **)(lVar4 + 0x28) == (undefined *)0x0) goto LAB_7fff5fb806f8;
  UIStatusBar_SetParameter(*(undefined **)(lVar4 + 0x28),iVar10,(undefined *)0x0);
  iVar10 = *(int *)(primaryStatus + 0x1c);
  *(int *)(self + 0xe0) = *(int *)(self + 0xe0) + iVar10 + -1;
  lVar4 = *(longlong *)(self + 0x30);
  if (lVar4 == 0) goto LAB_7fff5fb806f8;
  if (*(uint *)(lVar4 + 0x18) < 3) goto LAB_7fff5fb806fe;
  if (*(undefined **)(lVar4 + 0x30) == (undefined *)0x0) goto LAB_7fff5fb806f8;
  UIStatusBar_SetParameter(*(undefined **)(lVar4 + 0x30),iVar10,(undefined *)0x0);
  iVar10 = *(int *)(primaryStatus + 0x20);
  *(int *)(self + 0xe0) = *(int *)(self + 0xe0) + iVar10 + -1;
  lVar4 = *(longlong *)(self + 0x30);
  if (lVar4 == 0) goto LAB_7fff5fb806f8;
  if (*(uint *)(lVar4 + 0x18) < 4) goto LAB_7fff5fb806fe;
  if (*(undefined **)(lVar4 + 0x38) == (undefined *)0x0) goto LAB_7fff5fb806f8;
  UIStatusBar_SetParameter(*(undefined **)(lVar4 + 0x38),iVar10,(undefined *)0x0);
  iVar10 = *(int *)(primaryStatus + 0x24);
  *(int *)(self + 0xe0) = *(int *)(self + 0xe0) + iVar10 + -1;
  lVar4 = *(longlong *)(self + 0x30);
  if (lVar4 == 0) goto LAB_7fff5fb806f8;
  if (*(uint *)(lVar4 + 0x18) < 5) goto LAB_7fff5fb806fe;
  if (*(undefined **)(lVar4 + 0x40) == (undefined *)0x0) goto LAB_7fff5fb806f8;
  UIStatusBar_SetParameter(*(undefined **)(lVar4 + 0x40),iVar10,(undefined *)0x0);
  iVar10 = *(int *)(primaryStatus + 0x40);
  if (iVar10 == 1) {
    iVar10 = *(int *)(primaryStatus + 0x28);
    text = _DAT_7fff62473d98;
LAB_7fff5fb806d9:
    UIBuildPanel_SetStatusBar(self,text,iVar10,(undefined *)0x0);
  }
  else {
    if (iVar10 == 2) {
      iVar10 = *(int *)(primaryStatus + 0x2c);
      text = _DAT_7fff62440008;
      goto LAB_7fff5fb806d9;
    }
    if (iVar10 != 3) {
      if (iVar10 == 4) {
        iVar10 = *(int *)(primaryStatus + 0x30);
        text = _DAT_7fff6244ae88;
      }
      else {
        if (iVar10 != 8) goto LAB_7fff5fb80619;
        iVar10 = *(int *)(primaryStatus + 0x34);
        text = _DAT_7fff624211b0;
      }
      goto LAB_7fff5fb806d9;
    }
LAB_7fff5fb80619:
    if ((*(undefined **)(self + 0xd0) == (undefined *)0x0) ||
       (plVar5 = (longlong *)
                 PlayerDataManager_get_PlayerStatus(*(undefined **)(self + 0xd0),(undefined *)0x0),
       plVar5 == (longlong *)0x0)) {
LAB_7fff5fb806f8:
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    lVar4 = (**(code **)(*plVar5 + 0x188))(plVar5,*(undefined8 *)(*plVar5 + 400));
    if (lVar4 == 0) goto LAB_7fff5fb806f8;
    iVar10 = *(int *)(lVar4 + 0x10);
    if (*(longlong *)(self + 0x58) == 0) goto LAB_7fff5fb806f8;
    FUN_7fff618a4510(*(longlong *)(self + 0x58),0x27 < iVar10,0);
    if (*(longlong *)(self + 0x60) == 0) goto LAB_7fff5fb806f8;
    FUN_7fff618a4510(*(longlong *)(self + 0x60),iVar10 < 0x28,0);
    lVar4 = *(longlong *)(self + 0x30);
    if (lVar4 == 0) goto LAB_7fff5fb806f8;
    if (*(uint *)(lVar4 + 0x18) < 6) {
LAB_7fff5fb806fe:
      FUN_7fff5f47d650();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if ((*(longlong *)(lVar4 + 0x48) == 0) || (lVar4 = FUN_7fff618a1ae0(), lVar4 == 0))
    goto LAB_7fff5fb806f8;
    FUN_7fff618a4510(lVar4,0,0);
  }
  if (DAT_7fff625e3c20 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62478a78);
    FUN_7fff5f47d450(&DAT_7fff623fb7c0);
    DAT_7fff625e3c20 = '\x01';
  }
  iVar10 = 0;
  if ((*(undefined **)(self + 0xd0) == (undefined *)0x0) ||
     (plVar5 = (longlong *)
               PlayerDataManager_get_PlayerStatus(*(undefined **)(self + 0xd0),(undefined *)0x0),
     plVar5 == (longlong *)0x0)) goto LAB_7fff5fb80c8a;
  lVar3 = (**(code **)(*plVar5 + 0x188))(plVar5,*(undefined8 *)(*plVar5 + 400));
  lVar4 = *(longlong *)(self + 0x40);
  uVar9 = 0;
  do {
    if (lVar4 == 0) goto LAB_7fff5fb80c8a;
    if (*(uint *)(lVar4 + 0x18) <= uVar9) {
      FUN_7fff5f47d650();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    lVar6 = (longlong)(int)uVar9;
    uVar9 = uVar9 + 1;
    iVar10 = iVar10 + *(int *)(lVar4 + 0x20 + lVar6 * 4);
  } while ((int)uVar9 < 6);
  if (lVar3 == 0) goto LAB_7fff5fb80c8a;
  if (self[0x158] == '\0') {
    iVar11 = *(int *)(self + 0xe0) + *(int *)(lVar3 + 0x38);
    if (*(int *)(_DAT_7fff62478a78 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff62478a78);
    }
    if (iVar11 <= *(int *)(*(longlong *)(_DAT_7fff62478a78 + 0xb8) + 8)) goto LAB_7fff5fb80c81;
    iVar2 = UIBuildPanel_GetOverBuildPoint(self,(undefined *)0x0);
    if (*(int *)(_DAT_7fff62478a78 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    iVar2 = (iVar11 - *(int *)(*(longlong *)(_DAT_7fff62478a78 + 0xb8) + 8)) - iVar2;
    if (iVar2 != 0) {
      lVar4 = *(longlong *)(self + 0x78);
      aiStackX_18[0] = (*(int *)(lVar3 + 0x38) - iVar2) - iVar10;
      uVar7 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_18);
      aiStackX_20[0] = iVar2;
      uVar8 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_20);
      uVar7 = FUN_7fff60e74db0(_DAT_7fff623fb7c0,uVar7,uVar8,0);
      if (lVar4 == 0) {
        FUN_7fff5f47d660();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      goto LAB_7fff5fb80c65;
    }
    lVar4 = *(longlong *)(self + 0x78);
  }
  else {
LAB_7fff5fb80c81:
    lVar4 = *(longlong *)(self + 0x78);
  }
  uVar7 = FUN_7fff6100e780(&stack0x00000008,0);
  if (lVar4 != 0) {
LAB_7fff5fb80c65:
    FUN_7fff5ff0eed0(lVar4,uVar7,0);
    return;
  }
LAB_7fff5fb80c8a:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

