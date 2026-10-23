
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobPropertyCut___c__get_CutAttack_b__1_0(undefined *self,undefined *x,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  
  if ((x != (undefined *)0x0) && (lVar1 = *(longlong *)(x + 0x18), lVar1 != 0)) {
    if (*(int *)(lVar1 + 0x18) != 0) {
      return *(int *)(lVar1 + 0x20);
    }
    FUN_7ffe9996d790();
    pcVar2 = (code *)swi(3);
    iVar3 = (*pcVar2)();
    return iVar3;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

