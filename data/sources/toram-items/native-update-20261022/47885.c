
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte AssetBundleManager__Initialize_d__43_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  undefined8 uVar5;
  longlong lVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong *plVar9;
  
  if (DAT_7ffe9cad9fe2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c96b558);
    FUN_7ffe9996d590(&DAT_7ffe9c96b490);
    FUN_7ffe9996d590(0x7ffe9c96b958);
    FUN_7ffe9996d590(&DAT_7ffe9c96ba20);
    FUN_7ffe9996d590(0x7ffe9c96baf0);
    FUN_7ffe9996d590(&DAT_7ffe9c9276c8);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c951900);
    FUN_7ffe9996d590(&DAT_7ffe9c953080);
    FUN_7ffe9996d590(&DAT_7ffe9c952fb8);
    FUN_7ffe9996d590(&DAT_7ffe9c952ee8);
    DAT_7ffe9cad9fe2 = '\x01';
  }
  lVar1 = *(longlong *)(self + 0x20);
  if (*(int *)(self + 0x10) == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar1 != 0) {
      if (*(char *)(lVar1 + 0x68) != '\0') {
        func_0x7ffe999c3920(_DAT_7ffe9c952ee8,0);
        return 0;
      }
      *(undefined8 *)(lVar1 + 0x58) = *(undefined8 *)(self + 0x28);
      il2cpp_write_barrier_0();
      *(undefined8 *)(lVar1 + 0x60) = *(undefined8 *)(self + 0x30);
      il2cpp_write_barrier_0();
      uVar5 = func_0x7ffe99940040(_DAT_7ffe9c9276c8);
      func_0x7ffe999c30f0(uVar5,_DAT_7ffe9c96b490);
      *(undefined8 *)(self + 0x40) = uVar5;
      il2cpp_write_barrier_0();
      lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c951900);
      uVar7 = FUN_7ffe9b3675b0(*(undefined8 *)(lVar1 + 0x58),*(undefined8 *)(lVar1 + 0x60),0);
      uVar5 = *(undefined8 *)(self + 0x40);
      if (lVar6 != 0) {
        if (DAT_7ffe9cada007 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c934bb8);
          DAT_7ffe9cada007 = '\x01';
        }
        lVar8 = func_0x7ffe99940040(_DAT_7ffe9c934bb8);
        func_0x7ffe999c3920(lVar8,0);
        *(longlong *)(lVar8 + 0x20) = lVar6;
        *(undefined4 *)(lVar8 + 0x10) = 0;
        il2cpp_write_barrier_0();
        *(undefined8 *)(lVar8 + 0x30) = uVar7;
        il2cpp_write_barrier_0();
        *(undefined8 *)(lVar8 + 0x28) = uVar5;
        il2cpp_write_barrier_0();
        uVar5 = FUN_7ffe9bd9f640(lVar1,lVar8,0);
        *(undefined8 *)(self + 0x18) = uVar5;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 1;
        return 1;
      }
    }
    goto LAB_7ffe99abc868;
  }
  if (*(int *)(self + 0x10) == 1) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe99abc868;
    cVar3 = FUN_7ffe9adfad70(*(longlong *)(self + 0x40),_DAT_7ffe9c96ba20);
    if (cVar3 == '\0') {
      if ((*(longlong *)(self + 0x40) == 0) || (lVar1 == 0)) goto LAB_7ffe99abc868;
      cVar3 = FUN_7ffe99a98150(lVar1,*(undefined8 *)(*(longlong *)(self + 0x40) + 0x10),
                               *(undefined8 *)(lVar1 + 0x30),0);
      lVar6 = *(longlong *)(self + 0x40);
      if (cVar3 != '\0') {
        if (lVar6 != 0) {
          FUN_7ffe9adfa7a0(lVar6,_DAT_7ffe9c96b558);
          *(undefined8 *)(self + 0x40) = 0;
          il2cpp_write_barrier_0();
          lVar6 = *(longlong *)(self + 0x38);
          if (lVar6 != 0) {
            (**(code **)(lVar6 + 0x18))
                      (*(undefined8 *)(lVar6 + 0x40),1,*(undefined8 *)(lVar6 + 0x28));
            *(undefined1 *)(lVar1 + 0x68) = 1;
            return 0;
          }
        }
        goto LAB_7ffe99abc868;
      }
      if (lVar6 == 0) goto LAB_7ffe99abc868;
      FUN_7ffe9adfa7a0(lVar6,_DAT_7ffe9c96b558);
      *(undefined8 *)(self + 0x40) = 0;
      il2cpp_write_barrier_0();
      func_0x7ffe999c3920(_DAT_7ffe9c953080,0);
    }
    else {
      plVar9 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
      if ((*(longlong *)(self + 0x40) == 0) ||
         (lVar1 = *(longlong *)(*(longlong *)(self + 0x40) + 0x20), plVar9 == (longlong *)0x0))
      goto LAB_7ffe99abc868;
      if ((lVar1 != 0) &&
         (lVar6 = func_0x7ffe9996c920(lVar1,*(undefined8 *)(*plVar9 + 0x40)), lVar6 == 0)) {
        uVar5 = func_0x7ffe9996d1f0();
        FUN_7ffe9996d760(uVar5,0);
        pcVar2 = (code *)swi(3);
        bVar4 = (*pcVar2)();
        return bVar4;
      }
      if ((int)plVar9[3] == 0) {
        FUN_7ffe9996d790();
        pcVar2 = (code *)swi(3);
        bVar4 = (*pcVar2)();
        return bVar4;
      }
      plVar9[4] = lVar1;
      il2cpp_write_barrier_0();
      func_0x7ffe999c3920(_DAT_7ffe9c952fb8,plVar9,0);
      if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe99abc868;
      FUN_7ffe9adfa7a0(*(longlong *)(self + 0x40),_DAT_7ffe9c96b558);
      *(undefined8 *)(self + 0x40) = 0;
      il2cpp_write_barrier_0();
    }
    lVar1 = *(longlong *)(self + 0x38);
    if (lVar1 == 0) {
LAB_7ffe99abc868:
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      bVar4 = (*pcVar2)();
      return bVar4;
    }
    (**(code **)(lVar1 + 0x18))(*(undefined8 *)(lVar1 + 0x40),0,*(undefined8 *)(lVar1 + 0x28));
  }
  return 0;
}

