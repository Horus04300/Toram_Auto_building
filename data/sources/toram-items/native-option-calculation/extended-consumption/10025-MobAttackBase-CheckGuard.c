
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobAttackBase_CheckGuard
               (undefined *self,undefined *playerAction,undefined *mobAction,int damage,
               undefined *guardType,undefined *justGuard,undefined *methodInfo)

{
  uint uVar1;
  int iVar2;
  longlong *self_00;
  longlong lVar3;
  code *pcVar4;
  byte bVar5;
  
  if (DAT_7ffe9cadd7e0 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f7560);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    DAT_7ffe9cadd7e0 = '\x01';
  }
  if (*(longlong *)(self + 0xa0) != 0) {
    iVar2 = *(int *)(*(longlong *)(self + 0xa0) + 0x3c);
    if (iVar2 < 0x45a) {
      if (iVar2 - 0x424U < 4) goto LAB_7ffe9a374c69;
      uVar1 = iVar2 - 0x456;
    }
    else {
      if (iVar2 - 0x492U < 8) goto LAB_7ffe9a374c69;
      uVar1 = iVar2 - 0x49c;
    }
    if (3 < uVar1) {
      if (playerAction == (undefined *)0x0) goto LAB_7ffe9a374de5;
      self_00 = *(longlong **)(playerAction + 0x30);
      if (self_00 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c922a40 + 0x130) <= *(byte *)(*self_00 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*self_00 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) == _DAT_7ffe9c922a40)) {
          if ((*(byte *)(_DAT_7ffe9c922a40 + 0x130) <= *(byte *)(*self_00 + 0x130)) &&
             (lVar3 = *(longlong *)(*self_00 + 200),
             *(longlong *)(lVar3 + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) ==
             _DAT_7ffe9c922a40)) {
            if (*(longlong *)(lVar3 + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) ==
                _DAT_7ffe9c922a40) {
              bVar5 = PlayerBattleManager_CheckGuard
                                ((undefined *)self_00,mobAction,self,damage,guardType,justGuard,
                                 (undefined *)0x0);
              return bVar5;
            }
            FUN_7ffe9996c950();
            pcVar4 = (code *)swi(3);
            bVar5 = (*pcVar4)();
            return bVar5;
          }
          FUN_7ffe9996c950(self_00);
          pcVar4 = (code *)swi(3);
          bVar5 = (*pcVar4)();
          return bVar5;
        }
        if ((*(byte *)(_DAT_7ffe9c8f7560 + 0x130) <= *(byte *)(*self_00 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*self_00 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) == _DAT_7ffe9c8f7560)) {
          if ((*(byte *)(_DAT_7ffe9c8f7560 + 0x130) <= *(byte *)(*self_00 + 0x130)) &&
             (lVar3 = *(longlong *)(*self_00 + 200),
             *(longlong *)(lVar3 + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) ==
             _DAT_7ffe9c8f7560)) {
            if (*(longlong *)(lVar3 + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) ==
                _DAT_7ffe9c8f7560) {
              bVar5 = FUN_7ffe9a4300e0(self_00,mobAction,self,damage,guardType,justGuard,0);
              return bVar5;
            }
            FUN_7ffe9996c950(self_00);
            pcVar4 = (code *)swi(3);
            bVar5 = (*pcVar4)();
            return bVar5;
          }
          FUN_7ffe9996c950(self_00);
          pcVar4 = (code *)swi(3);
          bVar5 = (*pcVar4)();
          return bVar5;
        }
      }
    }
LAB_7ffe9a374c69:
    *(undefined4 *)guardType = 0;
    *justGuard = 0;
    return 0;
  }
LAB_7ffe9a374de5:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  bVar5 = (*pcVar4)();
  return bVar5;
}

