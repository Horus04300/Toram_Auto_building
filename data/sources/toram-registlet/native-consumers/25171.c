
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HeavySmashAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  int iVar2;
  code *pcVar3;
  char cVar4;
  undefined4 uVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined8 uVar9;
  int iVar10;
  undefined8 uStackX_10;
  
  if (DAT_7ffe9cadef2e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadef2e = '\x01';
  }
  uStackX_10 = 0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      lVar6 = (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (lVar6 != 0) {
        uVar5 = FUN_7ffe9a4a1cc0(lVar6,0);
        *(undefined4 *)(thisObject + 0x30) = uVar5;
        *(undefined4 *)(thisObject + 0xfc) = 0;
        cVar4 = FUN_7ffe9a4ad860(actarAction,0x10,&uStackX_10,0);
        if (cVar4 != '\0') {
          *(undefined4 *)(thisObject + 0xfc) = 0x10;
        }
        uVar5 = FUN_7ffe9a4adf80(uStackX_10,0);
        bVar1 = thisObject[0x14];
        *(undefined4 *)(thisObject + 0x20) = uVar5;
        iVar2 = (bVar1 + 10) * 10;
        *(int *)(thisObject + 0x128) = iVar2;
        iVar10 = (uint)bVar1 + (uint)bVar1 * 2;
        *(float *)(thisObject + 0x124) =
             ((float)bVar1 * _DAT_7ffe9c049ce8 + _DAT_7ffe9c049cfc) / _DAT_7ffe9c049cfc;
        if (*(int *)(thisObject + 0xfc) == 0x10) {
          *(int *)(thisObject + 0x128) = iVar2 + 100;
          *(int *)(thisObject + 300) = iVar10 + 0x46;
          plVar7 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a6ccbbb;
          puVar8 = (undefined *)
                   (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
          if (puVar8 == (undefined *)0x0) goto LAB_7ffe9a6ccbbb;
          puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x130,(undefined *)0x0);
          if (puVar8 != (undefined *)0x0) {
            iVar2 = *(int *)(thisObject + 0x130);
            iVar10 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
            *(int *)(thisObject + 0x130) = iVar10 + iVar2;
          }
        }
        else {
          *(int *)(thisObject + 300) = iVar10 + 0x14;
        }
        uVar9 = (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        uVar5 = FUN_7ffe9a4aabb0(uVar9,0);
        *(undefined4 *)(thisObject + 0x78) = uVar5;
        FUN_7ffe9a4aacd0(thisObject,actarAction,0);
        uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar9,0xc5c12,0);
        *(undefined8 *)(thisObject + 0x58) = uVar9;
        il2cpp_write_barrier_0();
        if ((*(longlong *)(thisObject + 0x58) != 0) &&
           (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
          FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
          return;
        }
      }
    }
  }
LAB_7ffe9a6ccbbb:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

