
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidBossBattleStatus_CalcDef(undefined *self,undefined *status,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  longlong lStackX_10;
  
  if (DAT_7fff625e4c9c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6243b368);
    DAT_7fff625e4c9c = '\x01';
  }
  lStackX_10 = 0;
  if (status == (undefined *)0x0) {
    iVar3 = HighRaidBossBattleStatus_get_Def(self,(undefined *)0x0);
    return iVar3;
  }
  iVar3 = HighRaidBossBattleStatus_get_Def(self,(undefined *)0x0);
  lVar5 = (**(code **)(*(longlong *)status + 0x1c8))
                    (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
  if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x40) != 0)) {
    cVar2 = FUN_7fff60898a30(*(longlong *)(lVar5 + 0x40),0x428,&lStackX_10,_DAT_7fff6243b368);
    if (cVar2 == '\0') {
      lVar5 = (**(code **)(*(longlong *)status + 0x1c8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
      if ((lVar5 == 0) || (*(longlong *)(lVar5 + 0x50) == 0)) goto LAB_7fff5fe2d28c;
      FUN_7fff60898a30(*(longlong *)(lVar5 + 0x50),0x428,&lStackX_10,_DAT_7fff6243b368);
    }
    if (lStackX_10 != 0) {
      iVar4 = func_0x7fff602ac5d0(lStackX_10,0x52);
      if (*(longlong *)(self + 0x10) == 0) goto LAB_7fff5fe2d28c;
      iVar6 = (int)((float)*(int *)(*(longlong *)(self + 0x10) + 0x3c) * _DAT_7fff61b52b4c);
      if (iVar4 < iVar6) {
        iVar6 = iVar4;
      }
      iVar3 = iVar3 - iVar6;
    }
    return iVar3;
  }
LAB_7fff5fe2d28c:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar3 = (*pcVar1)();
  return iVar3;
}

