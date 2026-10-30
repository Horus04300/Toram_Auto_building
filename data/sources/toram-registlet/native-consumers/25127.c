
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EarthBindAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  code *pcVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined8 uVar9;
  double dVar10;
  float fVar11;
  undefined8 uStackX_10;
  
  if (DAT_7ffe9cadef20 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadef20 = '\x01';
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
        uVar4 = FUN_7ffe9a4a1cc0(lVar6,0);
        *(undefined4 *)(thisObject + 0x30) = uVar4;
        *(undefined4 *)(thisObject + 0xfc) = 0;
        cVar3 = FUN_7ffe9a4ad860(actarAction,0x10,&uStackX_10,0);
        if (cVar3 != '\0') {
          *(undefined4 *)(thisObject + 0xfc) = 0x10;
        }
        uVar4 = FUN_7ffe9a4adf80(uStackX_10,0);
        bVar1 = thisObject[0x14];
        *(undefined4 *)(thisObject + 0x20) = uVar4;
        if (DAT_7ffe9cad9c12 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9c12 = '\x01';
        }
        fVar11 = (float)bVar1 * _DAT_7ffe9c049dc4;
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        dVar10 = (double)func_0x7ffe999978b4((double)fVar11);
        bVar1 = thisObject[0x14];
        *(uint *)(thisObject + 0x128) = (uint)bVar1 + (uint)bVar1 * 4;
        *(float *)(thisObject + 0x124) = (float)(int)dVar10 + _DAT_7ffe9c049cfc;
        if (DAT_7ffe9cad9c12 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9c12 = '\x01';
        }
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        dVar10 = (double)func_0x7ffe999978b4((double)(bVar1 / 3));
        *(uint *)(thisObject + 300) =
             (uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4;
        *(float *)(thisObject + 0x130) = (float)(int)dVar10 * _DAT_7ffe9c049b4c + _DAT_7ffe9c049b18;
        if (*(int *)(thisObject + 0xfc) == 0x10) {
          fVar11 = *(float *)(thisObject + 0x124);
          plVar7 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a6caf5b;
          lVar6 = (**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0));
          if (lVar6 == 0) goto LAB_7ffe9a6caf5b;
          iVar5 = FUN_7ffe99742ec0(4,_DAT_7ffe9c940d40,lVar6);
          *(float *)(thisObject + 0x124) = (float)(iVar5 / 5 + 0x19) + fVar11;
          plVar7 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a6caf5b;
          puVar8 = (undefined *)
                   (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
          if (puVar8 == (undefined *)0x0) goto LAB_7ffe9a6caf5b;
          puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0xd1,(undefined *)0x0);
          if (puVar8 != (undefined *)0x0) {
            fVar11 = *(float *)(thisObject + 0x124);
            iVar5 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
            *(float *)(thisObject + 0x124) = (float)iVar5 + fVar11;
          }
          fVar11 = *(float *)(thisObject + 0x130) + _DAT_7ffe9c049cd8;
          *(int *)(thisObject + 0x128) = *(int *)(thisObject + 0x128) + 0x19;
          *(int *)(thisObject + 300) = *(int *)(thisObject + 300) + 0x32;
          *(int *)(thisObject + 0x134) = *(int *)(thisObject + 0x134) + 500;
          *(float *)(thisObject + 0x130) = fVar11;
        }
        uVar4 = func_0x7ffe99a4d6a0();
        *(undefined4 *)(thisObject + 0x130) = uVar4;
        uVar9 = (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        uVar4 = FUN_7ffe9a4aabb0(uVar9,0);
        *(undefined4 *)(thisObject + 0x78) = uVar4;
        FUN_7ffe9a4aacd0(thisObject,actarAction,0);
        uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar9,0xc6f99,0);
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
LAB_7ffe9a6caf5b:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

