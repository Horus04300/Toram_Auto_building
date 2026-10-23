
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_Initialize(undefined *self,undefined *playerStatus,undefined *methodInfo)

{
  undefined8 uVar1;
  
  if (DAT_7fff625e5858 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624507a0);
    DAT_7fff625e5858 = '\x01';
  }
  if (*(longlong *)(self + 0x18) == 0) {
    uVar1 = func_0x7fff5f44ff00(_DAT_7fff624507a0);
    FUN_7fff600018d0(uVar1,playerStatus,0);
    *(undefined8 *)(self + 0x18) = uVar1;
    thunk_FUN_7fff5f491fd0();
  }
  return;
}

