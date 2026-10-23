
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobPropertyCriticalResist_GetCriticalResist
              (undefined *self,undefined *mobAction,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  int iVar7;
  float fVar8;
  longlong *plStackX_8;
  
  if (DAT_7fff625e4ee3 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62449a30);
    FUN_7fff5f47d450(&DAT_7fff62449af8);
    FUN_7fff5f47d450(&DAT_7fff624700a0);
    FUN_7fff5f47d450(&DAT_7fff62479db0);
    DAT_7fff625e4ee3 = '\x01';
  }
  iVar4 = 0;
  plStackX_8 = (longlong *)0x0;
  if (DAT_7fff625e4ee0 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6240d7c8);
    DAT_7fff625e4ee0 = '\x01';
  }
  lVar5 = FUN_7fff6068f640(*(undefined8 *)(self + 0x10),_DAT_7fff6240d7c8);
  if (lVar5 == 0) {
    return 0;
  }
  lVar6 = *(longlong *)(lVar5 + 0x18);
  if (lVar6 != 0) {
    if (*(int *)(lVar6 + 0x18) == 0) {
LAB_7fff5fe83b14:
      FUN_7fff5f47d650();
      pcVar1 = (code *)swi(3);
      iVar4 = (*pcVar1)();
      return iVar4;
    }
    iVar7 = *(int *)(lVar6 + 0x20);
    if ((mobAction != (undefined *)0x0) &&
       (lVar6 = FUN_7fff5f252ec0(10,_DAT_7fff62479db0,mobAction), lVar6 != 0)) {
      cVar2 = FUN_7fff5ffe5620(lVar6,0x20);
      fVar8 = _DAT_7fff61b52b4c;
      if ((cVar2 != '\0') && (0 < iVar7)) {
        cVar2 = FUN_7fff5f252ec0(0x11,_DAT_7fff62479db0,mobAction);
        if (cVar2 != '\0') {
          fVar8 = _DAT_7fff61b52b40;
        }
        lVar5 = *(longlong *)(lVar5 + 0x18);
        if (lVar5 == 0) goto LAB_7fff5fe83b1a;
        if (*(int *)(lVar5 + 0x18) == 0) goto LAB_7fff5fe83b14;
        iVar3 = FUN_7fff5f553d50((float)*(int *)(lVar5 + 0x20) * fVar8,0);
        if (0x19 < iVar3) {
          iVar3 = 0x19;
        }
        iVar7 = iVar7 - iVar3;
      }
      lVar5 = FUN_7fff5f252ec0(0xb,_DAT_7fff62479db0,mobAction);
      if (lVar5 != 0) {
        cVar2 = FUN_7fff5fdb76c0(lVar5,0xb,&plStackX_8);
        if (cVar2 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7fff5fe83b1a;
          if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7fff62449af8 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStackX_8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7fff62449af8 + 0x130) * 8) != _DAT_7fff62449af8)) ||
             (plStackX_8 == (longlong *)0x0)) {
            FUN_7fff5f47c810(plStackX_8);
            pcVar1 = (code *)swi(3);
            iVar4 = (*pcVar1)();
            return iVar4;
          }
          iVar4 = func_0x7fff5fdaea50(plStackX_8,0);
        }
        lVar5 = FUN_7fff5f252ec0(0xb,_DAT_7fff62479db0,mobAction);
        if (lVar5 != 0) {
          cVar2 = FUN_7fff5fdb76c0(lVar5,0xc,&plStackX_8);
          if (cVar2 != '\0') {
            if (plStackX_8 == (longlong *)0x0) goto LAB_7fff5fe83b1a;
            if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7fff62449a30 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStackX_8 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7fff62449a30 + 0x130) * 8) != _DAT_7fff62449a30)) ||
               (plStackX_8 == (longlong *)0x0)) {
              FUN_7fff5f47c810(plStackX_8);
              pcVar1 = (code *)swi(3);
              iVar4 = (*pcVar1)();
              return iVar4;
            }
            iVar3 = func_0x7fff5fdaea50(plStackX_8,0);
            iVar4 = iVar4 + iVar3;
          }
          if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          iVar4 = func_0x7fff61010f30(0,iVar7 - iVar4,0);
          return iVar4;
        }
      }
    }
  }
LAB_7fff5fe83b1a:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar4 = (*pcVar1)();
  return iVar4;
}

