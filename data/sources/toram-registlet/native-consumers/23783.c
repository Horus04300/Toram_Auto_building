
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void DragonTailAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  code *pcVar2;
  undefined4 uVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined *puVar6;
  undefined8 uVar7;
  int iVar8;
  float fVar9;
  double dVar10;
  
  if (DAT_7ffe9caded17 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9caded17 = '\x01';
  }
  if (actarAction != (undefined *)0x0) {
    if (((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
        (*(longlong *)
          (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) &&
       (lVar4 = (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0)),
       lVar4 != 0)) {
      uVar3 = FUN_7ffe9a4a1cc0(lVar4,0);
      *(undefined4 *)(thisObject + 0x30) = uVar3;
      uVar3 = func_0x7ffe99a4d6a0();
      *(undefined4 *)(thisObject + 0x20) = uVar3;
      uVar3 = func_0x7ffe99a4d6a0();
      *(undefined4 *)(thisObject + 0x138) = uVar3;
      bVar1 = thisObject[0x14];
      if (DAT_7ffe9cad9c12 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c968830);
        DAT_7ffe9cad9c12 = '\x01';
      }
      iVar8 = bVar1 - 1;
      if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      dVar10 = (double)func_0x7ffe999978b4((double)(iVar8 / 3 + (iVar8 >> 0x1f) +
                                                   (int)(((longlong)iVar8 / 3 +
                                                          ((longlong)iVar8 >> 0x3f) & 0xffffffffU)
                                                        >> 0x1f)));
      uVar3 = func_0x7ffe99a4d6a0((float)(int)dVar10 * _DAT_7ffe9c049b4c + _DAT_7ffe9c049dc4,0);
      *(undefined4 *)(thisObject + 0x13c) = uVar3;
      *(float *)(thisObject + 0x120) =
           (float)((uint)(byte)thisObject[0x14] * 3 + 0x46) / _DAT_7ffe9c049cfc;
      *(float *)(thisObject + 0x124) = (float)(((byte)thisObject[0x14] + 10) * 0x14);
      plVar5 = (longlong *)
               (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if ((plVar5 != (longlong *)0x0) &&
         (puVar6 = (undefined *)
                   (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
         puVar6 != (undefined *)0x0)) {
        puVar6 = GemCartBufferManager_GetGemCartBuffer(puVar6,0xd4,(undefined *)0x0);
        if (puVar6 != (undefined *)0x0) {
          fVar9 = *(float *)(thisObject + 0x124);
          iVar8 = GemCartBufferBase_GetValue(puVar6,(undefined *)0x4,(undefined *)0x0);
          *(float *)(thisObject + 0x124) = (float)iVar8 + fVar9;
        }
        fVar9 = *(float *)(thisObject + 0x124) / _DAT_7ffe9c049cfc;
        *(undefined4 *)(thisObject + 0x128) = 100;
        *(float *)(thisObject + 0x124) = fVar9;
        *(uint *)(thisObject + 300) = (uint)(byte)thisObject[0x14] * 0xf + 0x32;
        uVar7 = (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        uVar3 = FUN_7ffe9a4aabb0(uVar7,0);
        *(undefined4 *)(thisObject + 0x78) = uVar3;
        *(uint *)(thisObject + 0x140) =
             ((uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4) * 2;
        FUN_7ffe9a4aacd0(thisObject,actarAction,0);
        uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar7,0x10f7c1,0);
        *(undefined8 *)(thisObject + 0x58) = uVar7;
        il2cpp_write_barrier_0();
        if ((*(longlong *)(thisObject + 0x58) != 0) &&
           (lVar4 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar4 != 0)) {
          FUN_7ffe9ad10e00(lVar4,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
          thisObject[0x134] = 1;
          return;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

