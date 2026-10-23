
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BossMobBattleStatus_SetPartsMaster
               (undefined *self,int id,undefined *parts,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  
  if (DAT_7fff625e4927 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406230);
    FUN_7fff5f47d450(&DAT_7fff62400a70);
    FUN_7fff5f47d450(&DAT_7fff624063d0);
    FUN_7fff5f47d450(&DAT_7fff62406710);
    DAT_7fff625e4927 = '\x01';
  }
  if ((*(longlong *)(self + 0x10) != 0) &&
     (lVar1 = *(longlong *)(*(longlong *)(self + 0x10) + 0x90), lVar1 != 0)) {
    cVar4 = FUN_7fff6081b330(lVar1,id,_DAT_7fff62400a70);
    if (cVar4 == '\0') {
      return;
    }
    if (*(longlong *)(self + 0x30) != 0) {
      cVar4 = FUN_7fff6082f170(*(longlong *)(self + 0x30),id,_DAT_7fff624063d0);
      lVar1 = *(longlong *)(self + 0x30);
      if (cVar4 == '\0') {
        if (lVar1 != 0) {
          FUN_7fff60857660(lVar1,id,parts,_DAT_7fff62406230);
          return;
        }
      }
      else if (lVar1 != 0) {
        lVar2 = *(longlong *)(*(longlong *)(_DAT_7fff62406710 + 0x20) + 0xc0);
        FUN_7fff60862e70(lVar1,id,parts,CONCAT71((int7)((ulonglong)lVar2 >> 8),1),
                         *(undefined8 *)(lVar2 + 0x118));
        return;
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

