
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_GetExpBonus(undefined *thisObject,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined *thisObject_00;
  longlong *plStackX_8;
  longlong alStackX_18 [2];
  
  if (DAT_7ffe9cadde28 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    DAT_7ffe9cadde28 = '\x01';
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  plStackX_8 = (longlong *)0x0;
  alStackX_18[0] = 0;
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a485eda;
  lVar8 = (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
  if (lVar8 == 0) goto LAB_7ffe9a485eda;
  iVar5 = func_0x7ffe9a4eb350(lVar8,0x3f);
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a485eda;
  lVar8 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
  if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a485eda;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0xc2,&plStackX_8,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a485eda;
    iVar6 = (**(code **)(*plStackX_8 + 0x178))(plStackX_8,0x1c,*(undefined8 *)(*plStackX_8 + 0x180))
    ;
    iVar5 = iVar5 + iVar6;
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a485eda;
  lVar8 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar8 == 0) goto LAB_7ffe9a485eda;
  cVar3 = FUN_7ffe9a7cbb30(lVar8,0x301,alStackX_18,0);
  if (cVar3 != '\0') {
    if (alStackX_18[0] == 0) goto LAB_7ffe9a485eda;
    iVar6 = func_0x7ffe9a7a2140(alStackX_18[0],0x32);
    iVar5 = iVar5 + iVar6;
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a485eda;
  thisObject_00 =
       (undefined *)(**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220));
  if (thisObject_00 == (undefined *)0x0) goto LAB_7ffe9a485eda;
  bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x1a,(undefined *)0x0);
  if (bVar4 != 0) {
    iVar5 = iVar5 + 10;
  }
  if (*(int *)(thisObject + 0x18) == 1) {
LAB_7ffe9a485e4a:
    lVar8 = FUN_7ffe9a47bac0(0);
    if (lVar8 == 0) goto LAB_7ffe9a485eda;
    if (DAT_7ffe9cadddc1 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c952be8);
      DAT_7ffe9cadddc1 = '\x01';
    }
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c952be8);
    if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x40) == 0)) goto LAB_7ffe9a485eda;
    iVar6 = func_0x7ffe9a53b4e0(*(longlong *)(lVar8 + 0x40),*(undefined4 *)(thisObject + 0x18),0);
    iVar5 = iVar5 + iVar6;
  }
  else if (*(int *)(thisObject + 0x18) == 4) {
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar8 == 0) goto LAB_7ffe9a485eda;
    iVar7 = FUN_7ffe9a8db990(lVar8,0);
    iVar6 = *(int *)(thisObject + 0x20);
    if (iVar7 <= iVar6 / 3 + (iVar6 >> 0x1f) +
                 (int)(((longlong)iVar6 / 3 + ((longlong)iVar6 >> 0x3f) & 0xffffffffU) >> 0x1f))
    goto LAB_7ffe9a485e4a;
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (plVar1 != (longlong *)0x0) {
    lVar8 = (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
    if (lVar8 != 0) {
      iVar6 = FUN_7ffe9a4ebb50(lVar8,0x3f);
      return iVar6 + iVar5;
    }
  }
LAB_7ffe9a485eda:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

