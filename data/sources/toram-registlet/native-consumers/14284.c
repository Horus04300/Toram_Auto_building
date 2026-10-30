
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float PlayerAttackBase_CalcLastDamageRate
                (undefined *thisObject,undefined *playerStatus,undefined *attackType,
                undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  int iVar3;
  undefined *thisObject_00;
  longlong *thisObject_01;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float comboRate;
  
  if (DAT_7ffe9caddec1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c904970);
    DAT_7ffe9caddec1 = '\x01';
  }
  fVar5 = PlayerAttackBase_CalcSkillMasteryLastDamageRate
                    (thisObject,playerStatus,(undefined *)((ulonglong)attackType & 0xffffffff),
                     (undefined *)0x0);
  fVar6 = (float)FUN_7ffe9a4a7d60(thisObject,playerStatus);
  iVar4 = *(int *)(thisObject + 0xcc);
  iVar3 = (**(code **)(*(longlong *)thisObject + 0x618))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x620));
  iVar4 = iVar4 + iVar3;
  if (iVar4 < 10) {
    iVar4 = 10;
  }
  else {
    iVar3 = 0x96;
    if (0x96 < iVar4) goto LAB_7ffe9a4aa980;
  }
  iVar3 = iVar4;
LAB_7ffe9a4aa980:
  comboRate = (float)iVar3 / _DAT_7ffe9c049cfc;
  if (playerStatus != (undefined *)0x0) {
    thisObject_00 =
         (undefined *)
         (**(code **)(*(longlong *)playerStatus + 0x218))
                   (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x220));
    if (thisObject_00 != (undefined *)0x0) {
      thisObject_01 =
           (longlong *)GemCartBufferManager_GetGemCartBuffer(thisObject_00,0x2c,(undefined *)0x0);
      fVar5 = fVar5 + _DAT_7ffe9c049b18;
      if (thisObject_01 != (longlong *)0x0) {
        iVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
        if ((*(byte *)(*thisObject_01 + 0x130) < *(byte *)(_DAT_7ffe9c904970 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*thisObject_01 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c904970 + 0x130) * 8) != _DAT_7ffe9c904970)) {
          FUN_7ffe9996c950(thisObject_01,_DAT_7ffe9c904970);
          pcVar1 = (code *)swi(3);
          fVar5 = (float)(*pcVar1)();
          return fVar5;
        }
        bVar2 = GemCartBuffer_NothingStyleBuff_CheckBuffValid
                          ((undefined *)thisObject_01,iVar4,*(undefined **)(thisObject + 0xd8),
                           comboRate,(undefined *)0x0);
        if (bVar2 != 0) {
          iVar4 = GemCartBufferBase_GetValue
                            ((undefined *)thisObject_01,(undefined *)0x2,(undefined *)0x0);
          comboRate = comboRate + (float)iVar4 / _DAT_7ffe9c049cfc;
        }
      }
      fVar7 = (float)FUN_7ffe9a4a8ed0(thisObject,playerStatus,0);
      return fVar7 * (fVar5 + 0.0) * fVar6 * comboRate;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar5 = (float)(*pcVar1)();
  return fVar5;
}

