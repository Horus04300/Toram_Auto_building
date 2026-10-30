
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIRegistletMainManager_GetDescriptionValueText
          (undefined *self,undefined *id,int lv,int baseValue,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  longlong lVar3;
  undefined8 uVar4;
  int iVar5;
  undefined8 uVar6;
  uint uVar7;
  int aiStackX_10 [2];
  float afStack_28 [4];
  
  uVar7 = (uint)id;
  if (DAT_7ffe9cadc34f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949440);
    FUN_7ffe9996d590(&DAT_7ffe9c8f5220);
    FUN_7ffe9996d590(&DAT_7ffe9c8f5150);
    DAT_7ffe9cadc34f = '\x01';
  }
  if ((uVar7 == 0xcd) || (uVar7 == 0xce)) {
    iVar5 = lv * baseValue;
  }
  else {
    if (uVar7 == 0x2c) {
      afStack_28[0] = ((float)baseValue / _DAT_7ffe9c049cfc) * (float)lv + _DAT_7ffe9c049b18;
      uVar4 = func_0x7ffe9996c8e0(_DAT_7ffe9c949440,afStack_28);
      uVar6 = _DAT_7ffe9c8f5220;
      goto LAB_7ffe9a04dcd7;
    }
    iVar5 = lv * baseValue;
    if (uVar7 != 0x4c) {
      if ((uVar7 - 0x18 < 3) || (aiStackX_10[0] = iVar5, uVar7 == 0x20)) {
        aiStackX_10[0] = baseValue - lv;
      }
      if (((uVar7 < 0x27) && ((0x4a20000000U >> ((longlong)(int)uVar7 & 0x3fU) & 1) != 0)) ||
         (uVar7 == 0x29)) {
        aiStackX_10[0] = lv + baseValue;
      }
      if (uVar7 == 0x25) {
        aiStackX_10[0] = (baseValue - lv) + 1;
        puVar2 = (undefined *)FUN_7ffe9b5043c0(aiStackX_10,0);
        return puVar2;
      }
      if (uVar7 == 0x2a) {
        aiStackX_10[0] = baseValue + lv * -100 + 100;
        puVar2 = (undefined *)FUN_7ffe9b5043c0(aiStackX_10,0);
        return puVar2;
      }
      if (uVar7 == 0xcf) {
        if ((*(longlong *)(self + 0xd0) != 0) &&
           (lVar3 = FUN_7ffe9a480590(*(longlong *)(self + 0xd0),0), lVar3 != 0)) {
          iVar5 = FUN_7ffe9a7fd580(lVar3,0x6b,1,0);
          aiStackX_10[0] = (iVar5 + lv) / 2;
          puVar2 = (undefined *)FUN_7ffe9b5043c0(aiStackX_10,0);
          return puVar2;
        }
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        puVar2 = (undefined *)(*pcVar1)();
        return puVar2;
      }
      if (uVar7 == 0xd3) {
        aiStackX_10[0] = baseValue + lv * -10 + 10;
        puVar2 = (undefined *)FUN_7ffe9b5043c0(aiStackX_10,0);
        return puVar2;
      }
      if ((uVar7 - 0x3f3 < 2) || (uVar7 == 0x3f5)) {
        aiStackX_10[0] = ~lv * baseValue + 100;
      }
      if (uVar7 == 0x406) {
        aiStackX_10[0] = 300;
LAB_7ffe9a04dc45:
        aiStackX_10[0] = aiStackX_10[0] - iVar5;
LAB_7ffe9a04dc4a:
        puVar2 = (undefined *)FUN_7ffe9b5043c0(aiStackX_10,0);
        return puVar2;
      }
      if (uVar7 != 0x407) {
        if (uVar7 != 0x412) {
          if (uVar7 == 0x40f) {
            aiStackX_10[0] = 0x3c;
          }
          else {
            if (uVar7 == 0x415) {
              aiStackX_10[0] = (4 - lv) * baseValue;
              puVar2 = (undefined *)FUN_7ffe9b5043c0(aiStackX_10,0);
              return puVar2;
            }
            if (uVar7 == 0x417) {
              aiStackX_10[0] = 0xf - lv;
              puVar2 = (undefined *)FUN_7ffe9b5043c0(aiStackX_10,0);
              return puVar2;
            }
            if (uVar7 != 0x41b) goto LAB_7ffe9a04dc4a;
            aiStackX_10[0] = 100;
          }
          goto LAB_7ffe9a04dc45;
        }
        iVar5 = iVar5 + -1;
      }
    }
  }
  afStack_28[0] = (float)iVar5 / _DAT_7ffe9c049ce4;
  uVar4 = func_0x7ffe9996c8e0(_DAT_7ffe9c949440,afStack_28);
  uVar6 = _DAT_7ffe9c8f5150;
LAB_7ffe9a04dcd7:
  puVar2 = (undefined *)FUN_7ffe9b36a740(uVar6,uVar4,0);
  return puVar2;
}

