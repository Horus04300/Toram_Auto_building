
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_GetbGuardPower(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  undefined *puVar8;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadde26 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9cadde26 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  iVar5 = 0;
  plStackX_8 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if (lVar7 != 0) {
      puVar8 = (undefined *)FUN_7ffe99c08d90(lVar7,0);
      bVar3 = ItemDBData_CheckArmorAbility(puVar8,(undefined *)0x2,(undefined *)0x0);
      if (bVar3 != 0) {
        plVar1 = *(longlong **)(self + 0x10);
        if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a486371;
        lVar7 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
        if ((lVar7 == 0) || (*(longlong *)(lVar7 + 0x68) == 0)) goto LAB_7ffe9a486371;
        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0xa3,&plStackX_8,_DAT_7ffe9c935bd0);
        if (cVar4 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a486371;
          iVar5 = (**(code **)(*plStackX_8 + 0x178))
                            (plStackX_8,10,*(undefined8 *)(*plStackX_8 + 0x180));
        }
      }
      plVar1 = *(longlong **)(self + 0x10);
      if (plVar1 != (longlong *)0x0) {
        puVar8 = (undefined *)
                 (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
        if (puVar8 != (undefined *)0x0) {
          iVar6 = BonusManager_GetBonusValue(puVar8,0x2e,(undefined *)0x0);
          return iVar6 + iVar5;
        }
      }
    }
  }
LAB_7ffe9a486371:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

