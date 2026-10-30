
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_NothingStyleBuff_CheckBuffValid
               (undefined *self,int skillId,undefined *combo,float comboRate,undefined *methodInfo)

{
  char cVar1;
  
  if (DAT_7ffe9cadd3d3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9cadd3d3 = '\x01';
  }
  if (combo == (undefined *)0x0) {
    if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9a8129a0(skillId,0);
    if ((cVar1 == '\0') || (comboRate == _DAT_7ffe9c049b18)) {
      return 1;
    }
  }
  return 0;
}

