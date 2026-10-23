
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
  uint uVar10;
  longlong lVar11;
  longlong lVar12;
  undefined *puVar13;
  longlong *plVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  int aiStackX_8 [2];
  int aiStackX_20 [2];
  int aiStack_58 [8];
  
  if (DAT_7ffe9cae05c6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f25d8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f65a8);
    FUN_7ffe9996d590(&DAT_7ffe9c9240a0);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c953d70);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c953578);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c94fb48);
    FUN_7ffe9996d590(&DAT_7ffe9c915380);
    DAT_7ffe9cae05c6 = '\x01';
  }
  uVar16 = **(undefined8 **)(_DAT_7ffe9c9590b8 + 0xb8);
  puVar13 = *(undefined **)(self + 0x40);
  if (puVar13 != (undefined *)0x0) {
    if (*(int *)(puVar13 + 0x18) < 0x10) {
      bVar9 = FieldScriptLoader_ReadByte(puVar13,(undefined *)0x0);
      uVar10 = (uint)bVar9;
    }
    else {
      uVar10 = FieldScriptLoader_ReadInt(puVar13,(undefined *)0x0);
    }
    if (*(undefined **)(self + 0x40) != (undefined *)0x0) {
      bVar9 = FieldScriptLoader_ReadByte(*(undefined **)(self + 0x40),(undefined *)0x0);
      lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c953d70);
      if (lVar11 != 0) {
        lVar11 = FUN_7ffe9a33de50(lVar11,uVar10,0);
        uVar15 = uVar16;
        if (lVar11 != 0) {
          lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
          if (lVar12 == 0) goto LAB_7ffe9aa1d572;
          plVar14 = *(longlong **)(lVar12 + 0x28);
          if (plVar14 != (longlong *)0x0) {
            if ((*(byte *)(_DAT_7ffe9c9240a0 + 0x130) <= *(byte *)(*plVar14 + 0x130)) &&
               (*(longlong *)
                 (*(longlong *)(*plVar14 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c9240a0 + 0x130) * 8) == _DAT_7ffe9c9240a0)) {
              sVar4 = *(short *)((longlong)plVar14 + 0xb6);
              sVar5 = *(short *)((longlong)plVar14 + 0xb2);
              lVar12 = plVar14[0x16];
              fVar2 = *(float *)(plVar14 + 0x17);
              puVar13 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
              if (puVar13 != (undefined *)0x0) {
                plVar14 = (longlong *)LocalizeManager_Get(puVar13,(undefined *)0x7,(undefined *)0x0)
                ;
                uVar6 = *(undefined4 *)(lVar11 + 0x14);
                if (plVar14 != (longlong *)0x0) {
                  if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c8f65a8 + 0x130)) ||
                     (*(longlong *)
                       (*(longlong *)(*plVar14 + 200) + -8 +
                       (ulonglong)*(byte *)(_DAT_7ffe9c8f65a8 + 0x130) * 8) != _DAT_7ffe9c8f65a8)) {
                    FUN_7ffe9996c950(plVar14);
                    pcVar8 = (code *)swi(3);
                    (*pcVar8)();
                    return;
                  }
                  lVar11 = func_0x7ffe9996d210(*(undefined8 *)
                                                (*plVar14 +
                                                ((ulonglong)*(ushort *)(_DAT_7ffe9c8f25d8 + 0x50) +
                                                0x14) * 0x10));
                  plVar14 = (longlong *)(**(code **)(lVar11 + 8))(plVar14,uVar6,lVar11);
                  if (plVar14 != (longlong *)0x0) {
                    uVar15 = (**(code **)(*plVar14 + 0x178))
                                       (plVar14,*(undefined8 *)(*plVar14 + 0x180));
                  }
                  lVar11 = FUN_7ffe9aa2b870(self,0);
                  if (lVar11 == 0) {
                    FUN_7ffe9996d7a0();
                    pcVar8 = (code *)swi(3);
                    (*pcVar8)();
                    return;
                  }
                  uVar16 = FUN_7ffe99a58320(lVar11,_DAT_7ffe9c915380,0);
                  aiStackX_8[0] = (int)(short)lVar12;
                  uVar17 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
                  aiStackX_20[0] = (int)sVar4 - (int)sVar5;
                  uVar18 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_20);
                  aiStack_58[0] = (int)(fVar2 * _DAT_7ffe9c049cfc);
                  uVar19 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStack_58);
                  uVar16 = FUN_7ffe9b36a600(uVar16,uVar17,uVar18,uVar19,0);
                  goto il2cpp_write_barrier_0;
                }
              }
              goto LAB_7ffe9aa1d572;
            }
          }
        }
il2cpp_write_barrier_0:
        uVar17 = FUN_7ffe9bda5f80(_DAT_7ffe9c94fb48,0);
        uVar16 = FUN_7ffe9aa10610(self,uVar17,bVar9,uVar15,uVar16,0);
        *(undefined8 *)(self + 0x60) = uVar16;
        if (_DAT_7ffe9caee1a8 != 0) {
          uVar10 = (uint)((ulonglong)(self + 0x60) >> 0xc);
          puVar1 = (ulonglong *)((ulonglong)((uVar10 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
          do {
            uVar7 = *puVar1;
            LOCK();
            uVar3 = *puVar1;
            if (uVar7 == uVar3) {
              *puVar1 = uVar7 | 1L << (uVar10 & 0x3f);
            }
            UNLOCK();
          } while (uVar7 != uVar3);
        }
        return;
      }
    }
  }
LAB_7ffe9aa1d572:
  FUN_7ffe9996d7a0();
  pcVar8 = (code *)swi(3);
  (*pcVar8)();
  return;
}

