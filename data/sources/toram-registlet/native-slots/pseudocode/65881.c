
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIRegistletEditPanel_OnClickAddSlotButton(undefined *self,int param,undefined *methodInfo)

{
  longlong lVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  char cVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  int aiStackX_8 [2];
  int aiStackX_20 [2];
  int aiStack_28 [2];
  undefined8 uStack_20;
  
  if (DAT_7ffe9cadc328 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c955c78);
    FUN_7ffe9996d590(&DAT_7ffe9c94c190);
    FUN_7ffe9996d590(&DAT_7ffe9c8f4ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c920190);
    DAT_7ffe9cadc328 = '\x01';
  }
  if ((*(longlong *)(self + 0x68) != 0) &&
     (lVar7 = *(longlong *)(*(longlong *)(self + 0x68) + 0x30), lVar7 != 0)) {
    lVar7 = FUN_7ffe9bd98960(lVar7,0);
    if (lVar7 != 0) {
      cVar6 = FUN_7ffe9bd9b7d0(lVar7,0);
      if ((cVar6 == '\0') && (self[0xc0] != '\0')) {
        lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c955c78);
        if (lVar7 != 0) {
          FUN_7ffe99a314f0(lVar7);
          UIRegistletEditPanel_SetEnableEquipGemCartListWindow(self,0,(undefined *)0x0);
          if (*(longlong *)(self + 0x48) != 0) {
            FUN_7ffe9bd9b390(*(longlong *)(self + 0x48),1,0);
            if (*(longlong *)(self + 0xa0) != 0) {
              lVar7 = FUN_7ffe9a480320(*(longlong *)(self + 0xa0),0);
              if (lVar7 != 0) {
                iVar3 = *(int *)(lVar7 + 0x14);
                if (*(longlong *)(self + 0xa0) != 0) {
                  lVar7 = FUN_7ffe9a480320(*(longlong *)(self + 0xa0),0);
                  if ((lVar7 != 0) && (*(longlong *)(lVar7 + 0x18) != 0)) {
                    bVar2 = *(byte *)(*(longlong *)(lVar7 + 0x18) + 0x20);
                    if (*(longlong *)(self + 0xa0) != 0) {
                      lVar7 = FUN_7ffe9a480320(*(longlong *)(self + 0xa0),0);
                      if ((lVar7 != 0) && (lVar7 = *(longlong *)(lVar7 + 0x30), lVar7 != 0)) {
                        lVar1 = (ulonglong)bVar2 - 1;
                        if (*(uint *)(lVar7 + 0x18) <= (uint)lVar1) {
LAB_7ffe9a048a8f:
                          FUN_7ffe9996d790();
                          pcVar5 = (code *)swi(3);
                          (*pcVar5)();
                          return;
                        }
                        iVar4 = *(int *)(lVar7 + 0x20 + lVar1 * 4);
                        lVar7 = *(longlong *)(self + 0x50);
                        if (lVar7 != 0) {
                          if (*(int *)(lVar7 + 0x18) == 0) goto LAB_7ffe9a048a8f;
                          lVar7 = *(longlong *)(lVar7 + 0x20);
                          if (*(longlong *)(self + 0x70) != 0) {
                            uVar8 = FUN_7ffe99a58320(*(longlong *)(self + 0x70),_DAT_7ffe9c94c190,0)
                            ;
                            aiStackX_8[0] = iVar4;
                            uVar9 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
                            uVar9 = FUN_7ffe9b36a740(_DAT_7ffe9c920190,uVar9,0);
                            uVar8 = FUN_7ffe9b36a740(uVar8,uVar9,0);
                            if (lVar7 != 0) {
                              FUN_7ffe9a404310(lVar7,uVar8,0);
                              lVar7 = *(longlong *)(self + 0x50);
                              if (lVar7 != 0) {
                                if (*(uint *)(lVar7 + 0x18) < 2) goto LAB_7ffe9a048a8f;
                                lVar7 = *(longlong *)(lVar7 + 0x28);
                                aiStackX_20[0] = iVar3;
                                uVar8 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_20);
                                uVar8 = FUN_7ffe9b36a740(_DAT_7ffe9c8f4ad0,uVar8,0);
                                if (lVar7 != 0) {
                                  FUN_7ffe9a404310(lVar7,uVar8,0);
                                  lVar7 = *(longlong *)(self + 0x50);
                                  if (lVar7 != 0) {
                                    if (*(uint *)(lVar7 + 0x18) < 3) goto LAB_7ffe9a048a8f;
                                    lVar7 = *(longlong *)(lVar7 + 0x30);
                                    aiStack_28[0] = iVar3 - iVar4;
                                    uVar8 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStack_28);
                                    uVar8 = FUN_7ffe9b36a740(_DAT_7ffe9c8f4ad0,uVar8,0);
                                    if (lVar7 != 0) {
                                      FUN_7ffe9a404310(lVar7,uVar8,0);
                                      return;
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
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
        (*pcVar5)();
        return;
      }
      lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c955c78);
      if (lVar7 != 0) {
        uStack_20 = 0;
        aiStack_28[0] = 0;
        FUN_7ffe99a312c0(lVar7,8,0,_DAT_7ffe9c049cfc,0,&stack0xffffffffffffffe8,0,_DAT_7ffe9c049d1c)
        ;
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

