
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MapInfo_GetMobPopPoint(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  undefined8 uVar4;
  
  if (DAT_7fff625e7267 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62454b58);
    FUN_7fff5f47d450(&DAT_7fff62444138);
    FUN_7fff5f47d450(&DAT_7fff62444078);
    FUN_7fff5f47d450(&DAT_7fff62475810);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    DAT_7fff625e7267 = '\x01';
  }
  uVar4 = *(undefined8 *)(self + 0x20);
  if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  cVar2 = FUN_7fff618ab240(uVar4,0);
  if (cVar2 == '\0') {
    puVar3 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62475810);
    FUN_7fff60a943d0(puVar3,_DAT_7fff62444078);
    return puVar3;
  }
  if (*(longlong *)(self + 0x20) != 0) {
    uVar4 = FUN_7fff606788e0(*(longlong *)(self + 0x20),1,_DAT_7fff62454b58);
    puVar3 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62475810);
    FUN_7fff60aedad0(puVar3,uVar4,_DAT_7fff62444138);
    return puVar3;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar1)();
  return puVar3;
}

