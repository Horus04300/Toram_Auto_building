
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_CalcUnavoidableAttack
              (undefined *self,undefined *mobAction,undefined *playerAction,undefined *damageData,
              undefined *guardPower,undefined *justGuard,undefined *methodInfo)

{
  byte bVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined *status;
  undefined4 auStackX_18 [4];
  undefined4 *puVar7;
  longlong *aplStack_38 [2];
  undefined4 uVar8;
  
  if (DAT_7ffe9cadd7d8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c8f94c8);
    FUN_7ffe9996d590(&DAT_7ffe9c972b60);
    FUN_7ffe9996d590(&DAT_7ffe9c914fd0);
    DAT_7ffe9cadd7d8 = '\x01';
  }
  aplStack_38[0] = (longlong *)0x0;
  iVar4 = 0;
  auStackX_18[0] = 0;
  if (playerAction != (undefined *)0x0) {
    plVar5 = (longlong *)
             (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar5 != (longlong *)0x0) {
      lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0));
      if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x50) != 0)) {
        cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x50),0x283,aplStack_38,_DAT_7ffe9c934418);
        if (cVar3 != '\0') {
          if (aplStack_38[0] == (longlong *)0x0) goto LAB_7ffe9a373fbe;
          bVar1 = *(byte *)(_DAT_7ffe9c914fd0 + 0x130);
          if (((*(byte *)(*aplStack_38[0] + 0x130) < bVar1) ||
              (lVar6 = *(longlong *)(*aplStack_38[0] + 200),
              *(longlong *)(lVar6 + -8 + (ulonglong)bVar1 * 8) != _DAT_7ffe9c914fd0)) ||
             (aplStack_38[0] == (longlong *)0x0)) goto LAB_7ffe9a373fbe;
          plVar5 = (longlong *)0x0;
          if (*(longlong *)(lVar6 + -8 + (ulonglong)bVar1 * 8) == _DAT_7ffe9c914fd0) {
            plVar5 = aplStack_38[0];
          }
          func_0x7ffe9a79e3d0(plVar5,0);
        }
        *(undefined4 *)guardPower = 0xffffffff;
        puVar7 = auStackX_18;
        cVar3 = (**(code **)(*(longlong *)self + 0x598))
                          (self,playerAction,mobAction,0,puVar7,justGuard,
                           *(undefined8 *)(*(longlong *)self + 0x5a0));
        uVar8 = (undefined4)((ulonglong)puVar7 >> 0x20);
        if (cVar3 == '\0') {
          if (damageData == (undefined *)0x0) goto LAB_7ffe9a373fbe;
        }
        else {
          if (damageData == (undefined *)0x0) goto LAB_7ffe9a373fbe;
          *(undefined4 *)(damageData + 0x34) = auStackX_18[0];
          uVar8 = 0;
          iVar4 = MobAttackBase_CalcGuard(self,0,playerAction,guardPower,(undefined *)0x0);
        }
        iVar4 = MobAttackBase_CalcLastDamage
                          (self,mobAction,playerAction,iVar4,
                           (undefined *)CONCAT44(uVar8,*(undefined4 *)(damageData + 0x34)),
                           (undefined *)CONCAT71((int7)((ulonglong)justGuard >> 8),1),
                           (undefined *)0x0);
        status = (undefined *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (*(int *)(_DAT_7ffe9c972b60 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        aplStack_38[0] = (longlong *)MobAttackBase_GetBarrierBuf(self,status,(undefined *)0x0);
        if (aplStack_38[0] != (longlong *)0x0) {
          if (((*(byte *)(*aplStack_38[0] + 0x130) < *(byte *)(_DAT_7ffe9c8f94c8 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*aplStack_38[0] + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c8f94c8 + 0x130) * 8) != _DAT_7ffe9c8f94c8)) ||
             (aplStack_38[0] == (longlong *)0x0)) {
            FUN_7ffe9996c950(aplStack_38[0],_DAT_7ffe9c8f94c8);
            pcVar2 = (code *)swi(3);
            iVar4 = (*pcVar2)();
            return iVar4;
          }
          (**(code **)(*aplStack_38[0] + 0x2a8))
                    (aplStack_38[0],iVar4,playerAction,mobAction,
                     *(undefined8 *)(*aplStack_38[0] + 0x2b0));
        }
        *(undefined4 *)(damageData + 0x1c) = 1;
        return 0;
      }
    }
  }
LAB_7ffe9a373fbe:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

