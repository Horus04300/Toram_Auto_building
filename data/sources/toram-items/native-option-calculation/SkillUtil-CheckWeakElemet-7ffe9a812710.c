
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte SkillUtil_CheckWeakElemet(undefined *useType,undefined *targetType,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = (int)targetType;
  switch((int)useType) {
  case 1:
    return iVar1 == 4;
  case 2:
    return iVar1 == 1;
  case 3:
    return iVar1 == 2;
  case 4:
    return iVar1 == 3;
  case 5:
    return iVar1 == 6;
  case 6:
    return iVar1 == 5;
  default:
    return 0;
  }
}

