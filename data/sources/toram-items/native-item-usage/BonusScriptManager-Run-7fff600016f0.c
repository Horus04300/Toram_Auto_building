
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusScriptManager_Run
               (undefined *self,undefined *bonusScript,byte updateTime,undefined *methodInfo)

{
  int *piVar1;
  code *pcVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  undefined *puVar6;
  longlong lVar7;
  
  if (DAT_7fff625e5899 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244bdf8);
    FUN_7fff5f47d450(&DAT_7fff6244beb8);
    DAT_7fff625e5899 = '\x01';
  }
  if ((bonusScript == (undefined *)0x0) || (bonusScript[0x38] != '\0')) {
    return;
  }
  *(undefined **)(self + 0x20) = bonusScript;
  thunk_FUN_7fff5f491fd0();
  bVar3 = BonusScriptManager_timeCheck(self,updateTime,(undefined *)0x0);
  if (bVar3 == 0) {
LAB_7fff60001884:
    lVar7 = *(longlong *)(self + 0x20);
    if (lVar7 != 0) {
      if ((*(char *)(lVar7 + 0x40) != '\0') && (0.0 < *(float *)(lVar7 + 0x4c))) {
        *(undefined4 *)(lVar7 + 0x3c) = *(undefined4 *)(lVar7 + 0x70);
        return;
      }
      *(undefined1 *)(lVar7 + 0x38) = 1;
      return;
    }
  }
  else {
    puVar6 = *(undefined **)(self + 0x20);
    while (puVar6 != (undefined *)0x0) {
      puVar6 = BonusScriptData_get_CurrentBonusLine(puVar6,(undefined *)0x0);
      if (puVar6 == (undefined *)0x0) goto LAB_7fff60001884;
      if (((*(undefined **)(self + 0x20) == (undefined *)0x0) ||
          (puVar6 = BonusScriptData_get_CurrentBonusLine
                              (*(undefined **)(self + 0x20),(undefined *)0x0),
          puVar6 == (undefined *)0x0)) || (*(longlong *)(self + 0x10) == 0)) break;
      cVar4 = FUN_7fff60869460(*(longlong *)(self + 0x10),*(undefined4 *)(puVar6 + 0x10),
                               _DAT_7fff6244bdf8);
      if (cVar4 == '\0') {
LAB_7fff6000182b:
        if (*(longlong *)(self + 0x20) == 0) break;
        piVar1 = (int *)(*(longlong *)(self + 0x20) + 0x3c);
        *piVar1 = *piVar1 + 1;
      }
      else {
        if ((*(longlong *)(self + 0x10) == 0) ||
           (lVar7 = FUN_7fff6087c780(*(longlong *)(self + 0x10),*(undefined4 *)(puVar6 + 0x10),
                                     _DAT_7fff6244beb8), lVar7 == 0)) break;
        iVar5 = (**(code **)(lVar7 + 0x18))
                          (*(undefined8 *)(lVar7 + 0x40),puVar6,*(undefined8 *)(lVar7 + 0x28));
        if (iVar5 == 1) {
          lVar7 = *(longlong *)(self + 0x20);
          if (lVar7 != 0) {
            *(undefined4 *)(lVar7 + 0x3c) = *(undefined4 *)(lVar7 + 0x70);
            goto LAB_7fff60001884;
          }
          break;
        }
        if (iVar5 == 0) goto LAB_7fff6000182b;
        if (iVar5 == 2) {
          if (*(longlong *)(self + 0x20) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x20) + 0x38) = 1;
            goto LAB_7fff60001884;
          }
          break;
        }
      }
      lVar7 = *(longlong *)(self + 0x20);
      if (lVar7 == 0) break;
      if (0 < *(int *)(lVar7 + 0x68)) {
        iVar5 = *(int *)(lVar7 + 0x68) + -1;
        *(int *)(lVar7 + 0x68) = iVar5;
        if (0 < *(int *)(lVar7 + 100)) {
          *(int *)(lVar7 + 100) = *(int *)(lVar7 + 100) + -1;
        }
        if (0 < iVar5) {
          *(undefined4 *)(lVar7 + 0x3c) = *(undefined4 *)(lVar7 + 0x70);
        }
      }
      puVar6 = *(undefined **)(self + 0x20);
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

