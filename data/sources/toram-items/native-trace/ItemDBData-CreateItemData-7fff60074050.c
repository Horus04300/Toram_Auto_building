
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * ItemDBData_CreateItemData(undefined *reader,undefined *methodInfo)

{
  code *pcVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined8 uVar6;
  
  if (DAT_7fff625e5ca3 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62456480);
    DAT_7fff625e5ca3 = '\x01';
  }
  puVar5 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62456480);
  if (DAT_7fff625e5ca5 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6241f9e8);
    FUN_7fff5f47d450(&DAT_7fff6240f360);
    FUN_7fff5f47d450(&DAT_7fff6246bec0);
    DAT_7fff625e5ca5 = '\x01';
  }
  uVar6 = func_0x7fff5f47c850(_DAT_7fff6241f9e8,10);
  *(undefined8 *)(puVar5 + 0x10) = uVar6;
  thunk_FUN_7fff5f491fd0();
  uVar6 = func_0x7fff5f47c850(_DAT_7fff6241f9e8,10);
  *(undefined8 *)(puVar5 + 0x18) = uVar6;
  thunk_FUN_7fff5f491fd0();
  uVar6 = func_0x7fff5f44ff00(_DAT_7fff6246bec0);
  FUN_7fff60a943d0(uVar6,_DAT_7fff6240f360);
  *(undefined8 *)(puVar5 + 0x20) = uVar6;
  thunk_FUN_7fff5f491fd0();
  func_0x7fff5f4d3920(puVar5,0);
  if (reader != (undefined *)0x0) {
    uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
    *(undefined4 *)(puVar5 + 0x28) = uVar4;
    uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
    *(undefined4 *)(puVar5 + 0x2c) = uVar4;
    uVar3 = (**(code **)(*(longlong *)reader + 0x228))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
    *(undefined2 *)(puVar5 + 0x30) = uVar3;
    uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
    *(undefined4 *)(puVar5 + 0x34) = uVar4;
    uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar5[0x38] = uVar2;
    uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar5[0x39] = uVar2;
    uVar3 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(undefined2 *)(puVar5 + 0x3a) = uVar3;
    uVar3 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(undefined2 *)(puVar5 + 0x3c) = uVar3;
    uVar3 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(undefined2 *)(puVar5 + 0x3e) = uVar3;
    uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar5[0x40] = uVar2;
    uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar5[0x41] = uVar2;
    uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar5[0x42] = uVar2;
    uVar3 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(undefined2 *)(puVar5 + 0x4c) = uVar3;
    uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
    *(undefined4 *)(puVar5 + 0x48) = uVar4;
    uVar4 = (**(code **)(*(longlong *)reader + 0x228))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
    *(undefined4 *)(puVar5 + 0x44) = uVar4;
    return puVar5;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar5 = (undefined *)(*pcVar1)();
  return puVar5;
}

