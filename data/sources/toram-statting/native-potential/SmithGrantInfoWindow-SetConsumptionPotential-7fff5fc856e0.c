
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrantInfoWindow_SetConsumptionPotential
               (undefined *self,int onePotential,int usedPotential,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  undefined8 uVar3;
  
  if (DAT_7fff625e425c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6243f290);
    FUN_7fff5f47d450(&DAT_7fff62422a58);
    DAT_7fff625e425c = '\x01';
  }
  *(int *)(self + 0xb0) = usedPotential;
  lVar1 = *(longlong *)(self + 0x48);
  *(int *)(self + 0xb4) = onePotential;
  uVar3 = FUN_7fff5fc6ce20((longlong)onePotential,_DAT_7fff6243f290,0);
  if (lVar1 != 0) {
    FUN_7fff5ff0eed0(lVar1,uVar3,0);
    SmithGrantInfoWindow_UpdateDetailVal(self,(undefined *)0x0);
    return;
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

