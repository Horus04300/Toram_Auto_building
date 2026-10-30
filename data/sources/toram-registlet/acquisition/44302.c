
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnEventTreasureHuntPopMob
               (undefined *self,undefined *game,undefined *popEvent,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  undefined8 uVar5;
  longlong lVar6;
  undefined8 uVar7;
  longlong lVar8;
  uint uVar9;
  ulonglong uVar10;
  undefined *methodInfo_00;
  
  methodInfo_00 = popEvent;
  if (DAT_7ffe9cae0b37 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(&DAT_7ffe9c96c9c0);
    FUN_7ffe9996d590(&DAT_7ffe9c93aa40);
    DAT_7ffe9cae0b37 = '\x01';
  }
  lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar8 != 0) {
    if (*(longlong **)(lVar8 + 0x28) != (longlong *)0x0) {
      lVar8 = **(longlong **)(lVar8 + 0x28);
      if ((*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) <= *(byte *)(lVar8 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(lVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) * 8)
          == _DAT_7ffe9c96c9c0)) {
        PhotonListener_OnGmTreasureHuntTrialPointMax
                  (_DAT_7ffe9c93aa40,(undefined *)0x0,methodInfo_00);
        lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
        if ((popEvent != (undefined *)0x0) && (lVar8 != 0)) {
          lVar2 = *(longlong *)(popEvent + 0x20);
          if (DAT_7ffe9cadd5f6 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c90ad30,lVar2,0,0);
            FUN_7ffe9996d590(&DAT_7ffe9c91df50);
            FUN_7ffe9996d590(&DAT_7ffe9c906b90);
            DAT_7ffe9cadd5f6 = '\x01';
          }
          if (lVar2 != 0) {
            uVar10 = 0;
            while( true ) {
              uVar9 = (uint)uVar10;
              if ((int)*(uint *)(lVar2 + 0x18) <= (int)uVar9) break;
              if (*(uint *)(lVar2 + 0x18) <= uVar9) {
                FUN_7ffe9996d790();
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              lVar6 = *(longlong *)(lVar8 + 0x48);
              lVar1 = *(longlong *)(lVar2 + 0x20 + (longlong)(int)uVar9 * 8);
              if ((lVar1 == 0) || (uVar5 = FUN_7ffe9bc7e360(lVar1,0), lVar6 == 0)) {
LAB_7ffe9a33bf3b:
                FUN_7ffe9996d7a0();
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              lVar6 = FUN_7ffe9a3472e0(lVar6,uVar5,0);
              uVar10 = 0;
              if (lVar6 != 0) {
                uVar10 = *(ulonglong *)(lVar6 + 0x18);
              }
              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar4 = FUN_7ffe9bda2160(uVar10,0);
              lVar6 = *(longlong *)(lVar8 + 0x48);
              if (cVar4 == '\0') {
                uVar5 = FUN_7ffe9bc7e360(lVar1,0);
                uVar7 = FUN_7ffe997442c0(_DAT_7ffe9c90ad30);
                if ((lVar6 == 0) ||
                   (FUN_7ffe9a344500(lVar6,uVar5,0,0,uVar7,0), *(longlong *)(lVar8 + 0x20) == 0))
                goto LAB_7ffe9a33bf3b;
                FUN_7ffe99743100();
                uVar10 = (ulonglong)(uVar9 + 1);
              }
              else {
                FUN_7ffe9bc7e360(lVar1,0);
                if ((lVar6 == 0) || (FUN_7ffe9a353f90(lVar6), *(longlong *)(lVar8 + 0x48) == 0))
                goto LAB_7ffe9a33bf3b;
                FUN_7ffe9a3531a0();
                uVar10 = (ulonglong)(uVar9 + 1);
              }
            }
          }
          return;
        }
        goto LAB_7ffe9aaae05b;
      }
    }
    return;
  }
LAB_7ffe9aaae05b:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

