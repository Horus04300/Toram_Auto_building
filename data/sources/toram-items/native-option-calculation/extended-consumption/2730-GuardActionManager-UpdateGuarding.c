
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuardActionManager_UpdateGuarding(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  uint uVar8;
  float fVar9;
  float fVar10;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  float fStack_40;
  undefined8 uStack_38;
  float fStack_30;
  undefined4 uStack_2c;
  
  if (DAT_7ffe9cadfebe == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90aac0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    DAT_7ffe9cadfebe = '\x01';
  }
  if (self[0x80] != '\0') {
    if (DAT_7ffe9cadfea9 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c9540a0);
      DAT_7ffe9cadfea9 = '\x01';
    }
    lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c9540a0);
    if ((lVar4 == 0) || (*(longlong *)(lVar4 + 0x28) == 0)) goto LAB_7ffe9a8fb58a;
    if ((*(int *)(*(longlong *)(lVar4 + 0x28) + 0x48) == 0) && (self[0x70] == '\0')) {
      lVar4 = *(longlong *)(self + 0x38);
      lVar5 = FUN_7ffe9bd98960(self,0);
      if ((lVar5 == 0) || (lVar5 = FUN_7ffe9bd9b890(lVar5,0), lVar5 == 0)) {
LAB_7ffe9a8fb58a:
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      puVar6 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_38,lVar5,0);
      uStack_58 = *puVar6;
      uStack_50 = CONCAT44(uStack_50._4_4_,*(undefined4 *)(puVar6 + 1));
      lVar5 = FUN_7ffe9bd7a830(0);
      if ((lVar5 == 0) || (lVar5 = FUN_7ffe9bd98a10(lVar5,0), lVar5 == 0)) goto LAB_7ffe9a8fb58a;
      puVar6 = (undefined8 *)FUN_7ffe9bdbf190(&uStack_38,lVar5,0);
      uStack_38 = *puVar6;
      fStack_30 = *(float *)(puVar6 + 1);
      fStack_40 = (float)uStack_50 + fStack_30;
      uStack_48 = CONCAT44(uStack_58._4_4_ + (float)((ulonglong)uStack_38 >> 0x20),
                           (float)uStack_58 + (float)uStack_38);
      if (lVar4 == 0) goto LAB_7ffe9a8fb58a;
      uStack_38 = uStack_48;
      fStack_30 = fStack_40;
      FUN_7ffe99b1e890(lVar4,&uStack_38,0);
      if (self[0x8c] != '\0') {
        uVar1 = *(undefined4 *)(self + 0x58);
        if (DAT_7ffe9cad9cac == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
          DAT_7ffe9cad9cac = '\x01';
        }
        uStack_38 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
        fStack_30 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
        puVar6 = (undefined8 *)FUN_7ffe9bda2ff0(&uStack_48,uVar1,&uStack_38,0);
        uVar7 = *puVar6;
        uVar3 = puVar6[1];
        if (DAT_7ffe9cad9ca9 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
          DAT_7ffe9cad9ca9 = '\x01';
        }
        uStack_38 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x48);
        fStack_30 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x50);
        uStack_58 = uVar7;
        uStack_50 = uVar3;
        puVar6 = (undefined8 *)FUN_7ffe9bda42f0(&uStack_48,&uStack_58,&uStack_38,0);
        uVar7 = *puVar6;
        fVar10 = *(float *)(puVar6 + 1);
        lVar4 = FUN_7ffe9bd7a830(0);
        if ((lVar4 == 0) || (lVar4 = FUN_7ffe9bd98a10(lVar4,0), lVar4 == 0)) goto LAB_7ffe9a8fb58a;
        puVar6 = (undefined8 *)FUN_7ffe9bdbf190(&uStack_48,lVar4,0);
        uStack_38 = *puVar6;
        fStack_30 = *(float *)(puVar6 + 1);
        uStack_48 = uVar7;
        fStack_40 = fVar10;
        uVar8 = FUN_7ffe99a4ef70(&uStack_48,&uStack_38,0);
        if (_DAT_7ffe9c049e64 <= (float)(uVar8 & _DAT_7ffe9c049bf0)) {
          lVar4 = FUN_7ffe9bd98960(self,0);
          if ((lVar4 == 0) || (lVar4 = FUN_7ffe9bd9b890(lVar4,0), lVar4 == 0))
          goto LAB_7ffe9a8fb58a;
          puVar6 = (undefined8 *)FUN_7ffe9bdbf880(&uStack_38,lVar4,0);
          uStack_38 = *puVar6;
          fStack_30 = *(float *)(puVar6 + 1);
          uStack_2c = *(undefined4 *)((longlong)puVar6 + 0xc);
          puVar6 = (undefined8 *)FUN_7ffe9bda3580(&uStack_58,&uStack_38,0);
          fVar10 = _DAT_7ffe9c049d68;
          fStack_40 = *(float *)(puVar6 + 1) * _DAT_7ffe9c049d68;
          uStack_38 = CONCAT44((float)((ulonglong)*puVar6 >> 0x20) * _DAT_7ffe9c049d68,
                               (float)*puVar6 * _DAT_7ffe9c049d68);
          fStack_30 = fStack_40;
          puVar6 = (undefined8 *)func_0x7ffe9bda34a0(&uStack_48,&uStack_38,0);
          uStack_38 = *puVar6;
          fStack_30 = *(float *)(puVar6 + 1);
          *(int *)(self + 0x58) = (int)((ulonglong)uStack_38 >> 0x20);
          lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
          lVar5 = FUN_7ffe9bd98960(self,0);
          if ((lVar5 == 0) || (lVar5 = FUN_7ffe9bd9b890(lVar5,0), lVar5 == 0))
          goto LAB_7ffe9a8fb58a;
          puVar6 = (undefined8 *)FUN_7ffe9bdbf880(&uStack_38,lVar5,0);
          uStack_38 = *puVar6;
          fStack_30 = *(float *)(puVar6 + 1);
          uStack_2c = *(undefined4 *)((longlong)puVar6 + 0xc);
          puVar6 = (undefined8 *)FUN_7ffe9bda3580(&uStack_58,&uStack_38,0);
          fStack_40 = *(float *)(puVar6 + 1) * fVar10;
          uStack_38 = CONCAT44((float)((ulonglong)*puVar6 >> 0x20) * fVar10,(float)*puVar6 * fVar10)
          ;
          fStack_30 = fStack_40;
          puVar6 = (undefined8 *)func_0x7ffe9bda34a0(&uStack_48,&uStack_38,0);
          uStack_38 = *puVar6;
          uVar7 = FUN_7ffe997442c0(_DAT_7ffe9c90aac0);
          if (lVar4 == 0) goto LAB_7ffe9a8fb58a;
          func_0x7ffe9a8b5e80(lVar4,2,(int)(uStack_38._4_4_ * _DAT_7ffe9c049ce4),uVar7,0);
        }
      }
    }
    fVar10 = *(float *)(self + 0x4c);
    if (0.0 < fVar10) {
      fVar9 = (float)FUN_7ffe9bda7ce0(0);
      fVar10 = fVar10 - fVar9;
      *(float *)(self + 0x4c) = fVar10;
      if (fVar10 <= 0.0) {
        *(undefined4 *)(self + 0x4c) = 0;
      }
    }
  }
  return;
}

