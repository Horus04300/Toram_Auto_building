
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EnemyMobActionManagerBase_UpdateExpDef
               (undefined *self,int normal,int skill,int magic,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  
  if (self[0x151] == '\0') {
    lVar2 = *(longlong *)(self + 0x78);
  }
  else {
    if (*(longlong *)(self + 0xf8) == 0) goto LAB_7fff5fe21f16;
    lVar2 = FUN_7fff5fe22fb0(*(longlong *)(self + 0xf8),0);
  }
  if (lVar2 != 0) {
    *(int *)(lVar2 + 0x18) = normal;
    *(int *)(lVar2 + 0x24) = normal;
    *(int *)(lVar2 + 0x1c) = skill;
    *(int *)(lVar2 + 0x28) = skill;
    *(int *)(lVar2 + 0x20) = magic;
    *(int *)(lVar2 + 0x2c) = magic;
    return;
  }
LAB_7fff5fe21f16:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

