
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FireStyleStrengthenBuff__ctor(undefined *thisObject,short lv,undefined *methodInfo)

{
  double dVar1;
  float fVar2;
  
  func_0x7ffe999c3920(thisObject,0);
  *(short *)(thisObject + 0x14) = lv;
  if (DAT_7ffe9cad9e25 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cad9e25 = '\x01';
  }
  fVar2 = (float)(int)lv * _DAT_7ffe9c049dc4;
  if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  dVar1 = (double)func_0x7ffe99997768((double)fVar2);
  *(int *)(thisObject + 0x18) = (int)dVar1;
  return;
}

