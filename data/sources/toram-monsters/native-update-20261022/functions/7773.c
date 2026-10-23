
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobBattleStatus__ctor
               (undefined *self,undefined *statusMaster,undefined *abnormalManager,
               undefined *buffManager,int level,undefined *randomProperty,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  undefined8 uVar3;
  undefined *puVar4;
  uint uVar5;
  uint uVar6;
  
  if (DAT_7ffe9cadd515 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff130);
    FUN_7ffe9996d590(&DAT_7ffe9c912c08);
    FUN_7ffe9996d590(&DAT_7ffe9c8efdf8);
    DAT_7ffe9cadd515 = '\x01';
  }
  *(undefined4 *)(self + 0x50) = 1;
  func_0x7ffe999c3920(self,0);
  *(undefined **)(self + 0x20) = statusMaster;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 0x28) = abnormalManager;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 0x30) = buffManager;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 0x48) = randomProperty;
  *(int *)(self + 0x10) = level;
  il2cpp_write_barrier_0();
  uVar3 = func_0x7ffe99940040(_DAT_7ffe9c912c08);
  FUN_7ffe9ad214a0(uVar3,_DAT_7ffe9c8ff130);
  *(undefined8 *)(self + 0x18) = uVar3;
  il2cpp_write_barrier_0();
  uVar3 = func_0x7ffe99940040(_DAT_7ffe9c8efdf8);
  FUN_7ffe9a37ad10(uVar3,0);
  *(undefined8 *)(self + 0x40) = uVar3;
  il2cpp_write_barrier_0();
  if (*(longlong *)(self + 0x40) != 0) {
    FUN_7ffe9a37a850();
    if ((*(longlong *)(self + 0x20) != 0) &&
       (puVar4 = *(undefined **)(*(longlong *)(self + 0x20) + 0xa0), puVar4 != (undefined *)0x0)) {
      puVar4 = MobPropertyManager_GetMobPropertyMasters(puVar4,(undefined *)0x0);
      uVar5 = 0;
      if ((puVar4 != (undefined *)0x0) && (uVar6 = uVar5, *(longlong *)(puVar4 + 0x18) != 0)) {
        for (; (int)uVar6 < (int)*(uint *)(puVar4 + 0x18); uVar6 = uVar6 + 1) {
          if (*(uint *)(puVar4 + 0x18) <= uVar6) goto LAB_7ffe9a31ce10;
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe9a31ce16;
          FUN_7ffe9a37a780(*(longlong *)(self + 0x40),
                           *(undefined8 *)(puVar4 + (longlong)(int)uVar6 * 8 + 0x20),0);
        }
      }
      lVar1 = *(longlong *)(self + 0x48);
      if ((lVar1 != 0) && (*(longlong *)(lVar1 + 0x18) != 0)) {
        for (; (int)uVar5 < *(int *)(lVar1 + 0x18); uVar5 = uVar5 + 1) {
          if (*(uint *)(lVar1 + 0x18) <= uVar5) {
LAB_7ffe9a31ce10:
            FUN_7ffe9996d790();
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe9a31ce16;
          FUN_7ffe9a37a780(*(longlong *)(self + 0x40),
                           *(undefined8 *)(lVar1 + 0x20 + (longlong)(int)uVar5 * 8),0);
        }
      }
      return;
    }
  }
LAB_7ffe9a31ce16:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

