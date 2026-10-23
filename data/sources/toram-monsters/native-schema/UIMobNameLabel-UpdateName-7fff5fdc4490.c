
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIMobNameLabel_UpdateName(undefined *self,undefined *traceObject,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined4 auStackX_10 [2];
  
  if (DAT_7fff625e496f == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62469570);
    FUN_7fff5f47d450(&DAT_7fff624465a0);
    FUN_7fff5f47d450(&DAT_7fff6244d7b0);
    FUN_7fff5f47d450(&DAT_7fff62479db0);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff62449e70);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e496f = '\x01';
  }
  auStackX_10[0] = 0;
  if (traceObject != (undefined *)0x0) {
    lVar3 = FUN_7fff618a1ae0(traceObject,0);
    if (lVar3 != 0) {
      uVar5 = FUN_7fff606a6750(lVar3,_DAT_7fff62469570);
      *(undefined8 *)(self + 0x88) = uVar5;
      thunk_FUN_7fff5f491fd0();
      uVar5 = _DAT_7fff623f7f60;
      if (*(longlong *)(self + 0x88) != 0) {
        lVar3 = FUN_7fff5f252ec0(7,_DAT_7fff62479db0);
        if (lVar3 != 0) {
          if (0 < *(int *)(lVar3 + 0x10)) {
            if (*(longlong *)(self + 0x88) == 0) goto LAB_7fff5fdc466b;
            cVar2 = FUN_7fff5f259320(0x17,_DAT_7fff62479db0,*(longlong *)(self + 0x88),0x10);
            if (cVar2 == '\0') {
              if (*(longlong *)(self + 0x88) == 0) goto LAB_7fff5fdc466b;
              lVar4 = FUN_7fff5f252ec0(9,_DAT_7fff62479db0);
              if (lVar4 == 0) goto LAB_7fff5fdc466b;
              auStackX_10[0] = FUN_7fff5f252ec0(1,_DAT_7fff624465a0,lVar4);
              uVar5 = FUN_7fff6100e780(auStackX_10,0);
              uVar5 = FUN_7fff60e71650(_DAT_7fff62449e70,uVar5,_DAT_7fff623fda58,0);
            }
            uVar5 = FUN_7fff60e71970(uVar5,lVar3,0);
          }
          if (*(longlong *)(self + 0x58) != 0) {
            FUN_7fff5f252c60(1,_DAT_7fff6244d7b0,*(longlong *)(self + 0x58),uVar5);
            return;
          }
        }
      }
    }
  }
LAB_7fff5fdc466b:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

