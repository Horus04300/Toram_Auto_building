
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkillActionBase_AddTemporarySkillBuffer
               (undefined *thisObject,undefined *playerAction,undefined *methodInfo)

{
  int iVar1;
  longlong lVar2;
  code *pcVar3;
  longlong lVar4;
  char cVar5;
  byte bVar6;
  int iVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined *thisObject_00;
  undefined8 uVar10;
  uint uVar11;
  bool bVar12;
  longlong *plStackX_20;
  
  if (DAT_7ffe9cadfed5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c91ffd0);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c9132e8);
    FUN_7ffe9996d590(&DAT_7ffe9c8feb30);
    FUN_7ffe9996d590(&DAT_7ffe9c903520);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9cadfed5 = '\x01';
  }
  uVar11 = 0;
  plStackX_20 = (longlong *)0x0;
  if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
    func_0x7ffe9996d830(_DAT_7ffe9c94c0a0);
  }
  lVar2 = **(longlong **)(_DAT_7ffe9c94c0a0 + 0xb8);
  if (lVar2 != 0) {
    do {
      if (*(int *)(lVar2 + 0x18) <= (int)uVar11) {
        return;
      }
      if (*(uint *)(lVar2 + 0x18) <= uVar11) {
        FUN_7ffe9996d790();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      iVar1 = *(int *)(lVar2 + 0x20 + (longlong)(int)uVar11 * 4);
      if ((((playerAction == (undefined *)0x0) ||
           (plVar8 = (longlong *)
                     (**(code **)(*(longlong *)playerAction + 0x298))
                               (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
           plVar8 == (longlong *)0x0)) ||
          (lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
          lVar9 == 0)) || (*(longlong *)(lVar9 + 0x50) == 0)) break;
      cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x50),iVar1,&plStackX_20,_DAT_7ffe9c934418);
      if (cVar5 != '\0') {
        if (iVar1 == 0x268) {
          plVar8 = (longlong *)
                   (**(code **)(*(longlong *)playerAction + 0x298))
                             (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          if ((plVar8 == (longlong *)0x0) ||
             (thisObject_00 =
                   (undefined *)
                   (**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220)),
             thisObject_00 == (undefined *)0x0)) break;
          bVar6 = GemCartBufferManager_ContainsBuffer(thisObject_00,0xd8,(undefined *)0x0);
          if (bVar6 == 0) {
            iVar7 = (**(code **)(*(longlong *)thisObject + 0x188))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
            bVar12 = iVar7 == 0x27d;
LAB_7ffe9a8fc114:
            if (!bVar12) goto LAB_7ffe9a8fc11a;
          }
        }
        else {
          if (iVar1 == 0x53) {
            cVar5 = (**(code **)(*(longlong *)thisObject + 0x228))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x230));
            if (cVar5 != '\0') goto LAB_7ffe9a8fc22f;
          }
          else if (iVar1 == 0x22e) {
            if (plStackX_20 != (longlong *)0x0) {
              if (((*(byte *)(*plStackX_20 + 0x130) < *(byte *)(_DAT_7ffe9c8feb30 + 0x130)) ||
                  (*(longlong *)
                    (*(longlong *)(*plStackX_20 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c8feb30 + 0x130) * 8) != _DAT_7ffe9c8feb30)) ||
                 (plStackX_20 == (longlong *)0x0)) {
                FUN_7ffe9996c950(plStackX_20);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              cVar5 = func_0x7ffe99ad7b20(plStackX_20,0,0);
              bVar12 = cVar5 == '\0';
              goto LAB_7ffe9a8fc114;
            }
            break;
          }
LAB_7ffe9a8fc11a:
          plVar8 = plStackX_20;
          if (plStackX_20 == (longlong *)0x0) break;
          if (((*(byte *)(*plStackX_20 + 0x130) < *(byte *)(_DAT_7ffe9c903520 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStackX_20 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c903520 + 0x130) * 8) != _DAT_7ffe9c903520)) ||
             (plStackX_20 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStackX_20);
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          lVar4 = plStackX_20[4];
          (**(code **)(*plStackX_20 + 0x2a8))(plStackX_20,*(undefined8 *)(*plStackX_20 + 0x2b0));
          lVar9 = *(longlong *)(thisObject + 0x50);
          uVar10 = func_0x7ffe99940040(_DAT_7ffe9c91ffd0);
          FUN_7ffe9a8edff0(uVar10,iVar1,plVar8,(int)lVar4,0);
          if (lVar9 == 0) break;
          FUN_7ffe99743100(lVar9,uVar10,_DAT_7ffe9c9132e8);
          cVar5 = (**(code **)(*plVar8 + 0x288))(plVar8,*(undefined8 *)(*plVar8 + 0x290));
          if (cVar5 != '\0') {
            plVar8 = (longlong *)
                     (**(code **)(*(longlong *)playerAction + 0x298))
                               (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
            if ((plVar8 == (longlong *)0x0) ||
               (lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
               lVar9 == 0)) break;
            FUN_7ffe9a7ca6f0(lVar9,iVar1,0);
          }
        }
      }
LAB_7ffe9a8fc22f:
      uVar11 = uVar11 + 1;
    } while( true );
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

