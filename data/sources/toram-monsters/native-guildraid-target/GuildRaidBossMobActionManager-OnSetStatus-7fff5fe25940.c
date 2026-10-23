
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobActionManager_OnSetStatus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  undefined *statusMaster;
  undefined *abnormalManager;
  undefined *buffManager;
  code *pcVar2;
  undefined8 uVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  undefined *randomProperty;
  undefined *self_00;
  ulonglong uVar7;
  longlong lVar8;
  undefined8 *puVar9;
  ushort uVar10;
  longlong lVar11;
  uint uVar12;
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
  
  if (DAT_7fff625e4c59 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245a0e0);
    FUN_7fff5f47d450(&DAT_7fff6245a1a8);
    FUN_7fff5f47d450(&DAT_7fff623f8de8);
    FUN_7fff5f47d450(&DAT_7fff624306e0);
    FUN_7fff5f47d450(&DAT_7fff624307a8);
    FUN_7fff5f47d450(0x7fff62430868);
    FUN_7fff5f47d450(&DAT_7fff6242b1b0);
    FUN_7fff5f47d450(&DAT_7fff6242b278);
    FUN_7fff5f47d450(&DAT_7fff6242ba48);
    FUN_7fff5f47d450(&DAT_7fff6243dd98);
    FUN_7fff5f47d450(0x7fff62470e40);
    FUN_7fff5f47d450(0x7fff6246c428);
    FUN_7fff5f47d450(0x7fff6246c4f8);
    FUN_7fff5f47d450(0x7fff62470f08);
    FUN_7fff5f47d450(&DAT_7fff6245c360);
    FUN_7fff5f47d450(&DAT_7fff6246a1a8);
    DAT_7fff625e4c59 = '\x01';
  }
  lStackX_18 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_60 = 0;
  lVar6 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
  if (lVar6 != 0) {
    plVar1 = *(longlong **)(lVar6 + 0x28);
    randomProperty = (undefined *)0x0;
    if (plVar1 != (longlong *)0x0) {
      randomProperty = (undefined *)0x0;
      if ((*(byte *)(_DAT_7fff6242ba48 + 0x130) <= *(byte *)(*plVar1 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff6242ba48 + 0x130) * 8)
          == _DAT_7fff6242ba48)) {
        randomProperty =
             GuildRaidRoomData_GetMobGuildRaidBonus((undefined *)plVar1,(undefined *)0x0);
        GuildRaidRoomData_TryGetAbnormalAdaptation
                  ((undefined *)plVar1,self + 0x194,self + 0x198,self + 0x19c,(undefined *)0x0);
      }
    }
    statusMaster = *(undefined **)(self + 0x70);
    abnormalManager = *(undefined **)(self + 0x80);
    buffManager = *(undefined **)(self + 0x88);
    iVar5 = *(int *)(self + 400);
    self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242b278);
    GuildRaidBossMobBattleStatus__ctor
              (self_00,statusMaster,abnormalManager,buffManager,iVar5,randomProperty,
               (undefined *)0x0);
    *(undefined **)(self + 0x180) = self_00;
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0x180) != 0) {
      *(undefined4 *)(*(longlong *)(self + 0x180) + 0x50) = *(undefined4 *)(self + 0x178);
      if (*(longlong *)(self + 0x180) != 0) {
        *(undefined8 *)(*(longlong *)(self + 0x180) + 0x38) = *(undefined8 *)(self + 0x78);
        thunk_FUN_7fff5f491fd0();
        cVar4 = FUN_7fff60683c50(self,0x5a,&lStackX_18,_DAT_7fff623f8de8);
        if (cVar4 != '\0') {
          if (lStackX_18 == 0) goto LAB_7fff5fe25ea2;
          *(undefined **)(lStackX_18 + 0x18) = self;
          thunk_FUN_7fff5f491fd0();
          if (lStackX_18 == 0) goto LAB_7fff5fe25ea2;
          uVar7 = FUN_7fff5fe85290(lStackX_18,0);
          uStackX_20 = uVar7;
          lVar6 = FUN_7fff60c66630(_DAT_7fff6246a1a8);
          if (lVar6 == 0) goto LAB_7fff5fe25ea2;
          lVar6 = FUN_7fff5fe44150(lVar6,uVar7 & 0xffffffff,0);
          uVar12 = 0;
          if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x18) != 0)) {
            iVar5 = uStackX_20._4_4_;
            lVar11 = _DAT_7fff6242b1b0;
            for (; (int)uVar12 < (int)*(uint *)(lVar6 + 0x18); uVar12 = uVar12 + 1) {
              if (*(uint *)(lVar6 + 0x18) <= uVar12) {
                FUN_7fff5f47d650();
                goto LAB_7fff5fe25e96;
              }
              plVar1 = *(longlong **)(lVar6 + 0x20 + (longlong)(int)uVar12 * 8);
              if (plVar1 == (longlong *)0x0) goto LAB_7fff5fe25ea2;
              if (*(char *)((longlong)plVar1 + 0x151) == '\0') {
                lVar8 = plVar1[0xe];
              }
              else {
                if (plVar1[0x1f] == 0) goto LAB_7fff5fe25ea2;
                lVar8 = FUN_7fff5fe22f70(plVar1[0x1f],0);
                lVar11 = _DAT_7fff6242b1b0;
              }
              if (lVar8 == 0) goto LAB_7fff5fe25ea2;
              if (*(int *)(lVar8 + 0x10) != iVar5) {
                lVar8 = *plVar1;
                if ((*(byte *)(lVar11 + 0x130) <= *(byte *)(lVar8 + 0x130)) &&
                   (*(longlong *)
                     (*(longlong *)(lVar8 + 200) + -8 + (ulonglong)*(byte *)(lVar11 + 0x130) * 8) ==
                    lVar11)) {
                  if (lStackX_18 == 0) goto LAB_7fff5fe25ea2;
                  if ((*(byte *)(lVar8 + 0x130) < *(byte *)(lVar11 + 0x130)) ||
                     (*(longlong *)
                       (*(longlong *)(lVar8 + 200) + -8 + (ulonglong)*(byte *)(lVar11 + 0x130) * 8)
                      != lVar11)) {
                    FUN_7fff5f47c810(plVar1);
                    pcVar2 = (code *)swi(3);
                    (*pcVar2)();
                    return;
                  }
                  *(longlong **)(lStackX_18 + 0x20) = plVar1;
                  thunk_FUN_7fff5f491fd0();
                  lVar11 = _DAT_7fff6242b1b0;
                }
              }
            }
          }
        }
        if (*(longlong *)(self + 0x168) != 0) {
          iVar5 = func_0x7fff607e24e0(*(longlong *)(self + 0x168),_DAT_7fff6245a1a8);
          if (0 < iVar5) {
            if (*(longlong *)(self + 0x168) == 0) goto LAB_7fff5fe25ea2;
            FUN_7fff607d9c20(&uStack_58,*(longlong *)(self + 0x168),_DAT_7fff6245a0e0);
            uStack_80 = uStack_58;
            uStack_78 = uStack_50;
            uStack_70 = uStack_48;
            uStack_68 = uStack_40;
            uStack_60 = uStack_38;
            while (cVar4 = FUN_7fff60941a70(&uStack_80,_DAT_7fff624307a8), uVar3 = uStack_68,
                  cVar4 != '\0') {
              plVar1 = *(longlong **)(self + 0x180);
              uVar7 = uStack_70 & 0xff;
              if (plVar1 == (longlong *)0x0) {
LAB_7fff5fe25e96:
                FUN_7fff5f47d660();
                FUN_7fff5f40a410();
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              lVar6 = *plVar1;
              uVar10 = 0;
              if (*(ushort *)(lVar6 + 0x12e) != 0) {
                do {
                  if (*(longlong *)(*(longlong *)(lVar6 + 0xb0) + (ulonglong)uVar10 * 0x10) ==
                      _DAT_7fff6243dd98) {
                    puVar9 = (undefined8 *)
                             (lVar6 + 0x138 +
                             (longlong)
                             (*(int *)(*(longlong *)(lVar6 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10) +
                             1) * 0x10);
                    goto LAB_7fff5fe25e08;
                  }
                  uVar10 = uVar10 + 1;
                } while (uVar10 < *(ushort *)(lVar6 + 0x12e));
              }
              puVar9 = (undefined8 *)FUN_7fff5f3de400(plVar1,_DAT_7fff6243dd98,1);
LAB_7fff5fe25e08:
              (*(code *)*puVar9)(plVar1,uVar7,uVar3,puVar9[1]);
            }
            GuildRaidRoomData_LoadAsset((undefined *)&uStack_80,_DAT_7fff624306e0);
          }
          return;
        }
      }
    }
  }
LAB_7fff5fe25ea2:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

