
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_BaskInTheSunBuff_CheckTrigger(undefined *self,undefined *methodInfo)

{
  int iVar1;
  undefined8 uVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  byte bVar6;
  
  if (DAT_7ffe9cadd3c8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadd3c8 = '\x01';
  }
  uVar2 = *(undefined8 *)(self + 0x18);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar5 = FUN_7ffe9bda1fa0(uVar2,0,0);
  if (cVar5 == '\0') {
    lVar3 = *(longlong *)(self + 0x18);
    if (lVar3 != 0) {
      iVar1 = *(int *)(lVar3 + 0x40);
      bVar6 = func_0x7ffe9a40ebf0(lVar3,0);
      if (iVar1 == 0x215) {
        bVar6 = 1;
      }
      bVar6 = bVar6 | iVar1 == 0x24;
      if (iVar1 == 0x22) {
        bVar6 = 1;
      }
      return bVar6;
    }
    FUN_7ffe9996d7a0();
    pcVar4 = (code *)swi(3);
    bVar6 = (*pcVar4)();
    return bVar6;
  }
  return 0;
}

