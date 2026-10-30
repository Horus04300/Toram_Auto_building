
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PutitHealAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong *plVar6;
  undefined *puVar7;
  longlong lVar8;
  longlong *plStackX_10;
  
  if (DAT_7ffe9cadf893 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90dea0);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf893 = '\x01';
  }
  plStackX_10 = (longlong *)0x0;
  FUN_7ffe9a4a5ca0(thisObject,actarAction,target,0);
  if (actarAction != (undefined *)0x0) {
    if ((((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) &&
        (plVar6 = (longlong *)
                  (**(code **)(*(longlong *)actarAction + 0x298))
                            (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0)),
        plVar6 != (longlong *)0x0)) &&
       (puVar7 = (undefined *)
                 (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
       puVar7 != (undefined *)0x0)) {
      bVar2 = GemCartBufferManager_ContainsBuffer(puVar7,0x402,(undefined *)0x0);
      if (bVar2 != 0) {
        iVar4 = *(int *)(thisObject + 0x120) / 2;
        plVar6 = (longlong *)
                 (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if ((plVar6 == (longlong *)0x0) ||
           (puVar7 = (undefined *)
                     (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
           puVar7 == (undefined *)0x0)) goto LAB_7ffe9a83444f;
        iVar5 = GemCartBufferManager_GetBufferLevel(puVar7,0x47,(undefined *)0x0);
        if (0 < iVar5) {
          iVar4 = (int)((_DAT_7ffe9c049b18 - (float)(iVar5 * 10) * _DAT_7ffe9c049b34) * (float)iVar4
                       );
        }
        *(int *)(thisObject + 0x120) = *(int *)(thisObject + 0x120) - iVar4;
      }
      if (*(int *)(thisObject + 0x104) != 1) {
        return;
      }
      plVar6 = (longlong *)
               (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if ((plVar6 != (longlong *)0x0) &&
         (lVar8 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
         lVar8 != 0)) {
        cVar3 = FUN_7ffe9a7cbb30(lVar8,0x17,&plStackX_10);
        if (cVar3 != '\0') {
          if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a83444f;
          if (((*(byte *)(*plStackX_10 + 0x130) < *(byte *)(_DAT_7ffe9c90dea0 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStackX_10 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c90dea0 + 0x130) * 8) != _DAT_7ffe9c90dea0)) ||
             (plStackX_10 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStackX_10);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          FUN_7ffe9a78d340(plStackX_10,*(int *)(thisObject + 0x124) / 100,0);
        }
        return;
      }
    }
  }
LAB_7ffe9a83444f:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

