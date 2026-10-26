
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_CalcFlee(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  undefined8 unaff_RDI;
  undefined8 in_R9;
  
  if (*(longlong *)(self + 0xa0) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar3 = (*pcVar2)();
    return iVar3;
  }
  iVar3 = *(int *)(*(longlong *)(self + 0xa0) + 0x2c);
  if (DAT_7ffe9cadd7d1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949540);
    DAT_7ffe9cadd7d1 = '\x01';
  }
  iVar4 = (int)*(short *)(self + 0xc0);
  if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  if (DAT_7ffe9cae7a2e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949540,iVar4,0,in_R9,unaff_RDI);
    DAT_7ffe9cae7a2e = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
    func_0x7ffe9996d830(_DAT_7ffe9c949540);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x10);
  if (iVar4 < -1) {
    iVar4 = -1;
  }
  else if (3 < iVar4) {
    iVar4 = 3;
  }
  if (lVar1 != 0) {
    if ((uint)((longlong)iVar4 + 1) < *(uint *)(lVar1 + 0x18)) {
      return (int)((float)iVar3 * *(float *)(lVar1 + 0x20 + ((longlong)iVar4 + 1) * 4));
    }
    FUN_7ffe9996d790();
    pcVar2 = (code *)swi(3);
    iVar3 = (*pcVar2)();
    return iVar3;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

