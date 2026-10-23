
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ResourceManager__Initialize_d__31_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  longlong *plVar7;
  undefined *data;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uStackX_8;
  undefined8 uStackX_18;
  
  if (DAT_7ffe9cada116 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c96d390);
    FUN_7ffe9996d590(&DAT_7ffe9c96bc88);
    FUN_7ffe9996d590(&DAT_7ffe9c96bbb8);
    FUN_7ffe9996d590(&DAT_7ffe9c96c150);
    FUN_7ffe9996d590(0x7ffe9c96c218);
    FUN_7ffe9996d590(&DAT_7ffe9c927790);
    FUN_7ffe9996d590(&DAT_7ffe9c963400);
    FUN_7ffe9996d590(&DAT_7ffe9c903c08);
    FUN_7ffe9996d590(&DAT_7ffe9c918048);
    FUN_7ffe9996d590(&DAT_7ffe9c939eb8);
    FUN_7ffe9996d590(&DAT_7ffe9c955128);
    FUN_7ffe9996d590(&DAT_7ffe9c909e60);
    FUN_7ffe9996d590(&DAT_7ffe9c8fbbc0);
    FUN_7ffe9996d590(&DAT_7ffe9c909d90);
    FUN_7ffe9996d590(&DAT_7ffe9c954f98);
    DAT_7ffe9cada116 = '\x01';
  }
  iVar6 = *(int *)(self + 0x10);
  lVar1 = *(longlong *)(self + 0x20);
  if (iVar6 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    uVar8 = func_0x7ffe99940040(_DAT_7ffe9c918048);
    func_0x7ffe999c30f0(uVar8,0);
    *(undefined8 *)(self + 0x30) = uVar8;
    il2cpp_write_barrier_0();
    if (*(longlong *)(self + 0x30) == 0) {
LAB_7ffe99adfc52:
      FUN_7ffe9996d7a0();
      pcVar3 = (code *)swi(3);
      bVar5 = (*pcVar3)();
      return bVar5;
    }
    *(undefined1 *)(*(longlong *)(self + 0x30) + 0x10) = 0;
    if (lVar1 == 0) goto LAB_7ffe99adfc52;
    *(undefined8 *)(lVar1 + 0x38) = *(undefined8 *)(self + 0x28);
    il2cpp_write_barrier_0();
    if (*(int *)(_DAT_7ffe9c96d390 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    uStackX_8 = FUN_7ffe9b4fbf50(0);
    uStackX_18 = FUN_7ffe9b4fc1e0(&uStackX_8,0);
    uVar8 = FUN_7ffe9b5052a0(&uStackX_18,0);
    uVar9 = FUN_7ffe9b3675b0(_DAT_7ffe9c939eb8,uVar8,0);
    lVar2 = *(longlong *)(lVar1 + 0x20);
    uVar8 = *(undefined8 *)(lVar1 + 0x38);
    uVar10 = FUN_7ffe9b3675b0(_DAT_7ffe9c955128,uVar9,0);
    uVar9 = *(undefined8 *)(self + 0x30);
    uVar11 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
    FUN_7ffe9ac2ed50(uVar11,uVar9,_DAT_7ffe9c903c08,0);
    if (lVar2 == 0) goto LAB_7ffe99adfc52;
    uVar8 = FUN_7ffe99a95f00(lVar2,uVar8,uVar10,uVar11,0);
    uVar8 = FUN_7ffe9bd9f640(lVar1,uVar8,0);
    *(undefined8 *)(self + 0x18) = uVar8;
    il2cpp_write_barrier_0();
    *(undefined4 *)(self + 0x10) = 1;
LAB_7ffe99adf9b4:
    bVar5 = 1;
  }
  else {
    if (iVar6 == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (*(longlong *)(self + 0x30) == 0) goto LAB_7ffe99adfc52;
      if (*(char *)(*(longlong *)(self + 0x30) + 0x10) != '\0') {
        uVar8 = func_0x7ffe99940040(_DAT_7ffe9c927790);
        func_0x7ffe999c30f0(uVar8,_DAT_7ffe9c96bbb8);
        *(undefined8 *)(self + 0x40) = uVar8;
        il2cpp_write_barrier_0();
        uVar8 = FUN_7ffe99ad1910(0);
        *(undefined8 *)(self + 0x48) = uVar8;
        il2cpp_write_barrier_0();
        if (lVar1 == 0) goto LAB_7ffe99adfc52;
        lVar2 = *(longlong *)(lVar1 + 0x30);
        uVar8 = FUN_7ffe9b36a9f0(_DAT_7ffe9c8fbbc0,*(undefined8 *)(lVar1 + 0x38),
                                 *(undefined8 *)(self + 0x48),0);
        if (lVar2 == 0) goto LAB_7ffe99adfc52;
        uVar8 = FUN_7ffe99aaf050(lVar2,uVar8,*(undefined8 *)(self + 0x40),0);
        uVar8 = FUN_7ffe9bd9f640(lVar1,uVar8,0);
        *(undefined8 *)(self + 0x18) = uVar8;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 2;
        goto LAB_7ffe99adf9b4;
      }
      func_0x7ffe999c3920(_DAT_7ffe9c954f98,0);
      lVar1 = *(longlong *)(self + 0x38);
      if (lVar1 != 0) {
        if (*(longlong *)(self + 0x30) == 0) goto LAB_7ffe99adfc52;
        (**(code **)(lVar1 + 0x18))
                  (*(undefined8 *)(lVar1 + 0x40),*(undefined1 *)(*(longlong *)(self + 0x30) + 0x10),
                   *(undefined8 *)(lVar1 + 0x28));
      }
    }
    else {
      if (iVar6 == 2) {
        *(undefined4 *)(self + 0x10) = 0xffffffff;
        if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe99adfc52;
        cVar4 = FUN_7ffe9adfad70(*(longlong *)(self + 0x40),_DAT_7ffe9c96c150);
        if (cVar4 != '\0') {
          func_0x7ffe999c3920(_DAT_7ffe9c909e60,0);
          lVar1 = *(longlong *)(self + 0x38);
          if (lVar1 != 0) {
            (**(code **)(lVar1 + 0x18))
                      (*(undefined8 *)(lVar1 + 0x40),0,*(undefined8 *)(lVar1 + 0x28));
          }
          if (*(longlong *)(self + 0x40) != 0) {
            FUN_7ffe9adfa7a0(*(longlong *)(self + 0x40),_DAT_7ffe9c96bc88);
            return 0;
          }
          goto LAB_7ffe99adfc52;
        }
        if (((*(longlong *)(self + 0x40) == 0) ||
            (lVar2 = *(longlong *)(*(longlong *)(self + 0x40) + 0x10), lVar2 == 0)) ||
           (plVar7 = (longlong *)FUN_7ffe9bd743a0(lVar2,_DAT_7ffe9c909d90,0),
           plVar7 == (longlong *)0x0)) goto LAB_7ffe99adfc52;
        if (((*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7ffe9c963400 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plVar7 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c963400 + 0x130) * 8) != _DAT_7ffe9c963400)) ||
           ((data = (undefined *)FUN_7ffe9bda7ca0(plVar7,0), lVar1 == 0 ||
            (*(longlong *)(lVar1 + 0x20) == 0)))) goto LAB_7ffe99adfc52;
        iVar6 = FUN_7ffe99a95e20(*(longlong *)(lVar1 + 0x20),*(undefined8 *)(self + 0x48));
        ResourceManager_AssetDecrypt(data,iVar6,(undefined *)0x0);
        FUN_7ffe9bda6000(plVar7,0);
        if ((*(longlong *)(self + 0x40) == 0) ||
           (lVar2 = *(longlong *)(*(longlong *)(self + 0x40) + 0x10), lVar2 == 0))
        goto LAB_7ffe99adfc52;
        FUN_7ffe9bd74670(lVar2,1,0);
        if (*(longlong *)(lVar1 + 0x20) == 0) goto LAB_7ffe99adfc52;
        uVar8 = FUN_7ffe99a93b90(*(longlong *)(lVar1 + 0x20),*(undefined8 *)(self + 0x48),0,data,0);
        uVar8 = FUN_7ffe9bd9f640(lVar1,uVar8,0);
        *(undefined8 *)(self + 0x18) = uVar8;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 3;
        goto LAB_7ffe99adf9b4;
      }
      if (iVar6 == 3) {
        lVar1 = *(longlong *)(self + 0x38);
        *(undefined4 *)(self + 0x10) = 0xffffffff;
        if (lVar1 != 0) {
          (**(code **)(lVar1 + 0x18))(*(undefined8 *)(lVar1 + 0x40),1,*(undefined8 *)(lVar1 + 0x28))
          ;
          return 0;
        }
      }
    }
    bVar5 = 0;
  }
  return bVar5;
}

