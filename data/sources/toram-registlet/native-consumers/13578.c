
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_CurrectHit(undefined *thisObject,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  undefined *puVar6;
  int aiStackX_8 [2];
  longlong *plStackX_18;
  
  if (DAT_7ffe9cadde11 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968e08);
    DAT_7ffe9cadde11 = '\x01';
  }
  plVar1 = *(longlong **)(thisObject + 0x10);
  plStackX_18 = (longlong *)0x0;
  aiStackX_8[0] = 0;
  if (plVar1 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if ((lVar5 != 0) && (plVar1 = *(longlong **)(lVar5 + 0x18), plVar1 != (longlong *)0x0)) {
      (**(code **)(*plVar1 + 0x1d8))(plVar1,aiStackX_8,*(undefined8 *)(*plVar1 + 0x1e0));
      plVar1 = *(longlong **)(thisObject + 0x10);
      if (plVar1 != (longlong *)0x0) {
        lVar5 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
        if (lVar5 != 0) {
          cVar3 = FUN_7ffe9a7cbb30(lVar5,0x3d3,&plStackX_18,0);
          if (cVar3 != '\0') {
            plVar1 = *(longlong **)(thisObject + 0x10);
            if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a48835d;
            lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
            if (lVar5 == 0) goto LAB_7ffe9a48835d;
            lVar5 = FUN_7ffe99c090e0(lVar5,0);
            iVar4 = aiStackX_8[0];
            if ((lVar5 != 0) && (*(int *)(lVar5 + 0x38) == 9)) {
              if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a48835d;
              if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c968e08 + 0x130)) ||
                  (*(longlong *)
                    (*(longlong *)(*plStackX_18 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c968e08 + 0x130) * 8) != _DAT_7ffe9c968e08)) ||
                 (plStackX_18 == (longlong *)0x0)) {
                FUN_7ffe9996c950(plStackX_18);
                pcVar2 = (code *)swi(3);
                iVar4 = (*pcVar2)();
                return iVar4;
              }
              aiStackX_8[0] = func_0x7ffe9a7a51f0(plStackX_18,0);
              aiStackX_8[0] = aiStackX_8[0] + iVar4;
            }
          }
          plVar1 = *(longlong **)(thisObject + 0x10);
          if (plVar1 != (longlong *)0x0) {
            puVar6 = (undefined *)
                     (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220));
            if (puVar6 != (undefined *)0x0) {
              puVar6 = GemCartBufferManager_GetGemCartBuffer(puVar6,0xf,(undefined *)0x0);
              if (puVar6 != (undefined *)0x0) {
                iVar4 = GemCartBufferBase_GetValue(puVar6,(undefined *)0x2,(undefined *)0x0);
                if (iVar4 != 0) {
                  aiStackX_8[0] = 100;
                }
                return aiStackX_8[0];
              }
              return aiStackX_8[0];
            }
          }
        }
      }
    }
  }
LAB_7ffe9a48835d:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

