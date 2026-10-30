
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RegistletTextManager__ctor(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  
  if (DAT_7ffe9cad9de4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9038b0);
    FUN_7ffe9996d590(&DAT_7ffe9c913768);
    DAT_7ffe9cad9de4 = '\x01';
  }
  uVar1 = func_0x7ffe99940040(_DAT_7ffe9c913768);
  FUN_7ffe9ad214a0(uVar1,_DAT_7ffe9c9038b0);
  *(undefined8 *)(self + 0x18) = uVar1;
  il2cpp_write_barrier_0();
  func_0x7ffe999c3920(self,0);
  self[0x12] = 0;
  return;
}

