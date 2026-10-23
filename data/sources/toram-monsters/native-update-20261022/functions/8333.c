
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
  if (DAT_7ffe9cadd59e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c954060);
    FUN_7ffe9996d590(&DAT_7ffe9c954130);
    FUN_7ffe9996d590(0x7ffe9c9545f8);
    FUN_7ffe9996d590(0x7ffe9c9551d8);
    FUN_7ffe9996d590(0x7ffe9c955508);
    FUN_7ffe9996d590(0x7ffe9c9559d0);
    FUN_7ffe9996d590(&DAT_7ffe9c957288);
    FUN_7ffe9996d590(&DAT_7ffe9c957350);
    FUN_7ffe9996d590(&DAT_7ffe9c957420);
    FUN_7ffe9996d590(&DAT_7ffe9c9578e8);
    FUN_7ffe9996d590(&DAT_7ffe9c9579b0);
    FUN_7ffe9996d590(&DAT_7ffe9c9589a0);
    FUN_7ffe9996d590(&DAT_7ffe9c959198);
    FUN_7ffe9996d590(&DAT_7ffe9c959268);
    FUN_7ffe9996d590(&DAT_7ffe9c959598);
    FUN_7ffe9996d590(0x7ffe9c9598c8);
    FUN_7ffe9996d590(0x7ffe9c959990);
    FUN_7ffe9996d590(&DAT_7ffe9c95abe8);
    FUN_7ffe9996d590(&DAT_7ffe9c95acb0);
    FUN_7ffe9996d590(&DAT_7ffe9c95c168);
    FUN_7ffe9996d590(&DAT_7ffe9c95c238);
    FUN_7ffe9996d590(0x7ffe9c95dae0);
    FUN_7ffe9996d590(0x7ffe9c95dd48);
    DAT_7ffe9cadd59e = '\x01';
  }
  if (iVar7 < 0x102) {
    if (iVar7 < 0x46) {
      if (iVar7 < 0x21) {
        switch(iVar7) {
        case 0:
          lVar5 = _DAT_7ffe9c9589a0;
          break;
        case 1:
          lVar5 = lRam00007ffe9c9545f8;
          break;
        case 2:
        case 3:
          lVar5 = lRam00007ffe9c9559d0;
          break;
        case 4:
          lVar5 = lRam00007ffe9c955508;
          break;
        case 5:
          lVar5 = lRam00007ffe9c9551d8;
          break;
        case 6:
        case 7:
          goto LAB_7ffe9a329ed8;
        case 8:
          lVar5 = lRam00007ffe9c95dd48;
          break;
        case 9:
          lVar5 = lRam00007ffe9c95dae0;
          break;
        default:
          lVar5 = _DAT_7ffe9c95c238;
          if (iVar7 != 0x20) {
            return;
          }
        }
      }
      else {
        lVar5 = _DAT_7ffe9c95c168;
        if (iVar7 != 0x21) {
          switch(iVar7) {
          case 0x40:
          case 0x44:
            lVar5 = lRam00007ffe9c959990;
            break;
          case 0x41:
          case 0x45:
            lVar5 = lRam00007ffe9c9598c8;
            break;
          default:
            goto LAB_7ffe9a329ed8;
          }
        }
      }
    }
    else if (iVar7 < 0x82) {
      lVar5 = _DAT_7ffe9c9579b0;
      if ((iVar7 != 0x80) && (lVar5 = _DAT_7ffe9c9578e8, iVar7 != 0x81)) {
        return;
      }
    }
    else {
      lVar5 = _DAT_7ffe9c957420;
      if ((iVar7 != 0x100) && (lVar5 = _DAT_7ffe9c957288, iVar7 != 0x101)) {
        return;
      }
    }
  }
  else if (iVar7 < 0x402) {
    if (iVar7 < 0x222) {
      lVar5 = _DAT_7ffe9c959268;
      if (1 < iVar7 - 0x200U) {
        uVar2 = iVar7 - 0x220;
        lVar5 = _DAT_7ffe9c959198;
        goto joined_r0x7ffe9a329eec;
      }
    }
    else {
      lVar5 = _DAT_7ffe9c954130;
      if ((iVar7 != 0x400) && (lVar5 = _DAT_7ffe9c954060, iVar7 != 0x401)) {
        return;
      }
    }
  }
  else if (iVar7 < 0x802) {
    lVar5 = _DAT_7ffe9c95acb0;
    if ((iVar7 != 0x800) && (lVar5 = _DAT_7ffe9c95abe8, iVar7 != 0x801)) {
      return;
    }
  }
  else {
    if (iVar7 == 0x8101) {
      if (model != (undefined *)0x0) {
        FUN_7ffe9ab9b9b0(model,_DAT_7ffe9c957350);
        return;
      }
      goto LAB_7ffe9a32a29e;
    }
    uVar2 = iVar7 - 0x8220;
    lVar5 = _DAT_7ffe9c959598;
joined_r0x7ffe9a329eec:
    if (1 < uVar2) {
LAB_7ffe9a329ed8:
      return;
    }
  }
  if (model != (undefined *)0x0) {
    if ((*(longlong *)(lVar5 + 0x38) == 0) &&
       (FUN_7ffe9996d590(&DAT_7ffe9c96ec48), *(longlong *)(lVar5 + 0x38) == 0)) {
      FUN_7ffe998cedc0(lVar5);
    }
    uVar3 = **(undefined8 **)(lVar5 + 0x38);
    if (*(int *)(_DAT_7ffe9c96ec48 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    uVar3 = FUN_7ffe9b52cc00(uVar3,0);
    uVar3 = FUN_7ffe9bd9abe0(model,uVar3,0,in_R9,unaff_RDI);
    lVar4 = *(longlong *)(*(longlong *)(lVar5 + 0x38) + 8);
    if ((*(byte *)(lVar4 + 0x135) & 1) == 0) {
      lVar4 = FUN_7ffe998ced40(lVar4);
    }
    lVar5 = *(longlong *)(*(longlong *)(lVar5 + 0x38) + 8);
    if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
      lVar5 = FUN_7ffe998ced40(lVar5);
    }
    lVar5 = func_0x7ffe9996c920(uVar3,lVar5);
    if ((lVar5 != 0) && (lVar6 = func_0x7ffe9996c920(lVar5,lVar4), lVar6 == 0)) {
      FUN_7ffe9996c950(lVar5,lVar4);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    return;
  }
LAB_7ffe9a32a29e:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

