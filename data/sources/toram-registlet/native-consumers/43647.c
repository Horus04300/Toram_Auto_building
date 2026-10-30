
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnActionRoomChangeHateMine
               (undefined *thisObject,undefined *game,undefined *archetype,undefined *mobList,
               undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined *thisObject_00;
  longlong *plVar10;
  undefined8 uVar11;
  longlong *plVar12;
  longlong *plVar13;
  longlong *plVar14;
  
  if (DAT_7ffe9cae097f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c962ce0);
    FUN_7ffe9996d590(&DAT_7ffe9c962da8);
    FUN_7ffe9996d590(&DAT_7ffe9c962c10);
    FUN_7ffe9996d590(&DAT_7ffe9c962e78);
    FUN_7ffe9996d590(&DAT_7ffe9c962f40);
    FUN_7ffe9996d590(&DAT_7ffe9c90c8f8);
    FUN_7ffe9996d590(&DAT_7ffe9c923ea8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    FUN_7ffe9996d590(&DAT_7ffe9c951220);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(&DAT_7ffe9c9015a0);
    DAT_7ffe9cae097f = '\x01';
  }
  func_0x7ffe999c3920(_DAT_7ffe9c9015a0,0);
  lVar8 = FUN_7ffe9a47bac0(0);
  plVar14 = (longlong *)0x0;
  bVar4 = 0;
  if ((archetype != (undefined *)0x0) && (lVar8 != 0)) {
    cVar3 = func_0x7ffe9abd5d00(*(undefined8 *)(archetype + 0x20),*(undefined8 *)(lVar8 + 0x50));
    plVar10 = plVar14;
    plVar9 = plVar14;
    if (cVar3 != '\0') {
      plVar9 = (longlong *)FUN_7ffe9a47fe30(lVar8,0);
      thisObject_00 = (undefined *)FUN_7ffe9a47f780(lVar8,0);
      if ((((thisObject_00 == (undefined *)0x0) ||
           (bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3d,(undefined *)0x0),
           plVar9 == (longlong *)0x0)) ||
          (plVar10 = (longlong *)
                     (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
          plVar10 == (longlong *)0x0)) ||
         (lVar8 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
         lVar8 == 0)) goto LAB_7ffe9aa98b64;
      cVar3 = FUN_7ffe9a7c6d00(lVar8,0x46b,0);
      plVar10 = (longlong *)0x0;
      if (cVar3 != '\0' || bVar4 != 0) {
        plVar10 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c90c8f8);
        FUN_7ffe9ada4840(plVar10,_DAT_7ffe9c962c10);
        plVar12 = plVar14;
        if (mobList == (undefined *)0x0) goto LAB_7ffe9aa98b64;
        while( true ) {
          uVar5 = (uint)plVar12;
          if ((int)*(uint *)(mobList + 0x18) <= (int)uVar5) break;
          if (*(uint *)(mobList + 0x18) <= uVar5) goto LAB_7ffe9aa98b6a;
          uVar11 = *(undefined8 *)(mobList + (longlong)(int)uVar5 * 8 + 0x20);
          lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (((lVar8 == 0) || (*(longlong *)(lVar8 + 0x48) == 0)) ||
             (FUN_7ffe9a347020(*(longlong *)(lVar8 + 0x48),uVar11,0), plVar10 == (longlong *)0x0))
          goto LAB_7ffe9aa98b64;
          FUN_7ffe9ada6cf0(plVar10,uVar11);
          plVar12 = (longlong *)(ulonglong)(uVar5 + 1);
        }
      }
    }
    lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
    uVar11 = FUN_7ffe9ab92be0(mobList,_DAT_7ffe9c923ea8);
    if (lVar8 != 0) {
      FUN_7ffe9a336ec0(lVar8,uVar11,0);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar3 = FUN_7ffe9bda2160(plVar9,0,0);
      if (cVar3 == '\0') {
        return;
      }
      if (((plVar9 != (longlong *)0x0) &&
          (plVar12 = (longlong *)
                     (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
          plVar12 != (longlong *)0x0)) &&
         (lVar8 = (**(code **)(*plVar12 + 0x1c8))(plVar12,*(undefined8 *)(*plVar12 + 0x1d0)),
         lVar8 != 0)) {
        cVar3 = FUN_7ffe9a7c6d00(lVar8,0x229,0);
        if (cVar3 != '\0') {
          plVar12 = (longlong *)
                    (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
          if ((plVar12 == (longlong *)0x0) ||
             (lVar8 = (**(code **)(*plVar12 + 0x1c8))(plVar12,*(undefined8 *)(*plVar12 + 0x1d0)),
             lVar8 == 0)) goto LAB_7ffe9aa98b64;
          FUN_7ffe9a7cafa0(lVar8,0x229,0);
          plVar12 = (longlong *)plVar9[6];
          plVar13 = plVar14;
          if (plVar12 != (longlong *)0x0) {
            if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar12 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) != _DAT_7ffe9c922a40)) {
              bVar2 = false;
            }
            else {
              bVar2 = true;
            }
            if (bVar2) {
              plVar13 = plVar12;
            }
          }
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar3 = FUN_7ffe9bda2160(plVar13,0,0);
          if (cVar3 != '\0') {
            if (plVar13 == (longlong *)0x0) goto LAB_7ffe9aa98b64;
            FUN_7ffe9a46d2b0(plVar13,0);
          }
        }
        FUN_7ffe9a808f60(plVar9,0);
        if ((plVar10 != (longlong *)0x0) &&
           (iVar6 = func_0x7ffe9acd8120(plVar10,_DAT_7ffe9c962e78), 0 < iVar6)) {
          FUN_7ffe9a841a80(plVar9,0);
        }
        FUN_7ffe9a83a910(plVar9,0);
        if (bVar4 == 0) {
          return;
        }
        bVar2 = false;
        if (plVar10 == (longlong *)0x0) {
          return;
        }
        iVar6 = func_0x7ffe9acd8120(plVar10,_DAT_7ffe9c962e78);
        if (iVar6 == 0) {
          return;
        }
        plVar9 = plVar14;
        if (mobList != (undefined *)0x0) {
          while( true ) {
            uVar5 = (uint)plVar9;
            if ((int)*(uint *)(mobList + 0x18) <= (int)uVar5) break;
            if (*(uint *)(mobList + 0x18) <= uVar5) {
LAB_7ffe9aa98b6a:
              FUN_7ffe9996d790();
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            uVar11 = *(undefined8 *)(mobList + (longlong)(int)uVar5 * 8 + 0x20);
            cVar3 = FUN_7ffe9ada6de0(plVar10,uVar11,_DAT_7ffe9c962da8);
            if (cVar3 != '\0') {
              lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
              if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x48) == 0)) goto LAB_7ffe9aa98b64;
              iVar6 = FUN_7ffe9a347020(*(longlong *)(lVar8 + 0x48),uVar11,0);
              iVar7 = FUN_7ffe9adb63e0(plVar10,uVar11,_DAT_7ffe9c962f40);
              if ((iVar7 == 0) && (iVar6 != 0)) {
                bVar2 = true;
              }
            }
            plVar9 = (longlong *)(ulonglong)(uVar5 + 1);
          }
          if (bVar2) {
            return;
          }
          lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
          if (lVar8 != 0) {
            iVar6 = FUN_7ffe9a872680(lVar8,0);
            plVar10 = (longlong *)0x2;
            if (iVar6 == 0x1d) {
              plVar10 = plVar14;
            }
            lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c951220);
            if (lVar8 != 0) {
              FUN_7ffe9a4ff9c0(lVar8,plVar10,1,0);
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9aa98b64:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

