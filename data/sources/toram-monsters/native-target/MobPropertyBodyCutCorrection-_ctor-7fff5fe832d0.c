
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobPropertyBodyCutCorrection__ctor(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  
  if (DAT_7fff625e4ee2 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624442c0,0);
    FUN_7fff5f47d450(&DAT_7fff624758e0);
    DAT_7fff625e4ee2 = '\x01';
  }
  uVar1 = func_0x7fff5f44ff00(_DAT_7fff624758e0);
  FUN_7fff60a943d0(uVar1,_DAT_7fff624442c0);
  *(undefined8 *)(self + 0x10) = uVar1;
  thunk_FUN_7fff5f491fd0();
  return;
}

