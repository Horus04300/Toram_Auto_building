
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_AtkMpRecovery(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  float fVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  undefined *self_00;
  uint uVar10;
  uint uVar11;
  float fVar12;
  float fVar13;
  int aiStackX_8 [4];
  float afStackX_18 [2];
  longlong lStackX_20;
  longlong *aplStack_68 [6];
  
  if (DAT_7ffe9cadde13 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9cadde13 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  lStackX_20 = 0;
  aplStack_68[0] = (longlong *)0x0;
  if ((plVar1 != (longlong *)0x0) &&
     (lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar9 != 0))
  {
    cVar4 = FUN_7ffe9a7cbb30(lVar9,0x241,&lStackX_20,0);
    if (cVar4 != '\0') {
      if (lStackX_20 == 0) goto LAB_7ffe9a486e5c;
      if (*(char *)(lStackX_20 + 0x1c) != '\0') {
        return 0;
      }
    }
    uVar5 = PlayerSecondaryStatus_CalcBaseMaxMp(self,(undefined *)0x0);
    fVar13 = _DAT_7ffe9c049b18;
    uVar11 = 0;
    uVar10 = uVar11;
    if ((-1 < (int)uVar5) && (uVar10 = uVar5, 2000 < (int)uVar5)) {
      uVar10 = 2000;
    }
    plVar1 = *(longlong **)(self + 0x10);
    aiStackX_8[0] = 0;
    afStackX_18[0] = 1.0;
    if ((plVar1 != (longlong *)0x0) &&
       (self_00 = (undefined *)
                  (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0)),
       self_00 != (undefined *)0x0)) {
      BonusManager_GetBonusConstant_Rate
                (self_00,0x26,0x27,(undefined *)aiStackX_8,(undefined *)afStackX_18,(undefined *)0x0
                );
      fVar3 = afStackX_18[0];
      plVar1 = *(longlong **)(self + 0x10);
      if ((plVar1 != (longlong *)0x0) &&
         (lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
         lVar9 != 0)) {
        iVar6 = func_0x7ffe9a7c8f00(lVar9,0x22);
        iVar7 = aiStackX_8[0];
        plVar1 = *(longlong **)(self + 0x10);
        afStackX_18[0] = (float)iVar6 / _DAT_7ffe9c049cfc + fVar3;
        if ((plVar1 != (longlong *)0x0) &&
           (lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
           lVar9 != 0)) {
          aiStackX_8[0] = func_0x7ffe9a7c8f00(lVar9,0x21);
          fVar3 = afStackX_18[0];
          plVar1 = *(longlong **)(self + 0x10);
          aiStackX_8[0] = aiStackX_8[0] + iVar7;
          if ((plVar1 != (longlong *)0x0) &&
             (lVar9 = (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
             lVar9 != 0)) {
            fVar12 = (float)FUN_7ffe9a5b21c0(lVar9,7);
            plVar1 = *(longlong **)(self + 0x10);
            afStackX_18[0] = fVar12 / _DAT_7ffe9c049cfc + fVar3;
            if (((plVar1 != (longlong *)0x0) &&
                (lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
                lVar9 != 0)) && (*(longlong *)(lVar9 + 0x18) != 0)) {
              iVar7 = func_0x7ffe99c1ed70(*(longlong *)(lVar9 + 0x18),0);
              plVar1 = *(longlong **)(self + 0x10);
              if (((plVar1 != (longlong *)0x0) &&
                  (lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
                  lVar9 != 0)) && (*(longlong *)(lVar9 + 0x20) != 0)) {
                iVar6 = func_0x7ffe99c1ed70(*(longlong *)(lVar9 + 0x20),0);
                plVar1 = *(longlong **)(self + 0x10);
                if (((plVar1 != (longlong *)0x0) &&
                    (lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0))
                    , lVar9 != 0)) && (*(longlong *)(lVar9 + 0x68) != 0)) {
                  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x85,aplStack_68,
                                           _DAT_7ffe9c935bd0);
                  iVar8 = aiStackX_8[0];
                  if ((cVar4 != '\0') && (((iVar7 == 0x10 || (iVar6 == 0x10)) || (iVar7 == 0)))) {
                    if (aplStack_68[0] == (longlong *)0x0) goto LAB_7ffe9a486e5c;
                    aiStackX_8[0] =
                         (**(code **)(*aplStack_68[0] + 0x178))
                                   (aplStack_68[0],0x1c,*(undefined8 *)(*aplStack_68[0] + 0x180));
                    aiStackX_8[0] = aiStackX_8[0] + iVar8;
                  }
                  if ((iVar7 == 10) || (iVar7 == 0xb)) {
                    plVar1 = *(longlong **)(self + 0x10);
                    if ((plVar1 == (longlong *)0x0) ||
                       (lVar9 = (**(code **)(*plVar1 + 0x1c8))
                                          (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar9 == 0))
                    goto LAB_7ffe9a486e5c;
                    cVar4 = FUN_7ffe9a7cbb30(lVar9,0x29,&lStackX_20);
                    iVar8 = aiStackX_8[0];
                    if (cVar4 != '\0') {
                      if (iVar7 == 10) {
                        uVar11 = (uint)(iVar6 == 10);
                      }
                      if (lStackX_20 == 0) goto LAB_7ffe9a486e5c;
                      iVar6 = func_0x7ffe9a7a2140(lStackX_20,0x33);
                      aiStackX_8[0] = iVar6 / (int)(uVar11 + 1) + iVar8;
                    }
                  }
                  plVar1 = *(longlong **)(self + 0x10);
                  if ((plVar1 != (longlong *)0x0) &&
                     (lVar9 = (**(code **)(*plVar1 + 0x1c8))
                                        (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar9 != 0)) {
                    cVar4 = FUN_7ffe9a7cbb30(lVar9,0x26b,&lStackX_20,0);
                    iVar6 = aiStackX_8[0];
                    if (cVar4 != '\0') {
                      if (lStackX_20 == 0) goto LAB_7ffe9a486e5c;
                      iVar8 = func_0x7ffe9a7a2140(lStackX_20,0x32);
                      aiStackX_8[0] = iVar8 / (int)((iVar7 == 8) + 1) + iVar6;
                    }
                    plVar1 = *(longlong **)(self + 0x10);
                    if ((plVar1 != (longlong *)0x0) &&
                       (lVar9 = (**(code **)(*plVar1 + 0x1c8))
                                          (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar9 != 0)) {
                      cVar4 = FUN_7ffe9a7cbb30(lVar9,0x442,&lStackX_20,0);
                      if (cVar4 != '\0') {
                        plVar1 = *(longlong **)(self + 0x10);
                        if (((plVar1 == (longlong *)0x0) ||
                            (lVar9 = (**(code **)(*plVar1 + 0x1b8))
                                               (plVar1,*(undefined8 *)(*plVar1 + 0x1c0)), lVar9 == 0
                            )) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a486e5c;
                        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x446,aplStack_68,
                                                 _DAT_7ffe9c935bd0);
                        if (cVar4 != '\0') {
                          if (lStackX_20 == 0) goto LAB_7ffe9a486e5c;
                          iVar6 = func_0x7ffe9a7a2140(lStackX_20,0x14);
                          iVar7 = aiStackX_8[0];
                          if (0 < iVar6) {
                            if (aplStack_68[0] == (longlong *)0x0) goto LAB_7ffe9a486e5c;
                            aiStackX_8[0] =
                                 (**(code **)(*aplStack_68[0] + 0x178))
                                           (aplStack_68[0],0x1c,
                                            *(undefined8 *)(*aplStack_68[0] + 0x180));
                            aiStackX_8[0] = aiStackX_8[0] + iVar7;
                          }
                        }
                      }
                      plVar1 = *(longlong **)(self + 0x10);
                      if ((plVar1 != (longlong *)0x0) &&
                         (lVar9 = (**(code **)(*plVar1 + 0x1c8))
                                            (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar9 != 0))
                      {
                        cVar4 = FUN_7ffe9a7cbb30(lVar9,0x461,&lStackX_20,0);
                        if (cVar4 != '\0') {
                          if (lStackX_20 == 0) goto LAB_7ffe9a486e5c;
                          iVar7 = func_0x7ffe9a7a2140(lStackX_20,0x34);
                          fVar13 = (float)iVar7 / _DAT_7ffe9c049cfc + fVar13;
                        }
                        return (int)(((float)((int)uVar10 / 100 + 10) * afStackX_18[0] +
                                     (float)aiStackX_8[0]) * fVar13);
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
LAB_7ffe9a486e5c:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar7 = (*pcVar2)();
  return iVar7;
}

