
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnActionEventSkillCancel
               (undefined *self,undefined *game,undefined *actionEvent,undefined *methodInfo)

{
  code *pcVar1;
  undefined8 uVar2;
  char cVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uStackX_10;
  longlong lStackX_20;
  
  if (DAT_7ffe9cae0a47 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9636c0);
    DAT_7ffe9cae0a47 = '\x01';
  }
  lVar5 = FUN_7ffe9b15c270(_DAT_7ffe9c9636c0);
  if (lVar5 == 0) {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (DAT_7ffe9cadd9ee == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c955480,actionEvent,0);
    DAT_7ffe9cadd9ee = '\x01';
  }
  lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar4 != 0) {
    cVar3 = FUN_7ffe9a6039f0(lVar4,actionEvent,0);
    if (cVar3 == '\0') {
      lStackX_20 = 0;
      if (actionEvent == (undefined *)0x0) goto LAB_7ffe9a3d0b9d;
      uStackX_10 = 0;
      func_0x7ffe9bb9e840(&uStackX_10,actionEvent[0x20],*(undefined4 *)(actionEvent + 0x24),0);
      uVar2 = uStackX_10;
      if (DAT_7ffe9cadd9e9 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c9430c8);
        DAT_7ffe9cadd9e9 = '\x01';
      }
      if (*(longlong *)(lVar5 + 0x30) == 0) {
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      cVar3 = FUN_7ffe9ace5030(*(longlong *)(lVar5 + 0x30),uVar2,&lStackX_20,_DAT_7ffe9c9430c8);
      if (cVar3 != '\0') {
        if (lStackX_20 == 0) goto LAB_7ffe9a3d0b9d;
        func_0x7ffe9a3c5690(lStackX_20,actionEvent,0);
      }
    }
    return;
  }
LAB_7ffe9a3d0b9d:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

