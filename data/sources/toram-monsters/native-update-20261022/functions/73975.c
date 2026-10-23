
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
  
  if (DAT_7ffe9cadd214 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c945f30);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7318);
    FUN_7ffe9996d590(&DAT_7ffe9c943788);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    DAT_7ffe9cadd214 = '\x01';
  }
  auStackX_10[0] = 0;
  if (traceObject != (undefined *)0x0) {
    lVar3 = FUN_7ffe9bd98960(traceObject,0);
    if (lVar3 != 0) {
      uVar5 = FUN_7ffe9ab9c3a0(lVar3,_DAT_7ffe9c962758);
      *(undefined8 *)(self + 0x88) = uVar5;
      il2cpp_write_barrier_0();
      uVar5 = _DAT_7ffe9c8f1820;
      if (*(longlong *)(self + 0x88) != 0) {
        lVar3 = FUN_7ffe99742ec0(7,_DAT_7ffe9c9724e0);
        if (lVar3 != 0) {
          if (0 < *(int *)(lVar3 + 0x10)) {
            if (*(longlong *)(self + 0x88) == 0) goto LAB_7ffe9a2b982b;
            cVar2 = FUN_7ffe99749320(0x17,_DAT_7ffe9c9724e0,*(longlong *)(self + 0x88),0x10);
            if (cVar2 == '\0') {
              if (*(longlong *)(self + 0x88) == 0) goto LAB_7ffe9a2b982b;
              lVar4 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0);
              if (lVar4 == 0) goto LAB_7ffe9a2b982b;
              auStackX_10[0] = FUN_7ffe99742ec0(1,_DAT_7ffe9c93ed20,lVar4);
              uVar5 = FUN_7ffe9b5043c0(auStackX_10,0);
              uVar5 = FUN_7ffe9b367290(_DAT_7ffe9c943788,uVar5,_DAT_7ffe9c8f7318,0);
            }
            uVar5 = FUN_7ffe9b3675b0(uVar5,lVar3,0);
          }
          if (*(longlong *)(self + 0x58) != 0) {
            FUN_7ffe99742c60(1,_DAT_7ffe9c945f30,*(longlong *)(self + 0x58),uVar5);
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a2b982b:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

