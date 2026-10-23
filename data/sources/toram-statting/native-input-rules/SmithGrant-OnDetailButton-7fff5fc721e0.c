
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrant_OnDetailButton(undefined *self,int detailValue,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  
  SmithGrant_SetRequireMaterial(self,(undefined *)0x0);
  SmithGrant_InitMaterialTypeSelect(self,(undefined *)0x0);
  if (*(undefined **)(self + 0xb8) != (undefined *)0x0) {
    SmithGrantInfoWindow_SetMaterialList(*(undefined **)(self + 0xb8),1,(undefined *)0x0);
    SmithGrant_InitSlotSelect(self,(undefined *)0x0);
    plVar1 = *(longlong **)(self + 0x28);
    if (plVar1 != (longlong *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x7fff5fc72239. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar1 + 0x1e8))(plVar1,2,*(undefined8 *)(*plVar1 + 0x1f0));
      return;
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

