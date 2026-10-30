
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * RegistletTextManager_GetDatas(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 *puVar6;
  undefined8 uStack_78;
  undefined8 uStack_70;
  ulonglong uStack_68;
  longlong *plStack_60;
  undefined8 uStack_58;
  ulonglong uStack_48;
  longlong *plStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  ulonglong uStack_28;
  longlong *plStack_20;
  undefined8 uStack_18;
  
  if (DAT_7ffe9cad9de3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906be0);
    FUN_7ffe9996d590(&DAT_7ffe9c903b20);
    FUN_7ffe9996d590(&DAT_7ffe9c906b10);
    FUN_7ffe9996d590(&DAT_7ffe9c914058);
    FUN_7ffe9996d590(&DAT_7ffe9c9389b0);
    FUN_7ffe9996d590(&DAT_7ffe9c938a78);
    FUN_7ffe9996d590(0x7ffe9c938b38);
    FUN_7ffe9996d590(0x7ffe9c96b1b0);
    FUN_7ffe9996d590(0x7ffe9c96b278);
    DAT_7ffe9cad9de3 = '\x01';
  }
  puVar3 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c914058);
  FUN_7ffe9ad214a0(puVar3,_DAT_7ffe9c906b10);
  if (*(longlong *)(self + 0x18) == 0) {
    FUN_7ffe9996d7a0();
LAB_7ffe99a52a70:
    FUN_7ffe9996d7a0();
  }
  else {
    FUN_7ffe9accf860(&uStack_38,*(longlong *)(self + 0x18),_DAT_7ffe9c903b20);
    uStack_78 = uStack_38;
    uStack_70 = uStack_30;
    uStack_68 = uStack_28;
    plStack_60 = plStack_20;
    uStack_58 = uStack_18;
    uVar5 = 0;
    puVar6 = &uStack_78;
    while( true ) {
      cVar2 = FUN_7ffe9ae3f410(&uStack_78,_DAT_7ffe9c938a78);
      if (cVar2 == '\0') {
        func_0x7ffe999c3920(&uStack_78,_DAT_7ffe9c9389b0);
        return puVar3;
      }
      uStack_48 = uStack_68;
      plStack_40 = plStack_60;
      if (plStack_60 == (longlong *)0x0) break;
      uVar4 = (**(code **)(*plStack_60 + 0x188))(plStack_60,*(undefined8 *)(*plStack_60 + 400));
      if (puVar3 == (undefined *)0x0) goto LAB_7ffe99a52a70;
      FUN_7ffe9ad4d2a0(puVar3,uStack_48 & 0xffffffff,uVar4,_DAT_7ffe9c906be0,uVar5,puVar6);
    }
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar1)();
  return puVar3;
}

