
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkillBufferManager_AddSelfDanceBuf
               (undefined *thisObject,undefined *id,byte level,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  undefined *puVar5;
  longlong lVar6;
  int iVar7;
  undefined7 in_register_00000081;
  float fVar8;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadf58a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9341c8,id,CONCAT71(in_register_00000081,level));
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    DAT_7ffe9cadf58a = '\x01';
  }
  iVar7 = 5;
  plStackX_8 = (longlong *)0x0;
  if (*(longlong *)(thisObject + 0x40) == 0) goto LAB_7ffe9a7c2d63;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(thisObject + 0x40),(ulonglong)id & 0xffffffff,&plStackX_8,
                           _DAT_7ffe9c934418);
  if (cVar3 == '\0') {
    if (*(longlong *)(thisObject + 0x50) == 0) goto LAB_7ffe9a7c2d63;
    cVar3 = FUN_7ffe9ad5f0a0(*(longlong *)(thisObject + 0x50),(ulonglong)id & 0xffffffff);
    if (cVar3 != '\0') goto LAB_7ffe9a7c2c96;
  }
  else {
    if ((plStackX_8 == (longlong *)0x0) ||
       (iVar4 = (**(code **)(*plStackX_8 + 0x1f8))(plStackX_8,0x14), plStackX_8 == (longlong *)0x0))
    goto LAB_7ffe9a7c2d63;
    if (*(float *)((longlong)plStackX_8 + 0x14) <= _DAT_7ffe9c049ce0) {
      iVar7 = iVar4 + 1;
      if (10 < iVar4 + 1) {
        iVar7 = 10;
      }
    }
    else {
      iVar7 = 0;
      if (-1 < iVar4 + -1) {
        iVar7 = iVar4 + -1;
      }
    }
LAB_7ffe9a7c2c96:
    FUN_7ffe9a7ca6f0(thisObject,(ulonglong)id & 0xffffffff);
  }
  fVar8 = _DAT_7ffe9c049ce8;
  plVar1 = *(longlong **)(thisObject + 0x20);
  if ((plVar1 != (longlong *)0x0) &&
     (puVar5 = (undefined *)(**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
     puVar5 != (undefined *)0x0)) {
    puVar5 = GemCartBufferManager_GetGemCartBuffer(puVar5,0x2f,(undefined *)0x0);
    if ((puVar5 != (undefined *)0x0) && ((int)id != 0x323)) {
      iVar4 = GemCartBufferBase_GetValue(puVar5,(undefined *)0x2,(undefined *)0x0);
      fVar8 = fVar8 - (float)iVar4;
    }
    lVar6 = func_0x7ffe9a7f4970((ulonglong)id & 0xffffffff,level,1,fVar8,iVar7,0);
    if (lVar6 != 0) {
      FUN_7ffe9a7c26c0(thisObject,lVar6,0,0);
    }
    FUN_7ffe9a7c3660(thisObject,0);
    return;
  }
LAB_7ffe9a7c2d63:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

