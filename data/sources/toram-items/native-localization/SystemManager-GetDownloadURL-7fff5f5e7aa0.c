
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * SystemManager_GetDownloadURL(undefined *self,undefined *methodInfo)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  uint uVar4;
  longlong lVar5;
  undefined *puVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  
  if (DAT_7fff625e18b6 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62459938);
    FUN_7fff5f47d450(&DAT_7fff62462c28);
    FUN_7fff5f47d450(&DAT_7fff624653f8);
    FUN_7fff5f47d450(&DAT_7fff624428e8);
    FUN_7fff5f47d450(&DAT_7fff62478020);
    FUN_7fff5f47d450(&DAT_7fff62477f50);
    FUN_7fff5f47d450(&DAT_7fff62446508);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    FUN_7fff5f47d450(&DAT_7fff62477e80);
    DAT_7fff625e18b6 = '\x01';
  }
  iVar1 = *(int *)(self + 0x28);
  if (iVar1 == 1) {
LAB_7fff5f5e7c48:
    lVar5 = *(longlong *)(self + 0x20);
    if (lVar5 == 0) goto LAB_7fff5f5e7da7;
    if (*(uint *)(lVar5 + 0x18) < 2) {
LAB_7fff5f5e7dad:
      FUN_7fff5f47d650();
      pcVar3 = (code *)swi(3);
      puVar6 = (undefined *)(*pcVar3)();
      return puVar6;
    }
    uVar9 = *(undefined8 *)(lVar5 + 0x28);
    uVar8 = _DAT_7fff624653f8;
  }
  else if (iVar1 == 2) {
LAB_7fff5f5e7c24:
    lVar5 = *(longlong *)(self + 0x20);
    if (lVar5 == 0) goto LAB_7fff5f5e7da7;
    if (*(uint *)(lVar5 + 0x18) < 3) goto LAB_7fff5f5e7dad;
    uVar9 = *(undefined8 *)(lVar5 + 0x30);
    uVar8 = _DAT_7fff62462c28;
  }
  else if (iVar1 == 3) {
LAB_7fff5f5e7bf6:
    lVar5 = *(longlong *)(self + 0x20);
    if (lVar5 == 0) goto LAB_7fff5f5e7da7;
    if (*(uint *)(lVar5 + 0x18) < 4) goto LAB_7fff5f5e7dad;
    uVar9 = *(undefined8 *)(lVar5 + 0x38);
    uVar8 = _DAT_7fff623f7f60;
    if (self[0x34] != '\0') {
      uVar9 = *(undefined8 *)(self + 0x38);
    }
  }
  else {
    iVar2 = *(int *)(self + 0x2c);
    if (iVar2 == 0) {
      puVar6 = SystemManager_GetLocalResourcePath(self,_DAT_7fff62446508,(undefined *)0x0);
      return puVar6;
    }
    if (iVar2 == 1) goto LAB_7fff5f5e7c48;
    if (iVar2 == 2) goto LAB_7fff5f5e7c24;
    if (iVar2 == 3) goto LAB_7fff5f5e7bf6;
    lVar5 = *(longlong *)(self + 0x20);
    if (iVar1 == 0) {
LAB_7fff5f5e7bae:
      uVar4 = *(uint *)(self + 0x58);
    }
    else if (iVar1 == 1) {
      uVar4 = 1;
    }
    else if (iVar1 == 2) {
      uVar4 = 2;
    }
    else if (iVar1 == 3) {
      uVar4 = 3;
    }
    else {
      if (iVar1 != 4) goto LAB_7fff5f5e7bae;
      uVar4 = 4;
    }
    if (lVar5 == 0) goto LAB_7fff5f5e7da7;
    if (*(uint *)(lVar5 + 0x18) <= uVar4) goto LAB_7fff5f5e7dad;
    uVar9 = *(undefined8 *)(lVar5 + 0x20 + (longlong)(int)uVar4 * 8);
    uVar8 = _DAT_7fff624428e8;
  }
  if (DAT_7fff625e18b4 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62443090);
    FUN_7fff5f47d450(&DAT_7fff62443218);
    FUN_7fff5f47d450(&DAT_7fff624429b0);
    FUN_7fff5f47d450(&DAT_7fff62442b38);
    FUN_7fff5f47d450(&DAT_7fff62442f08);
    FUN_7fff5f47d450(&DAT_7fff62442cc0);
    DAT_7fff625e18b4 = '\x01';
  }
  iVar1 = *(int *)(self + 0x30);
  uVar10 = _DAT_7fff62442b38;
  if ((((iVar1 != 1) && (uVar10 = _DAT_7fff62442cc0, iVar1 != 2)) &&
      (uVar10 = _DAT_7fff62442f08, iVar1 != 3)) &&
     ((uVar10 = _DAT_7fff62443090, iVar1 != 4 && (uVar10 = _DAT_7fff62443218, iVar1 != 5)))) {
    uVar10 = _DAT_7fff624429b0;
  }
  iVar1 = *(int *)(self + 0x28);
  uVar7 = _DAT_7fff62478020;
  if (((iVar1 != 1) && (iVar1 != 2)) && ((iVar1 == 3 || (*(int *)(self + 0x2c) == 3)))) {
    lVar5 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if (lVar5 == 0) {
LAB_7fff5f5e7da7:
      FUN_7fff5f47d660();
      pcVar3 = (code *)swi(3);
      puVar6 = (undefined *)(*pcVar3)();
      return puVar6;
    }
    uVar7 = _DAT_7fff62477f50;
    if (*(char *)(lVar5 + 0x20) == '\0') {
      puVar6 = (undefined *)FUN_7fff60e71650(uVar9,_DAT_7fff62477e80,uVar10,0);
      goto LAB_7fff5f5e7d73;
    }
  }
  puVar6 = (undefined *)FUN_7fff60e71970(uVar9,uVar7,0);
LAB_7fff5f5e7d73:
  iVar1 = *(int *)(self + 0x28);
  if (((iVar1 == 1) || (iVar1 == 2)) || ((iVar1 != 3 && (*(int *)(self + 0x2c) != 3)))) {
    puVar6 = (undefined *)FUN_7fff60e71970(puVar6,uVar8,0);
  }
  return puVar6;
}

