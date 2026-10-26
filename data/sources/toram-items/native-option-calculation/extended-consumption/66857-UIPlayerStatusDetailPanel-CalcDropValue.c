
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int UIPlayerStatusDetailPanel_CalcDropValue(undefined *self,undefined *methodInfo)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  
  if (DAT_7ffe9cadc4c8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9528b8);
    DAT_7ffe9cadc4c8 = '\x01';
  }
  if (*(undefined **)(self + 0x78) != (undefined *)0x0) {
    iVar4 = PlayerSecondaryStatus_GetDropBonus(*(undefined **)(self + 0x78),(undefined *)0x0);
    lVar6 = *(longlong *)(self + 0xa8);
    if (lVar6 != 0) {
      if ((*(uint *)(lVar6 + 0x18) < 3) ||
         (iVar1 = *(int *)(lVar6 + 0x28), *(uint *)(lVar6 + 0x18) < 4)) {
        FUN_7ffe9996d790();
        pcVar3 = (code *)swi(3);
        iVar4 = (*pcVar3)();
        return iVar4;
      }
      iVar2 = *(int *)(lVar6 + 0x2c);
      lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c9528b8);
      if (lVar6 != 0) {
        iVar5 = FUN_7ffe9a527050(lVar6,0);
        return iVar5 + 100 + iVar2 + iVar1 + iVar4;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  iVar4 = (*pcVar3)();
  return iVar4;
}

