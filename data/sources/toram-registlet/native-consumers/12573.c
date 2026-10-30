
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobaPlayerActionManager_AddAbnormalState
               (undefined *thisObject,undefined *actor,undefined *type,float time,float resist,
               float addResist,byte localId,byte force,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  longlong lVar10;
  undefined *thisObject_00;
  ulonglong uVar11;
  int iVar12;
  undefined1 uVar13;
  longlong *aplStack_58 [2];
  undefined8 uStack_48;
  undefined4 uStack_40;
  
  uVar11 = (ulonglong)type & 0xffffffff;
  if (DAT_7ffe9caddbfb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f32b8);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c8f4048);
    FUN_7ffe9996d590(&DAT_7ffe9c9227e8);
    FUN_7ffe9996d590(&DAT_7ffe9c92e5b8);
    FUN_7ffe9996d590(&DAT_7ffe9c9693b8);
    FUN_7ffe9996d590(&DAT_7ffe9c969488);
    FUN_7ffe9996d590(&DAT_7ffe9c969550);
    FUN_7ffe9996d590(&DAT_7ffe9c969620);
    FUN_7ffe9996d590(&DAT_7ffe9c9696e8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3b70);
    DAT_7ffe9caddbfb = '\x01';
  }
  lVar10 = 0;
  aplStack_58[0] = (longlong *)0x0;
  lVar5 = func_0x7ffe99940040(_DAT_7ffe9c8f3b70);
  func_0x7ffe999c3920(lVar5,0);
  if (lVar5 == 0) goto LAB_7ffe9a41f5cb;
  *(undefined **)(lVar5 + 0x10) = thisObject;
  il2cpp_write_barrier_0();
  *(byte *)(lVar5 + 0x18) = localId;
  iVar12 = (int)type;
  if (force == 0) {
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (((plVar6 == (longlong *)0x0) ||
        (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar7 == 0
        )) || (*(longlong *)(lVar7 + 0x50) == 0)) goto LAB_7ffe9a41f5cb;
    cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0xe7,aplStack_58);
    if (((cVar2 != '\0') && (3 < iVar12 - 1U)) && (iVar12 != 0x2b)) {
      plVar6 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if (((plVar6 != (longlong *)0x0) &&
          (lVar5 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
          lVar5 != 0)) && (FUN_7ffe9a7ca6f0(lVar5,0xe7,0), aplStack_58[0] != (longlong *)0x0)) {
        if (((*(byte *)(*aplStack_58[0] + 0x130) < *(byte *)(_DAT_7ffe9c92e5b8 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*aplStack_58[0] + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c92e5b8 + 0x130) * 8) != _DAT_7ffe9c92e5b8)) ||
           (aplStack_58[0] == (longlong *)0x0)) {
          FUN_7ffe9996c950(aplStack_58[0]);
          pcVar1 = (code *)swi(3);
          bVar3 = (*pcVar1)();
          return bVar3;
        }
        cVar2 = func_0x7ffe9a79fb10(aplStack_58[0],0);
        if (cVar2 == '\0') {
          return 0;
        }
        if (aplStack_58[0] != (longlong *)0x0) {
          uVar4 = (**(code **)(*aplStack_58[0] + 0x1f8))
                            (aplStack_58[0],0x32,*(undefined8 *)(*aplStack_58[0] + 0x200));
          if (*(longlong *)(thisObject + 0xb8) != 0) {
            FUN_7ffe9a6fbaa0(*(longlong *)(thisObject + 0xb8),0xcc,uVar4,0);
            return 0;
          }
        }
      }
      goto LAB_7ffe9a41f5cb;
    }
  }
  else {
    cVar2 = FUN_7ffe99b1ccd0(thisObject,0);
    if ((cVar2 == '\0') && (iVar12 == 4)) {
      plVar6 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar6 == (longlong *)0x0) ||
         (lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)),
         lVar7 == 0)) goto LAB_7ffe9a41f5cb;
      cVar2 = FUN_7ffe9a4d9f40(lVar7,uVar11,0);
      if (cVar2 != '\0') {
        return 0;
      }
    }
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar6 == (longlong *)0x0) ||
       (lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)), lVar7 == 0)
       ) goto LAB_7ffe9a41f5cb;
    FUN_7ffe9a4dbbb0(lVar7,uVar11,force);
  }
  uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
  FUN_7ffe9a2f3fb0(uVar8,lVar5);
  if (iVar12 < 0x13) {
    if (iVar12 == 1) {
      uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
      FUN_7ffe9a2f3fb0(uVar9,lVar5,_DAT_7ffe9c969488,0);
      lVar7 = FUN_7ffe9b5595f0(uVar8,uVar9,0);
      uVar8 = _DAT_7ffe9c8f32b8;
      if ((lVar7 != 0) && (lVar10 = func_0x7ffe9996c920(lVar7,_DAT_7ffe9c8f32b8), lVar10 == 0)) {
        FUN_7ffe9996c950(lVar7,uVar8);
        pcVar1 = (code *)swi(3);
        bVar3 = (*pcVar1)();
        return bVar3;
      }
      plVar6 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar6 == (longlong *)0x0) ||
         (lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)),
         lVar7 == 0)) goto LAB_7ffe9a41f5cb;
      cVar2 = FUN_7ffe9a4d8d20(lVar7,uVar11,time,resist,*(undefined1 *)(lVar5 + 0x18),force,lVar10,0
                              );
      if (cVar2 == '\0') {
        return 0;
      }
      if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a41f5cb;
      cVar2 = *(char *)(*(longlong *)(thisObject + 0x28) + 0x142);
      if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a41f5cb;
      FUN_7ffe9a40e460(*(longlong *)(thisObject + 0xa8),0);
      (**(code **)(*(longlong *)thisObject + 0x388))
                (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x390));
      plVar6 = *(longlong **)(thisObject + 0x38);
      *(undefined4 *)(thisObject + 0xd8) = 0;
      if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a41f5cb;
      uVar8 = 100;
    }
    else {
      if (iVar12 != 2) {
        if (iVar12 != 3) {
          if (iVar12 == 4) {
            uVar13 = *(undefined1 *)(lVar5 + 0x18);
            if (DAT_7ffe9cad9b47 == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
              DAT_7ffe9cad9b47 = '\x01';
            }
            uStack_40 = *(undefined4 *)(*(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8) + 1);
            uStack_48 = **(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8);
            cVar2 = FUN_7ffe9a41fb10(thisObject,actor,time,resist,uVar13,force,&uStack_48,0);
            if (cVar2 == '\0') {
              return 0;
            }
            return 1;
          }
          if (iVar12 == 0xb) {
            FUN_7ffe9a423610(thisObject,0);
            lVar10 = *(longlong *)(thisObject + 0xa8);
            if (lVar10 == 0) goto LAB_7ffe9a41f5cb;
            if (*(int *)(lVar10 + 0x40) == 0x201) {
              FUN_7ffe9a40e460(lVar10,0);
            }
            lVar10 = *(longlong *)thisObject;
            if (time != 0.0) {
              plVar6 = (longlong *)
                       (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
              if (plVar6 != (longlong *)0x0) {
                lVar10 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0));
                if (lVar10 != 0) {
                  bVar3 = FUN_7ffe9a4d8d20(lVar10,0xb,time,resist,*(undefined1 *)(lVar5 + 0x18),
                                           force,uVar8,0);
                  return bVar3;
                }
              }
              goto LAB_7ffe9a41f5cb;
            }
            plVar6 = (longlong *)
                     (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
            if ((plVar6 == (longlong *)0x0) ||
               (lVar10 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)),
               lVar10 == 0)) goto LAB_7ffe9a41f5cb;
            uVar13 = *(undefined1 *)(lVar5 + 0x18);
            uVar11 = 0xb;
            goto LAB_7ffe9a41ee93;
          }
          if (iVar12 == 0x12) {
            plVar6 = (longlong *)
                     (**(code **)(*(longlong *)thisObject + 0x298))
                               (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
            if ((plVar6 != (longlong *)0x0) &&
               (lVar10 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
               lVar10 != 0)) {
              cVar2 = FUN_7ffe9a7c6d00(lVar10,0x34c,0);
              if (cVar2 != '\0') {
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)thisObject + 0x298))
                                   (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                if ((plVar6 == (longlong *)0x0) ||
                   (lVar10 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0))
                   , lVar10 == 0)) goto LAB_7ffe9a41f5cb;
                FUN_7ffe9a7cafa0(lVar10,0x34c,0);
              }
              lVar10 = *(longlong *)thisObject;
              if (time == 0.0) {
                plVar6 = (longlong *)
                         (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
                if ((plVar6 != (longlong *)0x0) &&
                   (lVar10 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0))
                   , lVar10 != 0)) {
                  uVar13 = *(undefined1 *)(lVar5 + 0x18);
                  uVar11 = 0x12;
                  goto LAB_7ffe9a41ee93;
                }
              }
              else {
                plVar6 = (longlong *)
                         (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
                if (plVar6 != (longlong *)0x0) {
                  lVar10 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0));
                  if (lVar10 != 0) {
                    bVar3 = FUN_7ffe9a4d8d20(lVar10,0x12,time,resist,*(undefined1 *)(lVar5 + 0x18),
                                             force,uVar8,0);
                    return bVar3;
                  }
                }
              }
            }
            goto LAB_7ffe9a41f5cb;
          }
          goto LAB_7ffe9a41f0b9;
        }
        goto LAB_7ffe9a41f209;
      }
      uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
      FUN_7ffe9a2f3fb0(uVar9,lVar5,_DAT_7ffe9c969550,0);
      lVar7 = FUN_7ffe9b5595f0(uVar8,uVar9,0);
      uVar8 = _DAT_7ffe9c8f32b8;
      if ((lVar7 != 0) && (lVar10 = func_0x7ffe9996c920(lVar7,_DAT_7ffe9c8f32b8), lVar10 == 0)) {
        FUN_7ffe9996c950(lVar7,uVar8);
        pcVar1 = (code *)swi(3);
        bVar3 = (*pcVar1)();
        return bVar3;
      }
      plVar6 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar6 == (longlong *)0x0) ||
         (lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)),
         lVar7 == 0)) goto LAB_7ffe9a41f5cb;
      cVar2 = FUN_7ffe9a4d8d20(lVar7,uVar11,time,resist,*(undefined1 *)(lVar5 + 0x18),force,lVar10,0
                              );
      if (cVar2 == '\0') {
        return 0;
      }
      if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a41f5cb;
      cVar2 = *(char *)(*(longlong *)(thisObject + 0x28) + 0x142);
      if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a41f5cb;
      FUN_7ffe9a40e460(*(longlong *)(thisObject + 0xa8),0);
      (**(code **)(*(longlong *)thisObject + 0x388))
                (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x390));
      plVar6 = *(longlong **)(thisObject + 0x38);
      *(undefined4 *)(thisObject + 0xd8) = 0;
      if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a41f5cb;
      uVar8 = 0x65;
    }
    uVar9 = 1;
LAB_7ffe9a41f590:
    (**(code **)(*plVar6 + 0x178))(plVar6,uVar8,uVar9,*(undefined8 *)(*plVar6 + 0x180));
  }
  else {
    if (iVar12 == 0x14) {
LAB_7ffe9a41f209:
      uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
      FUN_7ffe9a2f3fb0(uVar9,lVar5,_DAT_7ffe9c969620,0);
      lVar7 = FUN_7ffe9b5595f0(uVar8,uVar9,0);
      uVar8 = _DAT_7ffe9c8f32b8;
      if ((lVar7 != 0) && (lVar10 = func_0x7ffe9996c920(lVar7,_DAT_7ffe9c8f32b8), lVar10 == 0)) {
        FUN_7ffe9996c950(lVar7,uVar8);
        pcVar1 = (code *)swi(3);
        bVar3 = (*pcVar1)();
        return bVar3;
      }
      plVar6 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar6 == (longlong *)0x0) ||
         (lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)),
         lVar7 == 0)) goto LAB_7ffe9a41f5cb;
      cVar2 = FUN_7ffe9a4d8d20(lVar7,uVar11,time,resist,*(undefined1 *)(lVar5 + 0x18),force,lVar10,0
                              );
      if (cVar2 == '\0') {
        return 0;
      }
      if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a41f5cb;
      cVar2 = *(char *)(*(longlong *)(thisObject + 0x28) + 0x142);
      if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a41f5cb;
      FUN_7ffe9a40e460(*(longlong *)(thisObject + 0xa8),0);
      (**(code **)(*(longlong *)thisObject + 0x388))
                (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x390));
      plVar6 = *(longlong **)(thisObject + 0x38);
      *(undefined4 *)(thisObject + 0xd8) = 0;
      if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a41f5cb;
      uVar8 = 0x69;
      uVar9 = 2;
      goto LAB_7ffe9a41f590;
    }
    if (iVar12 != 0x2b) {
      if (iVar12 == 0x2c) {
        lVar10 = (**(code **)(*(longlong *)thisObject + 0x2a8))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2b0));
        if (lVar10 != 0) {
          cVar2 = FUN_7ffe9a4d8d20(lVar10,uVar11,_DAT_7ffe9c049b40,resist,
                                   *(undefined1 *)(lVar5 + 0x18),force,uVar8,0);
          if (cVar2 == '\0') {
            return 0;
          }
          if (*(undefined **)(thisObject + 0x98) != (undefined *)0x0) {
            MobaPlayer_CalcItemDelay(*(undefined **)(thisObject + 0x98),time,0,(undefined *)0x0);
            plVar6 = (longlong *)
                     (**(code **)(*(longlong *)thisObject + 0x298))
                               (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
            if ((plVar6 != (longlong *)0x0) &&
               (thisObject_00 =
                     (undefined *)
                     (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
               thisObject_00 != (undefined *)0x0)) {
              plVar6 = (longlong *)
                       GemCartBufferManager_GetGemCartBuffer
                                 (thisObject_00,(short)type + 0x21,(undefined *)0x0);
              if (plVar6 == (longlong *)0x0) {
                return 1;
              }
              if (*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7ffe9c8f4048 + 0x130)) {
                return 1;
              }
              if (*(longlong *)
                   (*(longlong *)(*plVar6 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c8f4048 + 0x130) * 8) != _DAT_7ffe9c8f4048) {
                return 1;
              }
              *(undefined1 *)(plVar6 + 3) = 1;
              return 1;
            }
          }
        }
        goto LAB_7ffe9a41f5cb;
      }
LAB_7ffe9a41f0b9:
      lVar10 = *(longlong *)thisObject;
      if (time == 0.0) {
        plVar6 = (longlong *)
                 (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
        if ((plVar6 != (longlong *)0x0) &&
           (lVar10 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)),
           lVar10 != 0)) {
          uVar13 = *(undefined1 *)(lVar5 + 0x18);
LAB_7ffe9a41ee93:
          bVar3 = FUN_7ffe9a4d8ee0(lVar10,uVar11,uVar13,force,uVar8,0);
          return bVar3;
        }
      }
      else {
        plVar6 = (longlong *)
                 (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
        if (plVar6 != (longlong *)0x0) {
          lVar10 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0));
          if (lVar10 != 0) {
            bVar3 = FUN_7ffe9a4d8d20(lVar10,uVar11,time,resist,*(undefined1 *)(lVar5 + 0x18),force,
                                     uVar8,0);
            return bVar3;
          }
        }
      }
      goto LAB_7ffe9a41f5cb;
    }
    uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
    FUN_7ffe9a2f3fb0(uVar9,lVar5,_DAT_7ffe9c9696e8,0);
    lVar7 = FUN_7ffe9b5595f0(uVar8,uVar9,0);
    uVar8 = _DAT_7ffe9c8f32b8;
    if ((lVar7 != 0) && (lVar10 = func_0x7ffe9996c920(lVar7,_DAT_7ffe9c8f32b8), lVar10 == 0)) {
      FUN_7ffe9996c950(lVar7,uVar8);
      pcVar1 = (code *)swi(3);
      bVar3 = (*pcVar1)();
      return bVar3;
    }
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar6 == (longlong *)0x0) ||
       (lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)), lVar7 == 0)
       ) goto LAB_7ffe9a41f5cb;
    cVar2 = FUN_7ffe9a4d8d20(lVar7,0x2b,time,resist,*(undefined1 *)(lVar5 + 0x18),force,lVar10,0);
    if (cVar2 == '\0') {
      return 0;
    }
    if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a41f5cb;
    cVar2 = *(char *)(*(longlong *)(thisObject + 0x28) + 0x142);
    if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a41f5cb;
    FUN_7ffe9a40e460(*(longlong *)(thisObject + 0xa8),0);
    (**(code **)(*(longlong *)thisObject + 0x388))
              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x390));
    plVar6 = *(longlong **)(thisObject + 0x38);
    *(undefined4 *)(thisObject + 0xd8) = 0;
    if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a41f5cb;
    if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7ffe9c9227e8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9227e8 + 0x130) * 8)
        != _DAT_7ffe9c9227e8)) {
      FUN_7ffe9996c950(plVar6);
      pcVar1 = (code *)swi(3);
      bVar3 = (*pcVar1)();
      return bVar3;
    }
    func_0x7ffe9a7e60b0(plVar6,0);
  }
  if (*(longlong *)(thisObject + 0x28) == 0) {
LAB_7ffe9a41f5cb:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    bVar3 = (*pcVar1)();
    return bVar3;
  }
  *(undefined1 *)(*(longlong *)(thisObject + 0x28) + 0x139) = 0;
  if (cVar2 != '\0') {
    if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a41f5cb;
    *(undefined1 *)(*(longlong *)(thisObject + 0x28) + 0x138) = 1;
  }
  return 1;
}

