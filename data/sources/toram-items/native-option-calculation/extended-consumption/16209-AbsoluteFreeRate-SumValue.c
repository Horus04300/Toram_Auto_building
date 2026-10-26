
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AbsoluteFreeRate_SumValue(undefined *self,short val,undefined *methodInfo)

{
  short sVar1;
  undefined2 uVar2;
  
  if (DAT_7ffe9cade231 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cade231 = '\x01';
  }
  *(short *)(self + 0x18) = *(short *)(self + 0x18) + val;
  sVar1 = *(short *)(self + 0x10);
  if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  uVar2 = func_0x7ffe9b506d80((int)val + (int)sVar1,0x1e);
  *(undefined2 *)(self + 0x10) = uVar2;
  return;
}

