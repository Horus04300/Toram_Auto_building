
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte AssetBundleManager__LoadCacheAssetBundle_d__61_MoveNext(undefined *self,undefined *methodInfo)

{
  int iVar1;
  undefined4 uVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  undefined1 uVar6;
  byte bVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  longlong lVar12;
  undefined8 uVar13;
  undefined8 *puVar14;
  
  if (DAT_7ffe9cad9fe3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c91d138);
    FUN_7ffe9996d590(&DAT_7ffe9c937ad8);
    FUN_7ffe9996d590(&DAT_7ffe9c9434e0);
    FUN_7ffe9996d590(&DAT_7ffe9c943b00);
    FUN_7ffe9996d590(&DAT_7ffe9c943c88);
    FUN_7ffe9996d590(&DAT_7ffe9c96bbb8);
    FUN_7ffe9996d590(0x7ffe9c96c080);
    FUN_7ffe9996d590(&DAT_7ffe9c96c150);
    FUN_7ffe9996d590(0x7ffe9c96c218);
    FUN_7ffe9996d590(&DAT_7ffe9c927790);
    FUN_7ffe9996d590(&DAT_7ffe9c95abe0);
    FUN_7ffe9996d590(&DAT_7ffe9c95af10);
    FUN_7ffe9996d590(&DAT_7ffe9c95b240);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c951900);
    FUN_7ffe9996d590(&DAT_7ffe9c953218);
    DAT_7ffe9cad9fe3 = '\x01';
  }
  iVar1 = *(int *)(self + 0x10);
  lVar3 = *(longlong *)(self + 0x28);
  if (iVar1 == 0) {
    puVar14 = (undefined8 *)(self + 0x20);
    *(undefined8 *)(self + 0x40) = *(undefined8 *)(self + 0x20);
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    il2cpp_write_barrier_0();
    uVar13 = *puVar14;
    if (*(int *)(_DAT_7ffe9c937ad8 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c937ad8);
    }
    uVar13 = FUN_7ffe9b3675b0(uVar13,**(undefined8 **)(_DAT_7ffe9c937ad8 + 0xb8),0);
    *puVar14 = uVar13;
    il2cpp_write_barrier_0();
    if ((lVar3 == 0) || (*(longlong *)(lVar3 + 0x30) == 0)) goto LAB_7ffe99abcf41;
    cVar5 = FUN_7ffe9ada6de0(*(longlong *)(lVar3 + 0x30),*puVar14,_DAT_7ffe9c943b00);
    if (cVar5 == '\0') {
      return 0;
    }
    if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe99abcf41;
    cVar5 = FUN_7ffe9ada6de0(*(longlong *)(lVar3 + 0x40),*puVar14,_DAT_7ffe9c9434e0);
    if (cVar5 != '\0') goto LAB_7ffe99abcf02;
    if (*(longlong *)(lVar3 + 0x50) == 0) goto LAB_7ffe99abcf41;
    cVar5 = FUN_7ffe9afd70c0(*(longlong *)(lVar3 + 0x50),*puVar14,_DAT_7ffe9c95af10);
    if (cVar5 != '\0') goto LAB_7ffe99abcd9f;
  }
  else {
    if (iVar1 != 1) {
      if (iVar1 == 2) {
        *(undefined4 *)(self + 0x10) = 0xffffffff;
        if (*(longlong *)(self + 0x50) == 0) goto LAB_7ffe99abcf41;
        cVar5 = FUN_7ffe9adfad70(*(longlong *)(self + 0x50),_DAT_7ffe9c96c150);
        lVar12 = *(longlong *)(self + 0x50);
        if (cVar5 == '\0') {
          if ((lVar12 == 0) || (uVar13 = *(undefined8 *)(lVar12 + 0x10), lVar3 == 0))
          goto LAB_7ffe99abcf41;
          if (*(longlong *)(lVar3 + 0x80) != 0) {
            lVar12 = *(longlong *)(self + 0x48);
            if (lVar12 == 0) goto LAB_7ffe99abcf41;
            if (*(char *)(lVar12 + 0x14) == '\0') {
              uVar2 = *(undefined4 *)(lVar12 + 0x10);
              uVar11 = *(undefined8 *)(self + 0x40);
              uVar10 = func_0x7ffe99940040(_DAT_7ffe9c91d138);
              FUN_7ffe99aac500(uVar10,uVar13,uVar2,uVar11,0);
              *(undefined8 *)(self + 0x58) = uVar10;
              il2cpp_write_barrier_0();
              lVar12 = *(longlong *)(lVar3 + 0x80);
              if (lVar12 != 0) {
                uVar13 = (**(code **)(lVar12 + 0x18))
                                   (*(undefined8 *)(lVar12 + 0x40),*(undefined8 *)(self + 0x58),
                                    *(undefined8 *)(lVar12 + 0x28));
                uVar13 = FUN_7ffe9bd9f640(lVar3,uVar13,0);
                *(undefined8 *)(self + 0x18) = uVar13;
                il2cpp_write_barrier_0();
                *(undefined4 *)(self + 0x10) = 3;
                return 1;
              }
              goto LAB_7ffe99abcf41;
            }
            goto LAB_7ffe99abcba1;
          }
          goto LAB_7ffe99abcbaa;
        }
        if (lVar12 == 0) goto LAB_7ffe99abcf41;
        uVar13 = *(undefined8 *)(lVar12 + 0x10);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar5 = FUN_7ffe9bda2160(uVar13,0,0);
        if (cVar5 != '\0') {
          if ((*(longlong *)(self + 0x50) == 0) ||
             (lVar12 = *(longlong *)(*(longlong *)(self + 0x50) + 0x10), lVar12 == 0))
          goto LAB_7ffe99abcf41;
          FUN_7ffe9bd74670(lVar12,1,0);
          FUN_7ffe9bda6070(0);
        }
        plVar8 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,2);
        lVar12 = *(longlong *)(self + 0x20);
        if (plVar8 == (longlong *)0x0) goto LAB_7ffe99abcf41;
        if ((lVar12 != 0) &&
           (lVar9 = func_0x7ffe9996c920(lVar12,*(undefined8 *)(*plVar8 + 0x40)), lVar9 == 0)) {
          uVar13 = func_0x7ffe9996d1f0();
          FUN_7ffe9996d760(uVar13,0);
          pcVar4 = (code *)swi(3);
          bVar7 = (*pcVar4)();
          return bVar7;
        }
        if ((int)plVar8[3] == 0) {
LAB_7ffe99abcf47:
          FUN_7ffe9996d790();
          pcVar4 = (code *)swi(3);
          bVar7 = (*pcVar4)();
          return bVar7;
        }
        plVar8[4] = lVar12;
        il2cpp_write_barrier_0();
        if (*(longlong *)(self + 0x50) == 0) goto LAB_7ffe99abcf41;
        lVar12 = *(longlong *)(*(longlong *)(self + 0x50) + 0x20);
        if ((lVar12 != 0) &&
           (lVar9 = func_0x7ffe9996c920(lVar12,*(undefined8 *)(*plVar8 + 0x40)), lVar9 == 0)) {
          uVar13 = func_0x7ffe9996d1f0();
          FUN_7ffe9996d760(uVar13,0);
          pcVar4 = (code *)swi(3);
          bVar7 = (*pcVar4)();
          return bVar7;
        }
        if (*(uint *)(plVar8 + 3) < 2) goto LAB_7ffe99abcf47;
        plVar8[5] = lVar12;
        il2cpp_write_barrier_0();
        func_0x7ffe999c3920(_DAT_7ffe9c953218,plVar8,0);
        if (lVar3 == 0) goto LAB_7ffe99abcf41;
      }
      else {
        if (iVar1 != 3) {
          return 0;
        }
        *(undefined4 *)(self + 0x10) = 0xffffffff;
        if (*(longlong *)(self + 0x58) == 0) goto LAB_7ffe99abcf41;
        uVar13 = *(undefined8 *)(*(longlong *)(self + 0x58) + 0x10);
        *(undefined8 *)(self + 0x58) = 0;
        il2cpp_write_barrier_0();
LAB_7ffe99abcba1:
        if (lVar3 == 0) goto LAB_7ffe99abcf41;
LAB_7ffe99abcbaa:
        FUN_7ffe99a93c50(lVar3,*(undefined8 *)(self + 0x40),*(undefined4 *)(self + 0x38),uVar13,0);
      }
      if (*(longlong *)(lVar3 + 0x50) != 0) {
        FUN_7ffe9afdbfb0(*(longlong *)(lVar3 + 0x50),*(undefined8 *)(self + 0x20),_DAT_7ffe9c95b240)
        ;
        lVar12 = *(longlong *)(self + 0x30);
        if (lVar12 != 0) {
          if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe99abcf41;
          uVar6 = FUN_7ffe9ada6de0(*(longlong *)(lVar3 + 0x40),*(undefined8 *)(self + 0x20),
                                   _DAT_7ffe9c9434e0);
          (**(code **)(lVar12 + 0x18))
                    (*(undefined8 *)(lVar12 + 0x40),uVar6,*(undefined8 *)(lVar12 + 0x28));
        }
        return 0;
      }
      goto LAB_7ffe99abcf41;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7ffe99abcd9f:
    if ((lVar3 == 0) || (*(longlong *)(lVar3 + 0x50) == 0)) goto LAB_7ffe99abcf41;
    cVar5 = FUN_7ffe9afd70c0(*(longlong *)(lVar3 + 0x50),*(undefined8 *)(self + 0x20),
                             _DAT_7ffe9c95af10);
    if (cVar5 != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
    if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe99abcf41;
    cVar5 = FUN_7ffe9ada6de0(*(longlong *)(lVar3 + 0x40),*(undefined8 *)(self + 0x20),
                             _DAT_7ffe9c9434e0);
    if (cVar5 != '\0') {
LAB_7ffe99abcf02:
      lVar3 = *(longlong *)(self + 0x30);
      if (lVar3 == 0) {
        return 0;
      }
      (**(code **)(lVar3 + 0x18))(*(undefined8 *)(lVar3 + 0x40),1,*(undefined8 *)(lVar3 + 0x28));
      return 0;
    }
  }
  puVar14 = (undefined8 *)(self + 0x20);
  if (*(longlong *)(lVar3 + 0x50) != 0) {
    FUN_7ffe99743100(*(longlong *)(lVar3 + 0x50),*puVar14,_DAT_7ffe9c95abe0);
    if (*(longlong *)(lVar3 + 0x30) != 0) {
      uVar13 = FUN_7ffe9adb6460(*(longlong *)(lVar3 + 0x30),*puVar14,_DAT_7ffe9c943c88);
      *(undefined8 *)(self + 0x48) = uVar13;
      il2cpp_write_barrier_0();
      uVar13 = FUN_7ffe9b3675b0(*(undefined8 *)(lVar3 + 0x58),*puVar14,0);
      uVar11 = func_0x7ffe99940040(_DAT_7ffe9c927790);
      func_0x7ffe999c30f0(uVar11,_DAT_7ffe9c96bbb8);
      *(undefined8 *)(self + 0x50) = uVar11;
      il2cpp_write_barrier_0();
      lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c951900);
      if ((*(longlong *)(self + 0x48) != 0) && (lVar12 != 0)) {
        uVar13 = FUN_7ffe99aaf190(lVar12,uVar13,*(undefined4 *)(*(longlong *)(self + 0x48) + 0x10),
                                  *(undefined8 *)(self + 0x50),0);
        uVar13 = FUN_7ffe9bd9f640(lVar3,uVar13,0);
        *(undefined8 *)(self + 0x18) = uVar13;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 2;
        return 1;
      }
    }
  }
LAB_7ffe99abcf41:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  bVar7 = (*pcVar4)();
  return bVar7;
}

