
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AuraBladeAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined *thisObject_00;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined4 uVar9;
  
  if (DAT_7ffe9cadeb5a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadeb5a = '\x01';
  }
  FUN_7ffe9a4a5ca0(thisObject,actarAction,target,0);
  if (actarAction == (undefined *)0x0) {
    plVar6 = (longlong *)0x0;
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
    plVar6 = (longlong *)0x0;
    if (bVar2) {
      plVar6 = (longlong *)actarAction;
    }
  }
  lVar5 = 0;
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda2160(target,0,0);
  if (cVar3 != '\0') {
    if (target == (undefined *)0x0) goto LAB_7ffe9a632ffa;
    lVar5 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c962758);
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda2160(plVar6,0,0);
  if (cVar3 == '\0') {
    return;
  }
  if (lVar5 == 0) {
    return;
  }
  if (((plVar6 != (longlong *)0x0) &&
      (plVar6 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
      plVar6 != (longlong *)0x0)) &&
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
     thisObject_00 != (undefined *)0x0)) {
    bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x411,(undefined *)0x0);
    if (bVar4 == 0) {
      return;
    }
    if ((actarAction != (undefined *)0x0) &&
       (uVar7 = FUN_7ffe9bd98a10(actarAction,0), target != (undefined *)0x0)) {
      uVar8 = FUN_7ffe9bd9b890(target,0);
      uVar9 = FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0,lVar5);
      cVar3 = (**(code **)(*(longlong *)thisObject + 0x4e8))
                        (thisObject,uVar7,uVar8,uVar9,
                         *(undefined8 *)(*(longlong *)thisObject + 0x4f0));
      if (cVar3 != '\0') {
        return;
      }
      *(longlong *)(thisObject + 0x138) = lVar5;
      il2cpp_write_barrier_0();
      if (*(longlong *)(thisObject + 0x58) != 0) {
        uVar9 = *(undefined4 *)(*(longlong *)(thisObject + 0x58) + 0x10);
        if (*(int *)(thisObject + 0xfc) == 10) {
          *(undefined4 *)(thisObject + 0x128) = 2;
          uVar9 = 0xbfb5261;
          if (*(int *)(thisObject + 0x100) != 10) {
            uVar9 = 0xbef1591;
          }
        }
        else if (*(int *)(thisObject + 0xfc) == 0xb) {
          uVar9 = 0xbf09461;
        }
        uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar7,uVar9,0);
        *(undefined8 *)(thisObject + 0x58) = uVar7;
        il2cpp_write_barrier_0();
        if ((*(longlong *)(thisObject + 0x58) != 0) &&
           (lVar5 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar5 != 0)) {
          FUN_7ffe9ad10e00(lVar5,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
          lVar5 = *(longlong *)(thisObject + 0x58);
          uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar7,0x11e7d8d8,0);
          if (lVar5 != 0) {
            *(undefined8 *)(lVar5 + 0x20) = uVar7;
            il2cpp_write_barrier_0();
            if (((*(longlong *)(thisObject + 0x58) != 0) &&
                (lVar5 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar5 != 0)) &&
               (lVar5 = *(longlong *)(lVar5 + 0x50), lVar5 != 0)) {
              FUN_7ffe9ad10e00(lVar5,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
              *(undefined4 *)(thisObject + 0x104) = 1;
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a632ffa:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

