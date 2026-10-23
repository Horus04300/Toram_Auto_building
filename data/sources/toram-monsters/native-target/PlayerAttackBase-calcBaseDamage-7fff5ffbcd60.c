
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerAttackBase_calcBaseDamage
              (undefined *self,undefined *playerAction,undefined *mobAction,undefined *type,
              undefined *eqLimit,byte isCritical,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong lVar9;
  longlong *plVar10;
  undefined8 uVar11;
  ushort uVar12;
  ulonglong uVar14;
  float fVar15;
  float fVar16;
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  float fStack_9c;
  int iStack_98;
  int iStack_94;
  int iStack_90;
  longlong *plStack_88;
  int iStack_80;
  longlong *plStack_78;
  longlong lStack_70;
  longlong alStack_68 [6];
  ulonglong uVar13;
  
  if (DAT_7fff625e5621 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62459eb0);
    FUN_7fff5f47d450(&DAT_7fff6243cb28);
    FUN_7fff5f47d450(&DAT_7fff624465a0);
    FUN_7fff5f47d450(&DAT_7fff624485c8);
    FUN_7fff5f47d450(&DAT_7fff62479db0);
    FUN_7fff5f47d450(&DAT_7fff6246eef0);
    DAT_7fff625e5621 = '\x01';
  }
  uVar13 = 0;
  lStack_70 = 0;
  plStack_88 = (longlong *)0x0;
  plStack_78 = (longlong *)0x0;
  if (mobAction == (undefined *)0x0) goto LAB_7fff5ffbd5ad;
  lVar6 = FUN_7fff5f252ec0(9,_DAT_7fff62479db0,mobAction);
  if (playerAction == (undefined *)0x0) goto LAB_7fff5ffbd5ad;
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (plVar7 == (longlong *)0x0) goto LAB_7fff5ffbd5ad;
  lVar8 = (**(code **)(*plVar7 + 0x1a8))(plVar7,*(undefined8 *)(*plVar7 + 0x1b0));
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  iStack_a8 = 0;
  iStack_a0 = 0;
  iStack_a4 = 0;
  if (lVar8 == 0) goto LAB_7fff5ffbd5ad;
  iVar3 = FUN_7fff5f252ec0(0,_DAT_7fff624485c8,lVar8);
  if (lVar6 == 0) goto LAB_7fff5ffbd5ad;
  iStack_90 = FUN_7fff5f252ec0(1,_DAT_7fff624465a0,lVar6);
  iStack_80 = FUN_7fff5f252ec0(0x28,_DAT_7fff624485c8,lVar8);
  iStack_94 = FUN_7fff5f252ec0(0xe,_DAT_7fff624485c8,lVar8);
  iStack_98 = FUN_7fff5f252ec0(0x10,_DAT_7fff624485c8,lVar8);
  cVar2 = FUN_7fff6028c190(self,plVar7,0);
  if (cVar2 != '\0') {
    if (plVar7 == (longlong *)0x0) goto LAB_7fff5ffbd5ad;
    lVar9 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0));
    if (lVar9 == 0) goto LAB_7fff5ffbd5ad;
    cVar2 = FUN_7fff606cc5c0(lVar9,0x369,&lStack_70,_DAT_7fff6246eef0);
    if (cVar2 != '\0') {
      if (lStack_70 == 0) goto LAB_7fff5ffbd5ad;
      FUN_7fff6028bf60(lStack_70,plVar7,&iStack_94,&iStack_98,0);
    }
  }
  fVar15 = _DAT_7fff61b52cfc;
  iVar5 = (int)type;
  if ((iVar5 == 0) || (iVar5 == 1)) {
LAB_7fff5ffbcfad:
    iStack_a4 = FUN_7fff5f252ec0(5,_DAT_7fff624465a0,lVar6);
    iVar5 = iStack_94;
    iStack_a8 = iStack_94;
    if (isCritical != 0) {
      if (plVar7 == (longlong *)0x0) goto LAB_7fff5ffbd5ad;
      lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
      if (lVar6 == 0) goto LAB_7fff5ffbd5ad;
      lVar6 = FUN_7fff5f718ca0(lVar6,0);
      if (lVar6 == 0) {
        lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
        if (lVar6 == 0) goto LAB_7fff5ffbd5ad;
        lVar6 = FUN_7fff5f718da0(lVar6,0);
        if (lVar6 == 0) goto LAB_7fff5ffbd03f;
LAB_7fff5ffbd11a:
        lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
        if (lVar6 == 0) goto LAB_7fff5ffbd5ad;
        lVar6 = FUN_7fff5f718da0(lVar6,0);
        if (lVar6 == 0) goto LAB_7fff5ffbd5ad;
        if (*(int *)(lVar6 + 0x38) == 8) {
          lVar6 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
          if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x68) == 0)) goto LAB_7fff5ffbd5ad;
          cVar2 = FUN_7fff60898a30(*(longlong *)(lVar6 + 0x68),0x265,&plStack_88,_DAT_7fff6243cb28);
          if (cVar2 != '\0') {
            if (plStack_88 == (longlong *)0x0) goto LAB_7fff5ffbd5ad;
            iVar4 = (**(code **)(*plStack_88 + 0x178))
                              (plStack_88,3,*(undefined8 *)(*plStack_88 + 0x180));
            iStack_a8 = (int)(((float)iVar4 / fVar15 + _DAT_7fff61b52b18) * (float)iVar5);
          }
        }
      }
      else {
LAB_7fff5ffbd03f:
        lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
        if (lVar6 == 0) goto LAB_7fff5ffbd5ad;
        lVar6 = FUN_7fff5f718da0(lVar6,0);
        if (lVar6 != 0) {
          lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
          if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x20) == 0)) goto LAB_7fff5ffbd5ad;
          iVar4 = func_0x7fff5f72ea30(*(longlong *)(lVar6 + 0x20),0);
          if (iVar4 == 0x17) {
            lVar6 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
            if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x68) == 0)) goto LAB_7fff5ffbd5ad;
            cVar2 = FUN_7fff60898a30(*(longlong *)(lVar6 + 0x68),0x4c1,&plStack_88,_DAT_7fff6243cb28
                                    );
            if (cVar2 != '\0') {
              if ((plStack_88 == (longlong *)0x0) || (plStack_88[2] == 0)) goto LAB_7fff5ffbd5ad;
              if (*(char *)(plStack_88[2] + 0x18) == '\n') goto LAB_7fff5ffbd11a;
            }
          }
        }
      }
    }
    uVar11 = 0x27;
LAB_7fff5ffbd1eb:
    iStack_a0 = FUN_7fff5f252ec0(uVar11,_DAT_7fff624485c8,lVar8);
  }
  else {
    if (iVar5 == 2) {
      iStack_a4 = FUN_7fff5f252ec0(6,_DAT_7fff624465a0,lVar6);
      iStack_a8 = iStack_98;
      uVar11 = 0x29;
      goto LAB_7fff5ffbd1eb;
    }
    if (iVar5 == 3) goto LAB_7fff5ffbcfad;
  }
  iVar5 = (**(code **)(*(longlong *)self + 0x588))(self,*(undefined8 *)(*(longlong *)self + 0x590));
  if (iVar5 == 0x20) {
    if (plVar7 == (longlong *)0x0) goto LAB_7fff5ffbd5ad;
    lVar6 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
    if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x68) == 0)) goto LAB_7fff5ffbd5ad;
    cVar2 = FUN_7fff60898a30(*(longlong *)(lVar6 + 0x68),0x409,&plStack_78,_DAT_7fff6243cb28);
    if (cVar2 != '\0') {
      if (plStack_78 == (longlong *)0x0) goto LAB_7fff5ffbd5ad;
      if (((*(byte *)(*plStack_78 + 0x130) < *(byte *)(_DAT_7fff62459eb0 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_78 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7fff62459eb0 + 0x130) * 8) != _DAT_7fff62459eb0)) ||
         (plStack_78 == (longlong *)0x0)) {
        FUN_7fff5f47c810(plStack_78);
        pcVar1 = (code *)swi(3);
        iVar3 = (*pcVar1)();
        return iVar3;
      }
      *(undefined1 *)(plStack_78 + 4) = 0;
    }
    iVar5 = FUN_7fff5f252ec0(0xe,_DAT_7fff624485c8,lVar8);
    iVar4 = FUN_7fff5f252ec0(0x10,_DAT_7fff624485c8,lVar8);
    iStack_a8 = (int)((float)iVar4 * _DAT_7fff61b52cc8) - (int)((float)iVar5 * _DAT_7fff61b54408);
    if (plStack_78 != (longlong *)0x0) {
      if (((*(byte *)(*plStack_78 + 0x130) < *(byte *)(_DAT_7fff62459eb0 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_78 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7fff62459eb0 + 0x130) * 8) != _DAT_7fff62459eb0)) ||
         (plStack_78 == (longlong *)0x0)) {
        FUN_7fff5f47c810(plStack_78);
        pcVar1 = (code *)swi(3);
        iVar3 = (*pcVar1)();
        return iVar3;
      }
      *(undefined1 *)(plStack_78 + 4) = 1;
    }
  }
  if (DAT_7fff625e5622 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242f4c0);
    DAT_7fff625e5622 = '\x01';
  }
  alStack_68[0] = 0;
  fStack_9c = 1.0;
  plVar10 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (plVar10 != (longlong *)0x0) {
    lVar6 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200));
    if (lVar6 != 0) {
      lVar8 = FUN_7fff5f718da0(lVar6,0);
      lVar6 = _DAT_7fff6242f4c0;
      uVar14 = uVar13;
      if (lVar8 != 0) {
        uVar14 = (ulonglong)*(uint *)(lVar8 + 0x38);
      }
      lVar8 = *(longlong *)mobAction;
      if (*(ushort *)(lVar8 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + uVar13 * 0x10) ==
              *(longlong *)(_DAT_7fff6242f4c0 + 0x20)) {
            lVar8 = (longlong)
                    (int)(*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + uVar13 * 0x10) +
                         (uint)*(ushort *)(_DAT_7fff6242f4c0 + 0x50)) * 0x10 + 0x138 + lVar8;
            goto LAB_7fff5ffbd427;
          }
          uVar12 = (short)uVar13 + 1;
          uVar13 = (ulonglong)uVar12;
        } while (uVar12 < *(ushort *)(lVar8 + 0x12e));
      }
      lVar8 = FUN_7fff5f3de400(mobAction,*(longlong *)(_DAT_7fff6242f4c0 + 0x20),
                               *(ushort *)(_DAT_7fff6242f4c0 + 0x50));
LAB_7fff5ffbd427:
      lVar6 = func_0x7fff5f47d0d0(*(undefined8 *)(lVar8 + 8),lVar6);
      cVar2 = (**(code **)(lVar6 + 8))(mobAction,4,alStack_68,lVar6);
      if (cVar2 != '\0') {
        if (alStack_68[0] == 0) goto LAB_7fff5ffbd5c5;
        FUN_7fff5fe86a10(alStack_68[0],uVar14,&fStack_9c,0);
      }
      if (((ulonglong)eqLimit & 0x8000) == 0) {
        fVar16 = (float)(100 - iStack_a4) / fVar15;
        fVar15 = (float)(iStack_a8 + (iVar3 - iStack_90));
LAB_7fff5ffbd56a:
        return (int)(fVar15 * fVar16 * fStack_9c);
      }
      if (plVar7 != (longlong *)0x0) {
        lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
        if (lVar6 != 0) {
          iVar3 = iVar3 - iStack_90;
          fVar16 = (float)(100 - iStack_a4) / fVar15;
          iVar5 = FUN_7fff5f718c10(lVar6,0);
          if (iVar5 == 10) {
            fVar15 = (float)(iStack_80 * iStack_a0) / fVar15 + (float)iStack_a8 + (float)iVar3;
          }
          else {
            fVar15 = (float)(iStack_a8 + iVar3);
          }
          goto LAB_7fff5ffbd56a;
        }
      }
LAB_7fff5ffbd5ad:
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      iVar3 = (*pcVar1)();
      return iVar3;
    }
  }
LAB_7fff5ffbd5c5:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar3 = (*pcVar1)();
  return iVar3;
}

