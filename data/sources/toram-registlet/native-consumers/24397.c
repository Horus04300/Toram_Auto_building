
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
BindStrikeAction_PossibilityAbnormalState
          (undefined *thisObject,undefined *status,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  undefined *puVar3;
  
  if (DAT_7ffe9cadee03 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90fed8);
    DAT_7ffe9cadee03 = '\x01';
  }
  if (status != (undefined *)0x0) {
    puVar3 = (undefined *)
             (**(code **)(*(longlong *)status + 0x218))
                       (status,*(undefined8 *)(*(longlong *)status + 0x220));
    if (puVar3 != (undefined *)0x0) {
      bVar2 = GemCartBufferManager_ContainsBuffer(puVar3,0x3fd,(undefined *)0x0);
      if (bVar2 == 0) {
        puVar3 = (undefined *)func_0x7ffe9996c990(_DAT_7ffe9c90fed8,1);
        if (puVar3 == (undefined *)0x0) goto LAB_7ffe9a69fe2f;
        if (*(int *)(puVar3 + 0x18) != 0) {
          *(undefined4 *)(puVar3 + 0x20) = 0xc;
          return puVar3;
        }
      }
      else {
        puVar3 = (undefined *)func_0x7ffe9996c990(_DAT_7ffe9c90fed8,1);
        if (puVar3 == (undefined *)0x0) goto LAB_7ffe9a69fe2f;
        if (*(int *)(puVar3 + 0x18) != 0) {
          *(undefined4 *)(puVar3 + 0x20) = 3;
          return puVar3;
        }
      }
      FUN_7ffe9996d790();
      pcVar1 = (code *)swi(3);
      puVar3 = (undefined *)(*pcVar1)();
      return puVar3;
    }
  }
LAB_7ffe9a69fe2f:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar1)();
  return puVar3;
}

