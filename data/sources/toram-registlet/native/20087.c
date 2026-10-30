
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MasterRegistletManager__ctor(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  undefined8 unaff_RBX;
  undefined8 in_R8;
  undefined8 in_R9;
  
  if (DAT_7ffe9cade7c4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c965b18);
    FUN_7ffe9996d590(&DAT_7ffe9c90d1e0);
    FUN_7ffe9996d590(&DAT_7ffe9c953978);
    DAT_7ffe9cade7c4 = '\x01';
  }
  uVar1 = func_0x7ffe99940040(_DAT_7ffe9c90d1e0);
  FUN_7ffe9ad0cd00(uVar1,_DAT_7ffe9c965b18);
  *(undefined8 *)(self + 0x20) = uVar1;
  il2cpp_write_barrier_0();
  if (DAT_7ffe9cae9700 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90,0,in_R8,in_R9,unaff_RBX);
    DAT_7ffe9cae9700 = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  return;
}

