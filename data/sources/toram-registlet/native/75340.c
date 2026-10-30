
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_BerserkSuppressionBuff_Exemption(undefined *status,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined *self;
  longlong lVar6;
  
  if (status != (undefined *)0x0) {
    self = (undefined *)
           (**(code **)(*(longlong *)status + 0x218))
                     (status,*(undefined8 *)(*(longlong *)status + 0x220));
    if (self != (undefined *)0x0) {
      bVar2 = GemCartBufferManager_ContainsBuffer(self,0x191,(undefined *)0x0);
      if (bVar2 != 0) {
        lVar6 = (**(code **)(*(longlong *)status + 0x1c8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
        if (lVar6 == 0) goto LAB_7ffe9a2e3750;
        cVar3 = FUN_7ffe9a7c6d00(lVar6,0x29);
        if (cVar3 != '\0') {
          lVar6 = (**(code **)(*(longlong *)status + 0x1c8))
                            (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
          if (lVar6 == 0) goto LAB_7ffe9a2e3750;
          cVar3 = FUN_7ffe9a7c6d00(lVar6,0x2e);
          if (cVar3 == '\0') {
            lVar6 = (**(code **)(*(longlong *)status + 0x1b8))
                              (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
            if (lVar6 == 0) goto LAB_7ffe9a2e3750;
            iVar5 = FUN_7ffe9a7fd580(lVar6,0x2e,1);
            if (0 < iVar5) {
              iVar4 = FUN_7ffe9bda4580(0,100);
              return iVar4 < iVar5 * 10;
            }
          }
        }
      }
      return 0;
    }
  }
LAB_7ffe9a2e3750:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

