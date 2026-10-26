
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuardActionManager_ReceiveDamage
               (undefined *self,undefined *otherPlayer,undefined *responseData,undefined *reaction,
               undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  undefined8 uVar3;
  undefined *actor;
  char cVar4;
  undefined4 uVar5;
  undefined *damageData;
  
  if (DAT_7ffe9cadfebc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c945240);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    DAT_7ffe9cadfebc = '\x01';
  }
  if (((responseData != (undefined *)0x0) && (*(longlong *)(responseData + 0x68) != 0)) &&
     (cVar4 = FUN_7ffe9bc60070(*(longlong *)(responseData + 0x68),1,0), cVar4 != '\0')) {
    if ((*(longlong *)(responseData + 0x68) != 0) &&
       (uVar5 = FUN_7ffe9bc601e0(*(longlong *)(responseData + 0x68),1,0),
       otherPlayer != (undefined *)0x0)) {
      uVar3 = FUN_7ffe9ab6e260(otherPlayer,_DAT_7ffe9c945240);
      uVar3 = FUN_7ffe9a8f6690(uVar3,0);
      damageData = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c94aa68);
      FUN_7ffe9a8fff70(damageData,uVar3,0);
      if (damageData != (undefined *)0x0) {
        uVar1 = *(undefined4 *)(responseData + 0x5c);
        *(undefined4 *)(damageData + 0x10) = uVar1;
        *(undefined4 *)(damageData + 0x84) = uVar1;
        *(undefined4 *)(damageData + 0x54) = uVar5;
        *(undefined4 *)(damageData + 0x18) = 2;
        *(undefined4 *)(self + 0x88) = uVar5;
        actor = (undefined *)FUN_7ffe9bd98960(otherPlayer,0);
        GuardActionManager_OnGuard(self,actor,damageData,(undefined *)0x0);
        return;
      }
    }
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  return;
}

