
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusScriptData_AddBonus(undefined *self,int type,int val,byte instant,undefined *methodInfo)

{
  undefined4 uVar1;
  uint uVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  longlong lVar6;
  undefined *puVar7;
  undefined8 uVar8;
  longlong lVar9;
  undefined4 in_register_00000084;
  undefined *methodInfo_00;
  
  methodInfo_00 = (undefined *)CONCAT44(in_register_00000084,val);
  if (DAT_7fff625e5891 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624124f8);
    FUN_7fff5f47d450(&DAT_7fff624493c8);
    FUN_7fff5f47d450(&DAT_7fff624520b0);
    FUN_7fff5f47d450(&DAT_7fff62452488);
    FUN_7fff5f47d450(&DAT_7fff62437450);
    FUN_7fff5f47d450(&DAT_7fff624206c8);
    FUN_7fff5f47d450(&DAT_7fff6242c758);
    DAT_7fff625e5891 = '\x01';
  }
  puVar7 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242c758);
  MainPlayer_OnSkillDelayStandbyOk(puVar7,0,methodInfo_00);
  if (puVar7 != (undefined *)0x0) {
    *(int *)(puVar7 + 0x10) = type;
    if (instant == 0) {
      uVar3 = *(undefined8 *)(self + 0x10);
      uVar8 = func_0x7fff5f44ff00(_DAT_7fff624493c8);
      FUN_7fff60a1d7e0(uVar8,puVar7,_DAT_7fff624206c8,0);
      lVar9 = FUN_7fff6068f870(uVar3,uVar8,_DAT_7fff624124f8);
      if (0 < *(int *)(self + 0x74)) {
        if (lVar9 != 0) {
          val = val + *(int *)(lVar9 + 0x14);
        }
        *(int *)(self + 0x74) = *(int *)(self + 0x74) + -1;
      }
      if (*(longlong *)(self + 0x10) == 0) goto LAB_7fff600003ec;
      methodInfo_00 = _DAT_7fff62452488;
      FUN_7fff60ae6370();
    }
    lVar9 = *(longlong *)(self + 0x10);
    uVar1 = *(undefined4 *)(puVar7 + 0x10);
    puVar7 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62437450);
    MainPlayer_OnSkillDelayStandbyOk(puVar7,0,methodInfo_00);
    *(undefined4 *)(puVar7 + 0x10) = uVar1;
    *(int *)(puVar7 + 0x14) = val;
    puVar7[0x18] = instant;
    lVar6 = _DAT_7fff624520b0;
    if (lVar9 != 0) {
      *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
      lVar4 = *(longlong *)(lVar9 + 0x10);
      uVar2 = *(uint *)(lVar9 + 0x18);
      if (lVar4 != 0) {
        if (uVar2 < *(uint *)(lVar4 + 0x18)) {
          *(uint *)(lVar9 + 0x18) = uVar2 + 1;
          if (*(uint *)(lVar4 + 0x18) <= uVar2) {
            FUN_7fff5f47d650();
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
          *(undefined **)(lVar4 + (longlong)(int)uVar2 * 8 + 0x20) = puVar7;
          thunk_FUN_7fff5f491fd0();
        }
        else {
          FUN_7fff60adfc70(lVar9,puVar7,
                           *(undefined8 *)(*(longlong *)(*(longlong *)(lVar6 + 0x20) + 0xc0) + 0x70)
                          );
        }
        return;
      }
    }
  }
LAB_7fff600003ec:
  FUN_7fff5f47d660();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

