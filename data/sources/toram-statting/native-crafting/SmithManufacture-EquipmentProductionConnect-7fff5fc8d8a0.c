
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
SmithManufacture_EquipmentProductionConnect
          (undefined *self,undefined *takeController,int takeUid,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if (DAT_7fff625e429d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242b348);
    DAT_7fff625e429d = '\x01';
  }
  puVar2 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242b348);
  FUN_7fff5f4eb770(puVar2,0,0);
  if (puVar2 != (undefined *)0x0) {
    *(undefined **)(puVar2 + 0x20) = self;
    thunk_FUN_7fff5f491fd0();
    *(undefined **)(puVar2 + 0x28) = takeController;
    thunk_FUN_7fff5f491fd0();
    *(int *)(puVar2 + 0x30) = takeUid;
    return puVar2;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

