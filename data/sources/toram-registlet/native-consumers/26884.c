
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ConquesterAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  float fVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  undefined4 uVar6;
  longlong lVar7;
  undefined8 uVar8;
  longlong *plVar9;
  undefined *thisObject_00;
  undefined4 uVar10;
  longlong *plVar11;
  
  if (DAT_7ffe9cadf22c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf22c = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar11 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar11 = (longlong *)0x0;
    if (bVar3) {
      plVar11 = (longlong *)actarAction;
    }
  }
  uVar10 = 0;
  uVar6 = FUN_7ffe9a4ae0a0(plVar11,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar6;
  uVar6 = FUN_7ffe9a4ade20(plVar11,0);
  *(undefined4 *)(thisObject + 0x100) = uVar6;
  uVar6 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar6;
  if (plVar11 != (longlong *)0x0) {
    lVar7 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
    if (lVar7 != 0) {
      uVar6 = FUN_7ffe9a4a1cc0(lVar7,0);
      *(undefined4 *)(thisObject + 0x30) = uVar6;
      uVar8 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      uVar6 = FUN_7ffe9a4aabb0(uVar8,0);
      *(undefined4 *)(thisObject + 0x78) = uVar6;
      *(undefined4 *)(thisObject + 0x124) = 0x4b0;
      *(float *)(thisObject + 0x120) = (float)(((byte)thisObject[0x14] + 5) * 100);
      uVar6 = func_0x7ffe99a4d6a0((float)(byte)thisObject[0x14] * _DAT_7ffe9c049b40 +
                                  _DAT_7ffe9c049b4c,0);
      *(undefined4 *)(thisObject + 0x48) = uVar6;
      if (*(int *)(thisObject + 0xfc) == 0xc) {
        uVar10 = 0xbf20b61;
      }
      else if (*(int *)(thisObject + 0xfc) == 0xd) {
        uVar10 = 0xbf39201;
      }
      fVar1 = *(float *)(thisObject + 0x120);
      pcVar2 = *(code **)(*plVar11 + 0x298);
      if (*(int *)(thisObject + 0x100) == 0xf) {
        plVar9 = (longlong *)(*pcVar2)(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
        if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a73cbf7;
        lVar7 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400));
        if (lVar7 == 0) goto LAB_7ffe9a73cbf7;
        *(float *)(thisObject + 0x120) = (float)*(int *)(lVar7 + 0x18) + fVar1;
      }
      else {
        plVar9 = (longlong *)(*pcVar2)();
        if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a73cbf7;
        lVar7 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400));
        if (lVar7 == 0) goto LAB_7ffe9a73cbf7;
        *(float *)(thisObject + 0x120) = (float)*(int *)(lVar7 + 0x24) + fVar1;
        if (*(int *)(thisObject + 0x100) == 0x12) {
          thisObject[0x130] = 0;
        }
      }
      plVar9 = (longlong *)
               (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      if (plVar9 != (longlong *)0x0) {
        thisObject_00 =
             (undefined *)(**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220));
        if (thisObject_00 != (undefined *)0x0) {
          bVar5 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x41c,(undefined *)0x0);
          thisObject[0x132] = bVar5;
          uVar8 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar8,uVar10,0);
          *(undefined8 *)(thisObject + 0x58) = uVar8;
          il2cpp_write_barrier_0();
          if ((*(longlong *)(thisObject + 0x58) != 0) &&
             (lVar7 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar7 != 0)) {
            FUN_7ffe9ad10e00(lVar7,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
            cVar4 = (**(code **)(*(longlong *)thisObject + 0x568))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x570),0);
            if (cVar4 == '\0') {
              uVar6 = FUN_7ffe9a4a81f0(thisObject,plVar11,0);
              *(undefined4 *)(thisObject + 200) = uVar6;
            }
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a73cbf7:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

