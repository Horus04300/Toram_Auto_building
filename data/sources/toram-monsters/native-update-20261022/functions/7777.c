
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobBattleStatus_SetPartsMaster
               (undefined *self,int id,undefined *parts,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  
  if (DAT_7ffe9cadd518 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff200);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9a40);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff3a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff6e0);
    DAT_7ffe9cadd518 = '\x01';
  }
  if ((*(longlong *)(self + 0x20) != 0) &&
     (lVar1 = *(longlong *)(*(longlong *)(self + 0x20) + 0x90), lVar1 != 0)) {
    cVar4 = FUN_7ffe9ad10f70(lVar1,id,_DAT_7ffe9c8f9a40);
    if (cVar4 == '\0') {
      return;
    }
    if (*(longlong *)(self + 0x18) != 0) {
      cVar4 = FUN_7ffe9ad24db0(*(longlong *)(self + 0x18),id,_DAT_7ffe9c8ff3a0);
      lVar1 = *(longlong *)(self + 0x18);
      if (cVar4 == '\0') {
        if (lVar1 != 0) {
          FUN_7ffe9ad4d2a0(lVar1,id,parts,_DAT_7ffe9c8ff200);
          return;
        }
      }
      else if (lVar1 != 0) {
        lVar2 = *(longlong *)(*(longlong *)(_DAT_7ffe9c8ff6e0 + 0x20) + 0xc0);
        FUN_7ffe9ad58ab0(lVar1,id,parts,CONCAT71((int7)((ulonglong)lVar2 >> 8),1),
                         *(undefined8 *)(lVar2 + 0x118));
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

