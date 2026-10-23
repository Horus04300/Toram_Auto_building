
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_Def(undefined *self,undefined *methodInfo)

{
  short sVar1;
  undefined4 uVar2;
  code *pcVar3;
  float fVar4;
  longlong *plVar5;
  char cVar6;
  byte bVar7;
  int iVar8;
  int iVar9;
  longlong lVar10;
  int iVar11;
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
  iVar11 = 0;
  if (*(longlong *)(self + 0x10) != 0) {
    uVar2 = *(undefined4 *)(*(longlong *)(self + 0x10) + 0x3c);
    sVar1 = *(short *)(self + 0x28);
    if (*(int *)(_DAT_7fff62450e80 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    iVar8 = FUN_7fff61793b90(uVar2,(int)sVar1,0);
    if ((*(longlong *)(self + 0x30) != 0) &&
       (lVar10 = FUN_7fff607dcb60(*(longlong *)(self + 0x30),_DAT_7fff62406640), lVar10 != 0)) {
      FUN_7fff60a4b980(&uStack_70,lVar10,_DAT_7fff62400b90);
      uStack_58 = uStack_70;
      puStack_50 = puStack_68;
      plStack_48 = plStack_60;
      uStack_70 = 0;
      puStack_68 = &uStack_58;
      while (cVar6 = FUN_7fff60941650(&uStack_58), plVar5 = plStack_48, cVar6 != '\0') {
        if (plStack_48 == (longlong *)0x0) goto LAB_7fff5fdb1a2d;
        bVar7 = MobPartsStatus_get_IsDead((undefined *)plStack_48,(undefined *)0x0);
        if (bVar7 == 0) {
          lVar10 = *plVar5;
          iVar9 = (**(code **)(lVar10 + 0x188))(plVar5,*(undefined8 *)(lVar10 + 400));
          iVar11 = iVar11 + iVar9;
        }
      }
      func_0x7fff5f4d3920(&uStack_58,_DAT_7fff6243e768);
      if (*(longlong *)(self + 0x20) != 0) {
        iVar9 = FUN_7fff5fdb72d0(*(longlong *)(self + 0x20),2);
        iVar11 = (int)(((float)iVar9 / _DAT_7fff61b52cfc + _DAT_7fff61b52b18) *
                      (float)(iVar8 + iVar11));
        if (*(longlong *)(self + 0x18) != 0) {
          cVar6 = FUN_7fff5ffe5620(*(longlong *)(self + 0x18),10);
          fVar4 = _DAT_7fff61b52b4c;
          if (cVar6 != '\0') {
            iVar11 = (int)((float)iVar11 * _DAT_7fff61b52b4c);
          }
          if (*(longlong *)(self + 0x18) != 0) {
            cVar6 = FUN_7fff5ffe5620(*(longlong *)(self + 0x18),0x16);
            if (cVar6 != '\0') {
              iVar11 = (int)((float)iVar11 * fVar4);
            }
            return iVar11;
          }
        }
      }
    }
  }
  FUN_7fff5f47d660();
LAB_7fff5fdb1a2d:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar3 = (code *)swi(3);
  iVar11 = (*pcVar3)();
  return iVar11;
}

