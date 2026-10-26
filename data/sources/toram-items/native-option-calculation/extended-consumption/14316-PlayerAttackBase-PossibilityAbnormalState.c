
/* WARNING: Removing unreachable block (ram,0x7ffe99940143) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
PlayerAttackBase_PossibilityAbnormalState(undefined *self,undefined *status,undefined *methodInfo)

{
  longlong lVar1;
  uint uVar2;
  longlong *plVar3;
  longlong lVar4;
  
  if (DAT_7ffe9cadded5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90fed8);
    DAT_7ffe9cadded5 = '\x01';
  }
  lVar1 = _DAT_7ffe9c90fed8;
  FUN_7ffe999205b0();
  uVar2 = func_0x7ffe9997d990(lVar1);
  lVar4 = (ulonglong)uVar2 + 0x20;
  if ((*(byte *)(lVar1 + 0x135) & 0x20) == 0) {
    plVar3 = (longlong *)func_0x7ffe999877b0(lVar4);
    *plVar3 = lVar1;
    plVar3[1] = 0;
    LOCK();
    _DAT_7ffe9caedaf8 = _DAT_7ffe9caedaf8 + 1;
    UNLOCK();
    plVar3[2] = 0;
    FUN_7ffe99992ee0(plVar3 + 2,0,(ulonglong)uVar2 + 0x10);
  }
  else if ((*(int *)(*(longlong *)(lVar1 + 0x40) + 0x28) < 0) &&
          ((*(byte *)(*(longlong *)(lVar1 + 0x40) + 8) & 3) == 1)) {
    plVar3 = (longlong *)FUN_7ffe99984de0(lVar4,lVar1);
  }
  else {
    if (*(longlong *)(lVar1 + 8) == 0) {
      plVar3 = (longlong *)func_0x7ffe999877a0(lVar4);
      *plVar3 = lVar1;
    }
    else {
      plVar3 = (longlong *)FUN_7ffe99984c70(lVar4,lVar1);
    }
    LOCK();
    _DAT_7ffe9caedaf8 = _DAT_7ffe9caedaf8 + 1;
    UNLOCK();
  }
  plVar3[3] = 1;
  if ((_DAT_7ffe9caed360 >> 7 & 1) != 0) {
    FUN_7ffe9994ac50(plVar3,lVar1);
  }
  return (undefined *)plVar3;
}

