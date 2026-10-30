
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __c__DisplayClass64_0__AddAbnormalState_b__4
               (undefined *thisObject,undefined *x,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined *puVar6;
  
  if (DAT_7ffe9caddc23 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9422c8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9caddc23 = '\x01';
  }
  if (*(longlong *)(thisObject + 0x10) != 0) {
    FUN_7ffe9a42c580(*(longlong *)(thisObject + 0x10),x,0);
    if ((*(longlong *)(thisObject + 0x10) != 0) &&
       (lVar4 = *(longlong *)(*(longlong *)(thisObject + 0x10) + 0x38), lVar4 != 0)) {
      lVar4 = FUN_7ffe9ab6e260(lVar4,_DAT_7ffe9c9422c8);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar2 = FUN_7ffe9bda2160(lVar4,0,0);
      if (cVar2 != '\0') {
        if (lVar4 == 0) goto LAB_7ffe9a442b33;
        FUN_7ffe9bd73570(lVar4,0);
      }
      lVar4 = *(longlong *)(thisObject + 0x10);
      if ((lVar4 != 0) && (*(longlong *)(lVar4 + 0x30) != 0)) {
        plVar5 = *(longlong **)(lVar4 + 0x38);
        if (*(char *)(*(longlong *)(lVar4 + 0x30) + 0x6a) == '\0') {
          if (plVar5 == (longlong *)0x0) goto LAB_7ffe9a442b33;
          (**(code **)(*plVar5 + 0x238))(plVar5,*(undefined8 *)(*plVar5 + 0x240));
        }
        else {
          if (plVar5 == (longlong *)0x0) goto LAB_7ffe9a442b33;
          (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0));
        }
        plVar5 = *(longlong **)(thisObject + 0x10);
        if (((plVar5 != (longlong *)0x0) &&
            (plVar5 = (longlong *)
                      (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
            plVar5 != (longlong *)0x0)) &&
           (puVar6 = (undefined *)
                     (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
           puVar6 != (undefined *)0x0)) {
          puVar6 = GemCartBufferManager_GetGemCartBuffer(puVar6,0x4c,(undefined *)0x0);
          if (puVar6 == (undefined *)0x0) {
            return;
          }
          plVar5 = *(longlong **)(thisObject + 0x10);
          if (plVar5 != (longlong *)0x0) {
            lVar4 = (**(code **)(*plVar5 + 0x2a8))(plVar5,*(undefined8 *)(*plVar5 + 0x2b0));
            iVar3 = GemCartBufferBase_GetValue(puVar6,(undefined *)0x2,(undefined *)0x0);
            if (lVar4 != 0) {
              FUN_7ffe9a4d99d0(lVar4,(float)iVar3 / _DAT_7ffe9c049ce4,0,0);
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a442b33:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

