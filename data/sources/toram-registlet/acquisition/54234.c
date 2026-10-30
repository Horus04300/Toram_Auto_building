
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UITreasureHuntEnterManager_DropCategoryBox
                (undefined *self,float y,undefined *rank,undefined *rewardItem,undefined *methodInfo
                )

{
  longlong lVar1;
  undefined8 uVar2;
  code *pcVar3;
  undefined4 uVar4;
  undefined *puVar5;
  longlong lVar6;
  longlong lVar7;
  uint uVar8;
  float fVar9;
  undefined8 uStack_38;
  undefined4 uStack_30;
  
  if (DAT_7ffe9cadab8c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3cc8);
    DAT_7ffe9cadab8c = '\x01';
  }
  if (rewardItem != (undefined *)0x0) {
    uVar8 = 0;
    fVar9 = UITreasureHuntEnterManager_AddDropCategoryButton
                      (self,y,(int)rank,*(int *)(rewardItem + 0x18),(undefined *)0x0);
    uVar4 = _DAT_7ffe9c049f40;
    while( true ) {
      if ((int)*(uint *)(rewardItem + 0x18) <= (int)uVar8) {
        if (*(int *)(_DAT_7ffe9c8f3cc8 + 0xe0) == 0) {
          func_0x7ffe9996d830(_DAT_7ffe9c8f3cc8,uVar8);
        }
        return fVar9;
      }
      if (*(uint *)(rewardItem + 0x18) <= uVar8) {
        FUN_7ffe9996d790();
        pcVar3 = (code *)swi(3);
        fVar9 = (float)(*pcVar3)();
        return fVar9;
      }
      lVar1 = *(longlong *)(self + 0xf8);
      lVar6 = *(longlong *)(rewardItem + (longlong)(int)uVar8 * 8 + 0x20);
      if (DAT_7ffe9cadab8e == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c93a5d8);
        FUN_7ffe9996d590(&DAT_7ffe9c906b90);
        DAT_7ffe9cadab8e = '\x01';
      }
      if ((lVar6 == 0) || (*(longlong *)(self + 0x108) == 0)) break;
      FUN_7ffe9a26e830(*(longlong *)(self + 0x108),*(undefined1 *)(lVar6 + 0x20),
                       *(undefined4 *)(lVar6 + 0x24));
      lVar7 = *(longlong *)(self + 0x110);
      puVar5 = UITreasureHuntEnterManager_GetDropItemName
                         (self,(undefined *)(ulonglong)*(byte *)(lVar6 + 0x20),
                          *(int *)(lVar6 + 0x24),(undefined *)0x0);
      if (lVar7 == 0) break;
      FUN_7ffe9a404310(lVar7,puVar5,0);
      uVar2 = *(undefined8 *)(self + 0x100);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      lVar6 = FUN_7ffe9abbb520(uVar2,_DAT_7ffe9c93a5d8);
      if (lVar6 == 0) break;
      FUN_7ffe9bd9b390(lVar6,1,0);
      lVar7 = FUN_7ffe9bd9b890(lVar6,0);
      if (lVar7 == 0) break;
      uStack_38 = CONCAT44(fVar9,uVar4);
      uStack_30 = 0;
      FUN_7ffe9bdbfcc0(lVar7,&uStack_38,0);
      if (lVar1 == 0) break;
      FUN_7ffe9a2c47a0(lVar1,lVar6,0);
      if (*(int *)(_DAT_7ffe9c8f3cc8 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar8 = uVar8 + 1;
      fVar9 = fVar9 - **(float **)(_DAT_7ffe9c8f3cc8 + 0xb8);
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  fVar9 = (float)(*pcVar3)();
  return fVar9;
}

