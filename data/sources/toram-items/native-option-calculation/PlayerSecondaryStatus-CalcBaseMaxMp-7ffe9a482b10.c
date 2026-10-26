
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_CalcBaseMaxMp(undefined *self,undefined *methodInfo)

{
  int iVar1;
  longlong *plVar2;
  code *pcVar3;
  int iVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined *puVar9;
  longlong lVar10;
  int aiStackX_8 [2];
  float afStackX_18 [2];
  longlong *plStackX_20;
  
  if (DAT_7ffe9cadde20 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cadde20 = '\x01';
  }
  plVar2 = *(longlong **)(self + 0x10);
  afStackX_18[0] = 0.0;
  plStackX_20 = (longlong *)0x0;
  aiStackX_8[0] = 0;
  if ((plVar2 != (longlong *)0x0) &&
     (puVar9 = (undefined *)(**(code **)(*plVar2 + 0x1d8))(plVar2,*(undefined8 *)(*plVar2 + 0x1e0)),
     puVar9 != (undefined *)0x0)) {
    BonusManager_GetMaxMpBonusConstant_Rate
              (puVar9,(undefined *)aiStackX_8,(undefined *)afStackX_18,(undefined *)0x0);
    plVar2 = *(longlong **)(self + 0x10);
    if ((plVar2 != (longlong *)0x0) &&
       ((lVar10 = (**(code **)(*plVar2 + 0x1b8))(plVar2,*(undefined8 *)(*plVar2 + 0x1c0)),
        lVar10 != 0 && (*(longlong *)(lVar10 + 0x68) != 0)))) {
      cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x68),200,&plStackX_20,_DAT_7ffe9c935bd0);
      iVar7 = aiStackX_8[0];
      if (cVar6 != '\0') {
        if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a482ec3;
        aiStackX_8[0] =
             (**(code **)(*plStackX_20 + 0x178))
                       (plStackX_20,0xe,*(undefined8 *)(*plStackX_20 + 0x180));
        aiStackX_8[0] = aiStackX_8[0] + iVar7;
      }
      plVar2 = *(longlong **)(self + 0x10);
      if (((plVar2 != (longlong *)0x0) &&
          (lVar10 = (**(code **)(*plVar2 + 0x1b8))(plVar2,*(undefined8 *)(*plVar2 + 0x1c0)),
          lVar10 != 0)) && (*(longlong *)(lVar10 + 0x68) != 0)) {
        cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x68),0x264,&plStackX_20,_DAT_7ffe9c935bd0);
        iVar7 = aiStackX_8[0];
        if (cVar6 != '\0') {
          if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a482ec3;
          aiStackX_8[0] = (**(code **)(*plStackX_20 + 0x178))(plStackX_20,0xe);
          aiStackX_8[0] = iVar7 + aiStackX_8[0];
        }
        iVar7 = aiStackX_8[0];
        plVar2 = *(longlong **)(self + 0x10);
        if ((plVar2 != (longlong *)0x0) &&
           (lVar10 = (**(code **)(*plVar2 + 0x1c8))(plVar2,*(undefined8 *)(*plVar2 + 0x1d0)),
           lVar10 != 0)) {
          aiStackX_8[0] = func_0x7ffe9a7c8f00(lVar10,0x40);
          fVar5 = afStackX_18[0];
          plVar2 = *(longlong **)(self + 0x10);
          aiStackX_8[0] = aiStackX_8[0] + iVar7;
          if ((plVar2 != (longlong *)0x0) &&
             (lVar10 = (**(code **)(*plVar2 + 0x1c8))(plVar2,*(undefined8 *)(*plVar2 + 0x1d0)),
             lVar10 != 0)) {
            iVar7 = func_0x7ffe9a7c8f00(lVar10,0x41);
            plVar2 = *(longlong **)(self + 0x10);
            afStackX_18[0] = (float)iVar7 / _DAT_7ffe9c049cfc + fVar5;
            if ((plVar2 != (longlong *)0x0) &&
               (puVar9 = (undefined *)
                         (**(code **)(*plVar2 + 0x1d8))(plVar2,*(undefined8 *)(*plVar2 + 0x1e0)),
               puVar9 != (undefined *)0x0)) {
              puVar9 = BonusManager_GetEquipElement(puVar9,(undefined *)0x1,(undefined *)0x0);
              iVar7 = aiStackX_8[0];
              if ((int)puVar9 == 8) {
                plVar2 = *(longlong **)(self + 0x10);
                if ((plVar2 == (longlong *)0x0) ||
                   (lVar10 = (**(code **)(*plVar2 + 0x188))(plVar2,*(undefined8 *)(*plVar2 + 400)),
                   lVar10 == 0)) goto LAB_7ffe9a482ec3;
                aiStackX_8[0] = (int)((float)*(int *)(lVar10 + 0x18) / _DAT_7ffe9c049dc4) + iVar7;
              }
              plVar2 = *(longlong **)(self + 0x10);
              if ((plVar2 != (longlong *)0x0) &&
                 (lVar10 = (**(code **)(*plVar2 + 0x188))(plVar2,*(undefined8 *)(*plVar2 + 400)),
                 lVar10 != 0)) {
                plVar2 = *(longlong **)(self + 0x10);
                iVar7 = *(int *)(lVar10 + 0x10);
                if ((plVar2 != (longlong *)0x0) &&
                   (lVar10 = (**(code **)(*plVar2 + 0x188))(plVar2,*(undefined8 *)(*plVar2 + 400)),
                   lVar10 != 0)) {
                  iVar8 = PlayerSecondaryStatus_CalcBaseSecondaryStatus
                                    (self,*(int *)(lVar10 + 0x18),7,2,(undefined *)0x0);
                  plVar2 = *(longlong **)(self + 0x10);
                  if ((plVar2 != (longlong *)0x0) &&
                     (lVar10 = (**(code **)(*plVar2 + 0x188))(plVar2,*(undefined8 *)(*plVar2 + 400))
                     , fVar5 = afStackX_18[0], iVar4 = aiStackX_8[0], lVar10 != 0)) {
                    iVar1 = *(int *)(lVar10 + 0x34);
                    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    iVar7 = func_0x7ffe9b506b70(0,(int)((float)(iVar8 / 10 + 99 + iVar1 + iVar7) *
                                                       fVar5) + iVar4,0);
                    return iVar7;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a482ec3:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  iVar7 = (*pcVar3)();
  return iVar7;
}

