
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_getElementShield(undefined *self,undefined *element,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = 0x4d;
  switch((int)element) {
  case 1:
    return 0x47;
  case 2:
    return 0x48;
  case 3:
    return 0x49;
  case 4:
    return 0x4a;
  case 5:
    return 0x4b;
  case 6:
    iVar1 = 0x4c;
  }
  return iVar1;
}

