
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte SkillUtil_CheckPursuitAttack(undefined *skill,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined *puVar6;
  
  if (DAT_7ffe9cadf6f1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    DAT_7ffe9cadf6f1 = '\x01';
  }
  cVar3 = FUN_7ffe9a8fec40(skill,0,0);
  if (cVar3 == '\0') {
    if (skill == (undefined *)0x0) {
LAB_7ffe9a8114dd:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      bVar4 = (*pcVar1)();
      return bVar4;
    }
    iVar5 = (**(code **)(*(longlong *)skill + 0x188))
                      (skill,*(undefined8 *)(*(longlong *)skill + 400));
    if (iVar5 - 0xbU < 2) {
LAB_7ffe9a8114c3:
      return 1;
    }
    switch(iVar5) {
    case 0x12:
    case 0x15:
    case 0x16:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
      goto LAB_7ffe9a8114c3;
    case 0x13:
    case 0x14:
    case 0x17:
    case 0x18:
      break;
    default:
      if (iVar5 == 0x2bf) {
        return 1;
      }
    }
    if ((*(byte *)(*(longlong *)skill + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)skill + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    puVar6 = (undefined *)0x0;
    if (bVar2) {
      puVar6 = skill;
    }
    cVar3 = FUN_7ffe9a8fecd0(puVar6,0,0);
    if (cVar3 != '\0') {
      if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a8114dd;
      if ((*(uint *)(puVar6 + 0x108) & 0x400) != 0) {
        return 1;
      }
    }
  }
  return 0;
}

