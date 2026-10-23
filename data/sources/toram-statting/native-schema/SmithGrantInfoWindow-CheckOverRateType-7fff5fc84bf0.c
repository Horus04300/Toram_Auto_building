
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte SmithGrantInfoWindow_CheckOverRateType(undefined *self,int type,undefined *methodInfo)

{
  if ((type - 0x16U < 0xb) && ((type - 0x16U & 1) == 0)) {
    return 1;
  }
  return type == 0xc;
}

