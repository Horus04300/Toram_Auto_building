
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EquipBuffDataBase_SumValue(undefined *self,short val,undefined *methodInfo)

{
  *(short *)(self + 0x10) = *(short *)(self + 0x10) + val;
  return;
}

