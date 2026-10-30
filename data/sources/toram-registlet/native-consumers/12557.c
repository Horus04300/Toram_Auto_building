
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float MobaPlayerActionManager_get_MoveSpeed(undefined *thisObject,undefined *methodInfo)

{
  code *pcVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined *puVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  longlong *plStackX_8;
  
  if (DAT_7ffe9caddbf1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c96e9e0);
    DAT_7ffe9caddbf1 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  plVar5 = (longlong *)
           (**(code **)(*(longlong *)thisObject + 0x298))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar5 == (longlong *)0x0) ||
     (lVar6 = (**(code **)(*plVar5 + 0x1e8))(plVar5,*(undefined8 *)(*plVar5 + 0x1f0)), lVar6 == 0))
  goto LAB_7ffe9a42d34d;
  cVar3 = FUN_7ffe9a4daa60(lVar6,0xc,0);
  if (cVar3 != '\0') {
    plVar5 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar5 == (longlong *)0x0) ||
       (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)), lVar6 == 0)
       ) goto LAB_7ffe9a42d34d;
    cVar3 = FUN_7ffe9a7c6d00(lVar6,0x4c7,0);
    if (cVar3 == '\0') {
      return 0.0;
    }
  }
  cVar3 = (**(code **)(*(longlong *)thisObject + 0x278))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x280));
  if ((cVar3 != '\0') && (lVar6 = FUN_7ffe9a42d360(thisObject,0), lVar6 != 0)) {
    lVar6 = FUN_7ffe9a42d360(thisObject,0);
    if (lVar6 == 0) goto LAB_7ffe9a42d34d;
    iVar4 = func_0x7ffe9a5f23a0(lVar6,0);
    if (iVar4 < 4) {
      if (*(longlong *)(thisObject + 0x28) != 0) {
        return *(float *)(*(longlong *)(thisObject + 0x28) + 0x38) * _DAT_7ffe9c049b4c;
      }
      goto LAB_7ffe9a42d34d;
    }
  }
  fVar2 = _DAT_7ffe9c049b34;
  fVar9 = _DAT_7ffe9c049b18;
  lVar6 = *(longlong *)(thisObject + 0xa8);
  if (lVar6 == 0) goto LAB_7ffe9a42d34d;
  fVar10 = _DAT_7ffe9c049d88;
  if ((((*(int *)(lVar6 + 0x40) != 0x101) && (*(int *)(lVar6 + 0x40) != 0x102)) &&
      (fVar10 = _DAT_7ffe9c049cd8, *(int *)(lVar6 + 0x40) != 0x201)) &&
     (cVar3 = FUN_7ffe9a478bc0(thisObject,0), fVar10 = fVar9, cVar3 != '\0')) {
    plVar5 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar5 == (longlong *)0x0) ||
       (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)), lVar6 == 0)
       ) goto LAB_7ffe9a42d34d;
    cVar3 = FUN_7ffe9a7c6d00(lVar6,0x28e,0);
    pcVar1 = *(code **)(*(longlong *)thisObject + 0x298);
    if (cVar3 == '\0') {
      plVar5 = (longlong *)(*pcVar1)();
      if ((plVar5 == (longlong *)0x0) ||
         (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)),
         lVar6 == 0)) goto LAB_7ffe9a42d34d;
      cVar3 = FUN_7ffe9a7cbb30(lVar6,0x52,&plStackX_8);
      if (cVar3 == '\0') {
LAB_7ffe9a42d021:
        plVar5 = (longlong *)
                 (**(code **)(*(longlong *)thisObject + 0x298))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar5 == (longlong *)0x0) ||
           (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)),
           lVar6 == 0)) goto LAB_7ffe9a42d34d;
        cVar3 = FUN_7ffe9a7cbb30(lVar6,0x36e,&plStackX_8,0);
        if (cVar3 == '\0') {
          plVar5 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar5 == (longlong *)0x0) ||
             (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)),
             lVar6 == 0)) goto LAB_7ffe9a42d34d;
          cVar3 = FUN_7ffe9a7c6d00(lVar6,0x444,0);
          if (cVar3 == '\0') goto LAB_7ffe9a42d20b;
          plVar5 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if (((plVar5 == (longlong *)0x0) ||
              (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)),
              lVar6 == 0)) ||
             (plVar5 = (longlong *)FUN_7ffe9a7c90b0(lVar6,0x444,0), plVar5 == (longlong *)0x0))
          goto LAB_7ffe9a42d34d;
          iVar4 = (**(code **)(*plVar5 + 0x1f8))(plVar5,0x32,*(undefined8 *)(*plVar5 + 0x200));
        }
        else {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a42d34d;
          iVar4 = (**(code **)(*plStackX_8 + 0x1f8))
                            (plStackX_8,0x45,*(undefined8 *)(*plStackX_8 + 0x200));
        }
      }
      else {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a42d34d;
        lVar6 = *plStackX_8;
        if (((*(byte *)(lVar6 + 0x130) < *(byte *)(_DAT_7ffe9c96e9e0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(lVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96e9e0 + 0x130) * 8
              ) != _DAT_7ffe9c96e9e0)) || (plStackX_8 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_8);
          pcVar1 = (code *)swi(3);
          fVar9 = (float)(*pcVar1)();
          return fVar9;
        }
        if ((char)plStackX_8[9] == '\0') goto LAB_7ffe9a42d021;
        iVar4 = (**(code **)(lVar6 + 0x1f8))(plStackX_8,0x45,*(undefined8 *)(lVar6 + 0x200));
      }
      fVar10 = (float)iVar4 * fVar2 + fVar9;
    }
    else {
      plVar5 = (longlong *)(*pcVar1)(thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if (((plVar5 == (longlong *)0x0) ||
          (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)),
          lVar6 == 0)) ||
         (plVar5 = (longlong *)FUN_7ffe9a7c90b0(lVar6,0x28e,0), plVar5 == (longlong *)0x0))
      goto LAB_7ffe9a42d34d;
      iVar4 = (**(code **)(*plVar5 + 0x1f8))(plVar5,0x32,*(undefined8 *)(*plVar5 + 0x200));
      fVar10 = (float)iVar4 * fVar2 + fVar9;
    }
  }
LAB_7ffe9a42d20b:
  plVar5 = (longlong *)
           (**(code **)(*(longlong *)thisObject + 0x298))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar5 == (longlong *)0x0) ||
     (lVar6 = (**(code **)(*plVar5 + 0x1e8))(plVar5,*(undefined8 *)(*plVar5 + 0x1f0)), lVar6 == 0))
  goto LAB_7ffe9a42d34d;
  cVar3 = FUN_7ffe9a4daa60(lVar6,0xb);
  fVar8 = _DAT_7ffe9c049b4c;
  if (cVar3 != '\0') {
    plVar5 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar5 == (longlong *)0x0) ||
       (puVar7 = (undefined *)
                 (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
       puVar7 == (undefined *)0x0)) goto LAB_7ffe9a42d34d;
    puVar7 = GemCartBufferManager_GetGemCartBuffer(puVar7,0x12,(undefined *)0x0);
    if (puVar7 != (undefined *)0x0) {
      iVar4 = GemCartBufferBase_GetValue(puVar7,(undefined *)0x2,(undefined *)0x0);
      fVar8 = ((float)iVar4 * fVar2 + fVar9) * fVar8;
    }
    plVar5 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar5 == (longlong *)0x0) ||
       (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)), lVar6 == 0)
       ) goto LAB_7ffe9a42d34d;
    cVar3 = FUN_7ffe9a7c6d00(lVar6,0x4c7,0);
    if (cVar3 != '\0') {
      fVar8 = fVar9;
    }
    fVar10 = fVar10 * fVar8;
  }
  if (*(longlong *)(thisObject + 0x28) != 0) {
    return fVar10 * *(float *)(*(longlong *)(thisObject + 0x28) + 0x38);
  }
LAB_7ffe9a42d34d:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar9 = (float)(*pcVar1)();
  return fVar9;
}

