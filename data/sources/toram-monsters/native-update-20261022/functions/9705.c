
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobPropertyCut_get_CutMagicAttack(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  int iVar8;
  
  if (DAT_7ffe9cadd78d == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c91bd90);
    FUN_7ffe9996d590(&DAT_7ffe9c93f2b8);
    FUN_7ffe9996d590(&DAT_7ffe9c968230);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1548);
    DAT_7ffe9cadd78d = '\x01';
  }
  uVar6 = *(undefined8 *)(self + 0x10);
  if (*(int *)(_DAT_7ffe9c8f1548 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_7ffe9c8f1548 + 0xb8) + 0x10);
  if (lVar5 == 0) {
    if (*(int *)(_DAT_7ffe9c8f1548 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    uVar7 = **(undefined8 **)(_DAT_7ffe9c8f1548 + 0xb8);
    lVar5 = func_0x7ffe99940040(_DAT_7ffe9c93f2b8);
    FUN_7ffe9af15670(lVar5,uVar7,_DAT_7ffe9c968230,0);
    *(longlong *)(*(longlong *)(_DAT_7ffe9c8f1548 + 0xb8) + 0x10) = lVar5;
    il2cpp_write_barrier_0();
  }
  lVar2 = _DAT_7ffe9c91bd90;
  if (*(longlong *)(_DAT_7ffe9c91bd90 + 0x38) == 0) {
    FUN_7ffe998cedc0(_DAT_7ffe9c91bd90);
  }
  lVar5 = FUN_7ffe9ab8c200(uVar6,lVar5,*(undefined8 *)(*(longlong *)(lVar2 + 0x38) + 0x10));
  if (DAT_7ffe9cae459e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92bb10,0);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c954838);
    FUN_7ffe9996d590(&DAT_7ffe9c95a168);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    DAT_7ffe9cae459e = '\x01';
  }
  if (lVar5 == 0) {
    uVar6 = func_0x7ffe9996d5b0(0x7ffe9c94f360);
    uVar6 = FUN_7ffe9b661bf0(uVar6,0);
    uVar7 = func_0x7ffe9996d5b0(&DAT_7ffe9c92bb10);
    FUN_7ffe9996d760(uVar6,uVar7);
LAB_7ffe9b6619ec:
    uVar6 = _DAT_7ffe9c92bb10;
    uVar7 = func_0x7ffe9996d380();
    FUN_7ffe9996d760(uVar7,uVar6);
LAB_7ffe9b661a03:
    FUN_7ffe9996d7a0();
  }
  else {
    iVar8 = 0;
    lVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c954838,lVar5);
    while (lVar5 != 0) {
      cVar3 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
      if (cVar3 == '\0') {
        if (lVar5 != 0) {
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
        }
        return iVar8;
      }
      if (lVar5 == 0) goto LAB_7ffe9b661a03;
      iVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c95a168);
      if (0xffffffff < (ulonglong)((longlong)iVar8 + (longlong)iVar4 + 0x80000000))
      goto LAB_7ffe9b6619ec;
      iVar8 = iVar8 + iVar4;
    }
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  iVar8 = (*pcVar1)();
  return iVar8;
}

