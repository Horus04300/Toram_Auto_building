
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int DamageReflection_Calc
              (undefined *self,int value,undefined *playerAct,undefined *mobAct,
              undefined *methodInfo)

{
  longlong *self_00;
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  
  if (DAT_7ffe9cade238 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7560);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    DAT_7ffe9cade238 = '\x01';
  }
  *(int *)(self + 0x18) =
       (int)(((float)(int)*(short *)(self + 0x10) / _DAT_7ffe9c049cfc) * (float)value);
  if (playerAct != (undefined *)0x0) {
    self_00 = *(longlong **)(playerAct + 0x30);
    if (self_00 != (longlong *)0x0) {
      if ((*(byte *)(*self_00 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*self_00 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8
           ) != _DAT_7ffe9c922a40)) {
        if ((*(byte *)(_DAT_7ffe9c8f7560 + 0x130) <= *(byte *)(*self_00 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*self_00 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) == _DAT_7ffe9c8f7560)) {
          if ((*(byte *)(*self_00 + 0x130) < *(byte *)(_DAT_7ffe9c8f7560 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*self_00 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) != _DAT_7ffe9c8f7560)) {
            FUN_7ffe9996c950(self_00);
            pcVar2 = (code *)swi(3);
            iVar4 = (*pcVar2)();
            return iVar4;
          }
          if ((self_00[9] == 0) ||
             (uVar1 = *(undefined8 *)(self_00[9] + 0x18), mobAct == (undefined *)0x0))
          goto LAB_7ffe9a51c9db;
          uVar5 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAct);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar3 = FUN_7ffe9bda1fa0(uVar1,uVar5,0);
          if (cVar3 != '\0') {
            FUN_7ffe9a431750(self_00,mobAct,0);
          }
        }
      }
      else {
        if ((*(byte *)(*self_00 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*self_00 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) != _DAT_7ffe9c922a40)) {
          FUN_7ffe9996c950(self_00);
          pcVar2 = (code *)swi(3);
          iVar4 = (*pcVar2)();
          return iVar4;
        }
        if ((self_00[9] == 0) ||
           (uVar1 = *(undefined8 *)(self_00[9] + 0x18), mobAct == (undefined *)0x0))
        goto LAB_7ffe9a51c9db;
        uVar5 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar3 = FUN_7ffe9bda1fa0(uVar1,uVar5);
        if (cVar3 != '\0') {
          PlayerBattleManager_DamagerReflection((undefined *)self_00,mobAct,(undefined *)0x0);
        }
      }
    }
    return *(int *)(self + 0x18);
  }
LAB_7ffe9a51c9db:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

