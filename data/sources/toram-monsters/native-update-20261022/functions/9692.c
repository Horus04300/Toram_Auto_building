
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MobPropertyBase_GetValue(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  undefined *puVar7;
  undefined8 uVar8;
  
  if (DAT_7ffe9cadd788 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906868);
    DAT_7ffe9cadd788 = '\x01';
  }
  lVar6 = _DAT_7ffe9c906868;
  lVar5 = *(longlong *)(self + 0x10);
  if (*(longlong *)(_DAT_7ffe9c906868 + 0x38) == 0) {
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    if (*(longlong *)(lVar6 + 0x38) == 0) {
      FUN_7ffe998cedc0(lVar6);
    }
  }
  if (lVar5 == 0) {
    uVar8 = func_0x7ffe9996d5b0(0x7ffe9c94f360);
    uVar8 = FUN_7ffe9b661bf0(uVar8,0);
    FUN_7ffe9996d760(uVar8,lVar6);
  }
  else {
    lVar4 = *(longlong *)(*(longlong *)(lVar6 + 0x38) + 8);
    if ((*(byte *)(lVar4 + 0x135) & 1) == 0) {
      lVar4 = FUN_7ffe998ced40(lVar4);
    }
    lVar4 = func_0x7ffe9996c920(lVar5,lVar4);
    if (lVar4 != 0) {
      lVar5 = (*(longlong **)(lVar6 + 0x38))[2];
      if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
        lVar5 = FUN_7ffe998ced40(lVar5);
      }
      iVar3 = FUN_7ffe99742ec0(0,lVar5,lVar4);
      if (iVar3 < 1) {
        return (undefined *)0x0;
      }
      lVar5 = *(longlong *)(*(longlong *)(lVar6 + 0x38) + 8);
      if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
        lVar5 = FUN_7ffe998ced40(lVar5);
      }
      puVar7 = (undefined *)FUN_7ffe99749320(0,lVar5,lVar4,0);
      return puVar7;
    }
    lVar4 = **(longlong **)(lVar6 + 0x38);
    if ((*(byte *)(lVar4 + 0x135) & 1) == 0) {
      lVar4 = FUN_7ffe998ced40(lVar4);
    }
    lVar5 = FUN_7ffe99742ec0(0,lVar4,lVar5);
    if (lVar5 == 0) goto LAB_7ffe9ab854a9;
    cVar2 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
    if (cVar2 == '\0') {
      if (lVar5 == 0) {
        return (undefined *)0x0;
      }
      FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      return (undefined *)0x0;
    }
    if (lVar5 != 0) {
      lVar6 = *(longlong *)(*(longlong *)(lVar6 + 0x38) + 0x38);
      if ((*(byte *)(lVar6 + 0x135) & 1) == 0) {
        lVar6 = FUN_7ffe998ced40(lVar6);
      }
      puVar7 = (undefined *)FUN_7ffe99742ec0(0,lVar6,lVar5);
      if (lVar5 != 0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
      return puVar7;
    }
  }
  FUN_7ffe9996d7a0();
LAB_7ffe9ab854a9:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  puVar7 = (undefined *)(*pcVar1)();
  return puVar7;
}

