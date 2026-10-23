
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobBattleStatus_InitializeMobProperty(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  
  if (*(longlong *)(self + 0x40) != 0) {
    FUN_7fff5fe85400(*(longlong *)(self + 0x40),0);
    if ((*(longlong *)(self + 0x20) != 0) &&
       (lVar2 = *(longlong *)(*(longlong *)(self + 0x20) + 0xa0), lVar2 != 0)) {
      lVar2 = FUN_7fff5fe85450(lVar2,0);
      uVar4 = 0;
      if ((lVar2 != 0) && (uVar3 = uVar4, *(longlong *)(lVar2 + 0x18) != 0)) {
        for (; (int)uVar3 < (int)*(uint *)(lVar2 + 0x18); uVar3 = uVar3 + 1) {
          if (*(uint *)(lVar2 + 0x18) <= uVar3) goto LAB_7fff5fe2775c;
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff5fe27762;
          FUN_7fff5fe85330(*(longlong *)(self + 0x40),
                           *(undefined8 *)(lVar2 + 0x20 + (longlong)(int)uVar3 * 8),0);
        }
      }
      lVar2 = *(longlong *)(self + 0x48);
      if ((lVar2 != 0) && (*(longlong *)(lVar2 + 0x18) != 0)) {
        for (; (int)uVar4 < *(int *)(lVar2 + 0x18); uVar4 = uVar4 + 1) {
          if (*(uint *)(lVar2 + 0x18) <= uVar4) {
LAB_7fff5fe2775c:
            FUN_7fff5f47d650();
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff5fe27762;
          FUN_7fff5fe85330(*(longlong *)(self + 0x40),
                           *(undefined8 *)(lVar2 + 0x20 + (longlong)(int)uVar4 * 8),0);
        }
      }
      return;
    }
  }
LAB_7fff5fe27762:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

