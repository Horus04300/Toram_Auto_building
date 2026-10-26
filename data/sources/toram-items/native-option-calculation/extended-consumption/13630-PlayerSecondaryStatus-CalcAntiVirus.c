
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_CalcAntiVirus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  longlong lVar7;
  undefined *self_00;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadde2c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9368c8);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cadde2c = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  plStackX_8 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    lVar7 = (**(code **)(*plVar1 + 0x188))(plVar1,*(undefined8 *)(*plVar1 + 400));
    if (lVar7 != 0) {
      plVar1 = *(longlong **)(self + 0x10);
      iVar5 = *(int *)(lVar7 + 0x30);
      if (plVar1 != (longlong *)0x0) {
        self_00 = (undefined *)
                  (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
        if (self_00 != (undefined *)0x0) {
          iVar4 = BonusManager_GetBonusValue(self_00,0x2c,(undefined *)0x0);
          plVar1 = *(longlong **)(self + 0x10);
          iVar4 = (iVar5 * 10) / 0x22 + iVar4;
          if (plVar1 != (longlong *)0x0) {
            lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
            if (lVar7 != 0) {
              cVar3 = FUN_7ffe9a7cbb30(lVar7,0x91,&plStackX_8,0);
              if (cVar3 != '\0') {
                if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a482234;
                if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c9368c8 + 0x130)) ||
                    (*(longlong *)
                      (*(longlong *)(*plStackX_8 + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c9368c8 + 0x130) * 8) != _DAT_7ffe9c9368c8)) ||
                   (plStackX_8 == (longlong *)0x0)) {
                  FUN_7ffe9996c950(plStackX_8);
                  pcVar2 = (code *)swi(3);
                  iVar5 = (*pcVar2)();
                  return iVar5;
                }
                if ((char)plStackX_8[5] != '\0') {
                  plVar1 = *(longlong **)(self + 0x10);
                  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a482234;
                  lVar7 = (**(code **)(*plVar1 + 0x178))(plVar1,*(undefined8 *)(*plVar1 + 0x180));
                  if (lVar7 == 0) goto LAB_7ffe9a482234;
                  iVar5 = (*(int *)(lVar7 + 0x18) / 100) * 10;
                  if (100 < iVar5) {
                    iVar5 = 100;
                  }
                  iVar4 = iVar4 + iVar5;
                }
              }
              plVar1 = *(longlong **)(self + 0x10);
              if (plVar1 != (longlong *)0x0) {
                lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
                if (lVar7 != 0) {
                  cVar3 = FUN_7ffe9a7cbb30(lVar7,0x486,&plStackX_8,0);
                  if (cVar3 != '\0') {
                    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a482234;
                    iVar5 = func_0x7ffe9a7a2140(plStackX_8,0x25);
                    iVar4 = iVar4 + iVar5;
                  }
                  plVar1 = *(longlong **)(self + 0x10);
                  if (plVar1 != (longlong *)0x0) {
                    lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
                    if (lVar7 != 0) {
                      cVar3 = FUN_7ffe9a7cbb30(lVar7,0x2c9,&plStackX_8,0);
                      if (cVar3 != '\0') {
                        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a482234;
                        iVar5 = func_0x7ffe9a7a2140(plStackX_8,0x32);
                        iVar4 = iVar4 + iVar5;
                      }
                      plVar1 = *(longlong **)(self + 0x10);
                      if (plVar1 != (longlong *)0x0) {
                        lVar7 = (**(code **)(*plVar1 + 0x1c8))
                                          (plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
                        if (lVar7 != 0) {
                          cVar3 = FUN_7ffe9a7cbb30(lVar7,0x461,&plStackX_8,0);
                          if (cVar3 != '\0') {
                            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a482234;
                            uVar6 = func_0x7ffe9a7a2140(plStackX_8,0x25);
                            if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                              func_0x7ffe9996d830();
                            }
                            iVar4 = func_0x7ffe9b506b70(iVar4,uVar6,0);
                          }
                          return iVar4;
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
LAB_7ffe9a482234:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

