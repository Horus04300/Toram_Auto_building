
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void TreasureHuntRoomData_SettingLoginRoomData
               (undefined *self,undefined *binary,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  byte bVar5;
  undefined1 uVar6;
  undefined2 uVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  int iVar11;
  int iVar12;
  
  if (DAT_7ffe9cadea8a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95d7d8);
    FUN_7ffe9996d590(&DAT_7ffe9c964cc8);
    FUN_7ffe9996d590(&DAT_7ffe9c964800);
    FUN_7ffe9996d590(&DAT_7ffe9c964a60);
    FUN_7ffe9996d590(&DAT_7ffe9c964998);
    FUN_7ffe9996d590(&DAT_7ffe9c964bf8);
    FUN_7ffe9996d590(&DAT_7ffe9c964730);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee368);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee438);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee508);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    FUN_7ffe9996d590(&DAT_7ffe9c96c100);
    FUN_7ffe9996d590(&DAT_7ffe9c96c4f8);
    FUN_7ffe9996d590(&DAT_7ffe9c96c690);
    DAT_7ffe9cadea8a = '\x01';
  }
  if (binary == (undefined *)0x0) {
    return;
  }
  if (*(int *)(_DAT_7ffe9c95d7d8 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  uVar9 = FUN_7ffe9bc8a000(binary,0);
  uVar10 = func_0x7ffe99940040(_DAT_7ffe9c969f48);
  FUN_7ffe9b4c0ad0(uVar10,uVar9,0);
  FUN_7ffe999cd470(uVar10,0);
  bVar5 = FUN_7ffe999cd470(uVar10,0);
  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8ee368);
  FUN_7ffe9af8a010(uVar9,_DAT_7ffe9c964730);
  *(undefined8 *)(self + 0x78) = uVar9;
  il2cpp_write_barrier_0();
  iVar12 = 0;
  iVar11 = 0;
  if (bVar5 != 0) {
    do {
      lVar2 = *(longlong *)(self + 0x78);
      uVar9 = func_0x7ffe99940040(_DAT_7ffe9c96c100);
      func_0x7ffe9bba5150(uVar9,uVar10,0);
      if (lVar2 == 0) goto LAB_7ffe9a627ea7;
      *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
      lVar3 = *(longlong *)(lVar2 + 0x10);
      uVar1 = *(uint *)(lVar2 + 0x18);
      if (lVar3 == 0) goto LAB_7ffe9a627ea7;
      if (uVar1 < *(uint *)(lVar3 + 0x18)) {
        *(uint *)(lVar2 + 0x18) = uVar1 + 1;
        if (*(uint *)(lVar3 + 0x18) <= uVar1) goto LAB_7ffe9a627ead;
        *(undefined8 *)(lVar3 + (longlong)(int)uVar1 * 8 + 0x20) = uVar9;
        il2cpp_write_barrier_0();
      }
      else {
        FUN_7ffe9afd58b0(lVar2,uVar9);
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 < (int)(uint)bVar5);
  }
  FUN_7ffe999cd9b0(uVar10,0);
  FUN_7ffe999cd470(uVar10,0);
  lVar2 = *(longlong *)(self + 0x70);
  uVar6 = FUN_7ffe999cd470(uVar10,0);
  if (lVar2 != 0) {
    *(undefined1 *)(lVar2 + 0x20) = uVar6;
    lVar2 = *(longlong *)(self + 0x70);
    uVar6 = FUN_7ffe999cd470(uVar10,0);
    if (lVar2 != 0) {
      *(undefined1 *)(lVar2 + 0x21) = uVar6;
      lVar2 = *(longlong *)(self + 0x70);
      uVar6 = FUN_7ffe999cd470(uVar10,0);
      if (lVar2 != 0) {
        *(undefined1 *)(lVar2 + 0x22) = uVar6;
        lVar2 = *(longlong *)(self + 0x70);
        uVar8 = FUN_7ffe999cd9b0(uVar10,0);
        if (lVar2 != 0) {
          *(undefined4 *)(lVar2 + 0x24) = uVar8;
          lVar2 = *(longlong *)(self + 0x70);
          uVar7 = FUN_7ffe999cdc80(uVar10,0);
          if (lVar2 != 0) {
            *(undefined2 *)(lVar2 + 0x28) = uVar7;
            lVar2 = *(longlong *)(self + 0x70);
            uVar8 = FUN_7ffe999cd9b0(uVar10,0);
            if (lVar2 != 0) {
              *(undefined4 *)(lVar2 + 0x2c) = uVar8;
              lVar2 = *(longlong *)(self + 0x70);
              uVar7 = FUN_7ffe999cdc80(uVar10,0);
              if (lVar2 != 0) {
                *(undefined2 *)(lVar2 + 0x30) = uVar7;
                lVar2 = *(longlong *)(self + 0x70);
                uVar8 = FUN_7ffe999cd9b0(uVar10,0);
                if (lVar2 != 0) {
                  *(undefined4 *)(lVar2 + 0x34) = uVar8;
                  lVar2 = *(longlong *)(self + 0x70);
                  uVar7 = FUN_7ffe999cdc80(uVar10,0);
                  if (lVar2 != 0) {
                    *(undefined2 *)(lVar2 + 0x38) = uVar7;
                    lVar2 = *(longlong *)(self + 0x70);
                    uVar8 = FUN_7ffe999cd9b0(uVar10,0);
                    if (lVar2 != 0) {
                      *(undefined4 *)(lVar2 + 0x3c) = uVar8;
                      lVar2 = *(longlong *)(self + 0x70);
                      uVar7 = FUN_7ffe999cdc80(uVar10,0);
                      if (lVar2 != 0) {
                        *(undefined2 *)(lVar2 + 0x40) = uVar7;
                        lVar2 = *(longlong *)(self + 0x70);
                        uVar8 = FUN_7ffe999cd9b0(uVar10,0);
                        if (lVar2 != 0) {
                          *(undefined4 *)(lVar2 + 0x44) = uVar8;
                          lVar2 = *(longlong *)(self + 0x70);
                          uVar7 = FUN_7ffe999cdc80(uVar10,0);
                          if (lVar2 != 0) {
                            *(undefined2 *)(lVar2 + 0x48) = uVar7;
                            bVar5 = FUN_7ffe999cd470(uVar10,0);
                            uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8ee438);
                            FUN_7ffe9af8a010(uVar9,_DAT_7ffe9c964998);
                            *(undefined8 *)(self + 0x80) = uVar9;
                            il2cpp_write_barrier_0();
                            iVar11 = 0;
                            if (bVar5 != 0) {
                              do {
                                lVar2 = *(longlong *)(self + 0x80);
                                uVar9 = func_0x7ffe99940040(_DAT_7ffe9c96c4f8);
                                func_0x7ffe9bba5150(uVar9,uVar10,0);
                                if (lVar2 == 0) goto LAB_7ffe9a627ea7;
                                *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
                                lVar3 = *(longlong *)(lVar2 + 0x10);
                                uVar1 = *(uint *)(lVar2 + 0x18);
                                if (lVar3 == 0) goto LAB_7ffe9a627ea7;
                                if (uVar1 < *(uint *)(lVar3 + 0x18)) {
                                  *(uint *)(lVar2 + 0x18) = uVar1 + 1;
                                  if (*(uint *)(lVar3 + 0x18) <= uVar1) goto LAB_7ffe9a627ead;
                                  *(undefined8 *)(lVar3 + (longlong)(int)uVar1 * 8 + 0x20) = uVar9;
                                  il2cpp_write_barrier_0();
                                }
                                else {
                                  FUN_7ffe9afd58b0(lVar2,uVar9);
                                }
                                iVar11 = iVar11 + 1;
                              } while (iVar11 < (int)(uint)bVar5);
                            }
                            bVar5 = FUN_7ffe999cd470(uVar10,0);
                            uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8ee508);
                            FUN_7ffe9af8a010(uVar9,_DAT_7ffe9c964bf8);
                            *(undefined8 *)(self + 0x88) = uVar9;
                            il2cpp_write_barrier_0();
                            if (bVar5 == 0) {
                              return;
                            }
                            while( true ) {
                              lVar2 = *(longlong *)(self + 0x88);
                              uVar9 = func_0x7ffe99940040(_DAT_7ffe9c96c690);
                              func_0x7ffe9bba5150(uVar9,uVar10,0);
                              if (lVar2 == 0) break;
                              *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
                              lVar3 = *(longlong *)(lVar2 + 0x10);
                              uVar1 = *(uint *)(lVar2 + 0x18);
                              if (lVar3 == 0) break;
                              if (uVar1 < *(uint *)(lVar3 + 0x18)) {
                                *(uint *)(lVar2 + 0x18) = uVar1 + 1;
                                if (*(uint *)(lVar3 + 0x18) <= uVar1) {
LAB_7ffe9a627ead:
                                  FUN_7ffe9996d790();
                                  pcVar4 = (code *)swi(3);
                                  (*pcVar4)();
                                  return;
                                }
                                *(undefined8 *)(lVar3 + (longlong)(int)uVar1 * 8 + 0x20) = uVar9;
                                il2cpp_write_barrier_0();
                              }
                              else {
                                FUN_7ffe9afd58b0(lVar2,uVar9);
                              }
                              iVar12 = iVar12 + 1;
                              if ((int)(uint)bVar5 <= iVar12) {
                                return;
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
LAB_7ffe9a627ea7:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

