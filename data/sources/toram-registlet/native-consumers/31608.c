
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BreathingMethodAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  undefined4 uVar4;
  longlong *plVar5;
  undefined *thisObject_00;
  undefined8 uVar6;
  undefined8 unaff_RDI;
  undefined8 in_R9;
  
  if (DAT_7ffe9cadf735 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9cadf735 = '\x01';
  }
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      plVar5 = (longlong *)
               (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (plVar5 != (longlong *)0x0) {
        thisObject_00 =
             (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220));
        if (thisObject_00 != (undefined *)0x0) {
          bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x40d,(undefined *)0x0);
          if (bVar3 != 0) {
            *(int *)(thisObject + 0x124) = *(int *)(thisObject + 0x124) + -100;
          }
          *(undefined4 *)(thisObject + 0x20) = 0xbf800000;
          uVar6 = (**(code **)(*(longlong *)actarAction + 0x298))
                            (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          uVar4 = FUN_7ffe9a4aabb0(uVar6,0);
          *(undefined4 *)(thisObject + 0x78) = uVar4;
          plVar5 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (plVar5 != (longlong *)0x0) {
            uVar6 = (**(code **)(*plVar5 + 0x1a8))(plVar5,*(undefined8 *)(*plVar5 + 0x1b0));
            if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            uVar4 = FUN_7ffe9a811090(0,uVar6,0);
            *(undefined4 *)(thisObject + 0x24) = uVar4;
            uVar6 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            FUN_7ffe9a9002e0(uVar6,0x1bd51,0);
            *(undefined8 *)(thisObject + 0x58) = uVar6;
            il2cpp_write_barrier_0();
            cVar2 = (**(code **)(*(longlong *)thisObject + 0x568))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x570),0,in_R9,
                               unaff_RDI);
            if (cVar2 == '\0') {
              uVar4 = FUN_7ffe9a4a81f0(thisObject,actarAction,0);
              *(undefined4 *)(thisObject + 200) = uVar4;
            }
            return;
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

