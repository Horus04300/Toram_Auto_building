
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerAttackBase_InitializeElement
               (undefined *self,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  longlong *plVar4;
  
  if (DAT_7ffe9caddec3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9caddec3 = '\x01';
  }
  if (actarAction != (undefined *)0x0) {
    if (((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
        (*(longlong *)
          (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) &&
       (puVar3 = (undefined *)(**(code **)(*(longlong *)actarAction + 0x298))(actarAction),
       puVar3 != (undefined *)0x0)) {
      puVar3 = PlayerStatusBase_GetEquipElement(puVar3,(undefined *)0x0);
      *(int *)(self + 0x30) = (int)puVar3;
      if ((*(longlong *)(self + 0xb8) != 0) && (*(int *)(*(longlong *)(self + 0xb8) + 0x1c) == 0x14)
         ) {
        plVar4 = (longlong *)
                 (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if ((plVar4 == (longlong *)0x0) ||
           (puVar3 = (undefined *)
                     (**(code **)(*plVar4 + 0x1d8))(plVar4,*(undefined8 *)(*plVar4 + 0x1e0)),
           puVar3 == (undefined *)0x0)) goto LAB_7ffe9a4aea53;
        puVar3 = BonusManager_GetEquipElement(puVar3,(undefined *)0x2,(undefined *)0x0);
        *(int *)(self + 0x34) = (int)puVar3;
      }
      cVar2 = FUN_7ffe9a7abc30(actarAction,0);
      if ((cVar2 == '\0') || (cVar2 = FUN_7ffe9a7abb70(self,0), cVar2 == '\0')) {
        return;
      }
      plVar4 = (longlong *)
               (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if ((plVar4 != (longlong *)0x0) &&
         (puVar3 = (undefined *)
                   (**(code **)(*plVar4 + 0x1d8))(plVar4,*(undefined8 *)(*plVar4 + 0x1e0)),
         puVar3 != (undefined *)0x0)) {
        puVar3 = BonusManager_GetEquipElement(puVar3,(undefined *)0x2,(undefined *)0x0);
        *(int *)(self + 0x34) = (int)puVar3;
        return;
      }
    }
  }
LAB_7ffe9a4aea53:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

