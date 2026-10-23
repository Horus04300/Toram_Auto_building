
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobBattleStatus_InitializeMobProperty(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  undefined *puVar3;
  uint uVar4;
  uint uVar5;
  
  if (*(longlong *)(self + 0x40) != 0) {
    FUN_7ffe9a37a850();
    if ((*(longlong *)(self + 0x20) != 0) &&
       (puVar3 = *(undefined **)(*(longlong *)(self + 0x20) + 0xa0), puVar3 != (undefined *)0x0)) {
      puVar3 = MobPropertyManager_GetMobPropertyMasters(puVar3,(undefined *)0x0);
      uVar5 = 0;
      if ((puVar3 != (undefined *)0x0) && (uVar4 = uVar5, *(longlong *)(puVar3 + 0x18) != 0)) {
        for (; (int)uVar4 < (int)*(uint *)(puVar3 + 0x18); uVar4 = uVar4 + 1) {
          if (*(uint *)(puVar3 + 0x18) <= uVar4) goto LAB_7ffe9a31ca8c;
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe9a31ca92;
          FUN_7ffe9a37a780(*(longlong *)(self + 0x40),
                           *(undefined8 *)(puVar3 + (longlong)(int)uVar4 * 8 + 0x20),0);
        }
      }
      lVar1 = *(longlong *)(self + 0x48);
      if ((lVar1 != 0) && (*(longlong *)(lVar1 + 0x18) != 0)) {
        for (; (int)uVar5 < *(int *)(lVar1 + 0x18); uVar5 = uVar5 + 1) {
          if (*(uint *)(lVar1 + 0x18) <= uVar5) {
LAB_7ffe9a31ca8c:
            FUN_7ffe9996d790();
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe9a31ca92;
          FUN_7ffe9a37a780(*(longlong *)(self + 0x40),
                           *(undefined8 *)(lVar1 + 0x20 + (longlong)(int)uVar5 * 8),0);
        }
      }
      return;
    }
  }
LAB_7ffe9a31ca92:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

