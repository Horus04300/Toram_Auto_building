
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobPartsStatus__ctor
               (undefined *self,undefined *statusMaster,int hp,short difficulty,
               undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  
  if (DAT_7fff625e4e1b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62430838);
    DAT_7fff625e4e1b = '\x01';
  }
  func_0x7fff5f4d3920(self,0);
  *(short *)(self + 0x10) = difficulty;
  *(undefined **)(self + 0x28) = statusMaster;
  thunk_FUN_7fff5f491fd0();
  if ((*(longlong *)(self + 0x28) != 0) &&
     (lVar1 = *(longlong *)(*(longlong *)(self + 0x28) + 0xa0), lVar1 != 0)) {
    FUN_7fff606c2a90(lVar1,8,self + 0x20,_DAT_7fff62430838);
    if ((*(longlong *)(self + 0x28) != 0) &&
       (lVar1 = *(longlong *)(*(longlong *)(self + 0x28) + 0xa0), lVar1 != 0)) {
      FUN_7fff606c2a90(lVar1,7,self + 0x18,_DAT_7fff62430838);
      *(int *)(self + 0x34) = hp;
      *(int *)(self + 0x30) = hp;
      return;
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

