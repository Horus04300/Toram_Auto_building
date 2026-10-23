
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithManufacture_SelectElement(undefined *self,int index,undefined *methodInfo)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  code *pcVar4;
  char cVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined8 *puVar8;
  longlong *methodInfo_00;
  longlong lVar9;
  uint uVar10;
  undefined4 auStackX_10 [2];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  float fStack_2c;
  
  if (DAT_7fff625e4290 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62473318);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62450e50);
    FUN_7fff5f47d450(&DAT_7fff623fd630);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff624445f8);
    DAT_7fff625e4290 = '\x01';
  }
  uVar1 = *(undefined4 *)(self + 0x160);
  uVar2 = *(undefined4 *)(self + 0x164);
  if (DAT_7fff625e42a0 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6246f760);
    FUN_7fff5f47d450(&DAT_7fff6246f828);
    FUN_7fff5f47d450(&DAT_7fff62417738);
    FUN_7fff5f47d450(&DAT_7fff6246f8f8);
    FUN_7fff5f47d450(&DAT_7fff62417ce0);
    FUN_7fff5f47d450(&DAT_7fff6241d5e0);
    DAT_7fff625e42a0 = '\x01';
  }
  if (*(longlong *)(self + 0x180) != 0) {
    cVar5 = FUN_7fff6082f170(*(longlong *)(self + 0x180),*(undefined4 *)(self + 0x160),
                             _DAT_7fff6246f828);
    if (cVar5 == '\0') {
      lVar7 = *(longlong *)(self + 0x180);
      uVar3 = *(undefined4 *)(self + 0x160);
      uVar6 = func_0x7fff5f44ff00(_DAT_7fff6241d5e0);
      FUN_7fff6082b860(uVar6,_DAT_7fff62417738);
      if (lVar7 == 0) goto LAB_7fff5fc93d69;
      FUN_7fff60857660(lVar7,uVar3,uVar6,_DAT_7fff6246f760);
    }
    if (((*(longlong *)(self + 0x70) != 0) &&
        (lVar7 = *(longlong *)(*(longlong *)(self + 0x70) + 0x20), lVar7 != 0)) &&
       (lVar7 = FUN_7fff618a1b90(lVar7,0), lVar7 != 0)) {
      puVar8 = (undefined8 *)FUN_7fff618c8560(&uStack_38,lVar7,0);
      uVar6 = *puVar8;
      uVar3 = *(undefined4 *)(puVar8 + 1);
      if (*(longlong *)(self + 0x180) != 0) {
        lVar7 = FUN_7fff6083faa0(*(longlong *)(self + 0x180),uVar1,_DAT_7fff6246f8f8);
        if (lVar7 != 0) {
          uStack_48 = (undefined4)uVar6;
          uStack_44 = (undefined4)((ulonglong)uVar6 >> 0x20);
          uStack_38 = uStack_48;
          uStack_34 = uStack_44;
          uStack_30 = uVar3;
          fStack_2c = (float)index;
          FUN_7fff60869040(lVar7,uVar2,&uStack_38,_DAT_7fff62417ce0);
          if (DAT_7fff625e4292 == '\0') {
            FUN_7fff5f47d450(&DAT_7fff6242b730);
            DAT_7fff625e4292 = '\x01';
          }
          lVar7 = func_0x7fff5f44ff00(_DAT_7fff6242b730);
          FUN_7fff5f4eb770(lVar7,0,0);
          if (lVar7 != 0) {
            *(undefined **)(lVar7 + 0x28) = self;
            thunk_FUN_7fff5f491fd0();
            *(int *)(lVar7 + 0x30) = index;
            *(undefined4 *)(lVar7 + 0x20) = 0;
            FUN_7fff618a87c0(self,lVar7,0);
            lVar7 = *(longlong *)(self + 0x150);
            uVar10 = 0;
            uVar1 = *(undefined4 *)(self + 0x160);
            *(int *)(self + 0x168) = index;
            while (((lVar7 != 0 &&
                    (lVar7 = FUN_7fff60a94f50(lVar7,uVar1,_DAT_7fff623fd630), lVar7 != 0)) &&
                   ((lVar7 = FUN_7fff6083faa0(lVar7,*(undefined4 *)(self + 0x164),_DAT_7fff62473318)
                    , lVar7 != 0 &&
                    ((lVar7 = FUN_7fff60a94f50(lVar7,*(undefined4 *)(self + 0x168),_DAT_7fff62450e50
                                              ), lVar7 != 0 && (*(longlong *)(lVar7 + 0x28) != 0))))
                   ))) {
              if (*(int *)(*(longlong *)(lVar7 + 0x28) + 0x18) <= (int)uVar10) {
                return;
              }
              methodInfo_00 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
              if ((((*(longlong *)(self + 0x150) == 0) ||
                   (lVar7 = FUN_7fff60a94f50(*(longlong *)(self + 0x150),
                                             *(undefined4 *)(self + 0x160),_DAT_7fff623fd630),
                   lVar7 == 0)) ||
                  (lVar7 = FUN_7fff6083faa0(lVar7,*(undefined4 *)(self + 0x164),_DAT_7fff62473318),
                  lVar7 == 0)) ||
                 ((lVar7 = FUN_7fff60a94f50(lVar7,*(undefined4 *)(self + 0x168),_DAT_7fff62450e50),
                  lVar7 == 0 || (lVar7 = *(longlong *)(lVar7 + 0x28), lVar7 == 0))))
              goto LAB_7fff5fc93d85;
              if (*(uint *)(lVar7 + 0x18) <= uVar10) {
LAB_7fff5fc93d7f:
                FUN_7fff5f47d650();
                pcVar4 = (code *)swi(3);
                (*pcVar4)();
                return;
              }
              lVar7 = *(longlong *)(lVar7 + 0x20 + (longlong)(int)uVar10 * 8);
              if (lVar7 == 0) {
LAB_7fff5fc93d85:
                FUN_7fff5f47d660();
                pcVar4 = (code *)swi(3);
                (*pcVar4)();
                return;
              }
              auStackX_10[0] = *(undefined4 *)(lVar7 + 0x14);
              lVar7 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,auStackX_10);
              if (methodInfo_00 == (longlong *)0x0) goto LAB_7fff5fc93d85;
              if ((lVar7 != 0) &&
                 (lVar9 = func_0x7fff5f47c7e0(lVar7,*(undefined8 *)(*methodInfo_00 + 0x40)),
                 lVar9 == 0)) {
                uVar6 = func_0x7fff5f47d0b0();
                FUN_7fff5f47d620(uVar6,0);
                pcVar4 = (code *)swi(3);
                (*pcVar4)();
                return;
              }
              if ((int)methodInfo_00[3] == 0) goto LAB_7fff5fc93d7f;
              methodInfo_00[4] = lVar7;
              thunk_FUN_7fff5f491fd0();
              SmithManufacture_Update(_DAT_7fff624445f8,(undefined *)methodInfo_00);
              lVar7 = *(longlong *)(self + 0x150);
              uVar10 = uVar10 + 1;
              uVar1 = *(undefined4 *)(self + 0x160);
            }
          }
        }
      }
    }
  }
LAB_7fff5fc93d69:
  FUN_7fff5f47d660();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

