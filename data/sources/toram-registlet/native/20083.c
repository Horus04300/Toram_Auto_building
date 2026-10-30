
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * GemCartMasterData_CreateGemCartData(undefined *reader,int version,undefined *methodInfo)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 in_register_00000014;
  
  if (DAT_7ffe9cade7c1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90df70,CONCAT44(in_register_00000014,version));
    DAT_7ffe9cade7c1 = '\x01';
  }
  puVar4 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c90df70);
  func_0x7ffe999c3920(puVar4,0);
  if (reader != (undefined *)0x0) {
    uVar2 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    if (puVar4 != (undefined *)0x0) {
      *(undefined2 *)(puVar4 + 0x10) = uVar2;
      uVar2 = (**(code **)(*(longlong *)reader + 0x208))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
      *(undefined2 *)(puVar4 + 0x18) = uVar2;
      uVar3 = (**(code **)(*(longlong *)reader + 0x228))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
      *(undefined4 *)(puVar4 + 0x14) = uVar3;
      return puVar4;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar4 = (undefined *)(*pcVar1)();
  return puVar4;
}

