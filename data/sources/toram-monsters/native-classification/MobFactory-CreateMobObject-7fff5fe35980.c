
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
MobFactory_CreateMobObject(int mobId,undefined *statusMaster,byte entourage,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined *puVar11;
  longlong lVar12;
  longlong lVar13;
  undefined8 uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  bool bVar18;
  
  if (DAT_7fff625e4cf4 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245da40);
    FUN_7fff5f47d450(&DAT_7fff624661b0);
    FUN_7fff5f47d450(&DAT_7fff623fec70);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff62458e78);
    DAT_7fff625e4cf4 = '\x01';
  }
  puVar11 = (undefined *)FUN_7fff5fe35230(mobId,0);
  if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  cVar3 = FUN_7fff618ab120(puVar11,0);
  if (cVar3 != '\0') {
    return (undefined *)0x0;
  }
  lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
  if (lVar12 != 0) {
    iVar6 = FUN_7fff6037cb10(lVar12,0);
    if (iVar6 == 0) {
      bVar18 = false;
    }
    else {
      lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
      if (lVar12 == 0) goto LAB_7fff5fe35dba;
      iVar6 = FUN_7fff6037cb10(lVar12,0);
      bVar18 = iVar6 != 7;
    }
    bVar4 = FUN_7fff5fe6a760(statusMaster,4);
    bVar4 = bVar4 & bVar18;
    cVar3 = FUN_7fff5fe6a760(statusMaster,0x10);
    uVar17 = 0x100;
    cVar5 = FUN_7fff5fe6a760(statusMaster);
    lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
    if (lVar12 != 0) {
      iVar6 = FUN_7fff6037cb10(lVar12);
      if (iVar6 == 3) {
        uVar15 = 1;
      }
      else {
        lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
        if (lVar12 == 0) goto LAB_7fff5fe35dba;
        iVar6 = FUN_7fff6037cb10(lVar12);
        uVar15 = (uint)(iVar6 == 0x19);
      }
      lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
      if (lVar12 != 0) {
        iVar6 = FUN_7fff6037cb10(lVar12);
        lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
        if (lVar12 != 0) {
          iVar7 = FUN_7fff6037cb10(lVar12);
          lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
          if (lVar12 != 0) {
            iVar8 = FUN_7fff6037cb10(lVar12);
            lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
            if (lVar12 != 0) {
              iVar9 = FUN_7fff6037cb10();
              lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
              if (lVar12 != 0) {
                iVar10 = FUN_7fff6037cb10(lVar12,0);
                if (iVar10 == 0x1d) {
                  uVar16 = 0x8100;
                }
                else {
                  uVar17 = 0;
                  uVar16 = 0x8000;
                }
                if (entourage == 0) {
                  uVar16 = uVar17;
                }
                uVar17 = uVar16 | (uint)(iVar9 == 0x28) << 0xb |
                         (uint)(iVar7 == 0x1a) << 6 | (uint)(iVar6 == 0x13) << 5 | uVar15 * 8 |
                         (uint)bVar4 | -(uint)(cVar5 != '\0') & 4 | -(uint)(cVar3 != '\0') & 2 |
                         (uint)(iVar8 == 0x1c) << 7;
                lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
                if (lVar12 != 0) {
                  iVar6 = FUN_7fff6037cb10(lVar12,0);
                  if ((iVar6 == 0x20) && (uVar17 = bVar4 + 0x200, 0x30da4 < mobId)) {
                    uVar17 = bVar4 + 0x200;
                    if (mobId < 0x30da8) {
                      uVar17 = bVar4 + 0x200 | 0x20;
                    }
                    else if ((0x30e08 < mobId) && (mobId < 0x30e0c)) {
                      uVar17 = uVar17 | 0x8020;
                    }
                  }
                  lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
                  if (lVar12 != 0) {
                    iVar6 = FUN_7fff6037cb10(lVar12,0);
                    if ((iVar6 == 0x12) && (uVar17 = 0x10, mobId != 2)) {
                      uVar17 = 0x11;
                    }
                    lVar12 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
                    if (lVar12 != 0) {
                      iVar6 = FUN_7fff6037cb10(lVar12,0);
                      if ((iVar6 == 0x27) && (uVar17 = 0x400, bVar4 != 0)) {
                        uVar17 = 0x401;
                      }
                      MobFactory_AddComponentMobActionManager
                                (puVar11,(undefined *)(ulonglong)uVar17,(undefined *)0x0);
                      if (puVar11 != (undefined *)0x0) {
                        lVar12 = FUN_7fff606a5d60(puVar11,_DAT_7fff6245da40);
                        lVar13 = FUN_7fff606a6750(puVar11,_DAT_7fff624661b0);
                        if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
                          func_0x7fff5f47d6f0();
                        }
                        cVar3 = FUN_7fff618ab2e0(lVar13,0,0);
                        if (cVar3 == '\0') {
                          return puVar11;
                        }
                        if (lVar13 != 0) {
                          uVar1 = *(undefined8 *)(lVar13 + 0x30);
                          uVar14 = FUN_7fff606a6890(puVar11,1,_DAT_7fff623fec70);
                          if (lVar12 != 0) {
                            FUN_7fff60384e90(lVar12,uVar1,uVar14,0);
                            return puVar11;
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
LAB_7fff5fe35dba:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  puVar11 = (undefined *)(*pcVar2)();
  return puVar11;
}

