
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus___c__get_CutMagicAttack_b__15_0
              (undefined *self,undefined *p,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  int iVar9;
  
  if (p == (undefined *)0x0) {
LAB_7ffe9a330310:
    FUN_7ffe9996d7a0(self);
    pcVar1 = (code *)swi(3);
    iVar9 = (*pcVar1)();
    return iVar9;
  }
  if (*(longlong *)(p + 0x20) != 0) {
    bVar3 = MobPartsStatus_get_IsDead(p,(undefined *)0x0);
    if (bVar3 == 0) {
      lVar6 = *(longlong *)(p + 0x20);
      self = (undefined *)0x0;
      if (lVar6 != 0) {
        if (DAT_7ffe9cadd78d == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c91bd90,0);
          FUN_7ffe9996d590(&DAT_7ffe9c93f2b8);
          FUN_7ffe9996d590(&DAT_7ffe9c968230);
          FUN_7ffe9996d590(&DAT_7ffe9c8f1548);
          DAT_7ffe9cadd78d = '\x01';
        }
        uVar7 = *(undefined8 *)(lVar6 + 0x10);
        if (*(int *)(_DAT_7ffe9c8f1548 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        lVar6 = *(longlong *)(*(longlong *)(_DAT_7ffe9c8f1548 + 0xb8) + 0x10);
        if (lVar6 == 0) {
          if (*(int *)(_DAT_7ffe9c8f1548 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          uVar8 = **(undefined8 **)(_DAT_7ffe9c8f1548 + 0xb8);
          lVar6 = func_0x7ffe99940040(_DAT_7ffe9c93f2b8);
          FUN_7ffe9af15670(lVar6,uVar8,_DAT_7ffe9c968230,0);
          *(longlong *)(*(longlong *)(_DAT_7ffe9c8f1548 + 0xb8) + 0x10) = lVar6;
          il2cpp_write_barrier_0();
        }
        lVar2 = _DAT_7ffe9c91bd90;
        if (*(longlong *)(_DAT_7ffe9c91bd90 + 0x38) == 0) {
          FUN_7ffe998cedc0(_DAT_7ffe9c91bd90);
        }
        lVar6 = FUN_7ffe9ab8c200(uVar7,lVar6,*(undefined8 *)(*(longlong *)(lVar2 + 0x38) + 0x10));
        if (DAT_7ffe9cae459e == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c92bb10,0);
          FUN_7ffe9996d590(&DAT_7ffe9c939b40);
          FUN_7ffe9996d590(&DAT_7ffe9c954838);
          FUN_7ffe9996d590(&DAT_7ffe9c95a168);
          FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
          DAT_7ffe9cae459e = '\x01';
        }
        if (lVar6 == 0) {
          uVar7 = func_0x7ffe9996d5b0(0x7ffe9c94f360);
          uVar7 = FUN_7ffe9b661bf0(uVar7,0);
          uVar8 = func_0x7ffe9996d5b0(&DAT_7ffe9c92bb10);
          FUN_7ffe9996d760(uVar7,uVar8);
LAB_7ffe9b6619ec:
          uVar7 = _DAT_7ffe9c92bb10;
          uVar8 = func_0x7ffe9996d380();
          FUN_7ffe9996d760(uVar8,uVar7);
LAB_7ffe9b661a03:
          FUN_7ffe9996d7a0();
        }
        else {
          iVar9 = 0;
          lVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c954838,lVar6);
          while (lVar6 != 0) {
            cVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
            if (cVar4 == '\0') {
              if (lVar6 != 0) {
                FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
              }
              return iVar9;
            }
            if (lVar6 == 0) goto LAB_7ffe9b661a03;
            iVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c95a168);
            if (0xffffffff < (ulonglong)((longlong)iVar9 + (longlong)iVar5 + 0x80000000))
            goto LAB_7ffe9b6619ec;
            iVar9 = iVar9 + iVar5;
          }
        }
        FUN_7ffe9996d7a0();
        FUN_7ffe998fa550();
        pcVar1 = (code *)swi(3);
        iVar9 = (*pcVar1)();
        return iVar9;
      }
      goto LAB_7ffe9a330310;
    }
  }
  return 0;
}

