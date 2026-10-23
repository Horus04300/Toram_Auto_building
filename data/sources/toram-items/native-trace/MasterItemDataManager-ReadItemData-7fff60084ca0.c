
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
  
  if (DAT_7fff625e5cf1 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b500);
    FUN_7fff5f47d450(&DAT_7fff6241c5f8);
    FUN_7fff5f47d450(&DAT_7fff624626f8);
    FUN_7fff5f47d450(&DAT_7fff62401360);
    FUN_7fff5f47d450(&DAT_7fff6241c6c8);
    FUN_7fff5f47d450(&DAT_7fff624627c0);
    FUN_7fff5f47d450(&DAT_7fff62401290);
    FUN_7fff5f47d450(&DAT_7fff6241c528);
    FUN_7fff5f47d450(&DAT_7fff6241e3b0);
    FUN_7fff5f47d450(&DAT_7fff62419a98);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff624717c0);
    DAT_7fff625e5cf1 = '\x01';
  }
  iVar10 = 0;
  plStack_88 = (longlong *)0x0;
  plStack_90 = (longlong *)0x0;
  lStack_98 = 0;
  plVar5 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff624717c0);
  FUN_7fff60fcae90(plVar5,data,0);
  uStack_80 = 0;
  pplStack_78 = &plStack_88;
  plStack_88 = plVar5;
  plVar6 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6244b500);
  FUN_7fff60fd77f0(plVar6,plVar5,0);
  uStack_70 = 0;
  pplStack_68 = &plStack_90;
  plStack_90 = plVar6;
  if (plVar6 != (longlong *)0x0) {
    iVar4 = (**(code **)(*plVar6 + 0x228))(plVar6,*(undefined8 *)(*plVar6 + 0x230));
    uVar7 = func_0x7fff5f44ff00(_DAT_7fff62419a98);
    func_0x7fff608662f0(uVar7,iVar4,_DAT_7fff62401290);
    *(undefined8 *)(self + 0x20) = uVar7;
    thunk_FUN_7fff5f491fd0();
    while( true ) {
      if (iVar4 <= iVar10) break;
      puVar8 = ItemDBData_CreateItemData((undefined *)plStack_90,(undefined *)0x0);
      if (puVar8 == (undefined *)0x0) {
LAB_7fff60085096:
        FUN_7fff5f47d660();
        goto LAB_7fff6008509b;
      }
      if (*(longlong *)(self + 0x20) == 0) {
LAB_7fff60085091:
        FUN_7fff5f47d660();
        goto LAB_7fff60085096;
      }
      FUN_7fff60857660(*(longlong *)(self + 0x20),*(undefined4 *)(puVar8 + 0x28),puVar8,
                       _DAT_7fff62401360);
      bVar2 = ItemDBData_CheckEquipItem
                        ((undefined *)(ulonglong)(uint)(int)*(short *)(puVar8 + 0x30),
                         (undefined *)0x0);
      if (bVar2 == 0) goto LAB_7fff60084f52;
      lStack_98 = 0;
      if (*(longlong *)(self + 0x28) == 0) {
LAB_7fff6008508c:
        FUN_7fff5f47d660();
        goto LAB_7fff60085091;
      }
      cVar3 = FUN_7fff60898a30(*(longlong *)(self + 0x28),(int)*(short *)(puVar8 + 0x30),&lStack_98,
                               _DAT_7fff624627c0);
      if (cVar3 == '\0') {
        lVar9 = func_0x7fff5f44ff00(_DAT_7fff6241e3b0);
        FUN_7fff6082b860(lVar9,_DAT_7fff6241c528);
        lStack_98 = lVar9;
        if (*(longlong *)(self + 0x28) != 0) {
          FUN_7fff6088cb20(*(longlong *)(self + 0x28),(int)*(short *)(puVar8 + 0x30),lVar9,
                           _DAT_7fff624626f8);
          goto LAB_7fff60084f10;
        }
        FUN_7fff5f47d660();
LAB_7fff60085082:
        FUN_7fff5f47d660();
LAB_7fff60085087:
        FUN_7fff5f47d660();
        goto LAB_7fff6008508c;
      }
LAB_7fff60084f10:
      if (lStack_98 == 0) goto LAB_7fff60085087;
      cVar3 = FUN_7fff6081b330(lStack_98,*(undefined4 *)(puVar8 + 0x48),_DAT_7fff6241c6c8);
      if (cVar3 == '\0') {
        if (lStack_98 == 0) goto LAB_7fff60085082;
        FUN_7fff6082f140(lStack_98,*(undefined4 *)(puVar8 + 0x48),*(undefined4 *)(puVar8 + 0x44),
                         _DAT_7fff6241c5f8);
      }
LAB_7fff60084f52:
      iVar10 = iVar10 + 1;
    }
    if (plStack_90 != (longlong *)0x0) {
      (**(code **)(*plStack_90 + 0x198))(plStack_90,*(undefined8 *)(*plStack_90 + 0x1a0));
      if (plStack_90 != (longlong *)0x0) {
        FUN_7fff5f253010(0,_DAT_7fff624413c0);
      }
      if (plStack_88 != (longlong *)0x0) {
        (**(code **)(*plStack_88 + 600))(plStack_88,*(undefined8 *)(*plStack_88 + 0x260));
        if (plStack_88 != (longlong *)0x0) {
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
        }
        return 1;
      }
      goto LAB_7fff600850ab;
    }
LAB_7fff6008509b:
    FUN_7fff5f47d660();
  }
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
LAB_7fff600850ab:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

