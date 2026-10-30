
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmashAction_OnInitialize(undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  float fVar1;
  byte bVar2;
  code *pcVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined *puVar10;
  undefined8 uVar11;
  undefined8 uStackX_10;
  
  if (DAT_7ffe9cadef7a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadef7a = '\x01';
  }
  uStackX_10 = 0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      lVar8 = (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (lVar8 != 0) {
        uVar5 = FUN_7ffe9a4a1cc0(lVar8,0);
        *(undefined4 *)(thisObject + 0x30) = uVar5;
        *(undefined4 *)(thisObject + 0xfc) = 0;
        cVar4 = FUN_7ffe9a4ad860(actarAction,0x10,&uStackX_10,0);
        if (cVar4 != '\0') {
          *(undefined4 *)(thisObject + 0xfc) = 0x10;
        }
        uVar5 = FUN_7ffe9a4adf80(uStackX_10,0);
        bVar2 = thisObject[0x14];
        *(undefined4 *)(thisObject + 0x20) = uVar5;
        *(uint *)(thisObject + 0x128) = (uint)bVar2 + (uint)bVar2 * 4;
        *(float *)(thisObject + 0x124) = (float)bVar2 + (float)bVar2 + _DAT_7ffe9c049cf4;
        uVar5 = 0x4b;
        if (bVar2 < 6) {
          uVar5 = 0x32;
        }
        *(undefined4 *)(thisObject + 300) = uVar5;
        if (*(int *)(thisObject + 0xfc) == 0x10) {
          *(float *)(thisObject + 0x124) =
               (float)((uint)(byte)thisObject[0x14] * 3 + 0x32) + *(float *)(thisObject + 0x124);
          plVar9 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a6f0ee1;
          puVar10 = (undefined *)
                    (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220));
          if (puVar10 == (undefined *)0x0) goto LAB_7ffe9a6f0ee1;
          puVar10 = GemCartBufferManager_GetGemCartBuffer(puVar10,0x6b,(undefined *)0x0);
          if (puVar10 != (undefined *)0x0) {
            fVar1 = *(float *)(thisObject + 0x124);
            iVar6 = GemCartBufferBase_GetValue(puVar10,(undefined *)0x4,(undefined *)0x0);
            *(float *)(thisObject + 0x124) = (float)iVar6 + fVar1;
          }
          iVar6 = *(int *)(thisObject + 0x128);
          plVar9 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a6f0ee1;
          lVar8 = (**(code **)(*plVar9 + 0x198))(plVar9,*(undefined8 *)(*plVar9 + 0x1a0));
          if (lVar8 == 0) goto LAB_7ffe9a6f0ee1;
          iVar7 = FUN_7ffe99742ec0(4,_DAT_7ffe9c940d40,lVar8);
          *(int *)(thisObject + 300) = *(int *)(thisObject + 300) + 0x19;
          *(int *)(thisObject + 0x128) = iVar6 + 0x19 + iVar7 / 10;
        }
        uVar11 = (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        uVar5 = FUN_7ffe9a4aabb0(uVar11,0);
        *(undefined4 *)(thisObject + 0x78) = uVar5;
        FUN_7ffe9a4aacd0(thisObject,actarAction,0);
        uVar11 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar11,0xc5059,0);
        *(undefined8 *)(thisObject + 0x58) = uVar11;
        il2cpp_write_barrier_0();
        if ((*(longlong *)(thisObject + 0x58) != 0) &&
           (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar8 != 0)) {
          FUN_7ffe9ad10e00(lVar8,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
          return;
        }
      }
    }
  }
LAB_7ffe9a6f0ee1:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

