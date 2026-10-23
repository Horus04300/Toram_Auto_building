
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
MobActionPattern_CreateActionPattern(int version,undefined *reader,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  byte bVar3;
  undefined1 uVar4;
  short sVar5;
  ushort uVar6;
  undefined2 uVar7;
  undefined4 uVar8;
  undefined *puVar9;
  undefined8 uVar10;
  
  if (DAT_7fff625e4ce0 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62479e80);
    DAT_7fff625e4ce0 = '\x01';
  }
  puVar9 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62479e80);
  if (DAT_7fff625e4ce1 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6241fab8);
    DAT_7fff625e4ce1 = '\x01';
  }
  uVar10 = func_0x7fff5f47c850(_DAT_7fff6241fab8,0x14);
  *(undefined8 *)(puVar9 + 0x60) = uVar10;
  thunk_FUN_7fff5f491fd0();
  _loadFieldData_d__125_System_IDisposable_Dispose(puVar9,(undefined *)0x0);
  if (reader != (undefined *)0x0) {
    lVar1 = *(longlong *)reader;
    if (version < -2) {
      uVar6 = (**(code **)(lVar1 + 0x208))(reader,*(undefined8 *)(lVar1 + 0x210));
    }
    else {
      bVar3 = (**(code **)(lVar1 + 0x1d8))(reader,*(undefined8 *)(lVar1 + 0x1e0));
      uVar6 = (ushort)bVar3;
    }
    *(ushort *)(puVar9 + 0x10) = uVar6;
    uVar8 = (**(code **)(*(longlong *)reader + 0x228))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x230));
    *(undefined4 *)(puVar9 + 0x14) = uVar8;
    uVar4 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar9[0x18] = uVar4;
    uVar4 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar9[0x19] = uVar4;
    bVar3 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    *(float *)(puVar9 + 0x1c) = (float)bVar3 / _DAT_7fff61b52ce4;
    bVar3 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    *(uint *)(puVar9 + 0x20) = (uint)bVar3;
    uVar4 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar9[0x24] = uVar4;
    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(int *)(puVar9 + 0x28) = (int)sVar5;
    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(int *)(puVar9 + 0x2c) = (int)sVar5;
    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(int *)(puVar9 + 0x30) = (int)sVar5;
    bVar3 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    *(uint *)(puVar9 + 0x34) = (uint)bVar3;
    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(int *)(puVar9 + 0x38) = (int)sVar5;
    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(int *)(puVar9 + 0x3c) = (int)sVar5;
    uVar4 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar9[0x40] = uVar4;
    bVar3 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    *(float *)(puVar9 + 0x44) = (float)bVar3 / _DAT_7fff61b52e64;
    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(int *)(puVar9 + 0x48) = (int)sVar5;
    bVar3 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    *(float *)(puVar9 + 0x4c) = (float)bVar3 / _DAT_7fff61b52e64;
    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(int *)(puVar9 + 0x50) = (int)sVar5;
    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    *(int *)(puVar9 + 0x54) = (int)sVar5;
    uVar4 = (**(code **)(*(longlong *)reader + 0x1d8))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x1e0));
    puVar9[0x58] = uVar4;
    lVar1 = *(longlong *)reader;
    if (version < -2) {
      uVar6 = (**(code **)(lVar1 + 0x208))(reader,*(undefined8 *)(lVar1 + 0x210));
    }
    else {
      bVar3 = (**(code **)(lVar1 + 0x1d8))(reader,*(undefined8 *)(lVar1 + 0x1e0));
      uVar6 = (ushort)bVar3;
    }
    *(ushort *)(puVar9 + 0x5a) = uVar6;
    lVar1 = *(longlong *)(puVar9 + 0x60);
    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    if (lVar1 != 0) {
      if (*(int *)(lVar1 + 0x18) != 0) {
        *(int *)(lVar1 + 0x20) = (int)sVar5;
        lVar1 = *(longlong *)(puVar9 + 0x60);
        sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                          (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
        if (lVar1 == 0) goto LAB_7fff5fe32b9a;
        if (1 < *(uint *)(lVar1 + 0x18)) {
          *(int *)(lVar1 + 0x24) = (int)sVar5;
          lVar1 = *(longlong *)(puVar9 + 0x60);
          sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                            (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
          if (lVar1 == 0) goto LAB_7fff5fe32b9a;
          if (2 < *(uint *)(lVar1 + 0x18)) {
            *(int *)(lVar1 + 0x28) = (int)sVar5;
            lVar1 = *(longlong *)(puVar9 + 0x60);
            sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                              (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
            if (lVar1 == 0) goto LAB_7fff5fe32b9a;
            if (3 < *(uint *)(lVar1 + 0x18)) {
              *(int *)(lVar1 + 0x2c) = (int)sVar5;
              lVar1 = *(longlong *)(puVar9 + 0x60);
              sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
              if (lVar1 == 0) goto LAB_7fff5fe32b9a;
              if (4 < *(uint *)(lVar1 + 0x18)) {
                *(int *)(lVar1 + 0x30) = (int)sVar5;
                lVar1 = *(longlong *)(puVar9 + 0x60);
                sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                  (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
                if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                if (5 < *(uint *)(lVar1 + 0x18)) {
                  *(int *)(lVar1 + 0x34) = (int)sVar5;
                  lVar1 = *(longlong *)(puVar9 + 0x60);
                  sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                    (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
                  if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                  if (6 < *(uint *)(lVar1 + 0x18)) {
                    *(int *)(lVar1 + 0x38) = (int)sVar5;
                    lVar1 = *(longlong *)(puVar9 + 0x60);
                    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
                    if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                    if (7 < *(uint *)(lVar1 + 0x18)) {
                      *(int *)(lVar1 + 0x3c) = (int)sVar5;
                      lVar1 = *(longlong *)(puVar9 + 0x60);
                      sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                        (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
                      if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                      if (8 < *(uint *)(lVar1 + 0x18)) {
                        *(int *)(lVar1 + 0x40) = (int)sVar5;
                        lVar1 = *(longlong *)(puVar9 + 0x60);
                        sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                          (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
                        if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                        if (9 < *(uint *)(lVar1 + 0x18)) {
                          *(int *)(lVar1 + 0x44) = (int)sVar5;
                          sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                            (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
                          *(int *)(puVar9 + 0x68) = (int)sVar5;
                          if (version < -3) {
                            uVar7 = (**(code **)(*(longlong *)reader + 0x208))
                                              (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
                            *(undefined2 *)(puVar9 + 0x6c) = uVar7;
                          }
                          if (-5 < version) {
                            return puVar9;
                          }
                          lVar1 = *(longlong *)(puVar9 + 0x60);
                          sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                            (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
                          if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                          if (10 < *(uint *)(lVar1 + 0x18)) {
                            *(int *)(lVar1 + 0x48) = (int)sVar5;
                            lVar1 = *(longlong *)(puVar9 + 0x60);
                            sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                              (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
                            if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                            if (0xb < *(uint *)(lVar1 + 0x18)) {
                              *(int *)(lVar1 + 0x4c) = (int)sVar5;
                              lVar1 = *(longlong *)(puVar9 + 0x60);
                              sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                                (reader,*(undefined8 *)(*(longlong *)reader + 0x210)
                                                );
                              if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                              if (0xc < *(uint *)(lVar1 + 0x18)) {
                                *(int *)(lVar1 + 0x50) = (int)sVar5;
                                lVar1 = *(longlong *)(puVar9 + 0x60);
                                sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                                  (reader,*(undefined8 *)
                                                           (*(longlong *)reader + 0x210));
                                if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                                if (0xd < *(uint *)(lVar1 + 0x18)) {
                                  *(int *)(lVar1 + 0x54) = (int)sVar5;
                                  lVar1 = *(longlong *)(puVar9 + 0x60);
                                  sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                                    (reader,*(undefined8 *)
                                                             (*(longlong *)reader + 0x210));
                                  if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                                  if (0xe < *(uint *)(lVar1 + 0x18)) {
                                    *(int *)(lVar1 + 0x58) = (int)sVar5;
                                    lVar1 = *(longlong *)(puVar9 + 0x60);
                                    sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                                      (reader,*(undefined8 *)
                                                               (*(longlong *)reader + 0x210));
                                    if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                                    if (0xf < *(uint *)(lVar1 + 0x18)) {
                                      *(int *)(lVar1 + 0x5c) = (int)sVar5;
                                      lVar1 = *(longlong *)(puVar9 + 0x60);
                                      sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                                        (reader,*(undefined8 *)
                                                                 (*(longlong *)reader + 0x210));
                                      if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                                      if (0x10 < *(uint *)(lVar1 + 0x18)) {
                                        *(int *)(lVar1 + 0x60) = (int)sVar5;
                                        lVar1 = *(longlong *)(puVar9 + 0x60);
                                        sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                                          (reader,*(undefined8 *)
                                                                   (*(longlong *)reader + 0x210));
                                        if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                                        if (0x11 < *(uint *)(lVar1 + 0x18)) {
                                          *(int *)(lVar1 + 100) = (int)sVar5;
                                          lVar1 = *(longlong *)(puVar9 + 0x60);
                                          sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                                            (reader,*(undefined8 *)
                                                                     (*(longlong *)reader + 0x210));
                                          if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                                          if (0x12 < *(uint *)(lVar1 + 0x18)) {
                                            *(int *)(lVar1 + 0x68) = (int)sVar5;
                                            lVar1 = *(longlong *)(puVar9 + 0x60);
                                            sVar5 = (**(code **)(*(longlong *)reader + 0x208))
                                                              (reader,*(undefined8 *)
                                                                       (*(longlong *)reader + 0x210)
                                                              );
                                            if (lVar1 == 0) goto LAB_7fff5fe32b9a;
                                            if (0x13 < *(uint *)(lVar1 + 0x18)) {
                                              *(int *)(lVar1 + 0x6c) = (int)sVar5;
                                              return puVar9;
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      FUN_7fff5f47d650();
      pcVar2 = (code *)swi(3);
      puVar9 = (undefined *)(*pcVar2)();
      return puVar9;
    }
  }
LAB_7fff5fe32b9a:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  puVar9 = (undefined *)(*pcVar2)();
  return puVar9;
}

