
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_CalcSkillComboTough
              (undefined *self,undefined *playerAction,int damage,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  longlong *plVar7;
  
  if (DAT_7ffe9cadd7cc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9550b0);
    FUN_7ffe9996d590(&DAT_7ffe9c95d758);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7490);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922658);
    DAT_7ffe9cadd7cc = '\x01';
  }
  if (playerAction != (undefined *)0x0) {
    lVar5 = *(longlong *)playerAction;
    if ((*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_7ffe9c922658 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922658 + 0x130) * 8) !=
        _DAT_7ffe9c922658)) {
      if (*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_7ffe9c8f7490 + 0x130)) {
        return damage;
      }
      if (*(longlong *)
           (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f7490 + 0x130) * 8)
          != _DAT_7ffe9c8f7490) {
        return damage;
      }
    }
    lVar5 = FUN_7ffe9a47bac0(0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda1fa0(lVar5,0,0);
    if (cVar3 == '\0') {
      if ((lVar5 != 0) && (lVar6 = FUN_7ffe9a4804c0(lVar5,0), lVar6 != 0)) {
        cVar3 = func_0x7ffe9a4ceea0(lVar6,0);
        if (cVar3 == '\0') {
          return damage;
        }
        lVar6 = FUN_7ffe9a47fe30(lVar5,0);
        if (((lVar6 != 0) && (*(longlong *)(lVar6 + 0x30) != 0)) &&
           (plVar7 = *(longlong **)(*(longlong *)(lVar6 + 0x30) + 0x30), plVar7 != (longlong *)0x0))
        {
          plVar7 = (longlong *)(**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400))
          ;
          cVar3 = FUN_7ffe9a8fecd0(plVar7,0,0);
          if (cVar3 != '\0') {
            if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a3739b2;
            iVar4 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
            bVar2 = true;
            if (iVar4 == 0x4c3) {
              if ((*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7ffe9c9550b0 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*plVar7 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c9550b0 + 0x130) * 8) != _DAT_7ffe9c9550b0)) {
                FUN_7ffe9996c950(plVar7);
                pcVar1 = (code *)swi(3);
                iVar4 = (*pcVar1)();
                return iVar4;
              }
              bVar2 = true;
              if ((char)plVar7[0x2c] == '\0') {
                bVar2 = false;
              }
            }
            iVar4 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
            if (iVar4 == 0x2ca) {
              if ((*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7ffe9c95d758 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*plVar7 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c95d758 + 0x130) * 8) != _DAT_7ffe9c95d758)) {
                FUN_7ffe9996c950(plVar7);
                pcVar1 = (code *)swi(3);
                iVar4 = (*pcVar1)();
                return iVar4;
              }
              if (*(char *)((longlong)plVar7 + 0x144) == '\0') {
                return damage;
              }
            }
            if (!bVar2) {
              return damage;
            }
          }
          lVar5 = FUN_7ffe9a4804c0(lVar5,0);
          if (lVar5 != 0) {
            iVar4 = FUN_7ffe9a7ef640(lVar5,0);
            if (iVar4 < 1) {
              return damage;
            }
            if (damage < 1) {
              return damage;
            }
            iVar4 = (int)((float)((100 - iVar4) * damage) * _DAT_7ffe9c049b34);
            if (0 < iVar4) {
              return iVar4;
            }
            return 1;
          }
        }
      }
LAB_7ffe9a3739b2:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      iVar4 = (*pcVar1)();
      return iVar4;
    }
  }
  return damage;
}

