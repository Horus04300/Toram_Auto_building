
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AutoMemberAITactical__ctor(undefined *thisObject,undefined *methodInfo)

{
  undefined8 uVar1;
  
  if (DAT_7ffe9cae04dc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fa490);
    FUN_7ffe9996d590(&DAT_7ffe9c961c10);
    DAT_7ffe9cae04dc = '\x01';
  }
  uVar1 = func_0x7ffe99940040(_DAT_7ffe9c961c10);
  FUN_7ffe9af8a010(uVar1,_DAT_7ffe9c8fa490);
  *(undefined8 *)(thisObject + 0x30) = uVar1;
  il2cpp_write_barrier_0();
  return;
}

