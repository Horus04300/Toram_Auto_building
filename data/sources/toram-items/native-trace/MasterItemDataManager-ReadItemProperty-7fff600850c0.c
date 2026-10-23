
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
  
  if (DAT_7fff625e5cf2 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b500);
    FUN_7fff5f47d450(&DAT_7fff624016a0);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff624717c0);
    DAT_7fff625e5cf2 = '\x01';
  }
  iVar7 = 0;
  plStack_78 = (longlong *)0x0;
  plStackX_20 = (longlong *)0x0;
  apuStack_70[0] = (undefined *)0x0;
  bVar8 = 1;
  plVar5 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff624717c0);
  FUN_7fff60fcae90(plVar5,data,0);
  uStack_48 = 0;
  pplStack_40 = &plStack_78;
  plStack_78 = plVar5;
  plVar6 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6244b500);
  FUN_7fff60fd77f0(plVar6,plVar5,0);
  uStack_38 = 0;
  pplStack_30 = &plStackX_20;
  plStackX_20 = plVar6;
  if (plVar6 != (longlong *)0x0) {
    iVar3 = (**(code **)(*plVar6 + 0x228))(plVar6,*(undefined8 *)(*plVar6 + 0x230));
    for (; iVar7 < iVar3; iVar7 = iVar7 + 1) {
      if (plStackX_20 == (longlong *)0x0) {
LAB_7fff60085372:
        FUN_7fff5f47d660();
        goto LAB_7fff60085377;
      }
      uVar4 = (**(code **)(*plStackX_20 + 0x228))(plStackX_20,*(undefined8 *)(*plStackX_20 + 0x230))
      ;
      if (*(longlong *)(self + 0x20) == 0) {
        FUN_7fff5f47d660();
        goto LAB_7fff60085372;
      }
      cVar2 = FUN_7fff60862d70(*(longlong *)(self + 0x20),uVar4,apuStack_70,_DAT_7fff624016a0);
      if (cVar2 == '\0') {
        bVar8 = 0;
        break;
      }
      ItemDBData_SetItemDataProperty(apuStack_70[0],(undefined *)plStackX_20,(undefined *)0x0);
    }
    if (plStackX_20 != (longlong *)0x0) {
      (**(code **)(*plStackX_20 + 0x198))(plStackX_20,*(undefined8 *)(*plStackX_20 + 0x1a0));
      if (plStackX_20 != (longlong *)0x0) {
        FUN_7fff5f253010(0,_DAT_7fff624413c0);
      }
      if (plStack_78 != (longlong *)0x0) {
        (**(code **)(*plStack_78 + 600))(plStack_78,*(undefined8 *)(*plStack_78 + 0x260));
        if (plStack_78 != (longlong *)0x0) {
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
        }
        return bVar8;
      }
      goto LAB_7fff60085387;
    }
LAB_7fff60085377:
    FUN_7fff5f47d660();
  }
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
LAB_7fff60085387:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  bVar8 = (*pcVar1)();
  return bVar8;
}

