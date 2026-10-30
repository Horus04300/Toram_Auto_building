
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_AvoidSpeed(undefined *thisObject,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined *thisObject_00;
  int iVar10;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadde18 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cadde18 = '\x01';
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  iVar10 = 0;
  iVar6 = 0;
  plStackX_8 = (longlong *)0x0;
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4873de;
  lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
  if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x20) == 0)) goto LAB_7ffe9a4873de;
  iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x20),0);
  if (iVar5 == 0x12) {
    iVar10 = 300;
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4873de;
  lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
  if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x18) == 0)) goto LAB_7ffe9a4873de;
  iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x18),0);
  if (iVar5 == 0x10) {
    iVar10 = iVar10 + 400;
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4873de;
  lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
  if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x18) == 0)) goto LAB_7ffe9a4873de;
  iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x18),0);
  if (iVar5 == 0xf) {
LAB_7ffe9a486fcc:
    iVar10 = iVar10 + 100;
  }
  else {
    plVar1 = *(longlong **)(thisObject + 0x10);
    if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4873de;
    lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x20) == 0)) goto LAB_7ffe9a4873de;
    iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x20),0);
    if (iVar5 == 0xf) goto LAB_7ffe9a486fcc;
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (plVar1 != (longlong *)0x0) {
    lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x18) != 0)) {
      iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x18),0);
      if (iVar5 == 10) {
        plVar1 = *(longlong **)(thisObject + 0x10);
        if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4873de;
        lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x20) == 0)) goto LAB_7ffe9a4873de;
        iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x20),0);
        if (iVar5 == 10) {
          iVar10 = iVar10 + 100;
        }
      }
      plVar1 = *(longlong **)(thisObject + 0x10);
      if (plVar1 != (longlong *)0x0) {
        lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
        if (lVar8 != 0) {
          uVar9 = FUN_7ffe99c08d90(lVar8,0);
          cVar3 = func_0x7ffe9a569860(uVar9,1);
          if (cVar3 != '\0') {
            iVar10 = iVar10 + 200;
          }
          plVar1 = *(longlong **)(thisObject + 0x10);
          if (plVar1 != (longlong *)0x0) {
            lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
            if (lVar8 != 0) {
              uVar9 = FUN_7ffe99c08d90(lVar8,0);
              cVar3 = func_0x7ffe9a569860(uVar9,1);
              if (cVar3 != '\0') {
                plVar1 = *(longlong **)(thisObject + 0x10);
                if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4873de;
                lVar8 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
                if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a4873de;
                cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0xa2,&plStackX_8,
                                         _DAT_7ffe9c935bd0);
                iVar6 = 0;
                if (cVar3 != '\0') {
                  if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4873de;
                  iVar6 = (**(code **)(*plStackX_8 + 0x178))
                                    (plStackX_8,0xb,*(undefined8 *)(*plStackX_8 + 0x180));
                }
                plVar1 = *(longlong **)(thisObject + 0x10);
                if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4873de;
                lVar8 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
                if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a4873de;
                cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0xa4,&plStackX_8,
                                         _DAT_7ffe9c935bd0);
                if (cVar3 != '\0') {
                  if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4873de;
                  iVar5 = (**(code **)(*plStackX_8 + 0x178))(plStackX_8,0xb);
                  iVar6 = iVar6 + iVar5;
                }
              }
              plVar1 = *(longlong **)(thisObject + 0x10);
              if (plVar1 != (longlong *)0x0) {
                lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
                if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x18) != 0)) {
                  iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x18),0);
                  if (iVar5 == 0) {
                    plVar1 = *(longlong **)(thisObject + 0x10);
                    if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4873de;
                    lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
                    if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x20) == 0)) goto LAB_7ffe9a4873de;
                    iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x20),0);
                    if (iVar5 == 0) {
                      plVar1 = *(longlong **)(thisObject + 0x10);
                      if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4873de;
                      lVar8 = (**(code **)(*plVar1 + 0x1b8))
                                        (plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
                      if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a4873de;
                      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x44c,&plStackX_8,
                                               _DAT_7ffe9c935bd0);
                      if (cVar3 != '\0') {
                        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4873de;
                        iVar5 = (**(code **)(*plStackX_8 + 0x178))(plStackX_8,0xb);
                        iVar10 = iVar10 + iVar5;
                      }
                    }
                  }
                  plVar1 = *(longlong **)(thisObject + 0x10);
                  if (plVar1 != (longlong *)0x0) {
                    thisObject_00 =
                         (undefined *)
                         (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220));
                    if (thisObject_00 != (undefined *)0x0) {
                      bVar4 = GemCartBufferManager_ContainsBuffer
                                        (thisObject_00,0x32,(undefined *)0x0);
                      if ((bVar4 != 0) && (iVar10 < 100)) {
                        iVar10 = 100;
                      }
                      plVar1 = *(longlong **)(thisObject + 0x10);
                      if (plVar1 != (longlong *)0x0) {
                        lVar8 = (**(code **)(*plVar1 + 0x1c8))
                                          (plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
                        if (lVar8 != 0) {
                          iVar5 = func_0x7ffe9a7c8f00(lVar8,0x57);
                          plVar1 = *(longlong **)(thisObject + 0x10);
                          if (plVar1 != (longlong *)0x0) {
                            lVar8 = (**(code **)(*plVar1 + 0x1d8))
                                              (plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
                            if (lVar8 != 0) {
                              iVar7 = func_0x7ffe9a4eb350(lVar8,0x2f);
                              if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                                func_0x7ffe9996d830();
                              }
                              iVar6 = func_0x7ffe9b506b70(1,((iVar7 + 100 + iVar5 + iVar6) * iVar10)
                                                            / 100);
                              return iVar6;
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
LAB_7ffe9a4873de:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar6 = (*pcVar2)();
  return iVar6;
}

