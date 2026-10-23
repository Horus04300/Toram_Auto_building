
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_Def(undefined *self,undefined *methodInfo)

{
  short sVar1;
  code *pcVar2;
  float fVar3;
  longlong *plVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  int iVar9;
  undefined8 uStack_70;
  undefined8 *puStack_68;
  longlong *plStack_60;
  undefined8 uStack_58;
  undefined8 *puStack_50;
  longlong *plStack_48;
  
  if (DAT_7fff625e492e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450e80);
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff6243e768);
    FUN_7fff5f47d450(&DAT_7fff6243e830);
    FUN_7fff5f47d450(0x7fff6243e8f0);
    FUN_7fff5f47d450(&DAT_7fff62400b90);
    DAT_7fff625e492e = '\x01';
  }
  iVar9 = 0;
  if (*(longlong *)(self + 0x10) != 0) {
    iVar6 = *(int *)(*(longlong *)(self + 0x10) + 0x3c);
    sVar1 = *(short *)(self + 0x28);
    if (*(int *)(_DAT_7fff62450e80 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    iVar6 = Toram_Common_Rooms_BossDifficultyLevelMethods_GetStatusRate
                      (iVar6,(int)sVar1,(undefined *)0x0);
    if ((*(longlong *)(self + 0x30) != 0) &&
       (lVar8 = FUN_7fff607dcb60(*(longlong *)(self + 0x30),_DAT_7fff62406640), lVar8 != 0)) {
      FUN_7fff60a4b980(&uStack_70,lVar8,_DAT_7fff62400b90);
      uStack_58 = uStack_70;
      puStack_50 = puStack_68;
      plStack_48 = plStack_60;
      uStack_70 = 0;
      puStack_68 = &uStack_58;
      while (cVar5 = FUN_7fff60941650(&uStack_58,_DAT_7fff6243e830), plVar4 = plStack_48,
            cVar5 != '\0') {
        if (plStack_48 == (longlong *)0x0) goto LAB_7fff5fdb1a2d;
        cVar5 = func_0x7fff5fe666a0(plStack_48,0);
        if (cVar5 == '\0') {
          lVar8 = *plVar4;
          iVar7 = (**(code **)(lVar8 + 0x188))(plVar4,*(undefined8 *)(lVar8 + 400));
          iVar9 = iVar9 + iVar7;
        }
      }
      func_0x7fff5f4d3920(&uStack_58,_DAT_7fff6243e768);
      if (*(longlong *)(self + 0x20) != 0) {
        iVar7 = FUN_7fff5fdb72d0(*(longlong *)(self + 0x20),2);
        iVar9 = (int)(((float)iVar7 / _DAT_7fff61b52cfc + _DAT_7fff61b52b18) *
                     (float)(iVar6 + iVar9));
        if (*(longlong *)(self + 0x18) != 0) {
          cVar5 = FUN_7fff5ffe5620(*(longlong *)(self + 0x18),10);
          fVar3 = _DAT_7fff61b52b4c;
          if (cVar5 != '\0') {
            iVar9 = (int)((float)iVar9 * _DAT_7fff61b52b4c);
          }
          if (*(longlong *)(self + 0x18) != 0) {
            cVar5 = FUN_7fff5ffe5620(*(longlong *)(self + 0x18),0x16);
            if (cVar5 != '\0') {
              iVar9 = (int)((float)iVar9 * fVar3);
            }
            return iVar9;
          }
        }
      }
    }
  }
  FUN_7fff5f47d660();
LAB_7fff5fdb1a2d:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar2 = (code *)swi(3);
  iVar9 = (*pcVar2)();
  return iVar9;
}

