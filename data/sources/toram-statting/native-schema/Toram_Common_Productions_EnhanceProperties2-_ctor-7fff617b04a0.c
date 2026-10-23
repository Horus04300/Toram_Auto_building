
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void Toram_Common_Productions_EnhanceProperties2__ctor
               (undefined *self,int usePotential,int coefficient,int materialCategory,
               int abilityCategory,float rate,int baseMax,int upperMax,int lowerMax,int overRate,
               int doubleUse,undefined *methodInfo)

{
  *(int *)(self + 0xc) = abilityCategory;
  *(int *)(self + 0x14) = baseMax;
  *(int *)(self + 0x18) = upperMax;
  *(int *)(self + 0x1c) = lowerMax;
  *(int *)(self + 0x20) = overRate;
  *(int *)(self + 0x24) = doubleUse;
  *(float *)(self + 0x10) = rate;
  *(int *)self = usePotential;
  *(int *)(self + 4) = coefficient;
  *(int *)(self + 8) = materialCategory;
  return;
}

