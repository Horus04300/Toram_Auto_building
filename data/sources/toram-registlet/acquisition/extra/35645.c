
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GameManager_CheckTreasureHuntRoom
               (undefined *self,int fieldId,byte roomId,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  longlong lVar3;
  undefined1 uVar4;
  char cVar5;
  undefined1 uVar6;
  longlong lVar7;
  undefined4 in_register_00000014;
  undefined7 in_register_00000081;
  longlong lVar8;
  
  if (DAT_7ffe9cadfcf5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c957778,CONCAT44(in_register_00000014,fieldId),
                     CONCAT71(in_register_00000081,roomId));
    FUN_7ffe9996d590(&DAT_7ffe9c954d60);
    DAT_7ffe9cadfcf5 = '\x01';
  }
  FUN_7ffe9bb996e0(*(undefined8 *)(self + 0x30),fieldId,roomId,0);
  lVar3 = FUN_7ffe9b141840(_DAT_7ffe9c954d60);
  lVar7 = func_0x7ffe99940040(_DAT_7ffe9c957778);
  FUN_7ffe9aadaf10(lVar7,fieldId,roomId,0);
  if (lVar3 == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  if (DAT_7ffe9cae0cbb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c951048,lVar7,0);
    FUN_7ffe9996d590(&DAT_7ffe9c947e18);
    FUN_7ffe9996d590(&DAT_7ffe9c951290);
    FUN_7ffe9996d590(&DAT_7ffe9c947fa0);
    FUN_7ffe9996d590(&DAT_7ffe9c950f80);
    FUN_7ffe9996d590(&DAT_7ffe9c9090e8);
    FUN_7ffe9996d590(&DAT_7ffe9c941c90);
    DAT_7ffe9cae0cbb = '\x01';
  }
  lVar1 = *(longlong *)(lVar3 + 0x30);
  lVar8 = 0;
  if (lVar7 != 0) {
    uVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c941c90,lVar7);
    if (lVar1 != 0) {
      cVar5 = FUN_7ffe9acf70d0(lVar1,uVar4,&stack0x00000008,_DAT_7ffe9c947fa0);
      if (cVar5 == '\0') {
        lVar8 = func_0x7ffe99940040(_DAT_7ffe9c9090e8);
        FUN_7ffe9ace8a00(lVar8,_DAT_7ffe9c950f80);
        lVar1 = *(longlong *)(lVar3 + 0x30);
        uVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c941c90,lVar7);
        if (lVar1 == 0) goto LAB_7ffe9aae5d9d;
        FUN_7ffe9aceb930(lVar1,uVar4,lVar8,_DAT_7ffe9c947e18);
      }
      uVar4 = FUN_7ffe99742ec0(1,_DAT_7ffe9c941c90,lVar7);
      if (lVar8 != 0) {
        FUN_7ffe9acf0120(lVar8,uVar4,_DAT_7ffe9c951290);
        uVar4 = FUN_7ffe99742ec0(1,_DAT_7ffe9c941c90,lVar7);
        if (lVar8 != 0) {
          FUN_7ffe9aceb930(lVar8,uVar4,lVar7,_DAT_7ffe9c951048);
          uVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c941c90,lVar7);
          uVar6 = FUN_7ffe99742ec0(1,_DAT_7ffe9c941c90,lVar7);
          FUN_7ffe9aae6230(lVar3,uVar4,uVar6,0);
          return;
        }
      }
    }
  }
LAB_7ffe9aae5d9d:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

