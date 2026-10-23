
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobPartsStatus__ctor
               (undefined *self,undefined *statusMaster,int hp,short difficulty,
               undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  
  if (DAT_7ffe9cadd6c3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c929990);
    DAT_7ffe9cadd6c3 = '\x01';
  }
  func_0x7ffe999c3920(self,0);
  *(short *)(self + 0x10) = difficulty;
  *(undefined **)(self + 0x28) = statusMaster;
  il2cpp_write_barrier_0();
  if ((*(longlong *)(self + 0x28) != 0) &&
     (lVar1 = *(longlong *)(*(longlong *)(self + 0x28) + 0xa0), lVar1 != 0)) {
    FUN_7ffe9abb86e0(lVar1,8,self + 0x20,_DAT_7ffe9c929990);
    if ((*(longlong *)(self + 0x28) != 0) &&
       (lVar1 = *(longlong *)(*(longlong *)(self + 0x28) + 0xa0), lVar1 != 0)) {
      FUN_7ffe9abb86e0(lVar1,7,self + 0x18,_DAT_7ffe9c929990);
      *(int *)(self + 0x34) = hp;
      *(int *)(self + 0x30) = hp;
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

