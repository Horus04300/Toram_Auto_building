
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte AvoidActionManager_CheckAvoid
               (undefined *self,undefined *mobAction,undefined *mobAttack,undefined *methodInfo)

{
  ulonglong uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined1 uVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  code *pcVar8;
  char cVar9;
  byte bVar10;
  undefined *puVar11;
  ulonglong *puVar12;
  longlong lVar13;
  undefined8 *puVar14;
  longlong *plVar15;
  undefined8 uVar16;
  longlong lVar17;
  ushort uVar18;
  ushort uVar19;
  undefined4 uVar20;
  float fVar21;
  float fStackX_8;
  float fStackX_c;
  ulonglong *in_stack_ffffffffffffff28;
  undefined8 in_stack_ffffffffffffff30;
  undefined4 uVar22;
  undefined8 uStack_b8;
  float fStack_b0;
  ulonglong uStack_a8;
  float fStack_a0;
  undefined8 uStack_98;
  float fStack_90;
  undefined8 uStack_88;
  float fStack_80;
  undefined8 uStack_78;
  undefined4 uStack_70;
  undefined8 uStack_68;
  float fStack_60;
  undefined4 uStack_5c;
  
  uVar22 = (undefined4)((ulonglong)in_stack_ffffffffffffff30 >> 0x20);
  if (DAT_7ffe9cadf5d9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8edca8);
    FUN_7ffe9996d590(&DAT_7ffe9c9530b0);
    DAT_7ffe9cadf5d9 = '\x01';
  }
  uStack_78 = 0;
  uStack_70 = 0;
  cVar9 = FUN_7ffe9a803ff0(*(undefined8 *)(self + 0x28),mobAttack,0);
  if (((cVar9 != '\0') ||
      (cVar9 = FUN_7ffe9a761600(*(undefined8 *)(self + 0x28),mobAttack,0), cVar9 != '\0')) ||
     (cVar9 = FUN_7ffe9a6e8d00(*(undefined8 *)(self + 0x28),mobAttack,0), cVar9 != '\0')) {
    return 1;
  }
  puVar11 = AvoidActionManager_get_AvoidType(self,(undefined *)0x0);
  if ((int)puVar11 != 1) {
    puVar11 = AvoidActionManager_get_AvoidType(self,(undefined *)0x0);
    if ((int)puVar11 != 0) {
      return 0;
    }
    if (mobAttack != (undefined *)0x0) {
      lVar13 = *(longlong *)mobAttack;
      if ((*(byte *)(_DAT_7ffe9c8edca8 + 0x130) <= *(byte *)(lVar13 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(lVar13 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8edca8 + 0x130) * 8)
          == _DAT_7ffe9c8edca8)) {
        if ((*(byte *)(lVar13 + 0x130) < *(byte *)(_DAT_7ffe9c8edca8 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(lVar13 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8edca8 + 0x130) * 8
             ) != _DAT_7ffe9c8edca8)) {
          FUN_7ffe9996c950(mobAttack);
          pcVar8 = (code *)swi(3);
          bVar10 = (*pcVar8)();
          return bVar10;
        }
        cVar9 = func_0x7ffe9a387690(mobAttack,0);
        if (cVar9 == '\0') {
          return 0;
        }
        goto LAB_7ffe9a7d635f;
      }
    }
    if (mobAction == (undefined *)0x0) {
      return 0;
    }
    if ((mobAttack != (undefined *)0x0) && (*(longlong *)(mobAttack + 0xa0) != 0)) {
      iVar5 = *(int *)(*(longlong *)(mobAttack + 0xa0) + 0x3c);
      if (iVar5 < 0xb) {
        if ((iVar5 != 0) && (iVar5 != 10)) {
          return 0;
        }
      }
      else if (((iVar5 != 0x14) && (iVar5 != 0x1e)) && (3 < iVar5 - 0xf0U)) {
        return 0;
      }
LAB_7ffe9a7d635f:
      return self[0x50];
    }
    goto LAB_7ffe9a7d6aee;
  }
  bVar10 = AvoidActionManager_CheckAvoidStart(self,(undefined *)0x0);
  if (bVar10 == 0) {
    return 0;
  }
  if (mobAttack == (undefined *)0x0) {
LAB_7ffe9a7d6471:
    if (mobAction == (undefined *)0x0) {
      return 0;
    }
    if ((mobAttack == (undefined *)0x0) || (*(longlong *)(mobAttack + 0xa0) == 0))
    goto LAB_7ffe9a7d6aee;
    iVar5 = *(int *)(*(longlong *)(mobAttack + 0xa0) + 0x3c);
    if (iVar5 < 0xb) {
      if (iVar5 == 0) {
        return 0;
      }
      if (iVar5 == 10) {
        return 0;
      }
    }
    else {
      if (iVar5 == 0x14) {
        return 0;
      }
      if (iVar5 == 0x1e) {
        return 0;
      }
      if (iVar5 - 0xf0U < 4) {
        return 0;
      }
    }
    lVar13 = FUN_7ffe9bd7a830(0);
    if ((lVar13 == 0) || (lVar13 = FUN_7ffe9bd98a10(lVar13,0), lVar13 == 0)) goto LAB_7ffe9a7d6aee;
    puVar14 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_68,lVar13,0);
    uVar2 = *puVar14;
    fVar7 = *(float *)(puVar14 + 1);
    lVar13 = FUN_7ffe9bd7a830(0);
    if ((lVar13 == 0) || (lVar13 = FUN_7ffe9bd98a10(lVar13,0), lVar13 == 0)) goto LAB_7ffe9a7d6aee;
    puVar14 = (undefined8 *)FUN_7ffe9bdbf190(&uStack_68,lVar13,0);
    lVar13 = *(longlong *)mobAction;
    uVar19 = 0;
    uVar16 = *puVar14;
    fVar21 = *(float *)(puVar14 + 1);
    if (*(ushort *)(lVar13 + 0x12e) != 0) {
      uVar18 = uVar19;
      do {
        if (*(longlong *)(*(longlong *)(lVar13 + 0xb0) + (ulonglong)uVar18 * 0x10) ==
            _DAT_7ffe9c9724e0) {
          puVar14 = (undefined8 *)
                    ((longlong)
                     (*(int *)(*(longlong *)(lVar13 + 0xb0) + 8 + (ulonglong)uVar18 * 0x10) + 0x16)
                     * 0x10 + 0x138 + lVar13);
          goto LAB_7ffe9a7d659a;
        }
        uVar18 = uVar18 + 1;
      } while (uVar18 < *(ushort *)(lVar13 + 0x12e));
    }
    puVar14 = (undefined8 *)FUN_7ffe998ce540(mobAction,_DAT_7ffe9c9724e0,0x16);
LAB_7ffe9a7d659a:
    lVar13 = (*(code *)*puVar14)(mobAction,puVar14[1]);
    if (lVar13 == 0) goto LAB_7ffe9a7d6aee;
    puVar12 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_68,lVar13,0);
    lVar13 = *(longlong *)mobAction;
    uVar1 = *puVar12;
    fVar6 = *(float *)(puVar12 + 1);
    if (*(ushort *)(lVar13 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar13 + 0xb0) + (ulonglong)uVar19 * 0x10) ==
            _DAT_7ffe9c9724e0) {
          puVar14 = (undefined8 *)
                    (lVar13 + 0x138 +
                    (longlong)*(int *)(*(longlong *)(lVar13 + 0xb0) + 8 + (ulonglong)uVar19 * 0x10)
                    * 0x10);
          goto LAB_7ffe9a7d6617;
        }
        uVar19 = uVar19 + 1;
      } while (uVar19 < *(ushort *)(lVar13 + 0x12e));
    }
    puVar14 = (undefined8 *)FUN_7ffe998ce540(mobAction,_DAT_7ffe9c9724e0,0);
LAB_7ffe9a7d6617:
    uVar20 = (*(code *)*puVar14)(mobAction,puVar14[1]);
    in_stack_ffffffffffffff28 = &uStack_a8;
    uStack_b8 = uVar16;
    fStack_b0 = fVar21;
    uStack_a8 = uVar1;
    fStack_a0 = fVar6;
    uStack_98 = uVar2;
    fStack_90 = fVar7;
    cVar9 = FUN_7ffe99a4e750(&uStack_98,&uStack_b8,_DAT_7ffe9c049ec0,_DAT_7ffe9c049b1c,
                             in_stack_ffffffffffffff28,CONCAT44(uVar22,uVar20),0);
  }
  else {
    lVar13 = *(longlong *)mobAttack;
    if ((*(byte *)(lVar13 + 0x130) < *(byte *)(_DAT_7ffe9c8edca8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar13 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8edca8 + 0x130) * 8) !=
        _DAT_7ffe9c8edca8)) goto LAB_7ffe9a7d6471;
    if ((*(byte *)(lVar13 + 0x130) < *(byte *)(_DAT_7ffe9c8edca8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar13 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8edca8 + 0x130) * 8) !=
        _DAT_7ffe9c8edca8)) {
      FUN_7ffe9996c950(mobAttack);
      pcVar8 = (code *)swi(3);
      bVar10 = (*pcVar8)();
      return bVar10;
    }
    cVar9 = func_0x7ffe9a387690(mobAttack,0);
  }
  if (cVar9 == '\0') {
    return 0;
  }
  lVar13 = *(longlong *)(self + 0x38);
  if (lVar13 != 0) {
    uVar4 = *(undefined1 *)(lVar13 + 0x13e);
    lVar13 = FUN_7ffe9bd98a10(lVar13,0);
    if (lVar13 != 0) {
      puVar14 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_68,lVar13);
      uVar2 = *puVar14;
      fVar7 = *(float *)(puVar14 + 1);
      lVar13 = FUN_7ffe9bd98960(self,0);
      if ((lVar13 != 0) && (lVar13 = FUN_7ffe9bd9b890(lVar13,0), lVar13 != 0)) {
        puVar14 = (undefined8 *)FUN_7ffe9bdbf880(&uStack_68,lVar13);
        uStack_68 = *puVar14;
        fStack_60 = *(float *)(puVar14 + 1);
        uStack_5c = *(undefined4 *)((longlong)puVar14 + 0xc);
        puVar14 = (undefined8 *)FUN_7ffe9bda3580(&uStack_88,&uStack_68);
        fStack_90 = *(float *)(puVar14 + 1) * _DAT_7ffe9c049d68;
        uStack_98 = CONCAT44((float)((ulonglong)*puVar14 >> 0x20) * _DAT_7ffe9c049d68,
                             (float)*puVar14 * _DAT_7ffe9c049d68);
        fStack_60 = fStack_90;
        plVar15 = (longlong *)func_0x7ffe9bda34a0(&uStack_a8,&uStack_98);
        uStack_68 = *plVar15;
        fStack_60 = (float)plVar15[1];
        if (*(longlong *)(self + 0x38) != 0) {
          FUN_7ffe99b23050(*(longlong *)(self + 0x38),0);
          lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c9530b0);
          if (lVar13 != 0) {
            uVar16 = FUN_7ffe99ab2b10(lVar13,0);
            lVar13 = FUN_7ffe9bd7a830(0);
            if ((lVar13 != 0) && (lVar13 = FUN_7ffe9bd98a10(lVar13,0), lVar13 != 0)) {
              puVar14 = (undefined8 *)FUN_7ffe9bdbf760(&uStack_88,lVar13);
              uStack_b8 = *puVar14;
              fStack_b0 = *(float *)(puVar14 + 1);
              lVar13 = FUN_7ffe9bd7a830(0);
              if ((lVar13 != 0) && (lVar13 = FUN_7ffe9bd98a10(lVar13,0), lVar13 != 0)) {
                puVar14 = (undefined8 *)FUN_7ffe9bdbf190(&uStack_88,lVar13);
                fStackX_c = (float)((ulonglong)uVar16 >> 0x20);
                fStackX_8 = (float)uVar16;
                lVar13 = *(longlong *)(self + 0x38);
                uStack_98 = *puVar14;
                fStack_90 = *(float *)(puVar14 + 1);
                fStack_a0 = fStackX_c * fStack_90 + fStackX_8 * fStack_b0;
                uStack_a8 = (ulonglong)
                            (uint)(fStackX_c * (float)uStack_98 + fStackX_8 * (float)uStack_b8);
                lVar17 = FUN_7ffe9bd98a10(self,0);
                if (lVar17 != 0) {
                  puVar14 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_88,lVar17);
                  uVar16 = *puVar14;
                  fStack_80 = *(float *)(puVar14 + 1);
                  puVar14 = (undefined8 *)FUN_7ffe999fca00(&uStack_98,&uStack_a8);
                  uVar3 = *puVar14;
                  fStack_90 = *(float *)(puVar14 + 1);
                  fVar21 = (float)func_0x7ffe99a4d6a0(_DAT_7ffe9c049d14,0);
                  fStack_b0 = fStack_80 + fStack_90 * fVar21;
                  uStack_b8 = CONCAT44((float)((ulonglong)uVar16 >> 0x20) +
                                       (float)((ulonglong)uVar3 >> 0x20) * fVar21,
                                       (float)uVar16 + (float)uVar3 * fVar21);
                  uStack_98 = uVar3;
                  uStack_88 = uVar16;
                  if (lVar13 != 0) {
                    uStack_88 = uStack_b8;
                    fStack_80 = fStack_b0;
                    FUN_7ffe99b1fa90(lVar13,&uStack_88,0,0,
                                     (ulonglong)in_stack_ffffffffffffff28 & 0xffffffffffffff00,0);
                    lVar13 = *(longlong *)(self + 0x38);
                    if (lVar13 != 0) {
                      lVar17 = *(longlong *)(lVar13 + 0x30);
                      lVar13 = FUN_7ffe9bd98a10(lVar13,0);
                      if ((lVar13 != 0) &&
                         (puVar14 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_98,lVar13), lVar17 != 0))
                      {
                        uStack_88 = *puVar14;
                        fStack_80 = *(float *)(puVar14 + 1);
                        cVar9 = FUN_7ffe9a876820(lVar17,&uStack_88,_DAT_7ffe9c049ec8,&uStack_78,0);
                        if (*(longlong *)(self + 0x38) != 0) {
                          puVar11 = (undefined *)FUN_7ffe9bd98a10(*(longlong *)(self + 0x38),0);
                          bVar10 = AvoidActionManager_CheckMobAttackArea
                                             (self,puVar11,(undefined *)0x0);
                          if ((*(longlong *)(self + 0x38) != 0) &&
                             (lVar13 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x38),0), lVar13 != 0))
                          {
                            uStack_88 = uVar2;
                            fStack_80 = fVar7;
                            FUN_7ffe9bdbff60(lVar13,&uStack_88,0);
                            if (*(longlong *)(self + 0x38) != 0) {
                              lVar13 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x38),0);
                              fStack_80 = 0.0;
                              fStack_60 = 0.0;
                              uStack_68 = (ulonglong)(uint)(uStack_68._4_4_ * _DAT_7ffe9c049b38) <<
                                          0x20;
                              plVar15 = (longlong *)FUN_7ffe9bda3450(&uStack_88,&uStack_68,0);
                              if (lVar13 != 0) {
                                uStack_68 = *plVar15;
                                fStack_60 = (float)plVar15[1];
                                uStack_5c = *(undefined4 *)((longlong)plVar15 + 0xc);
                                FUN_7ffe9bdc0000(lVar13,&uStack_68,0);
                                if (*(longlong *)(self + 0x38) != 0) {
                                  FUN_7ffe99b23050(*(longlong *)(self + 0x38),uVar4,0);
                                  if (cVar9 == '\0') {
                                    return 0;
                                  }
                                  return bVar10 == 0;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a7d6aee:
  FUN_7ffe9996d7a0();
  pcVar8 = (code *)swi(3);
  bVar10 = (*pcVar8)();
  return bVar10;
}

