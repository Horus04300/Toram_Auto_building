
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
  
  if (DAT_7ffe9cada13a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c95ced0);
    FUN_7ffe9996d590(&DAT_7ffe9c95f6a0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ca68);
    FUN_7ffe9996d590(&DAT_7ffe9c9722f0);
    FUN_7ffe9996d590(&DAT_7ffe9c972220);
    FUN_7ffe9996d590(&DAT_7ffe9c93fe20);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    FUN_7ffe9996d590(&DAT_7ffe9c972150);
    DAT_7ffe9cada13a = '\x01';
  }
  iVar1 = *(int *)(self + 0x28);
  if (iVar1 == 1) {
LAB_7ffe99ad7f78:
    lVar5 = *(longlong *)(self + 0x20);
    if (lVar5 == 0) goto LAB_7ffe99ad80d7;
    if (*(uint *)(lVar5 + 0x18) < 2) {
LAB_7ffe99ad80dd:
      FUN_7ffe9996d790();
      pcVar3 = (code *)swi(3);
      puVar6 = (undefined *)(*pcVar3)();
      return puVar6;
    }
    uVar9 = *(undefined8 *)(lVar5 + 0x28);
    uVar8 = _DAT_7ffe9c95f6a0;
  }
  else if (iVar1 == 2) {
LAB_7ffe99ad7f54:
    lVar5 = *(longlong *)(self + 0x20);
    if (lVar5 == 0) goto LAB_7ffe99ad80d7;
    if (*(uint *)(lVar5 + 0x18) < 3) goto LAB_7ffe99ad80dd;
    uVar9 = *(undefined8 *)(lVar5 + 0x30);
    uVar8 = _DAT_7ffe9c95ced0;
  }
  else if (iVar1 == 3) {
LAB_7ffe99ad7f26:
    lVar5 = *(longlong *)(self + 0x20);
    if (lVar5 == 0) goto LAB_7ffe99ad80d7;
    if (*(uint *)(lVar5 + 0x18) < 4) goto LAB_7ffe99ad80dd;
    uVar9 = *(undefined8 *)(lVar5 + 0x38);
    uVar8 = _DAT_7ffe9c8f1820;
    if (self[0x34] != '\0') {
      uVar9 = *(undefined8 *)(self + 0x38);
    }
  }
  else {
    iVar2 = *(int *)(self + 0x2c);
    if (iVar2 == 0) {
      puVar6 = (undefined *)FUN_7ffe99ad81f0(self,_DAT_7ffe9c93fe20,0);
      return puVar6;
    }
    if (iVar2 == 1) goto LAB_7ffe99ad7f78;
    if (iVar2 == 2) goto LAB_7ffe99ad7f54;
    if (iVar2 == 3) goto LAB_7ffe99ad7f26;
    lVar5 = *(longlong *)(self + 0x20);
    if (iVar1 == 0) {
LAB_7ffe99ad7ede:
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
      if (iVar1 != 4) goto LAB_7ffe99ad7ede;
      uVar4 = 4;
    }
    if (lVar5 == 0) goto LAB_7ffe99ad80d7;
    if (*(uint *)(lVar5 + 0x18) <= uVar4) goto LAB_7ffe99ad80dd;
    uVar9 = *(undefined8 *)(lVar5 + 0x20 + (longlong)(int)uVar4 * 8);
    uVar8 = _DAT_7ffe9c93ca68;
  }
  if (DAT_7ffe9cada138 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c93d210);
    FUN_7ffe9996d590(&DAT_7ffe9c93d398);
    FUN_7ffe9996d590(&DAT_7ffe9c93cb28);
    FUN_7ffe9996d590(&DAT_7ffe9c93ccb0);
    FUN_7ffe9996d590(&DAT_7ffe9c93d088);
    FUN_7ffe9996d590(&DAT_7ffe9c93ce38);
    DAT_7ffe9cada138 = '\x01';
  }
  iVar1 = *(int *)(self + 0x30);
  uVar10 = _DAT_7ffe9c93ccb0;
  if ((((iVar1 != 1) && (uVar10 = _DAT_7ffe9c93ce38, iVar1 != 2)) &&
      (uVar10 = _DAT_7ffe9c93d088, iVar1 != 3)) &&
     ((uVar10 = _DAT_7ffe9c93d210, iVar1 != 4 && (uVar10 = _DAT_7ffe9c93d398, iVar1 != 5)))) {
    uVar10 = _DAT_7ffe9c93cb28;
  }
  iVar1 = *(int *)(self + 0x28);
  uVar7 = _DAT_7ffe9c9722f0;
  if (((iVar1 != 1) && (iVar1 != 2)) && ((iVar1 == 3 || (*(int *)(self + 0x2c) == 3)))) {
    lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar5 == 0) {
LAB_7ffe99ad80d7:
      FUN_7ffe9996d7a0();
      pcVar3 = (code *)swi(3);
      puVar6 = (undefined *)(*pcVar3)();
      return puVar6;
    }
    uVar7 = _DAT_7ffe9c972220;
    if (*(char *)(lVar5 + 0x20) == '\0') {
      puVar6 = (undefined *)FUN_7ffe9b367290(uVar9,_DAT_7ffe9c972150,uVar10,0);
      goto LAB_7ffe99ad80a3;
    }
  }
  puVar6 = (undefined *)FUN_7ffe9b3675b0(uVar9,uVar7,0);
LAB_7ffe99ad80a3:
  iVar1 = *(int *)(self + 0x28);
  if (((iVar1 == 1) || (iVar1 == 2)) || ((iVar1 != 3 && (*(int *)(self + 0x2c) != 3)))) {
    puVar6 = (undefined *)FUN_7ffe9b3675b0(puVar6,uVar8,0);
  }
  return puVar6;
}

