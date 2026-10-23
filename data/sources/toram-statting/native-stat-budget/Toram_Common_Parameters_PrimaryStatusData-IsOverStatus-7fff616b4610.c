
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte Toram_Common_Parameters_PrimaryStatusData_IsOverStatus(undefined *self,undefined *methodInfo)

{
  undefined2 uVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  
  if (DAT_7fff625ee8fc == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624700a0);
    DAT_7fff625ee8fc = '\x01';
  }
  uVar1 = *(undefined2 *)(self + 0x20);
  if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  sVar2 = func_0x7fff61011120(uVar1,0xff,0);
  sVar3 = func_0x7fff61011120(*(undefined2 *)(self + 0x22),0xff,0);
  sVar4 = func_0x7fff61011120(*(undefined2 *)(self + 0x24),0xff,0);
  sVar5 = func_0x7fff61011120(*(undefined2 *)(self + 0x26),0xff,0);
  sVar6 = func_0x7fff61011120(*(undefined2 *)(self + 0x28),0xff,0);
  sVar7 = func_0x7fff61011120(*(undefined2 *)(self + 0x2a),0xff,0);
  sVar8 = func_0x7fff61011120(*(undefined2 *)(self + 0x2c),0xff,0);
  sVar9 = func_0x7fff61011120(*(undefined2 *)(self + 0x2e),0xff,0);
  sVar10 = func_0x7fff61011120(*(undefined2 *)(self + 0x30),0xff,0);
  return 499 < sVar2 + -9 +
               (int)sVar10 + (int)sVar9 + (int)sVar8 + (int)sVar7 + (int)sVar6 + (int)sVar5 +
               (int)sVar4 + (int)sVar3;
}

