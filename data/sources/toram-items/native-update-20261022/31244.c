
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SkillManager_GetAvatarSkillId(int bonusValue,undefined *methodInfo)

{
  switch(bonusValue) {
  case 0:
    return 0x501;
  case 1:
    return 0x502;
  default:
    return 0;
  case 5:
    return 0x505;
  }
}

