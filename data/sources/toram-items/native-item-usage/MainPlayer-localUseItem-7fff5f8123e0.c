
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MainPlayer_localUseItem(undefined *self,int uuid,undefined *methodInfo)

{
  undefined *self_00;
  longlong lVar1;
  code *pcVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined8 uVar5;
  
  if (DAT_7fff625e2674 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fd6e8);
    FUN_7fff5f47d450(&DAT_7fff62452300);
    FUN_7fff5f47d450(0x7fff6240fb80);
    FUN_7fff5f47d450(&DAT_7fff62463eb0);
    FUN_7fff5f47d450(&DAT_7fff62476ff0);
    DAT_7fff625e2674 = '\x01';
  }
  puVar3 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62476ff0);
  MainPlayer_OnSkillDelayStandbyOk(puVar3,0,methodInfo);
  if (puVar3 != (undefined *)0x0) {
    *(undefined **)(puVar3 + 0x10) = self;
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0xe0) != 0) {
      puVar4 = (undefined *)FUN_7fff6007b880(*(longlong *)(self + 0xe0),uuid,0);
      *(undefined8 *)(puVar3 + 0x18) = 0;
      thunk_FUN_7fff5f491fd0();
      if (puVar4 == (undefined *)0x0) {
LAB_7fff5f8125a1:
        return *(undefined **)(puVar3 + 0x18);
      }
      self_00 = *(undefined **)(self + 0x100);
      puVar4 = ItemData_get_BonusLines(puVar4,(undefined *)0x0);
      if (self_00 != (undefined *)0x0) {
        puVar4 = BonusManager_CreateBonus(self_00,puVar4,1,(undefined *)0x0);
        *(undefined **)(puVar3 + 0x18) = puVar4;
        thunk_FUN_7fff5f491fd0();
        puVar4 = *(undefined **)(puVar3 + 0x18);
        if ((puVar4 != (undefined *)0x0) && (*(longlong *)(puVar4 + 0x38) != 0)) {
          if (0 < *(int *)(*(longlong *)(puVar4 + 0x38) + 0x18)) {
            if (*(undefined **)(self + 0x100) == (undefined *)0x0) goto LAB_7fff5f8125bf;
            BonusManager_SetDebuff(*(undefined **)(self + 0x100),puVar4,(undefined *)0x0);
          }
          puVar4 = *(undefined **)(puVar3 + 0x18);
          if (puVar4 != (undefined *)0x0) {
            if (*(int *)(puVar4 + 0x44) != 0) {
              if (*(longlong *)(puVar4 + 0x10) == 0) goto LAB_7fff5f8125bf;
              if (*(char *)(*(longlong *)(puVar4 + 0x10) + 0x38) == '\0') {
                if (*(undefined **)(self + 0x100) != (undefined *)0x0) {
                  BonusManager_SetDurationBonus
                            (*(undefined **)(self + 0x100),puVar4,(undefined *)0x0);
                  goto LAB_7fff5f8125a1;
                }
                goto LAB_7fff5f8125bf;
              }
            }
            lVar1 = *(longlong *)(puVar4 + 0x20);
            uVar5 = func_0x7fff5f44ff00(_DAT_7fff623fd6e8);
            FUN_7fff5fdfedb0(uVar5,puVar3,_DAT_7fff62463eb0,0);
            if (lVar1 != 0) {
              FUN_7fff60a8d940(lVar1,uVar5,_DAT_7fff62452300);
              goto LAB_7fff5f8125a1;
            }
          }
        }
      }
    }
  }
LAB_7fff5f8125bf:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar2)();
  return puVar3;
}

