
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
  
  if (DAT_7ffe9cadd59d == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c956c28);
    FUN_7ffe9996d590(&DAT_7ffe9c95f398);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7d10);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadd59d = '\x01';
  }
  puVar4 = (undefined *)FUN_7ffe9a32a560(mobId,0);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda1fa0(puVar4,0,0);
  if (cVar3 == '\0') {
    if (DAT_7ffe9cadd59e == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c954060);
      FUN_7ffe9996d590(&DAT_7ffe9c954130);
      FUN_7ffe9996d590(0x7ffe9c9545f8);
      FUN_7ffe9996d590(0x7ffe9c9551d8);
      FUN_7ffe9996d590(0x7ffe9c955508);
      FUN_7ffe9996d590(0x7ffe9c9559d0);
      FUN_7ffe9996d590(&DAT_7ffe9c957288);
      FUN_7ffe9996d590(&DAT_7ffe9c957350);
      FUN_7ffe9996d590(&DAT_7ffe9c957420);
      FUN_7ffe9996d590(&DAT_7ffe9c9578e8);
      FUN_7ffe9996d590(&DAT_7ffe9c9579b0);
      FUN_7ffe9996d590(&DAT_7ffe9c9589a0);
      FUN_7ffe9996d590(&DAT_7ffe9c959198);
      FUN_7ffe9996d590(&DAT_7ffe9c959268);
      FUN_7ffe9996d590(&DAT_7ffe9c959598);
      FUN_7ffe9996d590(0x7ffe9c9598c8);
      FUN_7ffe9996d590(0x7ffe9c959990);
      FUN_7ffe9996d590(&DAT_7ffe9c95abe8);
      FUN_7ffe9996d590(&DAT_7ffe9c95acb0);
      FUN_7ffe9996d590(&DAT_7ffe9c95c168);
      FUN_7ffe9996d590(&DAT_7ffe9c95c238);
      FUN_7ffe9996d590(0x7ffe9c95dae0);
      FUN_7ffe9996d590(0x7ffe9c95dd48);
      DAT_7ffe9cadd59e = '\x01';
    }
    if (puVar4 != (undefined *)0x0) {
      FUN_7ffe9ab9b9b0(puVar4,_DAT_7ffe9c9589a0);
      lVar5 = FUN_7ffe9ab9b9b0(puVar4,_DAT_7ffe9c956c28);
      lVar6 = FUN_7ffe9ab9c3a0(puVar4,_DAT_7ffe9c95f398);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar3 = FUN_7ffe9bda2160(lVar6,0,0);
      if (cVar3 == '\0') {
        return puVar4;
      }
      if (lVar6 != 0) {
        uVar1 = *(undefined8 *)(lVar6 + 0x30);
        uVar7 = FUN_7ffe9ab9c4e0(puVar4,1,_DAT_7ffe9c8f7d10);
        if (lVar5 != 0) {
          FUN_7ffe9a87aa00(lVar5,uVar1,uVar7,0);
          return puVar4;
        }
      }
    }
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    puVar4 = (undefined *)(*pcVar2)();
    return puVar4;
  }
  return (undefined *)0x0;
}

