
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
    if (*(longlong *)(self + 0xf8) == 0) goto LAB_7ffe9a3171a6;
    lVar2 = FUN_7ffe9a318240(*(longlong *)(self + 0xf8),0);
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
LAB_7ffe9a3171a6:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

