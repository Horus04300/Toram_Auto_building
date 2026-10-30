
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BerserkAction_ActionHit
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  undefined1 uVar1;
  uint uVar2;
  longlong lVar3;
  longlong lVar4;
  undefined8 uVar5;
  code *pcVar6;
  bool bVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  longlong lVar13;
  longlong *plVar14;
  undefined *puVar15;
  longlong *plVar16;
  longlong lVar17;
  longlong *plVar18;
  undefined1 uVar19;
  longlong *plVar20;
  longlong alStack_58 [6];
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined8 uStack_20;
  
  if (DAT_7ffe9cadf72b == '\0') {
    alStack_58[1] = 0x7ffe9a807003;
    FUN_7ffe9996d590(&DAT_7ffe9c942338);
    alStack_58[1] = 0x7ffe9a80700f;
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf72b = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
LAB_7ffe9a807187:
    alStack_58[1] = 0x7ffe9a80718c;
    FUN_7ffe9996d7a0();
    pcVar6 = (code *)swi(3);
    (*pcVar6)();
    return;
  }
  if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
     (*(longlong *)
       (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
       (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720))
  goto LAB_7ffe9a807187;
  alStack_58[1] = 0x7ffe9a807069;
  plVar14 = (longlong *)
            (**(code **)(*(longlong *)actarAction + 0x298))
                      (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a807187;
  alStack_58[1] = 0x7ffe9a807089;
  puVar15 = (undefined *)(**(code **)(*plVar14 + 0x218))(plVar14,*(undefined8 *)(*plVar14 + 0x220));
  if (puVar15 == (undefined *)0x0) goto LAB_7ffe9a807187;
  alStack_58[1] = 0x7ffe9a8070b6;
  puVar15 = GemCartBufferManager_GetGemCartBuffer(puVar15,0x198,(undefined *)0x0);
  uVar19 = 0;
  if (puVar15 != (undefined *)0x0) {
    alStack_58[1] = 0x7ffe9a8070cd;
    iVar10 = GemCartBufferBase_GetValue(puVar15,(undefined *)0x2,(undefined *)0x0);
    uVar19 = (undefined1)iVar10;
  }
  uVar1 = thisObject[0x14];
  alStack_58[1] = 0x7ffe9a8070de;
  uVar11 = FUN_7ffe9a4ae0a0(actarAction,0);
  alStack_58[1] = 0x7ffe9a8070ea;
  uVar12 = FUN_7ffe9a4ade20(actarAction,0);
  alStack_58[1] = 0x7ffe9a8070f8;
  plVar14 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c942338);
  uStack_20 = 0;
  _uStack_28 = CONCAT44(uStack_24,uVar12);
  alStack_58[1] = 0x7ffe9a80711b;
  FUN_7ffe9a77b7f0(plVar14,uVar1,uVar19,uVar11);
  alStack_58[1] = 0x7ffe9a807132;
  plVar16 = (longlong *)
            (**(code **)(*(longlong *)actarAction + 0x298))
                      (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  if (plVar16 == (longlong *)0x0) goto LAB_7ffe9a807187;
  alStack_58[1] = 0x7ffe9a807162;
  lVar17 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0));
  if (lVar17 == 0) goto LAB_7ffe9a807187;
  uVar19 = thisObject[0x10];
  if (DAT_7ffe9cadf569 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9585d0,plVar14,uVar19,0);
    FUN_7ffe9996d590(&DAT_7ffe9c934040);
    FUN_7ffe9996d590(&DAT_7ffe9c9341c8);
    FUN_7ffe9996d590(&DAT_7ffe9c9345a0);
    FUN_7ffe9996d590(&DAT_7ffe9c9347e8);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c90e4a8);
    FUN_7ffe9996d590(&DAT_7ffe9c90e718);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c968f30);
    DAT_7ffe9cadf569 = '\x01';
  }
  if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a7c2b20;
  uVar11 = (**(code **)(*plVar14 + 0x178))(plVar14,*(undefined8 *)(*plVar14 + 0x180));
  plVar20 = (longlong *)0x0;
  iVar10 = 0;
  alStack_58[0] = 0;
  plVar16 = *(longlong **)(lVar17 + 0x20);
  if (((plVar16 != (longlong *)0x0) &&
      (lVar13 = (**(code **)(*plVar16 + 0x1a8))(plVar16,*(undefined8 *)(*plVar16 + 0x1b0)),
      lVar13 != 0)) &&
     (cVar8 = FUN_7ffe9abc2210(lVar17,0x6d,alStack_58,_DAT_7ffe9c968f30), cVar8 != '\0')) {
    plVar16 = *(longlong **)(lVar17 + 0x20);
    if ((plVar16 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar16 + 0x1a8))(plVar16,*(undefined8 *)(*plVar16 + 0x1b0)),
       lVar13 == 0)) goto LAB_7ffe9a7c2b20;
    iVar10 = FUN_7ffe99742ec0(0x17,_DAT_7ffe9c940d40,lVar13);
  }
  lVar13 = *(longlong *)(lVar17 + 0x40);
  uVar12 = (**(code **)(*plVar14 + 0x178))(plVar14,*(undefined8 *)(*plVar14 + 0x180));
  if (lVar13 == 0) goto LAB_7ffe9a7c2b20;
  cVar8 = FUN_7ffe9ad5f0a0(lVar13,uVar12,_DAT_7ffe9c9341c8);
  if (cVar8 == '\0') {
    if (*(longlong *)(lVar17 + 0x40) == 0) goto LAB_7ffe9a7c2b20;
    FUN_7ffe9ad82760(*(longlong *)(lVar17 + 0x40),uVar11,plVar14,_DAT_7ffe9c934040);
  }
  else {
    cVar8 = (**(code **)(*plVar14 + 0x198))(plVar14,*(undefined8 *)(*plVar14 + 0x1a0));
    if (cVar8 != '\0') {
      lVar13 = *(longlong *)(lVar17 + 0x48);
      if ((*(longlong *)(lVar17 + 0x40) == 0) ||
         (plVar16 = (longlong *)
                    FUN_7ffe9ad723c0(*(longlong *)(lVar17 + 0x40),uVar11,_DAT_7ffe9c9345a0),
         lVar13 == 0)) goto LAB_7ffe9a7c2b20;
      plVar18 = plVar20;
      if (plVar16 != (longlong *)0x0) {
        if ((*(byte *)(*plVar16 + 0x130) < *(byte *)(_DAT_7ffe9c9585d0 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar16 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c9585d0 + 0x130) * 8) != _DAT_7ffe9c9585d0)) {
          bVar7 = false;
        }
        else {
          bVar7 = true;
        }
        if (bVar7) {
          plVar18 = plVar16;
        }
      }
      FUN_7ffe9afdbfb0(lVar13,plVar18,_DAT_7ffe9c90e718);
    }
    if (*(longlong *)(lVar17 + 0x40) == 0) goto LAB_7ffe9a7c2b20;
    FUN_7ffe9ad94d20(*(longlong *)(lVar17 + 0x40),uVar11,plVar14,_DAT_7ffe9c9347e8);
    if (0.0 < *(float *)((longlong)plVar14 + 0x14)) {
      *(undefined1 *)(lVar17 + 0x78) = 1;
    }
  }
  cVar8 = (**(code **)(*plVar14 + 0x198))(plVar14,*(undefined8 *)(*plVar14 + 0x1a0));
  lVar13 = _DAT_7ffe9c90e4a8;
  if (cVar8 == '\0') {
LAB_7ffe9a7c2a89:
    FUN_7ffe9a7d0f10(lVar17,plVar14,0);
    if (alStack_58[0] == 0) {
      return;
    }
    plVar14 = *(longlong **)(lVar17 + 0x20);
    if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a7c2b37;
    lVar13 = (**(code **)(*plVar14 + 0x1a8))(plVar14,*(undefined8 *)(*plVar14 + 0x1b0));
    if (lVar13 == 0) goto LAB_7ffe9a7c2b2c;
    iVar9 = FUN_7ffe99742ec0(0x17,_DAT_7ffe9c940d40,lVar13);
    if (iVar10 == iVar9) {
      return;
    }
    if (alStack_58[0] != 0) {
      FUN_7ffe9a797240(alStack_58[0],*(undefined8 *)(lVar17 + 0x20),0);
      return;
    }
  }
  else {
    if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c9585d0 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar14 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9585d0 + 0x130) * 8)
        != _DAT_7ffe9c9585d0)) {
      bVar7 = false;
    }
    else {
      bVar7 = true;
    }
    if (bVar7) {
      plVar20 = plVar14;
    }
    lVar3 = *(longlong *)(lVar17 + 0x48);
    if (lVar3 == 0) goto LAB_7ffe9a7c2b20;
    *(int *)(lVar3 + 0x1c) = *(int *)(lVar3 + 0x1c) + 1;
    lVar4 = *(longlong *)(lVar3 + 0x10);
    uVar2 = *(uint *)(lVar3 + 0x18);
    if (lVar4 == 0) goto LAB_7ffe9a7c2b20;
    if (*(uint *)(lVar4 + 0x18) <= uVar2) {
      FUN_7ffe9afd58b0(lVar3,plVar20,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar13 + 0x20) + 0xc0) + 0x70));
LAB_7ffe9a7c29f5:
      if (plVar20 == (longlong *)0x0) {
LAB_7ffe9a7c2b20:
        FUN_7ffe9996d7a0();
        pcVar6 = (code *)swi(3);
        (*pcVar6)();
        return;
      }
      func_0x7ffe9a77ea00(plVar20,uVar19,0);
      cVar8 = (**(code **)(*plVar20 + 0x288))(plVar20,*(undefined8 *)(*plVar20 + 0x290));
      if (cVar8 == '\0') {
        uVar5 = *(undefined8 *)(lVar17 + 0x30);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar8 = FUN_7ffe9bda2160(uVar5,0,0);
        if (cVar8 != '\0') {
          lVar3 = plVar20[5];
          lVar13 = *(longlong *)(lVar17 + 0x30);
          uVar11 = (**(code **)(*plVar14 + 0x178))(plVar14,*(undefined8 *)(*plVar14 + 0x180));
          if (lVar13 == 0) goto LAB_7ffe9a7c2b20;
          FUN_7ffe9a6fdb50(lVar13,uVar11,(int)lVar3,0);
        }
      }
      goto LAB_7ffe9a7c2a89;
    }
    *(uint *)(lVar3 + 0x18) = uVar2 + 1;
    if (uVar2 < *(uint *)(lVar4 + 0x18)) {
      *(longlong **)(lVar4 + 0x20 + (longlong)(int)uVar2 * 8) = plVar20;
      il2cpp_write_barrier_0();
      goto LAB_7ffe9a7c29f5;
    }
    FUN_7ffe9996d790();
LAB_7ffe9a7c2b2c:
    FUN_7ffe9996d7a0();
  }
  FUN_7ffe9996d7a0();
LAB_7ffe9a7c2b37:
  FUN_7ffe9996d7a0();
  pcVar6 = (code *)swi(3);
  (*pcVar6)();
  return;
}

