
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_GetbGuardSpeed(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  undefined *puVar8;
  longlong lStackX_8;
  longlong *aplStackX_18 [2];
  
  if (DAT_7ffe9cadde25 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9cadde25 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  iVar5 = 0;
  aplStackX_18[0] = (longlong *)0x0;
  lStackX_8 = 0;
  if (plVar1 != (longlong *)0x0) {
    lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if (lVar7 != 0) {
      puVar8 = (undefined *)FUN_7ffe99c08d90(lVar7,0);
      bVar3 = ItemDBData_CheckArmorAbility(puVar8,(undefined *)0x2,(undefined *)0x0);
      if (bVar3 != 0) {
        plVar1 = *(longlong **)(self + 0x10);
        if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4866f0;
        lVar7 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
        if ((lVar7 == 0) || (*(longlong *)(lVar7 + 0x68) == 0)) goto LAB_7ffe9a4866f0;
        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0xa1,aplStackX_18,_DAT_7ffe9c935bd0);
        iVar5 = 0;
        if (cVar4 != '\0') {
          if (aplStackX_18[0] == (longlong *)0x0) goto LAB_7ffe9a4866f0;
          iVar5 = (**(code **)(*aplStackX_18[0] + 0x178))
                            (aplStackX_18[0],9,*(undefined8 *)(*aplStackX_18[0] + 0x180));
        }
        plVar1 = *(longlong **)(self + 0x10);
        if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4866f0;
        lVar7 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
        if ((lVar7 == 0) || (*(longlong *)(lVar7 + 0x68) == 0)) goto LAB_7ffe9a4866f0;
        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0xa3,aplStackX_18,_DAT_7ffe9c935bd0);
        if (cVar4 != '\0') {
          if (aplStackX_18[0] == (longlong *)0x0) goto LAB_7ffe9a4866f0;
          iVar6 = (**(code **)(*aplStackX_18[0] + 0x178))
                            (aplStackX_18[0],9,*(undefined8 *)(*aplStackX_18[0] + 0x180));
          iVar5 = iVar5 + iVar6;
        }
      }
      plVar1 = *(longlong **)(self + 0x10);
      if (plVar1 != (longlong *)0x0) {
        lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
        if (lVar7 != 0) {
          lVar7 = FUN_7ffe99c08fe0(lVar7,0);
          if (lVar7 != 0) {
            plVar1 = *(longlong **)(self + 0x10);
            if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4866f0;
            lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
            if (lVar7 == 0) goto LAB_7ffe9a4866f0;
            lVar7 = FUN_7ffe99c08fe0(lVar7,0);
            if (lVar7 == 0) goto LAB_7ffe9a4866f0;
            if (*(int *)(lVar7 + 0x38) == 0x11) {
              plVar1 = *(longlong **)(self + 0x10);
              if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4866f0;
              lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
              if ((lVar7 == 0) || (*(longlong *)(lVar7 + 0x50) == 0)) goto LAB_7ffe9a4866f0;
              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x343,&lStackX_8,
                                       _DAT_7ffe9c934418);
              if (cVar4 != '\0') {
                if (lStackX_8 == 0) goto LAB_7ffe9a4866f0;
                iVar6 = func_0x7ffe9a7a2140(lStackX_8,0x1b);
                iVar5 = iVar5 + iVar6;
              }
              plVar1 = *(longlong **)(self + 0x10);
              if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a4866f0;
              lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
              if ((lVar7 == 0) || (*(longlong *)(lVar7 + 0x50) == 0)) goto LAB_7ffe9a4866f0;
              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x109,&lStackX_8,
                                       _DAT_7ffe9c934418);
              if (cVar4 != '\0') {
                if (lStackX_8 == 0) goto LAB_7ffe9a4866f0;
                iVar6 = func_0x7ffe9a7a2140(lStackX_8,0x39);
                iVar5 = iVar5 + iVar6;
              }
            }
          }
          plVar1 = *(longlong **)(self + 0x10);
          if (plVar1 != (longlong *)0x0) {
            lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
            if ((lVar7 != 0) && (*(longlong *)(lVar7 + 0x50) != 0)) {
              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0xec,&lStackX_8,_DAT_7ffe9c934418
                                      );
              if (cVar4 != '\0') {
                if (lStackX_8 == 0) goto LAB_7ffe9a4866f0;
                iVar6 = func_0x7ffe9a7a2140(lStackX_8,0x39);
                iVar5 = iVar5 + iVar6;
              }
              plVar1 = *(longlong **)(self + 0x10);
              if (plVar1 != (longlong *)0x0) {
                puVar8 = (undefined *)
                         (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
                if (puVar8 != (undefined *)0x0) {
                  iVar6 = BonusManager_GetBonusValue(puVar8,0x2d,(undefined *)0x0);
                  return iVar6 + iVar5;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a4866f0:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

