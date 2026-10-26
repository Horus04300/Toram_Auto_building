
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobAttackBase_CheckPercentageDamage(undefined *self,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  byte bVar3;
  bool bVar4;
  bool bVar5;
  
  if (*(longlong *)(self + 0xa0) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    bVar3 = (*pcVar2)();
    return bVar3;
  }
  iVar1 = *(int *)(*(longlong *)(self + 0xa0) + 0x3c);
  if (iVar1 < 0x112) {
    if (iVar1 < 0x36) {
      if (iVar1 < 0x21) {
        if (iVar1 - 0x14U < 3) {
          return 1;
        }
        bVar4 = iVar1 - 0x1eU < 2;
        bVar5 = iVar1 - 0x1eU == 2;
      }
      else {
        if (iVar1 - 0x2aU < 2) {
          return 1;
        }
        if (iVar1 - 0x2eU < 2) {
          return 1;
        }
        bVar4 = iVar1 == 0x34;
        bVar5 = iVar1 == 0x35;
      }
    }
    else if (iVar1 < 0xd6) {
      if (iVar1 - 0x98U < 2) {
        return 1;
      }
      bVar4 = iVar1 == 0xd4;
      bVar5 = iVar1 == 0xd5;
    }
    else {
      if (iVar1 - 0xf2U < 2) {
        return 1;
      }
      if (iVar1 - 0xfcU < 2) {
        return 1;
      }
      bVar4 = iVar1 == 0x110;
      bVar5 = iVar1 == 0x111;
    }
  }
  else if (iVar1 < 0x45a) {
    if (iVar1 < 0x432) {
      if (iVar1 - 0x426U < 2) {
        return 1;
      }
      bVar4 = iVar1 == 0x430;
      bVar5 = iVar1 == 0x431;
    }
    else {
      if (iVar1 - 0x43aU < 2) {
        return 1;
      }
      if (iVar1 - 0x43eU < 2) {
        return 1;
      }
      bVar4 = iVar1 == 0x458;
      bVar5 = iVar1 == 0x459;
    }
  }
  else {
    if (0x49f < iVar1) {
      if (iVar1 - 0x4c6U < 2) {
        return 1;
      }
      if (iVar1 - 0x4d0U < 2) {
        return 1;
      }
      if (iVar1 - 0x4eeU < 2) {
        return 1;
      }
      return 0;
    }
    if (iVar1 - 0x494U < 2) {
      return 1;
    }
    if (iVar1 - 0x498U < 2) {
      return 1;
    }
    bVar4 = iVar1 == 0x49e;
    bVar5 = iVar1 == 0x49f;
  }
  if (bVar4 || bVar5) {
    return 1;
  }
  return 0;
}

