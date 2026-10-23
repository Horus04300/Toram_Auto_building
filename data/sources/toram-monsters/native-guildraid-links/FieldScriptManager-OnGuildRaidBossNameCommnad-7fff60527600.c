
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FieldScriptManager_OnGuildRaidBossNameCommnad
               (undefined *self,undefined *command,undefined *methodInfo)

{
  ulonglong *puVar1;
  float fVar2;
  ulonglong uVar3;
  short sVar4;
  short sVar5;
  undefined4 uVar6;
  ulonglong uVar7;
  code *pcVar8;
  byte bVar9;
  undefined1 uVar10;
  uint uVar11;
  longlong lVar12;
  longlong lVar13;
  longlong lVar14;
  longlong *plVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  int aiStackX_8 [2];
  int aiStackX_20 [2];
  int aiStack_58 [8];
  
  if (DAT_7fff625e7d1c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623f9538);
    FUN_7fff5f47d450(&DAT_7fff623fe068);
    FUN_7fff5f47d450(&DAT_7fff6242ba48);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff6245ac58);
    FUN_7fff5f47d450(&DAT_7fff6245c360);
    FUN_7fff5f47d450(&DAT_7fff6245a460);
    FUN_7fff5f47d450(&DAT_7fff624606c8);
    FUN_7fff5f47d450(&DAT_7fff624559c0);
    FUN_7fff5f47d450(&DAT_7fff6241bac0);
    DAT_7fff625e7d1c = '\x01';
  }
  uVar17 = **(undefined8 **)(_DAT_7fff624606c8 + 0xb8);
  lVar12 = *(longlong *)(self + 0x40);
  if (lVar12 != 0) {
    if (*(int *)(lVar12 + 0x18) < 0x10) {
      bVar9 = FUN_7fff60506580(lVar12,0);
      uVar11 = (uint)bVar9;
    }
    else {
      uVar11 = FUN_7fff60506890();
    }
    if (*(longlong *)(self + 0x40) != 0) {
      uVar10 = FUN_7fff60506580(*(longlong *)(self + 0x40),0);
      lVar12 = FUN_7fff60c4bc00(_DAT_7fff6245ac58);
      if (lVar12 != 0) {
        lVar12 = FUN_7fff5fe48b20(lVar12,uVar11,0);
        uVar16 = uVar17;
        if (lVar12 != 0) {
          lVar13 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
          if (lVar13 == 0) goto LAB_7fff60527962;
          plVar15 = *(longlong **)(lVar13 + 0x28);
          if (plVar15 != (longlong *)0x0) {
            if ((*(byte *)(_DAT_7fff6242ba48 + 0x130) <= *(byte *)(*plVar15 + 0x130)) &&
               (*(longlong *)
                 (*(longlong *)(*plVar15 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7fff6242ba48 + 0x130) * 8) == _DAT_7fff6242ba48)) {
              sVar4 = *(short *)((longlong)plVar15 + 0xb6);
              sVar5 = *(short *)((longlong)plVar15 + 0xb2);
              lVar13 = plVar15[0x16];
              fVar2 = *(float *)(plVar15 + 0x17);
              lVar14 = FUN_7fff60c4bc00(_DAT_7fff6245a460);
              if (lVar14 != 0) {
                plVar15 = (longlong *)FUN_7fff5f55ae30(lVar14,7,0);
                uVar6 = *(undefined4 *)(lVar12 + 0x14);
                if (plVar15 != (longlong *)0x0) {
                  if ((*(byte *)(*plVar15 + 0x130) < *(byte *)(_DAT_7fff623fe068 + 0x130)) ||
                     (*(longlong *)
                       (*(longlong *)(*plVar15 + 200) + -8 +
                       (ulonglong)*(byte *)(_DAT_7fff623fe068 + 0x130) * 8) != _DAT_7fff623fe068)) {
                    FUN_7fff5f47c810(plVar15);
                    pcVar8 = (code *)swi(3);
                    (*pcVar8)();
                    return;
                  }
                  lVar12 = func_0x7fff5f47d0d0(*(undefined8 *)
                                                (*plVar15 +
                                                ((ulonglong)*(ushort *)(_DAT_7fff623f9538 + 0x50) +
                                                0x14) * 0x10));
                  plVar15 = (longlong *)(**(code **)(lVar12 + 8))(plVar15,uVar6,lVar12);
                  if (plVar15 != (longlong *)0x0) {
                    uVar16 = (**(code **)(*plVar15 + 0x178))
                                       (plVar15,*(undefined8 *)(*plVar15 + 0x180));
                  }
                  lVar12 = FUN_7fff60535c60(self,0);
                  if (lVar12 == 0) {
                    FUN_7fff5f47d660();
                    pcVar8 = (code *)swi(3);
                    (*pcVar8)();
                    return;
                  }
                  uVar17 = FUN_7fff5f568150(lVar12,_DAT_7fff6241bac0,0);
                  aiStackX_8[0] = (int)(short)lVar13;
                  uVar18 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
                  aiStackX_20[0] = (int)sVar4 - (int)sVar5;
                  uVar19 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_20);
                  aiStack_58[0] = (int)(fVar2 * _DAT_7fff61b52cfc);
                  uVar20 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStack_58);
                  uVar17 = FUN_7fff60e749c0(uVar17,uVar18,uVar19,uVar20,0);
                  goto thunk_FUN_7fff5f491fd0;
                }
              }
              goto LAB_7fff60527962;
            }
          }
        }
thunk_FUN_7fff5f491fd0:
        uVar18 = FUN_7fff618af100(_DAT_7fff624559c0,0);
        uVar17 = FUN_7fff6051aa00(self,uVar18,uVar10,uVar16,uVar17,0);
        *(undefined8 *)(self + 0x60) = uVar17;
        if (_DAT_7fff625f58f8 != 0) {
          uVar11 = (uint)((ulonglong)(self + 0x60) >> 0xc);
          puVar1 = (ulonglong *)((ulonglong)((uVar11 & 0x1fffff) >> 6) * 8 + 0x7fff6263d720);
          do {
            uVar7 = *puVar1;
            LOCK();
            uVar3 = *puVar1;
            if (uVar7 == uVar3) {
              *puVar1 = uVar7 | 1L << (uVar11 & 0x3f);
            }
            UNLOCK();
          } while (uVar7 != uVar3);
        }
        return;
      }
    }
  }
LAB_7fff60527962:
  FUN_7fff5f47d660();
  pcVar8 = (code *)swi(3);
  (*pcVar8)();
  return;
}

