
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_Respawn(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  int iVar3;
  undefined *puVar4;
  float fVar5;
  
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 != (longlong *)0x0) {
    puVar4 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
    if (puVar4 != (undefined *)0x0) {
      iVar3 = BonusManager_GetAvatarBonusValue(puVar4,0xbc,(undefined *)0x0);
      plVar1 = *(longlong **)(self + 0x10);
      fVar5 = (float)iVar3 / _DAT_7ffe9c049cfc;
      if (plVar1 != (longlong *)0x0) {
        puVar4 = (undefined *)
                 (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
        if (puVar4 != (undefined *)0x0) {
          fVar5 = (_DAT_7ffe9c049b18 - fVar5) * _DAT_7ffe9c049d18;
          iVar3 = BonusManager_GetBonusValue(puVar4,0x30,(undefined *)0x0);
          return (int)(fVar5 - (float)iVar3);
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

