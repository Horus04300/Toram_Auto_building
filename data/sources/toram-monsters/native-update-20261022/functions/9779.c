
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobPropertyStatusCollection__ctor(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  
  if (DAT_7ffe9cadd78a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c93d370,0);
    FUN_7ffe9996d590(&DAT_7ffe9c96de78);
    DAT_7ffe9cadd78a = '\x01';
  }
  uVar1 = func_0x7ffe99940040(_DAT_7ffe9c96de78);
  FUN_7ffe9af8a010(uVar1,_DAT_7ffe9c93d370);
  *(undefined8 *)(self + 0x10) = uVar1;
  il2cpp_write_barrier_0();
  return;
}

