
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBuffer_StartDashBuff_Synchronization
               (undefined *self,short serverState,undefined *methodInfo)

{
  float fVar1;
  
  fVar1 = (float)(serverState & 0xfff) * _DAT_7ffe9c049b40;
  if ((ushort)serverState >> 0xc != 1) {
    if ((ushort)serverState >> 0xc != 2) {
      *(undefined4 *)(self + 0x20) = 0;
      *(undefined4 *)(self + 0x18) = 0;
      return;
    }
    *(float *)(self + 0x20) = fVar1;
    fVar1 = 0.0;
  }
  *(float *)(self + 0x18) = fVar1;
  return;
}

