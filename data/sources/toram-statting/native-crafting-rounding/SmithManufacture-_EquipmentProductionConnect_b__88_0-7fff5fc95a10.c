
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithManufacture__EquipmentProductionConnect_b__88_0(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  
  if (*(longlong *)(self + 0x1d8) != 0) {
    FUN_7fff5fdca140(*(longlong *)(self + 0x1d8),0);
    plVar1 = *(longlong **)(self + 0x28);
    if (plVar1 != (longlong *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x7fff5fc95a44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x188))(plVar1,*(undefined8 *)(*plVar1 + 400));
      return;
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

