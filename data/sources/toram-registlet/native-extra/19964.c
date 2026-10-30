
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FumaShurikenStrengthenBuff__ctor(undefined *thisObject,short lv,undefined *methodInfo)

{
  int iVar1;
  
  func_0x7ffe999c3920(thisObject,0);
  *(short *)(thisObject + 0x14) = lv;
  iVar1 = (3 - lv) * 100;
  if (iVar1 < 100) {
    iVar1 = 100;
  }
  *(int *)(thisObject + 0x18) = iVar1;
  return;
}

