
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte StageLoginDownloader__initLocalizeData_d__17_MoveNext(undefined *self,undefined *methodInfo)

{
  int iVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  byte bVar5;
  longlong *plVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  undefined8 uVar10;
  longlong lVar11;
  
  if (DAT_7ffe9cad9d13 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c96b558);
    FUN_7ffe9996d590(&DAT_7ffe9c96b490);
    FUN_7ffe9996d590(&DAT_7ffe9c96ba20);
    FUN_7ffe9996d590(0x7ffe9c96baf0);
    FUN_7ffe9996d590(&DAT_7ffe9c9276c8);
    FUN_7ffe9996d590(&DAT_7ffe9c951900);
    FUN_7ffe9996d590(&DAT_7ffe9c955fa8);
    FUN_7ffe9996d590(&DAT_7ffe9c91af40);
    FUN_7ffe9996d590(&DAT_7ffe9c91b010);
    FUN_7ffe9996d590(&DAT_7ffe9c928c70);
    FUN_7ffe9996d590(&DAT_7ffe9c948a08);
    FUN_7ffe9996d590(&DAT_7ffe9c9522f8);
    FUN_7ffe9996d590(&DAT_7ffe9c938b18);
    FUN_7ffe9996d590(&DAT_7ffe9c951790);
    FUN_7ffe9996d590(&DAT_7ffe9c9275f8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f2380);
    FUN_7ffe9996d590(&DAT_7ffe9c8fddd8);
    FUN_7ffe9996d590(&DAT_7ffe9c958c18);
    FUN_7ffe9996d590(&DAT_7ffe9c90f6f0);
    FUN_7ffe9996d590(&DAT_7ffe9c934228);
    FUN_7ffe9996d590(&DAT_7ffe9c91ebe8);
    FUN_7ffe9996d590(&DAT_7ffe9c900088);
    FUN_7ffe9996d590(&DAT_7ffe9c92e4e0);
    FUN_7ffe9996d590(&DAT_7ffe9c91ef08);
    FUN_7ffe9996d590(&DAT_7ffe9c9340a0);
    FUN_7ffe9996d590(&DAT_7ffe9c90c638);
    FUN_7ffe9996d590(&DAT_7ffe9c959e68);
    FUN_7ffe9996d590(&DAT_7ffe9c9003c0);
    FUN_7ffe9996d590(&DAT_7ffe9c9405c8);
    FUN_7ffe9996d590(&DAT_7ffe9c972218);
    DAT_7ffe9cad9d13 = '\x01';
  }
  iVar1 = *(int *)(self + 0x10);
  lVar2 = *(longlong *)(self + 0x20);
  if (iVar1 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    uVar8 = func_0x7ffe99940040(_DAT_7ffe9c928c70);
    func_0x7ffe999c3920(uVar8,0);
    *(undefined8 *)(self + 0x28) = uVar8;
    il2cpp_write_barrier_0();
    func_0x7ffe999c3920(_DAT_7ffe9c900088,0);
    if ((*(longlong *)(self + 0x28) == 0) ||
       (*(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 0, lVar2 == 0)) {
LAB_7ffe99a41fb3:
      FUN_7ffe9996d7a0();
      pcVar3 = (code *)swi(3);
      bVar5 = (*pcVar3)();
      return bVar5;
    }
    lVar9 = *(longlong *)(lVar2 + 0x50);
    uVar7 = FUN_7ffe9b367290(_DAT_7ffe9c9405c8,*(undefined8 *)(lVar2 + 0x68),_DAT_7ffe9c91ef08,0);
    uVar8 = *(undefined8 *)(self + 0x28);
    uVar10 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
    FUN_7ffe9ac2ed50(uVar10,uVar8,_DAT_7ffe9c91af40,0);
    if (lVar9 == 0) goto LAB_7ffe99a41fb3;
    uVar8 = FUN_7ffe99ad04b0(lVar9,uVar7,1,_DAT_7ffe9c8fddd8,uVar10,0);
    uVar8 = FUN_7ffe9bd9f640(lVar2,uVar8,0);
    *(undefined8 *)(self + 0x18) = uVar8;
    il2cpp_write_barrier_0();
    *(undefined4 *)(self + 0x10) = 1;
LAB_7ffe99a41d8c:
    bVar5 = 1;
  }
  else {
    if (iVar1 == 1) {
      lVar9 = *(longlong *)(self + 0x28);
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (lVar9 == 0) goto LAB_7ffe99a41fb3;
      if (*(char *)(lVar9 + 0x10) != '\0') {
        *(undefined1 *)(lVar9 + 0x10) = 0;
        if (lVar2 == 0) goto LAB_7ffe99a41fb3;
        uVar8 = FUN_7ffe9b366c90(_DAT_7ffe9c9405c8,*(undefined8 *)(lVar2 + 0x68),_DAT_7ffe9c91ebe8,
                                 *(undefined8 *)(lVar2 + 0x68),0);
        *(undefined8 *)(self + 0x30) = uVar8;
        il2cpp_write_barrier_0();
        uVar8 = FUN_7ffe9b3675b0(_DAT_7ffe9c9275f8,*(undefined8 *)(lVar2 + 0x68),0);
        *(undefined8 *)(self + 0x38) = uVar8;
        il2cpp_write_barrier_0();
        lVar9 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = *(undefined8 *)(self + 0x28);
        uVar10 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
        FUN_7ffe9ac2ed50(uVar10,uVar7,_DAT_7ffe9c91b010,0);
        if (lVar9 == 0) goto LAB_7ffe99a41fb3;
        uVar8 = FUN_7ffe99ad04b0(lVar9,uVar8,1,_DAT_7ffe9c8fddd8,uVar10,0);
        uVar8 = FUN_7ffe9bd9f640(lVar2,uVar8,0);
        *(undefined8 *)(self + 0x18) = uVar8;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 2;
        goto LAB_7ffe99a41d8c;
      }
      if (lVar2 == 0) goto LAB_7ffe99a41fb3;
LAB_7ffe99a41eb7:
      *(undefined1 *)(lVar2 + 0x30) = 1;
    }
    else if (iVar1 == 2) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if ((*(longlong *)(self + 0x28) == 0) || (lVar2 == 0)) goto LAB_7ffe99a41fb3;
      if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\0') goto LAB_7ffe99a41eb7;
      if (*(char *)(lVar2 + 0x30) == '\0') {
        if (*(undefined **)(lVar2 + 0x40) == (undefined *)0x0) goto LAB_7ffe99a41fb3;
        plVar6 = (longlong *)
                 LocalizeManager_Get(*(undefined **)(lVar2 + 0x40),(undefined *)0x0,(undefined *)0x0
                                    );
        lVar9 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c90f6f0,*(undefined8 *)(self + 0x38),0);
        if ((lVar9 == 0) ||
           (uVar8 = FUN_7ffe99ace740(lVar9,uVar8,uVar7,0), plVar6 == (longlong *)0x0))
        goto LAB_7ffe99a41fb3;
        (**(code **)(*plVar6 + 0x198))(plVar6,uVar8,*(undefined8 *)(*plVar6 + 0x1a0));
        lVar9 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c958c18,*(undefined8 *)(self + 0x38),0);
        if (lVar9 == 0) goto LAB_7ffe99a41fb3;
        lVar9 = FUN_7ffe99ace740(lVar9,uVar8,uVar7,0);
        if (lVar9 != 0) {
          (**(code **)(*plVar6 + 0x198))(plVar6,lVar9,*(undefined8 *)(*plVar6 + 0x1a0));
        }
        lVar9 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c959e68,*(undefined8 *)(self + 0x38),0);
        if (lVar9 == 0) goto LAB_7ffe99a41fb3;
        lVar9 = FUN_7ffe99ace740(lVar9,uVar8,uVar7,0);
        if (lVar9 != 0) {
          (**(code **)(*plVar6 + 0x198))(plVar6,lVar9,*(undefined8 *)(*plVar6 + 0x1a0));
        }
        lVar9 = *(longlong *)(lVar2 + 0x40);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c92e4e0,*(undefined8 *)(self + 0x38),0);
        if ((lVar11 == 0) || (uVar8 = FUN_7ffe99ace740(lVar11,uVar8,uVar7,0), lVar9 == 0))
        goto LAB_7ffe99a41fb3;
        FUN_7ffe99a4afa0(lVar9,uVar8,1);
        lVar9 = *(longlong *)(lVar2 + 0x40);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c934228,*(undefined8 *)(self + 0x38),0);
        if ((lVar11 == 0) || (uVar8 = FUN_7ffe99ace740(lVar11,uVar8,uVar7,0), lVar9 == 0))
        goto LAB_7ffe99a41fb3;
        FUN_7ffe99a4afa0(lVar9,uVar8,0xe);
        lVar9 = *(longlong *)(lVar2 + 0x40);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c972218,*(undefined8 *)(self + 0x38),0);
        if ((lVar11 == 0) || (uVar8 = FUN_7ffe99ace740(lVar11,uVar8,uVar7,0), lVar9 == 0))
        goto LAB_7ffe99a41fb3;
        FUN_7ffe99a4afa0(lVar9,uVar8,2);
        lVar9 = *(longlong *)(lVar2 + 0x40);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c938b18,*(undefined8 *)(self + 0x38),0);
        if ((lVar11 == 0) || (uVar8 = FUN_7ffe99ace740(lVar11,uVar8,uVar7,0), lVar9 == 0))
        goto LAB_7ffe99a41fb3;
        FUN_7ffe99a4afa0(lVar9,uVar8,7);
        lVar9 = *(longlong *)(lVar2 + 0x40);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c9340a0,*(undefined8 *)(self + 0x38),0);
        if ((lVar11 == 0) || (uVar8 = FUN_7ffe99ace740(lVar11,uVar8,uVar7,0), lVar9 == 0))
        goto LAB_7ffe99a41fb3;
        FUN_7ffe99a4afa0(lVar9,uVar8,3);
        lVar9 = *(longlong *)(lVar2 + 0x40);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c951790,*(undefined8 *)(self + 0x38),0);
        if ((lVar11 == 0) || (uVar8 = FUN_7ffe99ace740(lVar11,uVar8,uVar7,0), lVar9 == 0))
        goto LAB_7ffe99a41fb3;
        FUN_7ffe99a4afa0(lVar9,uVar8,4);
        lVar9 = *(longlong *)(lVar2 + 0x40);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c948a08,*(undefined8 *)(self + 0x38),0);
        if ((lVar11 == 0) || (uVar8 = FUN_7ffe99ace740(lVar11,uVar8,uVar7,0), lVar9 == 0))
        goto LAB_7ffe99a41fb3;
        FUN_7ffe99a4afa0(lVar9,uVar8,8);
        if (*(longlong *)(lVar2 + 0x40) == 0) goto LAB_7ffe99a41fb3;
        lVar9 = *(longlong *)(*(longlong *)(lVar2 + 0x40) + 0x28);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c8f2380,*(undefined8 *)(self + 0x38),0);
        if (lVar11 == 0) goto LAB_7ffe99a41fb3;
        uVar7 = FUN_7ffe99ace740(lVar11,uVar8,uVar7,0);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar10 = FUN_7ffe9b3675b0(_DAT_7ffe9c9003c0,*(undefined8 *)(self + 0x38),0);
        if ((lVar11 == 0) || (uVar8 = FUN_7ffe99ace740(lVar11,uVar8,uVar10,0), lVar9 == 0))
        goto LAB_7ffe99a41fb3;
        FUN_7ffe99ac1e50(lVar9,uVar7,uVar8,0);
        lVar9 = *(longlong *)(lVar2 + 0x40);
        lVar11 = *(longlong *)(lVar2 + 0x50);
        uVar8 = *(undefined8 *)(self + 0x30);
        uVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c9522f8,*(undefined8 *)(self + 0x38),0);
        if ((lVar11 == 0) || (uVar8 = FUN_7ffe99ace740(lVar11,uVar8,uVar7,0), lVar9 == 0))
        goto LAB_7ffe99a41fb3;
        FUN_7ffe99a4afa0(lVar9,uVar8,0xb);
        uVar8 = func_0x7ffe99940040(_DAT_7ffe9c9276c8);
        func_0x7ffe999c30f0(uVar8,_DAT_7ffe9c96b490);
        *(undefined8 *)(self + 0x40) = uVar8;
        il2cpp_write_barrier_0();
        lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951900);
        lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c955fa8);
        if (lVar11 == 0) goto LAB_7ffe99a41fb3;
        uVar8 = FUN_7ffe99ad80f0(lVar11,0);
        uVar8 = FUN_7ffe9b3675b0(uVar8,_DAT_7ffe9c90c638,0);
        if (lVar9 == 0) goto LAB_7ffe99a41fb3;
        uVar8 = FUN_7ffe99aaf0f0(lVar9,uVar8,*(undefined8 *)(self + 0x40),0);
        uVar8 = FUN_7ffe9bd9f640(lVar2,uVar8,0);
        *(undefined8 *)(self + 0x18) = uVar8;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 3;
        goto LAB_7ffe99a41d8c;
      }
    }
    else if (iVar1 == 3) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (*(longlong *)(self + 0x40) != 0) {
        cVar4 = FUN_7ffe9adfad70(*(longlong *)(self + 0x40),_DAT_7ffe9c96ba20);
        if (cVar4 != '\0') {
LAB_7ffe99a4183e:
          *(undefined8 *)(self + 0x40) = 0;
          il2cpp_write_barrier_0();
          *(undefined8 *)(self + 0x40) = 0;
          il2cpp_write_barrier_0();
          return 0;
        }
        if ((((lVar2 != 0) && (*(longlong *)(lVar2 + 0x40) != 0)) &&
            (*(longlong *)(self + 0x40) != 0)) &&
           (lVar2 = *(longlong *)(*(longlong *)(lVar2 + 0x40) + 0x28), lVar2 != 0)) {
          FUN_7ffe99ac1b40(lVar2,*(undefined8 *)(*(longlong *)(self + 0x40) + 0x10),0);
          if (*(longlong *)(self + 0x40) != 0) {
            FUN_7ffe9adfa7a0(*(longlong *)(self + 0x40),_DAT_7ffe9c96b558);
            goto LAB_7ffe99a4183e;
          }
        }
      }
      goto LAB_7ffe99a41fb3;
    }
    bVar5 = 0;
  }
  return bVar5;
}

