
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerBattleManager_CheckZeroActionDelay(undefined *thisObject,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined *puVar7;
  
  plVar5 = *(longlong **)(thisObject + 0x88);
  if (((plVar5 != (longlong *)0x0) &&
      (plVar5 = (longlong *)(**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
      plVar5 != (longlong *)0x0)) &&
     (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)), lVar6 != 0))
  {
    cVar2 = FUN_7ffe9a7c6d00(lVar6,0x26c,0);
    if (cVar2 != '\0') {
      plVar5 = *(longlong **)(thisObject + 0x88);
      if ((plVar5 == (longlong *)0x0) ||
         (lVar6 = (**(code **)(*plVar5 + 0x2a8))(plVar5,*(undefined8 *)(*plVar5 + 0x2b0)),
         lVar6 == 0)) goto LAB_7ffe9a45ab27;
      cVar2 = FUN_7ffe9a4daa60(lVar6,6);
      if (cVar2 == '\0') {
        return 1;
      }
    }
    plVar5 = *(longlong **)(thisObject + 0x88);
    if (((plVar5 != (longlong *)0x0) &&
        (plVar5 = (longlong *)
                  (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
        plVar5 != (longlong *)0x0)) &&
       (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)), lVar6 != 0)
       ) {
      cVar2 = FUN_7ffe9a7c6d00(lVar6,0x10b,0);
      if (cVar2 != '\0') {
        plVar5 = *(longlong **)(thisObject + 0x88);
        if ((plVar5 == (longlong *)0x0) ||
           (lVar6 = (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
           lVar6 == 0)) goto LAB_7ffe9a45ab27;
        cVar2 = FUN_7ffe9a4a1460(lVar6,2);
        if (cVar2 != '\0') {
          return 1;
        }
      }
      plVar5 = *(longlong **)(thisObject + 0x88);
      if (((plVar5 != (longlong *)0x0) &&
          (plVar5 = (longlong *)
                    (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
          plVar5 != (longlong *)0x0)) &&
         (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)),
         lVar6 != 0)) {
        cVar2 = FUN_7ffe9a7c6d00(lVar6,299,0);
        if (cVar2 != '\0') {
          return 1;
        }
        plVar5 = *(longlong **)(thisObject + 0x88);
        if (((plVar5 != (longlong *)0x0) &&
            (plVar5 = (longlong *)
                      (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
            plVar5 != (longlong *)0x0)) &&
           (puVar7 = (undefined *)
                     (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
           puVar7 != (undefined *)0x0)) {
          puVar7 = GemCartBufferManager_GetGemCartBuffer(puVar7,0x23,(undefined *)0x0);
          if ((puVar7 != (undefined *)0x0) &&
             (iVar4 = GemCartBufferBase_GetValue(puVar7,(undefined *)0x2,(undefined *)0x0),
             iVar4 != 0)) {
            return 1;
          }
          return 0;
        }
      }
    }
  }
LAB_7ffe9a45ab27:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

