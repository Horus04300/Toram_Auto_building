
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte InitGameSystem__Start_d__28_MoveNext(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  undefined1 uVar3;
  char cVar4;
  byte bVar5;
  undefined4 uVar6;
  int iVar7;
  undefined8 uVar8;
  longlong *plVar9;
  undefined *puVar10;
  undefined *result;
  longlong lVar11;
  longlong *plVar12;
  longlong lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  longlong lVar16;
  undefined *puVar17;
  longlong *plVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  longlong lVar21;
  ulonglong in_stack_ffffffffffffffb8;
  undefined8 in_stack_ffffffffffffffc0;
  
  uVar6 = (undefined4)((ulonglong)in_stack_ffffffffffffffc0 >> 0x20);
  if (DAT_7ffe9cad9cfc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(0x7ffe9c8f80b8);
    FUN_7ffe9996d590(&DAT_7ffe9c92eda0);
    FUN_7ffe9996d590(&DAT_7ffe9c933ea8);
    FUN_7ffe9996d590(0x7ffe9c9119a0);
    FUN_7ffe9996d590(0x7ffe9c8fdf18);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c93a5d8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(0x7ffe9c910e00);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(0x7ffe9c955618);
    FUN_7ffe9996d590(0x7ffe9c9506a0);
    FUN_7ffe9996d590(&DAT_7ffe9c956e00);
    FUN_7ffe9996d590(&DAT_7ffe9c951900);
    FUN_7ffe9996d590(&DAT_7ffe9c955fa8);
    FUN_7ffe9996d590(&DAT_7ffe9c954ef0);
    FUN_7ffe9996d590(&DAT_7ffe9c953578);
    FUN_7ffe9996d590(&DAT_7ffe9c954238);
    FUN_7ffe9996d590(0x7ffe9c950208);
    FUN_7ffe9996d590(&DAT_7ffe9c9509b0);
    FUN_7ffe9996d590(&DAT_7ffe9c91ef20);
    FUN_7ffe9996d590(&DAT_7ffe9c960dc8);
    FUN_7ffe9996d590(&DAT_7ffe9c963400);
    FUN_7ffe9996d590(0x7ffe9c9650b0);
    FUN_7ffe9996d590(0x7ffe9c94e330);
    FUN_7ffe9996d590(0x7ffe9c94e3f8);
    FUN_7ffe9996d590(0x7ffe9c94e4b8);
    FUN_7ffe9996d590(0x7ffe9c94e580);
    FUN_7ffe9996d590(0x7ffe9c94e890);
    FUN_7ffe9996d590(0x7ffe9c94e950);
    FUN_7ffe9996d590(0x7ffe9c960a18);
    FUN_7ffe9996d590(0x7ffe9c94ea18);
    FUN_7ffe9996d590(0x7ffe9c94ead8);
    FUN_7ffe9996d590(0x7ffe9c960ae0);
    FUN_7ffe9996d590(0x7ffe9c94eba0);
    FUN_7ffe9996d590(0x7ffe9c960bb0);
    FUN_7ffe9996d590(0x7ffe9c94ec60);
    FUN_7ffe9996d590(0x7ffe9c94ed28);
    FUN_7ffe9996d590(0x7ffe9c960c78);
    FUN_7ffe9996d590(0x7ffe9c94ede8);
    FUN_7ffe9996d590(0x7ffe9c960d48);
    FUN_7ffe9996d590(0x7ffe9c960948);
    FUN_7ffe9996d590(&DAT_7ffe9c8feeb8);
    FUN_7ffe9996d590(0x7ffe9c917920);
    FUN_7ffe9996d590(0x7ffe9c915458);
    FUN_7ffe9996d590(0x7ffe9c90c3c0);
    FUN_7ffe9996d590(0x7ffe9c96e048);
    FUN_7ffe9996d590(0x7ffe9c9523c0);
    FUN_7ffe9996d590(0x7ffe9c932000);
    FUN_7ffe9996d590(0x7ffe9c9011d8);
    FUN_7ffe9996d590(0x7ffe9c9694a0);
    FUN_7ffe9996d590(0x7ffe9c917e00);
    FUN_7ffe9996d590(0x7ffe9c940998);
    FUN_7ffe9996d590(0x7ffe9c8f5df8);
    FUN_7ffe9996d590(0x7ffe9c90c2f0);
    FUN_7ffe9996d590(0x7ffe9c9179f0);
    FUN_7ffe9996d590(0x7ffe9c944518);
    FUN_7ffe9996d590(0x7ffe9c8f2a08);
    FUN_7ffe9996d590(0x7ffe9c919598);
    FUN_7ffe9996d590(0x7ffe9c909350);
    FUN_7ffe9996d590(0x7ffe9c937a40);
    FUN_7ffe9996d590(&DAT_7ffe9c91e418);
    FUN_7ffe9996d590(0x7ffe9c96e118);
    FUN_7ffe9996d590(0x7ffe9c95a1e0);
    FUN_7ffe9996d590(0x7ffe9c96d850);
    FUN_7ffe9996d590(0x7ffe9c9446a0);
    FUN_7ffe9996d590(0x7ffe9c95a378);
    FUN_7ffe9996d590(0x7ffe9c909280);
    FUN_7ffe9996d590(0x7ffe9c917b90);
    FUN_7ffe9996d590(0x7ffe9c917c60);
    FUN_7ffe9996d590(0x7ffe9c917d30);
    FUN_7ffe9996d590(0x7ffe9c944828);
    FUN_7ffe9996d590(0x7ffe9c919258);
    FUN_7ffe9996d590(0x7ffe9c944760);
    FUN_7ffe9996d590(0x7ffe9c96e1e8);
    FUN_7ffe9996d590(0x7ffe9c91f8b8);
    FUN_7ffe9996d590(0x7ffe9c91f980);
    FUN_7ffe9996d590(&DAT_7ffe9c9405c8);
    FUN_7ffe9996d590(0x7ffe9c953a18);
    DAT_7ffe9cad9cfc = '\x01';
  }
  lVar16 = *(longlong *)(self + 0x20);
  plVar9 = (longlong *)0x0;
  switch(*(undefined4 *)(self + 0x10)) {
  case 0:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    uVar19 = func_0x7ffe99940040(uRam00007ffe9c960a18);
    func_0x7ffe999c3920(uVar19,0);
    *(undefined8 *)(self + 0x30) = uVar19;
    il2cpp_write_barrier_0();
    cVar4 = func_0x7ffe999d1200(0);
    if (cVar4 != '\0') {
      if (lVar16 == 0) goto code_r0x7ffe99a3dee4;
      uVar19 = *(undefined8 *)(lVar16 + 0xb0);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      FUN_7ffe9abbb520(uVar19,_DAT_7ffe9c93a5d8);
    }
    lVar21 = FUN_7ffe9b141840(uRam00007ffe9c955618);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    func_0x7ffe999c3920(lVar21,1,0);
    FUN_7ffe9bd90f10(0xffffffff);
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if ((lVar21 == 0) || (func_0x7ffe99a687e0(lVar21,0,0), lVar16 == 0)) goto code_r0x7ffe99a3dee4;
    FUN_7ffe99a2f2e0(lVar16,0);
    uVar19 = FUN_7ffe99a2cbb0(0);
    uVar19 = FUN_7ffe9b3675b0(uVar19,uRam00007ffe9c932000,0);
    lVar21 = *(longlong *)(lVar16 + 0x38);
    uVar19 = FUN_7ffe9b3675b0(uRam00007ffe9c96d850,uVar19,0);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    FUN_7ffe9a404310(lVar21,uVar19,0);
    func_0x7ffe999c3920(uRam00007ffe9c9011d8,0);
    cVar4 = FUN_7ffe9a2d15a0(0);
    if (cVar4 == '\0') {
      lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
      FUN_7ffe9a8c38b0(lVar21,0);
      goto code_r0x7ffe99a3c0dd;
    }
    break;
  case 1:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
code_r0x7ffe99a3c0dd:
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(lVar21 + 0x38) != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
    break;
  case 2:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    goto code_r0x7ffe99a3c160;
  case 3:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    goto code_r0x7ffe99a3c1e2;
  case 4:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    goto code_r0x7ffe99a3c3fc;
  case 5:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
    if (*(longlong *)(self + 0x70) != 0) {
      uVar19 = FUN_7ffe99a58320(*(longlong *)(self + 0x70),uRam00007ffe9c96e1e8,0);
      if ((*(longlong *)(self + 0x70) != 0) &&
         (uVar20 = FUN_7ffe99a58320(*(longlong *)(self + 0x70),uRam00007ffe9c96e118,0), lVar16 != 0)
         ) {
        FUN_7ffe9a2c9750(lVar16,uVar19,uVar20,0);
        *(undefined8 *)(self + 0x18) = *(undefined8 *)(self + 0x78);
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 6;
        return 1;
      }
    }
    goto code_r0x7ffe99a3dee4;
  case 6:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    FUN_7ffe9bd79740(0);
    lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
    if (lVar16 == 0) goto code_r0x7ffe99a3dee4;
    FUN_7ffe99ace4c0(lVar16,0);
    goto code_r0x7ffe99a3c68b;
  case 7:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(lVar21 + 0x20) == '\0') {
      if (lVar16 != 0) {
        if (cRam00007ffe9cad9ce3 == '\0') {
          FUN_7ffe9996d590(0x7ffe9c961868);
          cRam00007ffe9cad9ce3 = '\x01';
        }
        lVar21 = func_0x7ffe99940040(uRam00007ffe9c961868);
        func_0x7ffe999c3920(lVar21,0);
        *(longlong *)(lVar21 + 0x20) = lVar16;
        *(undefined4 *)(lVar21 + 0x10) = 0;
        il2cpp_write_barrier_0();
        uVar19 = FUN_7ffe9bd9f640(lVar16,lVar21,0);
        *(undefined8 *)(self + 0x18) = uVar19;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 8;
        return 1;
      }
      goto code_r0x7ffe99a3dee4;
    }
    goto code_r0x7ffe99a3c77f;
  case 8:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
code_r0x7ffe99a3c77f:
    if (lVar16 != 0) {
      lVar21 = *(longlong *)(lVar16 + 0x30);
      if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
         (uVar19 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c9179f0,0),
         lVar21 != 0)) {
        FUN_7ffe9a404310(lVar21,uVar19,0);
        lVar21 = FUN_7ffe9b141840(uRam00007ffe9c950208);
        lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c955fa8);
        if (lVar13 != 0) {
          uVar3 = func_0x7ffe999d1200(lVar13,0);
          lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c955fa8);
          if (lVar13 != 0) {
            uVar19 = *(undefined8 *)(lVar13 + 0x88);
            lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c955fa8);
            if (lVar13 != 0) {
              if (cRam00007ffe9cad9d4c == '\0') {
                FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
                cRam00007ffe9cad9d4c = '\x01';
              }
              if (lVar21 != 0) {
                uVar19 = FUN_7ffe99a92810(lVar21,uVar3,uVar19,
                                          **(undefined8 **)(_DAT_7ffe9c9590b8 + 0xb8),0);
                uVar19 = FUN_7ffe9bd9f640(lVar16,uVar19,0);
                *(undefined8 *)(self + 0x18) = uVar19;
                il2cpp_write_barrier_0();
                *(undefined4 *)(self + 0x10) = 9;
                return 1;
              }
            }
          }
        }
      }
    }
    goto code_r0x7ffe99a3dee4;
  case 9:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    lVar21 = FUN_7ffe9b141840(uRam00007ffe9c950208);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    uVar19 = *(undefined8 *)(lVar21 + 0x30);
    lVar21 = FUN_7ffe9b141840(uRam00007ffe9c9506a0);
    uVar20 = FUN_7ffe99a91630(0);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    uVar6 = FUN_7ffe99a93590(lVar21,uVar20,0);
    lVar21 = FUN_7ffe9b141840(uRam00007ffe9c9506a0);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    FUN_7ffe99a938f0(lVar21,uVar19,uVar6,0,in_stack_ffffffffffffffb8 & 0xffffffffffffff00,0);
    lVar21 = FUN_7ffe9b141840(uRam00007ffe9c950208);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(lVar21 + 0x3b) != '\0') {
      puVar17 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
      if (puVar17 != (undefined *)0x0) {
        plVar18 = (longlong *)LocalizeManager_Get(puVar17,(undefined *)0x0,(undefined *)0x0);
        lVar16 = FUN_7ffe9b141840(uRam00007ffe9c950208);
        if (lVar16 != 0) {
          if (plVar18 != (longlong *)0x0) {
            if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar18 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8) != _DAT_7ffe9c960dc8)) {
              bVar2 = false;
            }
            else {
              bVar2 = true;
            }
            if (bVar2) {
              plVar9 = plVar18;
            }
          }
          FUN_7ffe9a2da3e0(plVar9,uRam00007ffe9c909350,uRam00007ffe9c909280,
                           *(undefined8 *)(lVar16 + 0x40),0);
          return 0;
        }
      }
      goto code_r0x7ffe99a3dee4;
    }
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(lVar21 + 0x20) != '\0') {
      if (lVar16 != 0) {
        if (cRam00007ffe9cad9ce1 == '\0') {
          FUN_7ffe9996d590(0x7ffe9c961468);
          cRam00007ffe9cad9ce1 = '\x01';
        }
        lVar21 = func_0x7ffe99940040(uRam00007ffe9c961468);
        func_0x7ffe999c3920(lVar21,0);
        *(longlong *)(lVar21 + 0x20) = lVar16;
        *(undefined4 *)(lVar21 + 0x10) = 0;
        il2cpp_write_barrier_0();
        uVar19 = FUN_7ffe9bd9f640(lVar16,lVar21,0);
        *(undefined8 *)(self + 0x18) = uVar19;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 10;
        return 1;
      }
      goto code_r0x7ffe99a3dee4;
    }
    goto code_r0x7ffe99a3ca74;
  case 10:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
code_r0x7ffe99a3ca74:
    if (lVar16 != 0) {
      lVar21 = *(longlong *)(lVar16 + 0x30);
      if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
         (uVar19 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c917c60,0),
         lVar21 != 0)) {
        FUN_7ffe9a404310(lVar21,uVar19,0);
        plVar9 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8);
        puVar17 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c955fa8);
        if ((puVar17 != (undefined *)0x0) &&
           (puVar17 = SystemManager_GetDownloadURL(puVar17,(undefined *)0x0),
           plVar9 != (longlong *)0x0)) {
          if ((puVar17 != (undefined *)0x0) &&
             (lVar21 = func_0x7ffe9996c920(puVar17,*(undefined8 *)(*plVar9 + 0x40)), lVar21 == 0)) {
            uVar19 = func_0x7ffe9996d1f0();
            FUN_7ffe9996d760(uVar19,0);
            pcVar1 = (code *)swi(3);
            bVar5 = (*pcVar1)();
            return bVar5;
          }
          if ((int)plVar9[3] == 0) {
code_r0x7ffe99a3deea:
            FUN_7ffe9996d790();
            pcVar1 = (code *)swi(3);
            bVar5 = (*pcVar1)();
            return bVar5;
          }
          plVar9[4] = (longlong)puVar17;
          il2cpp_write_barrier_0();
          func_0x7ffe999c3920(uRam00007ffe9c953a18,plVar9,0);
          if (*(longlong *)(self + 0x30) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x30) + 0x10) = 0;
            if (*(int *)(_DAT_7ffe9c933ea8 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            FUN_7ffe9bd77ec0(2);
            lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c951900);
            if (lVar21 != 0) {
              func_0x7ffe99aaf480(lVar21);
              puVar17 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
              puVar10 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c955fa8);
              if (puVar10 != (undefined *)0x0) {
                puVar10 = SystemManager_GetDownloadURL(puVar10,(undefined *)0x0);
                uVar19 = *(undefined8 *)(self + 0x30);
                result = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8f3938);
                FUN_7ffe9ac2ed50(result,uVar19,uRam00007ffe9c94e890);
                if (puVar17 != (undefined *)0x0) {
                  puVar17 = ResourceManager_Initialize(puVar17,puVar10,result,(undefined *)0x0);
                  uVar19 = FUN_7ffe9bd9f640(lVar16,puVar17,0);
                  *(undefined8 *)(self + 0x18) = uVar19;
                  il2cpp_write_barrier_0();
                  *(undefined4 *)(self + 0x10) = 0xb;
                  return 1;
                }
              }
            }
          }
        }
      }
    }
    goto code_r0x7ffe99a3dee4;
  case 0xb:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x30) == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(*(longlong *)(self + 0x30) + 0x10) == '\0') {
      puVar17 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
      if (puVar17 == (undefined *)0x0) goto code_r0x7ffe99a3dee4;
      plVar18 = (longlong *)LocalizeManager_Get(puVar17,(undefined *)0x0,(undefined *)0x0);
      if (plVar18 == (longlong *)0x0) {
        FUN_7ffe9b141840(_DAT_7ffe9c956e00);
        goto code_r0x7ffe99a3dee4;
      }
      if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar18 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8
           ) != _DAT_7ffe9c960dc8)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        plVar9 = plVar18;
      }
      lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
      if (plVar9 == (longlong *)0x0) goto code_r0x7ffe99a3dee4;
      uVar19 = FUN_7ffe99a58320(plVar9,uRam00007ffe9c944828,0);
      uVar20 = FUN_7ffe99a58320(plVar9,uRam00007ffe9c944760,0);
      if (*(int *)(lRam00007ffe9c960948 + 0xe0) == 0) {
        func_0x7ffe9996d830(lRam00007ffe9c960948);
      }
      lVar21 = *(longlong *)(*(longlong *)(lRam00007ffe9c960948 + 0xb8) + 8);
      if (lVar21 == 0) {
        if (*(int *)(lRam00007ffe9c960948 + 0xe0) == 0) {
          func_0x7ffe9996d830(lRam00007ffe9c960948);
        }
        uVar14 = **(undefined8 **)(lRam00007ffe9c960948 + 0xb8);
        lVar21 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
        FUN_7ffe999e6880(lVar21,uVar14,uRam00007ffe9c94e4b8,0);
        *(longlong *)(*(longlong *)(lRam00007ffe9c960948 + 0xb8) + 8) = lVar21;
        goto code_r0x7ffe99a3cf73;
      }
      goto code_r0x7ffe99a3cf7b;
    }
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c9509b0);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    lVar21 = *(longlong *)(lVar21 + 0x28);
    uVar19 = FUN_7ffe9b141840(_DAT_7ffe9c954238);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    FUN_7ffe999d2a50(lVar21,uVar19,0);
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c9509b0);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    cVar4 = FUN_7ffe9a2cb040(lVar21,0);
    if (cVar4 != '\0') {
      if (lVar16 != 0) {
        lVar21 = *(longlong *)(lVar16 + 0x30);
        if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
           (uVar19 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c917920,0),
           lVar21 != 0)) {
          FUN_7ffe9a404310(lVar21,uVar19,0);
          lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c953578);
          if (lVar21 != 0) {
            uVar19 = FUN_7ffe99a4a810(lVar21,0);
            *(undefined8 *)(self + 0x50) = uVar19;
            il2cpp_write_barrier_0();
            uVar19 = FUN_7ffe9b36a9f0(uRam00007ffe9c940998,*(undefined8 *)(self + 0x50),
                                      *(undefined8 *)(self + 0x50),0);
            *(undefined8 *)(self + 0x58) = uVar19;
            il2cpp_write_barrier_0();
            *(undefined8 *)(self + 0x60) = 0;
            il2cpp_write_barrier_0();
            *(undefined8 *)(self + 0x68) = 0;
            il2cpp_write_barrier_0();
            uVar19 = func_0x7ffe99940040(uRam00007ffe9c960bb0);
            func_0x7ffe999c3920(uVar19,0);
            *(undefined8 *)(self + 0x38) = uVar19;
            il2cpp_write_barrier_0();
            if (*(longlong *)(self + 0x38) != 0) {
              *(undefined1 *)(*(longlong *)(self + 0x38) + 0x10) = 0;
              lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
              uVar19 = *(undefined8 *)(self + 0x58);
              uVar20 = *(undefined8 *)(self + 0x38);
              uVar14 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
              FUN_7ffe9ac2ed50(uVar14,uVar20,uRam00007ffe9c94eba0,0);
              if (lVar21 != 0) {
                uVar19 = FUN_7ffe99ad0580(lVar21,uVar19,1,uVar14,0);
                uVar19 = FUN_7ffe9bd9f640(lVar16,uVar19,0);
                *(undefined8 *)(self + 0x18) = uVar19;
                il2cpp_write_barrier_0();
                *(undefined4 *)(self + 0x10) = 0xc;
                return 1;
              }
            }
          }
        }
      }
      goto code_r0x7ffe99a3dee4;
    }
    func_0x7ffe999c3920(uRam00007ffe9c915458,0);
code_r0x7ffe99a3c68b:
    lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar16 != 0) {
      FUN_7ffe9a8c8170(lVar16,0);
LAB_7ffe99a3c6aa:
      return 0;
    }
    goto code_r0x7ffe99a3dee4;
  case 0xc:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x38) == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(*(longlong *)(self + 0x38) + 0x10) != '\0') {
      lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
      uVar19 = *(undefined8 *)(self + 0x58);
      lVar13 = func_0x7ffe9996c990(_DAT_7ffe9c91ef20,2);
      uVar20 = FUN_7ffe9b3675b0(uRam00007ffe9c95a1e0,*(undefined8 *)(self + 0x50),0);
      if (lVar13 == 0) goto code_r0x7ffe99a3dee4;
      if (*(int *)(lVar13 + 0x18) == 0) goto code_r0x7ffe99a3deea;
      *(undefined8 *)(lVar13 + 0x20) = uVar20;
      il2cpp_write_barrier_0();
      uVar20 = FUN_7ffe9b3675b0(uRam00007ffe9c95a378,*(undefined8 *)(self + 0x50),0);
      if (*(uint *)(lVar13 + 0x18) < 2) goto code_r0x7ffe99a3deea;
      *(undefined8 *)(lVar13 + 0x28) = uVar20;
      il2cpp_write_barrier_0();
      lVar11 = func_0x7ffe9996c990(uRam00007ffe9c9119a0,2);
      if (lVar11 == 0) goto code_r0x7ffe99a3dee4;
      if ((*(int *)(lVar11 + 0x18) == 0) ||
         (*(undefined4 *)(lVar11 + 0x20) = 2, *(uint *)(lVar11 + 0x18) < 2))
      goto code_r0x7ffe99a3deea;
      *(undefined4 *)(lVar11 + 0x24) = 2;
      if ((lVar21 == 0) ||
         (lVar21 = FUN_7ffe99acf200(lVar21,uVar19,lVar13,lVar11,
                                    in_stack_ffffffffffffffb8 & 0xffffffffffffff00,CONCAT44(uVar6,1)
                                    ,0), lVar21 == 0)) goto code_r0x7ffe99a3dee4;
      if (*(int *)(lVar21 + 0x18) == 0) goto code_r0x7ffe99a3deea;
      plVar18 = *(longlong **)(lVar21 + 0x20);
      if (plVar18 == (longlong *)0x0) {
        *(undefined8 *)(self + 0x60) = 0;
      }
      else {
        if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7ffe9c963400 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar18 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c963400 + 0x130) * 8) != _DAT_7ffe9c963400)) {
          bVar2 = false;
        }
        else {
          bVar2 = true;
        }
        plVar12 = plVar9;
        if (bVar2) {
          plVar12 = plVar18;
        }
        *(longlong **)(self + 0x60) = plVar12;
      }
      il2cpp_write_barrier_0();
      if (*(uint *)(lVar21 + 0x18) < 2) goto code_r0x7ffe99a3deea;
      plVar18 = *(longlong **)(lVar21 + 0x28);
      if (plVar18 == (longlong *)0x0) {
        *(undefined8 *)(self + 0x68) = 0;
      }
      else {
        if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(lRam00007ffe9c9650b0 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar18 + 200) + -8 +
             (ulonglong)*(byte *)(lRam00007ffe9c9650b0 + 0x130) * 8) != lRam00007ffe9c9650b0)) {
          bVar2 = false;
        }
        else {
          bVar2 = true;
        }
        if (bVar2) {
          plVar9 = plVar18;
        }
        *(longlong **)(self + 0x68) = plVar9;
      }
      il2cpp_write_barrier_0();
      uVar19 = *(undefined8 *)(self + 0x60);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar4 = FUN_7ffe9bda1fa0(uVar19,0,0);
      if (cVar4 == '\0') {
        uVar19 = *(undefined8 *)(self + 0x68);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar4 = FUN_7ffe9bda1fa0(uVar19,0,0);
        if (cVar4 == '\0') goto code_r0x7ffe99a3d256;
      }
      if (*(longlong *)(self + 0x38) == 0) goto code_r0x7ffe99a3dee4;
      *(undefined1 *)(*(longlong *)(self + 0x38) + 0x10) = 0;
    }
code_r0x7ffe99a3d256:
    if (*(longlong *)(self + 0x38) == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(*(longlong *)(self + 0x38) + 0x10) != '\0') {
      *(undefined8 *)(self + 0x38) = 0;
      il2cpp_write_barrier_0();
      uVar19 = func_0x7ffe99940040(uRam00007ffe9c960c78);
      func_0x7ffe999c3920(uVar19,0);
      *(undefined8 *)(self + 0x40) = uVar19;
      il2cpp_write_barrier_0();
      if (*(longlong *)(self + 0x40) != 0) {
        *(undefined1 *)(*(longlong *)(self + 0x40) + 0x18) = 0;
        if (*(longlong *)(self + 0x40) != 0) {
          *(undefined1 *)(*(longlong *)(self + 0x40) + 0x10) = 0;
          if ((*(longlong *)(self + 0x40) != 0) &&
             (*(undefined4 *)(*(longlong *)(self + 0x40) + 0x14) = 0, lVar16 != 0)) {
            lVar21 = *(longlong *)(lVar16 + 0x30);
            if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
               (uVar19 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c917b90,0),
               lVar21 != 0)) {
              FUN_7ffe9a404310(lVar21,uVar19,0);
              uVar19 = *(undefined8 *)(self + 0x40);
              uVar20 = func_0x7ffe99940040(uRam00007ffe9c8f80b8);
              FUN_7ffe9ac2fb80(uVar20,uVar19,uRam00007ffe9c94ec60,0);
              if (cRam00007ffe9cad9cdf == '\0') {
                FUN_7ffe9996d590(0x7ffe9c961538);
                cRam00007ffe9cad9cdf = '\x01';
              }
              lVar21 = func_0x7ffe99940040(uRam00007ffe9c961538);
              func_0x7ffe999c3920(lVar21,0);
              *(longlong *)(lVar21 + 0x20) = lVar16;
              *(undefined4 *)(lVar21 + 0x10) = 0;
              il2cpp_write_barrier_0();
              *(undefined8 *)(lVar21 + 0x30) = uVar20;
              il2cpp_write_barrier_0();
              uVar19 = FUN_7ffe9bd9f640(lVar16,lVar21,0);
              *(undefined8 *)(self + 0x18) = uVar19;
              il2cpp_write_barrier_0();
              *(undefined4 *)(self + 0x10) = 0xd;
              return 1;
            }
          }
        }
      }
      goto code_r0x7ffe99a3dee4;
    }
    func_0x7ffe999c3920(uRam00007ffe9c919258,0);
    if ((lVar16 == 0) || (*(longlong *)(lVar16 + 0xb8) == 0)) goto code_r0x7ffe99a3dee4;
    uVar19 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c944518,0);
    if (*(longlong *)(lVar16 + 0xb8) == 0) goto code_r0x7ffe99a3dee4;
    uVar20 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c9446a0,0);
    lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
    if (*(int *)(lRam00007ffe9c960948 + 0xe0) == 0) {
      func_0x7ffe9996d830(lRam00007ffe9c960948);
    }
    lVar21 = *(longlong *)(*(longlong *)(lRam00007ffe9c960948 + 0xb8) + 0x10);
    if (lVar21 == 0) {
      if (*(int *)(lRam00007ffe9c960948 + 0xe0) == 0) {
        func_0x7ffe9996d830(lRam00007ffe9c960948);
      }
      uVar14 = **(undefined8 **)(lRam00007ffe9c960948 + 0xb8);
      lVar21 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
      FUN_7ffe999e6880(lVar21,uVar14,uRam00007ffe9c94e580,0);
      *(longlong *)(*(longlong *)(lRam00007ffe9c960948 + 0xb8) + 0x10) = lVar21;
code_r0x7ffe99a3cf73:
      il2cpp_write_barrier_0();
    }
code_r0x7ffe99a3cf7b:
    if (lVar16 != 0) {
code_r0x7ffe99a3cf84:
      FUN_7ffe9a2c9c20(lVar16,uVar19,uVar20,lVar21,0);
      return 0;
    }
    goto code_r0x7ffe99a3dee4;
  case 0xd:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x40) == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(*(longlong *)(self + 0x40) + 0x10) != '\0') {
      uVar19 = func_0x7ffe99940040(uRam00007ffe9c960d48);
      func_0x7ffe999c3920(uVar19,0);
      *(undefined8 *)(self + 0x48) = uVar19;
      il2cpp_write_barrier_0();
      uVar19 = FUN_7ffe9b3675b0(uRam00007ffe9c9523c0,*(undefined8 *)(self + 0x50),0);
      *(undefined8 *)(self + 0x80) = uVar19;
      il2cpp_write_barrier_0();
      uVar19 = FUN_7ffe9b366c90(_DAT_7ffe9c9405c8,*(undefined8 *)(self + 0x50),_DAT_7ffe9c91e418,
                                *(undefined8 *)(self + 0x80),0);
      *(undefined8 *)(self + 0x58) = uVar19;
      il2cpp_write_barrier_0();
      lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
      uVar19 = *(undefined8 *)(self + 0x58);
      uVar20 = *(undefined8 *)(self + 0x40);
      uVar14 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
      FUN_7ffe9ac2ed50(uVar14,uVar20,uRam00007ffe9c94ed28,0);
      if ((lVar21 != 0) && (uVar19 = FUN_7ffe99ad0580(lVar21,uVar19,1,uVar14,0), lVar16 != 0)) {
        uVar19 = FUN_7ffe9bd9f640(lVar16,uVar19,0);
        *(undefined8 *)(self + 0x18) = uVar19;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 0xe;
        return 1;
      }
      goto code_r0x7ffe99a3def0;
    }
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c953578);
    if (*(longlong *)(self + 0x60) == 0) goto code_r0x7ffe99a3def0;
    uVar19 = FUN_7ffe9bda7ca0(*(longlong *)(self + 0x60),0);
    if ((*(longlong *)(self + 0x40) == 0) || (lVar21 == 0)) goto code_r0x7ffe99a3def0;
    FUN_7ffe99a4b570(lVar21,uVar19,*(undefined8 *)(self + 0x68),
                     *(undefined1 *)(*(longlong *)(self + 0x40) + 0x10),0);
    goto code_r0x7ffe99a3dbe5;
  case 0xe:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
    if (lVar21 == 0) goto code_r0x7ffe99a3def0;
    plVar18 = (longlong *)
              FUN_7ffe99aceed0(lVar21,*(undefined8 *)(self + 0x58),*(undefined8 *)(self + 0x80),2,
                               in_stack_ffffffffffffffb8 & 0xffffffffffffff00,CONCAT44(uVar6,1),0);
    if (plVar18 != (longlong *)0x0) {
      if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7ffe9c963400 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar18 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c963400 + 0x130) * 8
           ) != _DAT_7ffe9c963400)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        plVar9 = plVar18;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(plVar9,0,0);
    if (cVar4 == '\0') {
      func_0x7ffe999c3920(uRam00007ffe9c919598,0);
      if ((lVar16 == 0) || (*(longlong *)(lVar16 + 0xb8) == 0)) goto code_r0x7ffe99a3def0;
      uVar19 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c944518,0);
      if (*(longlong *)(lVar16 + 0xb8) == 0) goto code_r0x7ffe99a3def0;
      uVar20 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c9446a0,0);
      lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
      if (*(int *)(lRam00007ffe9c960948 + 0xe0) == 0) {
        func_0x7ffe9996d830(lRam00007ffe9c960948);
      }
      lVar21 = *(longlong *)(*(longlong *)(lRam00007ffe9c960948 + 0xb8) + 0x18);
      if (lVar21 == 0) {
        if (*(int *)(lRam00007ffe9c960948 + 0xe0) == 0) {
          func_0x7ffe9996d830(lRam00007ffe9c960948);
        }
        uVar14 = **(undefined8 **)(lRam00007ffe9c960948 + 0xb8);
        lVar21 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
        FUN_7ffe999e6880(lVar21,uVar14,uRam00007ffe9c94e330,0);
        *(longlong *)(*(longlong *)(lRam00007ffe9c960948 + 0xb8) + 0x18) = lVar21;
code_r0x7ffe99a3d806:
        il2cpp_write_barrier_0();
      }
code_r0x7ffe99a3d80e:
      if (lVar16 == 0) goto code_r0x7ffe99a3def0;
      goto code_r0x7ffe99a3cf84;
    }
    if ((plVar9 == (longlong *)0x0) || (lVar21 = FUN_7ffe9bda7b10(plVar9,0), lVar21 == 0))
    goto code_r0x7ffe99a3def0;
    iVar7 = FUN_7ffe9b36b890(lVar21,uRam00007ffe9c8f5df8,0);
    lVar21 = FUN_7ffe9bda7b10(plVar9,0);
    if (lVar21 == 0) goto code_r0x7ffe99a3def0;
    uVar19 = FUN_7ffe9b370080(lVar21,0,iVar7,0);
    lVar21 = FUN_7ffe9bda7b10(plVar9,0);
    if (lVar21 == 0) goto code_r0x7ffe99a3def0;
    uVar20 = func_0x7ffe9b370070(lVar21,iVar7 + 1,0);
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c953578);
    if (*(longlong *)(self + 0x60) == 0) goto code_r0x7ffe99a3def0;
    uVar14 = FUN_7ffe9bda7ca0(*(longlong *)(self + 0x60),0);
    if (((*(longlong *)(self + 0x40) == 0) || (lVar21 == 0)) ||
       (FUN_7ffe99a4b570(lVar21,uVar14,*(undefined8 *)(self + 0x68),
                         *(undefined1 *)(*(longlong *)(self + 0x40) + 0x10),0), lVar16 == 0))
    goto code_r0x7ffe99a3def0;
    lVar21 = *(longlong *)(lVar16 + 0x50);
    if (*(longlong *)(lVar16 + 0xb8) == 0) goto code_r0x7ffe99a3def0;
    uVar14 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c91f980,0);
    uVar19 = FUN_7ffe9b36a740(uVar14,uVar19,0);
    if (lVar21 == 0) goto code_r0x7ffe99a3def0;
    FUN_7ffe9a404310(lVar21,uVar19,0);
    lVar21 = *(longlong *)(lVar16 + 0x58);
    if ((*(longlong *)(lVar16 + 0xb8) == 0) ||
       (uVar19 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c91f8b8,0), lVar21 == 0)
       ) goto code_r0x7ffe99a3def0;
    FUN_7ffe9a404310(lVar21,uVar19,0);
    if (*(longlong *)(lVar16 + 0x48) == 0) goto code_r0x7ffe99a3def0;
    FUN_7ffe9bd9b390(*(longlong *)(lVar16 + 0x48),1,0);
    if (*(longlong *)(lVar16 + 0x60) == 0) goto code_r0x7ffe99a3def0;
    func_0x7ffe9a3055b0(*(longlong *)(lVar16 + 0x60),uVar20,0);
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
    if (lVar21 == 0) goto code_r0x7ffe99a3def0;
    FUN_7ffe9a2c77a0(lVar21,0,0);
    goto code_r0x7ffe99a3d9d8;
  case 0xf:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar16 == 0) goto code_r0x7ffe99a3def0;
code_r0x7ffe99a3d9d8:
    if (*(char *)(lVar16 + 0x68) == '\0') {
      cVar4 = FUN_7ffe9bde77f0(0x1b);
      if (cVar4 == '\0') goto code_r0x7ffe99a3da40;
      lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
      if (lVar16 != 0) {
        if (*(char *)(lVar16 + 0x38) == '\0') {
          lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
          if (lVar16 != 0) {
            FUN_7ffe9a2c7500(lVar16,0);
            goto code_r0x7ffe99a3da40;
          }
        }
        else {
          lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
          if (lVar16 != 0) {
            FUN_7ffe9a2c6e90(lVar16,0);
code_r0x7ffe99a3da40:
            *(undefined8 *)(self + 0x18) = 0;
            il2cpp_write_barrier_0();
            *(undefined4 *)(self + 0x10) = 0xf;
            return 1;
          }
        }
      }
    }
    else {
      lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
      if (lVar21 != 0) {
        FUN_7ffe9a2c77a0(lVar21,1,0);
        if (*(longlong *)(lVar16 + 0x48) != 0) {
          FUN_7ffe9bd9b390(*(longlong *)(lVar16 + 0x48),0,0);
          if (*(longlong *)(self + 0x48) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x48) + 0x10) = 0;
            lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c9509b0);
            if ((lVar21 != 0) && (plVar9 = *(longlong **)(lVar21 + 0x28), plVar9 != (longlong *)0x0)
               ) {
              if ((*(byte *)(*plVar9 + 0x130) < *(byte *)(lRam00007ffe9c910e00 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*plVar9 + 200) + -8 +
                   (ulonglong)*(byte *)(lRam00007ffe9c910e00 + 0x130) * 8) != lRam00007ffe9c910e00))
              {
                FUN_7ffe9996c950(plVar9);
                pcVar1 = (code *)swi(3);
                bVar5 = (*pcVar1)();
                return bVar5;
              }
              FUN_7ffe9a2cddf0(plVar9,0);
              if (*(longlong *)(self + 0x40) != 0) {
                uVar6 = *(undefined4 *)(*(longlong *)(self + 0x40) + 0x14);
                uVar19 = *(undefined8 *)(self + 0x48);
                uVar20 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
                FUN_7ffe9ac2ed50(uVar20,uVar19,uRam00007ffe9c94ede8,0);
                if (cRam00007ffe9cad9ce0 == '\0') {
                  FUN_7ffe9996d590(0x7ffe9c9612d0);
                  cRam00007ffe9cad9ce0 = '\x01';
                }
                lVar21 = func_0x7ffe99940040(uRam00007ffe9c9612d0);
                func_0x7ffe999c3920(lVar21,0);
                *(longlong *)(lVar21 + 0x28) = lVar16;
                *(undefined4 *)(lVar21 + 0x10) = 0;
                il2cpp_write_barrier_0();
                *(undefined8 *)(lVar21 + 0x38) = uVar20;
                *(undefined4 *)(lVar21 + 0x20) = uVar6;
                il2cpp_write_barrier_0();
                uVar19 = FUN_7ffe9bd9f640(lVar16,lVar21,0);
                *(undefined8 *)(self + 0x18) = uVar19;
                il2cpp_write_barrier_0();
                *(undefined4 *)(self + 0x10) = 0x10;
                return 1;
              }
            }
          }
        }
      }
    }
    goto code_r0x7ffe99a3def0;
  case 0x10:
    *(undefined8 *)(self + 0x48) = 0;
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    il2cpp_write_barrier_0();
    *(undefined8 *)(self + 0x80) = 0;
    il2cpp_write_barrier_0();
code_r0x7ffe99a3dbe5:
    *(undefined8 *)(self + 0x40) = 0;
    il2cpp_write_barrier_0();
    if (lVar16 != 0) {
      lVar21 = *(longlong *)(lVar16 + 0x30);
      if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
         (uVar19 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c917d30,0),
         lVar21 != 0)) {
        FUN_7ffe9a404310(lVar21,uVar19,0);
        lVar21 = FUN_7ffe9b141840(uRam00007ffe9c955618);
        if (lVar21 != 0) {
          *(undefined1 *)(lVar21 + 0x34) = *(undefined1 *)(lVar16 + 0x68);
          if (*(longlong *)(self + 0x30) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x30) + 0x11) = 0;
            lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
            lVar13 = FUN_7ffe9b141840(uRam00007ffe9c950208);
            if (lVar13 != 0) {
              uVar19 = *(undefined8 *)(lVar13 + 0x30);
              lVar13 = FUN_7ffe9b141840(uRam00007ffe9c950208);
              if (lVar13 != 0) {
                uVar14 = FUN_7ffe99a92e20(lVar13,0);
                uVar20 = *(undefined8 *)(self + 0x30);
                uVar15 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
                FUN_7ffe9ac2ed50(uVar15,uVar20,uRam00007ffe9c94e950,0);
                if (lVar21 != 0) {
                  uVar19 = FUN_7ffe9a8d6770(lVar21,uVar19,uVar14,0,uVar15,0);
                  uVar19 = FUN_7ffe9bd9f640(lVar16,uVar19,0);
                  *(undefined8 *)(self + 0x18) = uVar19;
                  il2cpp_write_barrier_0();
                  *(undefined4 *)(self + 0x10) = 0x11;
                  return 1;
                }
              }
            }
          }
        }
      }
    }
code_r0x7ffe99a3def0:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    bVar5 = (*pcVar1)();
    return bVar5;
  case 0x11:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x30) == 0) goto code_r0x7ffe99a3def0;
    if (*(char *)(*(longlong *)(self + 0x30) + 0x11) == '\0') {
      lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
      if (lVar16 == 0) goto code_r0x7ffe99a3def0;
      if (*(char *)(lVar16 + 0x38) == '\0') {
        puVar17 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
        if (puVar17 == (undefined *)0x0) goto code_r0x7ffe99a3def0;
        plVar18 = (longlong *)LocalizeManager_Get(puVar17,(undefined *)0x0,(undefined *)0x0);
        if (plVar18 == (longlong *)0x0) {
          FUN_7ffe9b141840(_DAT_7ffe9c956e00);
          goto code_r0x7ffe99a3def0;
        }
        if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar18 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8) != _DAT_7ffe9c960dc8)) {
          bVar2 = false;
        }
        else {
          bVar2 = true;
        }
        if (bVar2) {
          plVar9 = plVar18;
        }
        lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
        if (plVar9 == (longlong *)0x0) goto code_r0x7ffe99a3def0;
        uVar19 = FUN_7ffe99a58320(plVar9,uRam00007ffe9c90c3c0,0);
        uVar20 = FUN_7ffe99a58320(plVar9,uRam00007ffe9c90c2f0,0);
        if (*(int *)(lRam00007ffe9c960948 + 0xe0) == 0) {
          func_0x7ffe9996d830(lRam00007ffe9c960948);
        }
        lVar21 = *(longlong *)(*(longlong *)(lRam00007ffe9c960948 + 0xb8) + 0x20);
        if (lVar21 == 0) {
          if (*(int *)(lRam00007ffe9c960948 + 0xe0) == 0) {
            func_0x7ffe9996d830(lRam00007ffe9c960948);
          }
          uVar14 = **(undefined8 **)(lRam00007ffe9c960948 + 0xb8);
          lVar21 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
          FUN_7ffe999e6880(lVar21,uVar14,uRam00007ffe9c94e3f8,0);
          *(longlong *)(*(longlong *)(lRam00007ffe9c960948 + 0xb8) + 0x20) = lVar21;
          goto code_r0x7ffe99a3d806;
        }
        goto code_r0x7ffe99a3d80e;
      }
    }
    func_0x7ffe999c3920(uRam00007ffe9c937a40,0);
  default:
    goto LAB_7ffe99a3c6aa;
  }
  uVar19 = uRam00007ffe9c8f2a08;
  uVar20 = func_0x7ffe9b55c130(0);
  cVar4 = FUN_7ffe9ab80180(uVar20,uVar19);
  if (cVar4 == '\0') {
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    FUN_7ffe9a8c3d40(lVar21,0);
code_r0x7ffe99a3c160:
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(lVar21 + 0x38) != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 2;
      return 1;
    }
  }
  lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c9509b0);
  if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
  cVar4 = FUN_7ffe9a2cb010(lVar21,0);
  if (cVar4 == '\0') {
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    FUN_7ffe9a8c3af0(lVar21,0);
code_r0x7ffe99a3c1e2:
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(lVar21 + 0x38) != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 3;
      return 1;
    }
  }
  lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
  if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
  cVar4 = FUN_7ffe99ace430(lVar21,0);
  if (cVar4 != '\0') {
    uVar19 = func_0x7ffe99940040(uRam00007ffe9c960ae0);
    func_0x7ffe999c3920(uVar19,0);
    *(undefined8 *)(self + 0x28) = uVar19;
    il2cpp_write_barrier_0();
    if (*(longlong *)(self + 0x28) == 0) goto code_r0x7ffe99a3dee4;
    *(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 0;
    puVar17 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
    if (puVar17 == (undefined *)0x0) goto code_r0x7ffe99a3dee4;
    plVar18 = (longlong *)LocalizeManager_Get(puVar17,(undefined *)0x0,(undefined *)0x0);
    if (plVar18 == (longlong *)0x0) {
      *(undefined8 *)(self + 0x70) = 0;
    }
    else {
      if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar18 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8
           ) != _DAT_7ffe9c960dc8)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        plVar9 = plVar18;
      }
      *(longlong **)(self + 0x70) = plVar9;
    }
    il2cpp_write_barrier_0();
    lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
    lVar21 = *(longlong *)(self + 0x70);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    uVar19 = FUN_7ffe99a58320(lVar21,uRam00007ffe9c96e1e8,0);
    lVar21 = *(longlong *)(self + 0x70);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    uVar14 = FUN_7ffe99a58320(lVar21,uRam00007ffe9c96e048,0);
    uVar20 = *(undefined8 *)(self + 0x28);
    uVar15 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
    FUN_7ffe999e6880(uVar15,uVar20,uRam00007ffe9c94ea18,0);
    uVar20 = *(undefined8 *)(self + 0x28);
    uVar8 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
    FUN_7ffe999e6880(uVar8,uVar20,uRam00007ffe9c94ead8,0);
    if (lVar13 == 0) goto code_r0x7ffe99a3dee4;
    FUN_7ffe9a2c9b50(lVar13,uVar19,uVar14,uVar15,uVar8,0);
code_r0x7ffe99a3c3fc:
    if (*(longlong *)(self + 0x28) == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\0') {
      lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
      if (lVar16 != 0) {
        if ((*(char *)(lVar16 + 0x38) == '\0') || (cVar4 = FUN_7ffe9bde77f0(0x1b), cVar4 == '\0')) {
code_r0x7ffe99a3c468:
          *(undefined8 *)(self + 0x18) = 0;
          il2cpp_write_barrier_0();
          *(undefined4 *)(self + 0x10) = 4;
          return 1;
        }
        lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
        if (lVar16 != 0) {
          FUN_7ffe9a2c6e90(lVar16,0);
          if (*(longlong *)(self + 0x28) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 2;
            goto code_r0x7ffe99a3c468;
          }
        }
      }
      goto code_r0x7ffe99a3dee4;
    }
    lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
    if (lVar21 == 0) goto code_r0x7ffe99a3dee4;
    FUN_7ffe99ace4c0(lVar21,0);
    if (*(longlong *)(self + 0x28) == 0) goto code_r0x7ffe99a3dee4;
    if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\x01') {
      uVar19 = func_0x7ffe99940040(_DAT_7ffe9c8feeb8);
      FUN_7ffe9bdae370(uVar19,_DAT_7ffe9c049cc0,0);
      *(undefined8 *)(self + 0x78) = uVar19;
      il2cpp_write_barrier_0();
      *(undefined8 *)(self + 0x18) = *(undefined8 *)(self + 0x78);
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 5;
      return 1;
    }
    *(undefined8 *)(self + 0x28) = 0;
    il2cpp_write_barrier_0();
    *(undefined8 *)(self + 0x70) = 0;
    il2cpp_write_barrier_0();
  }
  lVar21 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
  if (((lVar21 != 0) && (FUN_7ffe9a2c77a0(lVar21,1,0), lVar16 != 0)) &&
     (*(longlong *)(lVar16 + 0xb8) != 0)) {
    func_0x7ffe99a58690(*(longlong *)(lVar16 + 0xb8),0);
    lVar21 = *(longlong *)(lVar16 + 0x30);
    if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
       (uVar19 = FUN_7ffe99a58320(*(longlong *)(lVar16 + 0xb8),uRam00007ffe9c917e00,0), lVar21 != 0)
       ) {
      FUN_7ffe9a404310(lVar21,uVar19,0);
      uVar19 = FUN_7ffe99a2ecb0(lVar16,0);
      uVar19 = FUN_7ffe9bd9f640(lVar16,uVar19,0);
      *(undefined8 *)(self + 0x18) = uVar19;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 7;
      return 1;
    }
  }
code_r0x7ffe99a3dee4:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar5 = (*pcVar1)();
  return bVar5;
}

