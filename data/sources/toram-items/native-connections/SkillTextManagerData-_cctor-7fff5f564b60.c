
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
  
  if (DAT_7fff625e1581 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62453610);
    FUN_7fff5f47d450(&DAT_7fff62426990);
    FUN_7fff5f47d450(&DAT_7fff6240b720);
    FUN_7fff5f47d450(&DAT_7fff62437c68);
    FUN_7fff5f47d450(&DAT_7fff6243f6d8);
    FUN_7fff5f47d450(&DAT_7fff62420d98);
    FUN_7fff5f47d450(&DAT_7fff624727d0);
    FUN_7fff5f47d450(&DAT_7fff62441800);
    FUN_7fff5f47d450(&DAT_7fff62451720);
    DAT_7fff625e1581 = '\x01';
  }
  lVar5 = func_0x7fff5f47c850(_DAT_7fff62426990,7);
  if (lVar5 == 0) {
    FUN_7fff5f47d660();
    pcVar4 = (code *)swi(3);
    (*pcVar4)();
    return;
  }
  if (*(int *)(lVar5 + 0x18) != 0) {
    *(undefined8 *)(lVar5 + 0x20) = _DAT_7fff624727d0;
    thunk_FUN_7fff5f491fd0();
    if (1 < *(uint *)(lVar5 + 0x18)) {
      *(undefined8 *)(lVar5 + 0x28) = _DAT_7fff62451720;
      thunk_FUN_7fff5f491fd0();
      if (2 < *(uint *)(lVar5 + 0x18)) {
        *(undefined8 *)(lVar5 + 0x30) = _DAT_7fff62441800;
        thunk_FUN_7fff5f491fd0();
        if (3 < *(uint *)(lVar5 + 0x18)) {
          *(undefined8 *)(lVar5 + 0x38) = _DAT_7fff6240b720;
          thunk_FUN_7fff5f491fd0();
          if (4 < *(uint *)(lVar5 + 0x18)) {
            *(undefined8 *)(lVar5 + 0x40) = _DAT_7fff62437c68;
            thunk_FUN_7fff5f491fd0();
            if (5 < *(uint *)(lVar5 + 0x18)) {
              *(undefined8 *)(lVar5 + 0x48) = _DAT_7fff6243f6d8;
              thunk_FUN_7fff5f491fd0();
              if (6 < *(uint *)(lVar5 + 0x18)) {
                *(undefined8 *)(lVar5 + 0x50) = _DAT_7fff62420d98;
                thunk_FUN_7fff5f491fd0();
                **(longlong **)(_DAT_7fff62453610 + 0xb8) = lVar5;
                if (_DAT_7fff625f58f8 != 0) {
                  uVar6 = (uint)(*(ulonglong *)(_DAT_7fff62453610 + 0xb8) >> 0xc);
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
            }
          }
        }
      }
    }
  }
  FUN_7fff5f47d650();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

