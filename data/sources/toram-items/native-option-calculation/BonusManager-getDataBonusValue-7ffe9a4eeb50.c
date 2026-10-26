
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BonusManager_getDataBonusValue(undefined *self,int type,undefined *methodInfo)

{
  code *pcVar1;
  undefined *self_00;
  longlong lVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_7ffe9cade123 == '\0') {
    FUN_7ffe9996d590(0x7ffe9c908190);
    FUN_7ffe9996d590(0x7ffe9c94b780);
    FUN_7ffe9996d590(&DAT_7ffe9c94b840);
    FUN_7ffe9996d590(&DAT_7ffe9c908260);
    DAT_7ffe9cade123 = '\x01';
  }
  iVar4 = 0;
  iVar5 = 0;
  lVar2 = *(longlong *)(self + 0x78);
  while (lVar2 != 0) {
    if (*(int *)(lVar2 + 0x18) <= iVar5) {
      return iVar4;
    }
    if ((lVar2 == 0) ||
       (self_00 = (undefined *)FUN_7ffe9af8ab90(lVar2,iVar5), self_00 == (undefined *)0x0)) break;
    if (self_00[0x40] != '\0') {
      if (*(undefined **)(self + 0x18) == (undefined *)0x0) break;
      BonusScriptManager_Run
                (*(undefined **)(self + 0x18),*(undefined **)(self_00 + 0x10),0,(undefined *)0x0);
      BonusData_UpdateBonusList(self_00,(undefined *)0x0);
    }
    iVar3 = 0;
    while( true ) {
      lVar2 = *(longlong *)(self_00 + 0x20);
      if (lVar2 == 0) goto LAB_7ffe9a4eec7f;
      if (*(int *)(lVar2 + 0x18) <= iVar3) break;
      lVar2 = FUN_7ffe9af8ab90(lVar2,iVar3,_DAT_7ffe9c94b840);
      if (lVar2 == 0) goto LAB_7ffe9a4eec7f;
      if (*(int *)(lVar2 + 0x10) == type) {
        iVar4 = iVar4 + *(int *)(lVar2 + 0x14);
      }
      iVar3 = iVar3 + 1;
    }
    iVar5 = iVar5 + 1;
    lVar2 = *(longlong *)(self + 0x78);
  }
LAB_7ffe9a4eec7f:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar4 = (*pcVar1)();
  return iVar4;
}

