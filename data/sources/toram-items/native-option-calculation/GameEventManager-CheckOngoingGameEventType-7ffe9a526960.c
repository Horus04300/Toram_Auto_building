
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GameEventManager_CheckOngoingGameEventType
               (undefined *self,byte ongoingGameEventType,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  byte bVar3;
  int iVar4;
  undefined7 in_register_00000011;
  
  if (DAT_7ffe9cade2c2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90a3b0,CONCAT71(in_register_00000011,ongoingGameEventType));
    DAT_7ffe9cade2c2 = '\x01';
  }
  lVar1 = *(longlong *)(self + 0x40);
  if (lVar1 != 0) {
    if (*(int *)(lVar1 + 0x18) == 0) {
      return 0;
    }
    iVar4 = FUN_7ffe9abf3340(*(undefined8 *)(lVar1 + 0x10),ongoingGameEventType,0,
                             *(int *)(lVar1 + 0x18),
                             *(undefined8 *)
                              (*(longlong *)
                                (*(longlong *)
                                  (*(longlong *)
                                    (*(longlong *)(*(longlong *)(_DAT_7ffe9c90a3b0 + 0x20) + 0xc0) +
                                    0xd0) + 0x20) + 0xc0) + 0x150));
    return iVar4 != -1;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar3 = (*pcVar2)();
  return bVar3;
}

