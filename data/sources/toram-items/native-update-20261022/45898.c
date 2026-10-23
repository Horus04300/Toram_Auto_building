
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte StageLoginDownloader__Start_d__12_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  bool bVar3;
  byte bVar4;
  undefined8 uVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong lVar8;
  
  if (DAT_7ffe9cad9d0e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c954ef0);
    FUN_7ffe9996d590(&DAT_7ffe9c953578);
    FUN_7ffe9996d590(&DAT_7ffe9c960dc8);
    FUN_7ffe9996d590(&DAT_7ffe9c8feeb8);
    DAT_7ffe9cad9d0e = '\x01';
  }
  lVar1 = *(longlong *)(self + 0x20);
  if (*(int *)(self + 0x10) == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    uVar5 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 0x58) = uVar5;
      il2cpp_write_barrier_0();
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        FUN_7ffe99ce63d0(*(longlong *)(lVar1 + 0x20),0);
        uVar5 = FUN_7ffe9b141840(_DAT_7ffe9c953578);
        *(undefined8 *)(lVar1 + 0x40) = uVar5;
        il2cpp_write_barrier_0();
        if (*(undefined **)(lVar1 + 0x40) != (undefined *)0x0) {
          plVar6 = (longlong *)
                   LocalizeManager_Get(*(undefined **)(lVar1 + 0x40),(undefined *)0x0,
                                       (undefined *)0x0);
          if (plVar6 == (longlong *)0x0) {
            *(undefined8 *)(lVar1 + 0x48) = 0;
          }
          else {
            if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar6 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8) != _DAT_7ffe9c960dc8)) {
              bVar3 = false;
            }
            else {
              bVar3 = true;
            }
            plVar7 = (longlong *)0x0;
            if (bVar3) {
              plVar7 = plVar6;
            }
            *(longlong **)(lVar1 + 0x48) = plVar7;
          }
          il2cpp_write_barrier_0();
          if (*(longlong *)(lVar1 + 0x40) != 0) {
            uVar5 = FUN_7ffe99a4a810(*(longlong *)(lVar1 + 0x40),0);
            *(undefined8 *)(lVar1 + 0x68) = uVar5;
            il2cpp_write_barrier_0();
            uVar5 = FUN_7ffe9b141840(_DAT_7ffe9c954ef0);
            *(undefined8 *)(lVar1 + 0x50) = uVar5;
            il2cpp_write_barrier_0();
            if (DAT_7ffe9cad9d02 == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c929058);
              DAT_7ffe9cad9d02 = '\x01';
            }
            lVar8 = func_0x7ffe99940040(_DAT_7ffe9c929058);
            func_0x7ffe999c3920(lVar8,0);
            *(longlong *)(lVar8 + 0x20) = lVar1;
            *(undefined4 *)(lVar8 + 0x10) = 0;
            il2cpp_write_barrier_0();
            FUN_7ffe9bd9f640(lVar1,lVar8,0);
            uVar5 = func_0x7ffe99940040(_DAT_7ffe9c8feeb8);
            FUN_7ffe9bdae370(uVar5,_DAT_7ffe9c049b40,0);
            *(undefined8 *)(self + 0x18) = uVar5;
            il2cpp_write_barrier_0();
            *(undefined4 *)(self + 0x10) = 1;
            return 1;
          }
        }
      }
    }
  }
  else {
    if (*(int *)(self + 0x10) != 1) {
      return 0;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if ((lVar1 != 0) && (*(longlong *)(lVar1 + 0x20) != 0)) {
      FUN_7ffe99ce5860(*(longlong *)(lVar1 + 0x20),0);
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        FUN_7ffe99ce6230(*(longlong *)(lVar1 + 0x20),7);
        if (*(longlong *)(lVar1 + 0x20) != 0) {
          *(undefined1 *)(*(longlong *)(lVar1 + 0x20) + 0x68) = 1;
          if (*(longlong *)(lVar1 + 0x20) != 0) {
            FUN_7ffe99ce63d0(*(longlong *)(lVar1 + 0x20),1,0);
            return 0;
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar4 = (*pcVar2)();
  return bVar4;
}

