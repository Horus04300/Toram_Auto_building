
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_AvoidStack(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  undefined *armorItem;
  int iVar7;
  longlong *plStackX_8;
  longlong lStackX_18;
  
  if (DAT_7ffe9cadde19 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c9540a0);
    DAT_7ffe9cadde19 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  iVar7 = 0;
  plStackX_8 = (longlong *)0x0;
  lStackX_18 = 0;
  if (((plVar1 == (longlong *)0x0) ||
      (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar6 == 0))
     || (*(longlong *)(lVar6 + 0x20) == 0)) goto LAB_7ffe9a487890;
  iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x20),0);
  if (iVar5 == 0x12) {
    iVar7 = 2000;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (((plVar1 == (longlong *)0x0) ||
      (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar6 == 0))
     || (*(longlong *)(lVar6 + 0x18) == 0)) goto LAB_7ffe9a487890;
  iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x18),0);
  if (iVar5 == 0x10) {
    iVar7 = iVar7 + 1000;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (((plVar1 == (longlong *)0x0) ||
      (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar6 == 0))
     || (*(longlong *)(lVar6 + 0x18) == 0)) goto LAB_7ffe9a487890;
  iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x18),0);
  if (iVar5 == 0xf) {
LAB_7ffe9a487557:
    iVar7 = iVar7 + 4000;
  }
  else {
    plVar1 = *(longlong **)(self + 0x10);
    if (((plVar1 == (longlong *)0x0) ||
        (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar6 == 0
        )) || (*(longlong *)(lVar6 + 0x20) == 0)) goto LAB_7ffe9a487890;
    iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x20),0);
    if (iVar5 == 0xf) goto LAB_7ffe9a487557;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (((plVar1 != (longlong *)0x0) &&
      (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar6 != 0))
     && (*(longlong *)(lVar6 + 0x18) != 0)) {
    iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x18),0);
    if (iVar5 == 10) {
      plVar1 = *(longlong **)(self + 0x10);
      if (((plVar1 == (longlong *)0x0) ||
          (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
          lVar6 == 0)) || (*(longlong *)(lVar6 + 0x20) == 0)) goto LAB_7ffe9a487890;
      iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x20),0);
      if (iVar5 == 10) {
        iVar7 = iVar7 + 1000;
      }
    }
    plVar1 = *(longlong **)(self + 0x10);
    if ((plVar1 != (longlong *)0x0) &&
       (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar6 != 0)
       ) {
      armorItem = (undefined *)FUN_7ffe99c08d90(lVar6,0);
      bVar3 = ItemDBData_CheckArmorAbility(armorItem,(undefined *)0x1,(undefined *)0x0);
      if (bVar3 != 0) {
        iVar7 = iVar7 + 3000;
      }
      plVar1 = *(longlong **)(self + 0x10);
      if (((plVar1 != (longlong *)0x0) &&
          (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
          lVar6 != 0)) && (*(longlong *)(lVar6 + 0x18) != 0)) {
        iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x18),0);
        if (iVar5 == 0) {
          plVar1 = *(longlong **)(self + 0x10);
          if (((plVar1 == (longlong *)0x0) ||
              (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
              lVar6 == 0)) || (*(longlong *)(lVar6 + 0x20) == 0)) goto LAB_7ffe9a487890;
          iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x20),0);
          if (iVar5 == 0) {
            plVar1 = *(longlong **)(self + 0x10);
            if (((plVar1 == (longlong *)0x0) ||
                (lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
                lVar6 == 0)) || (*(longlong *)(lVar6 + 0x68) == 0)) goto LAB_7ffe9a487890;
            cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x44c,&plStackX_8,_DAT_7ffe9c935bd0
                                    );
            if (cVar4 != '\0') {
              if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a487890;
              iVar5 = (**(code **)(*plStackX_8 + 0x178))
                                (plStackX_8,0x1c,*(undefined8 *)(*plStackX_8 + 0x180));
              iVar7 = iVar7 + iVar5;
            }
          }
        }
        plVar1 = *(longlong **)(self + 0x10);
        if ((plVar1 != (longlong *)0x0) &&
           (lVar6 = (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
           lVar6 != 0)) {
          cVar4 = FUN_7ffe9a5b20c0(lVar6,0x32,0);
          if ((cVar4 != '\0') && (iVar7 < 1000)) {
            iVar7 = 1000;
          }
          lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c9540a0);
          if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x28) != 0)) {
            plVar1 = *(longlong **)(self + 0x10);
            iVar5 = iVar7 * 2;
            if (*(int *)(*(longlong *)(lVar6 + 0x28) + 0x54) != 0) {
              iVar5 = iVar7;
            }
            if (((plVar1 != (longlong *)0x0) &&
                (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
                lVar6 != 0)) && (*(longlong *)(lVar6 + 0x18) != 0)) {
              iVar7 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x18),0);
              if (iVar7 != 10) {
                return iVar5;
              }
              plVar1 = *(longlong **)(self + 0x10);
              if (((plVar1 != (longlong *)0x0) &&
                  (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
                  lVar6 != 0)) && (*(longlong *)(lVar6 + 0x20) != 0)) {
                iVar7 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x20),0);
                if (iVar7 != 10) {
                  return iVar5;
                }
                plVar1 = *(longlong **)(self + 0x10);
                if (((plVar1 != (longlong *)0x0) &&
                    (lVar6 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0))
                    , lVar6 != 0)) && (*(longlong *)(lVar6 + 0x50) != 0)) {
                  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x50),0x28a,&lStackX_18,
                                           _DAT_7ffe9c934418);
                  if (cVar4 != '\0') {
                    if (lStackX_18 == 0) goto LAB_7ffe9a487890;
                    iVar7 = func_0x7ffe9a7a2140(lStackX_18,0x58);
                    iVar5 = iVar5 + iVar7;
                  }
                  return iVar5;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a487890:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar7 = (*pcVar2)();
  return iVar7;
}

