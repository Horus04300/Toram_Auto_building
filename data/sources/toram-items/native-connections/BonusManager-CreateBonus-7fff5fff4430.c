
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
BonusManager_CreateBonus
          (undefined *self,undefined *bonusLines,byte exec,int stack,undefined *methodInfo)

{
  undefined1 uVar1;
  undefined4 uVar2;
  uint uVar3;
  longlong lVar4;
  longlong lVar5;
  code *pcVar6;
  char cVar7;
  int iVar8;
  undefined *puVar9;
  longlong lVar10;
  undefined8 uVar11;
  int iVar12;
  undefined8 uStack_a8;
  undefined8 *puStack_a0;
  longlong lStack_98;
  undefined8 uStack_90;
  undefined8 *puStack_88;
  longlong lStack_80;
  longlong lStack_78;
  undefined8 uStack_70;
  undefined8 *puStack_68;
  longlong lStack_60;
  
  if (DAT_7fff625e585a == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62409338);
    FUN_7fff5f47d450(&DAT_7fff6247a4c8);
    FUN_7fff5f47d450(&DAT_7fff6247a598);
    FUN_7fff5f47d450(&DAT_7fff62409408);
    FUN_7fff5f47d450(0x7fff6247a668);
    FUN_7fff5f47d450(0x7fff624094d8);
    FUN_7fff5f47d450(&DAT_7fff62452178);
    FUN_7fff5f47d450(&DAT_7fff624520b0);
    FUN_7fff5f47d450(0x7fff62452238);
    FUN_7fff5f47d450(&DAT_7fff6240f9e0);
    FUN_7fff5f47d450(&DAT_7fff624523c0);
    FUN_7fff5f47d450(&DAT_7fff62451f28);
    FUN_7fff5f47d450(&DAT_7fff62478730);
    FUN_7fff5f47d450(&DAT_7fff62437450);
    DAT_7fff625e585a = '\x01';
  }
  uStack_90 = 0;
  puStack_88 = (undefined8 *)0x0;
  lStack_80 = 0;
  puVar9 = BonusManager_CreateBonus(self,bonusLines,exec,(undefined *)0x0);
  if (stack < 2) {
    return puVar9;
  }
  lVar10 = func_0x7fff5f44ff00(_DAT_7fff62478730);
  FUN_7fff60a943d0(lVar10,_DAT_7fff62451f28);
  lStack_78 = lVar10;
  if ((puVar9 != (undefined *)0x0) && (*(longlong *)(puVar9 + 0x20) != 0)) {
    FUN_7fff60a8da60(&uStack_a8,*(longlong *)(puVar9 + 0x20),_DAT_7fff624523c0);
    uStack_70 = uStack_a8;
    puStack_68 = puStack_a0;
    lStack_60 = lStack_98;
    uStack_a8 = 0;
    puStack_a0 = &uStack_70;
    while (cVar7 = FUN_7fff60933290(&uStack_70,_DAT_7fff62409408), cVar7 != '\0') {
      if (lStack_60 == 0) goto LAB_7fff5fff48dd;
      uVar2 = *(undefined4 *)(lStack_60 + 0x10);
      iVar12 = *(int *)(lStack_60 + 0x14);
      uVar1 = *(undefined1 *)(lStack_60 + 0x18);
      uVar11 = func_0x7fff5f44ff00(_DAT_7fff62437450);
      FUN_7fff60011310(uVar11,uVar2,iVar12 * stack,uVar1,0);
      lVar5 = _DAT_7fff624520b0;
      if (lVar10 == 0) goto LAB_7fff5fff48d8;
      *(int *)(lVar10 + 0x1c) = *(int *)(lVar10 + 0x1c) + 1;
      lVar4 = *(longlong *)(lVar10 + 0x10);
      uVar3 = *(uint *)(lVar10 + 0x18);
      if (lVar4 == 0) goto LAB_7fff5fff48d3;
      if (uVar3 < *(uint *)(lVar4 + 0x18)) {
        *(uint *)(lVar10 + 0x18) = uVar3 + 1;
        if (*(uint *)(lVar4 + 0x18) <= uVar3) goto LAB_7fff5fff48cd;
        *(undefined8 *)(lVar4 + (longlong)(int)uVar3 * 8 + 0x20) = uVar11;
        thunk_FUN_7fff5f491fd0();
      }
      else {
        FUN_7fff60adfc70(lVar10,uVar11,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
      }
    }
    func_0x7fff5f4d3920(&uStack_70,_DAT_7fff62409338);
    lVar5 = *(longlong *)(puVar9 + 0x20);
    if (lVar5 != 0) {
      *(int *)(lVar5 + 0x1c) = *(int *)(lVar5 + 0x1c) + 1;
      iVar12 = *(int *)(lVar5 + 0x18);
      *(undefined4 *)(lVar5 + 0x18) = 0;
      if (0 < iVar12) {
        FUN_7fff61022d30(*(undefined8 *)(lVar5 + 0x10),0,iVar12,0);
      }
      if (*(longlong *)(puVar9 + 0x20) != 0) {
        func_0x7fff60adf9c0(*(longlong *)(puVar9 + 0x20),lVar10,_DAT_7fff62452178);
        if (*(longlong *)(puVar9 + 0x30) != 0) {
          FUN_7fff60a8da60(&uStack_a8,*(longlong *)(puVar9 + 0x30),_DAT_7fff6240f9e0);
          uStack_90 = uStack_a8;
          puStack_88 = puStack_a0;
          lStack_80 = lStack_98;
          uStack_a8 = 0;
          puStack_a0 = &uStack_90;
          while (cVar7 = FUN_7fff60933290(&uStack_90,_DAT_7fff6247a598), cVar7 != '\0') {
            if (lStack_80 == 0) goto LAB_7fff5fff48e9;
            iVar8 = *(short *)(lStack_80 + 0x14) * stack;
            iVar12 = 0x7fff;
            if (iVar8 < 0x7fff) {
              iVar12 = iVar8;
            }
            *(short *)(lStack_80 + 0x14) = (short)iVar12;
          }
          func_0x7fff5f4d3920(&uStack_90,_DAT_7fff6247a4c8);
          if (*(longlong *)(puVar9 + 0x38) != 0) {
            FUN_7fff60a8da60(&uStack_a8,*(longlong *)(puVar9 + 0x38),_DAT_7fff6240f9e0);
            uStack_90 = uStack_a8;
            puStack_88 = puStack_a0;
            lStack_80 = lStack_98;
            uStack_a8 = 0;
            puStack_a0 = &uStack_90;
            while( true ) {
              cVar7 = FUN_7fff60933290(&uStack_90,_DAT_7fff6247a598);
              if (cVar7 == '\0') {
                func_0x7fff5f4d3920(&uStack_90,_DAT_7fff6247a4c8);
                return puVar9;
              }
              if (lStack_80 == 0) break;
              iVar8 = *(short *)(lStack_80 + 0x14) * stack;
              iVar12 = 0x7fff;
              if (0x7fff < iVar8) {
                iVar12 = iVar8;
              }
              *(short *)(lStack_80 + 0x14) = (short)iVar12;
            }
            goto LAB_7fff5fff48f5;
          }
        }
      }
    }
  }
  FUN_7fff5f47d660();
LAB_7fff5fff48cd:
  FUN_7fff5f47d650();
LAB_7fff5fff48d3:
  FUN_7fff5f47d660();
LAB_7fff5fff48d8:
  FUN_7fff5f47d660();
LAB_7fff5fff48dd:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
LAB_7fff5fff48e9:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
LAB_7fff5fff48f5:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar6 = (code *)swi(3);
  puVar9 = (undefined *)(*pcVar6)();
  return puVar9;
}

