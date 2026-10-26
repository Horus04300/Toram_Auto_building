
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_EquipBuffAttack
               (undefined *self,int type,undefined *mobAction,undefined *methodInfo)

{
  undefined4 uVar1;
  undefined4 uVar2;
  code *pcVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined *action;
  undefined8 uVar7;
  undefined8 uVar8;
  longlong lVar9;
  undefined8 *puVar10;
  float *pfVar11;
  int iVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  undefined8 uStack_e8;
  undefined4 uStack_e0;
  undefined8 uStack_d8;
  undefined4 uStack_d0;
  float fStack_c8;
  float fStack_c4;
  float fStack_c0;
  float fStack_bc;
  
  if (DAT_7ffe9caddd09 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    DAT_7ffe9caddd09 = '\x01';
  }
  iVar12 = 0;
  if (type == 0x99) {
    uVar7 = 0xb;
    iVar12 = 0x1a8;
  }
  else if (type == 0x9a) {
    uVar7 = 0xc;
    iVar12 = 0x1a9;
  }
  else {
    if (type != 0x9b) {
      return;
    }
    uVar7 = 10;
  }
  action = (undefined *)func_0x7ffe9a7fb2b0(uVar7,0);
  if ((action == (undefined *)0x0) ||
     (FUN_7ffe9a8fe290(action,*(undefined8 *)(self + 0x28),1,0), mobAction == (undefined *)0x0))
  goto LAB_7ffe9a45c424;
  uVar7 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAction);
  uVar8 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,mobAction);
  (**(code **)(*(longlong *)self + 0x2f8))
            (self,uVar7,uVar8,action,*(undefined8 *)(*(longlong *)self + 0x300));
  uVar7 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAction);
  uVar8 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,mobAction);
  (**(code **)(*(longlong *)self + 0x338))
            (self,uVar7,uVar8,action,*(undefined8 *)(*(longlong *)self + 0x340));
  if (iVar12 != 0) {
    uVar7 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c9724e0,mobAction);
    lVar9 = FUN_7ffe99ab3eb0(uVar7,0);
    if (lVar9 == 0) goto LAB_7ffe9a45c424;
    puVar10 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_d8,lVar9,0);
    uVar7 = *puVar10;
    uVar1 = *(undefined4 *)(puVar10 + 1);
    lVar9 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c9724e0,mobAction);
    if (lVar9 == 0) goto LAB_7ffe9a45c424;
    puVar10 = (undefined8 *)FUN_7ffe9bdbf190(&uStack_d8,lVar9,0);
    uStack_e8 = *puVar10;
    uStack_e0 = *(undefined4 *)(puVar10 + 1);
    pfVar11 = (float *)FUN_7ffe9bda38a0(&fStack_c8,&uStack_e8,0);
    fVar13 = *pfVar11;
    fVar15 = pfVar11[1];
    fVar14 = pfVar11[2];
    fVar16 = pfVar11[3];
    fStack_c8 = fVar13;
    fStack_c4 = fVar15;
    fStack_c0 = fVar14;
    fStack_bc = fVar16;
    lVar9 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c9724e0);
    if (lVar9 == 0) goto LAB_7ffe9a45c424;
    puVar10 = (undefined8 *)FUN_7ffe9bdbf520(&uStack_d8,lVar9);
    uVar8 = *puVar10;
    uVar2 = *(undefined4 *)(puVar10 + 1);
    if (type == 0x9a) {
      if (DAT_7ffe9cad9c13 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
        DAT_7ffe9cad9c13 = '\x01';
      }
      uStack_e8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x3c);
      uStack_e0 = *(undefined4 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x44);
      pfVar11 = (float *)FUN_7ffe9bda2ff0(&uStack_d8,_DAT_7ffe9c04a0b0,&uStack_e8,0);
      fVar14 = *pfVar11;
      fVar4 = pfVar11[1];
      fVar5 = pfVar11[2];
      fVar6 = pfVar11[3];
      fVar13 = (fStack_bc * fVar14 + fStack_c8 * fVar6 + fStack_c4 * fVar5) - fStack_c0 * fVar4;
      fVar15 = (fStack_c4 * fVar6 + fStack_bc * fVar4 + fStack_c0 * fVar14) - fStack_c8 * fVar5;
      fVar16 = ((fStack_bc * fVar6 - fStack_c8 * fVar14) - fStack_c4 * fVar4) - fStack_c0 * fVar5;
      fVar14 = (fStack_bc * fVar5 + fStack_c0 * fVar6 + fStack_c8 * fVar4) - fStack_c4 * fVar14;
      fStack_c8 = fVar13;
      fStack_c4 = fVar15;
      fStack_c0 = fVar14;
      fStack_bc = fVar16;
    }
    if ((*(longlong *)(self + 0x88) == 0) ||
       (lVar9 = *(longlong *)(*(longlong *)(self + 0x88) + 0x58), lVar9 == 0))
    goto LAB_7ffe9a45c424;
    uStack_e8 = uVar8;
    uStack_e0 = uVar2;
    uStack_d8 = uVar7;
    uStack_d0 = uVar1;
    fStack_c8 = fVar13;
    fStack_c4 = fVar15;
    fStack_c0 = fVar14;
    fStack_bc = fVar16;
    FUN_7ffe9a9b64e0(lVar9,iVar12,0,&uStack_d8,&fStack_c8,&uStack_e8,7,0);
  }
  lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
  if (lVar9 != 0) {
    FUN_7ffe9a89e600(lVar9,action);
    PlayerBattleManager_AddReconnectionActionEnd(self,action,(undefined *)0x0);
    return;
  }
LAB_7ffe9a45c424:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

