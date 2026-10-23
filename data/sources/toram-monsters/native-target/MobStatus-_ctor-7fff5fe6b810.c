
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobStatus__ctor(undefined *self,int mobid,undefined *methodInfo)

{
  undefined8 uVar1;
  
  if (DAT_7fff625e4e3b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624100a8);
    FUN_7fff5f47d450(&DAT_7fff623fe0f0);
    DAT_7fff625e4e3b = '\x01';
  }
  *(undefined4 *)(self + 0x18) = 100;
  *(undefined4 *)(self + 0x1c) = 100;
  *(undefined4 *)(self + 0x20) = 100;
  *(undefined4 *)(self + 0x24) = 100;
  *(undefined4 *)(self + 0x28) = 100;
  *(undefined4 *)(self + 0x2c) = 100;
  uVar1 = func_0x7fff5f44ff00(_DAT_7fff623fe0f0);
  FUN_7fff60a943d0(uVar1,_DAT_7fff624100a8);
  *(undefined8 *)(self + 0x30) = uVar1;
  thunk_FUN_7fff5f491fd0();
  func_0x7fff5f4d3920(self,0);
  *(int *)(self + 0x38) = mobid;
  *(undefined2 *)(self + 0x3c) = 0;
  *(undefined4 *)(self + 0x40) = 0xffffffff;
  return;
}

