
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuardActionManager_UpdateGuard(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  float fVar3;
  float fVar4;
  
  fVar4 = *(float *)(self + 0x54);
  if (0.0 < fVar4) {
    fVar3 = (float)FUN_7ffe9bda7ce0(0);
    fVar4 = fVar4 - fVar3;
    *(float *)(self + 0x54) = fVar4;
    if (fVar4 <= 0.0) {
      *(undefined4 *)(self + 0x54) = 0;
    }
  }
  GuardActionManager_UpdateGuarding(self,(undefined *)0x0);
  GuardActionManager_UpdateGuardWaiting(self,(undefined *)0x0);
  if (*(int *)(self + 0x48) < 0) {
    return;
  }
  if ((*(longlong *)(self + 0x40) != 0) &&
     (lVar2 = FUN_7ffe9a9b94c0(*(longlong *)(self + 0x40),0), lVar2 != 0)) {
    if (*(int *)(lVar2 + 0x7c) != *(int *)(self + 0x48)) {
      return;
    }
    if ((*(longlong *)(self + 0x40) != 0) &&
       (lVar2 = FUN_7ffe9a9b94c0(*(longlong *)(self + 0x40),0), lVar2 != 0)) {
      if (*(char *)(lVar2 + 0x3c) != '\0') {
        return;
      }
      *(undefined4 *)(self + 0x48) = 0xffffffff;
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

