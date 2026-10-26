
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_GetActionTypeResist(undefined *self,undefined *playerAction,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong *plVar3;
  undefined *self_00;
  
  if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a3758db;
  iVar2 = *(int *)(*(longlong *)(self + 0xa0) + 0x3c);
  if (iVar2 < 0xfc) {
    if (iVar2 < 0x2a) {
      if (iVar2 < 3) {
        if (iVar2 == 1) {
          iVar2 = 0x79;
        }
        else {
          if (iVar2 != 2) {
            return 0;
          }
LAB_7ffe9a375882:
          iVar2 = 0x7a;
        }
      }
      else if (iVar2 == 0xb) {
LAB_7ffe9a37581b:
        iVar2 = 0x79;
      }
      else {
        if (iVar2 == 0xc) goto LAB_7ffe9a375882;
        if (1 < iVar2 - 0x28U) {
          return 0;
        }
        iVar2 = 0x7c;
      }
    }
    else if (iVar2 < 0x34) {
      if (iVar2 - 0x2cU < 2) {
        iVar2 = 0x7c;
      }
      else {
        if (1 < iVar2 - 0x32U) {
          return 0;
        }
        iVar2 = 0x7b;
      }
    }
    else {
      if (1 < iVar2 - 0x96U) {
        if (iVar2 - 0xd2U < 2) goto LAB_7ffe9a37581b;
        if (1 < iVar2 - 0xfaU) {
          return 0;
        }
        goto LAB_7ffe9a375882;
      }
      iVar2 = 0x81;
    }
  }
  else if (iVar2 < 0x43e) {
    if (iVar2 < 0x426) {
      if (iVar2 - 0x10eU < 2) goto LAB_7ffe9a375882;
      if (1 < iVar2 - 0x424U) {
        return 0;
      }
      iVar2 = 0x7d;
    }
    else if (iVar2 - 0x42eU < 2) {
      iVar2 = 0x7e;
    }
    else {
      if ((1 < iVar2 - 0x438U) && (1 < iVar2 - 0x43cU)) {
        return 0;
      }
      iVar2 = 0x7f;
    }
  }
  else if (iVar2 < 0x498) {
    if (iVar2 - 0x456U < 2) {
      iVar2 = 0x80;
    }
    else {
      if ((1 < iVar2 - 0x492U) && (1 < iVar2 - 0x496U)) {
        return 0;
      }
      iVar2 = 0x83;
    }
  }
  else if (iVar2 - 0x49cU < 2) {
    iVar2 = 0x82;
  }
  else if (iVar2 - 0x4c4U < 2) {
    iVar2 = 0x7b;
  }
  else {
    if (1 < iVar2 - 0x4ceU) {
      return 0;
    }
    iVar2 = 0x7e;
  }
  if (((playerAction != (undefined *)0x0) &&
      (plVar3 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
      plVar3 != (longlong *)0x0)) &&
     (self_00 = (undefined *)(**(code **)(*plVar3 + 0x1d8))(plVar3,*(undefined8 *)(*plVar3 + 0x1e0))
     , self_00 != (undefined *)0x0)) {
    iVar2 = BonusManager_GetBonusValue(self_00,iVar2,(undefined *)0x0);
    return iVar2;
  }
LAB_7ffe9a3758db:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}

