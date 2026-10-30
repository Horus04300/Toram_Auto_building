
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UITreasureHuntEnterManager_UIinit(undefined *self,undefined *methodInfo)

{
  float fVar1;
  bool bVar2;
  code *pcVar3;
  float fVar4;
  char cVar5;
  int iVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  longlong lVar12;
  undefined8 *puVar13;
  longlong lVar14;
  uint uVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined4 auStackX_8 [2];
  float fVar19;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined8 uStack_88;
  float fStack_80;
  undefined8 uStack_78;
  float fStack_70;
  undefined1 auStack_68 [8];
  float fStack_60;
  undefined1 auStack_58 [48];
  
  if (DAT_7ffe9cadab7c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94d6a8);
    FUN_7ffe9996d590(&DAT_7ffe9c96df68);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c93a5d8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c953578);
    FUN_7ffe9996d590(&DAT_7ffe9c960dc8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3bf8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3cc8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3d98);
    FUN_7ffe9996d590(&DAT_7ffe9c908a60);
    FUN_7ffe9996d590(&DAT_7ffe9c91f060);
    FUN_7ffe9996d590(&DAT_7ffe9c929748);
    FUN_7ffe9996d590(&DAT_7ffe9c92ff50);
    FUN_7ffe9996d590(&DAT_7ffe9c915ff8);
    FUN_7ffe9996d590(&DAT_7ffe9c929810);
    DAT_7ffe9cadab7c = '\x01';
  }
  uVar15 = 0;
  if (*(longlong *)(self + 0x20) == 0) {
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c953578);
    uVar10 = uStack_78;
    fVar1 = fStack_70;
    if (lVar7 == 0) goto LAB_7ffe99c73e5d;
    plVar8 = (longlong *)FUN_7ffe99a4aed0(lVar7,0,0);
    if (plVar8 == (longlong *)0x0) {
      *(undefined8 *)(self + 0x20) = 0;
    }
    else {
      if ((*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8)
          != _DAT_7ffe9c960dc8)) {
        FUN_7ffe9996c950(plVar8);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      *(longlong **)(self + 0x20) = plVar8;
      if ((*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8)
          != _DAT_7ffe9c960dc8)) {
        FUN_7ffe9996c950(plVar8);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
    il2cpp_write_barrier_0();
  }
  lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
  uVar10 = uStack_78;
  fVar1 = fStack_70;
  if (lVar7 == 0) goto LAB_7ffe99c73e5d;
  cVar5 = FUN_7ffe9a5a4650(lVar7,0);
  if (cVar5 == '\0') {
    uVar10 = *(undefined8 *)(self + 0x70);
LAB_7ffe99c73642:
    uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8f3bf8);
    FUN_7ffe99c6f160(uVar9,uVar10,0);
  }
  else {
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    uVar10 = uStack_78;
    fVar1 = fStack_70;
    if (lVar7 == 0) goto LAB_7ffe99c73e5d;
    cVar5 = FUN_7ffe9a5a4230(lVar7,0);
    uVar10 = *(undefined8 *)(self + 0x70);
    if (cVar5 != '\0') goto LAB_7ffe99c73642;
    uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8f3d98);
    FUN_7ffe99c751c0(uVar9,uVar10,0);
  }
  *(undefined8 *)(self + 0x168) = uVar9;
  il2cpp_write_barrier_0();
  uVar10 = uStack_78;
  fVar1 = fStack_70;
  if (*(longlong *)(self + 0x40) != 0) {
    uVar10 = FUN_7ffe9ab9c3a0(*(longlong *)(self + 0x40),_DAT_7ffe9c96df68);
    *(undefined8 *)(self + 0x48) = uVar10;
    il2cpp_write_barrier_0();
    FUN_7ffe99c6ffa0(self,0,0);
    uVar10 = uStack_78;
    fVar1 = fStack_70;
    if (self[0x150] == '\0') {
      if ((*(longlong *)(self + 0xb8) != 0) &&
         (lVar7 = FUN_7ffe9bd98960(*(longlong *)(self + 0xb8),0), uVar10 = uStack_78,
         fVar1 = fStack_70, lVar7 != 0)) {
        FUN_7ffe9bd9b390(lVar7,1,0);
        uVar10 = uStack_78;
        fVar1 = fStack_70;
        if (*(longlong *)(self + 0x90) != 0) {
          FUN_7ffe9bd9b390(*(longlong *)(self + 0x90),1,0);
          uVar10 = uStack_78;
          fVar1 = fStack_70;
          if (*(longlong *)(self + 0x98) != 0) {
            FUN_7ffe9bd9b390(*(longlong *)(self + 0x98),1,0);
            uVar10 = uStack_78;
            fVar1 = fStack_70;
            if (((*(longlong *)(self + 0x178) != 0) &&
                (plVar8 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x178),0),
                uVar10 = uStack_78, fVar1 = fStack_70, plVar8 != (longlong *)0x0)) &&
               (lVar7 = (**(code **)(*plVar8 + 0x1a8))(plVar8,*(undefined8 *)(*plVar8 + 0x1b0)),
               uVar10 = uStack_78, fVar1 = fStack_70, lVar7 != 0)) {
              iVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar7);
              uVar10 = _DAT_7ffe9c91f060;
              if (*(int *)(self + 400) <= iVar6) {
                uVar10 = _DAT_7ffe9c915ff8;
              }
              lVar7 = *(longlong *)(self + 0x58);
              if (*(longlong *)(self + 0x20) != 0) {
                uVar9 = FUN_7ffe99a58320(*(longlong *)(self + 0x20),_DAT_7ffe9c908a60,0);
                auStackX_8[0] = *(undefined4 *)(self + 400);
                uVar11 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,auStackX_8);
                uVar9 = FUN_7ffe9b36a740(uVar9,uVar11,0);
                uVar10 = FUN_7ffe9b3675b0(uVar10,uVar9,0);
                if (lVar7 != 0) {
                  FUN_7ffe9a404310(lVar7,uVar10,0);
                  lVar7 = *(longlong *)(self + 0xb8);
                  lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c953578);
                  if ((lVar12 != 0) &&
                     (uVar10 = FUN_7ffe99a4a410(lVar12,0,*(undefined4 *)(self + 0x188),0),
                     lVar7 != 0)) {
                    FUN_7ffe9a404310(lVar7,uVar10,0);
                    lVar7 = *(longlong *)(self + 0x68);
                    if ((*(longlong *)(self + 0x20) != 0) &&
                       (uVar10 = FUN_7ffe99a58320(*(longlong *)(self + 0x20),_DAT_7ffe9c92ff50,0),
                       lVar7 != 0)) {
                      FUN_7ffe9a404310(lVar7,uVar10,0);
                      if (*(longlong *)(self + 0x60) != 0) {
                        FUN_7ffe999f2150(*(longlong *)(self + 0x60),self[0x150] == '\0',0);
                        if ((*(longlong *)(self + 0x60) != 0) &&
                           (lVar7 = FUN_7ffe9ab6e450(*(longlong *)(self + 0x60),_DAT_7ffe9c94d6a8),
                           lVar7 != 0)) {
                          if (*(uint *)(lVar7 + 0x18) < 2) {
                            FUN_7ffe9996d790();
                            pcVar3 = (code *)swi(3);
                            (*pcVar3)();
                            return;
                          }
                          if ((*(longlong *)(lVar7 + 0x28) != 0) &&
                             (lVar7 = FUN_7ffe9bd98960(*(longlong *)(lVar7 + 0x28),0), lVar7 != 0))
                          {
                            FUN_7ffe9bd9b390(lVar7,0,0);
                            if (*(longlong *)(self + 0x180) != 0) {
                              *(undefined8 *)(self + 0x198) =
                                   *(undefined8 *)(*(longlong *)(self + 0x180) + 0xe0);
                              il2cpp_write_barrier_0();
                              if ((*(longlong *)(self + 0xd8) != 0) &&
                                 (lVar7 = FUN_7ffe9bd9b890(*(longlong *)(self + 0xd8),0), lVar7 != 0
                                 )) {
                                puVar13 = (undefined8 *)FUN_7ffe9bdbf710(auStack_68,lVar7,0);
                                uVar9 = *puVar13;
                                fVar17 = (float)uVar9;
                                fVar18 = (float)((ulonglong)uVar9 >> 0x20);
                                fVar16 = *(float *)(puVar13 + 1);
                                if (*(longlong *)(self + 0xd8) != 0) {
                                  fVar19 = fVar16;
                                  FUN_7ffe9bd9b390(*(longlong *)(self + 0xd8),1,0);
                                  fVar4 = _DAT_7ffe9c049cf4;
                                  while( true ) {
                                    if (*(int *)(_DAT_7ffe9c8f3cc8 + 0xe0) == 0) {
                                      func_0x7ffe9996d830(_DAT_7ffe9c8f3cc8);
                                    }
                                    lVar7 = *(longlong *)(self + 0xd8);
                                    if (*(int *)(*(longlong *)(_DAT_7ffe9c8f3cc8 + 0xb8) + 0x20) <=
                                        (int)uVar15) break;
                                    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                      func_0x7ffe9996d830();
                                    }
                                    lVar7 = FUN_7ffe9abbb520(lVar7,_DAT_7ffe9c93a5d8);
                                    uVar10 = uStack_78;
                                    fVar1 = fStack_70;
                                    if (lVar7 == 0) goto LAB_7ffe99c73e5d;
                                    lVar12 = FUN_7ffe9bd9b890(lVar7,0);
                                    uVar10 = uStack_78;
                                    fVar1 = fStack_70;
                                    if (((*(longlong *)(self + 0xd8) == 0) ||
                                        (lVar14 = FUN_7ffe9bd9b890(*(longlong *)(self + 0xd8),0),
                                        uVar10 = uStack_78, fVar1 = fStack_70, lVar14 == 0)) ||
                                       (uVar11 = FUN_7ffe9bdbdeb0(lVar14,0), uVar10 = uStack_78,
                                       fVar1 = fStack_70, lVar12 == 0)) goto LAB_7ffe99c73e5d;
                                    FUN_7ffe9bdbfe50(lVar12,uVar11);
                                    lVar12 = FUN_7ffe9bd9b890(lVar7,0);
                                    uVar10 = uStack_78;
                                    fVar1 = fStack_70;
                                    if (((*(longlong *)(self + 0xd8) == 0) ||
                                        (lVar14 = FUN_7ffe9bd9b890(*(longlong *)(self + 0xd8),0),
                                        uVar10 = uStack_78, fVar1 = fStack_70, lVar14 == 0)) ||
                                       (puVar13 = (undefined8 *)FUN_7ffe9bdbf520(auStack_58,lVar14),
                                       uVar10 = uStack_78, fVar1 = fStack_70, lVar12 == 0))
                                    goto LAB_7ffe99c73e5d;
                                    uStack_98 = *puVar13;
                                    uStack_90 = *(undefined4 *)(puVar13 + 1);
                                    FUN_7ffe9bdbfe00(lVar12,&uStack_98);
                                    lVar12 = FUN_7ffe9bd9b890(lVar7,0);
                                    uVar10 = uStack_78;
                                    fVar1 = fStack_70;
                                    if (lVar12 == 0) goto LAB_7ffe99c73e5d;
                                    uStack_88 = CONCAT44(fVar18,fVar17);
                                    fStack_80 = fVar16;
                                    FUN_7ffe9bdbfcc0(lVar12,&uStack_88);
                                    FUN_7ffe9bd9b390(lVar7,(int)uVar15 <
                                                           (int)((uint)(byte)self[0x194] -
                                                                (uint)(byte)self[0x195]));
                                    if (DAT_7ffe9cad9c13 == '\0') {
                                      FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                                      DAT_7ffe9cad9c13 = '\x01';
                                    }
                                    uStack_78 = *(undefined8 *)
                                                 (*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x3c);
                                    fStack_70 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) +
                                                          0x44);
                                    fVar16 = fVar19 + fStack_70 * fVar4;
                                    fVar17 = (float)uVar9 + (float)uStack_78 * fVar4;
                                    fVar18 = (float)((ulonglong)uVar9 >> 0x20) +
                                             (float)((ulonglong)uStack_78 >> 0x20) * fVar4;
                                    lVar12 = *(longlong *)(self + 0x1d8);
                                    uVar9 = CONCAT44(fVar18,fVar17);
                                    uVar10 = uStack_78;
                                    fVar1 = fStack_70;
                                    fStack_60 = fVar16;
                                    if (lVar12 == 0) goto LAB_7ffe99c73e5d;
                                    if (*(uint *)(lVar12 + 0x18) <= uVar15) {
                                      FUN_7ffe9996d790((longlong)(int)uVar15,fVar17,fVar18,
                                                       fStack_70 * fVar4,uVar9,fVar16);
                                      pcVar3 = (code *)swi(3);
                                      (*pcVar3)();
                                      return;
                                    }
                                    *(longlong *)(lVar12 + 0x20 + (longlong)(int)uVar15 * 8) = lVar7
                                    ;
                                    fVar19 = fVar16;
                                    il2cpp_write_barrier_0();
                                    uVar15 = uVar15 + 1;
                                  }
                                  uVar10 = uStack_78;
                                  fVar1 = fStack_70;
                                  if (lVar7 != 0) {
                                    FUN_7ffe9bd9b390(lVar7,0,0);
                                    FUN_7ffe99c73050(self,0);
                                    uVar10 = uStack_78;
                                    fVar1 = fStack_70;
                                    if (*(longlong *)(self + 0xa0) != 0) {
                                      FUN_7ffe9bd9b390(*(longlong *)(self + 0xa0),1,0);
                                      bVar2 = (int)((uint)(byte)self[0x194] -
                                                   (uint)(byte)self[0x195]) < 1;
                                      uVar10 = uStack_78;
                                      fVar1 = fStack_70;
                                      if ((*(longlong *)(self + 0xe0) != 0) &&
                                         (lVar7 = FUN_7ffe9bd98960(*(longlong *)(self + 0xe0),0),
                                         uVar10 = uStack_78, fVar1 = fStack_70, lVar7 != 0)) {
                                        FUN_7ffe9bd9b390(lVar7,bVar2,0);
                                        uVar10 = uStack_78;
                                        fVar1 = fStack_70;
                                        if (*(longlong *)(self + 0xe0) != 0) {
                                          FUN_7ffe999f2150(*(longlong *)(self + 0xe0),bVar2,0);
                                          uVar9 = _DAT_7ffe9c929748;
                                          if (*(int *)(self + 0x1e4) == 0) {
                                            uVar9 = _DAT_7ffe9c929810;
                                          }
                                          lVar7 = *(longlong *)(self + 0xe8);
                                          uVar10 = uStack_78;
                                          fVar1 = fStack_70;
                                          if ((*(longlong *)(self + 0x20) != 0) &&
                                             (uVar9 = FUN_7ffe99a58320(*(longlong *)(self + 0x20),
                                                                       uVar9,0), uVar10 = uStack_78,
                                             fVar1 = fStack_70, lVar7 != 0)) {
                                            FUN_7ffe9a404310(lVar7,uVar9,0);
                                            FUN_7ffe99c72de0(self,0);
                                            FUN_7ffe99c6f1d0(self,0);
                                            self[0x170] = 1;
                                            uVar10 = uStack_78;
                                            fVar1 = fStack_70;
                                            if ((*(longlong *)(self + 0x38) != 0) &&
                                               (lVar7 = FUN_7ffe9bd98960(*(longlong *)(self + 0x38),
                                                                         0), uVar10 = uStack_78,
                                               fVar1 = fStack_70, lVar7 != 0)) {
                                              FUN_7ffe9bd9b390(lVar7,1,0);
                                              lVar7 = *(longlong *)(self + 0x38);
                                              if (DAT_7ffe9cad9ca8 == '\0') {
                                                FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                                                DAT_7ffe9cad9ca8 = '\x01';
                                              }
                                              uVar10 = *(undefined8 *)
                                                        (*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) +
                                                        0x30);
                                              fVar1 = *(float *)(*(longlong *)
                                                                  (_DAT_7ffe9c8fc068 + 0xb8) + 0x38)
                                              ;
                                              fStack_70 = fVar1 * _DAT_7ffe9c049da4;
                                              uStack_78 = CONCAT44((float)((ulonglong)uVar10 >> 0x20
                                                                          ) * _DAT_7ffe9c049da4,
                                                                   (float)uVar10 * _DAT_7ffe9c049da4
                                                                  );
                                              if (lVar7 != 0) {
                                                FUN_7ffe99a0ed20(lVar7,&uStack_78,_DAT_7ffe9c049cc0,
                                                                 0);
                                                return;
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                  goto LAB_7ffe99c73e5d;
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
              FUN_7ffe9996d7a0();
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
          }
        }
      }
    }
    else if ((*(longlong *)(self + 0x38) != 0) &&
            (lVar7 = FUN_7ffe9bd98960(*(longlong *)(self + 0x38),0), uVar10 = uStack_78,
            fVar1 = fStack_70, lVar7 != 0)) {
      FUN_7ffe9bd9b390(lVar7,1,0);
      lVar7 = *(longlong *)(self + 0x38);
      if (DAT_7ffe9cad9ca8 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
        DAT_7ffe9cad9ca8 = '\x01';
      }
      uVar10 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x30);
      fVar1 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x38);
      fStack_70 = fVar1 * _DAT_7ffe9c049da4;
      uStack_78 = CONCAT44((float)((ulonglong)uVar10 >> 0x20) * _DAT_7ffe9c049da4,
                           (float)uVar10 * _DAT_7ffe9c049da4);
      if (lVar7 != 0) {
        FUN_7ffe99a0ed20(lVar7,&uStack_78,_DAT_7ffe9c049b40,0);
        self[0x170] = 1;
        return;
      }
    }
  }
LAB_7ffe99c73e5d:
  fStack_70 = fVar1;
  uStack_78 = uVar10;
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

