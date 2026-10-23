
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * UIItemProperty_ItemText(undefined *self,int itemId,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined *puVar8;
  uint uVar9;
  int iVar10;
  longlong *plStack_78;
  undefined *puStack_70;
  longlong lStack_68;
  undefined8 auStack_60 [2];
  longlong **pplStack_50;
  undefined8 *puStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  
  if (DAT_7fff625e329b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    FUN_7fff5f47d450(&DAT_7fff62411ec0);
    FUN_7fff5f47d450(&DAT_7fff6246f180);
    FUN_7fff5f47d450(&DAT_7fff62437e48);
    FUN_7fff5f47d450(&DAT_7fff624606c8);
    FUN_7fff5f47d450(&DAT_7fff623fa248);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff62428c68);
    FUN_7fff5f47d450(&DAT_7fff623fa318);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e329b = '\x01';
  }
  puVar8 = _DAT_7fff623f7f60;
  iVar10 = 0;
  plStack_78 = (longlong *)0x0;
  auStack_60[0] = 0;
  puStack_70 = _DAT_7fff623f7f60;
  plVar4 = (longlong *)UIItemProperty_get_itemTextManager(self,(undefined *)0x0);
  if (plVar4 != (longlong *)0x0) {
    methodInfo = (undefined *)
                 func_0x7fff5f47d0d0(*(undefined8 *)
                                      (*plVar4 +
                                      ((ulonglong)*(ushort *)(_DAT_7fff62411ec0 + 0x50) + 0x14) *
                                      0x10));
    plVar4 = (longlong *)(**(code **)((longlong)methodInfo + 8))(plVar4,itemId,methodInfo);
    if (plVar4 != (longlong *)0x0) {
      lVar5 = (**(code **)(*plVar4 + 0x198))(plVar4,*(undefined8 *)(*plVar4 + 0x1a0));
      if (lVar5 != 0) {
        lStack_68 = lVar5;
        cVar2 = FUN_7fff60e7b970(lVar5,**(undefined8 **)(_DAT_7fff624606c8 + 0xb8),0);
        if (cVar2 != '\0') {
          for (; iVar10 < 10; iVar10 = iVar10 + 1) {
            uVar9 = 0x20;
            if (*(int *)(_DAT_7fff62437e48 + 0xe0) == 0) {
              func_0x7fff5f47d6f0();
            }
            methodInfo = (undefined *)0x0;
            lVar6 = FUN_7fff615682a0(lVar5,_DAT_7fff62428c68,0);
            if (lVar6 == 0) goto LAB_7fff5f9d601d;
            plStack_78 = (longlong *)FUN_7fff61557630(lVar6,0);
            pplStack_50 = &plStack_78;
            puStack_48 = auStack_60;
            uStack_40 = 0;
            uStack_38 = pplStack_50;
            uStack_30 = puStack_48;
            while( true ) {
              if (plStack_78 == (longlong *)0x0) goto LAB_7fff5f9d603b;
              methodInfo = (undefined *)plStack_78;
              cVar2 = FUN_7fff5f252ec0(0,_DAT_7fff62442498);
              if (cVar2 == '\0') break;
              if (plStack_78 == (longlong *)0x0) goto LAB_7fff5f9d6036;
              methodInfo = (undefined *)FUN_7fff5f252ec0(1,_DAT_7fff62442498);
              if ((longlong *)methodInfo == (longlong *)0x0) goto LAB_7fff5f9d6023;
              if ((*(byte *)(*(longlong *)methodInfo + 0x130) < *(byte *)(_DAT_7fff6246f180 + 0x130)
                  ) || (*(longlong *)
                         (*(longlong *)(*(longlong *)methodInfo + 200) + -8 +
                         (ulonglong)*(byte *)(_DAT_7fff6246f180 + 0x130) * 8) != _DAT_7fff6246f180))
              goto LAB_7fff5f9d602e;
              if ((int)*(longlong *)((longlong)methodInfo + 0x10) < (int)uVar9) {
                lVar6 = FUN_7fff61555670(methodInfo,0);
                if (lVar6 == 0) goto LAB_7fff5f9d6029;
                uVar9 = uVar9 + *(int *)(lVar6 + 0x10);
              }
            }
            FUN_7fff5f6ac790(&uStack_38);
            if (lVar5 == 0) goto LAB_7fff5f9d601d;
            if (*(int *)(lVar5 + 0x10) < (int)uVar9) break;
            methodInfo = (undefined *)(ulonglong)uVar9;
            lVar6 = FUN_7fff60e7a440(lVar5,0,methodInfo,0);
            if (lVar6 == 0) goto LAB_7fff5f9d601d;
            iVar3 = FUN_7fff60e77720(lVar6,_DAT_7fff623fa248);
            if (iVar3 < 1) {
              iVar3 = FUN_7fff60e77720(lVar6,_DAT_7fff623fda58);
              if (0 < iVar3) {
                iVar3 = iVar3 + 1;
                uVar7 = FUN_7fff60e7a440(lVar6,0,iVar3,0);
                lVar6 = FUN_7fff60e71970(uVar7,_DAT_7fff623fa248);
              }
            }
            else {
              iVar3 = iVar3 + 1;
              lVar6 = FUN_7fff60e7a440(lVar6,0,iVar3,0);
            }
            if (iVar3 < 0) break;
            puVar8 = (undefined *)FUN_7fff60e71970(puVar8,lVar6);
            puStack_70 = puVar8;
            lVar5 = func_0x7fff60e7a430(lVar5,iVar3);
            lStack_68 = lVar5;
          }
          puVar8 = (undefined *)FUN_7fff60e71650(puVar8,lVar5,_DAT_7fff623fa318,0);
        }
      }
      return puVar8;
    }
  }
LAB_7fff5f9d601d:
  FUN_7fff5f47d660();
LAB_7fff5f9d6023:
  FUN_7fff5f47d660();
LAB_7fff5f9d6029:
  FUN_7fff5f47d660();
LAB_7fff5f9d602e:
  FUN_7fff5f47c810(methodInfo);
LAB_7fff5f9d6036:
  FUN_7fff5f47d660();
LAB_7fff5f9d603b:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  puVar8 = (undefined *)(*pcVar1)();
  return puVar8;
}

