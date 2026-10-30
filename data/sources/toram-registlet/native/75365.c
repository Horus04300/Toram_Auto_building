
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBuffer_BaskInTheSunBuff__ctor(undefined *self,short lv,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  undefined8 uVar3;
  char cVar4;
  
  if (DAT_7ffe9cadd3c7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadd3c7 = '\x01';
  }
  GemCartBufferBase__ctor(self,lv,(undefined *)0x0);
  lVar2 = FUN_7ffe9a47bac0(0);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(lVar2,0,0);
  if (cVar4 != '\0') {
    if (lVar2 == 0) {
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    uVar3 = FUN_7ffe9a47f4d0(lVar2,0);
    *(undefined8 *)(self + 0x18) = uVar3;
    il2cpp_write_barrier_0();
  }
  return;
}

