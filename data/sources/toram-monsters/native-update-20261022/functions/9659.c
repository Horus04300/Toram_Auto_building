
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MobPropertyManager_GetMobPropertyMasters(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined *puVar7;
  longlong lStackX_8;
  undefined8 uStack_38;
  longlong *plStack_30;
  longlong lStack_28;
  undefined8 uStack_20;
  longlong *plStack_18;
  longlong lStack_10;
  
  if (DAT_7ffe9cadd780 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92a9b0);
    FUN_7ffe9996d590(&DAT_7ffe9c92ab38);
    FUN_7ffe9996d590(&DAT_7ffe9c9445f8);
    FUN_7ffe9996d590(&DAT_7ffe9c9446c0);
    FUN_7ffe9996d590(0x7ffe9c944780);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c955288);
    FUN_7ffe9996d590(&DAT_7ffe9c95ad60);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c93d430);
    FUN_7ffe9996d590(&DAT_7ffe9c93d5b8);
    FUN_7ffe9996d590(&DAT_7ffe9c93d370);
    FUN_7ffe9996d590(&DAT_7ffe9c96de78);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc0c0);
    DAT_7ffe9cadd780 = '\x01';
  }
  uStack_20 = 0;
  plStack_18 = (longlong *)0x0;
  lStack_10 = 0;
  lStackX_8 = 0;
  lVar4 = func_0x7ffe99940040(_DAT_7ffe9c96de78);
  FUN_7ffe9af8a010(lVar4,_DAT_7ffe9c93d370);
  if ((*(longlong *)(self + 0x10) != 0) &&
     (iVar3 = func_0x7ffe9acd8120(*(longlong *)(self + 0x10),_DAT_7ffe9c92a9b0), 0 < iVar3)) {
    if ((*(longlong *)(self + 0x10) == 0) ||
       (lVar5 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x10),_DAT_7ffe9c92ab38), lVar5 == 0))
    goto LAB_7ffe9a37ab9e;
    FUN_7ffe9af415c0(&uStack_38,lVar5,_DAT_7ffe9c8fc0c0);
    uStack_20 = uStack_38;
    plStack_18 = plStack_30;
    lStack_10 = lStack_28;
    while (cVar2 = FUN_7ffe9ae37290(&uStack_20,_DAT_7ffe9c9446c0), cVar2 != '\0') {
      if (lStack_10 == 0) goto LAB_7ffe9a37abbf;
      if (*(longlong *)(lStack_10 + 0x10) == 0) goto LAB_7ffe9a37abba;
      lStackX_8 = FUN_7ffe99742ec0(0,_DAT_7ffe9c955288);
      uStack_38 = 0;
      plStack_30 = &lStackX_8;
      while( true ) {
        if (lStackX_8 == 0) goto LAB_7ffe9a37abaf;
        cVar2 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
        if (cVar2 == '\0') break;
        if (lStackX_8 == 0) goto LAB_7ffe9a37abaa;
        uVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c95ad60);
        if (lVar4 == 0) goto LAB_7ffe9a37aba4;
        FUN_7ffe99743100(lVar4,uVar6,_DAT_7ffe9c93d430);
      }
      if (lStackX_8 != 0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
    }
    func_0x7ffe999c3920(&uStack_20,_DAT_7ffe9c9445f8);
  }
  if (lVar4 != 0) {
    puVar7 = (undefined *)FUN_7ffe9af89d20(lVar4,_DAT_7ffe9c93d5b8);
    return puVar7;
  }
LAB_7ffe9a37ab9e:
  FUN_7ffe9996d7a0();
LAB_7ffe9a37aba4:
  FUN_7ffe9996d7a0();
LAB_7ffe9a37abaa:
  FUN_7ffe9996d7a0();
LAB_7ffe9a37abaf:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a37abba:
  FUN_7ffe9996d7a0();
LAB_7ffe9a37abbf:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  puVar7 = (undefined *)(*pcVar1)();
  return puVar7;
}

