
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerActionManager_InMobAttackArea
               (undefined *thisObject,undefined *enemyAction,undefined *mobAttack,
               undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  longlong *plVar6;
  undefined *thisObject_00;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 uVar9;
  
  if (DAT_7ffe9caddcbb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c9644a8);
    DAT_7ffe9caddcbb = '\x01';
  }
  FUN_7ffe9a4789d0(thisObject,enemyAction,mobAttack,0);
  plVar6 = (longlong *)
           (**(code **)(*(longlong *)thisObject + 0x298))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar6 != (longlong *)0x0) &&
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
     thisObject_00 != (undefined *)0x0)) {
    bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3f,(undefined *)0x0);
    if (bVar3 == 0) {
      return;
    }
    lVar8 = *(longlong *)(thisObject + 0x30);
    if (lVar8 != 0) {
      if (*(longlong *)(lVar8 + 0x48) == 0) {
        return;
      }
      uVar9 = *(undefined8 *)(*(longlong *)(lVar8 + 0x48) + 0x18);
      if (enemyAction != (undefined *)0x0) {
        uVar7 = FUN_7ffe9bd98960(enemyAction,0);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar4 = FUN_7ffe9bda1fa0(uVar9,uVar7,0);
        if (cVar4 == '\0') {
          return;
        }
        if (mobAttack != (undefined *)0x0) {
          iVar5 = (**(code **)(*(longlong *)mobAttack + 0x588))
                            (mobAttack,enemyAction,thisObject,
                             *(undefined8 *)(*(longlong *)mobAttack + 0x590));
          plVar6 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar6 != (longlong *)0x0) &&
             (lVar8 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
             lVar8 != 0)) {
            iVar1 = *(int *)(lVar8 + 0x10);
            plVar6 = (longlong *)
                     (**(code **)(*(longlong *)thisObject + 0x298))
                               (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
            if ((plVar6 != (longlong *)0x0) &&
               (lVar8 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
               lVar8 != 0)) {
              if ((float)iVar5 < (float)(*(int *)(lVar8 + 0x20) + iVar1) * _DAT_7ffe9c049b4c) {
                return;
              }
              lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
              uVar9 = FUN_7ffe9bd98a10(enemyAction,0);
              if ((lVar8 != 0) && (lVar8 = func_0x7ffe99ca8200(lVar8,uVar9,0), lVar8 != 0)) {
                FUN_7ffe9a2b64b0(lVar8);
                return;
              }
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

