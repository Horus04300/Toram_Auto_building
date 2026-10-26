
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AvoidActionManager_UpdateAvoidStack(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  longlong *plVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  if (DAT_7ffe9cadf5e1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    DAT_7ffe9cadf5e1 = '\x01';
  }
  lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
  if (lVar5 == 0) {
LAB_7ffe9a7d9541:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if ((*(char *)(lVar5 + 0x22) != '\0') &&
     (bVar2 = AvoidActionManager_CheckAvoidEquip(self,(undefined *)0x0), bVar2 != 0)) {
    plVar6 = *(longlong **)(self + 0x28);
    if ((plVar6 == (longlong *)0x0) ||
       (lVar5 = (**(code **)(*plVar6 + 0x2a8))(plVar6,*(undefined8 *)(*plVar6 + 0x2b0)), lVar5 == 0)
       ) goto LAB_7ffe9a7d9541;
    cVar3 = FUN_7ffe9a4daa60(lVar5,0xe);
    if (cVar3 == '\0') {
      plVar6 = *(longlong **)(self + 0x28);
      if (((plVar6 == (longlong *)0x0) ||
          (plVar6 = (longlong *)
                    (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
          plVar6 == (longlong *)0x0)) ||
         (lVar5 = (**(code **)(*plVar6 + 0x198))(plVar6,*(undefined8 *)(*plVar6 + 0x1a0)),
         lVar5 == 0)) goto LAB_7ffe9a7d9541;
      iVar4 = FUN_7ffe99742ec0(0x24,_DAT_7ffe9c940d40,lVar5);
      fVar8 = *(float *)(self + 0x54);
      fVar9 = (float)iVar4;
      if (fVar8 < fVar9) {
        iVar4 = AvoidActionManager_get_AvoidSpeed(self,(undefined *)0x0);
        fVar7 = (float)FUN_7ffe9bda7ce0(0);
        fVar8 = fVar7 * (float)iVar4 + fVar8;
        *(float *)(self + 0x54) = fVar8;
        if (fVar9 <= fVar8) {
          *(float *)(self + 0x54) = fVar9;
        }
      }
    }
  }
  return;
}

