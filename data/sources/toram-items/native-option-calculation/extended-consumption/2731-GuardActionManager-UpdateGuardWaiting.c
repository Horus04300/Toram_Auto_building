
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuardActionManager_UpdateGuardWaiting(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  longlong *plVar6;
  float fVar7;
  float fVar8;
  
  if (DAT_7ffe9cadfebf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    DAT_7ffe9cadfebf = '\x01';
  }
  lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
  if (lVar5 == 0) {
LAB_7ffe9a8fb01c:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (((*(char *)(lVar5 + 0x22) != '\0') &&
      (bVar2 = GuardActionManager_CheckGuardEquip(self,(undefined *)0x0), bVar2 != 0)) &&
     (self[0x80] == '\0')) {
    plVar6 = *(longlong **)(self + 0x28);
    if ((plVar6 == (longlong *)0x0) ||
       (lVar5 = (**(code **)(*plVar6 + 0x2a8))(plVar6,*(undefined8 *)(*plVar6 + 0x2b0)), lVar5 == 0)
       ) goto LAB_7ffe9a8fb01c;
    cVar3 = FUN_7ffe9a4daa60(lVar5);
    if ((cVar3 == '\0') &&
       (bVar2 = GuardActionManager_CheckPairOfShieldsGuard(self,(undefined *)0x0), bVar2 == 0)) {
      fVar8 = *(float *)(self + 0x84);
      if (0.0 < fVar8) {
        fVar7 = (float)FUN_7ffe9bda7ce0(0);
        fVar8 = fVar8 - fVar7;
        *(float *)(self + 0x84) = fVar8;
        if (fVar8 <= 0.0) {
          *(undefined4 *)(self + 0x84) = 0;
        }
      }
      if (*(float *)(self + 0x54) <= 0.0) {
        plVar6 = *(longlong **)(self + 0x28);
        if ((plVar6 != (longlong *)0x0) &&
           (plVar6 = (longlong *)
                     (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
           plVar6 != (longlong *)0x0)) {
          lVar5 = (**(code **)(*plVar6 + 0x1a8))(plVar6,*(undefined8 *)(*plVar6 + 0x1b0));
          fVar8 = *(float *)(self + 0x74);
          if (lVar5 != 0) {
            iVar4 = FUN_7ffe99742ec0(0x21,_DAT_7ffe9c940d40,lVar5);
            fVar7 = *(float *)(self + 0x74);
            if ((int)fVar8 < iVar4) {
              iVar4 = FUN_7ffe99742ec0(0x22,_DAT_7ffe9c940d40,lVar5);
              fVar8 = (float)FUN_7ffe9bda7ce0(0);
              fVar7 = fVar8 * (float)iVar4 + fVar7;
              *(float *)(self + 0x74) = fVar7;
              iVar4 = FUN_7ffe99742ec0(0x21,_DAT_7ffe9c940d40,lVar5);
              if ((int)fVar7 < iVar4) {
                return;
              }
              iVar4 = FUN_7ffe99742ec0(0x21,_DAT_7ffe9c940d40,lVar5);
              *(float *)(self + 0x74) = (float)iVar4;
              return;
            }
            if (9999 < (int)fVar7) {
              return;
            }
            iVar4 = FUN_7ffe99742ec0(0x22,_DAT_7ffe9c940d40,lVar5);
            fVar8 = (float)FUN_7ffe9bda7ce0(0);
            fVar7 = fVar8 * (float)iVar4 * _DAT_7ffe9c049b40 + fVar7;
            *(float *)(self + 0x74) = fVar7;
            if ((int)fVar7 < 10000) {
              return;
            }
            *(undefined4 *)(self + 0x74) = 0x461c4000;
            return;
          }
        }
        goto LAB_7ffe9a8fb01c;
      }
    }
  }
  return;
}

