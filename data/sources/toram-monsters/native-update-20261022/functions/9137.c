
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobStatus__ctor(undefined *self,int mobid,undefined *methodInfo)

{
  undefined8 uVar1;
  
  if (DAT_7ffe9cadd6e3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c909078);
    FUN_7ffe9996d590(&DAT_7ffe9c8f6560);
    DAT_7ffe9cadd6e3 = '\x01';
  }
  *(undefined4 *)(self + 0x18) = 100;
  *(undefined4 *)(self + 0x1c) = 100;
  *(undefined4 *)(self + 0x20) = 100;
  *(undefined4 *)(self + 0x24) = 100;
  *(undefined4 *)(self + 0x28) = 100;
  *(undefined4 *)(self + 0x2c) = 100;
  uVar1 = func_0x7ffe99940040(_DAT_7ffe9c8f6560);
  FUN_7ffe9af8a010(uVar1,_DAT_7ffe9c909078);
  *(undefined8 *)(self + 0x30) = uVar1;
  il2cpp_write_barrier_0();
  func_0x7ffe999c3920(self,0);
  *(int *)(self + 0x38) = mobid;
  *(undefined2 *)(self + 0x3c) = 0;
  *(undefined4 *)(self + 0x40) = 0xffffffff;
  return;
}

