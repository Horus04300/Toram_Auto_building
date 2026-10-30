
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIRegistletBagPanel_OnClickReinforcementButton(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  longlong lVar4;
  
  if (DAT_7ffe9cadc311 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ee2b8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c953a40);
    DAT_7ffe9cadc311 = '\x01';
  }
  if (*(longlong *)(self + 0x68) == 0) {
    return;
  }
  puVar3 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953a40);
  if ((*(longlong *)(self + 0x68) != 0) && (puVar3 != (undefined *)0x0)) {
    puVar3 = MasterRegistletManager_GetGemCartMaster
                       (puVar3,*(short *)(*(longlong *)(self + 0x68) + 0x20),(undefined *)0x0);
    if (puVar3 != (undefined *)0x0) {
      if (*(longlong *)(self + 0x68) == 0) goto LAB_7ffe9a0467bf;
      if (*(short *)(*(longlong *)(self + 0x68) + 0x22) == *(short *)(puVar3 + 0x18)) {
        return;
      }
    }
    if (*(undefined **)(self + 0x48) != (undefined *)0x0) {
      UIRegistletMainManager_ChangePanelState
                (*(undefined **)(self + 0x48),(undefined *)0x3,(undefined *)0x0);
      if ((*(undefined **)(self + 0x48) != (undefined *)0x0) &&
         (puVar3 = UIRegistletMainManager_get_ActivePanel
                             (*(undefined **)(self + 0x48),(undefined *)0x0),
         puVar3 != (undefined *)0x0)) {
        lVar4 = FUN_7ffe9ab9c3a0(puVar3,_DAT_7ffe9c8ee2b8);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar2 = FUN_7ffe9bda2160(lVar4,0,0);
        if (cVar2 != '\0') {
          if (lVar4 == 0) goto LAB_7ffe9a0467bf;
          *(undefined8 *)(lVar4 + 0xa0) = *(undefined8 *)(self + 0x68);
          il2cpp_write_barrier_0();
        }
        return;
      }
    }
  }
LAB_7ffe9a0467bf:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

