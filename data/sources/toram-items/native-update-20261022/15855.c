
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
  longlong lVar6;
  longlong lVar7;
  
  if (DAT_7ffe9cade141 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c944ea0);
    FUN_7ffe9996d590(&DAT_7ffe9c944f68);
    DAT_7ffe9cade141 = '\x01';
  }
  if ((bonusScript == (undefined *)0x0) || (bonusScript[0x38] != '\0')) {
    return;
  }
  *(undefined **)(self + 0x20) = bonusScript;
  il2cpp_write_barrier_0();
  bVar3 = BonusScriptManager_timeCheck(self,updateTime,(undefined *)0x0);
  if (bVar3 == 0) {
LAB_7ffe9a4f6cc4:
    lVar6 = *(longlong *)(self + 0x20);
    if (lVar6 != 0) {
      if ((*(char *)(lVar6 + 0x40) != '\0') && (0.0 < *(float *)(lVar6 + 0x4c))) {
        *(undefined4 *)(lVar6 + 0x3c) = *(undefined4 *)(lVar6 + 0x70);
        return;
      }
      *(undefined1 *)(lVar6 + 0x38) = 1;
      return;
    }
  }
  else {
    lVar6 = *(longlong *)(self + 0x20);
    while (lVar6 != 0) {
      lVar6 = FUN_7ffe9a4f66f0(lVar6,0);
      if (lVar6 == 0) goto LAB_7ffe9a4f6cc4;
      if (((*(longlong *)(self + 0x20) == 0) ||
          (lVar6 = FUN_7ffe9a4f66f0(*(longlong *)(self + 0x20),0), lVar6 == 0)) ||
         (*(longlong *)(self + 0x10) == 0)) break;
      cVar4 = FUN_7ffe9ad5f0a0(*(longlong *)(self + 0x10),*(undefined4 *)(lVar6 + 0x10),
                               _DAT_7ffe9c944ea0);
      if (cVar4 == '\0') {
LAB_7ffe9a4f6c6b:
        if (*(longlong *)(self + 0x20) == 0) break;
        piVar1 = (int *)(*(longlong *)(self + 0x20) + 0x3c);
        *piVar1 = *piVar1 + 1;
      }
      else {
        if ((*(longlong *)(self + 0x10) == 0) ||
           (lVar7 = FUN_7ffe9ad723c0(*(longlong *)(self + 0x10),*(undefined4 *)(lVar6 + 0x10),
                                     _DAT_7ffe9c944f68), lVar7 == 0)) break;
        iVar5 = (**(code **)(lVar7 + 0x18))
                          (*(undefined8 *)(lVar7 + 0x40),lVar6,*(undefined8 *)(lVar7 + 0x28));
        if (iVar5 == 1) {
          lVar6 = *(longlong *)(self + 0x20);
          if (lVar6 != 0) {
            *(undefined4 *)(lVar6 + 0x3c) = *(undefined4 *)(lVar6 + 0x70);
            goto LAB_7ffe9a4f6cc4;
          }
          break;
        }
        if (iVar5 == 0) goto LAB_7ffe9a4f6c6b;
        if (iVar5 == 2) {
          if (*(longlong *)(self + 0x20) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x20) + 0x38) = 1;
            goto LAB_7ffe9a4f6cc4;
          }
          break;
        }
      }
      lVar6 = *(longlong *)(self + 0x20);
      if (lVar6 == 0) break;
      if (0 < *(int *)(lVar6 + 0x68)) {
        iVar5 = *(int *)(lVar6 + 0x68) + -1;
        *(int *)(lVar6 + 0x68) = iVar5;
        if (0 < *(int *)(lVar6 + 100)) {
          *(int *)(lVar6 + 100) = *(int *)(lVar6 + 100) + -1;
        }
        if (0 < iVar5) {
          *(undefined4 *)(lVar6 + 0x3c) = *(undefined4 *)(lVar6 + 0x70);
        }
      }
      lVar6 = *(longlong *)(self + 0x20);
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

