
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobaPlayerSecondaryStatus_GetCrtConstant
              (undefined *thisObject,byte isNormalAttack,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  undefined *thisObject_00;
  undefined8 uVar8;
  longlong *plStackX_8;
  longlong *plStackX_20;
  
  if (DAT_7ffe9caddd4d == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9caddd4d = '\x01';
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  plStackX_8 = (longlong *)0x0;
  if ((plVar1 == (longlong *)0x0) ||
     (lVar7 = (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0)), lVar7 == 0))
  goto LAB_7ffe9a47398c;
  iVar5 = func_0x7ffe9a4eb350(lVar7,0x28,0);
  plVar1 = *(longlong **)(thisObject + 0x10);
  plStackX_20 = (longlong *)0x0;
  if ((plVar1 == (longlong *)0x0) ||
     ((lVar7 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)), lVar7 == 0
      || (*(longlong *)(lVar7 + 0x68) == 0)))) goto LAB_7ffe9a47398c;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0x1e7,&plStackX_20,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a47398c;
    iVar6 = (**(code **)(*plStackX_20 + 0x178))
                      (plStackX_20,0x16,*(undefined8 *)(*plStackX_20 + 0x180));
    iVar5 = iVar5 + iVar6;
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if ((plVar1 == (longlong *)0x0) ||
     (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar7 == 0))
  goto LAB_7ffe9a47398c;
  lVar7 = FUN_7ffe99c090e0(lVar7,0);
  if (lVar7 != 0) {
    plVar1 = *(longlong **)(thisObject + 0x10);
    if (((plVar1 == (longlong *)0x0) ||
        (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar7 == 0
        )) || (lVar7 = FUN_7ffe99c090e0(lVar7,0), lVar7 == 0)) goto LAB_7ffe9a47398c;
    if (*(int *)(lVar7 + 0x38) == 9) {
      plVar1 = *(longlong **)(thisObject + 0x10);
      if (((plVar1 == (longlong *)0x0) ||
          (lVar7 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
          lVar7 == 0)) || (*(longlong *)(lVar7 + 0x68) == 0)) goto LAB_7ffe9a47398c;
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0x3cb,&plStackX_20,_DAT_7ffe9c935bd0);
      if (cVar3 != '\0') {
        if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a47398c;
        iVar6 = (**(code **)(*plStackX_20 + 0x178))
                          (plStackX_20,0x16,*(undefined8 *)(*plStackX_20 + 0x180));
        iVar5 = iVar5 + iVar6;
      }
    }
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if ((plVar1 == (longlong *)0x0) ||
     (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar7 == 0))
  goto LAB_7ffe9a47398c;
  lVar7 = FUN_7ffe99c08fe0(lVar7,0);
  if (lVar7 == 0) {
    plVar1 = *(longlong **)(thisObject + 0x10);
    if ((plVar1 == (longlong *)0x0) ||
       (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar7 == 0)
       ) goto LAB_7ffe9a47398c;
    lVar7 = FUN_7ffe99c090e0(lVar7,0);
    if (lVar7 == 0) goto LAB_7ffe9a472f04;
LAB_7ffe9a472ffd:
    plVar1 = *(longlong **)(thisObject + 0x10);
    if (((plVar1 == (longlong *)0x0) ||
        (lVar7 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)), lVar7 == 0
        )) || (*(longlong *)(lVar7 + 0x68) == 0)) goto LAB_7ffe9a47398c;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0x265,&plStackX_20,_DAT_7ffe9c935bd0);
    if (cVar3 != '\0') {
      if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a47398c;
      iVar6 = (**(code **)(*plStackX_20 + 0x178))
                        (plStackX_20,0x16,*(undefined8 *)(*plStackX_20 + 0x180));
      plVar1 = *(longlong **)(thisObject + 0x10);
      if (((plVar1 == (longlong *)0x0) ||
          (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
          lVar7 == 0)) || (lVar7 = FUN_7ffe99c090e0(lVar7,0), lVar7 == 0)) goto LAB_7ffe9a47398c;
      if (*(int *)(lVar7 + 0x38) != 8) {
        iVar6 = iVar6 / 2;
      }
      iVar5 = iVar5 + iVar6;
    }
  }
  else {
LAB_7ffe9a472f04:
    plVar1 = *(longlong **)(thisObject + 0x10);
    if ((plVar1 == (longlong *)0x0) ||
       (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar7 == 0)
       ) goto LAB_7ffe9a47398c;
    lVar7 = FUN_7ffe99c090e0(lVar7,0);
    if (lVar7 != 0) {
      plVar1 = *(longlong **)(thisObject + 0x10);
      if (((plVar1 == (longlong *)0x0) ||
          (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
          lVar7 == 0)) || (*(longlong *)(lVar7 + 0x20) == 0)) goto LAB_7ffe9a47398c;
      iVar6 = func_0x7ffe99c1ed70(*(longlong *)(lVar7 + 0x20),0);
      if (iVar6 == 0x17) {
        plVar1 = *(longlong **)(thisObject + 0x10);
        if (((plVar1 == (longlong *)0x0) ||
            (lVar7 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
            lVar7 == 0)) || (*(longlong *)(lVar7 + 0x68) == 0)) goto LAB_7ffe9a47398c;
        cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0x4c1,&plStackX_20,_DAT_7ffe9c935bd0);
        if (cVar3 != '\0') {
          if ((plStackX_20 == (longlong *)0x0) || (plStackX_20[2] == 0)) goto LAB_7ffe9a47398c;
          if (*(char *)(plStackX_20[2] + 0x18) == '\n') goto LAB_7ffe9a472ffd;
        }
      }
    }
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (((plVar1 == (longlong *)0x0) ||
      (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 == 0))
     || (*(longlong *)(lVar7 + 0x50) == 0)) goto LAB_7ffe9a47398c;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x22,&plStackX_8,_DAT_7ffe9c934418);
  if (cVar3 != '\0') {
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
    iVar6 = (**(code **)(*plStackX_8 + 0x1f8))(plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200))
    ;
    plVar1 = *(longlong **)(thisObject + 0x10);
    if ((plVar1 == (longlong *)0x0) ||
       (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar7 == 0)
       ) goto LAB_7ffe9a47398c;
    lVar7 = FUN_7ffe99c090e0(lVar7,0);
    if (lVar7 != 0) {
      plVar1 = *(longlong **)(thisObject + 0x10);
      if (((plVar1 == (longlong *)0x0) ||
          (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
          lVar7 == 0)) || (lVar7 = FUN_7ffe99c090e0(lVar7,0), lVar7 == 0)) goto LAB_7ffe9a47398c;
      if (*(int *)(lVar7 + 0x38) == 0xb) {
        iVar6 = iVar6 * 2;
      }
    }
    iVar5 = iVar5 + iVar6;
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (isNormalAttack == 0) {
    if (((plVar1 == (longlong *)0x0) ||
        (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 == 0
        )) || (lVar7 = *(longlong *)(lVar7 + 0x50), lVar7 == 0)) goto LAB_7ffe9a47398c;
    uVar8 = 0x3c7;
  }
  else {
    if (((plVar1 == (longlong *)0x0) ||
        (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 == 0
        )) || (lVar7 = *(longlong *)(lVar7 + 0x50), lVar7 == 0)) goto LAB_7ffe9a47398c;
    uVar8 = 0x12a;
  }
  cVar3 = FUN_7ffe9ad8e670(lVar7,uVar8,&plStackX_8,_DAT_7ffe9c934418);
  if (cVar3 != '\0') {
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
    iVar6 = (**(code **)(*plStackX_8 + 0x1f8))(plStackX_8,0x13);
    iVar5 = iVar5 + iVar6;
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  if ((plVar1 != (longlong *)0x0) &&
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
     thisObject_00 != (undefined *)0x0)) {
    bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0xd8,(undefined *)0x0);
    if ((bVar4 == 0) || (isNormalAttack != 0)) {
      plVar1 = *(longlong **)(thisObject + 0x10);
      if (((plVar1 == (longlong *)0x0) ||
          (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
          lVar7 == 0)) || (*(longlong *)(lVar7 + 0x50) == 0)) goto LAB_7ffe9a47398c;
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x268,&plStackX_8,_DAT_7ffe9c934418);
      if (cVar3 != '\0') {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
        iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                          (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
        iVar5 = iVar5 + iVar6;
      }
    }
    plVar1 = *(longlong **)(thisObject + 0x10);
    if (((plVar1 != (longlong *)0x0) &&
        (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 != 0
        )) && (*(longlong *)(lVar7 + 0x50) != 0)) {
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x2e,&plStackX_8,_DAT_7ffe9c934418);
      if (cVar3 != '\0') {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
        iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                          (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
        iVar5 = iVar5 + iVar6;
      }
      plVar1 = *(longlong **)(thisObject + 0x10);
      if (((plVar1 != (longlong *)0x0) &&
          (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
          lVar7 != 0)) && (*(longlong *)(lVar7 + 0x50) != 0)) {
        cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x443,&plStackX_8,_DAT_7ffe9c934418);
        if (cVar3 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
          iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                            (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
          iVar5 = iVar5 + iVar6;
        }
        plVar1 = *(longlong **)(thisObject + 0x10);
        if (((plVar1 != (longlong *)0x0) &&
            (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
            lVar7 != 0)) && (*(longlong *)(lVar7 + 0x50) != 0)) {
          cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x4f,&plStackX_8,_DAT_7ffe9c934418);
          if (cVar3 != '\0') {
            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
            iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                              (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
            iVar5 = iVar5 + iVar6;
          }
          plVar1 = *(longlong **)(thisObject + 0x10);
          if (((plVar1 != (longlong *)0x0) &&
              (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
              lVar7 != 0)) && (*(longlong *)(lVar7 + 0x50) != 0)) {
            cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x365,&plStackX_8,_DAT_7ffe9c934418
                                    );
            if (cVar3 != '\0') {
              if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
              iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
              iVar5 = iVar5 + iVar6;
            }
            plVar1 = *(longlong **)(thisObject + 0x10);
            if (((plVar1 != (longlong *)0x0) &&
                (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
                lVar7 != 0)) && (*(longlong *)(lVar7 + 0x50) != 0)) {
              cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x49,&plStackX_8,
                                       _DAT_7ffe9c934418);
              if (cVar3 != '\0') {
                if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                  (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
                iVar5 = iVar5 + iVar6;
              }
              plVar1 = *(longlong **)(thisObject + 0x10);
              if (((plVar1 != (longlong *)0x0) &&
                  (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
                  lVar7 != 0)) && (*(longlong *)(lVar7 + 0x50) != 0)) {
                cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x4c9,&plStackX_8,
                                         _DAT_7ffe9c934418);
                if (cVar3 != '\0') {
                  if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                  iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                    (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
                  iVar5 = iVar5 + iVar6;
                }
                plVar1 = *(longlong **)(thisObject + 0x10);
                if ((plVar1 != (longlong *)0x0) &&
                   (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
                   lVar7 != 0)) {
                  cVar3 = FUN_7ffe9a7cbb30(lVar7,0x91,&plStackX_8,0);
                  if (cVar3 != '\0') {
                    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                    iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                      (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
                    iVar5 = iVar5 + iVar6;
                  }
                  plVar1 = *(longlong **)(thisObject + 0x10);
                  if ((plVar1 != (longlong *)0x0) &&
                     (lVar7 = (**(code **)(*plVar1 + 0x1c8))
                                        (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 != 0)) {
                    cVar3 = FUN_7ffe9a7cbb30(lVar7,0x291,&plStackX_8,0);
                    if (cVar3 != '\0') {
                      if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                      iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                        (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
                      iVar5 = iVar5 + iVar6;
                    }
                    plVar1 = *(longlong **)(thisObject + 0x10);
                    if ((plVar1 != (longlong *)0x0) &&
                       (lVar7 = (**(code **)(*plVar1 + 0x1c8))
                                          (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 != 0)) {
                      cVar3 = FUN_7ffe9a7cbb30(lVar7,0x2c8,&plStackX_8,0);
                      if (cVar3 != '\0') {
                        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                        iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                          (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
                        iVar5 = iVar5 + iVar6;
                      }
                      if (isNormalAttack != 0) {
                        plVar1 = *(longlong **)(thisObject + 0x10);
                        if ((plVar1 == (longlong *)0x0) ||
                           (lVar7 = (**(code **)(*plVar1 + 0x1c8))
                                              (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 == 0)
                           ) goto LAB_7ffe9a47398c;
                        cVar3 = FUN_7ffe9a7cbb30(lVar7,299,&plStackX_8,0);
                        if (cVar3 != '\0') {
                          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                          iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                            (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
                          iVar5 = iVar5 + iVar6;
                        }
                      }
                      plVar1 = *(longlong **)(thisObject + 0x10);
                      if ((plVar1 != (longlong *)0x0) &&
                         (lVar7 = (**(code **)(*plVar1 + 0x1c8))
                                            (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 != 0))
                      {
                        cVar3 = FUN_7ffe9a7cbb30(lVar7,0x229,&plStackX_8,0);
                        if (cVar3 != '\0') {
                          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                          iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                            (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200));
                          iVar5 = iVar5 + iVar6;
                        }
                        plVar1 = *(longlong **)(thisObject + 0x10);
                        if (((plVar1 != (longlong *)0x0) &&
                            (lVar7 = (**(code **)(*plVar1 + 0x1c8))
                                               (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 != 0
                            )) && (*(longlong *)(lVar7 + 0x50) != 0)) {
                          cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x22e,&plStackX_8,
                                                   _DAT_7ffe9c934418);
                          if (cVar3 != '\0') {
                            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                            iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                              (plStackX_8,0x13,*(undefined8 *)(*plStackX_8 + 0x200))
                            ;
                            iVar5 = iVar5 + iVar6;
                          }
                          plVar1 = *(longlong **)(thisObject + 0x10);
                          if ((plVar1 != (longlong *)0x0) &&
                             (lVar7 = (**(code **)(*plVar1 + 0x1c8))
                                                (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
                             lVar7 != 0)) {
                            cVar3 = FUN_7ffe9a7cbb30(lVar7,0x22f,&plStackX_8,0);
                            if (cVar3 != '\0') {
                              if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                              iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                                (plStackX_8,0x13,
                                                 *(undefined8 *)(*plStackX_8 + 0x200));
                              iVar5 = iVar5 + iVar6;
                            }
                            plVar1 = *(longlong **)(thisObject + 0x10);
                            if (((plVar1 != (longlong *)0x0) &&
                                (lVar7 = (**(code **)(*plVar1 + 0x1b8))
                                                   (plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
                                lVar7 != 0)) && (*(longlong *)(lVar7 + 0x68) != 0)) {
                              cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0x22f,
                                                       &plStackX_20,_DAT_7ffe9c935bd0);
                              if (cVar3 == '\0') {
                                return iVar5;
                              }
                              plVar1 = *(longlong **)(thisObject + 0x10);
                              if ((plVar1 != (longlong *)0x0) &&
                                 (lVar7 = (**(code **)(*plVar1 + 0x1f8))
                                                    (plVar1,*(undefined8 *)(*plVar1 + 0x200)),
                                 lVar7 != 0)) {
                                iVar6 = FUN_7ffe99c09050(lVar7,0);
                                if (iVar6 == 0xd) {
                                  if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a47398c;
                                  iVar6 = (**(code **)(*plStackX_20 + 0x178))
                                                    (plStackX_20,0x16,
                                                     *(undefined8 *)(*plStackX_20 + 0x180));
                                  iVar5 = iVar5 + iVar6;
                                }
                                return iVar5;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a47398c:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

