
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_GetExpBonus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  longlong lVar8;
  longlong *plStackX_8;
  longlong alStackX_18 [2];
  
  if (DAT_7ffe9cadde28 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    DAT_7ffe9cadde28 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  plStackX_8 = (longlong *)0x0;
  alStackX_18[0] = 0;
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a485eda;
  puVar7 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
  if (puVar7 == (undefined *)0x0) goto LAB_7ffe9a485eda;
  iVar4 = BonusManager_GetBonusValue(puVar7,0x3f,(undefined *)0x0);
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a485eda;
  lVar8 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
  if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a485eda;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0xc2,&plStackX_8,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a485eda;
    iVar5 = (**(code **)(*plStackX_8 + 0x178))(plStackX_8,0x1c,*(undefined8 *)(*plStackX_8 + 0x180))
    ;
    iVar4 = iVar4 + iVar5;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a485eda;
  lVar8 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar8 == 0) goto LAB_7ffe9a485eda;
  cVar3 = FUN_7ffe9a7cbb30(lVar8,0x301,alStackX_18,0);
  if (cVar3 != '\0') {
    if (alStackX_18[0] == 0) goto LAB_7ffe9a485eda;
    iVar5 = func_0x7ffe9a7a2140(alStackX_18[0],0x32);
    iVar4 = iVar4 + iVar5;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a485eda;
  lVar8 = (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220));
  if (lVar8 == 0) goto LAB_7ffe9a485eda;
  cVar3 = FUN_7ffe9a5b20c0(lVar8,0x1a);
  if (cVar3 != '\0') {
    iVar4 = iVar4 + 10;
  }
  if (*(int *)(self + 0x18) == 1) {
LAB_7ffe9a485e4a:
    lVar8 = FUN_7ffe9a47bac0(0);
    if (lVar8 == 0) goto LAB_7ffe9a485eda;
    if (DAT_7ffe9cadddc1 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c952be8);
      DAT_7ffe9cadddc1 = '\x01';
    }
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c952be8);
    if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x40) == 0)) goto LAB_7ffe9a485eda;
    iVar5 = func_0x7ffe9a53b4e0(*(longlong *)(lVar8 + 0x40),*(undefined4 *)(self + 0x18));
    iVar4 = iVar4 + iVar5;
  }
  else if (*(int *)(self + 0x18) == 4) {
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar8 == 0) goto LAB_7ffe9a485eda;
    iVar6 = FUN_7ffe9a8db990(lVar8,0);
    iVar5 = *(int *)(self + 0x20);
    if (iVar6 <= iVar5 / 3 + (iVar5 >> 0x1f) +
                 (int)(((longlong)iVar5 / 3 + ((longlong)iVar5 >> 0x3f) & 0xffffffffU) >> 0x1f))
    goto LAB_7ffe9a485e4a;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 != (longlong *)0x0) {
    puVar7 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
    if (puVar7 != (undefined *)0x0) {
      iVar5 = BonusManager_GetGuildFacilityExpBonus(puVar7,0x3f,(undefined *)0x0);
      return iVar5 + iVar4;
    }
  }
LAB_7ffe9a485eda:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

