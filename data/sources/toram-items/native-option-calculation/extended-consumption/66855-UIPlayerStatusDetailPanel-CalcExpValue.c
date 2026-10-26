
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int UIPlayerStatusDetailPanel_CalcExpValue(undefined *self,undefined *methodInfo)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  longlong *plVar4;
  code *pcVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  undefined8 uVar10;
  
  if (DAT_7ffe9cadc4c7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fd6f8);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c9528b8);
    DAT_7ffe9cadc4c7 = '\x01';
  }
  if (*(undefined **)(self + 0x78) != (undefined *)0x0) {
    iVar7 = PlayerSecondaryStatus_GetExpBonus(*(undefined **)(self + 0x78),(undefined *)0x0);
    lVar9 = *(longlong *)(self + 0xa8);
    if (lVar9 != 0) {
      if ((*(int *)(lVar9 + 0x18) == 0) ||
         (iVar1 = *(int *)(lVar9 + 0x20), *(uint *)(lVar9 + 0x18) < 2)) {
        FUN_7ffe9996d790();
        pcVar5 = (code *)swi(3);
        iVar7 = (*pcVar5)();
        return iVar7;
      }
      plVar4 = *(longlong **)(self + 0x70);
      iVar2 = *(int *)(lVar9 + 0x24);
      if (plVar4 != (longlong *)0x0) {
        lVar9 = (**(code **)(*plVar4 + 0x188))(plVar4,*(undefined8 *)(*plVar4 + 400));
        if (lVar9 != 0) {
          uVar3 = *(undefined4 *)(lVar9 + 0x10);
          lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
          if (lVar9 != 0) {
            iVar8 = FUN_7ffe9a5a40d0(lVar9,0);
            lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c9528b8);
            if (lVar9 != 0) {
              iVar8 = FUN_7ffe9a5273c0(lVar9,uVar3,0 < iVar8,0);
              iVar7 = iVar2 + iVar8 + iVar1 + iVar7 + 100;
              if (*(longlong *)(self + 0x58) != 0) {
                lVar9 = FUN_7ffe9a480320(*(longlong *)(self + 0x58),0);
                if ((lVar9 != 0) && (*(longlong *)(lVar9 + 0x18) != 0)) {
                  uVar10 = FUN_7ffe9a5ad230(*(longlong *)(lVar9 + 0x18),0);
                  cVar6 = FUN_7ffe9ab7f110(uVar10,0x44,_DAT_7ffe9c8fd6f8);
                  if (cVar6 != '\0') {
                    iVar7 = 0;
                  }
                  return iVar7;
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  iVar7 = (*pcVar5)();
  return iVar7;
}

