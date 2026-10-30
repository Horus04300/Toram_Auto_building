
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobaPlayerSecondaryStatus_get_AtkMpRecovery(undefined *thisObject,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  float fVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined *thisObject_00;
  float fVar9;
  float afStackX_8 [4];
  int aiStackX_18 [2];
  longlong lStackX_20;
  
  lStackX_20 = 0;
  plVar1 = *(longlong **)(thisObject + 0x10);
  if (plVar1 != (longlong *)0x0) {
    lVar8 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
    if (lVar8 != 0) {
      cVar5 = FUN_7ffe9a7cbb30(lVar8,0x241,&lStackX_20,0);
      if (cVar5 != '\0') {
        if (lStackX_20 == 0) goto LAB_7ffe9a474a91;
        if (*(char *)(lStackX_20 + 0x1c) != '\0') {
          return 0;
        }
      }
      iVar6 = FUN_7ffe9a477680(thisObject,0);
      plVar1 = *(longlong **)(thisObject + 0x10);
      afStackX_8[0] = _DAT_7ffe9c049b18;
      aiStackX_18[0] = 0;
      if (plVar1 != (longlong *)0x0) {
        lVar8 = (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
        if (lVar8 != 0) {
          FUN_7ffe9a4eac40(lVar8,0x26,0x27,aiStackX_18,afStackX_8,0);
          fVar3 = afStackX_8[0];
          plVar1 = *(longlong **)(thisObject + 0x10);
          if (plVar1 != (longlong *)0x0) {
            lVar8 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
            if (lVar8 != 0) {
              iVar7 = func_0x7ffe9a7c8f00(lVar8,0x22);
              iVar4 = aiStackX_18[0];
              plVar1 = *(longlong **)(thisObject + 0x10);
              afStackX_8[0] = (float)iVar7 / _DAT_7ffe9c049cfc + fVar3;
              if (plVar1 != (longlong *)0x0) {
                lVar8 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
                if (lVar8 != 0) {
                  aiStackX_18[0] = func_0x7ffe9a7c8f00(lVar8,0x21);
                  fVar3 = afStackX_8[0];
                  plVar1 = *(longlong **)(thisObject + 0x10);
                  aiStackX_18[0] = aiStackX_18[0] + iVar4;
                  if (plVar1 != (longlong *)0x0) {
                    thisObject_00 =
                         (undefined *)
                         (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220));
                    if (thisObject_00 != (undefined *)0x0) {
                      fVar9 = GemCartBufferManager_GetBufferValue
                                        (thisObject_00,(undefined *)0x7,(undefined *)0x0);
                      return (int)((float)(iVar6 / 100 + 10) * (fVar9 / _DAT_7ffe9c049cfc + fVar3) +
                                  (float)aiStackX_18[0]);
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
LAB_7ffe9a474a91:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar6 = (*pcVar2)();
  return iVar6;
}

