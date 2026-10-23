
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte BonusManager_CheckEquipLimitBonusId(short id,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  byte bVar4;
  longlong lVar5;
  uint uVar6;
  
  if (DAT_7ffe9cade0f7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948908);
    DAT_7ffe9cade0f7 = '\x01';
  }
  uVar6 = 0;
  lVar5 = _DAT_7ffe9c948908;
  while( true ) {
    if (*(int *)(lVar5 + 0xe0) == 0) {
      func_0x7ffe9996d830(lVar5);
      lVar5 = _DAT_7ffe9c948908;
    }
    lVar2 = *(longlong *)(*(longlong *)(lVar5 + 0xb8) + 0x10);
    if (lVar2 == 0) break;
    if (*(int *)(lVar2 + 0x18) <= (int)uVar6) {
      return 0;
    }
    if (*(int *)(lVar5 + 0xe0) == 0) {
      func_0x7ffe9996d830(lVar5);
      lVar5 = _DAT_7ffe9c948908;
    }
    lVar2 = *(longlong *)(*(longlong *)(lVar5 + 0xb8) + 0x10);
    if (lVar2 == 0) break;
    if (*(uint *)(lVar2 + 0x18) <= uVar6) {
LAB_7ffe9a4e8d4d:
      FUN_7ffe9996d790();
      pcVar3 = (code *)swi(3);
      bVar4 = (*pcVar3)();
      return bVar4;
    }
    if (*(short *)(lVar2 + 0x20 + (longlong)(int)uVar6 * 4) <= id) {
      if (*(int *)(lVar5 + 0xe0) == 0) {
        func_0x7ffe9996d830(lVar5);
        lVar5 = _DAT_7ffe9c948908;
      }
      lVar2 = *(longlong *)(*(longlong *)(lVar5 + 0xb8) + 0x10);
      if (lVar2 == 0) break;
      lVar1 = (longlong)(int)uVar6 + 1;
      if (*(uint *)(lVar2 + 0x18) <= (uint)lVar1) goto LAB_7ffe9a4e8d4d;
      if (id <= *(short *)(lVar2 + 0x20 + lVar1 * 4)) {
        return 1;
      }
    }
    uVar6 = uVar6 + 2;
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  bVar4 = (*pcVar3)();
  return bVar4;
}

