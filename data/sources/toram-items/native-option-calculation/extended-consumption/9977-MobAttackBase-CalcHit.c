
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobAttackBase_CalcHit
               (undefined *self,undefined *damageData,undefined *mobAction,undefined *playerAction,
               undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 *puVar9;
  ushort uVar10;
  undefined *puVar11;
  bool bVar12;
  float necessaryFleePercent;
  float fVar13;
  byte abStackX_10 [8];
  longlong *plStack_58;
  longlong *plStack_50;
  longlong *aplStack_48 [4];
  
  if (DAT_7ffe9cadd7c4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c96dec0);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f64d8);
    FUN_7ffe9996d590(&DAT_7ffe9c92a608);
    FUN_7ffe9996d590(&DAT_7ffe9c92aaa0);
    FUN_7ffe9996d590(&DAT_7ffe9c935a78);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c93f5c8);
    FUN_7ffe9996d590(&DAT_7ffe9c9467e0);
    DAT_7ffe9cadd7c4 = '\x01';
  }
  iVar4 = 0;
  plStack_58 = (longlong *)0x0;
  plStack_50 = (longlong *)0x0;
  aplStack_48[0] = (longlong *)0x0;
  if (damageData == (undefined *)0x0) goto LAB_7ffe9a370468;
  *(undefined8 *)(damageData + 0x1c) = 1;
  bVar2 = MobAttackBase_CheckCriticalPercent(self,mobAction,(undefined *)0x0);
  if (bVar2 != 0) {
    *(undefined4 *)(damageData + 0x1c) = 2;
  }
  if ((((playerAction == (undefined *)0x0) ||
       (plVar7 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
       plVar7 == (longlong *)0x0)) ||
      (lVar8 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0)), lVar8 == 0))
     || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a370468;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x3e6,&plStack_58,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    if (plStack_58 == (longlong *)0x0) goto LAB_7ffe9a370468;
    iVar4 = (**(code **)(*plStack_58 + 0x178))(plStack_58,0x14,*(undefined8 *)(*plStack_58 + 0x180))
    ;
  }
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (((plVar7 == (longlong *)0x0) ||
      (lVar8 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0)), lVar8 == 0))
     || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a370468;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x4c1,&plStack_58,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    if (plStack_58 == (longlong *)0x0) goto LAB_7ffe9a370468;
    iVar5 = (**(code **)(*plStack_58 + 0x178))(plStack_58,0x14,*(undefined8 *)(*plStack_58 + 0x180))
    ;
    iVar4 = iVar4 + iVar5;
  }
  if ((mobAction == (undefined *)0x0) ||
     (lVar8 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction), lVar8 == 0)) goto LAB_7ffe9a370468;
  necessaryFleePercent = (float)FUN_7ffe99744d60(0xe,_DAT_7ffe9c93ed20,lVar8);
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar7 == (longlong *)0x0) ||
     ((lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0)), lVar8 == 0
      || (*(longlong *)(lVar8 + 0x50) == 0)))) goto LAB_7ffe9a370468;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x50),0x321,&plStack_50,_DAT_7ffe9c934418);
  if (cVar3 != '\0') {
    if (plStack_50 == (longlong *)0x0) goto LAB_7ffe9a370468;
    iVar5 = func_0x7ffe9a7a2140(plStack_50,0x32);
    necessaryFleePercent = necessaryFleePercent + (float)iVar5 * _DAT_7ffe9c049b34;
  }
  lVar8 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
  if (lVar8 == 0) goto LAB_7ffe9a370468;
  cVar3 = FUN_7ffe9a2ac880(lVar8,0xe,aplStack_48);
  if ((cVar3 != '\0') && (aplStack_48[0] != (longlong *)0x0)) {
    if ((*(byte *)(_DAT_7ffe9c96dec0 + 0x130) <= *(byte *)(*aplStack_48[0] + 0x130)) &&
       ((*(longlong *)
          (*(longlong *)(*aplStack_48[0] + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c96dec0 + 0x130) * 8) == _DAT_7ffe9c96dec0 &&
        (aplStack_48[0] != (longlong *)0x0)))) {
      fVar13 = (float)func_0x7ffe9a2a77f0(aplStack_48[0],0);
      necessaryFleePercent = necessaryFleePercent - fVar13;
    }
  }
  lVar8 = *(longlong *)mobAction;
  if (((*(byte *)(lVar8 + 0x130) < *(byte *)(_DAT_7ffe9c92a608 + 0x130)) ||
      (*(longlong *)
        (*(longlong *)(lVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c92a608 + 0x130) * 8) !=
       _DAT_7ffe9c92a608)) &&
     ((*(byte *)(lVar8 + 0x130) < *(byte *)(_DAT_7ffe9c92aaa0 + 0x130) ||
      (*(longlong *)
        (*(longlong *)(lVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c92aaa0 + 0x130) * 8) !=
       _DAT_7ffe9c92aaa0)))) {
    if ((*(byte *)(lVar8 + 0x130) < *(byte *)(_DAT_7ffe9c93f5c8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c93f5c8 + 0x130) * 8) !=
        _DAT_7ffe9c93f5c8)) {
      iVar5 = MobAttackBase_CalcFlee(self,(undefined *)0x0);
      plVar7 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar7 == (longlong *)0x0) ||
         (lVar8 = (**(code **)(*plVar7 + 0x1a8))(plVar7,*(undefined8 *)(*plVar7 + 0x1b0)),
         lVar8 == 0)) goto LAB_7ffe9a370468;
      iVar6 = FUN_7ffe99742ec0(0x12,_DAT_7ffe9c940d40,lVar8);
      if ((int)((float)iVar5 * necessaryFleePercent) == 0) {
LAB_7ffe9a370122:
        abStackX_10[0] = 1;
      }
      else {
        iVar4 = iVar4 + 0x4b;
        iVar5 = (int)((float)(iVar6 - (int)((float)iVar5 * necessaryFleePercent)) /
                     _DAT_7ffe9c049b74);
        if (iVar5 < 0) {
          iVar5 = 0;
        }
        else if ((iVar4 < iVar5) && (iVar5 = iVar4, iVar4 < 0)) goto LAB_7ffe9a370122;
        cVar3 = FUN_7ffe9a8fea70(self,100,iVar5);
        abStackX_10[0] = cVar3 == '\0';
      }
    }
    else {
      plVar7 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar7 == (longlong *)0x0) ||
         (lVar8 = (**(code **)(*plVar7 + 0x1a8))(plVar7,*(undefined8 *)(*plVar7 + 0x1b0)),
         lVar8 == 0)) goto LAB_7ffe9a370468;
      iVar5 = FUN_7ffe99742ec0(0x12,_DAT_7ffe9c940d40,lVar8);
      abStackX_10[0] =
           MobAttackBase_checkScoreAttackHit
                     (self,mobAction,necessaryFleePercent,iVar5,iVar4,(undefined *)0x0);
    }
  }
  else {
    plVar7 = (longlong *)
             (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar7 == (longlong *)0x0) ||
       (lVar8 = (**(code **)(*plVar7 + 0x1a8))(plVar7,*(undefined8 *)(*plVar7 + 0x1b0)), lVar8 == 0)
       ) goto LAB_7ffe9a370468;
    iVar5 = FUN_7ffe99742ec0(0x12,_DAT_7ffe9c940d40,lVar8);
    abStackX_10[0] = MobAttackBase_checkHighRaidHit(self,mobAction,iVar5,iVar4,(undefined *)0x0);
  }
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar7 != (longlong *)0x0) &&
     (lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0)), lVar8 != 0))
  {
    cVar3 = FUN_7ffe9a7c6d00(lVar8,0x3d3,0);
    if (cVar3 != '\0') {
      self[0xd5] = 1;
    }
    bVar2 = MobAttackBase_AbsoluteFree
                      (self,playerAction,(undefined *)(ulonglong)*(uint *)(damageData + 0x1c),
                       abStackX_10,(undefined *)0x0);
    if (bVar2 != 0) {
      *(undefined4 *)(damageData + 0x20) = 5;
    }
    bVar2 = MobAttackBase_CheckUnavoidable(self,playerAction,(undefined *)0x0);
    if (abStackX_10[0] == 0) {
      bVar12 = *(int *)(damageData + 0x1c) == 2;
    }
    else {
      bVar12 = true;
    }
    if (bVar2 == 0 && !bVar12) {
      *(undefined4 *)(damageData + 0x1c) = 0;
      if (*(int *)(damageData + 0x20) == 0) {
        *(undefined4 *)(damageData + 0x20) = 1;
        return;
      }
      return;
    }
    cVar3 = (**(code **)(*(longlong *)self + 0x5a8))
                      (self,playerAction,mobAction,*(undefined8 *)(*(longlong *)self + 0x5b0));
    if (cVar3 != '\0') {
      *(undefined4 *)(damageData + 0x1c) = 0;
      *(undefined4 *)(damageData + 0x34) = 1;
      *(undefined4 *)(damageData + 0x20) = 2;
    }
    plVar7 = (longlong *)
             (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (((plVar7 != (longlong *)0x0) &&
        (lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0)), lVar8 != 0
        )) && (*(longlong *)(lVar8 + 0x50) != 0)) {
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x50),1000,&plStack_50,_DAT_7ffe9c934418);
      if (cVar3 != '\0') {
        if ((*(byte *)(*(longlong *)mobAction + 0x130) < *(byte *)(_DAT_7ffe9c8f64d8 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)mobAction + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c8f64d8 + 0x130) * 8) != _DAT_7ffe9c8f64d8)) {
          bVar12 = false;
        }
        else {
          bVar12 = true;
        }
        puVar11 = (undefined *)0x0;
        if (bVar12) {
          puVar11 = mobAction;
        }
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar3 = FUN_7ffe9bda2160(puVar11,0,0);
        if (cVar3 != '\0') {
          if (puVar11 != (undefined *)0x0) {
            if ((puVar11[0x148] != '\0') && (puVar11[0x14a] == '\0')) {
              return;
            }
            plVar7 = (longlong *)
                     func_0x7ffe9996c920(*(undefined8 *)(playerAction + 0x30),_DAT_7ffe9c935a78);
            if (plVar7 == (longlong *)0x0) {
              return;
            }
            lVar8 = *plVar7;
            uVar10 = 0;
            if (*(ushort *)(lVar8 + 0x12e) != 0) {
              do {
                if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + (ulonglong)uVar10 * 0x10) ==
                    _DAT_7ffe9c935a78) {
                  puVar9 = (undefined8 *)
                           ((longlong)
                            (*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10) +
                            2) * 0x10 + 0x138 + lVar8);
                  goto LAB_7ffe9a3703b9;
                }
                uVar10 = uVar10 + 1;
              } while (uVar10 < *(ushort *)(lVar8 + 0x12e));
            }
            puVar9 = (undefined8 *)FUN_7ffe998ce540(plVar7,_DAT_7ffe9c935a78,2);
LAB_7ffe9a3703b9:
            lVar8 = (*(code *)*puVar9)(plVar7,puVar9[1]);
            plVar7 = plStack_50;
            if (lVar8 != 0) {
              if (*(char *)(lVar8 + 0x50) == '\0') {
                return;
              }
              if (plStack_50 != (longlong *)0x0) {
                if (((*(byte *)(_DAT_7ffe9c9467e0 + 0x130) <= *(byte *)(*plStack_50 + 0x130)) &&
                    (*(longlong *)
                      (*(longlong *)(*plStack_50 + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c9467e0 + 0x130) * 8) == _DAT_7ffe9c9467e0)) &&
                   (plStack_50 != (longlong *)0x0)) {
                  cVar3 = func_0x7ffe9a7a1970(plStack_50,0);
                  if (cVar3 != '\0') {
                    *(undefined4 *)(damageData + 0x1c) = 0;
                    *(undefined4 *)(damageData + 0x20) = 6;
                    FUN_7ffe9a7a1980(plVar7,1,0);
                    return;
                  }
                  return;
                }
              }
            }
          }
          goto LAB_7ffe9a370468;
        }
      }
      return;
    }
  }
LAB_7ffe9a370468:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

