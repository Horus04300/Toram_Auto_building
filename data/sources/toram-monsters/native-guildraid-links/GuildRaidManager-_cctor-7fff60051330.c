
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidManager__cctor(undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  uint uVar5;
  
  if (DAT_7fff625e5b68 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242b7f0);
    FUN_7fff5f47d450(&DAT_7fff6241fab8);
    FUN_7fff5f47d450(&DAT_7fff6244d1b8);
    DAT_7fff625e5b68 = '\x01';
  }
  uVar4 = func_0x7fff5f47c850(_DAT_7fff6241fab8,6);
  FUN_7fff60f40820(uVar4,_DAT_7fff6244d1b8,0);
  **(undefined8 **)(_DAT_7fff6242b7f0 + 0xb8) = uVar4;
  if (_DAT_7fff625f58f8 != 0) {
    uVar5 = (uint)(*(ulonglong *)(_DAT_7fff6242b7f0 + 0xb8) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar5 & 0x1fffff) >> 6) * 8 + 0x7fff6263d720);
    do {
      uVar3 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar3 == uVar2) {
        *puVar1 = uVar3 | 1L << (uVar5 & 0x3f);
      }
      UNLOCK();
    } while (uVar3 != uVar2);
  }
  return;
}

