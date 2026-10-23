
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkillTextManager_Initialize(undefined *self,undefined *binary,undefined *methodInfo)

{
  code *pcVar1;
  ulonglong uVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  longlong lVar6;
  longlong lVar7;
  ulonglong uVar8;
  longlong lVar9;
  longlong *plVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  int iVar15;
  longlong lStack_f0;
  ulonglong uStack_e8;
  longlong lStack_e0;
  undefined8 uStack_d8;
  longlong *plStack_d0;
  longlong lStack_c8;
  longlong lStack_c0;
  ulonglong uStack_b8;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined *puStack_a8;
  undefined8 uStack_98;
  undefined8 uStack_90;
  ulonglong uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_50;
  undefined8 uStack_48;
  ulonglong uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  
  puStack_a8 = self;
  if (DAT_7fff625e156c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b500);
    FUN_7fff5f47d450(&DAT_7fff6240cb00);
    FUN_7fff5f47d450(&DAT_7fff6240ddb0);
    FUN_7fff5f47d450(&DAT_7fff6240de80);
    FUN_7fff5f47d450(&DAT_7fff6240db40);
    FUN_7fff5f47d450(&DAT_7fff6240e1c0);
    FUN_7fff5f47d450(&DAT_7fff6240ce40);
    FUN_7fff5f47d450(&DAT_7fff6240e290);
    FUN_7fff5f47d450(&DAT_7fff6241bbe8);
    FUN_7fff5f47d450(&DAT_7fff62440918);
    FUN_7fff5f47d450(&DAT_7fff624409e0);
    FUN_7fff5f47d450(0x7fff62440aa0);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(0x7fff624726e8);
    FUN_7fff5f47d450(&DAT_7fff624717c0);
    FUN_7fff5f47d450(&DAT_7fff62453610);
    DAT_7fff625e156c = '\x01';
  }
  iVar15 = 0;
  lStack_f0 = 0;
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  self[0x11] = 0;
  lVar6 = func_0x7fff5f44ff00(_DAT_7fff6241bbe8);
  FUN_7fff6082b860(lVar6,_DAT_7fff6240db40);
  lStack_c8 = lVar6;
  lVar7 = func_0x7fff5f44ff00(_DAT_7fff6241bbe8);
  lStack_e0 = lVar7;
  FUN_7fff6082b860(lVar7,_DAT_7fff6240db40);
  lStack_c0 = lVar7;
  uVar8 = func_0x7fff5f44ff00(_DAT_7fff6241bbe8);
  uStack_e8 = uVar8;
  FUN_7fff6082b860(uVar8,_DAT_7fff6240db40);
  uStack_b8 = uVar8;
  if (*(longlong *)(self + 0x18) != 0) {
    FUN_7fff607d86f0(*(longlong *)(self + 0x18),_DAT_7fff6240cb00);
    lVar9 = func_0x7fff5f44ff00(_DAT_7fff624717c0);
    FUN_7fff60fcae90(lVar9,binary,0);
    uStack_d8 = 0;
    plStack_d0 = &lStack_f0;
    lStack_f0 = lVar9;
    plVar10 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6244b500);
    FUN_7fff60fd77f0(plVar10,lVar9,0);
    if (plVar10 == (longlong *)0x0) {
LAB_7fff5f565c67:
      FUN_7fff5f47d660();
      FUN_7fff5f40a410();
LAB_7fff5f565c73:
      FUN_7fff5f47d660();
LAB_7fff5f565c78:
      FUN_7fff5f47d660();
    }
    else {
      iVar4 = (**(code **)(*plVar10 + 0x228))(plVar10,*(undefined8 *)(*plVar10 + 0x230));
      while (iVar15 < iVar4) {
        if (plVar10 == (longlong *)0x0) {
LAB_7fff5f565c62:
          FUN_7fff5f47d660();
          goto LAB_7fff5f565c67;
        }
        uVar5 = (**(code **)(*plVar10 + 0x228))(plVar10,*(undefined8 *)(*plVar10 + 0x230));
        if (plVar10 == (longlong *)0x0) {
LAB_7fff5f565c5d:
          FUN_7fff5f47d660();
          goto LAB_7fff5f565c62;
        }
        cVar3 = (**(code **)(*plVar10 + 0x1d8))(plVar10,*(undefined8 *)(*plVar10 + 0x1e0));
        if (plVar10 == (longlong *)0x0) {
LAB_7fff5f565c58:
          FUN_7fff5f47d660();
          goto LAB_7fff5f565c5d;
        }
        uVar11 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
        if (cVar3 == '\0') {
          if (lVar6 == 0) {
LAB_7fff5f565c53:
            FUN_7fff5f47d660();
            goto LAB_7fff5f565c58;
          }
          FUN_7fff608690c0(lVar6,uVar5,uVar11,_DAT_7fff6240e290);
LAB_7fff5f565904:
          iVar15 = iVar15 + 1;
        }
        else if (cVar3 == '\x01') {
          if (lVar7 == 0) goto LAB_7fff5f565c4e;
          FUN_7fff608690c0(lVar7,uVar5,uVar11,_DAT_7fff6240e290);
          iVar15 = iVar15 + 1;
        }
        else {
          if (cVar3 != '\x02') goto LAB_7fff5f565904;
          if (uVar8 == 0) {
            FUN_7fff5f47d660();
LAB_7fff5f565c4e:
            FUN_7fff5f47d660();
            goto LAB_7fff5f565c53;
          }
          FUN_7fff608690c0(uVar8,uVar5,uVar11,_DAT_7fff6240e290);
          iVar15 = iVar15 + 1;
        }
      }
      if (plVar10 != (longlong *)0x0) {
        FUN_7fff5f253010(0,_DAT_7fff624413c0);
      }
      if (lVar6 == 0) goto LAB_7fff5f565c93;
      FUN_7fff607d9c20(&uStack_50,lVar6,_DAT_7fff6240de80);
      uStack_98 = uStack_50;
      uStack_90 = uStack_48;
      uStack_88 = uStack_40;
      uStack_80 = uStack_38;
      uStack_78 = uStack_30;
      while( true ) {
        do {
          cVar3 = FUN_7fff609497d0(&uStack_98,_DAT_7fff624409e0);
          if (cVar3 == '\0') {
            func_0x7fff5f4d3920(&uStack_98,_DAT_7fff62440918);
            if (*plStack_d0 != 0) {
              FUN_7fff5f253010(0,_DAT_7fff624413c0);
            }
            self[0x10] = 1;
            self[0x12] = 0;
            return;
          }
          uStack_b8 = uStack_88;
          uStack_b0 = (undefined4)uStack_80;
          uStack_ac = uStack_80._4_4_;
          if (lVar7 == 0) goto LAB_7fff5f565c82;
          cVar3 = FUN_7fff6082f170(lVar7,uStack_88 & 0xffffffff,_DAT_7fff6240ddb0);
          uVar2 = uStack_b8;
        } while (cVar3 == '\0');
        if (uVar8 == 0) break;
        cVar3 = FUN_7fff6082f170(uVar8,uStack_b8 & 0xffffffff,_DAT_7fff6240ddb0);
        lVar9 = *(longlong *)(puStack_a8 + 0x18);
        if (cVar3 == '\0') {
          uVar11 = FUN_7fff6083faa0(lVar6,uVar2 & 0xffffffff,_DAT_7fff6240e1c0);
          uVar12 = FUN_7fff6083faa0(lVar7,uVar2 & 0xffffffff,_DAT_7fff6240e1c0);
          uVar13 = func_0x7fff5f44ff00(_DAT_7fff62453610);
          FUN_7fff5f564d10(uVar13,uVar2 & 0xffffffff,uVar11,uVar12,0);
          if (lVar9 == 0) goto LAB_7fff5f565c78;
          FUN_7fff608690c0(lVar9,uVar2 & 0xffffffff,uVar13,_DAT_7fff6240ce40);
          lVar7 = lStack_e0;
        }
        else {
          uVar11 = FUN_7fff6083faa0(lVar6,uVar2 & 0xffffffff,_DAT_7fff6240e1c0);
          uVar12 = FUN_7fff6083faa0(lVar7,uVar2 & 0xffffffff,_DAT_7fff6240e1c0);
          uVar13 = FUN_7fff6083faa0(uStack_e8,uVar2 & 0xffffffff,_DAT_7fff6240e1c0);
          uVar14 = func_0x7fff5f44ff00(_DAT_7fff62453610);
          FUN_7fff5f564d90(uVar14,uVar2 & 0xffffffff,uVar11,uVar12,uVar13,0);
          if (lVar9 == 0) goto LAB_7fff5f565c73;
          FUN_7fff608690c0(lVar9,uVar2 & 0xffffffff,uVar14,_DAT_7fff6240ce40);
          uVar8 = uStack_e8;
          lVar7 = lStack_e0;
        }
      }
    }
    FUN_7fff5f47d660();
LAB_7fff5f565c82:
    FUN_7fff5f47d660();
  }
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
LAB_7fff5f565c93:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

