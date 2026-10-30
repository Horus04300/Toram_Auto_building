
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void TriggerSlashAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  int iVar2;
  code *pcVar3;
  bool bVar4;
  undefined4 uVar5;
  longlong *plVar6;
  undefined *puVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  longlong *plVar11;
  float fVar12;
  double dVar13;
  float fVar14;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadebbd == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadebbd = '\x01';
  }
  uStackX_8 = 0;
  if (actarAction == (undefined *)0x0) {
    *(undefined4 *)(thisObject + 0x30) = 1;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    *(undefined4 *)(thisObject + 0x30) = 1;
    plVar11 = (longlong *)0x0;
    if (bVar4) {
      plVar11 = (longlong *)actarAction;
    }
    if (plVar11 != (longlong *)0x0) {
      plVar6 = (longlong *)
               (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      if (plVar6 != (longlong *)0x0) {
        puVar7 = (undefined *)
                 (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
        if (puVar7 != (undefined *)0x0) {
          puVar7 = GemCartBufferManager_GetGemCartBuffer(puVar7,0xc9,(undefined *)0x0);
          if (puVar7 != (undefined *)0x0) {
            lVar8 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
            if (lVar8 == 0) goto LAB_7ffe9a65e7ef;
            uVar5 = FUN_7ffe9a4a1cc0(lVar8,0);
            *(undefined4 *)(thisObject + 0x30) = uVar5;
          }
          uVar5 = FUN_7ffe9a4adfc0(plVar11,&uStackX_8,0);
          *(undefined4 *)(thisObject + 0xfc) = uVar5;
          uVar5 = FUN_7ffe9a4adf80(uStackX_8,0);
          fVar14 = _DAT_7ffe9c049cfc;
          bVar1 = thisObject[0x14];
          *(undefined4 *)(thisObject + 0x20) = uVar5;
          fVar12 = (float)((bVar1 + 0x1e) * 5);
          *(float *)(thisObject + 0x120) = fVar12;
          if (*(int *)(thisObject + 0xfc) == 10) {
            thisObject[300] = 1;
          }
          else if (*(int *)(thisObject + 0xfc) == 0xb) {
            *(float *)(thisObject + 0x120) = fVar12 + fVar14;
          }
          *(uint *)(thisObject + 0x124) = (bVar1 + 0x14) * 10;
          *(float *)(thisObject + 0x120) = *(float *)(thisObject + 0x120) / fVar14;
          fVar14 = (float)bVar1 / _DAT_7ffe9c049ce0;
          if (DAT_7ffe9cad9e25 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c968830);
            DAT_7ffe9cad9e25 = '\x01';
          }
          if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          dVar13 = (double)func_0x7ffe99997768((double)fVar14);
          *(int *)(thisObject + 0x128) = (4 - (int)dVar13) * 100;
          uVar9 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
          uVar5 = FUN_7ffe9a4aabb0(uVar9,0);
          *(undefined4 *)(thisObject + 0x78) = uVar5;
          FUN_7ffe9a4aacd0(thisObject,plVar11,0);
          iVar2 = *(int *)(thisObject + 0xfc);
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          uVar10 = 0x4a769;
          if (iVar2 != 0xb) {
            uVar10 = 0x320c9;
          }
          FUN_7ffe9a9002e0(uVar9,uVar10,0);
          *(undefined8 *)(thisObject + 0x58) = uVar9;
          il2cpp_write_barrier_0();
          return;
        }
      }
    }
  }
LAB_7ffe9a65e7ef:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

