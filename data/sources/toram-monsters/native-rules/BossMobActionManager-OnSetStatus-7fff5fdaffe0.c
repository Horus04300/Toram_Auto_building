
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BossMobActionManager_OnSetStatus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  code *pcVar5;
  char cVar6;
  undefined2 uVar7;
  int iVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined8 *puVar11;
  longlong *plVar12;
  undefined8 uVar13;
  ushort uVar14;
  longlong *unaff_RSI;
  ulonglong uVar15;
  longlong *unaff_R14;
  undefined4 extraout_XMM0_Da;
  undefined4 uVar16;
  undefined8 uStack_80;
  undefined8 uStack_78;
  ulonglong uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  ulonglong uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  if (DAT_7fff625e491d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624510d0);
    FUN_7fff5f47d450(&DAT_7fff6245a0e0);
    FUN_7fff5f47d450(&DAT_7fff6245a1a8);
    FUN_7fff5f47d450(&DAT_7fff623f9b58);
    FUN_7fff5f47d450(&DAT_7fff623fa448);
    FUN_7fff5f47d450(&DAT_7fff624306e0);
    FUN_7fff5f47d450(&DAT_7fff624307a8);
    FUN_7fff5f47d450(0x7fff62430868);
    FUN_7fff5f47d450(&DAT_7fff6243dd98);
    FUN_7fff5f47d450(&DAT_7fff624465a0);
    FUN_7fff5f47d450(0x7fff6246c428);
    FUN_7fff5f47d450(0x7fff6246c4f8);
    FUN_7fff5f47d450(&DAT_7fff6245c360);
    DAT_7fff625e491d = '\x01';
  }
  cVar6 = FUN_7fff5fe6a760(*(undefined8 *)(self + 0x70),0x10);
  if (cVar6 == '\0') {
    unaff_R14 = *(longlong **)(self + 0x70);
    uVar3 = *(undefined8 *)(self + 0x80);
    uVar4 = *(undefined8 *)(self + 0x88);
    lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
    if (lVar9 != 0) {
      uVar7 = FUN_7fff6010c360(lVar9,0);
      lVar9 = func_0x7fff5f44ff00(_DAT_7fff624510d0);
      if (DAT_7fff625e4926 == '\0') {
        FUN_7fff5f47d450(&DAT_7fff62406160);
        FUN_7fff5f47d450(&DAT_7fff6241a798);
        DAT_7fff625e4926 = '\x01';
      }
      uVar10 = func_0x7fff5f44ff00(_DAT_7fff6241a798);
      FUN_7fff6082b860(uVar10,_DAT_7fff62406160);
      *(undefined8 *)(lVar9 + 0x30) = uVar10;
      thunk_FUN_7fff5f491fd0();
      func_0x7fff5f4d3920(lVar9,0);
      *(undefined2 *)(lVar9 + 0x28) = uVar7;
      *(longlong **)(lVar9 + 0x10) = unaff_R14;
      thunk_FUN_7fff5f491fd0();
      *(undefined8 *)(lVar9 + 0x18) = uVar3;
      thunk_FUN_7fff5f491fd0();
      *(undefined8 *)(lVar9 + 0x20) = uVar4;
      thunk_FUN_7fff5f491fd0();
      plVar1 = (longlong *)(self + 0x158);
      *plVar1 = lVar9;
      thunk_FUN_7fff5f491fd0();
      plVar12 = (longlong *)*plVar1;
      unaff_RSI = *(longlong **)(self + 0x78);
      unaff_R14 = plVar1;
      if (plVar12 != (longlong *)0x0) {
        lVar9 = *plVar12;
        if (*(ushort *)(lVar9 + 0x12e) != 0) {
          uVar14 = 0;
          do {
            if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar14 * 0x10) ==
                _DAT_7fff624465a0) {
              puVar11 = (undefined8 *)
                        (lVar9 + 0x138 +
                        (longlong)
                        (*(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar14 * 0x10) + 0x14
                        ) * 0x10);
              goto LAB_7fff5fdb0229;
            }
            uVar14 = uVar14 + 1;
          } while (uVar14 < *(ushort *)(lVar9 + 0x12e));
        }
        puVar11 = (undefined8 *)FUN_7fff5f3de400(plVar12,_DAT_7fff624465a0,0x14);
LAB_7fff5fdb0229:
        (*(code *)*puVar11)(plVar12,unaff_RSI,puVar11[1]);
        if (*(longlong *)(self + 0x168) != 0) {
          iVar8 = func_0x7fff607e24e0(*(longlong *)(self + 0x168),_DAT_7fff6245a1a8);
          if (0 < iVar8) {
            if (*(longlong *)(self + 0x168) == 0) goto LAB_7fff5fdb04e3;
            FUN_7fff607d9c20(&uStack_58,*(longlong *)(self + 0x168),_DAT_7fff6245a0e0);
            uStack_80 = uStack_58;
            uStack_78 = uStack_50;
            uStack_70 = uStack_48;
            uStack_68 = uStack_40;
            uStack_60 = uStack_38;
            while (cVar6 = FUN_7fff60941a70(&uStack_80,_DAT_7fff624307a8), uVar3 = uStack_68,
                  unaff_RSI = _DAT_7fff6243dd98, cVar6 != '\0') {
              self = (undefined *)*plVar1;
              uVar15 = uStack_70 & 0xff;
              unaff_R14 = plVar1;
              if (self == (undefined *)0x0) goto LAB_7fff5fdb04e9;
              lVar9 = func_0x7fff5f47c7e0(self,_DAT_7fff6243dd98);
              unaff_R14 = _DAT_7fff6243dd98;
              uVar16 = extraout_XMM0_Da;
              if (lVar9 == 0) goto LAB_7fff5fdb04fa;
              plVar12 = (longlong *)func_0x7fff5f47c7e0(self,_DAT_7fff6243dd98);
              unaff_RSI = (longlong *)0x0;
              if (plVar12 == (longlong *)0x0) goto LAB_7fff5fdb04ef;
              lVar9 = *plVar12;
              if (*(ushort *)(lVar9 + 0x12e) != 0) {
                uVar14 = 0;
                do {
                  if (*(longlong **)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar14 * 0x10) ==
                      _DAT_7fff6243dd98) {
                    puVar11 = (undefined8 *)
                              (lVar9 + 0x138 +
                              (longlong)
                              (*(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar14 * 0x10)
                              + 1) * 0x10);
                    goto LAB_7fff5fdb0398;
                  }
                  uVar14 = uVar14 + 1;
                } while (uVar14 < *(ushort *)(lVar9 + 0x12e));
              }
              puVar11 = (undefined8 *)FUN_7fff5f3de400(plVar12,_DAT_7fff6243dd98,1);
LAB_7fff5fdb0398:
              (*(code *)*puVar11)(plVar12,uVar15,uVar3,puVar11[1]);
            }
            func_0x7fff5f4d3920(&uStack_80,_DAT_7fff624306e0);
          }
          return;
        }
      }
    }
  }
  else {
    lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
    if ((lVar9 != 0) && (plVar1 = *(longlong **)(lVar9 + 0x28), plVar1 != (longlong *)0x0)) {
      if ((*(byte *)(_DAT_7fff623fa448 + 0x130) <= *(byte *)(*plVar1 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff623fa448 + 0x130) * 8)
          == _DAT_7fff623fa448)) {
        uVar3 = *(undefined8 *)(self + 0x70);
        uVar4 = *(undefined8 *)(self + 0x80);
        uVar10 = *(undefined8 *)(self + 0x88);
        uVar16 = *(undefined4 *)((longlong)plVar1 + 0x74);
        uVar2 = *(undefined4 *)((longlong)plVar1 + 0x7c);
        lVar9 = plVar1[0xf];
        uVar13 = func_0x7fff5f44ff00(_DAT_7fff623f9b58);
        FUN_7fff5fe15730(uVar13,uVar3,uVar4,uVar10,uVar16,uVar2,(int)lVar9,0);
        *(undefined8 *)(self + 0x158) = uVar13;
        thunk_FUN_7fff5f491fd0();
        return;
      }
      FUN_7fff5f47c810(plVar1);
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
  }
LAB_7fff5fdb04e3:
  FUN_7fff5f47d660();
LAB_7fff5fdb04e9:
  FUN_7fff5f47d660();
LAB_7fff5fdb04ef:
  uVar16 = FUN_7fff5f47c810(self,unaff_R14);
LAB_7fff5fdb04fa:
  FUN_7fff5f47c810(uVar16,unaff_RSI);
  FUN_7fff5f40a410();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

