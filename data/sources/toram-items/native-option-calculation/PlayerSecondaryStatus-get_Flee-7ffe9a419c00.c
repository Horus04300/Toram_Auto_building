
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_Flee(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined *self_00;
  longlong lVar6;
  longlong lVar7;
  float fVar8;
  int aiStackX_10 [4];
  float afStackX_20 [2];
  longlong *plStack_38;
  longlong alStack_30 [3];
  
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 != (longlong *)0x0) {
    alStack_30[0] = 0x7ffe9a419c25;
    lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if (lVar7 != 0) {
      plVar1 = *(longlong **)(self + 0x10);
      if (DAT_7ffe9cada8ba == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c935bd0,plVar1,0);
        FUN_7ffe9996d590(&DAT_7ffe9c940d40);
        DAT_7ffe9cada8ba = '\x01';
      }
      afStackX_20[0] = _DAT_7ffe9c049b18;
      plStack_38 = (longlong *)0x0;
      aiStackX_10[0] = 0;
      if ((plVar1 != (longlong *)0x0) &&
         (self_00 = (undefined *)
                    (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0)),
         self_00 != (undefined *)0x0)) {
        BonusManager_GetBonusConstant_AvatarConstan_Rate
                  (self_00,0x18,0xb7,0x19,(undefined *)aiStackX_10,(undefined *)afStackX_20,
                   (undefined *)0x0);
        lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
        if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x68) != 0)) {
          cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x1e6,&plStack_38,_DAT_7ffe9c935bd0);
          iVar5 = aiStackX_10[0];
          if (cVar3 != '\0') {
            if (plStack_38 == (longlong *)0x0) goto LAB_7ffe99c07ce7;
            aiStackX_10[0] =
                 (**(code **)(*plStack_38 + 0x178))
                           (plStack_38,0x13,*(undefined8 *)(*plStack_38 + 0x180));
            aiStackX_10[0] = aiStackX_10[0] + iVar5;
          }
          lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
          if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x68) != 0)) {
            cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x4c1,&plStack_38,_DAT_7ffe9c935bd0
                                    );
            iVar5 = aiStackX_10[0];
            if (cVar3 != '\0') {
              if (plStack_38 == (longlong *)0x0) goto LAB_7ffe99c07ce7;
              aiStackX_10[0] =
                   (**(code **)(*plStack_38 + 0x178))
                             (plStack_38,0x13,*(undefined8 *)(*plStack_38 + 0x180));
              aiStackX_10[0] = aiStackX_10[0] + iVar5;
            }
            fVar8 = afStackX_20[0];
            lVar6 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
            if (lVar6 != 0) {
              iVar4 = func_0x7ffe9a7c8f00(lVar6,0xc);
              iVar5 = aiStackX_10[0];
              afStackX_20[0] = (float)iVar4 / _DAT_7ffe9c049cfc + fVar8;
              lVar6 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
              if (lVar6 != 0) {
                aiStackX_10[0] = func_0x7ffe9a7c8f00(lVar6,0xd);
                aiStackX_10[0] = aiStackX_10[0] + iVar5;
                if (DAT_7ffe9cada8b3 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c95a358);
                  DAT_7ffe9cada8b3 = '\x01';
                }
                alStack_30[0] = 0;
                if (*(longlong *)(lVar7 + 0x10) == 0) {
                  FUN_7ffe9996d7a0();
                  pcVar2 = (code *)swi(3);
                  iVar5 = (*pcVar2)();
                  return iVar5;
                }
                cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x10),3,alStack_30,_DAT_7ffe9c95a358)
                ;
                if ((cVar3 == '\0') || (alStack_30[0] == 0)) {
                  cVar3 = '\x03';
                }
                else {
                  lVar7 = FUN_7ffe99c08d90(lVar7,0);
                  if (lVar7 == 0) goto LAB_7ffe99c07ce7;
                  cVar3 = func_0x7ffe9a56fc20(lVar7,0);
                }
                if (cVar3 != '\0') {
                  if (cVar3 == '\x01') {
                    lVar7 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
                    if (lVar7 == 0) goto LAB_7ffe99c07ce7;
                    iVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar7);
                    lVar7 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
                    if (lVar7 == 0) goto LAB_7ffe99c07ce7;
                    iVar4 = FUN_7ffe99742ec0(4,_DAT_7ffe9c940d40,lVar7);
                    fVar8 = (float)iVar4 * _DAT_7ffe9c04a124 + (float)iVar5 * _DAT_7ffe9c049fb8 +
                            _DAT_7ffe9c049e64;
                  }
                  else if (cVar3 == '\x02') {
                    lVar7 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
                    if (lVar7 == 0) goto LAB_7ffe99c07ce7;
                    iVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar7);
                    lVar7 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
                    if (lVar7 == 0) goto LAB_7ffe99c07ce7;
                    iVar4 = FUN_7ffe99742ec0(4,_DAT_7ffe9c940d40,lVar7);
                    fVar8 = ((float)iVar4 * _DAT_7ffe9c049cc8 + (float)iVar5 * _DAT_7ffe9c049b4c) -
                            _DAT_7ffe9c049ce8;
                  }
                  else {
                    if (cVar3 != '\x03') {
                      return 0;
                    }
                    lVar7 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
                    if (lVar7 == 0) goto LAB_7ffe99c07ce7;
                    iVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar7);
                    lVar7 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
                    if (lVar7 == 0) goto LAB_7ffe99c07ce7;
                    iVar4 = FUN_7ffe99742ec0(4,_DAT_7ffe9c940d40,lVar7);
                    fVar8 = (float)iVar5 * _DAT_7ffe9c049cd8 + (float)iVar4 + (float)iVar4 +
                            _DAT_7ffe9c049d94;
                  }
                  iVar4 = (int)fVar8;
LAB_7ffe99c07b26:
                  return (int)((float)iVar4 * afStackX_20[0]) + aiStackX_10[0];
                }
                lVar7 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
                if (lVar7 != 0) {
                  iVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar7);
                  lVar7 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
                  if (lVar7 != 0) {
                    iVar4 = FUN_7ffe99742ec0(4,_DAT_7ffe9c940d40,lVar7);
                    iVar4 = iVar4 + iVar5;
                    goto LAB_7ffe99c07b26;
                  }
                }
              }
            }
          }
        }
      }
LAB_7ffe99c07ce7:
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      iVar5 = (*pcVar2)();
      return iVar5;
    }
  }
  alStack_30[0] = 0x7ffe9a419c43;
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

