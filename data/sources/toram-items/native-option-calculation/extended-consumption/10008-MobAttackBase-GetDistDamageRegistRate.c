
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float MobAttackBase_GetDistDamageRegistRate
                (undefined *self,undefined *playerAction,undefined *mobAction,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  longlong lVar5;
  undefined8 *puVar6;
  longlong *plVar7;
  float fVar8;
  float fVar9;
  float fStack_38;
  float fStack_34;
  undefined8 uStack_28;
  float fStack_20;
  
  if (DAT_7ffe9cadd7d5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c93afa8);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadd7d5 = '\x01';
  }
  fVar8 = _DAT_7ffe9c049b18;
  if (playerAction == (undefined *)0x0) {
    plVar7 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)playerAction + 0x130) < *(byte *)(_DAT_7ffe9c93afa8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)playerAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c93afa8 + 0x130) * 8) != _DAT_7ffe9c93afa8)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar7 = (longlong *)0x0;
    if (bVar3) {
      plVar7 = (longlong *)playerAction;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(plVar7,0,0);
  if (cVar4 != '\0') {
    if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a375de6;
    cVar4 = (**(code **)(*plVar7 + 0x458))(plVar7,*(undefined8 *)(*plVar7 + 0x460));
    if (cVar4 == '\0') {
      return fVar8;
    }
    fVar8 = 0.0;
    if (mobAction != (undefined *)0x0) {
      if ((playerAction == (undefined *)0x0) ||
         (lVar5 = FUN_7ffe9bd98a10(playerAction,0), lVar5 == 0)) {
LAB_7ffe9a375de6:
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        fVar8 = (float)(*pcVar2)();
        return fVar8;
      }
      puVar6 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_28,lVar5,0);
      uVar1 = *puVar6;
      fVar8 = *(float *)(puVar6 + 1);
      lVar5 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c9724e0,mobAction);
      if (lVar5 == 0) goto LAB_7ffe9a375de6;
      puVar6 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_28,lVar5,0);
      fStack_34 = (float)((ulonglong)uVar1 >> 0x20);
      fStack_38 = (float)uVar1;
      fStack_20 = fVar8 - *(float *)(puVar6 + 1);
      uStack_28 = CONCAT44(fStack_34 - (float)((ulonglong)*puVar6 >> 0x20),
                           fStack_38 - (float)*puVar6);
      fVar8 = (float)FUN_7ffe999e62d0(&uStack_28,0);
      fVar9 = (float)FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0,mobAction);
      fVar8 = fVar8 - fVar9;
    }
    fVar9 = (float)func_0x7ffe99a4d6a0(_DAT_7ffe9c049b74,0);
    if (fVar9 <= fVar8) {
      fVar9 = fVar8;
    }
    fVar8 = (float)func_0x7ffe99a4d6b0(fVar9,0);
    fVar8 = (float)(int)fVar8 / _DAT_7ffe9c049ce4;
  }
  return fVar8;
}

