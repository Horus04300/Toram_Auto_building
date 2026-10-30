
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_PursuitResistBuff_CheckTrigger(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  byte bVar3;
  longlong lVar4;
  
  plVar1 = *(longlong **)(self + 0x18);
  if (plVar1 != (longlong *)0x0) {
    lVar4 = (**(code **)(*plVar1 + 0x1e8))(plVar1,*(undefined8 *)(*plVar1 + 0x1f0));
    if (lVar4 != 0) {
      return *(byte *)(lVar4 + 0x51);
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar3 = (*pcVar2)();
  return bVar3;
}

