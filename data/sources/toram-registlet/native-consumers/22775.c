
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void StormBlazerAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  longlong lVar6;
  undefined8 *puVar7;
  longlong *plVar8;
  undefined8 uVar9;
  longlong *plVar10;
  undefined *thisObject_00;
  float fVar11;
  undefined4 uVar12;
  longlong lStackX_10;
  undefined1 auStack_18 [16];
  
  if (DAT_7ffe9cadebae == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c969f20);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadebae = '\x01';
  }
  plVar10 = (longlong *)0x0;
  iVar5 = 0;
  lStackX_10 = 0;
  FUN_7ffe9a4a5ca0(thisObject,actarAction,target,0);
  cVar3 = func_0x7ffe9a4aea60(thisObject,0);
  if (cVar3 == '\0') {
    if (actarAction != (undefined *)0x0) {
      if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      plVar10 = (longlong *)0x0;
      if (bVar2) {
        plVar10 = (longlong *)actarAction;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda2160(plVar10,0,0);
    if (cVar3 != '\0') {
      if ((actarAction != (undefined *)0x0) && (lVar6 = FUN_7ffe9bd98a10(actarAction,0), lVar6 != 0)
         ) {
        puVar7 = (undefined8 *)FUN_7ffe9bdbf710(auStack_18,lVar6,0);
        uVar12 = *(undefined4 *)(puVar7 + 1);
        *(undefined8 *)(thisObject + 300) = *puVar7;
        *(undefined4 *)(thisObject + 0x134) = uVar12;
        if ((plVar10 != (longlong *)0x0) &&
           ((plVar8 = (longlong *)
                      (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
            plVar8 != (longlong *)0x0 &&
            (lVar6 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
            lVar6 != 0)))) {
          cVar3 = FUN_7ffe9abc2210(lVar6,0x36,&lStackX_10,_DAT_7ffe9c969f20);
          if (cVar3 != '\0') {
            if ((lStackX_10 == 0) || (iVar5 = func_0x7ffe9a7a4750(lStackX_10,0), lStackX_10 == 0))
            goto LAB_7ffe9a65b3ce;
            if (*(char *)(lStackX_10 + 0x13) != '\0') {
              plVar8 = (longlong *)
                       (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
              if ((plVar8 == (longlong *)0x0) ||
                 (lVar6 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
                 lVar6 == 0)) goto LAB_7ffe9a65b3ce;
              FUN_7ffe9a7cafa0(lVar6,0x36);
            }
          }
          *(int *)(thisObject + 0x104) = iVar5;
          if (iVar5 < 1) {
            uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            FUN_7ffe9a9002e0(uVar9,0xbf0a019,0);
            *(undefined8 *)(thisObject + 0x58) = uVar9;
            il2cpp_write_barrier_0();
            if ((*(longlong *)(thisObject + 0x58) == 0) ||
               (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 == 0))
            goto LAB_7ffe9a65b3ce;
            FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
          }
          else {
            fVar11 = (float)iVar5 * _DAT_7ffe9c049b4c + _DAT_7ffe9c049b18;
            *(float *)(thisObject + 0x120) = (float)iVar5 * *(float *)(thisObject + 0x120);
            uVar12 = func_0x7ffe99a4d6a0(fVar11,0);
            *(undefined4 *)(thisObject + 0x48) = uVar12;
            *(int *)(thisObject + 0x128) = iVar5 * iVar5 * 4;
          }
          plVar10 = (longlong *)
                    (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
          if ((plVar10 != (longlong *)0x0) &&
             (thisObject_00 =
                   (undefined *)
                   (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220)),
             thisObject_00 != (undefined *)0x0)) {
            bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x135,(undefined *)0x0);
            if (bVar4 == 0) {
              return;
            }
            thisObject[0x138] = 1;
            return;
          }
        }
      }
LAB_7ffe9a65b3ce:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  return;
}

