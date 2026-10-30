
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SonicWaveAction_OnInitialize
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
  
  if (DAT_7ffe9cadef7e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadef7e = '\x01';
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
        fVar11 = (float)(byte)thisObject[0x14] / _DAT_7ffe9c049b74;
        if (DAT_7ffe9cad9e25 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9e25 = '\x01';
        }
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        dVar10 = (double)func_0x7ffe99997768((double)fVar11);
        bVar1 = thisObject[0x14];
        iVar5 = (uint)bVar1 + (uint)bVar1 * 4;
        fVar11 = (float)bVar1;
        *(int *)(thisObject + 0x128) = iVar5;
        *(int *)(thisObject + 300) = iVar5;
        *(float *)(thisObject + 0x20) = (float)((int)dVar10 << 2);
        fVar11 = fVar11 + fVar11 + _DAT_7ffe9c049d94 + fVar11 * _DAT_7ffe9c049b4c;
        *(float *)(thisObject + 0x124) = fVar11;
        if (*(int *)(thisObject + 0xfc) == 0x10) {
          fVar11 = fVar11 + _DAT_7ffe9c049f04;
          *(float *)(thisObject + 0x20) = (float)((int)dVar10 << 2) + _DAT_7ffe9c049d14;
          *(float *)(thisObject + 0x124) = fVar11;
          plVar7 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a6f186f;
          puVar8 = (undefined *)
                   (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
          if (puVar8 == (undefined *)0x0) goto LAB_7ffe9a6f186f;
          puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x6c,(undefined *)0x0);
          if (puVar8 != (undefined *)0x0) {
            fVar11 = *(float *)(thisObject + 0x124);
            iVar5 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x4,(undefined *)0x0);
            *(float *)(thisObject + 0x124) = (float)iVar5 + fVar11;
          }
          *(int *)(thisObject + 0x128) = *(int *)(thisObject + 0x128) + 0x19;
          *(int *)(thisObject + 300) = *(int *)(thisObject + 300) + 0x32;
        }
        uVar4 = func_0x7ffe99a4d6a0();
        *(undefined4 *)(thisObject + 0x20) = uVar4;
        uVar9 = (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        uVar4 = FUN_7ffe9a4aabb0(uVar9,0);
        *(undefined4 *)(thisObject + 0x78) = uVar4;
        FUN_7ffe9a4aacd0(thisObject,actarAction,0);
        uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar9,0xbf825e2,0);
        *(undefined8 *)(thisObject + 0x58) = uVar9;
        il2cpp_write_barrier_0();
        if ((*(longlong *)(thisObject + 0x58) != 0) &&
           (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
          FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
          iVar5 = *(int *)(thisObject + 0x30);
          lVar6 = *(longlong *)(thisObject + 0x58);
          if ((iVar5 == 7) || (iVar5 == 8)) {
            iVar5 = 0x11e9480b;
          }
          else {
            iVar5 = iVar5 * 100000 + 0x11e9480b;
          }
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar9,iVar5,0);
          if (lVar6 != 0) {
            *(undefined8 *)(lVar6 + 0x20) = uVar9;
            il2cpp_write_barrier_0();
            if (((*(longlong *)(thisObject + 0x58) != 0) &&
                (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar6 != 0)) &&
               (lVar6 = *(longlong *)(lVar6 + 0x50), lVar6 != 0)) {
              FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a6f186f:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

