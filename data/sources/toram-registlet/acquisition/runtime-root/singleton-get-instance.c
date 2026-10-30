
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * ReviewedSingletonRoot_get_Instance(undefined *context,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong lVar6;
  undefined *puVar7;
  
  if (DAT_7ffe9cae2218 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c96ec48);
    DAT_7ffe9cae2218 = '\x01';
  }
  lVar3 = *(longlong *)(context + 0x20);
  if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
    lVar3 = FUN_7ffe998ced40(lVar3);
  }
  lVar3 = *(longlong *)(*(longlong *)(lVar3 + 0xc0) + 0x10);
  if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
    lVar3 = FUN_7ffe998ced40(lVar3);
  }
  uVar4 = **(undefined8 **)(lVar3 + 0xb8);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar2 = FUN_7ffe9bda1fa0(uVar4,0,0);
  if (cVar2 != '\0') {
    lVar3 = *(longlong *)(context + 0x20);
    if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
      lVar3 = FUN_7ffe998ced40(lVar3);
    }
    uVar4 = *(undefined8 *)(*(longlong *)(lVar3 + 0xc0) + 0x18);
    if (*(int *)(_DAT_7ffe9c96ec48 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    uVar4 = FUN_7ffe9b52cc00(uVar4,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    lVar5 = FUN_7ffe9bda0c20(uVar4,0);
    lVar3 = *(longlong *)(context + 0x20);
    if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
      lVar3 = FUN_7ffe998ced40(lVar3);
    }
    lVar3 = *(longlong *)(*(longlong *)(lVar3 + 0xc0) + 8);
    if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
      lVar3 = FUN_7ffe998ced40(lVar3);
    }
    if (lVar5 == 0) {
      lVar6 = 0;
    }
    else {
      lVar6 = func_0x7ffe9996c920(lVar5,lVar3);
      if (lVar6 == 0) {
        FUN_7ffe9996c950(lVar5,lVar3);
        pcVar1 = (code *)swi(3);
        puVar7 = (undefined *)(*pcVar1)();
        return puVar7;
      }
    }
    lVar3 = *(longlong *)(context + 0x20);
    if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
      lVar3 = FUN_7ffe998ced40(lVar3);
    }
    lVar3 = *(longlong *)(*(longlong *)(lVar3 + 0xc0) + 0x10);
    if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
      lVar3 = FUN_7ffe998ced40(lVar3);
    }
    **(longlong **)(lVar3 + 0xb8) = lVar6;
    lVar3 = *(longlong *)(context + 0x20);
    if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
      lVar3 = FUN_7ffe998ced40(lVar3);
    }
    lVar3 = *(longlong *)(*(longlong *)(lVar3 + 0xc0) + 8);
    if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
      lVar3 = FUN_7ffe998ced40(lVar3);
    }
    if (lVar5 != 0) {
      lVar6 = func_0x7ffe9996c920(lVar5,lVar3);
      if (lVar6 == 0) {
        FUN_7ffe9996c950(lVar5,lVar3);
        pcVar1 = (code *)swi(3);
        puVar7 = (undefined *)(*pcVar1)();
        return puVar7;
      }
    }
    lVar3 = *(longlong *)(context + 0x20);
    if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
      lVar3 = FUN_7ffe998ced40(lVar3);
    }
    lVar3 = *(longlong *)(*(longlong *)(lVar3 + 0xc0) + 0x10);
    if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
      FUN_7ffe998ced40(lVar3);
    }
    il2cpp_write_barrier_0();
  }
  lVar3 = *(longlong *)(context + 0x20);
  if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
    lVar3 = FUN_7ffe998ced40(lVar3);
  }
  lVar3 = *(longlong *)(*(longlong *)(lVar3 + 0xc0) + 0x10);
  if ((*(byte *)(lVar3 + 0x135) & 1) == 0) {
    lVar3 = FUN_7ffe998ced40(lVar3);
  }
  return (undefined *)**(undefined8 **)(lVar3 + 0xb8);
}

