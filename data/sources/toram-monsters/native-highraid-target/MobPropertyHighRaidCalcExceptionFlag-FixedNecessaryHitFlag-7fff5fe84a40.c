
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobPropertyHighRaidCalcExceptionFlag_FixedNecessaryHitFlag
               (undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  longlong lVar3;
  
  if (DAT_7fff625e4ee0 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6240d7c8);
    DAT_7fff625e4ee0 = '\x01';
  }
  lVar3 = FUN_7fff6068f640(*(undefined8 *)(self + 0x10),_DAT_7fff6240d7c8);
  if (lVar3 != 0) {
    lVar3 = *(longlong *)(lVar3 + 0x18);
    if (lVar3 == 0) {
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      bVar2 = (*pcVar1)();
      return bVar2;
    }
    if (*(int *)(lVar3 + 0x18) == 0) {
      FUN_7fff5f47d650();
      pcVar1 = (code *)swi(3);
      bVar2 = (*pcVar1)();
      return bVar2;
    }
    if ((*(byte *)(lVar3 + 0x20) & 2) != 0) {
      return 1;
    }
  }
  return 0;
}

