
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FirstAidBuf_Updata(undefined *self,undefined *methodInfo)

{
  char *pcVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = *(float *)(self + 0x20);
  if (0.0 < fVar3) {
    fVar2 = (float)FUN_7ffe9bda7ce0(0);
    fVar3 = fVar3 - fVar2;
    *(float *)(self + 0x20) = fVar3;
    if (fVar3 <= 0.0) {
      pcVar1 = self + 0x10;
      *pcVar1 = *pcVar1 + -1;
      if (*pcVar1 == '\0') {
        *(undefined4 *)(self + 0x20) = 0;
      }
      else {
        *(float *)(self + 0x20) = fVar3 + _DAT_7ffe9c049ddc;
      }
    }
  }
  fVar3 = *(float *)(self + 0x14);
  if (0.0 < fVar3) {
    fVar2 = (float)FUN_7ffe9bda7ce0(0);
    fVar3 = fVar3 - fVar2;
    *(float *)(self + 0x14) = fVar3;
    if (fVar3 <= 0.0) {
      *(uint *)(self + 0x24) = *(uint *)(self + 0x24) & 0xffffefff;
      *(uint *)(self + 0x24) = *(uint *)(self + 0x24) | 0x800;
      *(undefined4 *)(self + 0x14) = 0;
    }
  }
  if ((*(float *)(self + 0x20) == 0.0) && (*(float *)(self + 0x14) == 0.0)) {
    func_0x7ffe9a7a2130(self,0);
  }
  return;
}

