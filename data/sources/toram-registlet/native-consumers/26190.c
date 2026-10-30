
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FireStyleAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined *puVar8;
  longlong *plVar9;
  undefined4 uVar10;
  
  if (DAT_7ffe9cadf141 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf141 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar9 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    plVar9 = (longlong *)0x0;
    if (bVar2) {
      plVar9 = (longlong *)actarAction;
    }
  }
  uVar10 = func_0x7ffe99a4d6a0(_DAT_7ffe9c049b7c,0);
  *(undefined4 *)(thisObject + 0x20) = uVar10;
  uVar10 = FUN_7ffe9a4ae0a0(plVar9,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar10;
  if (plVar9 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
    if (lVar5 != 0) {
      uVar10 = FUN_7ffe9a4a1cc0(lVar5,0);
      *(undefined4 *)(thisObject + 0x30) = uVar10;
      uVar10 = FUN_7ffe9a7b7a30(thisObject,600,plVar9,0);
      *(undefined4 *)(thisObject + 0x128) = uVar10;
      FUN_7ffe9a4aacd0(thisObject,plVar9,0);
      uVar6 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
      uVar3 = FUN_7ffe9a4aabb0(uVar6,0);
      uVar10 = _DAT_7ffe9c049b74;
      *(undefined4 *)(thisObject + 0x78) = uVar3;
      plVar7 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
      if (plVar7 != (longlong *)0x0) {
        puVar8 = (undefined *)
                 (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
        if (puVar8 != (undefined *)0x0) {
          puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x407,(undefined *)0x0);
          uVar3 = _DAT_7ffe9c049d14;
          if (puVar8 != (undefined *)0x0) {
            iVar4 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
            *(int *)(thisObject + 0x164) = iVar4;
            uVar10 = uVar3;
          }
          uVar6 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
          FUN_7ffe9a7b7ae0(thisObject,uVar10,uVar6,0);
          *(uint *)(thisObject + 0x140) = (uint)(byte)thisObject[0x14] * 2 + 0x1e;
          return;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

