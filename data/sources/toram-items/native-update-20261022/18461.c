
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MasterItemDataManager_ReadItemData(undefined *self,undefined *data,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  longlong *plVar5;
  longlong *plVar6;
  undefined8 uVar7;
  undefined *puVar8;
  longlong lVar9;
  int iVar10;
  longlong lStack_98;
  longlong *plStack_90;
  longlong *plStack_88;
  undefined8 uStack_80;
  longlong **pplStack_78;
  undefined8 uStack_70;
  longlong **pplStack_68;
  
  if (DAT_7ffe9cade59a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943bb8);
    FUN_7ffe9996d590(&DAT_7ffe9c9155c8);
    FUN_7ffe9996d590(&DAT_7ffe9c95b810);
    FUN_7ffe9996d590(&DAT_7ffe9c8fa330);
    FUN_7ffe9996d590(&DAT_7ffe9c915698);
    FUN_7ffe9996d590(&DAT_7ffe9c95b8e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8fa260);
    FUN_7ffe9996d590(&DAT_7ffe9c9154f8);
    FUN_7ffe9996d590(&DAT_7ffe9c916820);
    FUN_7ffe9996d590(&DAT_7ffe9c911f08);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    DAT_7ffe9cade59a = '\x01';
  }
  iVar10 = 0;
  plStack_88 = (longlong *)0x0;
  plStack_90 = (longlong *)0x0;
  lStack_98 = 0;
  plVar5 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c969f48);
  FUN_7ffe9b4c0ad0(plVar5,data,0);
  uStack_80 = 0;
  pplStack_78 = &plStack_88;
  plStack_88 = plVar5;
  plVar6 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c943bb8);
  FUN_7ffe9b4cd430(plVar6,plVar5,0);
  uStack_70 = 0;
  pplStack_68 = &plStack_90;
  plStack_90 = plVar6;
  if (plVar6 != (longlong *)0x0) {
    iVar4 = (**(code **)(*plVar6 + 0x228))(plVar6,*(undefined8 *)(*plVar6 + 0x230));
    uVar7 = func_0x7ffe99940040(_DAT_7ffe9c911f08);
    func_0x7ffe9ad5bf30(uVar7,iVar4,_DAT_7ffe9c8fa260);
    *(undefined8 *)(self + 0x20) = uVar7;
    il2cpp_write_barrier_0();
    while( true ) {
      if (iVar4 <= iVar10) break;
      puVar8 = ItemDBData_CreateItemData((undefined *)plStack_90,(undefined *)0x0);
      if (puVar8 == (undefined *)0x0) {
LAB_7ffe9a57abe6:
        FUN_7ffe9996d7a0();
        goto LAB_7ffe9a57abeb;
      }
      if (*(longlong *)(self + 0x20) == 0) {
LAB_7ffe9a57abe1:
        FUN_7ffe9996d7a0();
        goto LAB_7ffe9a57abe6;
      }
      FUN_7ffe9ad4d2a0(*(longlong *)(self + 0x20),*(undefined4 *)(puVar8 + 0x28),puVar8,
                       _DAT_7ffe9c8fa330);
      bVar2 = UIItemListManager_CheckEquipItem
                        ((undefined *)(ulonglong)(uint)(int)*(short *)(puVar8 + 0x30),
                         (undefined *)0x0);
      if (bVar2 == 0) goto LAB_7ffe9a57aaa2;
      lStack_98 = 0;
      if (*(longlong *)(self + 0x28) == 0) {
LAB_7ffe9a57abdc:
        FUN_7ffe9996d7a0();
        goto LAB_7ffe9a57abe1;
      }
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(self + 0x28),(int)*(short *)(puVar8 + 0x30),&lStack_98,
                               _DAT_7ffe9c95b8e0);
      if (cVar3 == '\0') {
        lVar9 = func_0x7ffe99940040(_DAT_7ffe9c916820);
        FUN_7ffe9ad214a0(lVar9,_DAT_7ffe9c9154f8);
        lStack_98 = lVar9;
        if (*(longlong *)(self + 0x28) != 0) {
          FUN_7ffe9ad82760(*(longlong *)(self + 0x28),(int)*(short *)(puVar8 + 0x30),lVar9,
                           _DAT_7ffe9c95b810);
          goto LAB_7ffe9a57aa60;
        }
        FUN_7ffe9996d7a0();
LAB_7ffe9a57abd2:
        FUN_7ffe9996d7a0();
LAB_7ffe9a57abd7:
        FUN_7ffe9996d7a0();
        goto LAB_7ffe9a57abdc;
      }
LAB_7ffe9a57aa60:
      if (lStack_98 == 0) goto LAB_7ffe9a57abd7;
      cVar3 = FUN_7ffe9ad10f70(lStack_98,*(undefined4 *)(puVar8 + 0x48),_DAT_7ffe9c915698);
      if (cVar3 == '\0') {
        if (lStack_98 == 0) goto LAB_7ffe9a57abd2;
        FUN_7ffe9ad24d80(lStack_98,*(undefined4 *)(puVar8 + 0x48),*(undefined4 *)(puVar8 + 0x44),
                         _DAT_7ffe9c9155c8);
      }
LAB_7ffe9a57aaa2:
      iVar10 = iVar10 + 1;
    }
    if (plStack_90 != (longlong *)0x0) {
      (**(code **)(*plStack_90 + 0x198))(plStack_90,*(undefined8 *)(*plStack_90 + 0x1a0));
      if (plStack_90 != (longlong *)0x0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
      if (plStack_88 != (longlong *)0x0) {
        (**(code **)(*plStack_88 + 600))(plStack_88,*(undefined8 *)(*plStack_88 + 0x260));
        if (plStack_88 != (longlong *)0x0) {
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
        }
        return 1;
      }
      goto LAB_7ffe9a57abfb;
    }
LAB_7ffe9a57abeb:
    FUN_7ffe9996d7a0();
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a57abfb:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

