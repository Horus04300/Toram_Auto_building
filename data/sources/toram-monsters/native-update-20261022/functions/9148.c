
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobStatus_SetExpDef(undefined *self,int normal,int skill,int magic,undefined *methodInfo)

{
  *(int *)(self + 0x18) = normal;
  *(int *)(self + 0x24) = normal;
  *(int *)(self + 0x1c) = skill;
  *(int *)(self + 0x28) = skill;
  *(int *)(self + 0x20) = magic;
  *(int *)(self + 0x2c) = magic;
  return;
}

