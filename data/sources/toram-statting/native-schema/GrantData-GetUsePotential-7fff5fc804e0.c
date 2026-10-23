
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GrantData_GetUsePotential
              (undefined *key,int itemUuid,undefined *playerData,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined8 uStack_80;
  undefined8 *puStack_78;
  longlong lStack_70;
  int iStack_5c;
  undefined8 uStack_58;
  undefined8 *puStack_50;
  longlong lStack_48;
  longlong lStack_40;
  
  if (DAT_7fff625e424b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62462c40);
    FUN_7fff5f47d450(&DAT_7fff62476088);
    FUN_7fff5f47d450(&DAT_7fff62476158);
    FUN_7fff5f47d450(0x7fff62476228);
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    FUN_7fff5f47d450(&DAT_7fff62400550);
    FUN_7fff5f47d450(&DAT_7fff624006f0);
    FUN_7fff5f47d450(&DAT_7fff62400480);
    FUN_7fff5f47d450(&DAT_7fff624692f0);
    FUN_7fff5f47d450(&DAT_7fff624463f0);
    FUN_7fff5f47d450(0x7fff624464b0);
    FUN_7fff5f47d450(0x7fff62446578);
    FUN_7fff5f47d450(&DAT_7fff62407b50);
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    DAT_7fff625e424b = '\x01';
  }
  uStack_58 = 0;
  puStack_50 = (undefined8 *)0x0;
  lStack_48 = 0;
  if ((playerData != (undefined *)0x0) && (lVar6 = FUN_7fff5ff8a8a0(playerData,0), lVar6 != 0)) {
    lVar6 = FUN_7fff6007b880(lVar6,itemUuid,0);
    if (lVar6 == 0) {
      return 9999;
    }
    lStack_40 = lVar6;
    if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff62420f50);
    }
    lVar7 = *(longlong *)(*(longlong *)(_DAT_7fff62420f50 + 0xb8) + 8);
    if (lVar7 != 0) {
      FUN_7fff6088c670(&uStack_80,lVar7,(ulonglong)key & 0xffffffff,_DAT_7fff62462c40);
      lVar7 = *(longlong *)(*(longlong *)(_DAT_7fff62420f50 + 0xb8) + 8);
      if (lVar7 != 0) {
        FUN_7fff6088c670(&uStack_80,lVar7,(ulonglong)key & 0xffffffff,_DAT_7fff62462c40);
        iVar5 = (int)uStack_80;
        lVar7 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
        if (lVar7 != 0) {
          lVar7 = FUN_7fff600847d0(lVar7,*(undefined4 *)(lVar6 + 0x34),0);
          if (lVar7 != 0) {
            lVar8 = func_0x7fff5f44ff00(_DAT_7fff624692f0);
            FUN_7fff60a943d0(lVar8,_DAT_7fff62400480);
            uVar3 = FUN_7fff5fd06df0(lVar7,0);
            uVar4 = FUN_7fff5fd06fd0(lVar7,0);
            uStack_80 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uStack_80,uVar3,uVar4,_DAT_7fff624463f0);
            if (lVar8 == 0) goto LAB_7fff5fc80b8c;
            FUN_7fff5f253100(lVar8,uStack_80,_DAT_7fff62400550);
            uVar3 = FUN_7fff5fd06e20(lVar7,0);
            uVar4 = FUN_7fff5fd07000(lVar7,0);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uVar9,uVar3,uVar4,_DAT_7fff624463f0);
            FUN_7fff5f253100(lVar8,uVar9,_DAT_7fff62400550);
            uVar3 = FUN_7fff5fd06e50(lVar7,0);
            uVar4 = FUN_7fff5fd07030(lVar7,0);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uVar9,uVar3,uVar4,_DAT_7fff624463f0);
            FUN_7fff5f253100(lVar8,uVar9,_DAT_7fff62400550);
            uVar3 = FUN_7fff5fd06e80(lVar7,0);
            uVar4 = FUN_7fff5fd07060(lVar7,0);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uVar9,uVar3,uVar4,_DAT_7fff624463f0);
            FUN_7fff5f253100(lVar8,uVar9,_DAT_7fff62400550);
            uVar3 = FUN_7fff5fd06eb0(lVar7,0);
            uVar4 = FUN_7fff5fd07090(lVar7,0);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uVar9,uVar3,uVar4,_DAT_7fff624463f0);
            FUN_7fff5f253100(lVar8,uVar9,_DAT_7fff62400550);
            uVar3 = FUN_7fff5fd06ee0(lVar7,0);
            uVar4 = FUN_7fff5fd070c0(lVar7,0);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uVar9,uVar3,uVar4,_DAT_7fff624463f0);
            FUN_7fff5f253100(lVar8,uVar9,_DAT_7fff62400550);
            uVar3 = FUN_7fff5fd06f10(lVar7,0);
            uVar4 = FUN_7fff5fd070f0(lVar7,0);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uVar9,uVar3,uVar4,_DAT_7fff624463f0);
            FUN_7fff5f253100(lVar8,uVar9,_DAT_7fff62400550);
            uVar3 = FUN_7fff5fd06f40(lVar7,0);
            uVar4 = FUN_7fff5fd07120(lVar7,0);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uVar9,uVar3,uVar4,_DAT_7fff624463f0);
            FUN_7fff5f253100(lVar8,uVar9,_DAT_7fff62400550);
            uVar3 = FUN_7fff5fd06f70(lVar7,0);
            uVar4 = FUN_7fff5fd07150(lVar7,0);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uVar9,uVar3,uVar4,_DAT_7fff624463f0);
            FUN_7fff5f253100(lVar8,uVar9,_DAT_7fff62400550);
            uVar3 = FUN_7fff5fd06dc0(lVar7,0);
            uVar4 = FUN_7fff5fd06fa0(lVar7,0);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62407b50);
            FUN_7fff60bd19e0(uVar9,uVar3,uVar4,_DAT_7fff624463f0);
            FUN_7fff5f253100(lVar8,uVar9,_DAT_7fff62400550);
            FUN_7fff60a8da60(&uStack_80,lVar8,_DAT_7fff624006f0);
            uStack_58 = uStack_80;
            puStack_50 = puStack_78;
            lStack_48 = lStack_70;
            uStack_80 = 0;
            puStack_78 = &uStack_58;
            while (cVar2 = FUN_7fff60933290(&uStack_58,_DAT_7fff62476158), cVar2 != '\0') {
              if (lStack_48 == 0) goto LAB_7fff5fc80b92;
              if ((*(short *)(lStack_48 + 0x10) == 0x41) &&
                 (*(short *)(lStack_48 + 0x12) == (short)((ulonglong)key & 0xffffffff))) {
                iVar5 = iVar5 / 10;
              }
            }
            func_0x7fff5f4d3920(&uStack_58,_DAT_7fff62476088);
          }
          cVar2 = func_0x7fff5fc6d340(*(undefined4 *)(lVar6 + 0x38),0);
          if ((cVar2 == '\0') || (iStack_5c != 1)) {
            cVar2 = FUN_7fff5fc6d540(*(undefined4 *)(lVar6 + 0x34),0);
            if (cVar2 == '\0') {
              return iVar5;
            }
            if (iStack_5c != 2) {
              return iVar5;
            }
          }
          return iVar5 * 2;
        }
      }
    }
  }
LAB_7fff5fc80b8c:
  FUN_7fff5f47d660();
LAB_7fff5fc80b92:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

