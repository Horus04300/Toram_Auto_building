
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HelpMaster__ctor(undefined *self,short value,undefined *methodInfo)

{
  undefined2 uVar1;
  
  if (DAT_7ffe9cade23a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cade23a = '\x01';
  }
  _GetDurationBonusTime_d__7_System_IDisposable_Dispose(self,(undefined *)0x0);
  if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  uVar1 = func_0x7ffe9b506d60(value,10,0);
  *(undefined2 *)(self + 0x10) = uVar1;
  self[0x12] = 1;
  return;
}

