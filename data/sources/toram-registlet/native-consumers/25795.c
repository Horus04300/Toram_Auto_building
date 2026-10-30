
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ThreeStageThrustAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  int iVar3;
  longlong *plVar4;
  undefined *thisObject_00;
  longlong lVar5;
  undefined8 uVar6;
  undefined4 uVar7;
  float fVar8;
  undefined8 uStackX_10;
  
  if (DAT_7ffe9cadf0b6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf0b6 = '\x01';
  }
  uStackX_10 = 0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      plVar4 = (longlong *)
               (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (plVar4 != (longlong *)0x0) {
        thisObject_00 =
             (undefined *)(**(code **)(*plVar4 + 0x218))(plVar4,*(undefined8 *)(*plVar4 + 0x220));
        if (thisObject_00 != (undefined *)0x0) {
          bVar2 = GemCartBufferManager_ContainsBuffer(thisObject_00,0xd6,(undefined *)0x0);
          if (bVar2 == 0) {
            uVar7 = func_0x7ffe99a4d6a0();
          }
          else {
            uVar7 = FUN_7ffe9a4adfc0(actarAction,&uStackX_10,0);
            *(undefined4 *)(thisObject + 0xfc) = uVar7;
            uVar7 = FUN_7ffe9a4adf80(uStackX_10,0);
          }
          *(undefined4 *)(thisObject + 0x20) = uVar7;
          lVar5 = (**(code **)(*(longlong *)actarAction + 0x298))
                            (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (lVar5 != 0) {
            uVar7 = FUN_7ffe9a4a1cc0(lVar5,0);
            *(undefined4 *)(thisObject + 0x30) = uVar7;
            fVar8 = (float)(((uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4) * 4 +
                           0x96);
            *(float *)(thisObject + 0x120) = fVar8;
            plVar4 = (longlong *)
                     (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            if (plVar4 != (longlong *)0x0) {
              lVar5 = (**(code **)(*plVar4 + 0x198))(plVar4,*(undefined8 *)(*plVar4 + 0x1a0));
              if (lVar5 != 0) {
                iVar3 = FUN_7ffe99742ec0(4,_DAT_7ffe9c940d40,lVar5);
                *(float *)(thisObject + 0x120) = (float)(iVar3 / 5) + fVar8;
                uVar6 = (**(code **)(*(longlong *)actarAction + 0x298))
                                  (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
                uVar7 = FUN_7ffe9a4aabb0(uVar6,0);
                *(undefined4 *)(thisObject + 0x78) = uVar7;
                FUN_7ffe9a4aacd0(thisObject,actarAction,0);
                uVar6 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                FUN_7ffe9a9002e0(uVar6,(uint)bVar2 * 2 + 0x128630,0);
                *(undefined8 *)(thisObject + 0x58) = uVar6;
                il2cpp_write_barrier_0();
                if (bVar2 == 0) {
                  *(undefined4 *)(thisObject + 0x104) = 1;
                }
                *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 2;
                return;
              }
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

