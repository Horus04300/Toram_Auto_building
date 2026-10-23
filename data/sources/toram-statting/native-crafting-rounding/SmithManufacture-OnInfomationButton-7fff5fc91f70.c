
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithManufacture_OnInfomationButton(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined4 uVar4;
  undefined8 uStack_18;
  undefined8 uStack_10;
  
  if (DAT_7fff625e4295 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245cb58);
    DAT_7fff625e4295 = '\x01';
  }
  if (*(longlong *)(self + 200) != 0) {
    FUN_7fff5fc9bff0(*(longlong *)(self + 200),1,0);
    if (*(longlong *)(self + 0xf8) != 0) {
      FUN_7fff5f51e650(*(longlong *)(self + 0xf8),0);
      if (*(longlong *)(self + 0xb0) != 0) {
        lVar3 = FUN_7fff618a1ae0(*(longlong *)(self + 0xb0),0);
        if (lVar3 != 0) {
          cVar2 = FUN_7fff618a4950(lVar3,0);
          if (cVar2 != '\0') {
            if (*(longlong *)(self + 0xb0) == 0) goto LAB_7fff5fc9206e;
            FUN_7fff5f502150(*(longlong *)(self + 0xb0),0,0);
          }
          if (*(longlong *)(self + 0xa8) != 0) {
            lVar3 = FUN_7fff618a1ae0(*(longlong *)(self + 0xa8),0);
            if (lVar3 != 0) {
              cVar2 = FUN_7fff618a4950(lVar3,0);
              if (cVar2 != '\0') {
                if (*(longlong *)(self + 0xa8) == 0) goto LAB_7fff5fc9206e;
                FUN_7fff5f502150(*(longlong *)(self + 0xa8),1,0);
              }
              uVar4 = 0x7fff;
              lVar3 = FUN_7fff60c4bc00(_DAT_7fff6245cb58);
              if (lVar3 != 0) {
                uStack_18 = 0;
                uStack_10 = 0;
                FUN_7fff5f5412c0(lVar3,4,0,_DAT_7fff61b52cfc,0,&uStack_18,0,
                                 CONCAT44(uVar4,_DAT_7fff61b52d1c),0,0);
                return;
              }
            }
          }
        }
      }
    }
  }
LAB_7fff5fc9206e:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

