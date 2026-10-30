
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte _WaitRoomData_d__87_MoveNext(undefined *self,undefined *methodInfo)

{
  float fVar1;
  int iVar2;
  longlong *plVar3;
  code *pcVar4;
  float fVar5;
  char cVar6;
  byte bVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  longlong *plVar12;
  undefined8 uVar13;
  float fVar14;
  undefined2 auStackX_8 [4];
  undefined4 auStackX_18 [2];
  
  if (DAT_7ffe9cadaba1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c92eda0);
    FUN_7ffe9996d590(&DAT_7ffe9c94b8b0);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c931fc8);
    FUN_7ffe9996d590(&DAT_7ffe9c954d60);
    FUN_7ffe9996d590(&DAT_7ffe9c956e00);
    FUN_7ffe9996d590(&DAT_7ffe9c954ef0);
    FUN_7ffe9996d590(&DAT_7ffe9c953578);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c917368);
    FUN_7ffe9996d590(&DAT_7ffe9c90aa28);
    FUN_7ffe9996d590(&DAT_7ffe9c9275f8);
    FUN_7ffe9996d590(&DAT_7ffe9c90e3f8);
    FUN_7ffe9996d590(&DAT_7ffe9c91ebe8);
    FUN_7ffe9996d590(&DAT_7ffe9c90e4c8);
    FUN_7ffe9996d590(&DAT_7ffe9c94bf48);
    FUN_7ffe9996d590(&DAT_7ffe9c9405c8);
    DAT_7ffe9cadaba1 = '\x01';
  }
  iVar2 = *(int *)(self + 0x10);
  plVar3 = *(longlong **)(self + 0x20);
  auStackX_8[0] = 0;
  if (iVar2 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7ffe99c6c0b7:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954d60);
    if (lVar8 == 0) goto LAB_7ffe99c6c509;
    cVar6 = FUN_7ffe9aae6120(lVar8,0xb7,0x6c,0);
    if (cVar6 == '\0') {
      lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954d60);
      if (lVar8 == 0) goto LAB_7ffe99c6c509;
      cVar6 = FUN_7ffe9aae7f50(lVar8,0xb7,0x6c,auStackX_8,0);
      if (cVar6 != '\0') {
        if ((plVar3 == (longlong *)0x0) || (plVar3[4] == 0)) {
LAB_7ffe99c6c524:
          FUN_7ffe9996d7a0();
          pcVar4 = (code *)swi(3);
          bVar7 = (*pcVar4)();
          return bVar7;
        }
        uVar11 = FUN_7ffe99a58320(plVar3[4],_DAT_7ffe9c90e4c8,0);
        if (plVar3[4] == 0) goto LAB_7ffe99c6c524;
        uVar10 = FUN_7ffe99a58320(plVar3[4],_DAT_7ffe9c90e3f8,0);
        auStackX_18[0] = CONCAT22(auStackX_18[0]._2_2_,auStackX_8[0]);
        uVar13 = func_0x7ffe9996c8e0(_DAT_7ffe9c94b8b0,auStackX_18);
        uVar10 = FUN_7ffe9b36a740(uVar10,uVar13,0);
        lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
        uVar13 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
        FUN_7ffe999e6880(uVar13,plVar3,*(undefined8 *)(*plVar3 + 400),0);
        if (lVar8 == 0) goto LAB_7ffe99c6c524;
        FUN_7ffe9a2c9c20(lVar8,uVar11,uVar10,uVar13,0);
        goto LAB_7ffe99c6c502;
      }
      if ((plVar3 == (longlong *)0x0) || (plVar3[0x3e] == 0)) goto LAB_7ffe99c6c509;
      if (*(char *)(plVar3[0x3e] + 0x28) != '\0') goto LAB_7ffe99c6c191;
      uVar11 = func_0x7ffe99940040(_DAT_7ffe9c90aa28);
      func_0x7ffe999c3920(uVar11,0);
      *(undefined8 *)(self + 0x28) = uVar11;
      il2cpp_write_barrier_0();
      lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c953578);
      if (lVar8 == 0) goto LAB_7ffe99c6c509;
      uVar11 = FUN_7ffe99a4a810(lVar8,0);
      uVar10 = FUN_7ffe9b366c90(_DAT_7ffe9c9405c8,uVar11,_DAT_7ffe9c91ebe8,uVar11,0);
      *(undefined8 *)(self + 0x30) = uVar10;
      il2cpp_write_barrier_0();
      uVar11 = FUN_7ffe9b3675b0(_DAT_7ffe9c9275f8,uVar11,0);
      *(undefined8 *)(self + 0x38) = uVar11;
      il2cpp_write_barrier_0();
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99c6c509;
      *(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 0;
      lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if ((lVar8 == 0) || (lVar8 = FUN_7ffe9a29e0d0(lVar8,0), lVar8 == 0)) goto LAB_7ffe99c6c509;
      FUN_7ffe99ce5f20(lVar8,1,0);
      lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
      uVar11 = *(undefined8 *)(self + 0x30);
      uVar10 = *(undefined8 *)(self + 0x28);
      uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
      FUN_7ffe9ac2ed50(uVar13,uVar10,_DAT_7ffe9c917368,0);
      if (lVar8 == 0) goto LAB_7ffe99c6c509;
      uVar11 = FUN_7ffe99ad0580(lVar8,uVar11,1,uVar13,0);
      uVar11 = FUN_7ffe9bd9f640(plVar3,uVar11,0);
      *(undefined8 *)(self + 0x18) = uVar11;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 2;
    }
    else {
      auStackX_18[0] = 0;
      uVar11 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,auStackX_18);
      *(undefined8 *)(self + 0x18) = uVar11;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 1;
    }
    bVar7 = 1;
  }
  else {
    if (iVar2 == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (plVar3 == (longlong *)0x0) goto LAB_7ffe99c6c509;
      fVar1 = *(float *)((longlong)plVar3 + 0x1ac);
      fVar14 = (float)FUN_7ffe9bda7ce0(0);
      fVar5 = _DAT_7ffe9c049b18;
      fVar14 = fVar14 + fVar1;
      *(float *)((longlong)plVar3 + 0x1ac) = fVar14;
      if (fVar5 < fVar14) {
        lVar8 = plVar3[0x36];
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar6 = FUN_7ffe9bda1fa0(lVar8,0,0);
        if (cVar6 != '\0') {
          uVar11 = FUN_7ffe9bd98a10(plVar3,0);
          lVar8 = FUN_7ffe99ce53c0(uVar11,1,0);
          plVar3[0x36] = lVar8;
          il2cpp_write_barrier_0();
        }
      }
      goto LAB_7ffe99c6c0b7;
    }
    if (iVar2 == 2) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if ((lVar8 == 0) || (lVar8 = FUN_7ffe9a29e0d0(lVar8,0), lVar8 == 0)) goto LAB_7ffe99c6c509;
      FUN_7ffe99ce5f20(lVar8,0,0);
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99c6c509;
      if (*(char *)(*(longlong *)(self + 0x28) + 0x10) != '\0') {
        lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c953578);
        lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
        uVar11 = *(undefined8 *)(self + 0x30);
        uVar10 = FUN_7ffe9b3675b0(_DAT_7ffe9c94bf48,*(undefined8 *)(self + 0x38),0);
        if ((((lVar9 == 0) || (uVar11 = FUN_7ffe99ace740(lVar9,uVar11,uVar10,0), lVar8 == 0)) ||
            (FUN_7ffe99a4afa0(lVar8,uVar11,0xd,0), plVar3 == (longlong *)0x0)) ||
           (plVar3[0x3e] == 0)) goto LAB_7ffe99c6c509;
        func_0x7ffe99a843b0(plVar3[0x3e],1,0);
      }
      *(undefined8 *)(self + 0x28) = 0;
      il2cpp_write_barrier_0();
      *(undefined8 *)(self + 0x30) = 0;
      il2cpp_write_barrier_0();
      *(undefined8 *)(self + 0x38) = 0;
      il2cpp_write_barrier_0();
LAB_7ffe99c6c191:
      lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c953578);
      if ((lVar8 != 0) &&
         (plVar12 = (longlong *)FUN_7ffe99a4aed0(lVar8,0xd), plVar3 != (longlong *)0x0)) {
        if (plVar12 == (longlong *)0x0) {
          plVar3[0x3f] = 0;
        }
        else {
          if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7ffe9c931fc8 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar12 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c931fc8 + 0x130) * 8) != _DAT_7ffe9c931fc8)) {
            FUN_7ffe9996c950(plVar12);
            pcVar4 = (code *)swi(3);
            bVar7 = (*pcVar4)();
            return bVar7;
          }
          plVar3[0x3f] = (longlong)plVar12;
          if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7ffe9c931fc8 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar12 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c931fc8 + 0x130) * 8) != _DAT_7ffe9c931fc8)) {
            FUN_7ffe9996c950(plVar12,_DAT_7ffe9c931fc8);
            pcVar4 = (code *)swi(3);
            bVar7 = (*pcVar4)();
            return bVar7;
          }
        }
        il2cpp_write_barrier_0();
        lVar8 = plVar3[0x36];
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar6 = FUN_7ffe9bda2160(lVar8,0,0);
        if (cVar6 != '\0') {
          if (plVar3[0x36] == 0) goto LAB_7ffe99c6c509;
          uVar11 = func_0x7ffe9aaf83a0(plVar3[0x36],0);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          FUN_7ffe9bda0840(uVar11,0);
          plVar3[0x36] = 0;
          il2cpp_write_barrier_0();
        }
        FUN_7ffe99c73400(plVar3,0);
        return 0;
      }
LAB_7ffe99c6c509:
      FUN_7ffe9996d7a0();
      pcVar4 = (code *)swi(3);
      bVar7 = (*pcVar4)();
      return bVar7;
    }
LAB_7ffe99c6c502:
    bVar7 = 0;
  }
  return bVar7;
}

