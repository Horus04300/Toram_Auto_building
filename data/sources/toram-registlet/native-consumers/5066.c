
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MainPlayer_OnChangeState(undefined *thisObject,undefined *response,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  
  if (DAT_7ffe9cadaeff == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c951220);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    DAT_7ffe9cadaeff = '\x01';
  }
  if (response != (undefined *)0x0) {
    if ((*(uint *)(response + 0x2c) & 3) == 0) {
      lVar4 = FUN_7ffe99d026a0(thisObject,0);
      if (lVar4 != 0) {
        if (*(char *)(lVar4 + 0x40) == '\0') {
          return;
        }
        if (*(longlong *)(thisObject + 0x110) != 0) {
          func_0x7ffe99b14380(*(longlong *)(thisObject + 0x110),0);
          plVar5 = (longlong *)FUN_7ffe99d026a0(thisObject,0);
          if (plVar5 != (longlong *)0x0) {
            (**(code **)(*plVar5 + 1000))(plVar5,*(undefined8 *)(*plVar5 + 0x3f0));
            return;
          }
        }
      }
    }
    else {
      FUN_7ffe99d006a0(thisObject,(*(uint *)(response + 0x2c) & 2) != 0,
                       *(undefined4 *)(response + 0x30),(int)*(short *)(response + 0x34),0);
      if (*(undefined **)(thisObject + 0x130) != (undefined *)0x0) {
        bVar2 = GemCartBufferManager_ContainsBuffer
                          (*(undefined **)(thisObject + 0x130),0x3e,(undefined *)0x0);
        if (bVar2 != 0) {
          lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
          if (lVar4 == 0) goto LAB_7ffe99cffb73;
          iVar3 = FUN_7ffe9a872680(lVar4,0);
          uVar6 = 2;
          if (iVar3 == 0x1d) {
            uVar6 = 0;
          }
          lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c951220);
          if (lVar4 == 0) goto LAB_7ffe99cffb73;
          FUN_7ffe9a4ff9c0(lVar4,uVar6,2,0);
        }
        plVar5 = *(longlong **)(thisObject + 0xd8);
        if ((plVar5 != (longlong *)0x0) &&
           (lVar4 = (**(code **)(*plVar5 + 0x178))(plVar5,*(undefined8 *)(*plVar5 + 0x180)),
           lVar4 != 0)) {
          func_0x7ffe9a480df0(lVar4);
          plVar5 = *(longlong **)(thisObject + 0xd8);
          if ((plVar5 != (longlong *)0x0) &&
             (lVar4 = (**(code **)(*plVar5 + 0x198))(plVar5,*(undefined8 *)(*plVar5 + 0x1a0)),
             lVar4 != 0)) {
            iVar3 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar4);
            if (0 < iVar3) {
              plVar5 = *(longlong **)(thisObject + 0xd8);
              if ((plVar5 == (longlong *)0x0) ||
                 (lVar4 = (**(code **)(*plVar5 + 0x198))(plVar5,*(undefined8 *)(*plVar5 + 0x1a0)),
                 lVar4 == 0)) goto LAB_7ffe99cffb73;
              iVar3 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c940d40,lVar4);
              if (-1 < iVar3) {
                return;
              }
            }
            FUN_7ffe99cfdb40(thisObject,0);
            return;
          }
        }
      }
    }
  }
LAB_7ffe99cffb73:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

