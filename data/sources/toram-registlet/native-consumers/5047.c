
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MainPlayer_UseItem(undefined *thisObject,int uuid,byte isAutoUse,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong lVar6;
  undefined *thisObject_00;
  longlong *plVar7;
  undefined8 uVar8;
  undefined4 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  byte bVar12;
  int aiStack_28 [4];
  
  if (DAT_7ffe9cadaef5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c969f98);
    FUN_7ffe9996d590(&DAT_7ffe9c96a130);
    FUN_7ffe9996d590(&DAT_7ffe9c9380b0);
    FUN_7ffe9996d590(&DAT_7ffe9c94ff20);
    FUN_7ffe9996d590(&DAT_7ffe9c950390);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c91ef20);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(&DAT_7ffe9c95d3c8);
    FUN_7ffe9996d590(&DAT_7ffe9c96fc00);
    DAT_7ffe9cadaef5 = '\x01';
  }
  lVar5 = func_0x7ffe99940040(_DAT_7ffe9c96fc00);
  func_0x7ffe999c3920(lVar5,0);
  if (lVar5 != 0) {
    *(undefined **)(lVar5 + 0x10) = thisObject;
    il2cpp_write_barrier_0();
    *(int *)(lVar5 + 0x18) = uuid;
    if (0.0 < *(float *)(thisObject + 0xa8)) {
      lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if (lVar5 != 0) {
        lVar5 = *(longlong *)(lVar5 + 0x188);
        lVar6 = func_0x7ffe9996c990(_DAT_7ffe9c91ef20,1);
        aiStack_28[0] = (int)*(float *)(thisObject + 0xa8) + 1;
        uVar8 = FUN_7ffe9b5043c0(aiStack_28,0);
        if (lVar6 != 0) {
          if (*(int *)(lVar6 + 0x18) == 0) {
            FUN_7ffe9996d790();
            pcVar1 = (code *)swi(3);
            bVar12 = (*pcVar1)();
            return bVar12;
          }
          *(undefined8 *)(lVar6 + 0x20) = uVar8;
          il2cpp_write_barrier_0();
          if (lVar5 != 0) {
            FUN_7ffe9a502860(lVar5,0xe,lVar6);
            return 0;
          }
        }
      }
    }
    else {
      lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
      if (lVar6 != 0) {
        uVar9 = 1;
        cVar2 = FUN_7ffe9a601aa0(lVar6,1,0);
        if (cVar2 == '\0') {
          if (*(longlong *)(thisObject + 0xe0) != 0) {
            cVar2 = FUN_7ffe9a570530(*(longlong *)(thisObject + 0xe0),*(undefined4 *)(lVar5 + 0x18),
                                     5,0);
            if (cVar2 == '\0') {
              uVar10 = 0;
              *(undefined4 *)(thisObject + 0xac) = 0x41200000;
              bVar12 = 1;
              uVar11 = uVar10;
              if (isAutoUse == 0) {
                lVar6 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x48) == 0)) goto LAB_7ffe99d02407;
                cVar2 = FUN_7ffe9a349850(*(longlong *)(lVar6 + 0x48),0);
                bVar12 = 1;
                uVar11 = 0;
                if (cVar2 == '\0') {
                  bVar12 = 0;
                  *(undefined4 *)(thisObject + 0xac) = 0x40400000;
                  uVar11 = uVar10;
                }
              }
              else {
                plVar7 = *(longlong **)(thisObject + 0xd8);
                if ((plVar7 == (longlong *)0x0) ||
                   (thisObject_00 =
                         (undefined *)
                         (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220)),
                   thisObject_00 == (undefined *)0x0)) goto LAB_7ffe99d02407;
                plVar7 = (longlong *)
                         GemCartBufferManager_GetGemCartBuffer(thisObject_00,0x20,(undefined *)0x0);
                if ((plVar7 != (longlong *)0x0) &&
                   (iVar3 = GemCartBufferBase_GetValue
                                      ((undefined *)plVar7,(undefined *)0x2,(undefined *)0x0),
                   iVar3 != 0)) {
                  uVar9 = 0;
                  (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
                  uVar11 = 1;
                  *(float *)(thisObject + 0xac) =
                       *(float *)(thisObject + 0xac) + *(float *)(thisObject + 0xac);
                }
              }
              if (*(longlong *)(thisObject + 0xa0) != 0) {
                cVar2 = FUN_7ffe9ad24db0(*(longlong *)(thisObject + 0xa0),
                                         *(undefined4 *)(lVar5 + 0x18),_DAT_7ffe9c96a130);
                lVar6 = *(longlong *)(thisObject + 0xe0);
                if (cVar2 == '\0') {
                  if (lVar6 != 0) {
                    cVar2 = FUN_7ffe9a570a00(lVar6,*(undefined4 *)(lVar5 + 0x18),uVar9,0);
                    if (cVar2 == '\0') {
                      return 1;
                    }
                    FUN_7ffe9bb63de0(*(undefined8 *)(thisObject + 0x90),
                                     *(undefined4 *)(lVar5 + 0x18),uVar11,0);
                    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c950390);
                    uVar9 = *(undefined4 *)(lVar5 + 0x18);
                    uVar8 = func_0x7ffe99940040(_DAT_7ffe9c94ff20);
                    FUN_7ffe99f7ca00(uVar8,uVar9,isAutoUse,0);
                    if (lVar6 != 0) {
                      uVar4 = FUN_7ffe9aac4850(lVar6,uVar8,0);
                      uVar9 = *(undefined4 *)(lVar5 + 0x18);
                      *(undefined4 *)(lVar5 + 0x1c) = uVar4;
                      lVar6 = *(longlong *)(thisObject + 0xa0);
                      uVar8 = func_0x7ffe99940040(_DAT_7ffe9c9380b0);
                      FUN_7ffe9af13ca0(uVar8,lVar5,_DAT_7ffe9c95d3c8,0);
                      if (lVar6 != 0) {
                        FUN_7ffe9ad4d2a0(lVar6,uVar9,uVar8);
                        MainPlayer_CalcItemDelay
                                  (thisObject,*(float *)(thisObject + 0xac),bVar12,(undefined *)0x0)
                        ;
                        return 1;
                      }
                    }
                  }
                }
                else if (lVar6 != 0) {
                  FUN_7ffe9a573d70(lVar6,*(undefined4 *)(lVar5 + 0x18),0);
                  return 0;
                }
              }
            }
            else if (*(longlong *)(thisObject + 0xe0) != 0) {
              bVar12 = FUN_7ffe9a573210(*(longlong *)(thisObject + 0xe0),
                                        *(undefined4 *)(lVar5 + 0x18),1,0);
              return bVar12;
            }
          }
        }
        else {
          lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
          if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x188) != 0)) {
            FUN_7ffe9a502810(*(longlong *)(lVar5 + 0x188),0x2d);
            return 0;
          }
        }
      }
    }
  }
LAB_7ffe99d02407:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar12 = (*pcVar1)();
  return bVar12;
}

