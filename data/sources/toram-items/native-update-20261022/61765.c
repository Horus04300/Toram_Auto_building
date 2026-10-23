
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
  
  if (DAT_7ffe9cadbb20 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c90af60);
    FUN_7ffe9996d590(&DAT_7ffe9c967908);
    FUN_7ffe9996d590(&DAT_7ffe9c930688);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3b08);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7318);
    FUN_7ffe9996d590(&DAT_7ffe9c922e18);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3bd8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    DAT_7ffe9cadbb20 = '\x01';
  }
  puVar8 = _DAT_7ffe9c8f1820;
  iVar10 = 0;
  plStack_78 = (longlong *)0x0;
  auStack_60[0] = 0;
  puStack_70 = _DAT_7ffe9c8f1820;
  plVar4 = (longlong *)FUN_7ffe99ec9be0(self,0);
  if (plVar4 != (longlong *)0x0) {
    methodInfo = (undefined *)
                 func_0x7ffe9996d210(*(undefined8 *)
                                      (*plVar4 +
                                      ((ulonglong)*(ushort *)(_DAT_7ffe9c90af60 + 0x50) + 0x14) *
                                      0x10));
    plVar4 = (longlong *)(**(code **)((longlong)methodInfo + 8))(plVar4,itemId,methodInfo);
    if (plVar4 != (longlong *)0x0) {
      lVar5 = (**(code **)(*plVar4 + 0x198))(plVar4,*(undefined8 *)(*plVar4 + 0x1a0));
      if (lVar5 != 0) {
        lStack_68 = lVar5;
        cVar2 = FUN_7ffe9b3715b0(lVar5,**(undefined8 **)(_DAT_7ffe9c9590b8 + 0xb8),0);
        if (cVar2 != '\0') {
          for (; iVar10 < 10; iVar10 = iVar10 + 1) {
            uVar9 = 0x20;
            if (*(int *)(_DAT_7ffe9c930688 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            methodInfo = (undefined *)0x0;
            lVar6 = FUN_7ffe9ba5dee0(lVar5,_DAT_7ffe9c922e18,0);
            if (lVar6 == 0) goto LAB_7ffe99ec69cd;
            plStack_78 = (longlong *)FUN_7ffe9ba4d270(lVar6,0);
            pplStack_50 = &plStack_78;
            puStack_48 = auStack_60;
            uStack_40 = 0;
            uStack_38 = pplStack_50;
            uStack_30 = puStack_48;
            while( true ) {
              if (plStack_78 == (longlong *)0x0) goto LAB_7ffe99ec69eb;
              methodInfo = (undefined *)plStack_78;
              cVar2 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
              if (cVar2 == '\0') break;
              if (plStack_78 == (longlong *)0x0) goto LAB_7ffe99ec69e6;
              methodInfo = (undefined *)FUN_7ffe99742ec0(1,_DAT_7ffe9c93ac18);
              if ((longlong *)methodInfo == (longlong *)0x0) goto LAB_7ffe99ec69d3;
              if ((*(byte *)(*(longlong *)methodInfo + 0x130) < *(byte *)(_DAT_7ffe9c967908 + 0x130)
                  ) || (*(longlong *)
                         (*(longlong *)(*(longlong *)methodInfo + 200) + -8 +
                         (ulonglong)*(byte *)(_DAT_7ffe9c967908 + 0x130) * 8) != _DAT_7ffe9c967908))
              goto LAB_7ffe99ec69de;
              if ((int)*(longlong *)((longlong)methodInfo + 0x10) < (int)uVar9) {
                lVar6 = FUN_7ffe9ba4b2b0(methodInfo,0);
                if (lVar6 == 0) goto LAB_7ffe99ec69d9;
                uVar9 = uVar9 + *(int *)(lVar6 + 0x10);
              }
            }
            FUN_7ffe99b9cad0(&uStack_38);
            if (lVar5 == 0) goto LAB_7ffe99ec69cd;
            if (*(int *)(lVar5 + 0x10) < (int)uVar9) break;
            methodInfo = (undefined *)(ulonglong)uVar9;
            lVar6 = FUN_7ffe9b370080(lVar5,0,methodInfo,0);
            if (lVar6 == 0) goto LAB_7ffe99ec69cd;
            iVar3 = FUN_7ffe9b36d360(lVar6,_DAT_7ffe9c8f3b08);
            if (iVar3 < 1) {
              iVar3 = FUN_7ffe9b36d360(lVar6,_DAT_7ffe9c8f7318);
              if (0 < iVar3) {
                iVar3 = iVar3 + 1;
                uVar7 = FUN_7ffe9b370080(lVar6,0,iVar3,0);
                lVar6 = FUN_7ffe9b3675b0(uVar7,_DAT_7ffe9c8f3b08);
              }
            }
            else {
              iVar3 = iVar3 + 1;
              lVar6 = FUN_7ffe9b370080(lVar6,0,iVar3,0);
            }
            if (iVar3 < 0) break;
            puVar8 = (undefined *)FUN_7ffe9b3675b0(puVar8,lVar6);
            puStack_70 = puVar8;
            lVar5 = func_0x7ffe9b370070(lVar5,iVar3);
            lStack_68 = lVar5;
          }
          puVar8 = (undefined *)FUN_7ffe9b367290(puVar8,lVar5,_DAT_7ffe9c8f3bd8,0);
        }
      }
      return puVar8;
    }
  }
LAB_7ffe99ec69cd:
  FUN_7ffe9996d7a0();
LAB_7ffe99ec69d3:
  FUN_7ffe9996d7a0();
LAB_7ffe99ec69d9:
  FUN_7ffe9996d7a0();
LAB_7ffe99ec69de:
  FUN_7ffe9996c950(methodInfo);
LAB_7ffe99ec69e6:
  FUN_7ffe9996d7a0();
LAB_7ffe99ec69eb:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  puVar8 = (undefined *)(*pcVar1)();
  return puVar8;
}

