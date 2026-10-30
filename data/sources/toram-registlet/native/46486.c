
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RegistletTextManager_Initialize(undefined *self,undefined *binary,undefined *methodInfo)

{
  code *pcVar1;
  ulonglong uVar2;
  char cVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined8 uVar10;
  undefined *description;
  undefined *name;
  undefined *self_00;
  int iVar11;
  undefined4 auStackX_20 [2];
  longlong *plStack_118;
  undefined8 uStack_110;
  longlong **pplStack_108;
  int iStack_100;
  longlong lStack_f8;
  longlong lStack_f0;
  longlong lStack_e8;
  ulonglong uStack_e0;
  undefined8 uStack_d8;
  longlong *plStack_d0;
  ulonglong uStack_c8;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  longlong lStack_b8;
  longlong lStack_b0;
  longlong *plStack_a0;
  undefined8 uStack_98;
  ulonglong uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  longlong *plStack_58;
  undefined8 uStack_50;
  ulonglong uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  if (DAT_7ffe9cad9de1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943bb8);
    FUN_7ffe9996d590(&DAT_7ffe9c903980);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9a40);
    FUN_7ffe9996d590(&DAT_7ffe9c906d80);
    FUN_7ffe9996d590(&DAT_7ffe9c906e50);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9700);
    FUN_7ffe9996d590(&DAT_7ffe9c906b10);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9f20);
    FUN_7ffe9996d590(&DAT_7ffe9c907190);
    FUN_7ffe9996d590(&DAT_7ffe9c8fa190);
    FUN_7ffe9996d590(&DAT_7ffe9c903cc0);
    FUN_7ffe9996d590(&DAT_7ffe9c907260);
    FUN_7ffe9996d590(&DAT_7ffe9c914058);
    FUN_7ffe9996d590(&DAT_7ffe9c911d68);
    FUN_7ffe9996d590(&DAT_7ffe9c9399c8);
    FUN_7ffe9996d590(&DAT_7ffe9c939a88);
    FUN_7ffe9996d590(0x7ffe9c939b50);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(0x7ffe9c96b808);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    FUN_7ffe9996d590(&DAT_7ffe9c932090);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3b08);
    FUN_7ffe9996d590(&DAT_7ffe9c93a5a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    DAT_7ffe9cad9de1 = '\x01';
  }
  iVar11 = 0;
  lStack_f8 = 0;
  plStack_118 = (longlong *)0x0;
  auStackX_20[0] = 0;
  plStack_a0 = (longlong *)0x0;
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_80 = 0;
  self[0x11] = 0;
  lVar5 = func_0x7ffe99940040(_DAT_7ffe9c914058);
  lStack_f0 = lVar5;
  FUN_7ffe9ad214a0(lVar5,_DAT_7ffe9c906b10);
  lStack_b8 = lVar5;
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c914058);
  lStack_e8 = lVar6;
  FUN_7ffe9ad214a0(lVar6,_DAT_7ffe9c906b10);
  lStack_b0 = lVar6;
  uVar7 = func_0x7ffe99940040(_DAT_7ffe9c911d68);
  uStack_e0 = uVar7;
  FUN_7ffe9ad214a0(uVar7,_DAT_7ffe9c8f9700);
  uStack_c8 = uVar7;
  if (*(longlong *)(self + 0x18) != 0) {
    FUN_7ffe9acce330(*(longlong *)(self + 0x18),_DAT_7ffe9c903980);
    lVar8 = func_0x7ffe99940040(_DAT_7ffe9c969f48);
    FUN_7ffe9b4c0ad0(lVar8,binary,0);
    uStack_d8 = 0;
    plStack_d0 = &lStack_f8;
    lStack_f8 = lVar8;
    plVar9 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c943bb8);
    FUN_7ffe9b4cd430(plVar9,lVar8,0);
    uStack_110 = 0;
    pplStack_108 = &plStack_118;
    plStack_118 = plVar9;
    if (plVar9 == (longlong *)0x0) {
LAB_7ffe99a5318c:
      FUN_7ffe9996d7a0();
      FUN_7ffe998fa550();
LAB_7ffe99a53198:
      FUN_7ffe9996d7a0();
LAB_7ffe99a5319d:
      FUN_7ffe9996d7a0();
    }
    else {
      iStack_100 = (**(code **)(*plVar9 + 0x228))(plVar9,*(undefined8 *)(*plVar9 + 0x230));
LAB_7ffe99a52d44:
      if (iVar11 < iStack_100) {
        if (plStack_118 == (longlong *)0x0) {
LAB_7ffe99a53187:
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99a5318c;
        }
        uVar4 = (**(code **)(*plStack_118 + 0x228))
                          (plStack_118,*(undefined8 *)(*plStack_118 + 0x230));
        if (plStack_118 == (longlong *)0x0) {
LAB_7ffe99a53182:
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99a53187;
        }
        cVar3 = (**(code **)(*plStack_118 + 0x1d8))
                          (plStack_118,*(undefined8 *)(*plStack_118 + 0x1e0));
        if (plStack_118 == (longlong *)0x0) {
LAB_7ffe99a5317d:
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99a53182;
        }
        lVar8 = (**(code **)(*plStack_118 + 0x298))
                          (plStack_118,*(undefined8 *)(*plStack_118 + 0x2a0));
        if (cVar3 == '\0') {
          if (lVar5 != 0) {
            FUN_7ffe9ad5ed00(lVar5,uVar4,lVar8,_DAT_7ffe9c907260);
            goto LAB_7ffe99a52e8a;
          }
LAB_7ffe99a53178:
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99a5317d;
        }
        if (cVar3 == '\x01') {
          if (lVar8 == 0) {
LAB_7ffe99a53173:
            FUN_7ffe9996d7a0();
            goto LAB_7ffe99a53178;
          }
          uVar10 = FUN_7ffe9b36e700(lVar8,_DAT_7ffe9c93a5a0,_DAT_7ffe9c8f3b08,0);
          if (lVar6 == 0) goto LAB_7ffe99a5316e;
          FUN_7ffe9ad5ed00(lVar6,uVar4,uVar10);
          iVar11 = iVar11 + 1;
        }
        else {
          if (cVar3 == '\x02') {
            auStackX_20[0] = 0xffffffff;
            cVar3 = FUN_7ffe9b504890(lVar8,auStackX_20,0);
            if (cVar3 != '\0') {
              if (uVar7 == 0) {
                FUN_7ffe9996d7a0();
LAB_7ffe99a5316e:
                FUN_7ffe9996d7a0();
                goto LAB_7ffe99a53173;
              }
              FUN_7ffe9ad358f0(uVar7,uVar4);
              iVar11 = iVar11 + 1;
              goto LAB_7ffe99a52d44;
            }
          }
LAB_7ffe99a52e8a:
          iVar11 = iVar11 + 1;
        }
        goto LAB_7ffe99a52d44;
      }
      if (plStack_118 != (longlong *)0x0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
      if (lVar5 == 0) goto LAB_7ffe99a531b3;
      FUN_7ffe9accf860(&plStack_58,lVar5,_DAT_7ffe9c906e50);
      plStack_a0 = plStack_58;
      uStack_98 = uStack_50;
      uStack_90 = uStack_48;
      uStack_88 = uStack_40;
      uStack_80 = uStack_38;
      uStack_110 = 0;
      pplStack_108 = &plStack_a0;
      while( true ) {
        cVar3 = FUN_7ffe9ae3f410(&plStack_a0,_DAT_7ffe9c939a88);
        description = _DAT_7ffe9c8f1820;
        if (cVar3 == '\0') {
          func_0x7ffe999c3920(&plStack_a0,_DAT_7ffe9c9399c8);
          if (*plStack_d0 != 0) {
            FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
          }
          self[0x10] = 1;
          self[0x12] = 0;
          return;
        }
        uStack_c8 = uStack_90;
        uStack_c0 = (undefined4)uStack_88;
        uStack_bc = uStack_88._4_4_;
        if (lVar6 == 0) break;
        cVar3 = FUN_7ffe9ad24db0(lVar6,uStack_90 & 0xffffffff,_DAT_7ffe9c906d80);
        uVar2 = uStack_c8;
        if (cVar3 != '\0') {
          description = (undefined *)
                        FUN_7ffe9ad356e0(lVar6,uStack_c8 & 0xffffffff,_DAT_7ffe9c907190);
        }
        iVar11 = -1;
        if (uVar7 == 0) goto LAB_7ffe99a5319d;
        cVar3 = FUN_7ffe9ad10f70(uVar7,uVar2 & 0xffffffff,_DAT_7ffe9c8f9a40);
        if (cVar3 != '\0') {
          iVar11 = FUN_7ffe9ad35820(uVar7,uVar2 & 0xffffffff,_DAT_7ffe9c8f9f20);
        }
        lVar6 = *(longlong *)(self + 0x18);
        name = (undefined *)FUN_7ffe9ad356e0(lStack_f0,uVar2 & 0xffffffff,_DAT_7ffe9c907190);
        self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c932090);
        RegistletTextManagerData__ctor(self_00,name,description,iVar11,(undefined *)0x0);
        if (lVar6 == 0) goto LAB_7ffe99a53198;
        FUN_7ffe9ad5ed00(lVar6,uVar2 & 0xffffffff,self_00,_DAT_7ffe9c903cc0);
        uVar7 = uStack_e0;
        lVar6 = lStack_e8;
      }
    }
    FUN_7ffe9996d7a0();
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe99a531b3:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

