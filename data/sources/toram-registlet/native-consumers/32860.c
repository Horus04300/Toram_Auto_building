
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void QuickLoaderAction_ActionHit
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  undefined1 uVar1;
  int iVar2;
  code *pcVar3;
  bool bVar4;
  char cVar5;
  byte bVar6;
  uint uVar7;
  longlong lVar8;
  longlong *plVar9;
  longlong lVar10;
  undefined *thisObject_00;
  undefined8 uVar11;
  longlong *plVar12;
  longlong alStack_18 [2];
  
  if (DAT_7ffe9cadf8a0 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c929cd0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c92baf8);
    FUN_7ffe9996d590(&DAT_7ffe9c9697f8);
    FUN_7ffe9996d590(&DAT_7ffe9c9011c8);
    FUN_7ffe9996d590(&DAT_7ffe9c915130);
    DAT_7ffe9cadf8a0 = '\x01';
  }
  alStack_18[0] = 0;
  lVar8 = func_0x7ffe99940040(_DAT_7ffe9c915130);
  func_0x7ffe999c3920(lVar8,0);
  if (lVar8 != 0) {
    *(undefined **)(lVar8 + 0x10) = thisObject;
    il2cpp_write_barrier_0();
    *(undefined **)(lVar8 + 0x18) = actarAction;
    il2cpp_write_barrier_0();
    plVar9 = *(longlong **)(lVar8 + 0x18);
    plVar12 = (longlong *)0x0;
    if (plVar9 != (longlong *)0x0) {
      if ((*(byte *)(*plVar9 + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar9 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8)
          != _DAT_7ffe9c922720)) {
        bVar4 = false;
      }
      else {
        bVar4 = true;
      }
      if (bVar4) {
        plVar12 = plVar9;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar5 = FUN_7ffe9bda2160(plVar12,0,0);
    if (cVar5 == '\0') {
      return;
    }
    if (((plVar12 != (longlong *)0x0) &&
        (plVar9 = (longlong *)
                  (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0)),
        plVar9 != (longlong *)0x0)) &&
       (lVar10 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
       lVar10 != 0)) {
      cVar5 = FUN_7ffe9abc2210(lVar10,0x55,alStack_18,_DAT_7ffe9c9697f8);
      if (cVar5 == '\0') {
        uVar1 = thisObject[0x14];
        iVar2 = *(int *)(thisObject + 0xfc);
        lVar8 = func_0x7ffe99940040(_DAT_7ffe9c92baf8);
        FUN_7ffe9a79f450(lVar8,uVar1,iVar2 == 0xd,0);
        alStack_18[0] = lVar8;
        plVar9 = (longlong *)
                 (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
        if ((plVar9 != (longlong *)0x0) &&
           (lVar8 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
           lVar8 != 0)) {
          FUN_7ffe9a7c26c0(lVar8,alStack_18[0],thisObject[0x10],0);
          plVar9 = (longlong *)
                   (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
          if (plVar9 != (longlong *)0x0) {
            lVar8 = (**(code **)(*plVar9 + 0x1b8))(plVar9,*(undefined8 *)(*plVar9 + 0x1c0));
            if (lVar8 != 0) {
              uVar7 = FUN_7ffe9a7fd580(lVar8,0x45,1);
              if ((int)uVar7 < 1) {
                return;
              }
              if ((int)(uint)(byte)thisObject[0x14] < (int)uVar7) {
                uVar7 = (uint)(byte)thisObject[0x14];
              }
              plVar9 = (longlong *)
                       (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
              if ((plVar9 != (longlong *)0x0) &&
                 (thisObject_00 =
                       (undefined *)
                       (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220)),
                 thisObject_00 != (undefined *)0x0)) {
                bVar6 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x405,(undefined *)0x0);
                uVar11 = func_0x7ffe99940040(_DAT_7ffe9c929cd0);
                FUN_7ffe9a790c50(uVar11,uVar7 & 0xff,bVar6,0);
                plVar9 = (longlong *)
                         (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
                if ((plVar9 != (longlong *)0x0) &&
                   (lVar8 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
                   lVar8 != 0)) {
                  FUN_7ffe9a7c26c0(lVar8,uVar11,0,0);
                  return;
                }
              }
            }
          }
        }
      }
      else if (alStack_18[0] != 0) {
        func_0x7ffe999e7880(alStack_18[0],0);
        uVar11 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
        FUN_7ffe9ac2ed50(uVar11,lVar8,_DAT_7ffe9c9011c8,0);
        FUN_7ffe9a4b2010(thisObject,uVar11,0);
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

