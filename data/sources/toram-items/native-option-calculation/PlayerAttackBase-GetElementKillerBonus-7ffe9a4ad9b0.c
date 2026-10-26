
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerAttackBase_GetElementKillerBonus
              (undefined *status,undefined *targetElement,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined *self;
  longlong lVar5;
  longlong lStackX_20;
  
  if (DAT_7ffe9caddebe == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948908);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    DAT_7ffe9caddebe = '\x01';
  }
  iVar4 = 0;
  lStackX_20 = 0;
  if (*(int *)(_DAT_7ffe9c948908 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  iVar3 = BonusManager_GetElementKiller
                    ((undefined *)((ulonglong)targetElement & 0xffffffff),(undefined *)0x0);
  if (iVar3 == 0) {
    if (status == (undefined *)0x0) goto LAB_7ffe9a4a97d8;
  }
  else {
    if (status == (undefined *)0x0) goto LAB_7ffe9a4a97d8;
    self = (undefined *)
           (**(code **)(*(longlong *)status + 0x1d8))
                     (status,*(undefined8 *)(*(longlong *)status + 0x1e0));
    if (self == (undefined *)0x0) goto LAB_7ffe9a4a97d8;
    iVar4 = BonusManager_GetBonusValue(self,iVar3,(undefined *)0x0);
  }
  lVar5 = (**(code **)(*(longlong *)status + 0x1c8))
                    (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
  if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x50) != 0)) {
    cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar5 + 0x50),0x44a,&lStackX_20,_DAT_7ffe9c934418);
    if (cVar2 != '\0') {
      if (lStackX_20 == 0) goto LAB_7ffe9a4a97d8;
      iVar3 = func_0x7ffe9a7a2140(lStackX_20,0x34);
      iVar4 = iVar4 + iVar3;
    }
    return iVar4;
  }
LAB_7ffe9a4a97d8:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar4 = (*pcVar1)();
  return iVar4;
}

