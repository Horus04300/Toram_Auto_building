
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float NormalAttackAction_calcRampageSkillRate
                (undefined *thisObject,undefined *playerAction,undefined *attackStage,
                undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined *thisObject_00;
  int iVar7;
  int iVar8;
  bool bVar9;
  bool bVar10;
  float fVar11;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadde95 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    DAT_7ffe9cadde95 = '\x01';
  }
  fVar11 = _DAT_7ffe9c049cfc;
  iVar7 = 0;
  plStackX_8 = (longlong *)0x0;
  if (1 < *(int *)(thisObject + 0xfc) - 10U) {
    return _DAT_7ffe9c049b18;
  }
  if ((((playerAction == (undefined *)0x0) ||
       (plVar5 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
       plVar5 == (longlong *)0x0)) ||
      (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)), lVar6 == 0))
     || (*(longlong *)(lVar6 + 0x40) == 0)) {
LAB_7ffe9a49cea8:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    fVar11 = (float)(*pcVar1)();
    return fVar11;
  }
  cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x40),0x29,&plStackX_8,_DAT_7ffe9c934418);
  if (cVar2 == '\0') {
    return _DAT_7ffe9c049b18;
  }
  if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a49cea8;
  bVar10 = false;
  if (*(char *)((longlong)plStackX_8 + 0x1c) == '\0') {
    return _DAT_7ffe9c049b18;
  }
  iVar4 = (**(code **)(*plStackX_8 + 0x1f8))(plStackX_8,0x32,*(undefined8 *)(*plStackX_8 + 0x200));
  plVar5 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar5 == (longlong *)0x0) ||
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
     thisObject_00 == (undefined *)0x0)) goto LAB_7ffe9a49cea8;
  bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x12e,(undefined *)0x0);
  plVar5 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar5 == (longlong *)0x0) ||
     (lVar6 = (**(code **)(*plVar5 + 0x1f8))(plVar5,*(undefined8 *)(*plVar5 + 0x200)), lVar6 == 0))
  goto LAB_7ffe9a49cea8;
  lVar6 = FUN_7ffe99c090e0(lVar6,0);
  if (lVar6 == 0) {
    bVar9 = false;
  }
  else {
    bVar9 = *(int *)(lVar6 + 0x38) == 10;
    bVar10 = *(int *)(lVar6 + 0x38) == 0xb;
  }
  if (bVar3 == 0 && iVar4 == 1) {
    if ((int)attackStage < 1) goto LAB_7ffe9a49ce68;
    if ((int)attackStage == 3) {
      if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a49cea8;
      iVar8 = 500;
      iVar4 = (uint)*(byte *)(plStackX_8 + 2) + (uint)*(byte *)(plStackX_8 + 2) * 4;
      iVar7 = 800;
    }
    else {
      if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a49cea8;
      iVar4 = (uint)*(byte *)(plStackX_8 + 2) + (uint)*(byte *)(plStackX_8 + 2) * 4;
      iVar7 = 200;
      iVar8 = 100;
    }
    if (!bVar10) {
      iVar7 = iVar8;
    }
    iVar7 = iVar7 + iVar4 * 2;
  }
  else {
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a49cea8;
    bVar3 = *(byte *)(plStackX_8 + 2);
    if (bVar9) {
      iVar7 = (uint)bVar3 + (uint)bVar3 * 4;
    }
    iVar7 = (uint)bVar3 * 4 + 0x6e + iVar7;
  }
  fVar11 = (float)iVar7;
LAB_7ffe9a49ce68:
  if (0.0 < *(float *)(thisObject + 0x188)) {
    fVar11 = fVar11 * *(float *)(thisObject + 0x188);
  }
  return fVar11 / _DAT_7ffe9c049cfc;
}

