
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobBattleStatus_get_MagicDef(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  
  if (*(longlong *)(self + 0x10) != 0) {
    iVar5 = *(int *)(*(longlong *)(self + 0x10) + 0x40);
    if (*(longlong *)(self + 0x20) != 0) {
      iVar4 = FUN_7ffe9a2ac490(*(longlong *)(self + 0x20),3);
      fVar6 = _DAT_7ffe9c049b18;
      iVar5 = (int)(((float)iVar4 / _DAT_7ffe9c049cfc + _DAT_7ffe9c049b18) * (float)iVar5);
      if (*(longlong *)(self + 0x18) != 0) {
        cVar2 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),10);
        if (cVar2 != '\0') {
          iVar5 = (int)((float)iVar5 * _DAT_7ffe9c049b4c);
        }
        if (*(longlong *)(self + 0x18) != 0) {
          cVar2 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),0x10);
          if (cVar2 != '\0') {
            bVar3 = MobStatusMasterEx_CheckMultiFlag
                              (*(undefined **)(self + 0x10),(undefined *)0x4,(undefined *)0x0);
            if (bVar3 == 0) {
              fVar6 = _DAT_7ffe9c049cc8;
            }
            iVar5 = (int)((float)iVar5 * fVar6);
          }
          if (*(longlong *)(self + 0x18) != 0) {
            cVar2 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),0x16);
            if (cVar2 != '\0') {
              iVar5 = (int)((float)iVar5 * _DAT_7ffe9c049b4c);
            }
            return iVar5;
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

