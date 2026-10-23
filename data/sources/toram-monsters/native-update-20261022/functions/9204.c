
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
MobStatusMaster_CreateStatusMaster(int fieldId,int version,undefined *reader,undefined *methodInfo)

{
  code *pcVar1;
  undefined1 uVar2;
  byte bVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  undefined8 uVar9;
  undefined *puVar10;
  int iVar11;
  int iVar12;
  
  if (DAT_7ffe9cadd6eb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fedf0);
    FUN_7ffe9996d590(&DAT_7ffe9c8fe1c0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f98a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1178);
    DAT_7ffe9cadd6eb = '\x01';
  }
  puVar8 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8f1178);
  if (DAT_7ffe9cadd6ec == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fed20);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9700);
    FUN_7ffe9996d590(&DAT_7ffe9c8fe0f0);
    FUN_7ffe9996d590(&DAT_7ffe9c912b38);
    FUN_7ffe9996d590(&DAT_7ffe9c912998);
    FUN_7ffe9996d590(&DAT_7ffe9c911d68);
    FUN_7ffe9996d590(&DAT_7ffe9c8efdf8);
    DAT_7ffe9cadd6ec = '\x01';
  }
  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c912998);
  FUN_7ffe9ad214a0(uVar9,_DAT_7ffe9c8fe0f0);
  *(undefined8 *)(puVar8 + 0x80) = uVar9;
  il2cpp_write_barrier_0();
  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c912998);
  FUN_7ffe9ad214a0(uVar9,_DAT_7ffe9c8fe0f0);
  *(undefined8 *)(puVar8 + 0x88) = uVar9;
  il2cpp_write_barrier_0();
  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c911d68);
  FUN_7ffe9ad214a0(uVar9,_DAT_7ffe9c8f9700);
  *(undefined8 *)(puVar8 + 0x90) = uVar9;
  il2cpp_write_barrier_0();
  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c912b38);
  FUN_7ffe9ad214a0(uVar9,_DAT_7ffe9c8fed20);
  *(undefined8 *)(puVar8 + 0x98) = uVar9;
  il2cpp_write_barrier_0();
  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8efdf8);
  FUN_7ffe9a37ad10(uVar9,0);
  *(undefined8 *)(puVar8 + 0xa0) = uVar9;
  il2cpp_write_barrier_0();
  func_0x7ffe999c3920(puVar8,0);
  *(int *)(puVar8 + 0xb0) = fieldId;
  if (reader == (undefined *)0x0) {
LAB_7ffe9a360205:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    puVar8 = (undefined *)(*pcVar1)();
    return puVar8;
  }
  uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  *(undefined4 *)(puVar8 + 0x10) = uVar5;
  uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  *(undefined4 *)(puVar8 + 0x14) = uVar5;
  uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
  puVar8[0x18] = uVar2;
  uVar9 = (**(code **)(*(longlong *)reader + 0x298))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x2a0));
  *(undefined8 *)(puVar8 + 0x20) = uVar9;
  il2cpp_write_barrier_0();
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x28) = (int)sVar4;
  uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  *(undefined4 *)(puVar8 + 0x2c) = uVar5;
  uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  *(undefined4 *)(puVar8 + 0x30) = uVar5;
  uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
  puVar8[0x34] = uVar2;
  uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
  puVar8[0x35] = uVar2;
  uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
  puVar8[0x36] = uVar2;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x38) = (int)sVar4;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x3c) = (int)sVar4;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x40) = (int)sVar4;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x44) = (int)sVar4;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x48) = (int)sVar4;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x4c) = (int)sVar4;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x50) = (int)sVar4;
  uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  *(undefined4 *)(puVar8 + 0x58) = uVar5;
  bVar3 = (**(code **)(*(longlong *)reader + 0x1d8))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
  *(uint *)(puVar8 + 0x54) = (uint)bVar3;
  uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  *(undefined4 *)(puVar8 + 0x5c) = uVar5;
  uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
  puVar8[0x60] = uVar2;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 100) = (int)sVar4;
  uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  *(undefined4 *)(puVar8 + 0x68) = uVar5;
  uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  *(undefined4 *)(puVar8 + 0x6c) = uVar5;
  uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  *(undefined4 *)(puVar8 + 0x70) = uVar5;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x74) = (int)sVar4;
  uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
  puVar8[0x78] = uVar2;
  sVar4 = (**(code **)(*(longlong *)reader + 0x208))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
  *(int *)(puVar8 + 0x7c) = (int)sVar4;
  iVar6 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  iVar11 = 0;
  iVar12 = iVar11;
  if (0 < iVar6) {
    do {
      puVar10 = MobActionPattern_CreateActionPattern(version,reader,(undefined *)0x0);
      if (version < -2) {
        if (puVar10 == (undefined *)0x0) goto LAB_7ffe9a360205;
        sVar4 = *(short *)(puVar10 + 0x10);
        iVar7 = (int)sVar4;
        if (iVar7 < 100) goto LAB_7ffe9a360071;
        if (sVar4 < 10000) {
LAB_7ffe9a3601e3:
          if (*(longlong *)(puVar8 + 0x88) == 0) goto LAB_7ffe9a360205;
          FUN_7ffe9ad4d2a0(*(longlong *)(puVar8 + 0x88),iVar7,puVar10,_DAT_7ffe9c8fe1c0);
        }
        else {
          if (sVar4 < 20000) goto LAB_7ffe9a360071;
          if (sVar4 < 0x7fff) goto LAB_7ffe9a3601e3;
        }
      }
      else {
        if (puVar10 == (undefined *)0x0) goto LAB_7ffe9a360205;
        iVar7 = (int)*(short *)(puVar10 + 0x10);
        if (99 < iVar7) goto LAB_7ffe9a3601e3;
LAB_7ffe9a360071:
        if (*(longlong *)(puVar8 + 0x80) == 0) goto LAB_7ffe9a360205;
        FUN_7ffe9ad4d2a0(*(longlong *)(puVar8 + 0x80),iVar7,puVar10,_DAT_7ffe9c8fe1c0);
        *(int *)(puVar8 + 0xb4) = *(int *)(puVar8 + 0xb4) + *(int *)(puVar10 + 0x68);
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 < iVar6);
  }
  iVar6 = (**(code **)(*(longlong *)reader + 0x228))
                    (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
  iVar12 = iVar11;
  if (0 < iVar6) {
    do {
      uVar2 = (**(code **)(*(longlong *)reader + 0x1d8))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
      uVar5 = (**(code **)(*(longlong *)reader + 0x228))
                        (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
      if (*(longlong *)(puVar8 + 0x90) == 0) goto LAB_7ffe9a360205;
      FUN_7ffe9ad24d10(*(longlong *)(puVar8 + 0x90),uVar2,uVar5,_DAT_7ffe9c8f98a0);
      iVar12 = iVar12 + 1;
    } while (iVar12 < iVar6);
  }
  iVar12 = (**(code **)(*(longlong *)reader + 0x228))(reader);
  if (0 < iVar12) {
    do {
      puVar10 = MobModeData_CreateModeData(reader,(undefined *)0x0);
      if ((puVar10 == (undefined *)0x0) || (*(longlong *)(puVar8 + 0x98) == 0))
      goto LAB_7ffe9a360205;
      FUN_7ffe9ad4d2a0(*(longlong *)(puVar8 + 0x98),puVar10[0x10],puVar10,_DAT_7ffe9c8fedf0);
      iVar11 = iVar11 + 1;
    } while (iVar11 < iVar12);
  }
  return puVar8;
}

