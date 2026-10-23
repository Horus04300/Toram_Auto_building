
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ItemTextManager_Initialize(undefined *self,undefined *binary,undefined *methodInfo)

{
  code *pcVar1;
  ulonglong uVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  longlong lVar6;
  ulonglong uVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined8 uVar10;
  undefined *description;
  undefined *name;
  undefined *self_00;
  int iVar11;
  longlong *plStack_108;
  undefined8 uStack_100;
  longlong **pplStack_f8;
  longlong lStack_f0;
  ulonglong uStack_e8;
  longlong lStack_e0;
  undefined8 uStack_d8;
  longlong *plStack_d0;
  longlong lStack_c8;
  ulonglong uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined *puStack_b0;
  longlong *plStack_a0;
  undefined8 uStack_98;
  ulonglong uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  longlong *plStack_58;
  undefined8 uStack_50;
  ulonglong uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  puStack_b0 = self;
  if (DAT_7fff625e1514 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b500);
    FUN_7fff5f47d450(&DAT_7fff624026e0);
    FUN_7fff5f47d450(&DAT_7fff6240ddb0);
    FUN_7fff5f47d450(&DAT_7fff6240de80);
    FUN_7fff5f47d450(&DAT_7fff6240db40);
    FUN_7fff5f47d450(&DAT_7fff6240e1c0);
    FUN_7fff5f47d450(&DAT_7fff62402a20);
    FUN_7fff5f47d450(&DAT_7fff6240e290);
    FUN_7fff5f47d450(&DAT_7fff6241bbe8);
    FUN_7fff5f47d450(&DAT_7fff62440918);
    FUN_7fff5f47d450(&DAT_7fff624409e0);
    FUN_7fff5f47d450(0x7fff62440aa0);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff62457620);
    FUN_7fff5f47d450(0x7fff624726e8);
    FUN_7fff5f47d450(&DAT_7fff62434388);
    FUN_7fff5f47d450(&DAT_7fff624717c0);
    FUN_7fff5f47d450(&DAT_7fff623fa248);
    FUN_7fff5f47d450(&DAT_7fff624292a8);
    FUN_7fff5f47d450(&DAT_7fff62440c88);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e1514 = '\x01';
  }
  iVar11 = 0;
  lStack_f0 = 0;
  plStack_108 = (longlong *)0x0;
  plStack_a0 = (longlong *)0x0;
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_80 = 0;
  self[0x11] = 0;
  lVar6 = func_0x7fff5f44ff00(_DAT_7fff6241bbe8);
  lStack_e0 = lVar6;
  FUN_7fff6082b860(lVar6,_DAT_7fff6240db40);
  lStack_c8 = lVar6;
  uVar7 = func_0x7fff5f44ff00(_DAT_7fff6241bbe8);
  uStack_e8 = uVar7;
  FUN_7fff6082b860(uVar7,_DAT_7fff6240db40);
  uStack_c0 = uVar7;
  if (*(longlong *)(self + 0x18) == 0) goto LAB_7fff5f558fcb;
  FUN_7fff607d86f0(*(longlong *)(self + 0x18),_DAT_7fff624026e0);
  lVar8 = func_0x7fff5f44ff00(_DAT_7fff624717c0);
  FUN_7fff60fcae90(lVar8,binary,0);
  uStack_d8 = 0;
  plStack_d0 = &lStack_f0;
  lStack_f0 = lVar8;
  plVar9 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6244b500);
  FUN_7fff60fd77f0(plVar9,lVar8,0);
  uStack_100 = 0;
  pplStack_f8 = &plStack_108;
  plStack_108 = plVar9;
  if (plVar9 != (longlong *)0x0) {
    iVar4 = (**(code **)(*plVar9 + 0x228))(plVar9,*(undefined8 *)(*plVar9 + 0x230));
LAB_7fff5f558bb3:
    do {
      if (iVar4 <= iVar11) goto LAB_7fff5f558ccf;
      if (plStack_108 == (longlong *)0x0) {
LAB_7fff5f558f9a:
        FUN_7fff5f47d660();
        break;
      }
      uVar5 = (**(code **)(*plStack_108 + 0x228))(plStack_108,*(undefined8 *)(*plStack_108 + 0x230))
      ;
      if (plStack_108 == (longlong *)0x0) {
LAB_7fff5f558f95:
        FUN_7fff5f47d660();
        goto LAB_7fff5f558f9a;
      }
      cVar3 = (**(code **)(*plStack_108 + 0x1d8))(plStack_108,*(undefined8 *)(*plStack_108 + 0x1e0))
      ;
      if (plStack_108 == (longlong *)0x0) {
LAB_7fff5f558f90:
        FUN_7fff5f47d660();
        goto LAB_7fff5f558f95;
      }
      lVar8 = (**(code **)(*plStack_108 + 0x298))(plStack_108,*(undefined8 *)(*plStack_108 + 0x2a0))
      ;
      if (cVar3 == '\0') {
        if (lVar6 != 0) {
          FUN_7fff608690c0(lVar6,uVar5,lVar8);
          goto LAB_7fff5f558cc1;
        }
LAB_7fff5f558f8b:
        FUN_7fff5f47d660();
        goto LAB_7fff5f558f90;
      }
      if (cVar3 == '\x01') {
        if (lVar8 != 0) {
          lVar8 = FUN_7fff60e78ac0(lVar8,_DAT_7fff62440c88,_DAT_7fff623fa248,0);
          if (lVar8 != 0) {
            uVar10 = FUN_7fff60e78ac0(lVar8,_DAT_7fff624292a8,_DAT_7fff623fa248,0);
            if (uVar7 != 0) {
              FUN_7fff608690c0(uVar7,uVar5,uVar10);
              iVar11 = iVar11 + 1;
              goto LAB_7fff5f558bb3;
            }
            FUN_7fff5f47d660();
          }
          FUN_7fff5f47d660();
        }
        FUN_7fff5f47d660();
        goto LAB_7fff5f558f8b;
      }
LAB_7fff5f558cc1:
      iVar11 = iVar11 + 1;
    } while( true );
  }
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
LAB_7fff5f558fab:
  FUN_7fff5f47d660();
LAB_7fff5f558fb0:
  FUN_7fff5f47d660();
LAB_7fff5f558fb5:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  goto LAB_7fff5f558fc0;
LAB_7fff5f558ccf:
  if (plStack_108 != (longlong *)0x0) {
    FUN_7fff5f253010(0,_DAT_7fff624413c0);
  }
  if (lVar6 != 0) {
    FUN_7fff607d9c20(&plStack_58,lVar6,_DAT_7fff6240de80);
    plStack_a0 = plStack_58;
    uStack_98 = uStack_50;
    uStack_90 = uStack_48;
    uStack_88 = uStack_40;
    uStack_80 = uStack_38;
    uStack_100 = 0;
    pplStack_f8 = &plStack_a0;
    while( true ) {
      do {
        cVar3 = FUN_7fff609497d0(&plStack_a0,_DAT_7fff624409e0);
        if (cVar3 == '\0') {
          func_0x7fff5f4d3920(&plStack_a0,_DAT_7fff62440918);
          if (*plStack_d0 != 0) {
            FUN_7fff5f253010(0,_DAT_7fff624413c0);
          }
          self[0x10] = 1;
          self[0x12] = 0;
          return;
        }
        uStack_c0 = uStack_90;
        uStack_b8 = (undefined4)uStack_88;
        uStack_b4 = uStack_88._4_4_;
        if (*(longlong *)(self + 0x20) == 0) goto LAB_7fff5f558fb5;
        cVar3 = FUN_7fff60ad29f0(*(longlong *)(self + 0x20),uStack_90 & 0xffffffff,_DAT_7fff62434388
                                );
        uVar2 = uStack_c0;
        description = _DAT_7fff623f7f60;
      } while (cVar3 != '\0');
      if (uVar7 == 0) break;
      cVar3 = FUN_7fff6082f170(uVar7,uStack_c0 & 0xffffffff,_DAT_7fff6240ddb0);
      if (cVar3 == '\0') {
        lVar8 = *(longlong *)(self + 0x18);
      }
      else {
        description = (undefined *)FUN_7fff6083faa0(uVar7,uVar2 & 0xffffffff,_DAT_7fff6240e1c0);
        lVar8 = *(longlong *)(puStack_b0 + 0x18);
      }
      name = (undefined *)FUN_7fff6083faa0(lVar6,uVar2 & 0xffffffff,_DAT_7fff6240e1c0);
      self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62457620);
      TextManagerDataBase__ctor(self_00,name,description,(undefined *)0x0);
      if (lVar8 == 0) goto LAB_7fff5f558fab;
      FUN_7fff608690c0(lVar8,uVar2 & 0xffffffff,self_00);
      lVar6 = lStack_e0;
      uVar7 = uStack_e8;
    }
    goto LAB_7fff5f558fb0;
  }
LAB_7fff5f558fc0:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
LAB_7fff5f558fcb:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

