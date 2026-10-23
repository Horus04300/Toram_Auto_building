
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobActionManager_OnSetStatus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  undefined *statusMaster;
  undefined *abnormalManager;
  undefined *buffManager;
  longlong lVar2;
  code *pcVar3;
  undefined8 uVar4;
  char cVar5;
  int iVar6;
  longlong lVar7;
  undefined *puVar8;
  undefined *self_00;
  ulonglong uVar9;
  undefined8 *puVar10;
  ushort uVar11;
  longlong lVar12;
  uint uVar13;
  longlong lStackX_18;
  undefined8 uStackX_20;
  undefined8 uStack_80;
  undefined8 uStack_78;
  ulonglong uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  ulonglong uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  if (DAT_7ffe9cadd501 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9531f8);
    FUN_7ffe9996d590(&DAT_7ffe9c9532c8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1e88);
    FUN_7ffe9996d590(&DAT_7ffe9c929768);
    FUN_7ffe9996d590(&DAT_7ffe9c929830);
    FUN_7ffe9996d590(0x7ffe9c9298f8);
    FUN_7ffe9996d590(&DAT_7ffe9c923808);
    FUN_7ffe9996d590(&DAT_7ffe9c9238d0);
    FUN_7ffe9996d590(&DAT_7ffe9c9240a0);
    FUN_7ffe9996d590(&DAT_7ffe9c936530);
    FUN_7ffe9996d590(0x7ffe9c969f58);
    FUN_7ffe9996d590(0x7ffe9c965548);
    FUN_7ffe9996d590(0x7ffe9c965610);
    FUN_7ffe9996d590(0x7ffe9c96a028);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    DAT_7ffe9cadd501 = '\x01';
  }
  lStackX_18 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_60 = 0;
  lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar7 != 0) {
    plVar1 = *(longlong **)(lVar7 + 0x28);
    puVar8 = (undefined *)0x0;
    if (plVar1 != (longlong *)0x0) {
      puVar8 = (undefined *)0x0;
      if ((*(byte *)(_DAT_7ffe9c9240a0 + 0x130) <= *(byte *)(*plVar1 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9240a0 + 0x130) * 8)
          == _DAT_7ffe9c9240a0)) {
        puVar8 = GuildRaidRoomData_GetMobGuildRaidBonus((undefined *)plVar1,(undefined *)0x0);
        FUN_7ffe9a5d6850(plVar1,self + 0x194,self + 0x198,self + 0x19c,0);
      }
    }
    statusMaster = *(undefined **)(self + 0x70);
    abnormalManager = *(undefined **)(self + 0x80);
    buffManager = *(undefined **)(self + 0x88);
    iVar6 = *(int *)(self + 400);
    self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c9238d0);
    GuildRaidBossMobBattleStatus__ctor
              (self_00,statusMaster,abnormalManager,buffManager,iVar6,puVar8,(undefined *)0x0);
    *(undefined **)(self + 0x180) = self_00;
    il2cpp_write_barrier_0();
    if (*(longlong *)(self + 0x180) != 0) {
      *(undefined4 *)(*(longlong *)(self + 0x180) + 0x50) = *(undefined4 *)(self + 0x178);
      if (*(longlong *)(self + 0x180) != 0) {
        *(undefined8 *)(*(longlong *)(self + 0x180) + 0x38) = *(undefined8 *)(self + 0x78);
        il2cpp_write_barrier_0();
        cVar5 = FUN_7ffe9ab798a0(self,0x5a,&lStackX_18,_DAT_7ffe9c8f1e88);
        if (cVar5 != '\0') {
          if (lStackX_18 == 0) goto LAB_7ffe9a31b1d2;
          *(undefined **)(lStackX_18 + 0x18) = self;
          il2cpp_write_barrier_0();
          if (lStackX_18 == 0) goto LAB_7ffe9a31b1d2;
          uVar9 = FUN_7ffe9a37a6e0(lStackX_18,0);
          uStackX_20 = uVar9;
          lVar7 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (lVar7 == 0) goto LAB_7ffe9a31b1d2;
          lVar7 = FUN_7ffe9a339480(lVar7,uVar9 & 0xffffffff,0);
          uVar13 = 0;
          if ((lVar7 != 0) && (*(longlong *)(lVar7 + 0x18) != 0)) {
            iVar6 = uStackX_20._4_4_;
            lVar12 = _DAT_7ffe9c923808;
            for (; (int)uVar13 < (int)*(uint *)(lVar7 + 0x18); uVar13 = uVar13 + 1) {
              if (*(uint *)(lVar7 + 0x18) <= uVar13) {
                FUN_7ffe9996d790();
                goto LAB_7ffe9a31b1c6;
              }
              plVar1 = *(longlong **)(lVar7 + 0x20 + (longlong)(int)uVar13 * 8);
              if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a31b1d2;
              if (*(char *)((longlong)plVar1 + 0x151) == '\0') {
                puVar8 = (undefined *)plVar1[0xe];
              }
              else {
                if ((undefined *)plVar1[0x1f] == (undefined *)0x0) goto LAB_7ffe9a31b1d2;
                puVar8 = EnemyMobActionManagerBase_get_MobStatusMaster
                                   ((undefined *)plVar1[0x1f],(undefined *)0x0);
                lVar12 = _DAT_7ffe9c923808;
              }
              if (puVar8 == (undefined *)0x0) goto LAB_7ffe9a31b1d2;
              if (*(int *)(puVar8 + 0x10) != iVar6) {
                lVar2 = *plVar1;
                if ((*(byte *)(lVar12 + 0x130) <= *(byte *)(lVar2 + 0x130)) &&
                   (*(longlong *)
                     (*(longlong *)(lVar2 + 200) + -8 + (ulonglong)*(byte *)(lVar12 + 0x130) * 8) ==
                    lVar12)) {
                  if (lStackX_18 == 0) goto LAB_7ffe9a31b1d2;
                  if ((*(byte *)(lVar2 + 0x130) < *(byte *)(lVar12 + 0x130)) ||
                     (*(longlong *)
                       (*(longlong *)(lVar2 + 200) + -8 + (ulonglong)*(byte *)(lVar12 + 0x130) * 8)
                      != lVar12)) {
                    FUN_7ffe9996c950(plVar1);
                    pcVar3 = (code *)swi(3);
                    (*pcVar3)();
                    return;
                  }
                  *(longlong **)(lStackX_18 + 0x20) = plVar1;
                  il2cpp_write_barrier_0();
                  lVar12 = _DAT_7ffe9c923808;
                }
              }
            }
          }
        }
        if (*(longlong *)(self + 0x168) != 0) {
          iVar6 = func_0x7ffe9acd8120(*(longlong *)(self + 0x168),_DAT_7ffe9c9532c8);
          if (0 < iVar6) {
            if (*(longlong *)(self + 0x168) == 0) goto LAB_7ffe9a31b1d2;
            FUN_7ffe9accf860(&uStack_58,*(longlong *)(self + 0x168),_DAT_7ffe9c9531f8);
            uStack_80 = uStack_58;
            uStack_78 = uStack_50;
            uStack_70 = uStack_48;
            uStack_68 = uStack_40;
            uStack_60 = uStack_38;
            while (cVar5 = FUN_7ffe9ae376b0(&uStack_80,_DAT_7ffe9c929830), uVar4 = uStack_68,
                  cVar5 != '\0') {
              plVar1 = *(longlong **)(self + 0x180);
              uVar9 = uStack_70 & 0xff;
              if (plVar1 == (longlong *)0x0) {
LAB_7ffe9a31b1c6:
                FUN_7ffe9996d7a0();
                FUN_7ffe998fa550();
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              lVar7 = *plVar1;
              uVar11 = 0;
              if (*(ushort *)(lVar7 + 0x12e) != 0) {
                do {
                  if (*(longlong *)(*(longlong *)(lVar7 + 0xb0) + (ulonglong)uVar11 * 0x10) ==
                      _DAT_7ffe9c936530) {
                    puVar10 = (undefined8 *)
                              (lVar7 + 0x138 +
                              (longlong)
                              (*(int *)(*(longlong *)(lVar7 + 0xb0) + 8 + (ulonglong)uVar11 * 0x10)
                              + 1) * 0x10);
                    goto LAB_7ffe9a31b138;
                  }
                  uVar11 = uVar11 + 1;
                } while (uVar11 < *(ushort *)(lVar7 + 0x12e));
              }
              puVar10 = (undefined8 *)FUN_7ffe998ce540(plVar1,_DAT_7ffe9c936530,1);
LAB_7ffe9a31b138:
              (*(code *)*puVar10)(plVar1,uVar9,uVar4,puVar10[1]);
            }
            func_0x7ffe999c3920(&uStack_80,_DAT_7ffe9c929768);
          }
          return;
        }
      }
    }
  }
LAB_7ffe9a31b1d2:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

