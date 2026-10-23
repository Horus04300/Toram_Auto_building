
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ItemTextManager_Initialize(undefined *self,undefined *binary,undefined *methodInfo)

{
  code *pcVar1;
  ulonglong uVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  longlong lVar6;
  ulonglong uVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  int iVar13;
  longlong *plStack_108;
  undefined8 uStack_100;
  longlong **pplStack_f8;
  longlong lStack_f0;
  ulonglong uStack_e8;
  longlong lStack_e0;
  undefined8 uStack_d8;
  longlong *plStack_d0;
  longlong lStack_c8;
  ulonglong uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined *puStack_b0;
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
  
  puStack_b0 = self;
  if (DAT_7ffe9cad9d96 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943bb8);
    FUN_7ffe9996d590(&DAT_7ffe9c8fb6b0);
    FUN_7ffe9996d590(&DAT_7ffe9c906d80);
    FUN_7ffe9996d590(&DAT_7ffe9c906e50);
    FUN_7ffe9996d590(&DAT_7ffe9c906b10);
    FUN_7ffe9996d590(&DAT_7ffe9c907190);
    FUN_7ffe9996d590(&DAT_7ffe9c8fb9f0);
    FUN_7ffe9996d590(&DAT_7ffe9c907260);
    FUN_7ffe9996d590(&DAT_7ffe9c914058);
    FUN_7ffe9996d590(&DAT_7ffe9c9399c8);
    FUN_7ffe9996d590(&DAT_7ffe9c939a88);
    FUN_7ffe9996d590(0x7ffe9c939b50);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c94fd98);
    FUN_7ffe9996d590(0x7ffe9c96b808);
    FUN_7ffe9996d590(&DAT_7ffe9c92d438);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3b08);
    FUN_7ffe9996d590(&DAT_7ffe9c923458);
    FUN_7ffe9996d590(&DAT_7ffe9c93a5a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    DAT_7ffe9cad9d96 = '\x01';
  }
  iVar13 = 0;
  lStack_f0 = 0;
  plStack_108 = (longlong *)0x0;
  plStack_a0 = (longlong *)0x0;
  uStack_98 = 0;
  uStack_90 = 0;
  uStack_88 = 0;
  uStack_80 = 0;
  self[0x11] = 0;
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c914058);
  lStack_e0 = lVar6;
  FUN_7ffe9ad214a0(lVar6,_DAT_7ffe9c906b10);
  lStack_c8 = lVar6;
  uVar7 = func_0x7ffe99940040(_DAT_7ffe9c914058);
  uStack_e8 = uVar7;
  FUN_7ffe9ad214a0(uVar7,_DAT_7ffe9c906b10);
  uStack_c0 = uVar7;
  if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe99a4906b;
  FUN_7ffe9acce330(*(longlong *)(self + 0x18),_DAT_7ffe9c8fb6b0);
  lVar8 = func_0x7ffe99940040(_DAT_7ffe9c969f48);
  FUN_7ffe9b4c0ad0(lVar8,binary,0);
  uStack_d8 = 0;
  plStack_d0 = &lStack_f0;
  lStack_f0 = lVar8;
  plVar9 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c943bb8);
  FUN_7ffe9b4cd430(plVar9,lVar8,0);
  uStack_100 = 0;
  pplStack_f8 = &plStack_108;
  plStack_108 = plVar9;
  if (plVar9 != (longlong *)0x0) {
    iVar4 = (**(code **)(*plVar9 + 0x228))(plVar9,*(undefined8 *)(*plVar9 + 0x230));
LAB_7ffe99a48c53:
    do {
      if (iVar4 <= iVar13) goto LAB_7ffe99a48d6f;
      if (plStack_108 == (longlong *)0x0) {
LAB_7ffe99a4903a:
        FUN_7ffe9996d7a0();
        break;
      }
      uVar5 = (**(code **)(*plStack_108 + 0x228))(plStack_108,*(undefined8 *)(*plStack_108 + 0x230))
      ;
      if (plStack_108 == (longlong *)0x0) {
LAB_7ffe99a49035:
        FUN_7ffe9996d7a0();
        goto LAB_7ffe99a4903a;
      }
      cVar3 = (**(code **)(*plStack_108 + 0x1d8))(plStack_108,*(undefined8 *)(*plStack_108 + 0x1e0))
      ;
      if (plStack_108 == (longlong *)0x0) {
LAB_7ffe99a49030:
        FUN_7ffe9996d7a0();
        goto LAB_7ffe99a49035;
      }
      lVar8 = (**(code **)(*plStack_108 + 0x298))(plStack_108,*(undefined8 *)(*plStack_108 + 0x2a0))
      ;
      if (cVar3 == '\0') {
        if (lVar6 != 0) {
          FUN_7ffe9ad5ed00(lVar6,uVar5,lVar8);
          goto LAB_7ffe99a48d61;
        }
LAB_7ffe99a4902b:
        FUN_7ffe9996d7a0();
        goto LAB_7ffe99a49030;
      }
      if (cVar3 == '\x01') {
        if (lVar8 != 0) {
          lVar8 = FUN_7ffe9b36e700(lVar8,_DAT_7ffe9c93a5a0,_DAT_7ffe9c8f3b08,0);
          if (lVar8 != 0) {
            uVar10 = FUN_7ffe9b36e700(lVar8,_DAT_7ffe9c923458,_DAT_7ffe9c8f3b08,0);
            if (uVar7 != 0) {
              FUN_7ffe9ad5ed00(uVar7,uVar5,uVar10);
              iVar13 = iVar13 + 1;
              goto LAB_7ffe99a48c53;
            }
            FUN_7ffe9996d7a0();
          }
          FUN_7ffe9996d7a0();
        }
        FUN_7ffe9996d7a0();
        goto LAB_7ffe99a4902b;
      }
LAB_7ffe99a48d61:
      iVar13 = iVar13 + 1;
    } while( true );
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe99a4904b:
  FUN_7ffe9996d7a0();
LAB_7ffe99a49050:
  FUN_7ffe9996d7a0();
LAB_7ffe99a49055:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  goto LAB_7ffe99a49060;
LAB_7ffe99a48d6f:
  if (plStack_108 != (longlong *)0x0) {
    FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
  }
  if (lVar6 != 0) {
    FUN_7ffe9accf860(&plStack_58,lVar6,_DAT_7ffe9c906e50);
    plStack_a0 = plStack_58;
    uStack_98 = uStack_50;
    uStack_90 = uStack_48;
    uStack_88 = uStack_40;
    uStack_80 = uStack_38;
    uStack_100 = 0;
    pplStack_f8 = &plStack_a0;
    while( true ) {
      do {
        cVar3 = FUN_7ffe9ae3f410(&plStack_a0,_DAT_7ffe9c939a88);
        if (cVar3 == '\0') {
          func_0x7ffe999c3920(&plStack_a0,_DAT_7ffe9c9399c8);
          if (*plStack_d0 != 0) {
            FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
          }
          self[0x10] = 1;
          self[0x12] = 0;
          return;
        }
        uStack_c0 = uStack_90;
        uStack_b8 = (undefined4)uStack_88;
        uStack_b4 = uStack_88._4_4_;
        if (*(longlong *)(self + 0x20) == 0) goto LAB_7ffe99a49055;
        cVar3 = FUN_7ffe9afc8630(*(longlong *)(self + 0x20),uStack_90 & 0xffffffff,_DAT_7ffe9c92d438
                                );
        uVar2 = uStack_c0;
        uVar10 = _DAT_7ffe9c8f1820;
      } while (cVar3 != '\0');
      if (uVar7 == 0) break;
      cVar3 = FUN_7ffe9ad24db0(uVar7,uStack_c0 & 0xffffffff,_DAT_7ffe9c906d80);
      if (cVar3 == '\0') {
        lVar8 = *(longlong *)(self + 0x18);
      }
      else {
        uVar10 = FUN_7ffe9ad356e0(uVar7,uVar2 & 0xffffffff,_DAT_7ffe9c907190);
        lVar8 = *(longlong *)(puStack_b0 + 0x18);
      }
      uVar11 = FUN_7ffe9ad356e0(lVar6,uVar2 & 0xffffffff,_DAT_7ffe9c907190);
      uVar12 = func_0x7ffe99940040(_DAT_7ffe9c94fd98);
      FUN_7ffe99a479e0(uVar12,uVar11,uVar10,0);
      if (lVar8 == 0) goto LAB_7ffe99a4904b;
      FUN_7ffe9ad5ed00(lVar8,uVar2 & 0xffffffff,uVar12);
      lVar6 = lStack_e0;
      uVar7 = uStack_e8;
    }
    goto LAB_7ffe99a49050;
  }
LAB_7ffe99a49060:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe99a4906b:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

