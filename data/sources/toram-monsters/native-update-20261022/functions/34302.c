
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte FieldManager__LoadMapInfo_d__94_MoveNext(undefined *self,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  longlong *plVar6;
  undefined8 uVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined *puVar10;
  longlong *plVar11;
  undefined8 uVar12;
  longlong *plVar13;
  undefined8 uVar14;
  longlong lVar15;
  undefined8 uVar16;
  int aiStackX_8 [2];
  undefined4 auStackX_18 [2];
  ulonglong in_stack_ffffffffffffffb8;
  
  if (DAT_7ffe9cadfa7f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c92eda0);
    FUN_7ffe9996d590(&DAT_7ffe9c933ea8);
    FUN_7ffe9996d590(0x7ffe9c9465d0);
    FUN_7ffe9996d590(&DAT_7ffe9c94c948);
    FUN_7ffe9996d590(&DAT_7ffe9c9621c8);
    FUN_7ffe9996d590(&DAT_7ffe9c90c578);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c956608);
    FUN_7ffe9996d590(&DAT_7ffe9c956e00);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c954ef0);
    FUN_7ffe9996d590(&DAT_7ffe9c953578);
    FUN_7ffe9996d590(&DAT_7ffe9c960dc8);
    FUN_7ffe9996d590(&DAT_7ffe9c963400);
    FUN_7ffe9996d590(&DAT_7ffe9c931220);
    FUN_7ffe9996d590(&DAT_7ffe9c93da88);
    FUN_7ffe9996d590(&DAT_7ffe9c9312e8);
    FUN_7ffe9996d590(&DAT_7ffe9c93db50);
    FUN_7ffe9996d590(&DAT_7ffe9c9313a8);
    FUN_7ffe9996d590(&DAT_7ffe9c93dc10);
    FUN_7ffe9996d590(&DAT_7ffe9c8feeb8);
    FUN_7ffe9996d590(0x7ffe9c95d858);
    FUN_7ffe9996d590(0x7ffe9c964ca0);
    FUN_7ffe9996d590(0x7ffe9c93db38);
    FUN_7ffe9996d590(0x7ffe9c951db0);
    FUN_7ffe9996d590(0x7ffe9c951e78);
    FUN_7ffe9996d590(0x7ffe9c9520d8);
    FUN_7ffe9996d590(0x7ffe9c8f1c38);
    FUN_7ffe9996d590(0x7ffe9c96b9b8);
    FUN_7ffe9996d590(0x7ffe9c948728);
    FUN_7ffe9996d590(&DAT_7ffe9c956aa8);
    FUN_7ffe9996d590(0x7ffe9c951f40);
    FUN_7ffe9996d590(&DAT_7ffe9c951cf0);
    FUN_7ffe9996d590(0x7ffe9c9519e0);
    FUN_7ffe9996d590(&DAT_7ffe9c9449b0);
    FUN_7ffe9996d590(0x7ffe9c951918);
    FUN_7ffe9996d590(0x7ffe9c8f9cd0);
    FUN_7ffe9996d590(0x7ffe9c952010);
    FUN_7ffe9996d590(0x7ffe9c931850);
    FUN_7ffe9996d590(0x7ffe9c951c28);
    FUN_7ffe9996d590(&DAT_7ffe9c944bf8);
    FUN_7ffe9996d590(0x7ffe9c964d68);
    FUN_7ffe9996d590(0x7ffe9c951b68);
    FUN_7ffe9996d590(&DAT_7ffe9c9521a8);
    FUN_7ffe9996d590(0x7ffe9c963a88);
    FUN_7ffe9996d590(0x7ffe9c951aa0);
    FUN_7ffe9996d590(&DAT_7ffe9c94d840);
    FUN_7ffe9996d590(0x7ffe9c962268);
    FUN_7ffe9996d590(0x7ffe9c963b58);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    FUN_7ffe9996d590(&DAT_7ffe9c94d780);
    FUN_7ffe9996d590(0x7ffe9c9141a0);
    FUN_7ffe9996d590(0x7ffe9c8f1d08);
    FUN_7ffe9996d590(&DAT_7ffe9c952270);
    FUN_7ffe9996d590(&DAT_7ffe9c919440);
    DAT_7ffe9cadfa7f = '\x01';
  }
  iVar1 = *(int *)(self + 0x10);
  plVar13 = (longlong *)0x0;
  lVar9 = *(longlong *)(self + 0x30);
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (*(longlong *)(self + 0x38) == 0) goto LAB_7ffe9a87505b;
      if (*(char *)(*(longlong *)(self + 0x38) + 0x10) == '\0') {
        plVar11 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
        lVar9 = *(longlong *)(self + 0x60);
        if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a87505b;
        if ((lVar9 != 0) &&
           (lVar15 = func_0x7ffe9996c920(lVar9,*(undefined8 *)(*plVar11 + 0x40)), lVar15 == 0)) {
          uVar14 = func_0x7ffe9996d1f0();
          FUN_7ffe9996d760(uVar14,0);
          pcVar2 = (code *)swi(3);
          bVar5 = (*pcVar2)();
          return bVar5;
        }
        if ((int)plVar11[3] == 0) {
          FUN_7ffe9996d790();
          pcVar2 = (code *)swi(3);
          bVar5 = (*pcVar2)();
          return bVar5;
        }
        plVar11[4] = lVar9;
        il2cpp_write_barrier_0();
        func_0x7ffe999c3920(_DAT_7ffe9c94d780,plVar11);
        if (*(int *)(self + 0x70) < 5) {
          plVar13 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
          aiStackX_8[0] = *(int *)(self + 0x70) + 1;
          lVar9 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
          if (plVar13 == (longlong *)0x0) {
            FUN_7ffe9996d7a0();
            pcVar2 = (code *)swi(3);
            bVar5 = (*pcVar2)();
            return bVar5;
          }
          if ((lVar9 != 0) &&
             (lVar15 = func_0x7ffe9996c920(lVar9,*(undefined8 *)(*plVar13 + 0x40)), lVar15 == 0)) {
            uVar14 = func_0x7ffe9996d1f0();
            FUN_7ffe9996d760(uVar14,0);
            pcVar2 = (code *)swi(3);
            bVar5 = (*pcVar2)();
            return bVar5;
          }
          if ((int)plVar13[3] == 0) {
            FUN_7ffe9996d790();
            pcVar2 = (code *)swi(3);
            bVar5 = (*pcVar2)();
            return bVar5;
          }
          plVar13[4] = lVar9;
          il2cpp_write_barrier_0();
          func_0x7ffe999c3920(_DAT_7ffe9c94d840,plVar13,0);
          uVar14 = func_0x7ffe99940040(_DAT_7ffe9c8feeb8);
          FUN_7ffe9bdae370(uVar14,_DAT_7ffe9c049b74,0);
          *(undefined8 *)(self + 0x18) = uVar14;
          il2cpp_write_barrier_0();
          *(undefined4 *)(self + 0x10) = 2;
          return 1;
        }
        uVar14 = func_0x7ffe99940040(_DAT_7ffe9c93db50);
        func_0x7ffe999c3920(uVar14,0);
        *(undefined8 *)(self + 0x40) = uVar14;
        il2cpp_write_barrier_0();
        if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe9a87505b;
        *(undefined1 *)(*(longlong *)(self + 0x40) + 0x10) = 0;
        puVar10 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
        if (puVar10 == (undefined *)0x0) goto LAB_7ffe9a87505b;
        plVar11 = (longlong *)LocalizeManager_Get(puVar10,(undefined *)0x0,(undefined *)0x0);
        if (plVar11 != (longlong *)0x0) {
          if ((*(byte *)(*plVar11 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar11 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8) != _DAT_7ffe9c960dc8)) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
          if (bVar3) {
            plVar13 = plVar11;
          }
          lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
          if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a87505b;
          uVar7 = FUN_7ffe99a58320(plVar13,_DAT_7ffe9c944bf8,0);
          uVar16 = FUN_7ffe99a58320(plVar13,_DAT_7ffe9c9449b0,0);
          uVar14 = *(undefined8 *)(self + 0x40);
          uVar12 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
          FUN_7ffe999e6880(uVar12,uVar14,_DAT_7ffe9c9312e8,0);
          if (lVar9 == 0) goto LAB_7ffe9a87505b;
          FUN_7ffe9a2c9c20(lVar9,uVar7,uVar16,uVar12,0);
          goto LAB_7ffe9a8748bb;
        }
      }
      else {
        lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
        if (lVar15 == 0) goto LAB_7ffe9a87505b;
        in_stack_ffffffffffffffb8 = in_stack_ffffffffffffffb8 & 0xffffffffffffff00;
        plVar6 = (longlong *)
                 FUN_7ffe99aceed0(lVar15,*(undefined8 *)(self + 0x60),*(undefined8 *)(self + 0x68),4
                                  ,in_stack_ffffffffffffffb8,1,0);
        plVar11 = plVar13;
        if ((plVar6 != (longlong *)0x0) && (*plVar6 == _DAT_7ffe9c90c578)) {
          plVar11 = plVar6;
        }
        if (self[0x48] != '\0') {
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
          aiStackX_8[0] = *(int *)(self + 0x58);
          uVar14 = *(undefined8 *)(self + 0x60);
          uVar7 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
          uVar7 = FUN_7ffe9b36a740(_DAT_7ffe9c952270,uVar7,0);
          if (lVar15 == 0) {
            FUN_7ffe9996d7a0();
            pcVar2 = (code *)swi(3);
            bVar5 = (*pcVar2)();
            return bVar5;
          }
          plVar8 = (longlong *)
                   FUN_7ffe99aceed0(lVar15,uVar14,uVar7,0,
                                    in_stack_ffffffffffffffb8 & 0xffffffffffffff00,1,0);
          plVar6 = plVar13;
          if (plVar8 != (longlong *)0x0) {
            if ((*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c963400 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar8 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c963400 + 0x130) * 8) != _DAT_7ffe9c963400)) {
              bVar3 = false;
            }
            else {
              bVar3 = true;
            }
            if (bVar3) {
              plVar6 = plVar8;
            }
          }
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar4 = FUN_7ffe9bda2160(plVar6,0);
          if (cVar4 != '\0') {
            if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a87505b;
            uVar14 = FUN_7ffe9bda7ca0(plVar6,0);
            *(undefined8 *)(self + 0x50) = uVar14;
            il2cpp_write_barrier_0();
          }
        }
        lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
        if (lVar15 == 0) goto LAB_7ffe9a87505b;
        FUN_7ffe99ad1300(lVar15,*(undefined8 *)(self + 0x60),0,0);
        if (*(longlong *)(self + 0x38) == 0) goto LAB_7ffe9a87505b;
        if (*(char *)(*(longlong *)(self + 0x38) + 0x10) != '\0') {
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar4 = FUN_7ffe9bda2160(plVar11);
          if (cVar4 != '\0') {
            if (plVar11 != (longlong *)0x0) {
              FUN_7ffe9bd9b390(plVar11,1,0);
              lVar15 = FUN_7ffe9bd9b890(plVar11,0);
              if ((lVar9 != 0) && (uVar14 = FUN_7ffe9bd98a10(lVar9,0), lVar15 != 0)) {
                FUN_7ffe9bdbfe50(lVar15,uVar14,0);
                uVar14 = FUN_7ffe9ab9c3a0(plVar11,_DAT_7ffe9c9621c8);
                *(undefined8 *)(lVar9 + 0x20) = uVar14;
                il2cpp_write_barrier_0();
                if (self[0x48] == '\0') {
                  return 0;
                }
                lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c956608);
                if (lVar9 != 0) {
                  FUN_7ffe9a85ad00(lVar9,*(undefined4 *)(self + 0x58),*(undefined8 *)(self + 0x50),0
                                  );
                  return 0;
                }
              }
            }
            goto LAB_7ffe9a87505b;
          }
        }
        lVar9 = func_0x7ffe99940040(_DAT_7ffe9c93dc10);
        func_0x7ffe999c3920(lVar9);
        if (lVar9 == 0) goto LAB_7ffe9a87505b;
        *(undefined1 *)(lVar9 + 0x10) = 0;
        puVar10 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
        if (puVar10 == (undefined *)0x0) goto LAB_7ffe9a87505b;
        plVar11 = (longlong *)LocalizeManager_Get(puVar10,(undefined *)0x0,(undefined *)0x0);
        if (plVar11 != (longlong *)0x0) {
          if ((*(byte *)(*plVar11 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar11 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8) != _DAT_7ffe9c960dc8)) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
          if (bVar3) {
            plVar13 = plVar11;
          }
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
          if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a87505b;
          uVar14 = FUN_7ffe99a58320(plVar13,_DAT_7ffe9c944bf8,0);
          uVar7 = FUN_7ffe99a58320(plVar13,_DAT_7ffe9c9449b0,0);
          uVar16 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
          FUN_7ffe999e6880(uVar16,lVar9,_DAT_7ffe9c9313a8,0);
          if (lVar15 == 0) goto LAB_7ffe9a87505b;
          FUN_7ffe9a2c9c20(lVar15,uVar14,uVar7,uVar16,0);
          goto LAB_7ffe9a874701;
        }
      }
      FUN_7ffe9b141840(_DAT_7ffe9c956e00);
      goto LAB_7ffe9a87505b;
    }
    if (iVar1 != 2) {
      if (iVar1 != 3) {
        return 0;
      }
      *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7ffe9a8748bb:
      if (*(longlong *)(self + 0x40) != 0) {
        if (*(char *)(*(longlong *)(self + 0x40) + 0x10) == '\0') {
          *(undefined8 *)(self + 0x18) = 0;
          il2cpp_write_barrier_0();
          *(undefined4 *)(self + 0x10) = 3;
          return 1;
        }
LAB_7ffe9a874701:
        if (*(int *)(_DAT_7ffe9c933ea8 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        FUN_7ffe9bd77910(0);
        return 0;
      }
      goto LAB_7ffe9a87505b;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    *(int *)(self + 0x70) = *(int *)(self + 0x70) + 1;
    goto LAB_7ffe9a874f40;
  }
  *(undefined8 *)(self + 0x50) = 0;
  *(undefined4 *)(self + 0x10) = 0xffffffff;
  self[0x48] = 0;
  il2cpp_write_barrier_0();
  *(undefined4 *)(self + 0x58) = 0xffffffff;
  *(undefined8 *)(self + 0x60) = _DAT_7ffe9c8f1820;
  il2cpp_write_barrier_0();
  *(undefined8 *)(self + 0x68) = _DAT_7ffe9c8f1820;
  il2cpp_write_barrier_0();
  iVar1 = *(int *)(self + 0x20);
  switch(iVar1) {
  case 4:
    *(undefined8 *)(self + 0x60) = uRam00007ffe9c951c28;
    il2cpp_write_barrier_0();
    aiStackX_8[0] = 0;
    uVar7 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
    uVar14 = uRam00007ffe9c962268;
    goto LAB_7ffe9a874a9d;
  case 5:
    *(undefined8 *)(self + 0x60) = uRam00007ffe9c951db0;
    il2cpp_write_barrier_0();
    aiStackX_8[0] = CONCAT31(aiStackX_8[0]._1_3_,self[0x24]);
    uVar7 = func_0x7ffe9996c8e0(_DAT_7ffe9c94c948,aiStackX_8);
    uVar14 = uRam00007ffe9c8f1d08;
    goto LAB_7ffe9a874a9d;
  case 6:
  case 7:
  case 9:
LAB_7ffe9a874e90:
    aiStackX_8[0] = *(int *)(self + 0x28) / 1000;
    *(int *)(self + 0x58) = aiStackX_8[0];
    uVar14 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
    uVar14 = FUN_7ffe9b36a740(_DAT_7ffe9c951cf0,uVar14,0);
    *(undefined8 *)(self + 0x60) = uVar14;
    il2cpp_write_barrier_0();
    auStackX_18[0] = *(undefined4 *)(self + 0x28);
    uVar14 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,auStackX_18);
    uVar14 = FUN_7ffe9b36a740(_DAT_7ffe9c919440,uVar14,0);
    *(undefined8 *)(self + 0x68) = uVar14;
    il2cpp_write_barrier_0();
    lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956608);
    if (lVar15 == 0) {
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      bVar5 = (*pcVar2)();
      return bVar5;
    }
    self[0x48] = *(int *)(lVar15 + 0x28) != *(int *)(self + 0x58);
    break;
  case 8:
    *(undefined8 *)(self + 0x60) = uRam00007ffe9c951b68;
    il2cpp_write_barrier_0();
    aiStackX_8[0] = 0;
    uVar7 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
    uVar14 = uRam00007ffe9c95d858;
LAB_7ffe9a874a9d:
    uVar14 = FUN_7ffe9b36a740(uVar14,uVar7,0);
code_r0x7ffe9a874aa8:
    *(undefined8 *)(self + 0x68) = uVar14;
    il2cpp_write_barrier_0();
    break;
  case 10:
    *(undefined8 *)(self + 0x60) = uRam00007ffe9c952010;
    il2cpp_write_barrier_0();
    *(undefined8 *)(self + 0x68) = uRam00007ffe9c96b9b8;
    il2cpp_write_barrier_0();
    break;
  default:
    if (iVar1 == 0x11) {
      *(undefined8 *)(self + 0x60) = _DAT_7ffe9c9521a8;
      il2cpp_write_barrier_0();
      aiStackX_8[0] = 0;
      uVar7 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
      uVar14 = _DAT_7ffe9c956aa8;
      goto LAB_7ffe9a874a9d;
    }
    switch(iVar1) {
    case 0x16:
      *(undefined8 *)(self + 0x60) = uRam00007ffe9c951918;
      il2cpp_write_barrier_0();
      lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
      if (lVar15 == 0) goto LAB_7ffe9a87505b;
      plVar13 = *(longlong **)(lVar15 + 0x28);
      if (plVar13 != (longlong *)0x0) {
        if (((*(byte *)(lRam00007ffe9c9465d0 + 0x130) <= *(byte *)(*plVar13 + 0x130)) &&
            (*(longlong *)
              (*(longlong *)(*plVar13 + 200) + -8 +
              (ulonglong)*(byte *)(lRam00007ffe9c9465d0 + 0x130) * 8) == lRam00007ffe9c9465d0)) &&
           ((char)plVar13[0xf] == '\x01')) {
          uVar14 = FUN_7ffe9b5043c0(self + 0x28,0);
          uVar14 = FUN_7ffe9b3675b0(uRam00007ffe9c963a88,uVar14,0);
          goto code_r0x7ffe9a874aa8;
        }
      }
      *(undefined8 *)(self + 0x68) = uRam00007ffe9c963b58;
      il2cpp_write_barrier_0();
      break;
    default:
      goto LAB_7ffe9a874e90;
    case 0x1b:
      uVar14 = FUN_7ffe9bda5f80(uRam00007ffe9c93db38,0);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      plVar11 = (longlong *)FUN_7ffe9bda12a0(uVar14,0);
      if (plVar11 != (longlong *)0x0) {
        if (*plVar11 == _DAT_7ffe9c90c578) {
          plVar13 = plVar11;
        }
        if (plVar13 != (longlong *)0x0) {
          FUN_7ffe9bd9b390(plVar13,1,0);
          lVar15 = FUN_7ffe9bd9b890(plVar13,0);
          if ((lVar9 != 0) && (uVar14 = FUN_7ffe9bd98a10(lVar9,0), lVar15 != 0)) {
            FUN_7ffe9bdbfe50(lVar15,uVar14,0);
            uVar14 = FUN_7ffe9ab9c3a0(plVar13,_DAT_7ffe9c9621c8);
            *(undefined8 *)(lVar9 + 0x20) = uVar14;
            il2cpp_write_barrier_0();
            return 0;
          }
        }
      }
      goto LAB_7ffe9a87505b;
    case 0x1e:
      *(undefined8 *)(self + 0x60) = uRam00007ffe9c951db0;
      il2cpp_write_barrier_0();
      aiStackX_8[0] = (uint)(byte)self[0x24] + ((byte)self[0x24] / 10) * -10;
      uVar7 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
      uVar14 = uRam00007ffe9c8f1c38;
      goto LAB_7ffe9a874a9d;
    case 0x1f:
      *(undefined8 *)(self + 0x60) = uRam00007ffe9c9519e0;
      il2cpp_write_barrier_0();
      uVar14 = FUN_7ffe9b485060(self + 0x24,0);
      uVar14 = FUN_7ffe9b3675b0(uRam00007ffe9c8f9cd0,uVar14,0);
      goto code_r0x7ffe9a874aa8;
    case 0x20:
      *(undefined8 *)(self + 0x60) = uRam00007ffe9c951f40;
      il2cpp_write_barrier_0();
      if (*(int *)(self + 0x28) == 0x17250) {
        *(undefined8 *)(self + 0x68) = uRam00007ffe9c964d68;
        il2cpp_write_barrier_0();
      }
      else {
        *(undefined8 *)(self + 0x68) = uRam00007ffe9c964ca0;
        il2cpp_write_barrier_0();
      }
      break;
    case 0x21:
      *(undefined8 *)(self + 0x60) = uRam00007ffe9c951aa0;
      il2cpp_write_barrier_0();
      *(undefined8 *)(self + 0x68) = uRam00007ffe9c9141a0;
      il2cpp_write_barrier_0();
      break;
    case 0x22:
      *(undefined8 *)(self + 0x60) = uRam00007ffe9c9520d8;
      il2cpp_write_barrier_0();
      aiStackX_8[0] = *(int *)(self + 0x28);
      uVar7 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
      uVar14 = uRam00007ffe9c931850;
      goto LAB_7ffe9a874a9d;
    case 0x24:
      *(undefined8 *)(self + 0x60) = uRam00007ffe9c951e78;
      il2cpp_write_barrier_0();
      *(undefined8 *)(self + 0x68) = uRam00007ffe9c948728;
      il2cpp_write_barrier_0();
    }
  }
  *(undefined4 *)(self + 0x70) = 0;
LAB_7ffe9a874f40:
  if (4 < *(int *)(self + 0x70)) {
    return 0;
  }
  uVar14 = func_0x7ffe99940040(_DAT_7ffe9c93da88);
  func_0x7ffe999c3920(uVar14,0);
  *(undefined8 *)(self + 0x38) = uVar14;
  il2cpp_write_barrier_0();
  if (*(longlong *)(self + 0x38) != 0) {
    *(undefined1 *)(*(longlong *)(self + 0x38) + 0x10) = 0;
    lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
    uVar14 = *(undefined8 *)(self + 0x60);
    uVar7 = *(undefined8 *)(self + 0x38);
    uVar16 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
    FUN_7ffe9ac2ed50(uVar16,uVar7,_DAT_7ffe9c931220,0);
    if ((lVar15 != 0) && (uVar14 = FUN_7ffe99ad0580(lVar15,uVar14,1,uVar16,0), lVar9 != 0)) {
      uVar14 = FUN_7ffe9bd9f640(lVar9,uVar14,0);
      *(undefined8 *)(self + 0x18) = uVar14;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
  }
LAB_7ffe9a87505b:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar5 = (*pcVar2)();
  return bVar5;
}

