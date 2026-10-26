
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_CalcGuard
              (undefined *self,int damage,undefined *playerAction,undefined *guardPower,
              undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  longlong *plVar6;
  
  if (DAT_7ffe9cadd7e1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    DAT_7ffe9cadd7e1 = '\x01';
  }
  *(undefined4 *)guardPower = 0;
  if (playerAction == (undefined *)0x0) {
LAB_7ffe9a36f7d0:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar5 = (*pcVar2)();
    return iVar5;
  }
  plVar1 = *(longlong **)(playerAction + 0x30);
  plVar6 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    if ((*(byte *)(*plVar1 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8)
        != _DAT_7ffe9c922a40)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    if (bVar3) {
      plVar6 = plVar1;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda1fa0(plVar6,0,0);
  if (cVar4 == '\0') {
    if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a36f7d0;
    damage = (**(code **)(*plVar6 + 0x2d8))
                       (plVar6,damage,guardPower,*(undefined8 *)(*plVar6 + 0x2e0));
  }
  return damage;
}

