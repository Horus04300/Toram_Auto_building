
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EquipMagicBarrierBuf_GetBarrierValue(undefined *self,undefined *status,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  int iVar5;
  longlong lStackX_8;
  
  iVar5 = *(int *)(self + 0x20);
  lStackX_8 = 0;
  if (status != (undefined *)0x0) {
    lVar4 = (**(code **)(*(longlong *)status + 0x1c8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
    if (lVar4 != 0) {
      cVar2 = FUN_7ffe9a7cbb30(lVar4,0x44a,&lStackX_8,0);
      if (cVar2 != '\0') {
        if (lStackX_8 == 0) goto LAB_7ffe9a78903b;
        iVar3 = func_0x7ffe9a7a2140(lStackX_8,0x32);
        iVar5 = iVar5 + iVar3;
      }
      lVar4 = (**(code **)(*(longlong *)status + 0x1c8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
      if (lVar4 != 0) {
        cVar2 = FUN_7ffe9a7cbb30(lVar4,0x2a8,&lStackX_8,0);
        if (cVar2 != '\0') {
          if (lStackX_8 == 0) goto LAB_7ffe9a78903b;
          iVar3 = func_0x7ffe9a7a2140(lStackX_8,0x34);
          iVar5 = iVar5 + iVar3;
        }
        return iVar5;
      }
    }
  }
LAB_7ffe9a78903b:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

