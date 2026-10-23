
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MasterItemDataManager_ReadItemProperty(undefined *self,undefined *data,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  longlong *plVar5;
  longlong *plVar6;
  int iVar7;
  byte bVar8;
  longlong *plStackX_20;
  longlong *plStack_78;
  undefined *apuStack_70 [5];
  undefined8 uStack_48;
  longlong **pplStack_40;
  undefined8 uStack_38;
  longlong **pplStack_30;
  
  if (DAT_7ffe9cade59b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943bb8);
    FUN_7ffe9996d590(&DAT_7ffe9c8fa670);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    DAT_7ffe9cade59b = '\x01';
  }
  iVar7 = 0;
  plStack_78 = (longlong *)0x0;
  plStackX_20 = (longlong *)0x0;
  apuStack_70[0] = (undefined *)0x0;
  bVar8 = 1;
  plVar5 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c969f48);
  FUN_7ffe9b4c0ad0(plVar5,data,0);
  uStack_48 = 0;
  pplStack_40 = &plStack_78;
  plStack_78 = plVar5;
  plVar6 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c943bb8);
  FUN_7ffe9b4cd430(plVar6,plVar5,0);
  uStack_38 = 0;
  pplStack_30 = &plStackX_20;
  plStackX_20 = plVar6;
  if (plVar6 != (longlong *)0x0) {
    iVar3 = (**(code **)(*plVar6 + 0x228))(plVar6,*(undefined8 *)(*plVar6 + 0x230));
    for (; iVar7 < iVar3; iVar7 = iVar7 + 1) {
      if (plStackX_20 == (longlong *)0x0) {
LAB_7ffe9a57aec2:
        FUN_7ffe9996d7a0();
        goto LAB_7ffe9a57aec7;
      }
      uVar4 = (**(code **)(*plStackX_20 + 0x228))(plStackX_20,*(undefined8 *)(*plStackX_20 + 0x230))
      ;
      if (*(longlong *)(self + 0x20) == 0) {
        FUN_7ffe9996d7a0();
        goto LAB_7ffe9a57aec2;
      }
      cVar2 = FUN_7ffe9ad589b0(*(longlong *)(self + 0x20),uVar4,apuStack_70,_DAT_7ffe9c8fa670);
      if (cVar2 == '\0') {
        bVar8 = 0;
        break;
      }
      ItemDBData_SetItemDataProperty(apuStack_70[0],(undefined *)plStackX_20,(undefined *)0x0);
    }
    if (plStackX_20 != (longlong *)0x0) {
      (**(code **)(*plStackX_20 + 0x198))(plStackX_20,*(undefined8 *)(*plStackX_20 + 0x1a0));
      if (plStackX_20 != (longlong *)0x0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
      if (plStack_78 != (longlong *)0x0) {
        (**(code **)(*plStack_78 + 600))(plStack_78,*(undefined8 *)(*plStack_78 + 0x260));
        if (plStack_78 != (longlong *)0x0) {
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
        }
        return bVar8;
      }
      goto LAB_7ffe9a57aed7;
    }
LAB_7ffe9a57aec7:
    FUN_7ffe9996d7a0();
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a57aed7:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  bVar8 = (*pcVar1)();
  return bVar8;
}

