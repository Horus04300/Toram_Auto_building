
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_Initialize(undefined *self,undefined *playerStatus,undefined *methodInfo)

{
  undefined *self_00;
  
  if (DAT_7ffe9cade100 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948e68);
    DAT_7ffe9cade100 = '\x01';
  }
  if (*(longlong *)(self + 0x18) == 0) {
    self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c948e68);
    BonusScriptManager__ctor(self_00,playerStatus,(undefined *)0x0);
    *(undefined **)(self + 0x18) = self_00;
    il2cpp_write_barrier_0();
  }
  return;
}

