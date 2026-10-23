
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobPropertyBase_TryAddProperty(undefined *self,undefined *master,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  longlong lVar5;
  char cVar6;
  byte bVar7;
  
  if (DAT_7ffe9cadd787 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c93d430);
    DAT_7ffe9cadd787 = '\x01';
  }
  cVar6 = (**(code **)(*(longlong *)self + 0x188))
                    (self,master,*(undefined8 *)(*(longlong *)self + 400));
  lVar5 = _DAT_7ffe9c93d430;
  if (cVar6 == '\0') {
    return 0;
  }
  lVar2 = *(longlong *)(self + 0x10);
  if (lVar2 != 0) {
    *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
    lVar3 = *(longlong *)(lVar2 + 0x10);
    uVar1 = *(uint *)(lVar2 + 0x18);
    if (lVar3 != 0) {
      if (*(uint *)(lVar3 + 0x18) <= uVar1) {
        FUN_7ffe9afd58b0(lVar2,master,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
        return 1;
      }
      *(uint *)(lVar2 + 0x18) = uVar1 + 1;
      if (uVar1 < *(uint *)(lVar3 + 0x18)) {
        *(undefined **)(lVar3 + 0x20 + (longlong)(int)uVar1 * 8) = master;
        il2cpp_write_barrier_0();
        return 1;
      }
      FUN_7ffe9996d790();
      pcVar4 = (code *)swi(3);
      bVar7 = (*pcVar4)();
      return bVar7;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  bVar7 = (*pcVar4)();
  return bVar7;
}

