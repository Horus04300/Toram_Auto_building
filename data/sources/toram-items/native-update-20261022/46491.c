
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkillTextManagerData__cctor(undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  code *pcVar4;
  longlong lVar5;
  uint uVar6;
  
  if (DAT_7ffe9cad9e05 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94bf18);
    FUN_7ffe9996d590(&DAT_7ffe9c91ef20);
    FUN_7ffe9996d590(&DAT_7ffe9c9058d0);
    FUN_7ffe9996d590(&DAT_7ffe9c931580);
    FUN_7ffe9996d590(&DAT_7ffe9c938ff0);
    FUN_7ffe9996d590(&DAT_7ffe9c91a658);
    FUN_7ffe9996d590(&DAT_7ffe9c96c1b0);
    FUN_7ffe9996d590(&DAT_7ffe9c93b118);
    FUN_7ffe9996d590(&DAT_7ffe9c94b038);
    DAT_7ffe9cad9e05 = '\x01';
  }
  lVar5 = func_0x7ffe9996c990(_DAT_7ffe9c91ef20,7);
  if (lVar5 == 0) {
    FUN_7ffe9996d7a0();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (*(int *)(lVar5 + 0x18) != 0) {
    *(undefined8 *)(lVar5 + 0x20) = _DAT_7ffe9c96c1b0;
    il2cpp_write_barrier_0();
    if (1 < *(uint *)(lVar5 + 0x18)) {
      *(undefined8 *)(lVar5 + 0x28) = _DAT_7ffe9c94b038;
      il2cpp_write_barrier_0();
      if (2 < *(uint *)(lVar5 + 0x18)) {
        *(undefined8 *)(lVar5 + 0x30) = _DAT_7ffe9c93b118;
        il2cpp_write_barrier_0();
        if (3 < *(uint *)(lVar5 + 0x18)) {
          *(undefined8 *)(lVar5 + 0x38) = _DAT_7ffe9c9058d0;
          il2cpp_write_barrier_0();
          if (4 < *(uint *)(lVar5 + 0x18)) {
            *(undefined8 *)(lVar5 + 0x40) = _DAT_7ffe9c931580;
            il2cpp_write_barrier_0();
            if (5 < *(uint *)(lVar5 + 0x18)) {
              *(undefined8 *)(lVar5 + 0x48) = _DAT_7ffe9c938ff0;
              il2cpp_write_barrier_0();
              if (6 < *(uint *)(lVar5 + 0x18)) {
                *(undefined8 *)(lVar5 + 0x50) = _DAT_7ffe9c91a658;
                il2cpp_write_barrier_0();
                **(longlong **)(_DAT_7ffe9c94bf18 + 0xb8) = lVar5;
                if (_DAT_7ffe9caee1a8 != 0) {
                  uVar6 = (uint)(*(ulonglong *)(_DAT_7ffe9c94bf18 + 0xb8) >> 0xc);
                  puVar1 = (ulonglong *)((ulonglong)((uVar6 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
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
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d790();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

