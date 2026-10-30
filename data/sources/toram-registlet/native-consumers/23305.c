
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HorizontalCutAction_Damaged
               (undefined *playerAction,undefined *actor,undefined *action,undefined *damageData,
               undefined *methodInfo)

{
  float fVar1;
  longlong *plVar2;
  code *pcVar3;
  bool bVar4;
  char cVar5;
  byte bVar6;
  char cVar7;
  int iVar8;
  uint uVar9;
  longlong *plVar10;
  longlong lVar11;
  undefined *thisObject;
  longlong lVar12;
  undefined8 uVar13;
  uint uVar14;
  undefined4 uVar15;
  float fVar16;
  undefined8 in_stack_ffffffffffffffc0;
  uint uVar17;
  
  uVar17 = (uint)((ulonglong)in_stack_ffffffffffffffc0 >> 0x20);
  if (DAT_7ffe9cadec70 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    FUN_7ffe9996d590(&DAT_7ffe9c9667d0);
    FUN_7ffe9996d590(&DAT_7ffe9c966638);
    FUN_7ffe9996d590(&DAT_7ffe9c90d450);
    FUN_7ffe9996d590(&DAT_7ffe9c960050);
    FUN_7ffe9996d590(&DAT_7ffe9c8ed808);
    FUN_7ffe9996d590(&DAT_7ffe9c972b60);
    FUN_7ffe9996d590(&DAT_7ffe9c8edca8);
    FUN_7ffe9996d590(&DAT_7ffe9c9412e0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    DAT_7ffe9cadec70 = '\x01';
  }
  if (((playerAction == (undefined *)0x0) || (*(longlong *)(playerAction + 0x30) == 0)) ||
     (plVar10 = *(longlong **)(*(longlong *)(playerAction + 0x30) + 0x30),
     plVar10 == (longlong *)0x0)) goto LAB_7ffe9a66bd70;
  plVar10 = (longlong *)(**(code **)(*plVar10 + 0x188))(plVar10,*(undefined8 *)(*plVar10 + 400));
  cVar5 = FUN_7ffe9a8fec40(plVar10,0,0);
  if (cVar5 != '\0') {
    return;
  }
  if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a66bd70;
  iVar8 = (**(code **)(*plVar10 + 0x188))(plVar10,*(undefined8 *)(*plVar10 + 400));
  if (iVar8 != 0x294) {
    return;
  }
  if (damageData == (undefined *)0x0) goto LAB_7ffe9a66bd70;
  if (*(int *)(damageData + 0x8c) - 1U < 4) {
    return;
  }
  if (*(int *)(damageData + 0x8c) == 0x2b) {
    return;
  }
  if (action == (undefined *)0x0) {
    plVar10 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c972b60 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)action + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c972b60 + 0x130) * 8) != _DAT_7ffe9c972b60)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    plVar10 = (longlong *)0x0;
    if (bVar4) {
      plVar10 = (longlong *)action;
    }
  }
  cVar5 = FUN_7ffe9a8fecd0(plVar10,0,0);
  if (cVar5 != '\0') {
    if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a66bd70;
    if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c8edca8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar10 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8edca8 + 0x130) * 8)
        != _DAT_7ffe9c8edca8)) {
      plVar2 = (longlong *)plVar10[0x15];
      if (plVar2 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c9412e0 + 0x130) <= *(byte *)(*plVar2 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*plVar2 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c9412e0 + 0x130) * 8) == _DAT_7ffe9c9412e0)) {
          if ((*(byte *)(*plVar2 + 0x130) < *(byte *)(_DAT_7ffe9c9412e0 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar2 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c9412e0 + 0x130) * 8) != _DAT_7ffe9c9412e0)) {
            FUN_7ffe9996c950(plVar2);
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          if (plVar2[2] == 0) goto LAB_7ffe9a66bd70;
          uVar9 = FUN_7ffe9a328210(plVar2[2],0);
          if (DAT_7ffe9cad9c14 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c968830);
            DAT_7ffe9cad9c14 = '\x01';
          }
          if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          if ((int)((uVar9 ^ (int)uVar9 >> 0x1f) - ((int)uVar9 >> 0x1f)) < 0x168)
          goto LAB_7ffe9a66ba49;
        }
      }
      cVar5 = (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220));
      if (cVar5 != '\0') {
        plVar10 = (longlong *)plVar10[0x15];
        if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a66bd70;
        lVar11 = (**(code **)(*plVar10 + 0x368))(plVar10,*(undefined8 *)(*plVar10 + 0x370));
        if (lVar11 != 0) {
          uVar9 = *(uint *)(lVar11 + 0x18);
          if ((int)uVar9 < 2) {
            if (uVar9 == 0) {
LAB_7ffe9a66bd6a:
              FUN_7ffe9996d790();
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            fVar16 = *(float *)(lVar11 + 0x20);
          }
          else {
            fVar16 = _DAT_7ffe9c049b8c;
            for (uVar14 = 0; (int)uVar14 < (int)uVar9; uVar14 = uVar14 + 1) {
              if (uVar9 <= uVar14) goto LAB_7ffe9a66bd6a;
              fVar1 = *(float *)(lVar11 + 0x20 + (longlong)(int)uVar14 * 4);
              if (fVar1 < fVar16) {
                fVar16 = fVar1;
              }
            }
          }
          if (_DAT_7ffe9c04abb4 <= fVar16) {
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a66ba49:
  if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  uVar15 = FUN_7ffe9a4db1f0(2);
  cVar5 = FUN_7ffe99744fb0(0xf,playerAction,actor,2,uVar15,(ulonglong)uVar17 << 0x20,0,0,1);
  if (cVar5 == '\0') {
    return;
  }
  lVar11 = (**(code **)(*(longlong *)playerAction + 0x2b8))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2c0));
  if (lVar11 != 0) {
    FUN_7ffe99b14390(lVar11,2,uVar15);
    plVar10 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar10 != (longlong *)0x0) &&
       (lVar11 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
       lVar11 != 0)) {
      FUN_7ffe9a7c9b90(lVar11,0);
      plVar10 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar10 != (longlong *)0x0) &&
         (thisObject = (undefined *)
                       (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220)),
         thisObject != (undefined *)0x0)) {
        bVar6 = GemCartBufferManager_ContainsBuffer(thisObject,0x191,(undefined *)0x0);
        cVar5 = '\0';
        if (bVar6 != 0) {
          plVar10 = (longlong *)
                    (**(code **)(*(longlong *)playerAction + 0x298))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          if ((plVar10 == (longlong *)0x0) ||
             (lVar11 = (**(code **)(*plVar10 + 0x1b8))(plVar10,*(undefined8 *)(*plVar10 + 0x1c0)),
             lVar11 == 0)) goto LAB_7ffe9a66bd70;
          iVar8 = FUN_7ffe9a7fd580(lVar11,0x2e,1,0);
          if ((0 < iVar8) && (cVar7 = FUN_7ffe99a4d1d0(iVar8 * 10,0), cVar5 = '\0', cVar7 != '\0'))
          {
            cVar5 = '\x01';
          }
        }
        plVar10 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar10 != (longlong *)0x0) &&
           (lVar11 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
           lVar11 != 0)) {
          cVar7 = FUN_7ffe9a7c6d00(lVar11,0x2e);
          if ((cVar7 == '\0') && (cVar5 == '\0')) {
            plVar10 = (longlong *)
                      (**(code **)(*(longlong *)playerAction + 0x298))
                                (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
            if ((plVar10 == (longlong *)0x0) ||
               (lVar11 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
               lVar11 == 0)) goto LAB_7ffe9a66bd70;
            FUN_7ffe9a7cafa0(lVar11,0x29);
          }
          lVar11 = func_0x7ffe99940040(_DAT_7ffe9c90d450);
          FUN_7ffe9ad0cd00(lVar11,_DAT_7ffe9c966638);
          if (lVar11 != 0) {
            FUN_7ffe9acfd310(lVar11,1,cVar5,_DAT_7ffe9c9667d0);
            lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
            uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8ed808);
            FUN_7ffe9af8a010(uVar13,_DAT_7ffe9c960050);
            if (lVar12 != 0) {
              FUN_7ffe9a89f5e0(lVar12,0x294,uVar13,lVar11,1,0);
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a66bd70:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

