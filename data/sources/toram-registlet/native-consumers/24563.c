
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EtherFlareAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  char cVar3;
  undefined1 uVar4;
  byte bVar5;
  undefined4 uVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined *thisObject_00;
  
  if (DAT_7ffe9cadee3e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadee3e = '\x01';
  }
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      plVar7 = (longlong *)
               (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (plVar7 != (longlong *)0x0) {
        lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0));
        if (lVar8 != 0) {
          uVar4 = FUN_7ffe9a7c6d00(lVar8,0x363,0);
          thisObject[0x12d] = uVar4;
          lVar8 = (**(code **)(*(longlong *)actarAction + 0x298))
                            (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (lVar8 != 0) {
            uVar6 = FUN_7ffe9a4a1fb0(lVar8,0);
            *(undefined4 *)(thisObject + 0x30) = uVar6;
            uVar6 = func_0x7ffe99a4d6a0();
            *(undefined4 *)(thisObject + 0x20) = uVar6;
            plVar7 = (longlong *)
                     (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            if (plVar7 != (longlong *)0x0) {
              lVar8 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
              if (lVar8 != 0) {
                iVar1 = *(int *)(lVar8 + 0x18);
                plVar7 = (longlong *)
                         (**(code **)(*(longlong *)actarAction + 0x298))
                                   (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
                if (plVar7 != (longlong *)0x0) {
                  lVar8 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
                  if (lVar8 != 0) {
                    if (iVar1 <= *(int *)(lVar8 + 0x14)) {
                      iVar1 = *(int *)(lVar8 + 0x14);
                    }
                    *(uint *)(thisObject + 0x124) = ((byte)thisObject[0x14] + 10) * 5;
                    *(uint *)(thisObject + 0x128) = (uint)(byte)thisObject[0x14] * 7 + 0x1e;
                    *(float *)(thisObject + 0x120) = (float)iVar1 + _DAT_7ffe9c049df8;
                    uVar9 = (**(code **)(*(longlong *)actarAction + 0x298))
                                      (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0)
                                      );
                    uVar6 = FUN_7ffe9a4a7fe0(thisObject,0,uVar9,0);
                    *(undefined4 *)(thisObject + 0x24) = uVar6;
                    uVar9 = (**(code **)(*(longlong *)actarAction + 0x298))
                                      (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0)
                                      );
                    uVar6 = FUN_7ffe9a4aabb0(uVar9,0);
                    *(undefined4 *)(thisObject + 0x78) = uVar6;
                    plVar7 = (longlong *)
                             (**(code **)(*(longlong *)actarAction + 0x298))
                                       (actarAction,
                                        *(undefined8 *)(*(longlong *)actarAction + 0x2a0));
                    if (plVar7 != (longlong *)0x0) {
                      thisObject_00 =
                           (undefined *)
                           (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
                      if (thisObject_00 != (undefined *)0x0) {
                        bVar5 = GemCartBufferManager_ContainsBuffer
                                          (thisObject_00,0x3f6,(undefined *)0x0);
                        thisObject[300] = bVar5;
                        cVar3 = (**(code **)(*(longlong *)thisObject + 0x568))
                                          (thisObject,
                                           *(undefined8 *)(*(longlong *)thisObject + 0x570),0);
                        if (cVar3 == '\0') {
                          uVar6 = FUN_7ffe9a4a81f0(thisObject,actarAction,0);
                          *(undefined4 *)(thisObject + 200) = uVar6;
                        }
                        return;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

