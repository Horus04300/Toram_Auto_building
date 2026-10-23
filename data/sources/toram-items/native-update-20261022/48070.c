
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte DownloadManager__DownloadCacheAssetBundle_d__34_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  undefined *puVar3;
  char cVar4;
  undefined1 uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  longlong *plVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined *apuStackX_8 [2];
  undefined1 uStackX_18;
  undefined4 auStackX_20 [2];
  undefined8 in_stack_ffffffffffffff68;
  undefined4 uVar15;
  undefined8 uStack_88;
  undefined8 auStack_80 [2];
  undefined8 uStack_70;
  undefined **appuStack_68 [2];
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffff68 >> 0x20);
  apuStackX_8[0] = self;
  if (DAT_7ffe9cada014 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f6518);
    FUN_7ffe9996d590(&DAT_7ffe9c96d390);
    FUN_7ffe9996d590(&DAT_7ffe9c96bd50);
    FUN_7ffe9996d590(&DAT_7ffe9c96be20);
    FUN_7ffe9996d590(&DAT_7ffe9c96bee8);
    FUN_7ffe9996d590(&DAT_7ffe9c96bfb8);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c9294a0);
    FUN_7ffe9996d590(&DAT_7ffe9c9348a8);
    FUN_7ffe9996d590(&DAT_7ffe9c8fe9d8);
    FUN_7ffe9996d590(&DAT_7ffe9c8feeb8);
    FUN_7ffe9996d590(&DAT_7ffe9c92e258);
    FUN_7ffe9996d590(&DAT_7ffe9c92e0d8);
    FUN_7ffe9996d590(&DAT_7ffe9c92e318);
    FUN_7ffe9996d590(&DAT_7ffe9c939eb8);
    DAT_7ffe9cada014 = '\x01';
  }
  uStackX_18 = 0;
  uStack_88 = 0;
  auStack_80[0] = 0;
  uStack_70 = 0;
  appuStack_68[0] = apuStackX_8;
  iVar7 = *(int *)(apuStackX_8[0] + 0x10);
  lVar1 = *(longlong *)(apuStackX_8[0] + 0x20);
  if (iVar7 == 0) {
    *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xffffffff;
    *(undefined4 *)(apuStackX_8[0] + 0x48) = 0;
LAB_7ffe99ab7b64:
    if (lVar1 == 0) goto LAB_7ffe99ab7fbd;
    if (*(int *)(lVar1 + 0x30) <= *(int *)(lVar1 + 0x2c)) {
      auStackX_20[0] = 0;
      uVar13 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,auStackX_20);
      *(undefined8 *)(apuStackX_8[0] + 0x18) = uVar13;
      il2cpp_write_barrier_0();
      *(undefined4 *)(apuStackX_8[0] + 0x10) = 1;
      return 1;
    }
    if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
      func_0x7ffe9a0f23e0(*(longlong *)(apuStackX_8[0] + 0x28),_DAT_7ffe9c96bfb8);
      *(int *)(lVar1 + 0x2c) = *(int *)(lVar1 + 0x2c) + 1;
      apuStackX_8[0][0x4c] = 0;
      goto LAB_7ffe99ab7bfe;
    }
  }
  else {
    if (iVar7 == 1) {
      *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xffffffff;
      goto LAB_7ffe99ab7b64;
    }
    if (iVar7 == 2) {
      *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xffffffff;
LAB_7ffe99ab7bfe:
      cVar4 = FUN_7ffe9bd799c0(0);
      if (cVar4 == '\0') {
        *(undefined8 *)(apuStackX_8[0] + 0x18) = 0;
        il2cpp_write_barrier_0();
        *(undefined4 *)(apuStackX_8[0] + 0x10) = 2;
        return 1;
      }
      apuStackX_8[0][0x4c] = 1;
      uVar13 = *(undefined8 *)(apuStackX_8[0] + 0x30);
      uStack_58 = 0;
      uStack_50 = 0;
      func_0x7ffe9bd83b10(&uStack_58,0,0,0,CONCAT44(uVar15,*(undefined4 *)(apuStackX_8[0] + 0x38)),0
                         );
      uStack_48 = (undefined4)uStack_58;
      uStack_44 = uStack_58._4_4_;
      uStack_40 = (undefined4)uStack_50;
      uStack_3c = uStack_50._4_4_;
      uVar5 = FUN_7ffe9bd798f0(uVar13,&uStack_48,0);
      if (lVar1 != 0) {
        *(undefined1 *)(lVar1 + 0x41) = uVar5;
        if (*(char *)(lVar1 + 0x48) != '\0') {
          uVar13 = *(undefined8 *)(apuStackX_8[0] + 0x30);
          if (*(int *)(_DAT_7ffe9c96d390 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          uStack_88 = FUN_7ffe9b4fbf50(0);
          auStack_80[0] = FUN_7ffe9b4fc1e0(&uStack_88,0);
          uVar12 = FUN_7ffe9b5052a0(auStack_80,0);
          uVar13 = FUN_7ffe9b367290(uVar13,_DAT_7ffe9c939eb8,uVar12,0);
          *(undefined8 *)(apuStackX_8[0] + 0x30) = uVar13;
          il2cpp_write_barrier_0();
        }
        goto LAB_7ffe99ab7d27;
      }
    }
    else {
      if (iVar7 == 3) {
        *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xfffffffd;
        if (lVar1 == 0) {
LAB_7ffe99ab7f40:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f45:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f4a:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f4f:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f54:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f59:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f5e:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f63:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f68:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f6d:
          uVar13 = func_0x7ffe9996d1f0();
          FUN_7ffe9996d760(uVar13,0);
LAB_7ffe99ab7f7c:
          FUN_7ffe9996d790();
LAB_7ffe99ab7f81:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f86:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f8b:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f90:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f95:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7f9a:
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99ab7f9f;
        }
        if (*(char *)(lVar1 + 0x40) == '\0') {
          if (*(longlong *)(apuStackX_8[0] + 0x40) == 0) goto LAB_7ffe99ab7f95;
          cVar4 = func_0x7ffe9b36bcd0(*(undefined8 *)(*(longlong *)(apuStackX_8[0] + 0x40) + 0x10),0
                                     );
          if (cVar4 == '\0') {
            if (*(longlong *)(apuStackX_8[0] + 0x40) != 0) {
              if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
                func_0x7ffe999c30b0(*(longlong *)(apuStackX_8[0] + 0x28),
                                    *(undefined8 *)(*(longlong *)(apuStackX_8[0] + 0x40) + 0x10),
                                    _DAT_7ffe9c96be20);
                iVar7 = *(int *)(lVar1 + 0x3c) + 1;
                *(int *)(lVar1 + 0x3c) = iVar7;
                if (*(int *)(lVar1 + 0x38) <= iVar7) {
                  iVar7 = *(int *)(lVar1 + 0x34);
                  if (iVar7 < *(int *)(lVar1 + 0x30)) {
                    iVar8 = *(int *)(lVar1 + 0x30) / 2;
                    if (iVar7 <= iVar8) {
                      iVar7 = iVar8;
                    }
                    *(int *)(lVar1 + 0x30) = iVar7;
                    *(undefined4 *)(lVar1 + 0x3c) = 0;
                  }
                }
                iVar7 = *(int *)(apuStackX_8[0] + 0x48);
                *(int *)(apuStackX_8[0] + 0x48) = iVar7 + 1;
                if (iVar7 + 1 < *(int *)(lVar1 + 0x24)) goto LAB_7ffe99ab78ef;
                plVar9 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
                if (*(longlong *)(apuStackX_8[0] + 0x40) != 0) {
                  lVar10 = *(longlong *)(*(longlong *)(apuStackX_8[0] + 0x40) + 0x10);
                  if (plVar9 != (longlong *)0x0) {
                    if ((lVar10 != 0) &&
                       (lVar11 = func_0x7ffe9996c920(lVar10,*(undefined8 *)(*plVar9 + 0x40)),
                       lVar11 == 0)) goto LAB_7ffe99ab7f6d;
                    if ((int)plVar9[3] != 0) {
                      plVar9[4] = lVar10;
                      il2cpp_write_barrier_0();
                      uVar13 = _DAT_7ffe9c92e258;
LAB_7ffe99ab78de:
                      func_0x7ffe999c3920(uVar13,plVar9,0);
                      goto LAB_7ffe99ab78eb;
                    }
                    goto LAB_7ffe99ab7f7c;
                  }
                  goto LAB_7ffe99ab7f81;
                }
                goto LAB_7ffe99ab7f86;
              }
              goto LAB_7ffe99ab7f8b;
            }
            goto LAB_7ffe99ab7f90;
          }
          if (*(longlong *)(apuStackX_8[0] + 0x50) == 0) goto LAB_7ffe99ab7f68;
          uVar13 = FUN_7ffe9c00b790(*(longlong *)(apuStackX_8[0] + 0x50),0);
          cVar4 = func_0x7ffe9b36bcd0(uVar13,0);
          if (cVar4 != '\0') {
            lVar10 = *(longlong *)(apuStackX_8[0] + 0x28);
            if (*(longlong *)(apuStackX_8[0] + 0x50) != 0) {
              uVar13 = FUN_7ffe9c00b560(*(longlong *)(apuStackX_8[0] + 0x50),0);
              if (lVar10 != 0) {
                func_0x7ffe999c30e0(lVar10,uVar13,_DAT_7ffe9c96bee8);
                if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
                  func_0x7ffe999c30b0(*(longlong *)(apuStackX_8[0] + 0x28),0,_DAT_7ffe9c96be20);
                  if (0 < *(int *)(lVar1 + 0x3c)) {
                    *(int *)(lVar1 + 0x3c) = *(int *)(lVar1 + 0x3c) + -1;
                  }
                  goto LAB_7ffe99ab78eb;
                }
                goto LAB_7ffe99ab7f59;
              }
              goto LAB_7ffe99ab7f5e;
            }
            goto LAB_7ffe99ab7f63;
          }
          iVar7 = *(int *)(lVar1 + 0x3c) + 1;
          *(int *)(lVar1 + 0x3c) = iVar7;
          if (*(int *)(lVar1 + 0x38) <= iVar7) {
            iVar7 = *(int *)(lVar1 + 0x34);
            if (iVar7 < *(int *)(lVar1 + 0x30)) {
              iVar8 = *(int *)(lVar1 + 0x30) / 2;
              if (iVar7 <= iVar8) {
                iVar7 = iVar8;
              }
              *(int *)(lVar1 + 0x30) = iVar7;
              *(undefined4 *)(lVar1 + 0x3c) = 0;
            }
          }
          lVar10 = *(longlong *)(apuStackX_8[0] + 0x28);
          if (*(longlong *)(apuStackX_8[0] + 0x50) == 0) goto LAB_7ffe99ab7f54;
          uVar13 = FUN_7ffe9c00b790(*(longlong *)(apuStackX_8[0] + 0x50),0);
          if (lVar10 == 0) goto LAB_7ffe99ab7f4f;
          func_0x7ffe999c30b0(lVar10,uVar13,_DAT_7ffe9c96be20);
          iVar7 = *(int *)(apuStackX_8[0] + 0x48);
          *(int *)(apuStackX_8[0] + 0x48) = iVar7 + 1;
          if (*(int *)(lVar1 + 0x24) <= iVar7 + 1) {
            plVar9 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
            if (*(longlong *)(apuStackX_8[0] + 0x50) != 0) {
              lVar10 = FUN_7ffe9c00b790(*(longlong *)(apuStackX_8[0] + 0x50),0);
              if (plVar9 != (longlong *)0x0) {
                if ((lVar10 == 0) ||
                   (lVar11 = func_0x7ffe9996c920(lVar10,*(undefined8 *)(*plVar9 + 0x40)),
                   lVar11 != 0)) {
                  if ((int)plVar9[3] != 0) {
                    plVar9[4] = lVar10;
                    il2cpp_write_barrier_0();
                    uVar13 = _DAT_7ffe9c92e318;
                    goto LAB_7ffe99ab78de;
                  }
                }
                else {
                  uVar13 = func_0x7ffe9996d1f0();
                  FUN_7ffe9996d760(uVar13,0);
                }
                FUN_7ffe9996d790();
                goto LAB_7ffe99ab7f40;
              }
              goto LAB_7ffe99ab7f45;
            }
            goto LAB_7ffe99ab7f4a;
          }
        }
        else {
LAB_7ffe99ab78eb:
          apuStackX_8[0][0x4d] = 1;
        }
LAB_7ffe99ab78ef:
        *(undefined8 *)(apuStackX_8[0] + 0x40) = 0;
        il2cpp_write_barrier_0();
        puVar3 = apuStackX_8[0];
        if (DAT_7ffe9cada015 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c939b40);
          DAT_7ffe9cada015 = '\x01';
        }
        *(undefined4 *)(puVar3 + 0x10) = 0xffffffff;
        if (*(longlong *)(puVar3 + 0x50) != 0) {
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
        }
        *(undefined8 *)(apuStackX_8[0] + 0x50) = 0;
        il2cpp_write_barrier_0();
        if (apuStackX_8[0][0x4d] == '\0') {
          uVar15 = *(undefined4 *)(lVar1 + 0x28);
          uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8feeb8);
          FUN_7ffe9bdae370(uVar13,uVar15,0);
          *(undefined8 *)(apuStackX_8[0] + 0x18) = uVar13;
          il2cpp_write_barrier_0();
          *(undefined4 *)(apuStackX_8[0] + 0x10) = 4;
          return 1;
        }
LAB_7ffe99ab7ea5:
        if (*(char *)(lVar1 + 0x40) == '\0') {
LAB_7ffe99ab7ecb:
          *(undefined1 *)(lVar1 + 0x41) = 0;
          *(int *)(lVar1 + 0x2c) = *(int *)(lVar1 + 0x2c) + -1;
          if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
            func_0x7ffe9a537960(*(longlong *)(apuStackX_8[0] + 0x28),_DAT_7ffe9c96bd50);
            return 0;
          }
          goto LAB_7ffe99ab7fa4;
        }
        if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
          func_0x7ffe999c30b0(*(longlong *)(apuStackX_8[0] + 0x28),_DAT_7ffe9c92e0d8,
                              _DAT_7ffe9c96be20);
          goto LAB_7ffe99ab7ecb;
        }
LAB_7ffe99ab7fa9:
        FUN_7ffe9996d7a0();
      }
      else {
        if (iVar7 != 4) {
          return 0;
        }
        *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xffffffff;
LAB_7ffe99ab7d27:
        puVar3 = apuStackX_8[0];
        if (lVar1 != 0) {
          if (*(int *)(lVar1 + 0x24) <= *(int *)(apuStackX_8[0] + 0x48)) goto LAB_7ffe99ab7ea5;
          apuStackX_8[0][0x4d] = 0;
          if (apuStackX_8[0][0x4c] == '\0') {
            uVar13 = *(undefined8 *)(apuStackX_8[0] + 0x30);
            uVar12 = func_0x7ffe99940040(_DAT_7ffe9c8fe9d8);
            FUN_7ffe9c00b3c0(uVar12,uVar13,0);
          }
          else {
            uVar12 = FUN_7ffe9c00b0a0(*(undefined8 *)(apuStackX_8[0] + 0x30),
                                      *(undefined4 *)(apuStackX_8[0] + 0x38),0);
          }
          if (puVar3 != (undefined *)0x0) {
            *(undefined8 *)(puVar3 + 0x50) = uVar12;
            il2cpp_write_barrier_0();
            *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xfffffffd;
            uVar13 = func_0x7ffe99940040(_DAT_7ffe9c9348a8);
            func_0x7ffe999c3920(uVar13,0);
            *(undefined8 *)(apuStackX_8[0] + 0x40) = uVar13;
            il2cpp_write_barrier_0();
            if (*(longlong *)(apuStackX_8[0] + 0x40) != 0) {
              *(undefined8 *)(*(longlong *)(apuStackX_8[0] + 0x40) + 0x10) = 0;
              il2cpp_write_barrier_0();
              uVar13 = *(undefined8 *)(apuStackX_8[0] + 0x50);
              uVar15 = *(undefined4 *)(lVar1 + 0x20);
              uVar12 = *(undefined8 *)(apuStackX_8[0] + 0x40);
              uVar14 = func_0x7ffe99940040(_DAT_7ffe9c8f6518);
              FUN_7ffe9a2f3fb0(uVar14,uVar12,_DAT_7ffe9c9294a0,0);
              uVar13 = FUN_7ffe99aaf500(lVar1,uVar13,uVar15,uVar14,0);
              uVar13 = FUN_7ffe9bd9f640(lVar1,uVar13,0);
              *(undefined8 *)(apuStackX_8[0] + 0x18) = uVar13;
              il2cpp_write_barrier_0();
              *(undefined4 *)(apuStackX_8[0] + 0x10) = 3;
              return 1;
            }
            goto LAB_7ffe99ab7f9a;
          }
LAB_7ffe99ab7f9f:
          FUN_7ffe9996d7a0();
LAB_7ffe99ab7fa4:
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99ab7fa9;
        }
      }
      FUN_7ffe9996d7a0();
    }
    FUN_7ffe9996d7a0();
  }
  FUN_7ffe9996d7a0();
LAB_7ffe99ab7fbd:
  FUN_7ffe9996d7a0();
  func_0x7ffe99aac480(appuStack_68);
  FUN_7ffe998fa550(lVar1);
  pcVar2 = (code *)swi(3);
  bVar6 = (*pcVar2)();
  return bVar6;
}

