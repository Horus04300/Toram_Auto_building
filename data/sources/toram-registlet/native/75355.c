
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_AspdUpBuff_GetBonusData
               (undefined *self,undefined *id,undefined *val,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  longlong lVar3;
  
  if (DAT_7ffe9cadd3c5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c917e58);
    DAT_7ffe9cadd3c5 = '\x01';
  }
  lVar3 = func_0x7ffe9996c990(_DAT_7ffe9c917e58,1);
  if (lVar3 != 0) {
    if (*(int *)(lVar3 + 0x18) != 0) {
      *(undefined2 *)(lVar3 + 0x20) = 0x1e;
      *(longlong *)id = lVar3;
      il2cpp_write_barrier_0();
      lVar3 = func_0x7ffe9996c990(_DAT_7ffe9c917e58,1);
      if (lVar3 == 0) goto LAB_7ffe9a2e324b;
      if (*(int *)(lVar3 + 0x18) != 0) {
        *(undefined2 *)(lVar3 + 0x20) = *(undefined2 *)(self + 0x14);
        *(longlong *)val = lVar3;
        il2cpp_write_barrier_0();
        return 1;
      }
    }
    FUN_7ffe9996d790();
    pcVar1 = (code *)swi(3);
    bVar2 = (*pcVar1)();
    return bVar2;
  }
LAB_7ffe9a2e324b:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

