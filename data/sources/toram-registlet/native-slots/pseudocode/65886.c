
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * UIRegistletEditPanel_AddSlot(undefined *self,undefined *methodInfo)

{
  undefined *puVar1;
  
  if (DAT_7ffe9cadc32c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fb4c8);
    DAT_7ffe9cadc32c = '\x01';
  }
  puVar1 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8fb4c8);
  func_0x7ffe999c3920(puVar1,0);
  *(undefined **)(puVar1 + 0x20) = self;
  *(undefined4 *)(puVar1 + 0x10) = 0;
  il2cpp_write_barrier_0();
  return puVar1;
}

