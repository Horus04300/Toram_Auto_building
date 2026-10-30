
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_BloodyWarriorBuff_CheckTrigger(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  byte bVar3;
  int iVar4;
  longlong lVar5;
  
  plVar1 = *(longlong **)(self + 0x18);
  if (plVar1 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar1 + 0x1e8))(plVar1,*(undefined8 *)(*plVar1 + 0x1f0));
    if (lVar5 != 0) {
      if (DAT_7ffe9cade052 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c93f450);
        DAT_7ffe9cade052 = '\x01';
      }
      if (*(longlong *)(lVar5 + 0x18) != 0) {
        iVar4 = FUN_7ffe9ad606a0(*(longlong *)(lVar5 + 0x18),0x13,
                                 *(undefined8 *)
                                  (*(longlong *)(*(longlong *)(_DAT_7ffe9c93f450 + 0x20) + 0xc0) +
                                  0x110));
        return -1 < iVar4;
      }
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      bVar3 = (*pcVar2)();
      return bVar3;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar3 = (*pcVar2)();
  return bVar3;
}

