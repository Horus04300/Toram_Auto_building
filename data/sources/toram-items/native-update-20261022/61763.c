
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIItemProperty_ItemPropertysData(undefined *self,undefined *itemData,undefined *methodInfo)

{
  int widthWord;
  undefined *capVal;
  undefined *systemManager;
  code *pcVar1;
  undefined *itemPropertyTextManager;
  undefined *puVar2;
  
  if (DAT_7ffe9cadbb1e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ee100);
    DAT_7ffe9cadbb1e = '\x01';
  }
  if (itemData != (undefined *)0x0) {
    widthWord = *(int *)(self + 0x98);
    puVar2 = *(undefined **)(itemData + 0x10);
    capVal = *(undefined **)(itemData + 0x18);
    itemPropertyTextManager = (undefined *)FUN_7ffe99ec99c0(self,0);
    systemManager = *(undefined **)(self + 0x70);
    if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    puVar2 = UIItemProperty_GetItemPropertysTextData
                       (puVar2,capVal,widthWord,itemPropertyTextManager,systemManager,
                        (undefined *)0x0);
    return puVar2;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

