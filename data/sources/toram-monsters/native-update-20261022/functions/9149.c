
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobStatus_CalcExpDef
               (undefined *self,undefined *type,int normal,int skill,int magic,undefined *methodInfo
               )

{
  int iVar1;
  int iVar2;
  
  iVar1 = (int)type;
  if (iVar1 == 0) {
    normal = -normal;
  }
  else if (iVar1 == 1) {
    skill = -skill;
  }
  else if (iVar1 == 2) {
    magic = -magic;
  }
  iVar1 = *(int *)(self + 0x18) + normal;
  if (iVar1 < 0x32) {
    iVar1 = 0x32;
  }
  else if (0xfa < iVar1) {
    iVar1 = 0xfa;
  }
  *(int *)(self + 0x18) = iVar1;
  iVar1 = *(int *)(self + 0x1c) + skill;
  if (iVar1 < 0x32) {
    iVar1 = 0x32;
  }
  else if (0xfa < iVar1) {
    iVar1 = 0xfa;
  }
  iVar2 = magic + *(int *)(self + 0x20);
  *(int *)(self + 0x1c) = iVar1;
  if (0x31 < iVar2) {
    if (0xfa < iVar2) {
      *(undefined4 *)(self + 0x20) = 0xfa;
      return;
    }
    *(int *)(self + 0x20) = iVar2;
    return;
  }
  *(undefined4 *)(self + 0x20) = 0x32;
  return;
}

