
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnEventTreasureHuntGameStart
               (undefined *self,undefined *game,undefined *startEvent,undefined *methodInfo)

{
  int iVar1;
  longlong *plVar2;
  code *pcVar3;
  longlong lVar4;
  longlong lVar5;
  uint uVar6;
  undefined4 uVar7;
  float fVar8;
  
  if (DAT_7ffe9cae0b36 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c96c9c0);
    DAT_7ffe9cae0b36 = '\x01';
  }
  lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar5 != 0) {
    plVar2 = *(longlong **)(lVar5 + 0x28);
    if (plVar2 != (longlong *)0x0) {
      if ((*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) <= *(byte *)(*plVar2 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar2 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) * 8)
          == _DAT_7ffe9c96c9c0)) {
        if (startEvent != (undefined *)0x0) {
          iVar1 = *(int *)(startEvent + 0x20);
          uVar7 = FUN_7ffe9bda7da0(0,iVar1,0);
          *(undefined4 *)((longlong)plVar2 + 0xac) = uVar7;
          *(undefined4 *)(plVar2 + 0x15) = 2;
          fVar8 = (float)iVar1;
          *(float *)((longlong)plVar2 + 0xb4) = fVar8;
          *(float *)(plVar2 + 0x16) = fVar8;
          if (plVar2[0x1e] == 0) {
            FUN_7ffe9996d7a0();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          FUN_7ffe9a4d6a90(plVar2[0x1e],0);
          if (DAT_7ffe9cadea98 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c956140,0);
            DAT_7ffe9cadea98 = '\x01';
          }
          lVar5 = plVar2[0x21];
          if (lVar5 != 0) {
            for (uVar6 = 0; (int)uVar6 < *(int *)(lVar5 + 0x18); uVar6 = uVar6 + 1) {
              if (*(uint *)(lVar5 + 0x18) <= uVar6) {
                FUN_7ffe9996d790();
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              uVar7 = *(undefined4 *)(lVar5 + 0x20 + (longlong)(int)uVar6 * 4);
              lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c956140);
              if ((lVar4 == 0) || (*(longlong *)(lVar4 + 0x20) == 0)) {
                FUN_7ffe9996d7a0();
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              FUN_7ffe9a9b86b0(*(longlong *)(lVar4 + 0x20),uVar7,0);
            }
            plVar2[0x21] = 0;
            il2cpp_write_barrier_0();
          }
          return;
        }
        goto LAB_7ffe9aaadf0e;
      }
    }
    return;
  }
LAB_7ffe9aaadf0e:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

