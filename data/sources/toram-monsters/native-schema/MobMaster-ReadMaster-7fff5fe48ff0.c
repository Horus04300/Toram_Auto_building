
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobMaster_ReadMaster
               (undefined *self,int fieldId,undefined *mobDbAsset,undefined *popMobList,
               undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  longlong *plVar8;
  longlong lVar9;
  longlong lVar10;
  undefined8 uVar11;
  longlong *plVar12;
  undefined *puVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  ushort uVar16;
  int iVar17;
  uint uVar18;
  int aiStackX_10 [2];
  byte bStack_e8;
  longlong *plStack_e0;
  int iStack_d8;
  int iStack_d4;
  int iStack_d0;
  int iStack_cc;
  undefined8 uStack_c8;
  longlong **pplStack_c0;
  longlong *plStack_b8;
  longlong *plStack_b0;
  undefined8 uStack_a8;
  longlong **pplStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  longlong lStack_88;
  undefined *puStack_80;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  longlong lStack_38;
  
  aiStackX_10[0] = fieldId;
  if (DAT_7fff625e4d5d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b500);
    FUN_7fff5f47d450(&DAT_7fff624068b0);
    FUN_7fff5f47d450(&DAT_7fff62479850);
    FUN_7fff5f47d450(&DAT_7fff62479920);
    FUN_7fff5f47d450(&DAT_7fff62406980);
    FUN_7fff5f47d450(&DAT_7fff62406b20);
    FUN_7fff5f47d450(&DAT_7fff62406bf0);
    FUN_7fff5f47d450(&DAT_7fff62406090);
    FUN_7fff5f47d450(&DAT_7fff62406cc0);
    FUN_7fff5f47d450(&DAT_7fff62404728);
    FUN_7fff5f47d450(&DAT_7fff62411318);
    FUN_7fff5f47d450(&DAT_7fff6242f928);
    FUN_7fff5f47d450(&DAT_7fff6243e520);
    FUN_7fff5f47d450(&DAT_7fff6243e5e0);
    FUN_7fff5f47d450(0x7fff6243e6a8);
    FUN_7fff5f47d450(&DAT_7fff624469b0);
    FUN_7fff5f47d450(&DAT_7fff62446d80);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff6245cd60);
    FUN_7fff5f47d450(&DAT_7fff62462838);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    FUN_7fff5f47d450(&DAT_7fff6241fab8);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62443130);
    FUN_7fff5f47d450(0x7fff624431f0);
    FUN_7fff5f47d450(&DAT_7fff624717c0);
    FUN_7fff5f47d450(&DAT_7fff623f59d8);
    FUN_7fff5f47d450(&DAT_7fff62422288);
    FUN_7fff5f47d450(&DAT_7fff623f78b8);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff62469578);
    FUN_7fff5f47d450(&DAT_7fff624697e0);
    FUN_7fff5f47d450(&DAT_7fff623f5588);
    FUN_7fff5f47d450(&DAT_7fff623f5318);
    FUN_7fff5f47d450(&DAT_7fff62400ac0);
    FUN_7fff5f47d450(&DAT_7fff62400d30);
    FUN_7fff5f47d450(&DAT_7fff6244e2e0);
    FUN_7fff5f47d450(&DAT_7fff6244e218);
    FUN_7fff5f47d450(&DAT_7fff6244e158);
    FUN_7fff5f47d450(&DAT_7fff6244e090);
    DAT_7fff625e4d5d = '\x01';
  }
  iVar7 = 0;
  plStack_b8 = (longlong *)0x0;
  plStack_e0 = (longlong *)0x0;
  plStack_b0 = (longlong *)0x0;
  uStack_98 = (longlong *)0x0;
  uStack_90 = 0;
  lStack_88 = 0;
  plVar8 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
  iStack_d8 = fieldId;
  lVar9 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,&iStack_d8);
  if (plVar8 == (longlong *)0x0) goto LAB_7fff5fe49e2c;
  if ((lVar9 != 0) &&
     (lVar10 = func_0x7fff5f47c7e0(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0)) {
    uVar11 = func_0x7fff5f47d0b0();
    FUN_7fff5f47d620(uVar11,0);
    pcVar1 = (code *)swi(3);
    bVar4 = (*pcVar1)();
    return bVar4;
  }
  if ((int)plVar8[3] == 0) {
    FUN_7fff5f47d650();
LAB_7fff5fe49e48:
    FUN_7fff5f47d660();
LAB_7fff5fe49e4e:
    uVar11 = func_0x7fff5f47d0b0();
    FUN_7fff5f47d620(uVar11,0);
LAB_7fff5fe49e5d:
    FUN_7fff5f47d650();
LAB_7fff5fe49e62:
    uVar11 = func_0x7fff5f47d0b0();
    FUN_7fff5f47d620(uVar11,0);
LAB_7fff5fe49e71:
    FUN_7fff5f47d650();
LAB_7fff5fe49e76:
    uVar11 = func_0x7fff5f47d0b0();
    FUN_7fff5f47d620(uVar11,0);
LAB_7fff5fe49e85:
    FUN_7fff5f47d650();
LAB_7fff5fe49e8a:
    uVar11 = func_0x7fff5f47d0b0();
    FUN_7fff5f47d620(uVar11,0);
LAB_7fff5fe49e99:
    FUN_7fff5f47d650();
LAB_7fff5fe49e9e:
    FUN_7fff5f47d660();
LAB_7fff5fe49ea3:
    FUN_7fff5f47d660();
LAB_7fff5fe49ea8:
    FUN_7fff5f47d660();
LAB_7fff5fe49ead:
    FUN_7fff5f47d660();
LAB_7fff5fe49eb2:
    uVar11 = func_0x7fff5f47d0b0();
    FUN_7fff5f47d620(uVar11,0);
LAB_7fff5fe49ec1:
    FUN_7fff5f47d650();
LAB_7fff5fe49ec6:
    FUN_7fff5f47d650();
LAB_7fff5fe49ecb:
    FUN_7fff5f47d660();
LAB_7fff5fe49ed0:
    FUN_7fff5f47d660();
LAB_7fff5fe49ed5:
    FUN_7fff5f47d660();
LAB_7fff5fe49eda:
    FUN_7fff5f47d660();
LAB_7fff5fe49edf:
    FUN_7fff5f47d660();
LAB_7fff5fe49ee4:
    FUN_7fff5f47d660();
LAB_7fff5fe49ee9:
    FUN_7fff5f47d660();
LAB_7fff5fe49eee:
    FUN_7fff5f47d660();
LAB_7fff5fe49ef3:
    FUN_7fff5f47d660();
LAB_7fff5fe49ef8:
    FUN_7fff5f47d660();
LAB_7fff5fe49efd:
    FUN_7fff5f47d660();
LAB_7fff5fe49f02:
    FUN_7fff5f47d660();
LAB_7fff5fe49f07:
    FUN_7fff5f47d660();
    FUN_7fff5f40a410();
LAB_7fff5fe49f12:
    FUN_7fff5f47d660();
    FUN_7fff5f40a410();
  }
  else {
    plVar8[4] = lVar9;
    thunk_FUN_7fff5f491fd0();
    _loadFieldData_d__125_System_IDisposable_Dispose(_DAT_7fff6244e090,(undefined *)plVar8);
    bStack_e8 = 1;
    if (*(longlong *)(self + 0x20) == 0) {
LAB_7fff5fe49e2c:
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      bVar4 = (*pcVar1)();
      return bVar4;
    }
    FUN_7fff607d86f0(*(longlong *)(self + 0x20),_DAT_7fff62406980);
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5fe49e2c;
    FUN_7fff607d86f0(*(longlong *)(self + 0x28),_DAT_7fff62479920);
    lVar9 = *(longlong *)(self + 0x40);
    if (lVar9 == 0) goto LAB_7fff5fe49e2c;
    *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
    iVar5 = *(int *)(lVar9 + 0x18);
    *(undefined4 *)(lVar9 + 0x18) = 0;
    if (0 < iVar5) {
      FUN_7fff61022d30(*(undefined8 *)(lVar9 + 0x10),0);
    }
    self[0x38] = 0;
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar3 = FUN_7fff618ab2e0(mobDbAsset,0,0);
    if (cVar3 == '\0') {
LAB_7fff5fe499bb:
      if ((*(longlong *)(self + 0x20) == 0) ||
         (lVar9 = FUN_7fff607dcb60(*(longlong *)(self + 0x20),_DAT_7fff62406cc0), lVar9 == 0)) {
LAB_7fff5fe49f72:
        FUN_7fff5f47d660();
        pcVar1 = (code *)swi(3);
        bVar4 = (*pcVar1)();
        return bVar4;
      }
      iVar7 = FUN_7fff60a4e310(lVar9,_DAT_7fff62400d30);
      if (iVar7 < 1) {
        return bStack_e8;
      }
      if (*(longlong *)(self + 0x20) == 0) goto LAB_7fff5fe49f72;
      uVar11 = FUN_7fff607dcb60(*(longlong *)(self + 0x20),_DAT_7fff62406cc0);
      if (*(int *)(_DAT_7fff623f5318 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(_DAT_7fff623f5318);
      }
      lVar9 = *(longlong *)(*(longlong *)(_DAT_7fff623f5318 + 0xb8) + 8);
      if (lVar9 == 0) {
        if (*(int *)(_DAT_7fff623f5318 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(_DAT_7fff623f5318);
        }
        uVar15 = **(undefined8 **)(_DAT_7fff623f5318 + 0xb8);
        lVar9 = func_0x7fff5f44ff00(_DAT_7fff62446d80);
        FUN_7fff60a1d7e0(lVar9,uVar15,_DAT_7fff62469578,0);
        *(longlong *)(*(longlong *)(_DAT_7fff623f5318 + 0xb8) + 8) = lVar9;
        thunk_FUN_7fff5f491fd0();
      }
      lVar9 = FUN_7fff6069d430(uVar11,lVar9,_DAT_7fff6242f928);
      if (lVar9 == 0) goto LAB_7fff5fe49f72;
      plStack_b0 = (longlong *)FUN_7fff5f252ec0(0,_DAT_7fff6245cd60,lVar9);
      uStack_c8 = 0;
      pplStack_c0 = &plStack_b0;
      while (plStack_b0 != (longlong *)0x0) {
        cVar3 = FUN_7fff5f252ec0(0);
        if (cVar3 == '\0') {
          if (*pplStack_c0 == (longlong *)0x0) {
            return bStack_e8;
          }
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
          return bStack_e8;
        }
        puVar13 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623f5588);
        _loadFieldData_d__125_System_IDisposable_Dispose(puVar13,(undefined *)0x0);
        plVar8 = plStack_b0;
        if (plStack_b0 == (longlong *)0x0) goto LAB_7fff5fe49f61;
        lVar9 = *plStack_b0;
        uVar16 = 0;
        if (*(ushort *)(lVar9 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar16 * 0x10) ==
                _DAT_7fff62462838) {
              puVar14 = (undefined8 *)
                        (lVar9 + 0x138 +
                        (longlong)
                        *(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar16 * 0x10) * 0x10)
              ;
              goto LAB_7fff5fe49b89;
            }
            uVar16 = uVar16 + 1;
          } while (uVar16 < *(ushort *)(lVar9 + 0x12e));
        }
        puVar14 = (undefined8 *)FUN_7fff5f3de400(plStack_b0,_DAT_7fff62462838,0);
LAB_7fff5fe49b89:
        lVar9 = (*(code *)*puVar14)(plVar8,puVar14[1]);
        if (puVar13 == (undefined *)0x0) goto LAB_7fff5fe49f5c;
        plVar8 = (longlong *)(puVar13 + 0x10);
        *plVar8 = lVar9;
        thunk_FUN_7fff5f491fd0();
        uVar11 = *(undefined8 *)(self + 0x40);
        uVar15 = func_0x7fff5f44ff00(_DAT_7fff624469b0);
        FUN_7fff60a1d7e0(uVar15,puVar13,_DAT_7fff624697e0,0);
        lVar9 = FUN_7fff6068f870(uVar11,uVar15,_DAT_7fff62411318);
        if (lVar9 == 0) {
          lVar9 = func_0x7fff5f44ff00(_DAT_7fff623f59d8);
          FUN_7fff5fe3b6d0(lVar9,0);
          if (lVar9 == 0) goto LAB_7fff5fe49f2d;
          FUN_7fff5fe3b2c0(lVar9,*plVar8,0);
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff5fe49f28;
          FUN_7fff5f253100(*(longlong *)(self + 0x40),lVar9,_DAT_7fff62443130);
          if (*plVar8 == 0) goto LAB_7fff5fe49f23;
          *(longlong *)(*plVar8 + 0xa8) = lVar9;
          thunk_FUN_7fff5f491fd0();
        }
        if (*plVar8 == 0) goto LAB_7fff5fe49f57;
        lVar10 = *(longlong *)(*plVar8 + 0x98);
        if (lVar10 == 0) goto LAB_7fff5fe49f52;
        lVar10 = FUN_7fff607dcb60(lVar10,_DAT_7fff62406090);
        if (lVar10 == 0) goto LAB_7fff5fe49f4d;
        FUN_7fff60a4b980(&uStack_48,lVar10,_DAT_7fff62400ac0);
        uStack_98 = (longlong *)CONCAT44(uStack_44,uStack_48);
        uStack_90 = CONCAT44(uStack_3c,uStack_40);
        lStack_88 = lStack_38;
        uStack_a8 = 0;
        pplStack_a0 = (longlong **)&uStack_98;
        while (cVar3 = FUN_7fff60941650(&uStack_98,_DAT_7fff6243e5e0), lVar10 = lStack_88,
              cVar3 != '\0') {
          if (*(longlong *)(self + 0x20) == 0) goto LAB_7fff5fe49f42;
          uVar11 = FUN_7fff607dcab0(*(longlong *)(self + 0x20),_DAT_7fff62406bf0);
          if (lVar10 == 0) goto LAB_7fff5fe49f3d;
          cVar3 = FUN_7fff60689fb0(uVar11,*(undefined4 *)(lVar10 + 0x18),_DAT_7fff62404728);
          if (cVar3 != '\0') {
            if (*(longlong *)(self + 0x20) == 0) goto LAB_7fff5fe49f38;
            uVar11 = FUN_7fff6083faa0(*(longlong *)(self + 0x20),*(undefined4 *)(lVar10 + 0x18),
                                      _DAT_7fff62406b20);
            if (lVar9 == 0) goto LAB_7fff5fe49f33;
            FUN_7fff5fe3b2c0(lVar9,uVar11,0);
          }
        }
        _loadFieldData_d__125_System_IDisposable_Dispose((undefined *)&uStack_98,_DAT_7fff6243e520);
      }
      goto LAB_7fff5fe49f66;
    }
    if (mobDbAsset != (undefined *)0x0) {
      uVar11 = FUN_7fff618b0e20(mobDbAsset,0);
      plVar8 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff624717c0);
      FUN_7fff60fcae90(plVar8,uVar11,0);
      uStack_c8 = 0;
      pplStack_c0 = &plStack_b8;
      plStack_b8 = plVar8;
      plVar12 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6244b500);
      FUN_7fff60fd77f0(plVar12,plVar8,0);
      uStack_a8 = 0;
      pplStack_a0 = &plStack_e0;
      plStack_e0 = plVar12;
      if (plVar12 == (longlong *)0x0) goto LAB_7fff5fe49f07;
      iVar5 = (**(code **)(*plVar12 + 0x228))(plVar12,*(undefined8 *)(*plVar12 + 0x230));
      iStack_d0 = iVar5;
      if (iVar5 < 1) {
        if (plStack_e0 == (longlong *)0x0) goto LAB_7fff5fe49e48;
        iVar5 = (**(code **)(*plStack_e0 + 0x228))(plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
      }
      plVar8 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,2);
      iStack_d8 = iVar5;
      lVar9 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,&iStack_d8);
      if (plVar8 == (longlong *)0x0) goto LAB_7fff5fe49f02;
      if ((lVar9 != 0) &&
         (lVar10 = func_0x7fff5f47c7e0(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0))
      goto LAB_7fff5fe49e4e;
      if ((int)plVar8[3] == 0) goto LAB_7fff5fe49e5d;
      plVar8[4] = lVar9;
      thunk_FUN_7fff5f491fd0();
      iStack_d4 = iStack_d0;
      lVar9 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,&iStack_d4);
      if ((lVar9 != 0) &&
         (lVar10 = func_0x7fff5f47c7e0(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0))
      goto LAB_7fff5fe49e62;
      if (*(uint *)(plVar8 + 3) < 2) goto LAB_7fff5fe49e71;
      plVar8[5] = lVar9;
      thunk_FUN_7fff5f491fd0();
      _loadFieldData_d__125_System_IDisposable_Dispose(_DAT_7fff6244e218,(undefined *)plVar8);
      if (iVar5 == aiStackX_10[0]) {
        if (plStack_e0 != (longlong *)0x0) {
          iVar5 = (**(code **)(*plStack_e0 + 0x228))
                            (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
          iStack_cc = iVar5;
          plVar8 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
          iStack_d4 = iVar5;
          lVar9 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,&iStack_d4);
          if (plVar8 != (longlong *)0x0) {
            if ((lVar9 != 0) &&
               (lVar10 = func_0x7fff5f47c7e0(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0))
            goto LAB_7fff5fe49e76;
            if ((int)plVar8[3] == 0) goto LAB_7fff5fe49e85;
            plVar8[4] = lVar9;
            thunk_FUN_7fff5f491fd0();
            _loadFieldData_d__125_System_IDisposable_Dispose(_DAT_7fff6244e158,(undefined *)plVar8);
            while (iVar2 = iStack_d0, iVar17 = 0, iStack_d8 = iVar7, iVar7 < iVar5) {
              puStack_80 = MobStatusMaster_CreateStatusMaster
                                     (aiStackX_10[0],iStack_d0,(undefined *)plStack_e0,
                                      (undefined *)0x0);
              if (puStack_80 == (undefined *)0x0) goto LAB_7fff5fe49ead;
              if (*(longlong *)(self + 0x20) == 0) goto LAB_7fff5fe49ea8;
              FUN_7fff60857660(*(longlong *)(self + 0x20),*(undefined4 *)(puStack_80 + 0x10));
              if (iVar2 < -1) {
                if (plStack_e0 == (longlong *)0x0) goto LAB_7fff5fe49ea3;
                iVar7 = (**(code **)(*plStack_e0 + 0x228))
                                  (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                iStack_d4 = iVar7;
                if (0 < iVar7) {
                  plVar8 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422288,iVar7);
                  for (uVar18 = 0; plVar12 = plStack_e0, (int)uVar18 < iVar7; uVar18 = uVar18 + 1) {
                    puVar13 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623f78b8);
                    MobPropertyMaster__ctor(puVar13,(undefined *)plVar12,(undefined *)0x0);
                    if (plVar8 == (longlong *)0x0) goto LAB_7fff5fe49e9e;
                    if ((puVar13 != (undefined *)0x0) &&
                       (lVar9 = func_0x7fff5f47c7e0(puVar13,*(undefined8 *)(*plVar8 + 0x40)),
                       lVar9 == 0)) goto LAB_7fff5fe49e8a;
                    if (*(uint *)(plVar8 + 3) <= uVar18) goto LAB_7fff5fe49e99;
                    plVar8[(longlong)(int)uVar18 + 4] = (longlong)puVar13;
                    thunk_FUN_7fff5f491fd0();
                    iVar7 = iStack_d4;
                  }
                  MobStatusMaster_SetMobPropertyMaster
                            (puStack_80,(undefined *)plVar8,(undefined *)0x0);
                  iVar5 = iStack_cc;
                }
              }
              iVar7 = iStack_d8 + 1;
            }
            if (iStack_d0 < 0) {
              if (plStack_e0 == (longlong *)0x0) goto LAB_7fff5fe49eee;
              iVar7 = (**(code **)(*plStack_e0 + 0x228))
                                (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
              iStack_cc = iVar7;
              plVar8 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
              aiStackX_10[0] = iVar7;
              lVar9 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_10);
              if (plVar8 == (longlong *)0x0) goto LAB_7fff5fe49ee9;
              if ((lVar9 != 0) &&
                 (lVar10 = func_0x7fff5f47c7e0(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0))
              goto LAB_7fff5fe49eb2;
              if ((int)plVar8[3] == 0) goto LAB_7fff5fe49ec1;
              plVar8[4] = lVar9;
              thunk_FUN_7fff5f491fd0();
              _loadFieldData_d__125_System_IDisposable_Dispose
                        (_DAT_7fff6244e2e0,(undefined *)plVar8);
              for (; iVar17 < iVar7; iVar17 = iVar17 + 1) {
                if (plStack_e0 == (longlong *)0x0) goto LAB_7fff5fe49ee4;
                aiStackX_10[0] =
                     (**(code **)(*plStack_e0 + 0x228))
                               (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                if (plStack_e0 == (longlong *)0x0) goto LAB_7fff5fe49edf;
                iVar7 = (**(code **)(*plStack_e0 + 0x228))
                                  (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                lVar9 = func_0x7fff5f47c850(_DAT_7fff6241fab8,iVar7);
                for (uVar18 = 0; (int)uVar18 < iVar7; uVar18 = uVar18 + 1) {
                  if (plStack_e0 == (longlong *)0x0) goto LAB_7fff5fe49ed5;
                  uVar6 = (**(code **)(*plStack_e0 + 0x228))
                                    (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                  if (lVar9 == 0) goto LAB_7fff5fe49ed0;
                  if (*(uint *)(lVar9 + 0x18) <= uVar18) goto LAB_7fff5fe49ec6;
                  *(undefined4 *)(lVar9 + 0x20 + (longlong)(int)uVar18 * 4) = uVar6;
                  if (plStack_e0 == (longlong *)0x0) goto LAB_7fff5fe49ecb;
                  (**(code **)(*plStack_e0 + 0x228))
                            (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                }
                if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5fe49eda;
                FUN_7fff60857660(*(longlong *)(self + 0x28),aiStackX_10[0],lVar9,_DAT_7fff62479850);
                iVar7 = iStack_cc;
              }
            }
            goto LAB_7fff5fe498a9;
          }
          goto LAB_7fff5fe49ef8;
        }
        goto LAB_7fff5fe49efd;
      }
      bStack_e8 = 0;
LAB_7fff5fe498a9:
      if (plStack_e0 == (longlong *)0x0) goto LAB_7fff5fe49ef3;
      (**(code **)(*plStack_e0 + 0x198))(plStack_e0,*(undefined8 *)(*plStack_e0 + 0x1a0));
      if (plStack_e0 != (longlong *)0x0) {
        FUN_7fff5f253010(0,_DAT_7fff624413c0);
      }
      if (plStack_b8 != (longlong *)0x0) {
        (**(code **)(*plStack_b8 + 600))(plStack_b8,*(undefined8 *)(*plStack_b8 + 0x260));
        if (plStack_b8 != (longlong *)0x0) {
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
        }
        goto LAB_7fff5fe499bb;
      }
      goto LAB_7fff5fe49f12;
    }
  }
  FUN_7fff5f47d660();
LAB_7fff5fe49f23:
  FUN_7fff5f47d660();
LAB_7fff5fe49f28:
  FUN_7fff5f47d660();
LAB_7fff5fe49f2d:
  FUN_7fff5f47d660();
LAB_7fff5fe49f33:
  FUN_7fff5f47d660();
LAB_7fff5fe49f38:
  FUN_7fff5f47d660();
LAB_7fff5fe49f3d:
  FUN_7fff5f47d660();
LAB_7fff5fe49f42:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
LAB_7fff5fe49f4d:
  FUN_7fff5f47d660();
LAB_7fff5fe49f52:
  FUN_7fff5f47d660();
LAB_7fff5fe49f57:
  FUN_7fff5f47d660();
LAB_7fff5fe49f5c:
  FUN_7fff5f47d660();
LAB_7fff5fe49f61:
  FUN_7fff5f47d660();
LAB_7fff5fe49f66:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  bVar4 = (*pcVar1)();
  return bVar4;
}

