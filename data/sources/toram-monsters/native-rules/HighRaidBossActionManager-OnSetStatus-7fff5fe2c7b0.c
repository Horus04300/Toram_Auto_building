
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidBossActionManager_OnSetStatus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  char cVar6;
  ushort uVar7;
  int iVar8;
  longlong lVar9;
  undefined8 uVar10;
  longlong lVar11;
  longlong *plVar12;
  undefined8 *puVar13;
  longlong lVar14;
  ulonglong uVar15;
  undefined4 extraout_XMM0_Da;
  undefined4 uVar16;
  undefined8 uStack_70;
  undefined8 uStack_68;
  ulonglong uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  ulonglong uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  
  if (DAT_7fff625e4c8d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245a0e0);
    FUN_7fff5f47d450(&DAT_7fff6245a1a8);
    FUN_7fff5f47d450(&DAT_7fff624306e0);
    FUN_7fff5f47d450(&DAT_7fff624307a8);
    FUN_7fff5f47d450(0x7fff62430868);
    FUN_7fff5f47d450(&DAT_7fff62431f50);
    FUN_7fff5f47d450(&DAT_7fff6243dd98);
    FUN_7fff5f47d450(&DAT_7fff624465a0);
    FUN_7fff5f47d450(0x7fff6246c428);
    FUN_7fff5f47d450(0x7fff6246c4f8);
    DAT_7fff625e4c8d = '\x01';
  }
  lVar14 = *(longlong *)(self + 0x70);
  uVar2 = *(undefined8 *)(self + 0x80);
  uVar3 = *(undefined8 *)(self + 0x88);
  uVar16 = *(undefined4 *)(self + 0x160);
  lVar9 = func_0x7fff5f44ff00(_DAT_7fff62431f50);
  if (DAT_7fff625e4c9b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406160);
    FUN_7fff5f47d450(&DAT_7fff6241a798);
    DAT_7fff625e4c9b = '\x01';
  }
  uVar10 = func_0x7fff5f44ff00(_DAT_7fff6241a798);
  FUN_7fff6082b860(uVar10,_DAT_7fff62406160);
  *(undefined8 *)(lVar9 + 0x38) = uVar10;
  thunk_FUN_7fff5f491fd0();
  func_0x7fff5f4d3920(lVar9,0);
  *(longlong *)(lVar9 + 0x10) = lVar14;
  thunk_FUN_7fff5f491fd0();
  *(undefined8 *)(lVar9 + 0x18) = uVar2;
  thunk_FUN_7fff5f491fd0();
  *(undefined8 *)(lVar9 + 0x20) = uVar3;
  thunk_FUN_7fff5f491fd0();
  *(undefined4 *)(lVar9 + 0x30) = uVar16;
  plVar1 = (longlong *)(self + 0x158);
  *plVar1 = lVar9;
  thunk_FUN_7fff5f491fd0();
  if (*plVar1 != 0) {
    FUN_7fff5f252c60(0x14,_DAT_7fff624465a0,*plVar1,*(undefined8 *)(self + 0x78));
    if (*(longlong *)(self + 0x168) != 0) {
      iVar8 = func_0x7fff607e24e0(*(longlong *)(self + 0x168),_DAT_7fff6245a1a8);
      if (0 < iVar8) {
        if (*(longlong *)(self + 0x168) == 0) goto LAB_7fff5fe2cb2b;
        FUN_7fff607d9c20(&uStack_48,*(longlong *)(self + 0x168),_DAT_7fff6245a0e0);
        uStack_70 = uStack_48;
        uStack_68 = uStack_40;
        uStack_60 = uStack_38;
        uStack_58 = uStack_30;
        uStack_50 = uStack_28;
        while( true ) {
          cVar6 = FUN_7fff60941a70(&uStack_70,_DAT_7fff624307a8);
          uVar2 = uStack_58;
          lVar9 = _DAT_7fff6243dd98;
          if (cVar6 == '\0') break;
          lVar4 = *plVar1;
          uVar15 = uStack_60 & 0xff;
          if (lVar4 == 0) {
            FUN_7fff5f47d660();
LAB_7fff5fe2cb11:
            uVar16 = FUN_7fff5f47c810(lVar4,lVar14);
LAB_7fff5fe2cb1c:
            FUN_7fff5f47c810(uVar16,lVar9);
            FUN_7fff5f40a410();
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
          lVar11 = func_0x7fff5f47c7e0(lVar4,_DAT_7fff6243dd98);
          lVar14 = _DAT_7fff6243dd98;
          uVar16 = extraout_XMM0_Da;
          if (lVar11 == 0) goto LAB_7fff5fe2cb1c;
          plVar12 = (longlong *)func_0x7fff5f47c7e0(lVar4,_DAT_7fff6243dd98);
          lVar9 = 0;
          if (plVar12 == (longlong *)0x0) goto LAB_7fff5fe2cb11;
          lVar9 = *plVar12;
          uVar7 = 0;
          if (*(ushort *)(lVar9 + 0x12e) != 0) {
            do {
              if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar7 * 0x10) ==
                  _DAT_7fff6243dd98) {
                puVar13 = (undefined8 *)
                          (lVar9 + 0x138 +
                          (longlong)
                          (*(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar7 * 0x10) + 1)
                          * 0x10);
                goto LAB_7fff5fe2ca86;
              }
              uVar7 = uVar7 + 1;
            } while (uVar7 < *(ushort *)(lVar9 + 0x12e));
          }
          puVar13 = (undefined8 *)FUN_7fff5f3de400(plVar12,_DAT_7fff6243dd98,1);
LAB_7fff5fe2ca86:
          (*(code *)*puVar13)(plVar12,uVar15,uVar2,puVar13[1]);
        }
        func_0x7fff5f4d3920(&uStack_70,_DAT_7fff624306e0);
      }
      return;
    }
  }
LAB_7fff5fe2cb2b:
  FUN_7fff5f47d660();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

