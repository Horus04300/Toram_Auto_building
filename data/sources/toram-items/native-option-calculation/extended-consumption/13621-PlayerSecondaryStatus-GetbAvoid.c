
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_GetbAvoid(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined *puVar9;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadde24 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9cadde24 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  iVar5 = 0;
  plStackX_8 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    lVar8 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if (lVar8 != 0) {
      puVar9 = (undefined *)FUN_7ffe99c08d90(lVar8,0);
      bVar3 = ItemDBData_CheckArmorAbility(puVar9,(undefined *)0x1,(undefined *)0x0);
      if (bVar3 != 0) {
        plVar1 = *(longlong **)(self + 0x10);
        if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a486243;
        lVar8 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a486243;
        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0xa2,&plStackX_8,_DAT_7ffe9c935bd0);
        iVar5 = 0;
        if (cVar4 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a486243;
          iVar5 = (**(code **)(*plStackX_8 + 0x178))
                            (plStackX_8,0xb,*(undefined8 *)(*plStackX_8 + 0x180));
        }
        plVar1 = *(longlong **)(self + 0x10);
        if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a486243;
        lVar8 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a486243;
        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0xa4,&plStackX_8,_DAT_7ffe9c935bd0);
        if (cVar4 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a486243;
          iVar6 = (**(code **)(*plStackX_8 + 0x178))
                            (plStackX_8,0xb,*(undefined8 *)(*plStackX_8 + 0x180));
          iVar5 = iVar5 + iVar6;
        }
      }
      plVar1 = *(longlong **)(self + 0x10);
      if (plVar1 != (longlong *)0x0) {
        lVar8 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
        if (lVar8 != 0) {
          iVar6 = func_0x7ffe9a7c8f00(lVar8,0x57);
          plVar1 = *(longlong **)(self + 0x10);
          if (plVar1 != (longlong *)0x0) {
            puVar9 = (undefined *)
                     (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
            if (puVar9 != (undefined *)0x0) {
              iVar7 = BonusManager_GetBonusValue(puVar9,0x2f,(undefined *)0x0);
              return iVar7 + iVar5 + iVar6;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a486243:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

