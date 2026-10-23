
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
  
  if (DAT_7ffe9cadd78b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9420e8);
    FUN_7ffe9996d590(&DAT_7ffe9c9421b0);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    DAT_7ffe9cadd78b = '\x01';
  }
  iVar4 = 0;
  plStackX_8 = (longlong *)0x0;
  if (DAT_7ffe9cadd788 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906868);
    DAT_7ffe9cadd788 = '\x01';
  }
  lVar5 = FUN_7ffe9ab85290(*(undefined8 *)(self + 0x10),_DAT_7ffe9c906868);
  if (lVar5 == 0) {
    return 0;
  }
  lVar6 = *(longlong *)(lVar5 + 0x18);
  if (lVar6 != 0) {
    if (*(int *)(lVar6 + 0x18) == 0) {
LAB_7ffe9a378f64:
      FUN_7ffe9996d790();
      pcVar1 = (code *)swi(3);
      iVar4 = (*pcVar1)();
      return iVar4;
    }
    iVar7 = *(int *)(lVar6 + 0x20);
    if ((mobAction != (undefined *)0x0) &&
       (lVar6 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction), lVar6 != 0)) {
      cVar2 = FUN_7ffe9a4daa60(lVar6,0x20);
      fVar8 = _DAT_7ffe9c049b4c;
      if ((cVar2 != '\0') && (0 < iVar7)) {
        cVar2 = FUN_7ffe99742ec0(0x11,_DAT_7ffe9c9724e0,mobAction);
        if (cVar2 != '\0') {
          fVar8 = _DAT_7ffe9c049b40;
        }
        lVar5 = *(longlong *)(lVar5 + 0x18);
        if (lVar5 == 0) goto LAB_7ffe9a378f6a;
        if (*(int *)(lVar5 + 0x18) == 0) goto LAB_7ffe9a378f64;
        iVar3 = FUN_7ffe99a43d50((float)*(int *)(lVar5 + 0x20) * fVar8,0);
        if (0x19 < iVar3) {
          iVar3 = 0x19;
        }
        iVar7 = iVar7 - iVar3;
      }
      lVar5 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
      if (lVar5 != 0) {
        cVar2 = FUN_7ffe9a2ac880(lVar5,0xb,&plStackX_8);
        if (cVar2 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a378f6a;
          if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c9421b0 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStackX_8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c9421b0 + 0x130) * 8) != _DAT_7ffe9c9421b0)) ||
             (plStackX_8 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStackX_8);
            pcVar1 = (code *)swi(3);
            iVar4 = (*pcVar1)();
            return iVar4;
          }
          iVar4 = func_0x7ffe9a2a3c10(plStackX_8,0);
        }
        lVar5 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
        if (lVar5 != 0) {
          cVar2 = FUN_7ffe9a2ac880(lVar5,0xc,&plStackX_8);
          if (cVar2 != '\0') {
            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a378f6a;
            if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c9420e8 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStackX_8 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c9420e8 + 0x130) * 8) != _DAT_7ffe9c9420e8)) ||
               (plStackX_8 == (longlong *)0x0)) {
              FUN_7ffe9996c950(plStackX_8);
              pcVar1 = (code *)swi(3);
              iVar4 = (*pcVar1)();
              return iVar4;
            }
            iVar3 = func_0x7ffe9a2a3c10(plStackX_8,0);
            iVar4 = iVar4 + iVar3;
          }
          if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          iVar4 = func_0x7ffe9b506b70(0,iVar7 - iVar4,0);
          return iVar4;
        }
      }
    }
  }
LAB_7ffe9a378f6a:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar4 = (*pcVar1)();
  return iVar4;
}

