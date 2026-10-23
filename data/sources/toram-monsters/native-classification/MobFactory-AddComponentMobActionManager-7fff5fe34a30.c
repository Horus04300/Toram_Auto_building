
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobFactory_AddComponentMobActionManager(undefined *model,undefined *flag,undefined *methodInfo)

{
  code *pcVar1;
  uint uVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  int iVar7;
  undefined8 unaff_RDI;
  undefined8 in_R9;
  
  iVar7 = (int)flag;
  if (DAT_7fff625e4cf6 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245ae78);
    FUN_7fff5f47d450(&DAT_7fff6245af48);
    FUN_7fff5f47d450(0x7fff6245b410);
    FUN_7fff5f47d450(0x7fff6245bff0);
    FUN_7fff5f47d450(0x7fff6245c320);
    FUN_7fff5f47d450(0x7fff6245c7e8);
    FUN_7fff5f47d450(&DAT_7fff6245e0a0);
    FUN_7fff5f47d450(&DAT_7fff6245e168);
    FUN_7fff5f47d450(&DAT_7fff6245e238);
    FUN_7fff5f47d450(&DAT_7fff6245e700);
    FUN_7fff5f47d450(&DAT_7fff6245e7c8);
    FUN_7fff5f47d450(&DAT_7fff6245f7b8);
    FUN_7fff5f47d450(&DAT_7fff6245ffb0);
    FUN_7fff5f47d450(&DAT_7fff62460080);
    FUN_7fff5f47d450(&DAT_7fff624603b0);
    FUN_7fff5f47d450(0x7fff624606e0);
    FUN_7fff5f47d450(0x7fff624607a8);
    FUN_7fff5f47d450(&DAT_7fff62461a00);
    FUN_7fff5f47d450(&DAT_7fff62461ac8);
    FUN_7fff5f47d450(&DAT_7fff62462f80);
    FUN_7fff5f47d450(&DAT_7fff62463050);
    FUN_7fff5f47d450(0x7fff624648f8);
    FUN_7fff5f47d450(0x7fff62464b58);
    DAT_7fff625e4cf6 = '\x01';
  }
  if (iVar7 < 0x102) {
    if (iVar7 < 0x46) {
      if (iVar7 < 0x21) {
        switch(iVar7) {
        case 0:
          lVar5 = _DAT_7fff6245f7b8;
          break;
        case 1:
          lVar5 = lRam00007fff6245b410;
          break;
        case 2:
        case 3:
          lVar5 = lRam00007fff6245c7e8;
          break;
        case 4:
          lVar5 = lRam00007fff6245c320;
          break;
        case 5:
          lVar5 = lRam00007fff6245bff0;
          break;
        case 6:
        case 7:
          goto LAB_7fff5fe34ba8;
        case 8:
          lVar5 = lRam00007fff62464b58;
          break;
        case 9:
          lVar5 = lRam00007fff624648f8;
          break;
        default:
          lVar5 = _DAT_7fff62463050;
          if (iVar7 != 0x20) {
            return;
          }
        }
      }
      else {
        lVar5 = _DAT_7fff62462f80;
        if (iVar7 != 0x21) {
          switch(iVar7) {
          case 0x40:
          case 0x44:
            lVar5 = lRam00007fff624607a8;
            break;
          case 0x41:
          case 0x45:
            lVar5 = lRam00007fff624606e0;
            break;
          default:
            goto LAB_7fff5fe34ba8;
          }
        }
      }
    }
    else if (iVar7 < 0x82) {
      lVar5 = _DAT_7fff6245e7c8;
      if ((iVar7 != 0x80) && (lVar5 = _DAT_7fff6245e700, iVar7 != 0x81)) {
        return;
      }
    }
    else {
      lVar5 = _DAT_7fff6245e238;
      if ((iVar7 != 0x100) && (lVar5 = _DAT_7fff6245e0a0, iVar7 != 0x101)) {
        return;
      }
    }
  }
  else if (iVar7 < 0x402) {
    if (iVar7 < 0x222) {
      lVar5 = _DAT_7fff62460080;
      if (1 < iVar7 - 0x200U) {
        uVar2 = iVar7 - 0x220;
        lVar5 = _DAT_7fff6245ffb0;
        goto joined_r0x7fff5fe34bbc;
      }
    }
    else {
      lVar5 = _DAT_7fff6245af48;
      if ((iVar7 != 0x400) && (lVar5 = _DAT_7fff6245ae78, iVar7 != 0x401)) {
        return;
      }
    }
  }
  else if (iVar7 < 0x802) {
    lVar5 = _DAT_7fff62461ac8;
    if ((iVar7 != 0x800) && (lVar5 = _DAT_7fff62461a00, iVar7 != 0x801)) {
      return;
    }
  }
  else {
    if (iVar7 == 0x8101) {
      if (model != (undefined *)0x0) {
        FUN_7fff606a5d60(model,_DAT_7fff6245e168);
        return;
      }
      goto LAB_7fff5fe34f6e;
    }
    uVar2 = iVar7 - 0x8220;
    lVar5 = _DAT_7fff624603b0;
joined_r0x7fff5fe34bbc:
    if (1 < uVar2) {
LAB_7fff5fe34ba8:
      return;
    }
  }
  if (model != (undefined *)0x0) {
    if ((*(longlong *)(lVar5 + 0x38) == 0) &&
       (FUN_7fff5f47d450(&DAT_7fff624761d8), *(longlong *)(lVar5 + 0x38) == 0)) {
      FUN_7fff5f3dec80(lVar5);
    }
    uVar3 = **(undefined8 **)(lVar5 + 0x38);
    if (*(int *)(_DAT_7fff624761d8 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    uVar3 = FUN_7fff61036fc0(uVar3,0);
    uVar3 = FUN_7fff618a3d60(model,uVar3,0,in_R9,unaff_RDI);
    lVar4 = *(longlong *)(*(longlong *)(lVar5 + 0x38) + 8);
    if ((*(byte *)(lVar4 + 0x135) & 1) == 0) {
      lVar4 = FUN_7fff5f3dec00(lVar4);
    }
    lVar5 = *(longlong *)(*(longlong *)(lVar5 + 0x38) + 8);
    if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
      lVar5 = FUN_7fff5f3dec00(lVar5);
    }
    lVar5 = func_0x7fff5f47c7e0(uVar3,lVar5);
    if ((lVar5 != 0) && (lVar6 = func_0x7fff5f47c7e0(lVar5,lVar4), lVar6 == 0)) {
      FUN_7fff5f47c810(lVar5,lVar4);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    return;
  }
LAB_7fff5fe34f6e:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

