
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * BonusManager_GetEquipElement(undefined *self,undefined *type,undefined *methodInfo)

{
  undefined8 uVar1;
  undefined8 uVar2;
  code *pcVar3;
  char cVar4;
  longlong lVar5;
  undefined *puVar6;
  uint uVar7;
  
  if (DAT_7ffe9cade120 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9595d0);
    FUN_7ffe9996d590(&DAT_7ffe9c959900);
    FUN_7ffe9996d590(&DAT_7ffe9c90b598);
    FUN_7ffe9996d590(&DAT_7ffe9c9419c0);
    FUN_7ffe9996d590(&DAT_7ffe9c919698);
    FUN_7ffe9996d590(&DAT_7ffe9c924e78);
    DAT_7ffe9cade120 = '\x01';
  }
  if (*(longlong *)(self + 0x20) != 0) {
    cVar4 = FUN_7ffe9ad5f0a0(*(longlong *)(self + 0x20),(ulonglong)type & 0xffffffff,
                             _DAT_7ffe9c9595d0);
    uVar7 = 0;
    if (cVar4 == '\0') {
LAB_7ffe9a4eba46:
      return (undefined *)(ulonglong)uVar7;
    }
    if (*(longlong *)(self + 0x20) != 0) {
      lVar5 = FUN_7ffe9ad723c0(*(longlong *)(self + 0x20),(ulonglong)type & 0xffffffff,
                               _DAT_7ffe9c959900);
      if (lVar5 != 0) {
        uVar1 = *(undefined8 *)(lVar5 + 0x20);
        if (*(int *)(_DAT_7ffe9c924e78 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        lVar5 = *(longlong *)(*(longlong *)(_DAT_7ffe9c924e78 + 0xb8) + 8);
        if (lVar5 == 0) {
          if (*(int *)(_DAT_7ffe9c924e78 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          uVar2 = **(undefined8 **)(_DAT_7ffe9c924e78 + 0xb8);
          lVar5 = func_0x7ffe99940040(_DAT_7ffe9c9419c0);
          FUN_7ffe9af13420(lVar5,uVar2,_DAT_7ffe9c919698,0);
          *(longlong *)(*(longlong *)(_DAT_7ffe9c924e78 + 0xb8) + 8) = lVar5;
          il2cpp_write_barrier_0();
        }
        lVar5 = FUN_7ffe9ab854c0(uVar1,lVar5,_DAT_7ffe9c90b598);
        uVar7 = 0;
        if (lVar5 != 0) {
          uVar7 = *(uint *)(lVar5 + 0x14);
        }
        goto LAB_7ffe9a4eba46;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  puVar6 = (undefined *)(*pcVar3)();
  return puVar6;
}

