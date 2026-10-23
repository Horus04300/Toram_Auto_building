
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
  
  if (DAT_7ffe9caddec9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c952570);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c9680d8);
    DAT_7ffe9caddec9 = '\x01';
  }
  uVar13 = 0;
  lStack_70 = 0;
  plStack_88 = (longlong *)0x0;
  plStack_78 = (longlong *)0x0;
  if (mobAction == (undefined *)0x0) goto LAB_7ffe9a4b29ed;
  lVar6 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
  if (playerAction == (undefined *)0x0) goto LAB_7ffe9a4b29ed;
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a4b29ed;
  lVar8 = (**(code **)(*plVar7 + 0x1a8))(plVar7,*(undefined8 *)(*plVar7 + 0x1b0));
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  iStack_a8 = 0;
  iStack_a0 = 0;
  iStack_a4 = 0;
  if (lVar8 == 0) goto LAB_7ffe9a4b29ed;
  iVar3 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar8);
  if (lVar6 == 0) goto LAB_7ffe9a4b29ed;
  iStack_90 = FUN_7ffe99742ec0(1,_DAT_7ffe9c93ed20,lVar6);
  iStack_80 = FUN_7ffe99742ec0(0x28,_DAT_7ffe9c940d40,lVar8);
  iStack_94 = FUN_7ffe99742ec0(0xe,_DAT_7ffe9c940d40,lVar8);
  iStack_98 = FUN_7ffe99742ec0(0x10,_DAT_7ffe9c940d40,lVar8);
  cVar2 = FUN_7ffe9a781d00(self,plVar7,0);
  if (cVar2 != '\0') {
    if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a4b29ed;
    lVar9 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0));
    if (lVar9 == 0) goto LAB_7ffe9a4b29ed;
    cVar2 = FUN_7ffe9abc2210(lVar9,0x369,&lStack_70,_DAT_7ffe9c9680d8);
    if (cVar2 != '\0') {
      if (lStack_70 == 0) goto LAB_7ffe9a4b29ed;
      FUN_7ffe9a781ad0(lStack_70,plVar7,&iStack_94,&iStack_98,0);
    }
  }
  fVar15 = _DAT_7ffe9c049cfc;
  iVar5 = (int)type;
  if ((iVar5 == 0) || (iVar5 == 1)) {
LAB_7ffe9a4b23ed:
    iStack_a4 = FUN_7ffe99742ec0(5,_DAT_7ffe9c93ed20,lVar6);
    iVar5 = iStack_94;
    iStack_a8 = iStack_94;
    if (isCritical != 0) {
      if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a4b29ed;
      lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
      if (lVar6 == 0) goto LAB_7ffe9a4b29ed;
      lVar6 = FUN_7ffe99c08fe0(lVar6,0);
      if (lVar6 == 0) {
        lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
        if (lVar6 == 0) goto LAB_7ffe9a4b29ed;
        lVar6 = FUN_7ffe99c090e0(lVar6,0);
        if (lVar6 == 0) goto LAB_7ffe9a4b247f;
LAB_7ffe9a4b255a:
        lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
        if (lVar6 == 0) goto LAB_7ffe9a4b29ed;
        lVar6 = FUN_7ffe99c090e0(lVar6,0);
        if (lVar6 == 0) goto LAB_7ffe9a4b29ed;
        if (*(int *)(lVar6 + 0x38) == 8) {
          lVar6 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
          if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x68) == 0)) goto LAB_7ffe9a4b29ed;
          cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x265,&plStack_88,_DAT_7ffe9c935bd0);
          if (cVar2 != '\0') {
            if (plStack_88 == (longlong *)0x0) goto LAB_7ffe9a4b29ed;
            iVar4 = (**(code **)(*plStack_88 + 0x178))
                              (plStack_88,3,*(undefined8 *)(*plStack_88 + 0x180));
            iStack_a8 = (int)(((float)iVar4 / fVar15 + _DAT_7ffe9c049b18) * (float)iVar5);
          }
        }
      }
      else {
LAB_7ffe9a4b247f:
        lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
        if (lVar6 == 0) goto LAB_7ffe9a4b29ed;
        lVar6 = FUN_7ffe99c090e0(lVar6,0);
        if (lVar6 != 0) {
          lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
          if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x20) == 0)) goto LAB_7ffe9a4b29ed;
          iVar4 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x20),0);
          if (iVar4 == 0x17) {
            lVar6 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
            if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x68) == 0)) goto LAB_7ffe9a4b29ed;
            cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x4c1,&plStack_88,_DAT_7ffe9c935bd0
                                    );
            if (cVar2 != '\0') {
              if ((plStack_88 == (longlong *)0x0) || (plStack_88[2] == 0)) goto LAB_7ffe9a4b29ed;
              if (*(char *)(plStack_88[2] + 0x18) == '\n') goto LAB_7ffe9a4b255a;
            }
          }
        }
      }
    }
    uVar11 = 0x27;
LAB_7ffe9a4b262b:
    iStack_a0 = FUN_7ffe99742ec0(uVar11,_DAT_7ffe9c940d40,lVar8);
  }
  else {
    if (iVar5 == 2) {
      iStack_a4 = FUN_7ffe99742ec0(6,_DAT_7ffe9c93ed20,lVar6);
      iStack_a8 = iStack_98;
      uVar11 = 0x29;
      goto LAB_7ffe9a4b262b;
    }
    if (iVar5 == 3) goto LAB_7ffe9a4b23ed;
  }
  iVar5 = (**(code **)(*(longlong *)self + 0x588))(self,*(undefined8 *)(*(longlong *)self + 0x590));
  if (iVar5 == 0x20) {
    if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a4b29ed;
    lVar6 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
    if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x68) == 0)) goto LAB_7ffe9a4b29ed;
    cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x409,&plStack_78,_DAT_7ffe9c935bd0);
    if (cVar2 != '\0') {
      if (plStack_78 == (longlong *)0x0) goto LAB_7ffe9a4b29ed;
      if (((*(byte *)(*plStack_78 + 0x130) < *(byte *)(_DAT_7ffe9c952570 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_78 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c952570 + 0x130) * 8) != _DAT_7ffe9c952570)) ||
         (plStack_78 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_78);
        pcVar1 = (code *)swi(3);
        iVar3 = (*pcVar1)();
        return iVar3;
      }
      *(undefined1 *)(plStack_78 + 4) = 0;
    }
    iVar5 = FUN_7ffe99742ec0(0xe,_DAT_7ffe9c940d40,lVar8);
    iVar4 = FUN_7ffe99742ec0(0x10,_DAT_7ffe9c940d40,lVar8);
    iStack_a8 = (int)((float)iVar4 * _DAT_7ffe9c049cc8) - (int)((float)iVar5 * _DAT_7ffe9c04b3f8);
    if (plStack_78 != (longlong *)0x0) {
      if (((*(byte *)(*plStack_78 + 0x130) < *(byte *)(_DAT_7ffe9c952570 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_78 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c952570 + 0x130) * 8) != _DAT_7ffe9c952570)) ||
         (plStack_78 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_78);
        pcVar1 = (code *)swi(3);
        iVar3 = (*pcVar1)();
        return iVar3;
      }
      *(undefined1 *)(plStack_78 + 4) = 1;
    }
  }
  if (DAT_7ffe9caddeca == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c928608);
    DAT_7ffe9caddeca = '\x01';
  }
  alStack_68[0] = 0;
  fStack_9c = 1.0;
  plVar10 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (plVar10 != (longlong *)0x0) {
    lVar6 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200));
    if (lVar6 != 0) {
      lVar8 = FUN_7ffe99c090e0(lVar6,0);
      lVar6 = _DAT_7ffe9c928608;
      uVar14 = uVar13;
      if (lVar8 != 0) {
        uVar14 = (ulonglong)*(uint *)(lVar8 + 0x38);
      }
      lVar8 = *(longlong *)mobAction;
      if (*(ushort *)(lVar8 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + uVar13 * 0x10) ==
              *(longlong *)(_DAT_7ffe9c928608 + 0x20)) {
            lVar8 = (longlong)
                    (int)(*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + uVar13 * 0x10) +
                         (uint)*(ushort *)(_DAT_7ffe9c928608 + 0x50)) * 0x10 + 0x138 + lVar8;
            goto LAB_7ffe9a4b2867;
          }
          uVar12 = (short)uVar13 + 1;
          uVar13 = (ulonglong)uVar12;
        } while (uVar12 < *(ushort *)(lVar8 + 0x12e));
      }
      lVar8 = FUN_7ffe998ce540(mobAction,*(longlong *)(_DAT_7ffe9c928608 + 0x20),
                               *(ushort *)(_DAT_7ffe9c928608 + 0x50));
LAB_7ffe9a4b2867:
      lVar6 = func_0x7ffe9996d210(*(undefined8 *)(lVar8 + 8),lVar6);
      cVar2 = (**(code **)(lVar6 + 8))(mobAction,4,alStack_68,lVar6);
      if (cVar2 != '\0') {
        if (alStack_68[0] == 0) goto LAB_7ffe9a4b2a05;
        FUN_7ffe9a37be60(alStack_68[0],uVar14,&fStack_9c,0);
      }
      if (((ulonglong)eqLimit & 0x8000) == 0) {
        fVar16 = (float)(100 - iStack_a4) / fVar15;
        fVar15 = (float)(iStack_a8 + (iVar3 - iStack_90));
LAB_7ffe9a4b29aa:
        return (int)(fVar15 * fVar16 * fStack_9c);
      }
      if (plVar7 != (longlong *)0x0) {
        lVar6 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
        if (lVar6 != 0) {
          iVar3 = iVar3 - iStack_90;
          fVar16 = (float)(100 - iStack_a4) / fVar15;
          iVar5 = FUN_7ffe99c08f50(lVar6,0);
          if (iVar5 == 10) {
            fVar15 = (float)(iStack_80 * iStack_a0) / fVar15 + (float)iStack_a8 + (float)iVar3;
          }
          else {
            fVar15 = (float)(iStack_a8 + iVar3);
          }
          goto LAB_7ffe9a4b29aa;
        }
      }
LAB_7ffe9a4b29ed:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      iVar3 = (*pcVar1)();
      return iVar3;
    }
  }
LAB_7ffe9a4b2a05:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar3 = (*pcVar1)();
  return iVar3;
}

