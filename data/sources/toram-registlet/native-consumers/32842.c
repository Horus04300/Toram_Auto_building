
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void P_DeffenceAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  byte bVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  longlong lVar8;
  longlong *plVar9;
  longlong lVar10;
  undefined *puVar11;
  undefined8 uVar12;
  int iVar13;
  longlong *plVar14;
  longlong *plStackX_10;
  
  if (DAT_7ffe9cadf89a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92eda0);
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c954998);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    FUN_7ffe9996d590(&DAT_7ffe9c8f2ca8);
    FUN_7ffe9996d590(&DAT_7ffe9c907ed0);
    DAT_7ffe9cadf89a = '\x01';
  }
  plStackX_10 = (longlong *)0x0;
  lVar8 = func_0x7ffe99940040(_DAT_7ffe9c907ed0);
  func_0x7ffe999c3920(lVar8,0);
  FUN_7ffe9a4a5ca0(thisObject,actarAction,target,0);
  if (lVar8 != 0) {
    if (actarAction == (undefined *)0x0) {
      *(undefined8 *)(lVar8 + 0x10) = 0;
    }
    else {
      if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
        bVar3 = false;
      }
      else {
        bVar3 = true;
      }
      puVar11 = (undefined *)0x0;
      if (bVar3) {
        puVar11 = actarAction;
      }
      *(undefined **)(lVar8 + 0x10) = puVar11;
    }
    plVar14 = (longlong *)(lVar8 + 0x10);
    il2cpp_write_barrier_0();
    lVar10 = *plVar14;
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(lVar10,0,0);
    if (cVar4 == '\0') {
      return;
    }
    plVar9 = (longlong *)*plVar14;
    if (((plVar9 != (longlong *)0x0) &&
        (plVar9 = (longlong *)
                  (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
        plVar9 != (longlong *)0x0)) &&
       (lVar10 = (**(code **)(*plVar9 + 0x198))(plVar9,*(undefined8 *)(*plVar9 + 0x1a0)),
       lVar10 != 0)) {
      iVar5 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar10);
      bVar1 = thisObject[0x14];
      if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      iVar6 = func_0x7ffe9b506b70(0,bVar1 - 5,0);
      plVar9 = (longlong *)*plVar14;
      iVar13 = 0xfa;
      if (thisObject[0x14] != '\n') {
        iVar13 = 0;
      }
      iVar13 = iVar13 + (uint)bVar1 * 100 + iVar6 * 0x96;
      if (((plVar9 != (longlong *)0x0) &&
          (plVar9 = (longlong *)
                    (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
          plVar9 != (longlong *)0x0)) &&
         (puVar11 = (undefined *)
                    (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220)),
         puVar11 != (undefined *)0x0)) {
        iVar6 = GemCartBufferManager_GetBufferLevel(puVar11,0x3fc,(undefined *)0x0);
        if (0 < iVar6) {
          iVar13 = (int)(((float)((iVar6 + 0x14) * 5) / _DAT_7ffe9c049cfc) * (float)iVar13);
        }
        if (((*(uint *)(thisObject + 0x108) & 0x200) != 0) && (thisObject[0x14] == '\n')) {
          plStackX_10 = (longlong *)0x0;
          plVar9 = (longlong *)*plVar14;
          if ((plVar9 == (longlong *)0x0) ||
             (((plVar9 = (longlong *)
                         (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
               plVar9 == (longlong *)0x0 ||
               (lVar10 = (**(code **)(*plVar9 + 0x1b8))(plVar9,*(undefined8 *)(*plVar9 + 0x1c0)),
               lVar10 == 0)) || (*(longlong *)(lVar10 + 0x68) == 0)))) goto LAB_7ffe9a83112b;
          cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x68),0x208,&plStackX_10,_DAT_7ffe9c935bd0
                                  );
          if (cVar4 != '\0') {
            if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a83112b;
            if (((*(byte *)(*plStackX_10 + 0x130) < *(byte *)(_DAT_7ffe9c954998 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStackX_10 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c954998 + 0x130) * 8) != _DAT_7ffe9c954998)) ||
               (plStackX_10 == (longlong *)0x0)) {
              FUN_7ffe9996c950(plStackX_10);
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            iVar6 = FUN_7ffe9a7b4880(plStackX_10,4,1);
            iVar13 = iVar13 + iVar6;
          }
        }
        plVar14 = (longlong *)*plVar14;
        if (plVar14 != (longlong *)0x0) {
          uVar12 = (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
          cVar4 = FUN_7ffe9a7a65d0(uVar12,lVar8 + 0x18,0);
          if (cVar4 != '\0') {
            uVar12 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
            FUN_7ffe999e6880(uVar12,lVar8,_DAT_7ffe9c8f2ca8,0);
            FUN_7ffe9a4b20c0(thisObject,uVar12,0);
          }
          bVar1 = thisObject[0x14];
          if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          uVar7 = func_0x7ffe9b506d80((int)((uint)bVar1 * iVar5) / 100,iVar13,0);
          uVar12 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar12,0xbed6fb0,0);
          *(undefined8 *)(thisObject + 0x58) = uVar12;
          il2cpp_write_barrier_0();
          lVar8 = *(longlong *)(thisObject + 0x58);
          uVar12 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar12,0x1cfe9b8,0);
          if (lVar8 != 0) {
            *(undefined8 *)(lVar8 + 0x20) = uVar12;
            il2cpp_write_barrier_0();
            if (((*(longlong *)(thisObject + 0x58) != 0) &&
                (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar8 != 0)) &&
               (lVar8 = *(longlong *)(lVar8 + 0x50), lVar8 != 0)) {
              FUN_7ffe9ad10e00(lVar8,0xb,uVar7,_DAT_7ffe9c949490);
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a83112b:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

