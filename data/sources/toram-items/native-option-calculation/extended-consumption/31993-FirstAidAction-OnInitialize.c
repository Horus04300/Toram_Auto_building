
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FirstAidAction_OnInitialize(undefined *self,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *status;
  longlong *plVar6;
  longlong lVar7;
  undefined8 uVar8;
  longlong *playerAction;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadf798 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf798 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  if (actarAction == (undefined *)0x0) {
    *(undefined4 *)(self + 0x20) = 0x40c00000;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    *(undefined4 *)(self + 0x20) = 0x40c00000;
    playerAction = (longlong *)0x0;
    if (bVar2) {
      playerAction = (longlong *)actarAction;
    }
    if (playerAction != (longlong *)0x0) {
      status = (undefined *)(**(code **)(*playerAction + 0x298))(playerAction);
      iVar4 = PlayerAttackBase_CalcMotionSpeed(status,(undefined *)0x0);
      *(int *)(self + 0x78) = iVar4;
      plVar6 = (longlong *)
               (**(code **)(*playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*playerAction + 0x2a0));
      if (plVar6 != (longlong *)0x0) {
        lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0));
        if ((lVar7 != 0) && (*(longlong *)(lVar7 + 0x50) != 0)) {
          cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),9,&plStackX_8,_DAT_7ffe9c934418);
          if (cVar3 == '\0') {
            uVar5 = 100;
          }
          else {
            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a81889d;
            uVar5 = (**(code **)(*plStackX_8 + 0x1f8))(plStackX_8,0xe);
          }
          *(undefined4 *)(self + 0x120) = uVar5;
          uVar8 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar8,0x1e078);
          *(undefined8 *)(self + 0x58) = uVar8;
          il2cpp_write_barrier_0();
          lVar7 = *(longlong *)(self + 0x58);
          uVar8 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar8,0x9ebcba);
          if (lVar7 != 0) {
            *(undefined8 *)(lVar7 + 0x20) = uVar8;
            il2cpp_write_barrier_0();
            PlayerAttackBase_CalcMp(self,(undefined *)playerAction,(undefined *)0x0);
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a81889d:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

