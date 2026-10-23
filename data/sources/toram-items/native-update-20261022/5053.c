
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MainPlayer_localUseItem(undefined *self,int uuid,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  longlong lVar3;
  undefined *bonusLines;
  undefined *puVar4;
  undefined8 uVar5;
  
  if (DAT_7ffe9cadaef8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f5b58);
    FUN_7ffe9996d590(&DAT_7ffe9c94b3a8);
    FUN_7ffe9996d590(0x7ffe9c908b50);
    FUN_7ffe9996d590(&DAT_7ffe9c95d488);
    FUN_7ffe9996d590(&DAT_7ffe9c96fcd0);
    DAT_7ffe9cadaef8 = '\x01';
  }
  lVar2 = func_0x7ffe99940040(_DAT_7ffe9c96fcd0);
  func_0x7ffe999c3920(lVar2,0);
  if (lVar2 != 0) {
    *(undefined **)(lVar2 + 0x10) = self;
    il2cpp_write_barrier_0();
    if (*(longlong *)(self + 0xe0) != 0) {
      lVar3 = FUN_7ffe9a5713d0(*(longlong *)(self + 0xe0),uuid,0);
      *(undefined8 *)(lVar2 + 0x18) = 0;
      il2cpp_write_barrier_0();
      if (lVar3 == 0) {
LAB_7ffe99d02911:
        return *(undefined **)(lVar2 + 0x18);
      }
      puVar4 = *(undefined **)(self + 0x100);
      bonusLines = (undefined *)FUN_7ffe9a56fc30(lVar3,0);
      if (puVar4 != (undefined *)0x0) {
        puVar4 = BonusManager_CreateBonus(puVar4,bonusLines,1,(undefined *)0x0);
        *(undefined **)(lVar2 + 0x18) = puVar4;
        il2cpp_write_barrier_0();
        if ((*(longlong *)(lVar2 + 0x18) != 0) &&
           (lVar3 = *(longlong *)(*(longlong *)(lVar2 + 0x18) + 0x38), lVar3 != 0)) {
          if (0 < *(int *)(lVar3 + 0x18)) {
            if (*(longlong *)(self + 0x100) == 0) goto LAB_7ffe99d0292f;
            FUN_7ffe9a4ec380();
          }
          puVar4 = *(undefined **)(lVar2 + 0x18);
          if (puVar4 != (undefined *)0x0) {
            if (*(int *)(puVar4 + 0x44) != 0) {
              if (*(longlong *)(puVar4 + 0x10) == 0) goto LAB_7ffe99d0292f;
              if (*(char *)(*(longlong *)(puVar4 + 0x10) + 0x38) == '\0') {
                if (*(undefined **)(self + 0x100) != (undefined *)0x0) {
                  BonusManager_SetDurationBonus
                            (*(undefined **)(self + 0x100),puVar4,(undefined *)0x0);
                  goto LAB_7ffe99d02911;
                }
                goto LAB_7ffe99d0292f;
              }
            }
            lVar3 = *(longlong *)(puVar4 + 0x20);
            uVar5 = func_0x7ffe99940040(_DAT_7ffe9c8f5b58);
            FUN_7ffe9a2f3fb0(uVar5,lVar2,_DAT_7ffe9c95d488,0);
            if (lVar3 != 0) {
              FUN_7ffe9af83580(lVar3,uVar5,_DAT_7ffe9c94b3a8);
              goto LAB_7ffe99d02911;
            }
          }
        }
      }
    }
  }
LAB_7ffe99d0292f:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar4 = (undefined *)(*pcVar1)();
  return puVar4;
}

