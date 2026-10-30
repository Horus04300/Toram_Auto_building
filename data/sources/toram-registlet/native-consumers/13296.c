
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerBattleStatus_get_Aspd(undefined *thisObject,undefined *methodInfo)

{
  code *UNRECOVERED_JUMPTABLE;
  char cVar1;
  ushort uVar2;
  int iVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined *puVar7;
  float fVar8;
  
  if (DAT_7ffe9caddd82 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9caddd82 = '\x01';
  }
  plVar6 = *(longlong **)(thisObject + 0x10);
  if (plVar6 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0));
    if (lVar5 != 0) {
      cVar1 = FUN_7ffe9a4daa60(lVar5,6);
      fVar8 = _DAT_7ffe9c049b4c;
      plVar6 = *(longlong **)(thisObject + 0x10);
      if (cVar1 == '\0') {
        if (plVar6 != (longlong *)0x0) {
          plVar6 = (longlong *)
                   (**(code **)(*plVar6 + 0x198))(plVar6,*(undefined8 *)(*plVar6 + 0x1a0));
          if (plVar6 != (longlong *)0x0) {
            uVar2 = 0;
            lVar5 = *plVar6;
            if (*(ushort *)(lVar5 + 0x12e) != 0) {
              do {
                if (*(longlong *)(*(longlong *)(lVar5 + 0xb0) + (ulonglong)uVar2 * 0x10) ==
                    _DAT_7ffe9c940d40) {
                  puVar4 = (undefined8 *)
                           ((longlong)
                            (*(int *)(*(longlong *)(lVar5 + 0xb0) + 8 + (ulonglong)uVar2 * 0x10) +
                            0x16) * 0x10 + 0x138 + lVar5);
                  UNRECOVERED_JUMPTABLE = (code *)*puVar4;
                    /* WARNING: Could not recover jumptable at 0x7ffe99742f4b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                  iVar3 = (*UNRECOVERED_JUMPTABLE)(plVar6,puVar4[1],UNRECOVERED_JUMPTABLE);
                  return iVar3;
                }
                uVar2 = uVar2 + 1;
              } while (uVar2 < *(ushort *)(lVar5 + 0x12e));
            }
            puVar4 = (undefined8 *)FUN_7ffe998ce540(plVar6);
                    /* WARNING: Could not recover jumptable at 0x7ffe99742f1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            iVar3 = (*(code *)*puVar4)(plVar6,puVar4[1],(code *)*puVar4);
            return iVar3;
          }
        }
      }
      else if (plVar6 != (longlong *)0x0) {
        puVar7 = (undefined *)
                 (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
        if (puVar7 != (undefined *)0x0) {
          puVar7 = GemCartBufferManager_GetGemCartBuffer(puVar7,0xe,(undefined *)0x0);
          if (puVar7 != (undefined *)0x0) {
            iVar3 = GemCartBufferBase_GetValue(puVar7,(undefined *)0x2,(undefined *)0x0);
            fVar8 = (float)iVar3 * _DAT_7ffe9c049b34 + fVar8;
          }
          plVar6 = *(longlong **)(thisObject + 0x10);
          if (plVar6 != (longlong *)0x0) {
            lVar5 = (**(code **)(*plVar6 + 0x198))(plVar6,*(undefined8 *)(*plVar6 + 0x1a0));
            if (lVar5 != 0) {
              iVar3 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c940d40,lVar5);
              return (int)((float)iVar3 * fVar8);
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  UNRECOVERED_JUMPTABLE = (code *)swi(3);
  iVar3 = (*UNRECOVERED_JUMPTABLE)();
  return iVar3;
}

