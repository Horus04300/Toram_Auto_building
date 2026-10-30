
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte NormalAttackAction_RampageHitCheck
               (undefined *thisObject,undefined *playerAction,byte hit,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined *thisObject_00;
  bool bVar7;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadde98 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    DAT_7ffe9cadde98 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  if (1 < *(int *)(thisObject + 0xfc) - 10U) {
    return hit;
  }
  if ((((playerAction != (undefined *)0x0) &&
       (plVar5 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
       plVar5 != (longlong *)0x0)) &&
      (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)), lVar6 != 0))
     && (*(longlong *)(lVar6 + 0x40) != 0)) {
    cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x40),0x29,&plStackX_8,_DAT_7ffe9c934418);
    if (cVar2 == '\0') {
      return hit;
    }
    if (plStackX_8 != (longlong *)0x0) {
      if (*(char *)((longlong)plStackX_8 + 0x1c) == '\0') {
        return hit;
      }
      iVar4 = (**(code **)(*plStackX_8 + 0x1f8))
                        (plStackX_8,0x32,*(undefined8 *)(*plStackX_8 + 0x200));
      bVar7 = iVar4 == 1;
      plVar5 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar5 != (longlong *)0x0) &&
         (thisObject_00 =
               (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
         thisObject_00 != (undefined *)0x0)) {
        bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x12e,(undefined *)0x0);
        if (bVar3 == 0) {
          if (bVar7) {
            hit = 1;
          }
        }
        else {
          bVar7 = false;
        }
        *(uint *)(thisObject + 0x104) = bVar7 + 1 | *(uint *)(thisObject + 0x104);
        return hit;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

