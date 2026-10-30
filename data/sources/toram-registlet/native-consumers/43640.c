
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnActionPartyChangeHateMine
               (undefined *thisObject,undefined *game,undefined *archetype,undefined *mobList,
               undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  longlong *plVar10;
  undefined *thisObject_00;
  longlong *plVar11;
  longlong *plVar12;
  longlong *plVar13;
  longlong *plVar14;
  
  if (DAT_7ffe9cae097a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c962ce0);
    FUN_7ffe9996d590(&DAT_7ffe9c962da8);
    FUN_7ffe9996d590(&DAT_7ffe9c962c10);
    FUN_7ffe9996d590(&DAT_7ffe9c962e78);
    FUN_7ffe9996d590(&DAT_7ffe9c962f40);
    FUN_7ffe9996d590(&DAT_7ffe9c90c8f8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    FUN_7ffe9996d590(&DAT_7ffe9c951220);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(&DAT_7ffe9c8fd270);
    DAT_7ffe9cae097a = '\x01';
  }
  func_0x7ffe999c3920(_DAT_7ffe9c8fd270,0);
  lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
  if (lVar9 != 0) {
    cVar4 = FUN_7ffe9a5a4650(lVar9,0);
    if (cVar4 == '\0') {
      return;
    }
    lVar9 = FUN_7ffe9a47bac0(0);
    plVar14 = (longlong *)0x0;
    bVar5 = 0;
    if ((archetype != (undefined *)0x0) && (lVar9 != 0)) {
      cVar4 = func_0x7ffe9abd5d00(*(undefined8 *)(archetype + 0x20),*(undefined8 *)(lVar9 + 0x50));
      plVar11 = plVar14;
      plVar10 = plVar14;
      if (cVar4 != '\0') {
        plVar10 = (longlong *)FUN_7ffe9a47fe30(lVar9,0);
        thisObject_00 = (undefined *)FUN_7ffe9a47f780(lVar9,0);
        if ((((thisObject_00 == (undefined *)0x0) ||
             (bVar5 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3d,(undefined *)0x0),
             plVar10 == (longlong *)0x0)) ||
            (plVar11 = (longlong *)
                       (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
            plVar11 == (longlong *)0x0)) ||
           (lVar9 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
           lVar9 == 0)) goto LAB_7ffe9aa97d9e;
        cVar4 = FUN_7ffe9a7c6d00(lVar9,0x46b,0);
        plVar11 = (longlong *)0x0;
        if (cVar4 != '\0' || bVar5 != 0) {
          plVar11 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c90c8f8);
          FUN_7ffe9ada4840(plVar11,_DAT_7ffe9c962c10);
          plVar12 = plVar14;
          if (mobList == (undefined *)0x0) goto LAB_7ffe9aa97d9e;
          while( true ) {
            uVar6 = (uint)plVar12;
            if ((int)*(uint *)(mobList + 0x18) <= (int)uVar6) break;
            if (*(uint *)(mobList + 0x18) <= uVar6) goto LAB_7ffe9aa97da4;
            uVar1 = *(undefined8 *)(mobList + (longlong)(int)uVar6 * 8 + 0x20);
            lVar9 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
            if (((lVar9 == 0) || (*(longlong *)(lVar9 + 0x48) == 0)) ||
               (FUN_7ffe9a347020(*(longlong *)(lVar9 + 0x48),uVar1,0), plVar11 == (longlong *)0x0))
            goto LAB_7ffe9aa97d9e;
            FUN_7ffe9ada6cf0(plVar11,uVar1);
            plVar12 = (longlong *)(ulonglong)(uVar6 + 1);
          }
        }
      }
      lVar9 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
      if (lVar9 != 0) {
        FUN_7ffe9a336e80(lVar9,mobList,0);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar4 = FUN_7ffe9bda2160(plVar10,0,0);
        if (cVar4 == '\0') {
          return;
        }
        if (((plVar10 != (longlong *)0x0) &&
            (plVar12 = (longlong *)
                       (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
            plVar12 != (longlong *)0x0)) &&
           (lVar9 = (**(code **)(*plVar12 + 0x1c8))(plVar12,*(undefined8 *)(*plVar12 + 0x1d0)),
           lVar9 != 0)) {
          cVar4 = FUN_7ffe9a7c6d00(lVar9,0x229,0);
          if (cVar4 != '\0') {
            plVar12 = (longlong *)
                      (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
            if ((plVar12 == (longlong *)0x0) ||
               (lVar9 = (**(code **)(*plVar12 + 0x1c8))(plVar12,*(undefined8 *)(*plVar12 + 0x1d0)),
               lVar9 == 0)) goto LAB_7ffe9aa97d9e;
            FUN_7ffe9a7cafa0(lVar9,0x229,0);
            plVar12 = (longlong *)plVar10[6];
            plVar13 = plVar14;
            if (plVar12 != (longlong *)0x0) {
              if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*plVar12 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) != _DAT_7ffe9c922a40)) {
                bVar3 = false;
              }
              else {
                bVar3 = true;
              }
              if (bVar3) {
                plVar13 = plVar12;
              }
            }
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar4 = FUN_7ffe9bda2160(plVar13,0,0);
            if (cVar4 != '\0') {
              if (plVar13 == (longlong *)0x0) goto LAB_7ffe9aa97d9e;
              FUN_7ffe9a46d2b0(plVar13,0);
            }
          }
          FUN_7ffe9a808f60(plVar10,0);
          if ((plVar11 != (longlong *)0x0) &&
             (iVar7 = func_0x7ffe9acd8120(plVar11,_DAT_7ffe9c962e78), 0 < iVar7)) {
            FUN_7ffe9a841a80(plVar10,0);
          }
          FUN_7ffe9a83a910(plVar10,0);
          if (((bVar5 == 0) || (bVar3 = false, plVar11 == (longlong *)0x0)) ||
             (iVar7 = func_0x7ffe9acd8120(plVar11,_DAT_7ffe9c962e78), iVar7 == 0)) {
            return;
          }
          plVar10 = plVar14;
          if (mobList != (undefined *)0x0) {
            while( true ) {
              uVar6 = (uint)plVar10;
              if ((int)*(uint *)(mobList + 0x18) <= (int)uVar6) break;
              if (*(uint *)(mobList + 0x18) <= uVar6) {
LAB_7ffe9aa97da4:
                FUN_7ffe9996d790();
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              uVar1 = *(undefined8 *)(mobList + (longlong)(int)uVar6 * 8 + 0x20);
              cVar4 = FUN_7ffe9ada6de0(plVar11,uVar1,_DAT_7ffe9c962da8);
              if (cVar4 != '\0') {
                lVar9 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x48) == 0)) goto LAB_7ffe9aa97d9e;
                iVar7 = FUN_7ffe9a347020(*(longlong *)(lVar9 + 0x48),uVar1,0);
                iVar8 = FUN_7ffe9adb63e0(plVar11,uVar1,_DAT_7ffe9c962f40);
                if ((iVar8 == 0) && (iVar7 != 0)) {
                  bVar3 = true;
                }
              }
              plVar10 = (longlong *)(ulonglong)(uVar6 + 1);
            }
            if (bVar3) {
              return;
            }
            lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
            if (lVar9 != 0) {
              iVar7 = FUN_7ffe9a872680(lVar9,0);
              plVar11 = (longlong *)0x2;
              if (iVar7 == 0x1d) {
                plVar11 = plVar14;
              }
              lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951220);
              if (lVar9 != 0) {
                FUN_7ffe9a4ff9c0(lVar9,plVar11,1,0);
                return;
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9aa97d9e:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

