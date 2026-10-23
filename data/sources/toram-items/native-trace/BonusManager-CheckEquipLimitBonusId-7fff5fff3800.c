
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
  
  if (DAT_7fff625e584f == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450248);
    DAT_7fff625e584f = '\x01';
  }
  uVar6 = 0;
  lVar5 = _DAT_7fff62450248;
  while( true ) {
    if (*(int *)(lVar5 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(lVar5);
      lVar5 = _DAT_7fff62450248;
    }
    lVar2 = *(longlong *)(*(longlong *)(lVar5 + 0xb8) + 0x10);
    if (lVar2 == 0) break;
    if (*(int *)(lVar2 + 0x18) <= (int)uVar6) {
      return 0;
    }
    if (*(int *)(lVar5 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(lVar5);
      lVar5 = _DAT_7fff62450248;
    }
    lVar2 = *(longlong *)(*(longlong *)(lVar5 + 0xb8) + 0x10);
    if (lVar2 == 0) break;
    if (*(uint *)(lVar2 + 0x18) <= uVar6) {
LAB_7fff5fff390d:
      FUN_7fff5f47d650();
      pcVar3 = (code *)swi(3);
      bVar4 = (*pcVar3)();
      return bVar4;
    }
    if (*(short *)(lVar2 + 0x20 + (longlong)(int)uVar6 * 4) <= id) {
      if (*(int *)(lVar5 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(lVar5);
        lVar5 = _DAT_7fff62450248;
      }
      lVar2 = *(longlong *)(*(longlong *)(lVar5 + 0xb8) + 0x10);
      if (lVar2 == 0) break;
      lVar1 = (longlong)(int)uVar6 + 1;
      if (*(uint *)(lVar2 + 0x18) <= (uint)lVar1) goto LAB_7fff5fff390d;
      if (id <= *(short *)(lVar2 + 0x20 + lVar1 * 4)) {
        return 1;
      }
    }
    uVar6 = uVar6 + 2;
  }
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  bVar4 = (*pcVar3)();
  return bVar4;
}

