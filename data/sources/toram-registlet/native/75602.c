
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float GemCartBuffer_LunaDitherStarAssaultBuff_get_CoolDownTime
                (undefined *self,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = (**(code **)(*(longlong *)self + 0x1d8))
                    (self,2,*(undefined8 *)(*(longlong *)self + 0x1e0));
  return (float)(0xf - iVar1);
}

