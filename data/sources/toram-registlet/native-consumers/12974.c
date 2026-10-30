
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerActionManager_CalcAbnormalKnockBackDistance
               (undefined *thisObject,undefined *damageData,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined *puVar7;
  float fVar8;
  undefined4 uVar9;
  float fVar10;
  longlong *plStackX_10;
  
  if (DAT_7ffe9caddcad == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    DAT_7ffe9caddcad = '\x01';
  }
  plStackX_10 = (longlong *)0x0;
  if (damageData != (undefined *)0x0) {
    if (*(int *)(damageData + 0x8c) != 4) {
      return;
    }
    fVar10 = 0.0;
    iVar3 = FUN_7ffe9a826ae0(thisObject,damageData,0);
    plVar5 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar5 != (longlong *)0x0) &&
       (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)), lVar6 != 0)
       ) {
      cVar2 = FUN_7ffe9a7cbb30(lVar6,0x307,&plStackX_10,0);
      if (cVar2 != '\0') {
        if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a4468f1;
        iVar4 = (**(code **)(*plStackX_10 + 0x1f8))
                          (plStackX_10,0x32,*(undefined8 *)(*plStackX_10 + 0x200));
        iVar3 = iVar3 + iVar4;
      }
      plVar5 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar5 != (longlong *)0x0) &&
         (puVar7 = (undefined *)
                   (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
         puVar7 != (undefined *)0x0)) {
        puVar7 = GemCartBufferManager_GetGemCartBuffer(puVar7,0x4e,(undefined *)0x0);
        if (puVar7 != (undefined *)0x0) {
          iVar4 = GemCartBufferBase_GetValue(puVar7,(undefined *)0x2,(undefined *)0x0);
          fVar10 = (float)iVar4;
        }
        if ((iVar3 < 1) && (fVar10 <= 0.0)) {
          return;
        }
        iVar4 = 0;
        if (-1 < 100 - iVar3) {
          iVar4 = 100 - iVar3;
        }
        fVar8 = ((float)iVar4 / _DAT_7ffe9c049cfc) * *(float *)(damageData + 0x94) -
                fVar10 / _DAT_7ffe9c049ce4;
        fVar10 = _DAT_7ffe9c049b40;
        if (_DAT_7ffe9c049b40 <= fVar8) {
          fVar10 = fVar8;
        }
        *(float *)(damageData + 0x94) = fVar10;
        if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        uVar9 = FUN_7ffe9a4daf00(4,fVar10);
        *(undefined4 *)(damageData + 0x98) = uVar9;
        return;
      }
    }
  }
LAB_7ffe9a4468f1:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

