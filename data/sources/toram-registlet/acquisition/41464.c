
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte _OnChallengeDungeon2MenuCommand_d__292_MoveNext(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  undefined4 uVar2;
  longlong lVar3;
  code *pcVar4;
  byte bVar5;
  byte bVar6;
  byte roomId;
  char cVar7;
  short sVar8;
  int fieldId;
  int level;
  undefined8 *puVar9;
  undefined *emergency;
  longlong *plVar10;
  longlong lVar11;
  undefined8 uVar12;
  undefined8 uStack_58;
  undefined4 uStack_50;
  
  if (DAT_7ffe9cae064b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f0f68);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    DAT_7ffe9cae064b = '\x01';
  }
  lVar3 = *(longlong *)(self + 0x20);
  if (*(int *)(self + 0x10) == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if ((lVar3 == 0) || (*(longlong *)(lVar3 + 0x40) == 0)) goto LAB_7ffe9aa2fea3;
    bVar5 = FUN_7ffe9a9fc190(*(longlong *)(lVar3 + 0x40),0);
    if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe9aa2fea3;
    bVar6 = FUN_7ffe9a9fc190(*(longlong *)(lVar3 + 0x40),0);
    if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe9aa2fea3;
    fieldId = FUN_7ffe9a9fc4e0(*(longlong *)(lVar3 + 0x40),bVar6 & 1,0);
    if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe9aa2fea3;
    roomId = FUN_7ffe9a9fc140(*(longlong *)(lVar3 + 0x40),(bVar6 & 2) != 0,0);
    if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe9aa2fea3;
    level = FUN_7ffe9a9fc4e0(*(longlong *)(lVar3 + 0x40),(bVar6 & 4) != 0,0);
    if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe9aa2fea3;
    puVar9 = (undefined8 *)FUN_7ffe9a9fc860(&uStack_58,*(longlong *)(lVar3 + 0x40),bVar6 & 0x38,0);
    uVar1 = *puVar9;
    uVar2 = *(undefined4 *)(puVar9 + 1);
    if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe9aa2fea3;
    sVar8 = FUN_7ffe9a9fc5b0(*(longlong *)(lVar3 + 0x40),(bVar6 & 0x40) != 0,0);
    if (*(longlong *)(lVar3 + 0x40) == 0) goto LAB_7ffe9aa2fea3;
    FUN_7ffe9a9fc5b0(*(longlong *)(lVar3 + 0x40),(bVar6 & 0x80) != 0,0);
    emergency = (undefined *)0x0;
    if (0xd < bVar5) {
      emergency = (undefined *)FUN_7ffe9aa10da0(lVar3,0);
    }
    if (*(int *)(lVar3 + 0xdc) == 0) {
      FUN_7ffe9aa10230(lVar3,1);
    }
    self[0x2c] = *(undefined1 *)(lVar3 + 0xe2);
    *(undefined1 *)(lVar3 + 0xe2) = 2;
    plVar10 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
    if (plVar10 == (longlong *)0x0) goto LAB_7ffe9aa2fea3;
    (**(code **)(*plVar10 + 0x278))(plVar10,0x8c,*(undefined8 *)(*plVar10 + 0x280));
    lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
    if ((lVar11 == 0) || (lVar11 = FUN_7ffe9a29dca0(lVar11,0), lVar11 == 0)) goto LAB_7ffe9aa2fea3;
    uVar12 = FUN_7ffe9ab9c3a0(lVar11,_DAT_7ffe9c8f0f68);
    *(undefined8 *)(self + 0x30) = uVar12;
    il2cpp_write_barrier_0();
    if (*(undefined **)(self + 0x30) == (undefined *)0x0) goto LAB_7ffe9aa2fea3;
    uStack_58 = uVar1;
    uStack_50 = uVar2;
    UITreasureHuntEnterManager_Initialize
              (*(undefined **)(self + 0x30),fieldId,roomId,level,(undefined *)&uStack_58,
               (float)(int)sVar8,emergency,(undefined *)0x0);
    *(undefined2 *)(self + 0x38) = 0;
  }
  else {
    if (*(int *)(self + 0x10) != 1) {
      return 0;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
  }
  uVar1 = *(undefined8 *)(self + 0x30);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar7 = FUN_7ffe9bda2160(uVar1,0,0);
  if (cVar7 != '\0') {
    lVar11 = *(longlong *)(self + 0x30);
    if (lVar11 == 0) goto LAB_7ffe9aa2fea3;
    if (*(char *)(lVar11 + 0x149) == '\0') {
      cVar7 = *(char *)(lVar11 + 0x148);
      self[0x38] = cVar7;
      self[0x39] = *(undefined1 *)(lVar11 + 0x14a);
      if (cVar7 == '\0') {
        if (((lVar3 != 0) && (*(longlong *)(lVar3 + 0x20) != 0)) &&
           (plVar10 = (longlong *)FUN_7ffe9a480070(*(longlong *)(lVar3 + 0x20),0),
           plVar10 != (longlong *)0x0)) {
          cVar7 = (**(code **)(*plVar10 + 0x248))(plVar10,*(undefined8 *)(*plVar10 + 0x250));
          if (cVar7 != '\0') {
            plVar10 = *(longlong **)(self + 0x30);
            if (plVar10 == (longlong *)0x0) goto LAB_7ffe9aa2fea3;
            (**(code **)(*plVar10 + 0x188))(plVar10,*(undefined8 *)(*plVar10 + 400));
          }
          *(undefined8 *)(self + 0x18) = 0;
          il2cpp_write_barrier_0();
          *(undefined4 *)(self + 0x10) = 1;
          return 1;
        }
        goto LAB_7ffe9aa2fea3;
      }
    }
  }
  if (lVar3 == 0) {
LAB_7ffe9aa2fea3:
    FUN_7ffe9996d7a0();
    pcVar4 = (code *)swi(3);
    bVar5 = (*pcVar4)();
    return bVar5;
  }
  *(undefined *)(lVar3 + 0xe2) = self[0x2c];
  FUN_7ffe9aa19880(lVar3,*(undefined4 *)(self + 0x28),0);
  if (self[0x39] == '\0') {
    if ((*(longlong *)(lVar3 + 0x20) == 0) ||
       (plVar10 = (longlong *)FUN_7ffe9a480070(*(longlong *)(lVar3 + 0x20),0),
       plVar10 == (longlong *)0x0)) goto LAB_7ffe9aa2fea3;
    cVar7 = (**(code **)(*plVar10 + 0x248))(plVar10,*(undefined8 *)(*plVar10 + 0x250));
    if (cVar7 == '\0') {
      plVar10 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if (plVar10 == (longlong *)0x0) goto LAB_7ffe9aa2fea3;
      (**(code **)(*plVar10 + 0x278))(plVar10,2,*(undefined8 *)(*plVar10 + 0x280));
      if (self[0x38] == '\0') {
        plVar10 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
        if (plVar10 == (longlong *)0x0) goto LAB_7ffe9aa2fea3;
        (**(code **)(*plVar10 + 0x248))(plVar10,0,5,*(undefined8 *)(*plVar10 + 0x250));
      }
    }
  }
  return 0;
}

