
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MobPropertyBase_GetValue(undefined *self,int type,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  undefined *puVar7;
  undefined8 uVar8;
  
  if (DAT_7ffe9cadd789 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90a488);
    FUN_7ffe9996d590(&DAT_7ffe9c93f1f8);
    FUN_7ffe9996d590(&DAT_7ffe9c968098);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1478);
    DAT_7ffe9cadd789 = '\x01';
  }
  lVar3 = func_0x7ffe99940040(_DAT_7ffe9c8f1478);
  func_0x7ffe999c3920(lVar3,0);
  if (lVar3 == 0) {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    puVar7 = (undefined *)(*pcVar1)();
    return puVar7;
  }
  *(int *)(lVar3 + 0x10) = type;
  lVar6 = *(longlong *)(self + 0x10);
  lVar4 = func_0x7ffe99940040(_DAT_7ffe9c93f1f8);
  FUN_7ffe9af13420(lVar4,lVar3,_DAT_7ffe9c968098,0);
  lVar3 = _DAT_7ffe9c90a488;
  if (*(longlong *)(_DAT_7ffe9c90a488 + 0x38) == 0) {
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    if (*(longlong *)(lVar3 + 0x38) == 0) {
      FUN_7ffe998cedc0(lVar3);
    }
  }
  if (lVar6 == 0) {
    uVar8 = func_0x7ffe9996d5b0(0x7ffe9c94f360);
    uVar8 = FUN_7ffe9b661bf0(uVar8,0);
    FUN_7ffe9996d760(uVar8,lVar3);
LAB_7ffe9ab8565e:
    FUN_7ffe9996d7a0();
  }
  else {
    if (lVar4 == 0) {
      uVar8 = func_0x7ffe9996d5b0(0x7ffe9c937638);
      uVar8 = FUN_7ffe9b661bf0(uVar8,0);
      FUN_7ffe9996d760(uVar8,lVar3);
      pcVar1 = (code *)swi(3);
      puVar7 = (undefined *)(*pcVar1)();
      return puVar7;
    }
    lVar5 = **(longlong **)(lVar3 + 0x38);
    if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
      lVar5 = FUN_7ffe998ced40(lVar5);
    }
    lVar6 = FUN_7ffe99742ec0(0,lVar5,lVar6);
    while (lVar6 != 0) {
      cVar2 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
      if (cVar2 == '\0') {
        if (lVar6 != 0) {
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
        }
        return (undefined *)0x0;
      }
      if (lVar6 == 0) goto LAB_7ffe9ab8565e;
      lVar5 = *(longlong *)(*(longlong *)(lVar3 + 0x38) + 0x18);
      if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
        lVar5 = FUN_7ffe998ced40(lVar5);
      }
      puVar7 = (undefined *)FUN_7ffe99742ec0(0,lVar5,lVar6);
      cVar2 = (**(code **)(lVar4 + 0x18))
                        (*(undefined8 *)(lVar4 + 0x40),puVar7,*(undefined8 *)(lVar4 + 0x28));
      if (cVar2 != '\0') {
        if (lVar6 != 0) {
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
        }
        return puVar7;
      }
    }
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  puVar7 = (undefined *)(*pcVar1)();
  return puVar7;
}

