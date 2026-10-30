
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIRegistletEditPanel_OnClickAddSlotWindowButton(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  if (DAT_7ffe9cadc32b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c955c78);
    DAT_7ffe9cadc32b = '\x01';
  }
  lVar3 = FUN_7ffe9b141840(_DAT_7ffe9c955c78);
  if (lVar3 == 0) {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  FUN_7ffe99a314f0(lVar3,7,0);
  if (DAT_7ffe9cadc32c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fb4c8);
    DAT_7ffe9cadc32c = '\x01';
  }
  lVar3 = func_0x7ffe99940040(_DAT_7ffe9c8fb4c8);
  func_0x7ffe999c3920(lVar3,0);
  *(undefined **)(lVar3 + 0x20) = self;
  *(undefined4 *)(lVar3 + 0x10) = 0;
  il2cpp_write_barrier_0();
  if (lVar3 != 0) {
    if (_DAT_7ffe9cae9848 == (code *)0x0) {
      _DAT_7ffe9cae9848 = (code *)FUN_7ffe9996d800(&UNK_7ffe9c133f90);
    }
    cVar2 = (*_DAT_7ffe9cae9848)(self);
    if (cVar2 != '\0') {
      if (_DAT_7ffe9cae9858 == (code *)0x0) {
        _DAT_7ffe9cae9858 = (code *)FUN_7ffe9996d800(&UNK_7ffe9c134030);
      }
                    /* WARNING: Could not recover jumptable at 0x7ffe9bd9f6ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*_DAT_7ffe9cae9858)(self,lVar3);
      return;
    }
    uVar4 = func_0x7ffe9996d5b0(&DAT_7ffe9c9354e0);
    uVar4 = func_0x7ffe99940040(uVar4);
    uVar5 = func_0x7ffe9996d5b0(0x7ffe9c90f888);
    FUN_7ffe9b481770(uVar4,uVar5,0);
    uVar5 = func_0x7ffe9996d5b0(0x7ffe9c92d548);
    FUN_7ffe9996d760(uVar4,uVar5);
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  uVar4 = func_0x7ffe9996d5b0(0x7ffe9c906100,0,0);
  uVar4 = func_0x7ffe99940040(uVar4);
  uVar5 = func_0x7ffe9996d5b0(0x7ffe9c9413e0);
  FUN_7ffe9b508730(uVar4,uVar5,0);
  uVar5 = func_0x7ffe9996d5b0(0x7ffe9c92d548);
  FUN_7ffe9996d760(uVar4,uVar5);
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

