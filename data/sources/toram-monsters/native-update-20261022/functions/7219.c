
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_Def(undefined *self,undefined *methodInfo)

{
  short sVar1;
  code *pcVar2;
  float fVar3;
  longlong *plVar4;
  char cVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  int iVar10;
  undefined8 uStack_70;
  undefined8 *puStack_68;
  longlong *plStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_50;
  longlong *plStack_48;
  
  if (DAT_7ffe9cadd1d3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949540);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c937818);
    FUN_7ffe9996d590(&DAT_7ffe9c9378d8);
    FUN_7ffe9996d590(0x7ffe9c9379a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9b60);
    DAT_7ffe9cadd1d3 = '\x01';
  }
  iVar10 = 0;
  if (*(longlong *)(self + 0x10) != 0) {
    iVar7 = *(int *)(*(longlong *)(self + 0x10) + 0x3c);
    sVar1 = *(short *)(self + 0x28);
    if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    iVar7 = Toram_Common_Rooms_BossDifficultyLevelMethods_GetStatusRate
                      (iVar7,(int)sVar1,(undefined *)0x0);
    if ((*(longlong *)(self + 0x30) != 0) &&
       (lVar9 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x30),_DAT_7ffe9c8ff610), lVar9 != 0)) {
      FUN_7ffe9af415c0(&uStack_70,lVar9,_DAT_7ffe9c8f9b60);
      uStack_58 = uStack_70;
      puStack_50 = puStack_68;
      plStack_48 = plStack_60;
      uStack_70 = 0;
      puStack_68 = &uStack_58;
      while (cVar5 = FUN_7ffe9ae37290(&uStack_58), plVar4 = plStack_48, cVar5 != '\0') {
        if (plStack_48 == (longlong *)0x0) goto LAB_7ffe9a2a6bed;
        bVar6 = MobPartsStatus_get_IsDead((undefined *)plStack_48,(undefined *)0x0);
        if (bVar6 == 0) {
          lVar9 = *plVar4;
          iVar8 = (**(code **)(lVar9 + 0x188))(plVar4,*(undefined8 *)(lVar9 + 400));
          iVar10 = iVar10 + iVar8;
        }
      }
      func_0x7ffe999c3920(&uStack_58,_DAT_7ffe9c937818);
      if (*(longlong *)(self + 0x20) != 0) {
        iVar8 = FUN_7ffe9a2ac490(*(longlong *)(self + 0x20),2);
        iVar10 = (int)(((float)iVar8 / _DAT_7ffe9c049cfc + _DAT_7ffe9c049b18) *
                      (float)(iVar7 + iVar10));
        if (*(longlong *)(self + 0x18) != 0) {
          cVar5 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),10);
          fVar3 = _DAT_7ffe9c049b4c;
          if (cVar5 != '\0') {
            iVar10 = (int)((float)iVar10 * _DAT_7ffe9c049b4c);
          }
          if (*(longlong *)(self + 0x18) != 0) {
            cVar5 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),0x16);
            if (cVar5 != '\0') {
              iVar10 = (int)((float)iVar10 * fVar3);
            }
            return iVar10;
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
LAB_7ffe9a2a6bed:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar2 = (code *)swi(3);
  iVar10 = (*pcVar2)();
  return iVar10;
}

