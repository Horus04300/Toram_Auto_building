
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuardActionManager_CalcGuard
              (undefined *self,int damage,undefined *guardPower,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong *plVar3;
  longlong lVar4;
  int iVar5;
  float fVar6;
  
  if (DAT_7ffe9cadfebb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9cadfebb = '\x01';
  }
  plVar3 = *(longlong **)(self + 0x28);
  if (plVar3 == (longlong *)0x0) {
LAB_7ffe9a8f6c39:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    iVar2 = (*pcVar1)();
    return iVar2;
  }
  plVar3 = (longlong *)(**(code **)(*plVar3 + 0x298))(plVar3,*(undefined8 *)(*plVar3 + 0x2a0));
  if (plVar3 == (longlong *)0x0) goto LAB_7ffe9a8f6c39;
  lVar4 = (**(code **)(*plVar3 + 0x198))(plVar3,*(undefined8 *)(*plVar3 + 0x1a0));
  if (lVar4 == 0) goto LAB_7ffe9a8f6c39;
  iVar2 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar4);
  iVar2 = (int)((_DAT_7ffe9c049b18 - (float)(iVar2 - damage) / (float)iVar2) * _DAT_7ffe9c049cfc *
               _DAT_7ffe9c049cfc);
  if (*(short *)(self + 0x82) != 0x10b) {
    if (DAT_7ffe9cadfea9 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c9540a0);
      DAT_7ffe9cadfea9 = '\x01';
    }
    lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c9540a0);
    if ((lVar4 == 0) || (*(longlong *)(lVar4 + 0x28) == 0)) goto LAB_7ffe9a8f6c39;
    if ((*(int *)(*(longlong *)(lVar4 + 0x28) + 0x48) != 0) || (*(float *)(self + 0x4c) <= 0.0))
    goto LAB_7ffe9a8f6bb4;
  }
  iVar2 = iVar2 / 2;
LAB_7ffe9a8f6bb4:
  iVar5 = *(int *)(self + 0x88);
  if (*(int *)(self + 0x88) <= iVar2) {
    iVar5 = iVar2;
  }
  *(int *)(self + 0x88) = iVar5;
  *(int *)guardPower = (int)*(float *)(self + 0x74);
  iVar2 = (int)*(float *)(self + 0x74);
  if (10000 < iVar2) {
    iVar2 = 10000;
  }
  fVar6 = (float)iVar2 / _DAT_7ffe9c049ec0;
  if ((*(short *)(self + 0x82) == 0x6c) || (*(short *)(self + 0x82) == 0x2ca)) {
    fVar6 = fVar6 * _DAT_7ffe9c049b4c;
  }
  iVar5 = damage - (int)((float)damage * fVar6);
  iVar2 = 0;
  if (-1 < iVar5) {
    iVar2 = iVar5;
  }
  return iVar2;
}

