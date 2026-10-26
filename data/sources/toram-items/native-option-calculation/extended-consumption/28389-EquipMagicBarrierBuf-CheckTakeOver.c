
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte EquipMagicBarrierBuf_CheckTakeOver
               (undefined *self,undefined *playerStatus,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong alStackX_10 [3];
  
  iVar4 = 0;
  alStackX_10[0] = 0;
  if (playerStatus != (undefined *)0x0) {
    lVar6 = (**(code **)(*(longlong *)playerStatus + 0x1c8))
                      (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1d0));
    if (lVar6 != 0) {
      cVar2 = FUN_7ffe9a7cbb30(lVar6,0x44a,alStackX_10,0);
      if (cVar2 != '\0') {
        if (alStackX_10[0] == 0) goto LAB_7ffe9a788f69;
        iVar4 = func_0x7ffe9a7a2140(alStackX_10[0],0x32,0);
      }
      lVar6 = (**(code **)(*(longlong *)playerStatus + 0x1c8))
                        (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1d0));
      if (lVar6 != 0) {
        cVar2 = FUN_7ffe9a7cbb30(lVar6,0x2a8,alStackX_10,0);
        if (cVar2 != '\0') {
          if (alStackX_10[0] == 0) goto LAB_7ffe9a788f69;
          iVar5 = func_0x7ffe9a7a2140(alStackX_10[0],0x34);
          iVar4 = iVar4 + iVar5;
        }
        return 0 < iVar4;
      }
    }
  }
LAB_7ffe9a788f69:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

