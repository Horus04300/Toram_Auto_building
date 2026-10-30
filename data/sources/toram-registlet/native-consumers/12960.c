
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerActionManager_EventDamaged
               (undefined *thisObject,undefined *actor,undefined *action,undefined *damageData,
               byte id,byte trapDamage,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined8 *puVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined *puVar11;
  uint uVar12;
  uint uVar13;
  undefined4 uVar14;
  longlong *plStack_58;
  longlong *plStack_50;
  undefined8 uStack_48;
  float fStack_40;
  undefined8 uStack_38;
  float fStack_30;
  
  if (DAT_7ffe9caddca0 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c93cd40);
    FUN_7ffe9996d590(&DAT_7ffe9c969a58);
    DAT_7ffe9caddca0 = '\x01';
  }
  plStack_50 = (longlong *)0x0;
  if (*(longlong *)(thisObject + 0xc0) != 0) {
    FUN_7ffe9a40cb40(*(longlong *)(thisObject + 0xc0),0);
    if (damageData == (undefined *)0x0) {
      return;
    }
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (plVar6 != (longlong *)0x0) {
      cVar2 = (**(code **)(*plVar6 + 0x268))(plVar6,*(undefined8 *)(*plVar6 + 0x270));
      uVar12 = 0;
      if (cVar2 != '\0') {
        *(undefined8 *)(damageData + 0x14) = 0;
        *(undefined4 *)(damageData + 0x8c) = 0;
        FUN_7ffe9a824800(thisObject,0);
        return;
      }
      FUN_7ffe9a447f90();
      uVar13 = *(uint *)(damageData + 0x84);
      plStack_58 = (longlong *)0x0;
      plVar6 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar6 != (longlong *)0x0) &&
         (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
         lVar7 != 0)) {
        cVar2 = FUN_7ffe9abc2210(lVar7,0x34e,&plStack_58,_DAT_7ffe9c969a58);
        if (cVar2 != '\0') {
          if (plStack_58 == (longlong *)0x0) goto LAB_7ffe9a44cc6e;
          iVar4 = (**(code **)(*plStack_58 + 0x1f8))
                            (plStack_58,0x33,*(undefined8 *)(*plStack_58 + 0x200));
          plVar6 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar6 == (longlong *)0x0) ||
             (lVar7 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
             lVar7 == 0)) goto LAB_7ffe9a44cc6e;
          iVar5 = *(int *)(lVar7 + 0x14);
          plVar6 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar6 == (longlong *)0x0) ||
             (lVar7 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
             lVar7 == 0)) goto LAB_7ffe9a44cc6e;
          func_0x7ffe9a480d40(lVar7,iVar5 + iVar4,0,0);
          plVar6 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar6 == (longlong *)0x0) ||
             (lVar7 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
             lVar7 == 0)) goto LAB_7ffe9a44cc6e;
          if (0 < *(int *)(lVar7 + 0x24)) {
            plVar6 = (longlong *)
                     (**(code **)(*(longlong *)thisObject + 0x298))
                               (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
            if ((plVar6 == (longlong *)0x0) ||
               (lVar7 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
               lVar7 == 0)) goto LAB_7ffe9a44cc6e;
            uVar13 = uVar12;
            if (*(int *)(lVar7 + 0x24) - *(int *)(damageData + 0x84) < 0) {
              plVar6 = (longlong *)
                       (**(code **)(*(longlong *)thisObject + 0x298))
                                 (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
              if ((plVar6 == (longlong *)0x0) ||
                 (lVar7 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
                 lVar7 == 0)) goto LAB_7ffe9a44cc6e;
              uVar13 = *(int *)(damageData + 0x84) - *(int *)(lVar7 + 0x24);
            }
          }
        }
        FUN_7ffe9a824800(thisObject,0);
        plVar6 = (longlong *)
                 (**(code **)(*(longlong *)thisObject + 0x298))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar6 != (longlong *)0x0) &&
           (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
           lVar7 != 0)) {
          cVar2 = FUN_7ffe9a7c6d00(lVar7,0x426,0);
          lVar7 = (**(code **)(*(longlong *)thisObject + 0x298))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if (lVar7 != 0) {
            FUN_7ffe9a4a1500(lVar7,*(undefined4 *)(damageData + 0x84),cVar2,0);
            if (plStack_58 != (longlong *)0x0) {
              func_0x7ffe9a7a1530(plStack_58,uVar13,0);
              if (plStack_58 == (longlong *)0x0) goto LAB_7ffe9a44cc6e;
              iVar4 = (**(code **)(*plStack_58 + 0x1f8))
                                (plStack_58,0x33,*(undefined8 *)(*plStack_58 + 0x200));
              if (0 < iVar4) {
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)thisObject + 0x298))
                                   (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                if ((plVar6 == (longlong *)0x0) ||
                   (lVar7 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
                   lVar7 == 0)) goto LAB_7ffe9a44cc6e;
                iVar5 = *(int *)(lVar7 + 0x14);
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)thisObject + 0x298))
                                   (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                if ((plVar6 == (longlong *)0x0) ||
                   (lVar7 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
                   lVar7 == 0)) goto LAB_7ffe9a44cc6e;
                func_0x7ffe9a480d40(lVar7,iVar5 - iVar4,0,0);
              }
            }
            if (trapDamage != 0) {
              plVar6 = (longlong *)
                       (**(code **)(*(longlong *)thisObject + 0x298))
                                 (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
              if ((plVar6 == (longlong *)0x0) ||
                 (lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0)),
                 lVar7 == 0)) goto LAB_7ffe9a44cc6e;
              FUN_7ffe9a4dacc0(lVar7,0);
              plVar6 = (longlong *)
                       (**(code **)(*(longlong *)thisObject + 0x298))
                                 (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
              if ((plVar6 == (longlong *)0x0) ||
                 (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
                 lVar7 == 0)) goto LAB_7ffe9a44cc6e;
              FUN_7ffe9a7c9e70(lVar7,thisObject,0);
            }
            cVar3 = (**(code **)(*(longlong *)thisObject + 0x188))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
            if (cVar3 == '\0') {
              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar2 = FUN_7ffe9bda2160(actor,0,0);
              if (cVar2 != '\0') {
                if (*(longlong *)(thisObject + 0x20) == 0) goto LAB_7ffe9a44cc6e;
                puVar8 = (undefined8 *)
                         FUN_7ffe9bdbf710(&uStack_38,*(longlong *)(thisObject + 0x20),0);
                uStack_48 = *puVar8;
                fStack_40 = *(float *)(puVar8 + 1);
                if ((actor == (undefined *)0x0) || (lVar7 = FUN_7ffe9bd9b890(actor,0), lVar7 == 0))
                goto LAB_7ffe9a44cc6e;
                puVar8 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_38,lVar7,0);
                fStack_40 = fStack_40 - *(float *)(puVar8 + 1);
                lVar7 = *(longlong *)(thisObject + 0x48);
                iVar4 = *(int *)(damageData + 0x84);
                uStack_38 = CONCAT44(uStack_48._4_4_ - (float)((ulonglong)*puVar8 >> 0x20),
                                     (float)uStack_48 - (float)*puVar8);
                fStack_30 = fStack_40;
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)thisObject + 0x298))
                                   (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                if ((plVar6 == (longlong *)0x0) ||
                   (lVar9 = (**(code **)(*plVar6 + 0x198))(plVar6,*(undefined8 *)(*plVar6 + 0x1a0)),
                   lVar9 == 0)) goto LAB_7ffe9a44cc6e;
                iVar5 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar9);
                puVar8 = (undefined8 *)FUN_7ffe999fca00(&uStack_48,&uStack_38,0);
                if (lVar7 == 0) goto LAB_7ffe9a44cc6e;
                uStack_38 = *puVar8;
                fStack_30 = *(float *)(puVar8 + 1);
                uVar10 = FUN_7ffe9a9f43c0(lVar7,_DAT_7ffe9c049cc8,(float)iVar4 / (float)iVar5,
                                          &uStack_38,0);
                FUN_7ffe9bd9f640(thisObject,uVar10,0);
              }
            }
            else {
              plVar6 = (longlong *)
                       (**(code **)(*(longlong *)thisObject + 0x298))
                                 (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
              if (((plVar6 == (longlong *)0x0) ||
                  (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
                  lVar7 == 0)) || (*(longlong *)(lVar7 + 0x40) == 0)) goto LAB_7ffe9a44cc6e;
              cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x40),0x28e,&plStack_50,
                                       _DAT_7ffe9c934418);
              if (cVar3 != '\0') {
                if (plStack_50 == (longlong *)0x0) goto LAB_7ffe9a44cc6e;
                if (((*(byte *)(*plStack_50 + 0x130) < *(byte *)(_DAT_7ffe9c93cd40 + 0x130)) ||
                    (*(longlong *)
                      (*(longlong *)(*plStack_50 + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c93cd40 + 0x130) * 8) != _DAT_7ffe9c93cd40)) ||
                   (plStack_50 == (longlong *)0x0)) {
                  FUN_7ffe9996c950(plStack_50);
                  pcVar1 = (code *)swi(3);
                  (*pcVar1)();
                  return;
                }
                if ((char)plStack_50[10] == '\0') {
                  uVar12 = 1;
                }
              }
              plVar6 = (longlong *)
                       (**(code **)(*(longlong *)thisObject + 0x298))
                                 (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
              if ((plVar6 == (longlong *)0x0) ||
                 (puVar11 = (undefined *)
                            (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
                 puVar11 == (undefined *)0x0)) goto LAB_7ffe9a44cc6e;
              puVar11 = GemCartBufferManager_GetGemCartBuffer(puVar11,0x26,(undefined *)0x0);
              if ((puVar11 == (undefined *)0x0) ||
                 (iVar4 = GemCartBufferBase_GetValue(puVar11,(undefined *)0x2,(undefined *)0x0),
                 iVar4 == 0)) {
                FUN_7ffe9974ab00(0x29,thisObject,actor,id,*(undefined4 *)(damageData + 0x84));
              }
              else {
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)thisObject + 0x298))
                                   (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                if ((plVar6 == (longlong *)0x0) ||
                   (lVar7 = (**(code **)(*plVar6 + 0x198))(plVar6,*(undefined8 *)(*plVar6 + 0x1a0)),
                   lVar7 == 0)) goto LAB_7ffe9a44cc6e;
                iVar4 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar7);
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)thisObject + 0x298))
                                   (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                if ((plVar6 == (longlong *)0x0) ||
                   (lVar7 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
                   lVar7 == 0)) goto LAB_7ffe9a44cc6e;
                func_0x7ffe9a480d40(lVar7,(int)((float)iVar4 * _DAT_7ffe9c049b34),0,0);
                *(undefined4 *)(damageData + 0x8c) = 1;
                if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                uVar14 = FUN_7ffe9a4db1f0(1);
                *(undefined4 *)(damageData + 0x94) = uVar14;
                uVar14 = FUN_7ffe9a4db080(1);
                *(undefined4 *)(damageData + 0x98) = uVar14;
              }
              uVar13 = 0;
              if (cVar2 == '\0') {
                uVar13 = trapDamage & uVar12;
              }
              if (uVar13 != 0) {
                if (plStack_50 == (longlong *)0x0) goto LAB_7ffe9a44cc6e;
                if (((*(byte *)(*plStack_50 + 0x130) < *(byte *)(_DAT_7ffe9c93cd40 + 0x130)) ||
                    (*(longlong *)
                      (*(longlong *)(*plStack_50 + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c93cd40 + 0x130) * 8) != _DAT_7ffe9c93cd40)) ||
                   (plStack_50 == (longlong *)0x0)) {
                  FUN_7ffe9996c950(plStack_50);
                  pcVar1 = (code *)swi(3);
                  (*pcVar1)();
                  return;
                }
                FUN_7ffe9a7a0830(plStack_50,0);
                thisObject[0x40] = 0;
                thisObject[0x70] = 0;
                if (*(longlong *)(thisObject + 0x30) == 0) goto LAB_7ffe9a44cc6e;
                func_0x7ffe9a7e0410(*(longlong *)(thisObject + 0x30),0);
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)thisObject + 0x298))
                                   (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                if ((plVar6 == (longlong *)0x0) ||
                   (lVar7 = (**(code **)(*plVar6 + 0x198))(plVar6,*(undefined8 *)(*plVar6 + 0x1a0)),
                   lVar7 == 0)) goto LAB_7ffe9a44cc6e;
                iVar4 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar7);
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)thisObject + 0x298))
                                   (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
                if ((plVar6 == (longlong *)0x0) ||
                   (lVar7 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180)),
                   lVar7 == 0)) goto LAB_7ffe9a44cc6e;
                func_0x7ffe9a480d40(lVar7,(int)((float)iVar4 * _DAT_7ffe9c049b34),0,0);
              }
            }
            lVar7 = FUN_7ffe9a4565c0(thisObject,0);
            if (lVar7 != 0) {
              FUN_7ffe9a45bd40(lVar7,*(undefined4 *)(damageData + 0x84),0);
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a44cc6e:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

