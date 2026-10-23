
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MobFactory_CreateMmoMobObject(int mobId,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  undefined *puVar4;
  longlong lVar5;
  longlong lVar6;
  undefined8 uVar7;
  
  if (DAT_7fff625e4cf5 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245da40);
    FUN_7fff5f47d450(&DAT_7fff624661b0);
    FUN_7fff5f47d450(&DAT_7fff623fec70);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    DAT_7fff625e4cf5 = '\x01';
  }
  puVar4 = (undefined *)FUN_7fff5fe35230(mobId,0);
  if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  cVar3 = FUN_7fff618ab120(puVar4,0,0);
  if (cVar3 == '\0') {
    if (DAT_7fff625e4cf6 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff6245ae78);
      FUN_7fff5f47d450(&DAT_7fff6245af48);
      FUN_7fff5f47d450(0x7fff6245b410);
      FUN_7fff5f47d450(0x7fff6245bff0);
      FUN_7fff5f47d450(0x7fff6245c320);
      FUN_7fff5f47d450(0x7fff6245c7e8);
      FUN_7fff5f47d450(&DAT_7fff6245e0a0);
      FUN_7fff5f47d450(&DAT_7fff6245e168);
      FUN_7fff5f47d450(&DAT_7fff6245e238);
      FUN_7fff5f47d450(&DAT_7fff6245e700);
      FUN_7fff5f47d450(&DAT_7fff6245e7c8);
      FUN_7fff5f47d450(&DAT_7fff6245f7b8);
      FUN_7fff5f47d450(&DAT_7fff6245ffb0);
      FUN_7fff5f47d450(&DAT_7fff62460080);
      FUN_7fff5f47d450(&DAT_7fff624603b0);
      FUN_7fff5f47d450(0x7fff624606e0);
      FUN_7fff5f47d450(0x7fff624607a8);
      FUN_7fff5f47d450(&DAT_7fff62461a00);
      FUN_7fff5f47d450(&DAT_7fff62461ac8);
      FUN_7fff5f47d450(&DAT_7fff62462f80);
      FUN_7fff5f47d450(&DAT_7fff62463050);
      FUN_7fff5f47d450(0x7fff624648f8);
      FUN_7fff5f47d450(0x7fff62464b58);
      DAT_7fff625e4cf6 = '\x01';
    }
    if (puVar4 != (undefined *)0x0) {
      FUN_7fff606a5d60(puVar4,_DAT_7fff6245f7b8);
      lVar5 = FUN_7fff606a5d60(puVar4,_DAT_7fff6245da40);
      lVar6 = FUN_7fff606a6750(puVar4,_DAT_7fff624661b0);
      if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      cVar3 = FUN_7fff618ab2e0(lVar6,0,0);
      if (cVar3 == '\0') {
        return puVar4;
      }
      if (lVar6 != 0) {
        uVar1 = *(undefined8 *)(lVar6 + 0x30);
        uVar7 = FUN_7fff606a6890(puVar4,1,_DAT_7fff623fec70);
        if (lVar5 != 0) {
          FUN_7fff60384e90(lVar5,uVar1,uVar7,0);
          return puVar4;
        }
      }
    }
    FUN_7fff5f47d660();
    pcVar2 = (code *)swi(3);
    puVar4 = (undefined *)(*pcVar2)();
    return puVar4;
  }
  return (undefined *)0x0;
}

