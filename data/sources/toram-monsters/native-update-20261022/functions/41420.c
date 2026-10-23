
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte FieldScriptManager__OnBossMenuCommand_d__263_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  undefined *self_00;
  code *pcVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  byte bVar6;
  short sVar7;
  int iVar8;
  undefined8 *puVar9;
  longlong lVar10;
  undefined8 uVar11;
  longlong *plVar12;
  int iVar13;
  undefined4 uVar14;
  uint uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  bool bStackX_8;
  short sStackX_18;
  undefined4 uStackX_20;
  undefined8 in_stack_ffffffffffffff80;
  undefined8 uStack_68;
  undefined8 uStack_58;
  undefined4 uStack_50;
  
  if (DAT_7ffe9cae0649 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949850);
    FUN_7ffe9996d590(&DAT_7ffe9c9499d0);
    FUN_7ffe9996d590(&DAT_7ffe9c967568);
    FUN_7ffe9996d590(&DAT_7ffe9c9677d0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    DAT_7ffe9cae0649 = '\x01';
  }
  iVar13 = *(int *)(self + 0x10);
  lVar1 = *(longlong *)(self + 0x20);
  if (iVar13 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar1 == 0) goto LAB_7ffe9aa2f0f7;
    if (*(int *)(lVar1 + 0xdc) == 0) {
      FUN_7ffe9aa10230(lVar1);
    }
    bVar6 = 0;
    self[0x2c] = *(undefined1 *)(lVar1 + 0xe2);
    self_00 = *(undefined **)(lVar1 + 0x40);
    *(undefined1 *)(lVar1 + 0xe2) = 2;
    bStackX_8 = false;
    if (self_00 == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
    if (*(int *)(self_00 + 0x18) < 0xf) {
      if (*(int *)(self_00 + 0x18) < 0xe) {
        sVar7 = FieldScriptLoader_ReadShort(self_00,(undefined *)0x0);
        iVar13 = (int)sVar7;
      }
      else {
        iVar13 = FieldScriptLoader_ReadInt(self_00,(undefined *)0x0);
      }
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      bVar3 = FieldScriptLoader_ReadByte(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
      uVar15 = (uint)bVar3;
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7ffe9aa2f0f7;
      puVar9 = (undefined8 *)FUN_7ffe9a9fc760(&uStack_58,*(longlong *)(lVar1 + 0x40),0);
      uVar16 = (undefined4)*puVar9;
      uVar17 = (undefined4)((ulonglong)*puVar9 >> 0x20);
      uStackX_20 = *(undefined4 *)(puVar9 + 1);
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      sStackX_18 = FieldScriptLoader_ReadShort(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      FieldScriptLoader_ReadShort(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
      uStack_68 = FUN_7ffe9aa10da0(lVar1);
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      iVar8 = FieldScriptLoader_ReadInt(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
    }
    else {
      bVar3 = FieldScriptLoader_ReadByte(self_00,(undefined *)0x0);
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      FieldScriptLoader_ReadByte(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      iVar13 = FieldScriptLoader_ReadInt(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      bVar4 = FieldScriptLoader_ReadByte(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
      uVar15 = (uint)bVar4;
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7ffe9aa2f0f7;
      puVar9 = (undefined8 *)FUN_7ffe9a9fc760(&uStack_58,*(longlong *)(lVar1 + 0x40),0);
      uVar16 = (undefined4)*puVar9;
      uVar17 = (undefined4)((ulonglong)*puVar9 >> 0x20);
      uStackX_20 = *(undefined4 *)(puVar9 + 1);
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      sStackX_18 = FieldScriptLoader_ReadShort(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      FieldScriptLoader_ReadShort(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
      uStack_68 = FUN_7ffe9aa10da0(lVar1);
      if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
      iVar8 = FieldScriptLoader_ReadInt(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
      if (0xe < bVar3) {
        if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
        bVar6 = FieldScriptLoader_ReadByte(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
        if (0xf < bVar3) {
          if (*(undefined **)(lVar1 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa2f0f7;
          bVar3 = FieldScriptLoader_ReadByte(*(undefined **)(lVar1 + 0x40),(undefined *)0x0);
          bStackX_8 = bVar3 != 0;
        }
      }
    }
    lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (lVar10 == 0) goto LAB_7ffe9aa2f0f7;
    plVar12 = *(longlong **)(lVar10 + 0x28);
    if (plVar12 == (longlong *)0x0) {
LAB_7ffe9aa2eb4d:
      lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
      if (lVar10 == 0) goto LAB_7ffe9aa2f0f7;
      plVar12 = *(longlong **)(lVar10 + 0x28);
      uVar14 = 0;
      if (plVar12 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c949850 + 0x130) <= *(byte *)(*plVar12 + 0x130)) &&
           (uVar14 = 0,
           *(longlong *)
            (*(longlong *)(*plVar12 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c949850 + 0x130) * 8) == _DAT_7ffe9c949850)) {
          if ((int)plVar12[7] != iVar13) {
            func_0x7ffe9a5c8f60(plVar12,0);
          }
          uVar14 = *(undefined4 *)((longlong)plVar12 + 0xa4);
        }
      }
    }
    else {
      if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7ffe9c9499d0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar12 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9499d0 + 0x130) * 8
           ) != _DAT_7ffe9c9499d0)) goto LAB_7ffe9aa2eb4d;
      if ((int)plVar12[7] != iVar13) {
        func_0x7ffe9a5ca1e0(plVar12,0);
      }
      uVar14 = *(undefined4 *)((longlong)plVar12 + 0xac);
    }
    *(undefined2 *)(self + 0x2d) = 0;
    if ((uVar15 == *(uint *)(lVar1 + 200)) && (iVar13 == *(int *)(lVar1 + 0xc4))) {
      plVar12 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if (plVar12 == (longlong *)0x0) goto LAB_7ffe9aa2f0f7;
      (**(code **)(*plVar12 + 0x278))(plVar12,0x7a,*(undefined8 *)(*plVar12 + 0x280));
      lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if ((lVar10 == 0) || (lVar10 = FUN_7ffe9a29dca0(lVar10,0), lVar10 == 0))
      goto LAB_7ffe9aa2f0f7;
      uVar11 = FUN_7ffe9ab9c3a0(lVar10,_DAT_7ffe9c967568);
      *(undefined8 *)(self + 0x30) = uVar11;
      il2cpp_write_barrier_0();
      if (*(longlong *)(self + 0x30) == 0) goto LAB_7ffe9aa2f0f7;
      uStack_50 = uStackX_20;
      uStack_58 = CONCAT44(uVar17,uVar16);
      FUN_7ffe99af35c0(*(longlong *)(self + 0x30),iVar13,uVar15,&uStack_58,(float)(int)sStackX_18,
                       uStack_68,iVar8,uVar14,1,_DAT_7ffe9c8f1820,bVar6,
                       CONCAT71((int7)((ulonglong)in_stack_ffffffffffffff80 >> 8),
                                ~*(byte *)(lVar1 + 0xcc)) & 0xffffffffffffff01,
                       *(undefined8 *)(lVar1 + 0xd0),0);
      goto LAB_7ffe9aa2ecdd;
    }
    plVar12 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
    if (plVar12 == (longlong *)0x0) goto LAB_7ffe9aa2f0f7;
    (**(code **)(*plVar12 + 0x278))(plVar12,0x40,*(undefined8 *)(*plVar12 + 0x280));
    lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
    if ((lVar10 == 0) || (lVar10 = FUN_7ffe9a29dca0(lVar10,0), lVar10 == 0)) goto LAB_7ffe9aa2f0f7;
    uVar11 = FUN_7ffe9ab9c3a0(lVar10,_DAT_7ffe9c9677d0);
    *(undefined8 *)(self + 0x38) = uVar11;
    il2cpp_write_barrier_0();
    if (*(longlong *)(self + 0x38) == 0) goto LAB_7ffe9aa2f0f7;
    uStack_50 = uStackX_20;
    uStack_58 = CONCAT44(uVar17,uVar16);
    FUN_7ffe99c7f9e0(*(longlong *)(self + 0x38),iVar13,uVar15,&uStack_58,(float)(int)sStackX_18,
                     uStack_68,iVar8,uVar14,1,_DAT_7ffe9c8f1820,bVar6,*(undefined8 *)(lVar1 + 0xd0),
                     bStackX_8,0);
LAB_7ffe9aa2ef0f:
    uVar11 = *(undefined8 *)(self + 0x38);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar5 = FUN_7ffe9bda2160(uVar11,0,0);
    if (cVar5 != '\0') {
      lVar10 = *(longlong *)(self + 0x38);
      if (lVar10 == 0) goto LAB_7ffe9aa2f0f7;
      if (*(char *)(lVar10 + 0x1d9) == '\0') {
        self[0x2d] = *(undefined1 *)(lVar10 + 0x1d8);
        self[0x2e] = *(undefined1 *)(lVar10 + 0x210);
        if (((lVar1 == 0) || (*(longlong *)(lVar1 + 0x20) == 0)) ||
           (plVar12 = (longlong *)FUN_7ffe9a480070(*(longlong *)(lVar1 + 0x20),0),
           plVar12 == (longlong *)0x0)) goto LAB_7ffe9aa2f0f7;
        cVar5 = (**(code **)(*plVar12 + 0x248))(plVar12,*(undefined8 *)(*plVar12 + 0x250));
        if (cVar5 != '\0') {
          plVar12 = *(longlong **)(self + 0x38);
          if (plVar12 == (longlong *)0x0) goto LAB_7ffe9aa2f0f7;
          (**(code **)(*plVar12 + 0x188))(plVar12,*(undefined8 *)(*plVar12 + 400));
        }
        if (self[0x2d] == '\0') {
          *(undefined8 *)(self + 0x18) = 0;
          il2cpp_write_barrier_0();
          *(undefined4 *)(self + 0x10) = 2;
          return 1;
        }
      }
    }
    *(undefined8 *)(self + 0x38) = 0;
  }
  else {
    if (iVar13 != 1) {
      if (iVar13 != 2) {
        return 0;
      }
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      goto LAB_7ffe9aa2ef0f;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7ffe9aa2ecdd:
    uVar11 = *(undefined8 *)(self + 0x30);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar5 = FUN_7ffe9bda2160(uVar11,0,0);
    if (cVar5 != '\0') {
      lVar10 = *(longlong *)(self + 0x30);
      if (lVar10 == 0) goto LAB_7ffe9aa2f0f7;
      if (*(char *)(lVar10 + 0x1e9) == '\0') {
        cVar5 = *(char *)(lVar10 + 0x1e8);
        self[0x2d] = cVar5;
        self[0x2e] = *(undefined1 *)(lVar10 + 0x220);
        if (cVar5 == '\0') {
          if (((lVar1 != 0) && (*(longlong *)(lVar1 + 0x20) != 0)) &&
             (plVar12 = (longlong *)FUN_7ffe9a480070(*(longlong *)(lVar1 + 0x20),0),
             plVar12 != (longlong *)0x0)) {
            cVar5 = (**(code **)(*plVar12 + 0x248))(plVar12,*(undefined8 *)(*plVar12 + 0x250));
            if (cVar5 != '\0') {
              plVar12 = *(longlong **)(self + 0x30);
              if (plVar12 == (longlong *)0x0) goto LAB_7ffe9aa2f0f7;
              (**(code **)(*plVar12 + 0x188))(plVar12,*(undefined8 *)(*plVar12 + 400));
            }
            *(undefined8 *)(self + 0x18) = 0;
            il2cpp_write_barrier_0();
            *(undefined4 *)(self + 0x10) = 1;
            return 1;
          }
          goto LAB_7ffe9aa2f0f7;
        }
      }
    }
    *(undefined8 *)(self + 0x30) = 0;
  }
  il2cpp_write_barrier_0();
  if (lVar1 != 0) {
    *(undefined *)(lVar1 + 0xe2) = self[0x2c];
    FUN_7ffe9aa19880(lVar1,*(undefined4 *)(self + 0x28),0);
    if ((*(longlong *)(lVar1 + 0x20) != 0) &&
       (plVar12 = (longlong *)FUN_7ffe9a480070(*(longlong *)(lVar1 + 0x20),0),
       plVar12 != (longlong *)0x0)) {
      cVar5 = (**(code **)(*plVar12 + 0x248))(plVar12,*(undefined8 *)(*plVar12 + 0x250));
      if (cVar5 != '\0') {
        return 0;
      }
      plVar12 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if (plVar12 != (longlong *)0x0) {
        (**(code **)(*plVar12 + 0x278))(plVar12,2,*(undefined8 *)(*plVar12 + 0x280));
        if (self[0x2d] == '\0') {
          plVar12 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
          if (plVar12 != (longlong *)0x0) {
            (**(code **)(*plVar12 + 0x248))(plVar12,0,5,*(undefined8 *)(*plVar12 + 0x250));
            return 0;
          }
        }
        else {
          if (self[0x2e] == '\0') {
            return 0;
          }
          plVar12 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
          if (plVar12 != (longlong *)0x0) {
            (**(code **)(*plVar12 + 0x278))(plVar12,0x5d,*(undefined8 *)(*plVar12 + 0x280));
            return 0;
          }
        }
      }
    }
  }
LAB_7ffe9aa2f0f7:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar6 = (*pcVar2)();
  return bVar6;
}

