
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
MobFactory_CreateMobObject(int mobId,undefined *statusMaster,byte entourage,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined *puVar12;
  longlong lVar13;
  longlong lVar14;
  undefined8 uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  bool bVar19;
  
  if (DAT_7ffe9cadd59c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c956c28);
    FUN_7ffe9996d590(&DAT_7ffe9c95f398);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7d10);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    DAT_7ffe9cadd59c = '\x01';
  }
  puVar12 = (undefined *)FUN_7ffe9a32a560(mobId,0);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda1fa0(puVar12,0);
  if (cVar3 != '\0') {
    return (undefined *)0x0;
  }
  lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
  if (lVar13 != 0) {
    iVar7 = FUN_7ffe9a872680(lVar13,0);
    if (iVar7 == 0) {
      bVar19 = false;
    }
    else {
      lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
      if (lVar13 == 0) goto LAB_7ffe9a32b0ea;
      iVar7 = FUN_7ffe9a872680(lVar13,0);
      bVar19 = iVar7 != 7;
    }
    bVar4 = MobStatusMasterEx_CheckMultiFlag(statusMaster,(undefined *)0x4,(undefined *)0x0);
    bVar4 = bVar4 & bVar19;
    bVar5 = MobStatusMasterEx_CheckMultiFlag(statusMaster,(undefined *)0x10,(undefined *)0x0);
    uVar18 = 0x100;
    bVar6 = MobStatusMasterEx_CheckMultiFlag(statusMaster,(undefined *)0x100,(undefined *)0x0);
    lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar13 != 0) {
      iVar7 = FUN_7ffe9a872680(lVar13);
      if (iVar7 == 3) {
        uVar16 = 1;
      }
      else {
        lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
        if (lVar13 == 0) goto LAB_7ffe9a32b0ea;
        iVar7 = FUN_7ffe9a872680(lVar13);
        uVar16 = (uint)(iVar7 == 0x19);
      }
      lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
      if (lVar13 != 0) {
        iVar7 = FUN_7ffe9a872680(lVar13);
        lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
        if (lVar13 != 0) {
          iVar8 = FUN_7ffe9a872680(lVar13);
          lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
          if (lVar13 != 0) {
            iVar9 = FUN_7ffe9a872680(lVar13);
            lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
            if (lVar13 != 0) {
              iVar10 = FUN_7ffe9a872680();
              lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
              if (lVar13 != 0) {
                iVar11 = FUN_7ffe9a872680(lVar13,0);
                if (iVar11 == 0x1d) {
                  uVar17 = 0x8100;
                }
                else {
                  uVar18 = 0;
                  uVar17 = 0x8000;
                }
                if (entourage == 0) {
                  uVar17 = uVar18;
                }
                uVar18 = uVar17 | (uint)(iVar10 == 0x28) << 0xb |
                         (uint)(iVar8 == 0x1a) << 6 | (uint)(iVar7 == 0x13) << 5 | uVar16 * 8 |
                         (uint)bVar4 | -(uint)(bVar6 != 0) & 4 | -(uint)(bVar5 != 0) & 2 |
                         (uint)(iVar9 == 0x1c) << 7;
                lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
                if (lVar13 != 0) {
                  iVar7 = FUN_7ffe9a872680(lVar13,0);
                  if ((iVar7 == 0x20) && (uVar18 = bVar4 + 0x200, 0x30da4 < mobId)) {
                    uVar18 = bVar4 + 0x200;
                    if (mobId < 0x30da8) {
                      uVar18 = bVar4 + 0x200 | 0x20;
                    }
                    else if ((0x30e08 < mobId) && (mobId < 0x30e0c)) {
                      uVar18 = uVar18 | 0x8020;
                    }
                  }
                  lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
                  if (lVar13 != 0) {
                    iVar7 = FUN_7ffe9a872680(lVar13,0);
                    if ((iVar7 == 0x12) && (uVar18 = 0x10, mobId != 2)) {
                      uVar18 = 0x11;
                    }
                    lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
                    if (lVar13 != 0) {
                      iVar7 = FUN_7ffe9a872680(lVar13,0);
                      if ((iVar7 == 0x27) && (uVar18 = 0x400, bVar4 != 0)) {
                        uVar18 = 0x401;
                      }
                      MobFactory_AddComponentMobActionManager
                                (puVar12,(undefined *)(ulonglong)uVar18,(undefined *)0x0);
                      if (puVar12 != (undefined *)0x0) {
                        lVar13 = FUN_7ffe9ab9b9b0(puVar12,_DAT_7ffe9c956c28);
                        lVar14 = FUN_7ffe9ab9c3a0(puVar12,_DAT_7ffe9c95f398);
                        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                          func_0x7ffe9996d830();
                        }
                        cVar3 = FUN_7ffe9bda2160(lVar14,0,0);
                        if (cVar3 == '\0') {
                          return puVar12;
                        }
                        if (lVar14 != 0) {
                          uVar1 = *(undefined8 *)(lVar14 + 0x30);
                          uVar15 = FUN_7ffe9ab9c4e0(puVar12,1,_DAT_7ffe9c8f7d10);
                          if (lVar13 != 0) {
                            FUN_7ffe9a87aa00(lVar13,uVar1,uVar15,0);
                            return puVar12;
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
LAB_7ffe9a32b0ea:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  puVar12 = (undefined *)(*pcVar2)();
  return puVar12;
}

