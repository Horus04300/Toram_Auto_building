
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PhysicalPursuit_Calc
              (undefined *self,int value,undefined *playerAct,undefined *mobAct,
              undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined4 in_register_00000014;
  int iVar10;
  longlong lStackX_8;
  longlong *aplStack_28 [2];
  
  if (DAT_7ffe9cade245 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418,CONCAT44(in_register_00000014,value));
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7560);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    DAT_7ffe9cade245 = '\x01';
  }
  aplStack_28[0] = (longlong *)0x0;
  lStackX_8 = 0;
  if (self[0x12] == '\0') {
    return 0;
  }
  iVar10 = 0x19;
  if ((((playerAct == (undefined *)0x0) ||
       (plVar7 = (longlong *)
                 (**(code **)(*(longlong *)playerAct + 0x298))
                           (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0)),
       plVar7 == (longlong *)0x0)) ||
      (lVar8 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0)), lVar8 == 0))
     || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a52cfea;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x1ed,aplStack_28,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    if (aplStack_28[0] == (longlong *)0x0) goto LAB_7ffe9a52cfea;
    iVar10 = (**(code **)(*aplStack_28[0] + 0x178))
                       (aplStack_28[0],0x1b,*(undefined8 *)(*aplStack_28[0] + 0x180));
    iVar10 = iVar10 + 0x19;
    plVar7 = (longlong *)
             (**(code **)(*(longlong *)playerAct + 0x298))
                       (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
    if ((plVar7 == (longlong *)0x0) ||
       (lVar8 = (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220)), lVar8 == 0)
       ) goto LAB_7ffe9a52cfea;
    cVar3 = FUN_7ffe9a5b20c0(lVar8,0x3f2,0);
    if (cVar3 != '\0') {
      if ((aplStack_28[0] == (longlong *)0x0) || (aplStack_28[0][2] == 0)) goto LAB_7ffe9a52cfea;
      iVar10 = iVar10 + (uint)*(byte *)(aplStack_28[0][2] + 0x18);
    }
  }
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)playerAct + 0x298))
                     (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
  if (((plVar7 != (longlong *)0x0) &&
      (lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0)), lVar8 != 0))
     && (*(longlong *)(lVar8 + 0x50) != 0)) {
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x50),0x448,&lStackX_8);
    if (cVar3 != '\0') {
      if (lStackX_8 == 0) goto LAB_7ffe9a52cfea;
      iVar4 = func_0x7ffe9a7a2140(lStackX_8,0x34);
      iVar10 = iVar10 + iVar4;
    }
    plVar7 = (longlong *)
             (**(code **)(*(longlong *)playerAct + 0x298))
                       (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
    if ((plVar7 != (longlong *)0x0) &&
       (lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0)), lVar8 != 0)
       ) {
      cVar3 = FUN_7ffe9a7cbb30(lVar8,0x3d3,&lStackX_8);
      if (cVar3 != '\0') {
        plVar7 = (longlong *)
                 (**(code **)(*(longlong *)playerAct + 0x298))
                           (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
        if ((plVar7 == (longlong *)0x0) ||
           (lVar8 = (**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0)),
           lVar8 == 0)) goto LAB_7ffe9a52cfea;
        iVar4 = FUN_7ffe99742ec0(0xe,_DAT_7ffe9c940d40,lVar8);
        plVar7 = (longlong *)
                 (**(code **)(*(longlong *)playerAct + 0x298))
                           (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
        if ((plVar7 == (longlong *)0x0) ||
           (lVar8 = (**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0)),
           lVar8 == 0)) goto LAB_7ffe9a52cfea;
        iVar5 = FUN_7ffe99742ec0(0x10,_DAT_7ffe9c940d40,lVar8);
        if (iVar5 <= iVar4) {
          if (lStackX_8 == 0) goto LAB_7ffe9a52cfea;
          iVar4 = func_0x7ffe9a7a2140(lStackX_8,0x34);
          iVar10 = iVar10 + iVar4;
        }
      }
      cVar3 = FUN_7ffe99a4d1d0(iVar10,0);
      if (cVar3 == '\0') {
        return 0;
      }
      plVar7 = *(longlong **)(playerAct + 0x30);
      if (plVar7 != (longlong *)0x0) {
        if ((*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar7 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) != _DAT_7ffe9c922a40)) {
          if ((*(byte *)(_DAT_7ffe9c8f7560 + 0x130) <= *(byte *)(*plVar7 + 0x130)) &&
             (*(longlong *)
               (*(longlong *)(*plVar7 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) == _DAT_7ffe9c8f7560)) {
            if ((*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7ffe9c8f7560 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar7 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) != _DAT_7ffe9c8f7560)) {
              FUN_7ffe9996c950(plVar7);
              pcVar2 = (code *)swi(3);
              iVar10 = (*pcVar2)();
              return iVar10;
            }
            if ((plVar7[9] == 0) ||
               (uVar1 = *(undefined8 *)(plVar7[9] + 0x18), mobAct == (undefined *)0x0))
            goto LAB_7ffe9a52cfea;
            uVar9 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAct);
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar3 = FUN_7ffe9bda1fa0(uVar1,uVar9,0);
            if (cVar3 != '\0') {
              uVar6 = (**(code **)(*(longlong *)self + 0x178))
                                (self,*(undefined8 *)(*(longlong *)self + 0x180));
              FUN_7ffe9a4318b0(plVar7,uVar6,mobAct,0);
              return 1;
            }
          }
        }
        else {
          if ((*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar7 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) != _DAT_7ffe9c922a40)) {
            FUN_7ffe9996c950(plVar7);
            pcVar2 = (code *)swi(3);
            iVar10 = (*pcVar2)();
            return iVar10;
          }
          if ((plVar7[9] == 0) ||
             (uVar1 = *(undefined8 *)(plVar7[9] + 0x18), mobAct == (undefined *)0x0))
          goto LAB_7ffe9a52cfea;
          uVar9 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAct);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar3 = FUN_7ffe9bda1fa0(uVar1,uVar9,0);
          if (cVar3 != '\0') {
            iVar10 = (**(code **)(*(longlong *)self + 0x178))
                               (self,*(undefined8 *)(*(longlong *)self + 0x180));
            PlayerBattleManager_EquipBuffAttack((undefined *)plVar7,iVar10,mobAct,(undefined *)0x0);
          }
        }
      }
      return 1;
    }
  }
LAB_7ffe9a52cfea:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar10 = (*pcVar2)();
  return iVar10;
}

