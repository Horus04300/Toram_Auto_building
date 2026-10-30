
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AssassinStubAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  undefined1 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  longlong lVar6;
  undefined8 *puVar7;
  longlong *plVar8;
  undefined *puVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  uint uVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_48;
  float fStack_40;
  undefined8 uStack_38;
  float fStack_30;
  
  if (DAT_7ffe9cadeb06 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c910f70);
    FUN_7ffe9996d590(&DAT_7ffe9c936d48);
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadeb06 = '\x01';
  }
  FUN_7ffe9a4a5ca0(thisObject,actarAction,target,0);
  uVar11 = 202000000;
  if ((target != (undefined *)0x0) && (lVar6 = FUN_7ffe9bd9b890(target,0), lVar6 != 0)) {
    puVar7 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_38,lVar6,0);
    uStack_48 = *puVar7;
    fStack_40 = *(float *)(puVar7 + 1);
    if ((actarAction != (undefined *)0x0) && (lVar6 = FUN_7ffe9bd98a10(actarAction,0), lVar6 != 0))
    {
      puVar7 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_38,lVar6,0);
      fStack_40 = fStack_40 - *(float *)(puVar7 + 1);
      uStack_38 = CONCAT44(uStack_48._4_4_ - (float)((ulonglong)*puVar7 >> 0x20),
                           (float)uStack_48 - (float)*puVar7);
      fStack_30 = fStack_40;
      puVar7 = (undefined8 *)FUN_7ffe999fca00(&uStack_48,&uStack_38,0);
      uVar10 = *puVar7;
      fVar13 = *(float *)(puVar7 + 1);
      lVar6 = FUN_7ffe9bd9b890(target,0);
      if (lVar6 != 0) {
        puVar7 = (undefined8 *)FUN_7ffe9bdbf190(&uStack_48,lVar6,0);
        uStack_38 = *puVar7;
        fStack_30 = *(float *)(puVar7 + 1);
        uStack_48 = uVar10;
        fStack_40 = fVar13;
        uVar12 = FUN_7ffe99a4ef70(&uStack_48,&uStack_38,0);
        fVar13 = (float)(uVar12 & _DAT_7ffe9c049bf0);
        if (fVar13 <= _DAT_7ffe9c049dd8) {
          *(undefined4 *)(thisObject + 0x130) = 1;
          uVar11 = 0xc0a4682;
          iVar4 = 0x19a;
          if (thisObject[300] == '\0') {
            iVar4 = 0x6e;
          }
          *(float *)(thisObject + 0x120) =
               (float)(iVar4 + (uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 8);
          *(undefined4 *)(thisObject + 0x104) = 1;
        }
        else if ((fVar13 <= _DAT_7ffe9c049dd8) || (_DAT_7ffe9c049de8 < fVar13)) {
          *(undefined4 *)(thisObject + 0x130) = 0;
          iVar4 = 0x96;
          if (thisObject[300] == '\0') {
            iVar4 = 100;
          }
          *(float *)(thisObject + 0x120) = (float)(iVar4 + (uint)(byte)thisObject[0x14]);
          *(undefined4 *)(thisObject + 0x104) = 0;
        }
        else {
          *(undefined4 *)(thisObject + 0x130) = 2;
          uVar11 = 0xc0a4681;
          iVar4 = 0xcd;
          if (thisObject[300] == '\0') {
            iVar4 = 0x69;
          }
          *(float *)(thisObject + 0x120) =
               (float)(iVar4 + (uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 2);
          *(undefined4 *)(thisObject + 0x104) = 2;
        }
        uVar10 = *(undefined8 *)(thisObject + 0x138);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar3 = FUN_7ffe9bda1fa0(uVar10,0,0);
        if (cVar3 != '\0') {
          return;
        }
        plVar8 = *(longlong **)(thisObject + 0x138);
        if (((plVar8 != (longlong *)0x0) &&
            (plVar8 = (longlong *)
                      (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0)),
            plVar8 != (longlong *)0x0)) &&
           (puVar9 = (undefined *)
                     (**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220)),
           puVar9 != (undefined *)0x0)) {
          puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,0x3ec,(undefined *)0x0);
          if (puVar9 != (undefined *)0x0) {
            fVar13 = *(float *)(thisObject + 0x120);
            iVar4 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x4,(undefined *)0x0);
            *(float *)(thisObject + 0x120) = (float)iVar4 + fVar13;
            if (*(int *)(thisObject + 0x130) == 1) {
              uVar1 = thisObject[0x14];
              iVar4 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x2,(undefined *)0x0);
              uVar10 = func_0x7ffe99940040(_DAT_7ffe9c936d48);
              FUN_7ffe9a77a9a0(uVar10,uVar1,iVar4,0);
              plVar8 = *(longlong **)(thisObject + 0x138);
              if (((plVar8 == (longlong *)0x0) ||
                  (plVar8 = (longlong *)
                            (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0)),
                  plVar8 == (longlong *)0x0)) ||
                 (lVar6 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
                 lVar6 == 0)) goto LAB_7ffe9a631917;
              FUN_7ffe9a7c26c0(lVar6,uVar10,thisObject[0x10],0);
            }
          }
          plVar8 = *(longlong **)(thisObject + 0x138);
          if ((plVar8 != (longlong *)0x0) &&
             (plVar8 = (longlong *)
                       (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0)),
             plVar8 != (longlong *)0x0)) {
            lVar6 = (**(code **)(*plVar8 + 0x1b8))(plVar8,*(undefined8 *)(*plVar8 + 0x1c0));
            if (lVar6 != 0) {
              uVar12 = FUN_7ffe9a7fd580(lVar6,0x3ed,1,0);
              if (0 < (int)uVar12) {
                plVar8 = *(longlong **)(thisObject + 0x138);
                fVar13 = *(float *)(thisObject + 0x120);
                if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a631917;
                uVar10 = (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
                fVar14 = (float)FUN_7ffe9a7a7230(uVar12 & 0xff,uVar10,0);
                *(float *)(thisObject + 0x120) = fVar14 + fVar13;
              }
              lVar6 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c962758);
              if (lVar6 != 0) {
                uVar5 = FUN_7ffe9a4adee0(thisObject,*(undefined8 *)(thisObject + 0x138),lVar6,0);
                *(undefined4 *)(thisObject + 0x30) = uVar5;
              }
              uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
              FUN_7ffe9a9002e0(uVar10,uVar11,0);
              *(undefined8 *)(thisObject + 0x58) = uVar10;
              il2cpp_write_barrier_0();
              if ((*(longlong *)(thisObject + 0x58) != 0) &&
                 (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
                FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
                uVar11 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
                FUN_7ffe9ac2ed50(uVar11,thisObject,_DAT_7ffe9c910f70,0);
                FUN_7ffe9a4b2010(thisObject,uVar11,0);
                return;
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a631917:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

