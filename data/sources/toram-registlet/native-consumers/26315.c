
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ThunderStyleAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined4 uVar9;
  float fVar10;
  
  if (DAT_7ffe9cadf16a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf16a = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar7 = (longlong *)0x0;
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
    plVar7 = (longlong *)0x0;
    if (bVar2) {
      plVar7 = (longlong *)actarAction;
    }
  }
  uVar9 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar9;
  uVar9 = FUN_7ffe9a4ae0a0(plVar7,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar9;
  if (plVar7 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
    if (lVar5 != 0) {
      uVar9 = FUN_7ffe9a4a1cc0(lVar5,0);
      *(undefined4 *)(thisObject + 0x30) = uVar9;
      uVar9 = FUN_7ffe9a7b7a30(thisObject,600,plVar7,0);
      *(undefined4 *)(thisObject + 300) = uVar9;
      FUN_7ffe9a4aacd0(thisObject,plVar7,0);
      uVar6 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      uVar9 = FUN_7ffe9a4aabb0(uVar6,0);
      *(undefined4 *)(thisObject + 0x78) = uVar9;
      uVar6 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      FUN_7ffe9a7b7ae0(thisObject,_DAT_7ffe9c049b70,uVar6,0);
      *(uint *)(thisObject + 0x134) = ((byte)thisObject[0x14] + 10) * 0x14;
      fVar10 = (float)(((byte)thisObject[0x14] + 10) * 10);
      *(float *)(thisObject + 0x130) = fVar10;
      uVar6 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      iVar3 = FUN_7ffe9a7b7d10(thisObject,uVar6,0);
      fVar10 = (float)iVar3 + fVar10;
      *(float *)(thisObject + 0x130) = fVar10;
      uVar6 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      iVar3 = FUN_7ffe9a7b7c00(thisObject,uVar6,0);
      *(float *)(thisObject + 0x130) = (float)(iVar3 * 0x1e) + fVar10;
      if (*(int *)(thisObject + 0xfc) == 8) {
        thisObject[0x138] = 1;
        *(undefined4 *)(thisObject + 0x104) = 1;
      }
      *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 2;
      plVar7 = (longlong *)(**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      if (plVar7 != (longlong *)0x0) {
        puVar8 = (undefined *)
                 (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
        if (puVar8 != (undefined *)0x0) {
          puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x41b,(undefined *)0x0);
          if (puVar8 != (undefined *)0x0) {
            iVar3 = *(int *)(thisObject + 0x134);
            iVar4 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
            thisObject[0x140] = 1;
            *(int *)(thisObject + 0x134) = iVar4 + iVar3;
          }
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

