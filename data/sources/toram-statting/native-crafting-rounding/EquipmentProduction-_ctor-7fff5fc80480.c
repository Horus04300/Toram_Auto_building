
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EquipmentProduction__ctor
               (undefined *self,undefined *manager,int recipeId,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  code *pcVar4;
  undefined8 *puVar5;
  uint uVar6;
  
  FUN_7fff61643670(self,recipeId,0);
  *(undefined **)(self + 0x28) = manager;
  thunk_FUN_7fff5f491fd0();
  if (*(longlong *)(self + 0x28) == 0) {
    FUN_7fff5f47d660();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  puVar5 = (undefined8 *)(*(longlong *)(self + 0x28) + 0x1e8);
  *puVar5 = 0;
  if (_DAT_7fff625f58f8 != 0) {
    uVar6 = (uint)((ulonglong)puVar5 >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar6 & 0x1fffff) >> 6) * 8 + 0x7fff6263d720);
    do {
      uVar3 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar3 == uVar2) {
        *puVar1 = uVar3 | 1L << (uVar6 & 0x3f);
      }
      UNLOCK();
    } while (uVar3 != uVar2);
  }
  return;
}

