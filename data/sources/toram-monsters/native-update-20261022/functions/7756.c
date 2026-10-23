
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus_get_CutAttack(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  longlong lVar6;
  
  if (DAT_7ffe9cadd510 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c91bcc0);
    FUN_7ffe9996d590(&DAT_7ffe9c93f070);
    FUN_7ffe9996d590(&DAT_7ffe9c9485d8);
    FUN_7ffe9996d590(&DAT_7ffe9c95a5b8);
    DAT_7ffe9cadd510 = '\x01';
  }
  if (*(longlong *)(self + 0x20) != 0) {
    iVar4 = *(int *)(*(longlong *)(self + 0x20) + 0x44);
    if (*(longlong *)(self + 0x18) != 0) {
      uVar5 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x18),_DAT_7ffe9c8ff610);
      if (*(int *)(_DAT_7ffe9c95a5b8 + 0xe0) == 0) {
        func_0x7ffe9996d830(_DAT_7ffe9c95a5b8);
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_7ffe9c95a5b8 + 0xb8) + 0x20);
      if (lVar6 == 0) {
        if (*(int *)(_DAT_7ffe9c95a5b8 + 0xe0) == 0) {
          func_0x7ffe9996d830(_DAT_7ffe9c95a5b8);
        }
        uVar1 = **(undefined8 **)(_DAT_7ffe9c95a5b8 + 0xb8);
        lVar6 = func_0x7ffe99940040(_DAT_7ffe9c93f070);
        FUN_7ffe9af15670(lVar6,uVar1,_DAT_7ffe9c9485d8,0);
        *(longlong *)(*(longlong *)(_DAT_7ffe9c95a5b8 + 0xb8) + 0x20) = lVar6;
        il2cpp_write_barrier_0();
      }
      iVar3 = FUN_7ffe9ab8ff30(uVar5,lVar6,_DAT_7ffe9c91bcc0);
      return *(int *)(self + 0x10) / 10 + iVar4 + iVar3;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

