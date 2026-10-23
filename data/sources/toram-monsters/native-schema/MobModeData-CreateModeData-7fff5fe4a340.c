
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MobModeData_CreateModeData(undefined *reader,undefined *methodInfo)

{
  code *pcVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  
  if (DAT_7fff625e4d6d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623f5f88);
    DAT_7fff625e4d6d = '\x01';
  }
  puVar5 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623f5f88);
  _loadFieldData_d__125_System_IDisposable_Dispose(puVar5,(undefined *)0x0);
  if (reader != (undefined *)0x0) {
    uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    if (puVar5 != (undefined *)0x0) {
      puVar5[0x10] = uVar2;
      uVar3 = (**(code **)(*(longlong *)reader + 0x208))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
      *(undefined2 *)(puVar5 + 0x12) = uVar3;
      uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
      *(undefined4 *)(puVar5 + 0x14) = uVar4;
      uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
      *(undefined4 *)(puVar5 + 0x18) = uVar4;
      uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
      *(undefined4 *)(puVar5 + 0x1c) = uVar4;
      uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
      puVar5[0x20] = uVar2;
      uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
      *(undefined4 *)(puVar5 + 0x24) = uVar4;
      uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
      *(undefined4 *)(puVar5 + 0x28) = uVar4;
      uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
      puVar5[0x2c] = uVar2;
      uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
      *(undefined4 *)(puVar5 + 0x30) = uVar4;
      uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
      *(undefined4 *)(puVar5 + 0x34) = uVar4;
      uVar3 = (**(code **)(*(longlong *)reader + 0x208))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
      *(undefined2 *)(puVar5 + 0x38) = uVar3;
      return puVar5;
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar5 = (undefined *)(*pcVar1)();
  return puVar5;
}

