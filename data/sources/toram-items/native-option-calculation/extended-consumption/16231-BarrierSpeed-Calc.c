
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BarrierSpeed_Calc(undefined *self,int value,undefined *methodInfo)

{
  return value - (int)(((float)(int)*(short *)(self + 0x10) * _DAT_7ffe9c049b88) / _DAT_7ffe9c049cfc
                      );
}

