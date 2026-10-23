
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobActionManager_OnSetStatus(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  longlong *plVar6;
  code *pcVar7;
  char cVar8;
  undefined1 uVar9;
  longlong lVar10;
  longlong lVar11;
  
  if (DAT_7ffe9cadd585 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f27e8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f2988);
    FUN_7ffe9996d590(&DAT_7ffe9c973380);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    DAT_7ffe9cadd585 = '\x01';
  }
  cVar8 = (**(code **)(*(longlong *)self + 0x5d8))
                    (self,0x10,*(undefined8 *)(*(longlong *)self + 0x5e0));
  if (cVar8 == '\0') {
    uVar3 = *(undefined8 *)(self + 0x70);
    uVar4 = *(undefined8 *)(self + 0x80);
    uVar5 = *(undefined8 *)(self + 0x88);
    lVar10 = func_0x7ffe99940040(_DAT_7ffe9c973380);
    func_0x7ffe999c3920(lVar10,0);
    *(undefined8 *)(lVar10 + 0x10) = uVar3;
    il2cpp_write_barrier_0();
    *(undefined8 *)(lVar10 + 0x18) = uVar4;
    il2cpp_write_barrier_0();
    *(undefined8 *)(lVar10 + 0x20) = uVar5;
    il2cpp_write_barrier_0();
LAB_7ffe9a327285:
    *(longlong *)(self + 0x158) = lVar10;
    il2cpp_write_barrier_0();
    uVar9 = (**(code **)(*(longlong *)self + 0x5d8))
                      (self,4,*(undefined8 *)(*(longlong *)self + 0x5e0));
    self[0x160] = uVar9;
    return;
  }
  lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar11 != 0) {
    plVar6 = *(longlong **)(lVar11 + 0x28);
    if (plVar6 != (longlong *)0x0) {
      if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7ffe9c8f2988 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f2988 + 0x130) * 8)
          != _DAT_7ffe9c8f2988)) {
        FUN_7ffe9996c950(plVar6);
        pcVar7 = (code *)swi(3);
        (*pcVar7)();
        return;
      }
      uVar1 = *(undefined4 *)((longlong)plVar6 + 0x74);
      uVar2 = *(undefined4 *)((longlong)plVar6 + 0x7c);
      lVar11 = plVar6[0xf];
      uVar3 = *(undefined8 *)(self + 0x88);
      uVar4 = *(undefined8 *)(self + 0x80);
      uVar5 = *(undefined8 *)(self + 0x70);
      lVar10 = func_0x7ffe99940040(_DAT_7ffe9c8f27e8);
      FUN_7ffe9a30bc60(lVar10,uVar5,uVar4,uVar3,uVar1,uVar2,(int)lVar11,0);
      goto LAB_7ffe9a327285;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar7 = (code *)swi(3);
  (*pcVar7)();
  return;
}

