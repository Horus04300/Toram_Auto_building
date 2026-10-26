
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobAttackBase_CheckAvoid
               (undefined *self,undefined *playerAction,undefined *mobAction,undefined *methodInfo)

{
  longlong *plVar1;
  longlong lVar2;
  code *pcVar3;
  bool bVar4;
  char cVar5;
  byte bVar6;
  longlong *plVar7;
  
  if (DAT_7ffe9cadd7e2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    DAT_7ffe9cadd7e2 = '\x01';
  }
  if (playerAction != (undefined *)0x0) {
    plVar1 = *(longlong **)(playerAction + 0x30);
    if (plVar1 == (longlong *)0x0) {
      plVar7 = (longlong *)0x0;
    }
    else {
      if ((*(byte *)(*plVar1 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8)
          != _DAT_7ffe9c922a40)) {
        bVar4 = false;
      }
      else {
        bVar4 = true;
      }
      plVar7 = (longlong *)0x0;
      if (bVar4) {
        plVar7 = plVar1;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar5 = FUN_7ffe9bda1fa0(plVar7,0,0);
    if (cVar5 != '\0') {
      return 0;
    }
    if (plVar7 != (longlong *)0x0) {
      if (DAT_7ffe9caddce2 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c906b90);
        DAT_7ffe9caddce2 = '\x01';
      }
      lVar2 = plVar7[0x14];
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar5 = FUN_7ffe9bda2160(lVar2,0,0);
      bVar6 = 0;
      if (cVar5 != '\0') {
        if ((undefined *)plVar7[0x14] == (undefined *)0x0) {
          FUN_7ffe9996d7a0();
          pcVar3 = (code *)swi(3);
          bVar6 = (*pcVar3)();
          return bVar6;
        }
        bVar6 = AvoidActionManager_CheckAvoid
                          ((undefined *)plVar7[0x14],mobAction,self,(undefined *)0x0);
      }
      return bVar6;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  bVar6 = (*pcVar3)();
  return bVar6;
}

