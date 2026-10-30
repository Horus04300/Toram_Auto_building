
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float PlayerActionManager_get_MoveSpeed(undefined *thisObject,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined *puVar8;
  undefined8 uVar9;
  longlong *plVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  longlong *plStackX_8;
  
  if (DAT_7ffe9caddc83 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    FUN_7ffe9996d590(&DAT_7ffe9c95c7b0);
    FUN_7ffe9996d590(&DAT_7ffe9c96e9e0);
    DAT_7ffe9caddc83 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  plVar6 = (longlong *)
           (**(code **)(*(longlong *)thisObject + 0x298))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar6 == (longlong *)0x0) ||
     (lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)), lVar7 == 0))
  goto LAB_7ffe9a4565ae;
  cVar4 = FUN_7ffe9a4daa60(lVar7,0xc,0);
  if (cVar4 != '\0') {
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar6 == (longlong *)0x0) ||
       (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar7 == 0)
       ) goto LAB_7ffe9a4565ae;
    cVar4 = FUN_7ffe9a7c6d00(lVar7,0x4c7,0);
    if (cVar4 == '\0') {
      plVar6 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar6 == (longlong *)0x0) ||
         (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
         lVar7 == 0)) goto LAB_7ffe9a4565ae;
      cVar4 = FUN_7ffe9a7c6d00(lVar7,0x2c2,0);
      if (cVar4 == '\0') {
        return 0.0;
      }
    }
  }
  lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
  if (lVar7 == 0) goto LAB_7ffe9a4565ae;
  iVar5 = FUN_7ffe9a872680(lVar7,0);
  if (iVar5 != 0xf) {
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar7 == 0) goto LAB_7ffe9a4565ae;
    iVar5 = FUN_7ffe9a872680(lVar7,0);
    if (iVar5 != 0x14) {
      lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
      if (lVar7 == 0) goto LAB_7ffe9a4565ae;
      iVar5 = FUN_7ffe9a872680(lVar7,0);
      fVar3 = _DAT_7ffe9c049b34;
      fVar12 = _DAT_7ffe9c049b18;
      if (iVar5 != 0x17) {
        lVar7 = *(longlong *)(thisObject + 0xc0);
        if (lVar7 == 0) goto LAB_7ffe9a4565ae;
        fVar13 = _DAT_7ffe9c049d88;
        if ((((*(int *)(lVar7 + 0x40) != 0x101) && (*(int *)(lVar7 + 0x40) != 0x102)) &&
            (fVar13 = _DAT_7ffe9c049cd8, *(int *)(lVar7 + 0x40) != 0x201)) &&
           (cVar4 = FUN_7ffe9a478bc0(thisObject,0), fVar13 = fVar12, cVar4 != '\0')) {
          plVar6 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar6 == (longlong *)0x0) ||
             (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
             lVar7 == 0)) goto LAB_7ffe9a4565ae;
          cVar4 = FUN_7ffe9a7c4f20(lVar7,0);
          fVar13 = _DAT_7ffe9c049d88;
          if (cVar4 == '\0') {
            plVar6 = (longlong *)
                     (**(code **)(*(longlong *)thisObject + 0x298))
                               (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
            if ((plVar6 == (longlong *)0x0) ||
               (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
               lVar7 == 0)) goto LAB_7ffe9a4565ae;
            cVar4 = FUN_7ffe9a7c6d00(lVar7,0x28e,0);
            pcVar1 = *(code **)(*(longlong *)thisObject + 0x298);
            if (cVar4 == '\0') {
              plVar6 = (longlong *)(*pcVar1)();
              if ((plVar6 == (longlong *)0x0) ||
                 (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
                 lVar7 == 0)) goto LAB_7ffe9a4565ae;
              cVar4 = FUN_7ffe9a7cbb30(lVar7,0x52,&plStackX_8);
              if (cVar4 == '\0') {
LAB_7ffe9a45617b:
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)thisObject + 0x298))
                                   (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                if ((plVar6 == (longlong *)0x0) ||
                   (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
                   lVar7 == 0)) goto LAB_7ffe9a4565ae;
                cVar4 = FUN_7ffe9a7cbb30(lVar7,0x36e,&plStackX_8,0);
                if (cVar4 == '\0') {
                  plVar6 = (longlong *)
                           (**(code **)(*(longlong *)thisObject + 0x298))
                                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                  if ((plVar6 == (longlong *)0x0) ||
                     (lVar7 = (**(code **)(*plVar6 + 0x1c8))
                                        (plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar7 == 0))
                  goto LAB_7ffe9a4565ae;
                  cVar4 = FUN_7ffe9a7c6d00(lVar7,0x2c2,0);
                  fVar13 = _DAT_7ffe9c049b70;
                  if (cVar4 == '\0') {
                    plVar6 = (longlong *)
                             (**(code **)(*(longlong *)thisObject + 0x298))
                                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0))
                    ;
                    if ((plVar6 == (longlong *)0x0) ||
                       (lVar7 = (**(code **)(*plVar6 + 0x1c8))
                                          (plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar7 == 0))
                    goto LAB_7ffe9a4565ae;
                    cVar4 = FUN_7ffe9a7c6d00(lVar7,0x444,0);
                    fVar13 = fVar12;
                    if (cVar4 != '\0') {
                      plVar6 = (longlong *)
                               (**(code **)(*(longlong *)thisObject + 0x298))
                                         (thisObject,
                                          *(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                      if ((plVar6 == (longlong *)0x0) ||
                         (lVar7 = (**(code **)(*plVar6 + 0x1c8))
                                            (plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar7 == 0))
                      goto LAB_7ffe9a4565ae;
                      uVar9 = 0x444;
                      goto LAB_7ffe9a4562c9;
                    }
                  }
                  goto LAB_7ffe9a456385;
                }
                if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4565ae;
                iVar5 = (**(code **)(*plStackX_8 + 0x1f8))
                                  (plStackX_8,0x45,*(undefined8 *)(*plStackX_8 + 0x200));
              }
              else {
                if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4565ae;
                lVar7 = *plStackX_8;
                if (((*(byte *)(lVar7 + 0x130) < *(byte *)(_DAT_7ffe9c96e9e0 + 0x130)) ||
                    (*(longlong *)
                      (*(longlong *)(lVar7 + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c96e9e0 + 0x130) * 8) != _DAT_7ffe9c96e9e0)) ||
                   (plStackX_8 == (longlong *)0x0)) {
                  FUN_7ffe9996c950(plStackX_8);
                  pcVar1 = (code *)swi(3);
                  fVar12 = (float)(*pcVar1)();
                  return fVar12;
                }
                if ((char)plStackX_8[9] == '\0') goto LAB_7ffe9a45617b;
                iVar5 = (**(code **)(lVar7 + 0x1f8))(plStackX_8,0x45,*(undefined8 *)(lVar7 + 0x200))
                ;
              }
            }
            else {
              plVar6 = (longlong *)
                       (*pcVar1)(thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
              if ((plVar6 == (longlong *)0x0) ||
                 (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
                 lVar7 == 0)) goto LAB_7ffe9a4565ae;
              uVar9 = 0x28e;
LAB_7ffe9a4562c9:
              plVar6 = (longlong *)FUN_7ffe9a7c90b0(lVar7,uVar9,0);
              if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a4565ae;
              iVar5 = (**(code **)(*plVar6 + 0x1f8))(plVar6,0x32,*(undefined8 *)(*plVar6 + 0x200));
            }
            fVar13 = (float)iVar5 * fVar3 + fVar12;
          }
        }
LAB_7ffe9a456385:
        plVar6 = (longlong *)
                 (**(code **)(*(longlong *)thisObject + 0x298))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar6 == (longlong *)0x0) ||
           (lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)),
           lVar7 == 0)) goto LAB_7ffe9a4565ae;
        cVar4 = FUN_7ffe9a4daa60(lVar7,0xb);
        fVar11 = _DAT_7ffe9c049b4c;
        if (cVar4 != '\0') {
          plVar6 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar6 == (longlong *)0x0) ||
             (puVar8 = (undefined *)
                       (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
             puVar8 == (undefined *)0x0)) goto LAB_7ffe9a4565ae;
          puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x12,(undefined *)0x0);
          if (puVar8 != (undefined *)0x0) {
            iVar5 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
            fVar11 = ((float)iVar5 * fVar3 + fVar12) * fVar11;
          }
          plVar6 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar6 == (longlong *)0x0) ||
             (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
             lVar7 == 0)) goto LAB_7ffe9a4565ae;
          cVar4 = FUN_7ffe9a7c6d00(lVar7,0x4c7,0);
          if (cVar4 != '\0') {
            fVar11 = fVar12;
          }
          plVar6 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar6 == (longlong *)0x0) ||
             (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
             lVar7 == 0)) goto LAB_7ffe9a4565ae;
          cVar4 = FUN_7ffe9a7c6d00(lVar7,0x2c2,0);
          if (cVar4 != '\0') {
            fVar11 = fVar12;
          }
          fVar13 = fVar13 * fVar11;
        }
        if (*(longlong *)(thisObject + 0x28) != 0) {
          return fVar13 * *(float *)(*(longlong *)(thisObject + 0x28) + 0x38);
        }
        goto LAB_7ffe9a4565ae;
      }
    }
  }
  lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar7 != 0) {
    plVar6 = *(longlong **)(lVar7 + 0x28);
    if (plVar6 == (longlong *)0x0) {
      lVar7 = *(longlong *)(thisObject + 0x28);
    }
    else {
      if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7ffe9c95c7b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c95c7b0 + 0x130) * 8)
          != _DAT_7ffe9c95c7b0)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      lVar7 = *(longlong *)(thisObject + 0x28);
      plVar10 = (longlong *)0x0;
      if (bVar2) {
        plVar10 = plVar6;
      }
      if (plVar10 != (longlong *)0x0) {
        if (lVar7 != 0) {
          fVar12 = (float)FUN_7ffe9a61de10(plVar10,*(undefined4 *)(lVar7 + 0x38),0);
          return fVar12;
        }
        goto LAB_7ffe9a4565ae;
      }
    }
    if (lVar7 != 0) {
      return *(float *)(lVar7 + 0x38);
    }
  }
LAB_7ffe9a4565ae:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar12 = (float)(*pcVar1)();
  return fVar12;
}

