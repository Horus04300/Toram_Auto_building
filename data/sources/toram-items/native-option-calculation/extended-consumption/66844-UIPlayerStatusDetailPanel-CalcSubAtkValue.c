
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int UIPlayerStatusDetailPanel_CalcSubAtkValue(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar1 = *(longlong **)(self + 0x70);
  if (plVar1 != (longlong *)0x0) {
    lVar4 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if (lVar4 != 0) {
      lVar4 = FUN_7ffe99c08fe0(lVar4,0);
      plVar1 = *(longlong **)(self + 0x70);
      if (plVar1 != (longlong *)0x0) {
        lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
        if (lVar5 != 0) {
          lVar5 = FUN_7ffe99c08fe0(lVar5,0);
          if ((((lVar4 == 0) || (*(int *)(lVar4 + 0x38) != 10)) || (lVar5 == 0)) ||
             (*(int *)(lVar5 + 0x38) != 10)) {
            return 0;
          }
          lVar4 = *(longlong *)(self + 0x78);
          if (lVar4 != 0) {
            plVar1 = *(longlong **)(lVar4 + 0x10);
            if (plVar1 != (longlong *)0x0) {
              lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
              if ((lVar5 != 0) && (plVar1 = *(longlong **)(lVar5 + 0x20), plVar1 != (longlong *)0x0)
                 ) {
                    /* WARNING: Could not recover jumptable at 0x7ffe9a41b3bd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                iVar3 = (**(code **)(*plVar1 + 0x178))
                                  (plVar1,*(undefined8 *)(lVar4 + 0x10),
                                   *(undefined8 *)(*plVar1 + 0x180));
                return iVar3;
              }
            }
            FUN_7ffe9996d7a0();
            pcVar2 = (code *)swi(3);
            iVar3 = (*pcVar2)();
            return iVar3;
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

