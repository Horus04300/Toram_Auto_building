
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
BonusManager_CreateBonus(undefined *self,undefined *bonusLines,byte exec,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if (DAT_7ffe9cade101 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9485f8);
    DAT_7ffe9cade101 = '\x01';
  }
  puVar2 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c9485f8);
  BonusData__ctor(puVar2,bonusLines,(undefined *)0x0);
  if (exec == 0) {
    if (puVar2 == (undefined *)0x0) goto LAB_7ffe9a4e9e1a;
    if (puVar2[0x40] != '\0') {
      if (puVar2[0x41] == '\0') goto LAB_7ffe9a4e9de4;
      goto LAB_7ffe9a4e9dbd;
    }
  }
  else {
LAB_7ffe9a4e9dbd:
    if (puVar2 == (undefined *)0x0) goto LAB_7ffe9a4e9e1a;
  }
  if (*(undefined **)(self + 0x18) != (undefined *)0x0) {
    BonusScriptManager_Run
              (*(undefined **)(self + 0x18),*(undefined **)(puVar2 + 0x10),0,(undefined *)0x0);
    BonusData_UpdateBonusList(puVar2,(undefined *)0x0);
LAB_7ffe9a4e9de4:
    if ((puVar2[0x40] == '\0') && (puVar2[0x41] == '\0')) {
      *(undefined8 *)(puVar2 + 0x10) = 0;
      il2cpp_write_barrier_0();
    }
    return puVar2;
  }
LAB_7ffe9a4e9e1a:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

