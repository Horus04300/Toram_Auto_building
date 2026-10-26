
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * SkillUtil_GetWeakElement(undefined *target,undefined *methodInfo)

{
  switch((int)target) {
  case 1:
    return (undefined *)0x2;
  case 2:
    return (undefined *)0x3;
  case 3:
    return (undefined *)0x4;
  case 4:
    return (undefined *)0x1;
  case 5:
    return (undefined *)0x6;
  case 6:
    return (undefined *)0x5;
  default:
    return (undefined *)0x0;
  }
}

