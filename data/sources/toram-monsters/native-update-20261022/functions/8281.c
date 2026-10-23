
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int WaveMobBattleStatus_get_Def(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  
  if (*(longlong *)(self + 0x10) != 0) {
    iVar4 = *(int *)(*(longlong *)(self + 0x10) + 0x3c);
    if (*(longlong *)(self + 0x20) != 0) {
      iVar3 = FUN_7ffe9a2ac490(*(longlong *)(self + 0x20),2);
      iVar4 = (int)(((float)iVar3 / _DAT_7ffe9c049cfc + _DAT_7ffe9c049b18) * (float)iVar4);
      if (*(longlong *)(self + 0x18) != 0) {
        cVar2 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),10);
        if (cVar2 != '\0') {
          iVar4 = (int)((float)iVar4 * _DAT_7ffe9c049b4c);
        }
        if (*(longlong *)(self + 0x18) != 0) {
          cVar2 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),0x16);
          if (cVar2 != '\0') {
            iVar4 = (int)((float)iVar4 * _DAT_7ffe9c049b4c);
          }
          return iVar4;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar4 = (*pcVar1)();
  return iVar4;
}

