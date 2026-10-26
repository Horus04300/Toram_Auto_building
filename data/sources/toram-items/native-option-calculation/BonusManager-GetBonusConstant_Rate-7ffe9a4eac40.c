
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_GetBonusConstant_Rate
               (undefined *self,int constantType,int rateType,undefined *constant,undefined *rate,
               undefined *methodInfo)

{
  code *pcVar1;
  float fVar2;
  undefined *self_00;
  longlong lVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_7ffe9cade126 == '\0') {
    FUN_7ffe9996d590(0x7ffe9c908190);
    FUN_7ffe9996d590(0x7ffe9c94b780);
    FUN_7ffe9996d590(&DAT_7ffe9c94b840);
    FUN_7ffe9996d590(&DAT_7ffe9c908260);
    DAT_7ffe9cade126 = '\x01';
  }
  iVar5 = 0;
  *(undefined4 *)constant = 0;
  lVar3 = *(longlong *)(self + 0x78);
  *(undefined4 *)rate = 0x3f800000;
  fVar2 = _DAT_7ffe9c049b34;
  if (lVar3 != 0) {
    do {
      if (*(int *)(lVar3 + 0x18) <= iVar5) {
        return;
      }
      if ((lVar3 == 0) ||
         (self_00 = (undefined *)FUN_7ffe9af8ab90(lVar3,iVar5), self_00 == (undefined *)0x0)) break;
      if (self_00[0x40] != '\0') {
        if (*(undefined **)(self + 0x18) == (undefined *)0x0) break;
        BonusScriptManager_Run
                  (*(undefined **)(self + 0x18),*(undefined **)(self_00 + 0x10),0,(undefined *)0x0);
        BonusData_UpdateBonusList(self_00,(undefined *)0x0);
      }
      iVar4 = 0;
      while( true ) {
        lVar3 = *(longlong *)(self_00 + 0x20);
        if (lVar3 == 0) goto LAB_7ffe9a4eadcd;
        if (*(int *)(lVar3 + 0x18) <= iVar4) break;
        lVar3 = FUN_7ffe9af8ab90(lVar3,iVar4,_DAT_7ffe9c94b840);
        if (lVar3 == 0) goto LAB_7ffe9a4eadcd;
        if (*(int *)(lVar3 + 0x10) == constantType) {
          *(int *)constant = *(int *)constant + *(int *)(lVar3 + 0x14);
LAB_7ffe9a4ead90:
          iVar4 = iVar4 + 1;
        }
        else {
          if (*(int *)(lVar3 + 0x10) != rateType) goto LAB_7ffe9a4ead90;
          iVar4 = iVar4 + 1;
          *(float *)rate = (float)*(int *)(lVar3 + 0x14) * fVar2 + *(float *)rate;
        }
      }
      lVar3 = *(longlong *)(self + 0x78);
      iVar5 = iVar5 + 1;
      if (lVar3 == 0) break;
    } while( true );
  }
LAB_7ffe9a4eadcd:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

