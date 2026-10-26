
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_CalcBaseMaxHp(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined *self_00;
  float fVar7;
  float fVar8;
  int aiStackX_8 [4];
  float afStackX_18 [2];
  longlong *plStackX_20;
  longlong alStack_78 [10];
  
  if (DAT_7ffe9cadde21 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9cadde21 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  plStackX_20 = (longlong *)0x0;
  if ((plVar1 != (longlong *)0x0) &&
     (lVar6 = (**(code **)(*plVar1 + 0x188))(plVar1,*(undefined8 *)(*plVar1 + 400)), lVar6 != 0)) {
    plVar1 = *(longlong **)(self + 0x10);
    afStackX_18[0] = 0.0;
    aiStackX_8[0] = 0;
    fVar8 = (float)*(int *)(lVar6 + 0x10);
    if ((plVar1 != (longlong *)0x0) &&
       (self_00 = (undefined *)
                  (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0)),
       self_00 != (undefined *)0x0)) {
      BonusManager_GetMaxHpBonusConstant_Rate
                (self_00,(undefined *)aiStackX_8,(undefined *)afStackX_18,(undefined *)0x0);
      plVar1 = *(longlong **)(self + 0x10);
      if (((plVar1 != (longlong *)0x0) &&
          (lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
          lVar6 != 0)) && (*(longlong *)(lVar6 + 0x68) != 0)) {
        cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0xc6,&plStackX_20,_DAT_7ffe9c935bd0);
        fVar7 = afStackX_18[0];
        if (cVar3 != '\0') {
          if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a482af6;
          iVar4 = (**(code **)(*plStackX_20 + 0x178))
                            (plStackX_20,0xd,*(undefined8 *)(*plStackX_20 + 0x180));
          iVar5 = aiStackX_8[0];
          afStackX_18[0] = (float)iVar4 / _DAT_7ffe9c049cfc + fVar7;
          if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a482af6;
          aiStackX_8[0] =
               (**(code **)(*plStackX_20 + 0x178))
                         (plStackX_20,0xc,*(undefined8 *)(*plStackX_20 + 0x180));
          aiStackX_8[0] = aiStackX_8[0] + iVar5;
        }
        plVar1 = *(longlong **)(self + 0x10);
        if ((plVar1 != (longlong *)0x0) &&
           (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
           lVar6 != 0)) {
          lVar6 = FUN_7ffe99c08fe0(lVar6,0);
          if (lVar6 != 0) {
            plVar1 = *(longlong **)(self + 0x10);
            if (((plVar1 == (longlong *)0x0) ||
                (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
                lVar6 == 0)) || (lVar6 = FUN_7ffe99c08fe0(lVar6,0), lVar6 == 0))
            goto LAB_7ffe9a482af6;
            if (*(int *)(lVar6 + 0x38) == 0x11) {
              plVar1 = *(longlong **)(self + 0x10);
              if (((plVar1 == (longlong *)0x0) ||
                  (lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
                  lVar6 == 0)) || (*(longlong *)(lVar6 + 0x68) == 0)) goto LAB_7ffe9a482af6;
              cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x103,&plStackX_20,
                                       _DAT_7ffe9c935bd0);
              iVar5 = aiStackX_8[0];
              if (cVar3 != '\0') {
                if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a482af6;
                aiStackX_8[0] =
                     (**(code **)(*plStackX_20 + 0x178))
                               (plStackX_20,0xc,*(undefined8 *)(*plStackX_20 + 0x180));
                aiStackX_8[0] = aiStackX_8[0] + iVar5;
              }
              plVar1 = *(longlong **)(self + 0x10);
              if (((plVar1 == (longlong *)0x0) ||
                  (lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
                  lVar6 == 0)) || (*(longlong *)(lVar6 + 0x68) == 0)) goto LAB_7ffe9a482af6;
              cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x105,&plStackX_20,
                                       _DAT_7ffe9c935bd0);
              iVar5 = aiStackX_8[0];
              if (cVar3 != '\0') {
                if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a482af6;
                aiStackX_8[0] =
                     (**(code **)(*plStackX_20 + 0x178))
                               (plStackX_20,0xc,*(undefined8 *)(*plStackX_20 + 0x180));
                aiStackX_8[0] = aiStackX_8[0] + iVar5;
              }
            }
          }
          plVar1 = *(longlong **)(self + 0x10);
          if (((plVar1 != (longlong *)0x0) &&
              (lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
              lVar6 != 0)) && (*(longlong *)(lVar6 + 0x68) != 0)) {
            cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x264,&plStackX_20,
                                     _DAT_7ffe9c935bd0);
            iVar5 = aiStackX_8[0];
            if (cVar3 != '\0') {
              if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a482af6;
              aiStackX_8[0] =
                   (**(code **)(*plStackX_20 + 0x178))
                             (plStackX_20,0xc,*(undefined8 *)(*plStackX_20 + 0x180));
              aiStackX_8[0] = aiStackX_8[0] + iVar5;
            }
            plVar1 = *(longlong **)(self + 0x10);
            if (((plVar1 != (longlong *)0x0) &&
                (lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
                lVar6 != 0)) && (*(longlong *)(lVar6 + 0x68) != 0)) {
              cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x2a9,&plStackX_20,
                                       _DAT_7ffe9c935bd0);
              iVar5 = aiStackX_8[0];
              if (cVar3 != '\0') {
                if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a482af6;
                iVar4 = (**(code **)(*plStackX_20 + 0x178))
                                  (plStackX_20,0xc,*(undefined8 *)(*plStackX_20 + 0x180));
                plVar1 = *(longlong **)(self + 0x10);
                if ((plVar1 == (longlong *)0x0) ||
                   (lVar6 = (**(code **)(*plVar1 + 0x188))(plVar1,*(undefined8 *)(*plVar1 + 400)),
                   lVar6 == 0)) goto LAB_7ffe9a482af6;
                aiStackX_8[0] = iVar4 + *(int *)(lVar6 + 0x10) * 10 + iVar5;
              }
              iVar5 = aiStackX_8[0];
              plVar1 = *(longlong **)(self + 0x10);
              if ((plVar1 != (longlong *)0x0) &&
                 (lVar6 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
                 lVar6 != 0)) {
                aiStackX_8[0] = func_0x7ffe9a7c8f00(lVar6,0x3d);
                fVar7 = afStackX_18[0];
                plVar1 = *(longlong **)(self + 0x10);
                aiStackX_8[0] = aiStackX_8[0] + iVar5;
                if ((plVar1 != (longlong *)0x0) &&
                   (lVar6 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
                   lVar6 != 0)) {
                  iVar5 = func_0x7ffe9a7c8f00(lVar6,0x3e);
                  plVar1 = *(longlong **)(self + 0x10);
                  fVar7 = (float)iVar5 / _DAT_7ffe9c049cfc + fVar7;
                  afStackX_18[0] = fVar7;
                  if ((plVar1 != (longlong *)0x0) &&
                     (lVar6 = (**(code **)(*plVar1 + 0x1c8))
                                        (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar6 != 0)) {
                    iVar5 = func_0x7ffe9a7c8f00(lVar6,0x3f);
                    plVar1 = *(longlong **)(self + 0x10);
                    alStack_78[0] = 0;
                    afStackX_18[0] = (float)iVar5 / _DAT_7ffe9c049ec0 + fVar7;
                    if ((plVar1 != (longlong *)0x0) &&
                       (lVar6 = (**(code **)(*plVar1 + 0x188))
                                          (plVar1,*(undefined8 *)(*plVar1 + 400)), lVar6 != 0)) {
                      iVar5 = PlayerSecondaryStatus_CalcBaseSecondaryStatus
                                        (self,*(int *)(lVar6 + 0x1c),8,3,(undefined *)0x0);
                      plVar1 = *(longlong **)(self + 0x10);
                      if ((plVar1 != (longlong *)0x0) &&
                         (lVar6 = (**(code **)(*plVar1 + 0x1c8))
                                            (plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar6 != 0))
                      {
                        cVar3 = FUN_7ffe9a7cbb30(lVar6,0x209,alStack_78,0);
                        if (cVar3 != '\0') {
                          if (alStack_78[0] == 0) goto LAB_7ffe9a482afc;
                          iVar5 = iVar5 + (uint)*(byte *)(alStack_78[0] + 0x10);
                        }
                        iVar5 = (int)(((float)iVar5 * fVar8) / _DAT_7ffe9c049b74 +
                                      (fVar8 * _DAT_7ffe9c04b3ec) / _DAT_7ffe9c049cfc +
                                      _DAT_7ffe9c04b3e8 + fVar8 * _DAT_7ffe9c04b3e0);
                        if ((-1 < iVar5) || (0.0 <= afStackX_18[0])) {
                          fVar8 = (float)iVar5 * afStackX_18[0] + (float)aiStackX_8[0];
                        }
                        else {
                          fVar8 = afStackX_18[0] * _DAT_7ffe9c049b90 * (float)iVar5 +
                                  (float)aiStackX_8[0];
                        }
                        return (int)fVar8;
                      }
                    }
LAB_7ffe9a482afc:
                    FUN_7ffe9996d7a0();
                    pcVar2 = (code *)swi(3);
                    iVar5 = (*pcVar2)();
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
LAB_7ffe9a482af6:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

