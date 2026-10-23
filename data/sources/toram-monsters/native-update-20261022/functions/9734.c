
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobPropertyHighRaidCalcExceptionFlag_FixedDefFlag(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  longlong lVar3;
  
  if (DAT_7ffe9cadd788 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906868);
    DAT_7ffe9cadd788 = '\x01';
  }
  lVar3 = FUN_7ffe9ab85290(*(undefined8 *)(self + 0x10),_DAT_7ffe9c906868);
  if (lVar3 != 0) {
    lVar3 = *(longlong *)(lVar3 + 0x18);
    if (lVar3 == 0) {
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      bVar2 = (*pcVar1)();
      return bVar2;
    }
    if (*(int *)(lVar3 + 0x18) == 0) {
      FUN_7ffe9996d790();
      pcVar1 = (code *)swi(3);
      bVar2 = (*pcVar1)();
      return bVar2;
    }
    if ((*(byte *)(lVar3 + 0x20) & 4) != 0) {
      return 1;
    }
  }
  return 0;
}

