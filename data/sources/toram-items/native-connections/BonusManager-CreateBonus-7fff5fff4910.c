
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
BonusManager_CreateBonus(undefined *self,undefined *bonusLines,byte exec,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if (DAT_7fff625e5859 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244ff38);
    DAT_7fff625e5859 = '\x01';
  }
  puVar2 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6244ff38);
  BonusData__ctor(puVar2,bonusLines,(undefined *)0x0);
  if (exec == 0) {
    if (puVar2 == (undefined *)0x0) goto LAB_7fff5fff49da;
    if (puVar2[0x40] != '\0') {
      if (puVar2[0x41] == '\0') goto LAB_7fff5fff49a4;
      goto LAB_7fff5fff497d;
    }
  }
  else {
LAB_7fff5fff497d:
    if (puVar2 == (undefined *)0x0) goto LAB_7fff5fff49da;
  }
  if (*(undefined **)(self + 0x18) != (undefined *)0x0) {
    BonusScriptManager_Run
              (*(undefined **)(self + 0x18),*(undefined **)(puVar2 + 0x10),0,(undefined *)0x0);
    BonusData_UpdateBonusList(puVar2,(undefined *)0x0);
LAB_7fff5fff49a4:
    if ((puVar2[0x40] == '\0') && (puVar2[0x41] == '\0')) {
      *(undefined8 *)(puVar2 + 0x10) = 0;
      thunk_FUN_7fff5f491fd0();
    }
    return puVar2;
  }
LAB_7fff5fff49da:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

