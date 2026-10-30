
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void CronosDrivePursuitAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  longlong *plVar5;
  undefined *thisObject_00;
  longlong lVar6;
  undefined8 uVar7;
  
  if (DAT_7ffe9cadde66 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadde66 = '\x01';
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
          bVar2 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x199,(undefined *)0x0);
          if (bVar2 != 0) {
            thisObject[0x120] = 0;
          }
          uVar3 = FUN_7ffe9a4ae0a0(actarAction,0);
          *(undefined4 *)(thisObject + 0xfc) = uVar3;
          bVar2 = thisObject[0x14];
          *(undefined4 *)(thisObject + 0x20) = 0xbf800000;
          *(float *)(thisObject + 0x124) = (float)(bVar2 + 0x28);
          pcVar1 = *(code **)(*(longlong *)actarAction + 0x298);
          if (thisObject[0x120] == '\0') {
            plVar5 = (longlong *)(*pcVar1)();
            if (plVar5 != (longlong *)0x0) {
              lVar6 = (**(code **)(*plVar5 + 0x198))(plVar5,*(undefined8 *)(*plVar5 + 0x1a0));
              if (lVar6 != 0) {
                uVar7 = 1;
LAB_7ffe9a490943:
                iVar4 = FUN_7ffe99742ec0(uVar7,_DAT_7ffe9c940d40,lVar6);
                *(float *)(thisObject + 0x124) = (float)(iVar4 / 5) + (float)(bVar2 + 0x28);
                *(uint *)(thisObject + 0x128) = ((byte)thisObject[0x14] + 10) * 0x19;
                return;
              }
            }
          }
          else {
            plVar5 = (longlong *)
                     (*pcVar1)(actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            if (plVar5 != (longlong *)0x0) {
              lVar6 = (**(code **)(*plVar5 + 0x198))(plVar5,*(undefined8 *)(*plVar5 + 0x1a0));
              if (lVar6 != 0) {
                uVar7 = 2;
                goto LAB_7ffe9a490943;
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

