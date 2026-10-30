
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhantomRaveAction_CalcPhantomRaveLastDamageRate
               (undefined *thisObject,undefined *status,undefined *bonusLastRate,
               undefined *noBonusLastRate,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  longlong lVar5;
  undefined *puVar6;
  longlong *thisObject_00;
  float comboRate;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadec9a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c904970);
    DAT_7ffe9cadec9a = '\x01';
  }
  *(undefined4 *)bonusLastRate = 0;
  fVar9 = 0.0;
  *(undefined4 *)noBonusLastRate = 0;
  fVar8 = 0.0;
  thisObject[0x158] = 1;
  plStackX_8 = (longlong *)0x0;
  if (status != (undefined *)0x0) {
    lVar5 = (**(code **)(*(longlong *)status + 0x1b8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
    if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x68) != 0)) {
      cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar5 + 0x68),0x48,&plStackX_8,_DAT_7ffe9c935bd0);
      if (cVar2 != '\0') {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a682bed;
        iVar4 = (**(code **)(*plStackX_8 + 0x178))
                          (plStackX_8,8,*(undefined8 *)(*plStackX_8 + 0x180));
        fVar8 = (float)iVar4 / _DAT_7ffe9c049cfc + 0.0;
      }
      lVar5 = (**(code **)(*(longlong *)status + 0x1b8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
      if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x68) != 0)) {
        cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar5 + 0x68),0x1e4,&plStackX_8,_DAT_7ffe9c935bd0);
        if (cVar2 != '\0') {
          puVar6 = (undefined *)
                   (**(code **)(*(longlong *)status + 0x218))
                             (status,*(undefined8 *)(*(longlong *)status + 0x220));
          if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a682bed;
          puVar6 = GemCartBufferManager_GetGemCartBuffer(puVar6,0x3f0,(undefined *)0x0);
          if (puVar6 != (undefined *)0x0) {
            GemCartBufferBase_GetValue(puVar6,(undefined *)0x2,(undefined *)0x0);
          }
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a682bed;
          (**(code **)(*plStackX_8 + 0x178))(plStackX_8,0,*(undefined8 *)(*plStackX_8 + 0x180));
          cVar2 = FUN_7ffe9a8fea70(thisObject,100);
          if (cVar2 != '\0') {
            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a682bed;
            iVar4 = (**(code **)(*plStackX_8 + 0x178))(plStackX_8,8);
            fVar9 = (float)iVar4 / _DAT_7ffe9c049cfc + 0.0;
          }
        }
        fVar10 = fVar9 + fVar8 + _DAT_7ffe9c049b18;
        fVar8 = (float)FUN_7ffe9a4a7d60(thisObject,status);
        comboRate = (float)FUN_7ffe9a4a81a0(thisObject,0);
        puVar6 = (undefined *)
                 (**(code **)(*(longlong *)status + 0x218))
                           (status,*(undefined8 *)(*(longlong *)status + 0x220));
        if (puVar6 != (undefined *)0x0) {
          thisObject_00 =
               (longlong *)GemCartBufferManager_GetGemCartBuffer(puVar6,0x2c,(undefined *)0x0);
          if (thisObject_00 != (longlong *)0x0) {
            iVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
            if ((*(byte *)(*thisObject_00 + 0x130) < *(byte *)(_DAT_7ffe9c904970 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*thisObject_00 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c904970 + 0x130) * 8) != _DAT_7ffe9c904970)) {
              FUN_7ffe9996c950(thisObject_00,_DAT_7ffe9c904970);
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            bVar3 = GemCartBuffer_NothingStyleBuff_CheckBuffValid
                              ((undefined *)thisObject_00,iVar4,*(undefined **)(thisObject + 0xd8),
                               comboRate,(undefined *)0x0);
            if (bVar3 != 0) {
              iVar4 = GemCartBufferBase_GetValue
                                ((undefined *)thisObject_00,(undefined *)0x2,(undefined *)0x0);
              comboRate = comboRate + (float)iVar4 / _DAT_7ffe9c049cfc;
            }
          }
          fVar7 = (float)FUN_7ffe9a4a8ed0(thisObject,status,0);
          *(float *)bonusLastRate = fVar8 * fVar10 * comboRate * fVar7;
          thisObject[0x158] = 0;
          fVar8 = (float)FUN_7ffe9a4a7d60(thisObject,status,0);
          fVar9 = fVar9 + _DAT_7ffe9c049b18;
          thisObject[0x158] = 1;
          *(float *)noBonusLastRate = fVar9 * fVar8 * comboRate * fVar7;
          return;
        }
      }
    }
  }
LAB_7ffe9a682bed:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

