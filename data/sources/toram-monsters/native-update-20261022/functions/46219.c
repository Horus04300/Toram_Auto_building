
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EnemyTextManager_Initialize(undefined *self,undefined *binary,undefined *methodInfo)

{
  code *pcVar1;
  undefined4 uVar2;
  longlong lVar3;
  longlong *plVar4;
  undefined8 uVar5;
  longlong lVar6;
  int iVar7;
  longlong *plStack_88;
  int iStack_80;
  longlong alStack_78 [2];
  longlong *plStack_68;
  undefined8 uStack_60;
  longlong **pplStack_58;
  
  if (DAT_7ffe9cad9d75 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943bb8);
    FUN_7ffe9996d590(&DAT_7ffe9c9093b0);
    FUN_7ffe9996d590(&DAT_7ffe9c909890);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    FUN_7ffe9996d590(&DAT_7ffe9c964588);
    DAT_7ffe9cad9d75 = '\x01';
  }
  iVar7 = 0;
  alStack_78[0] = 0;
  plStack_88 = (longlong *)0x0;
  self[0x11] = 0;
  if (*(longlong *)(self + 0x18) != 0) {
    FUN_7ffe9acce330(*(longlong *)(self + 0x18),_DAT_7ffe9c9093b0);
    lVar3 = func_0x7ffe99940040(_DAT_7ffe9c969f48);
    FUN_7ffe9b4c0ad0(lVar3,binary,0);
    alStack_78[1] = 0;
    plStack_68 = alStack_78;
    alStack_78[0] = lVar3;
    plVar4 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c943bb8);
    FUN_7ffe9b4cd430(plVar4,lVar3,0);
    uStack_60 = 0;
    pplStack_58 = &plStack_88;
    plStack_88 = plVar4;
    if (plVar4 != (longlong *)0x0) {
      iStack_80 = (**(code **)(*plVar4 + 0x228))(plVar4,*(undefined8 *)(*plVar4 + 0x230));
      while( true ) {
        if (iStack_80 <= iVar7) {
          if (plStack_88 != (longlong *)0x0) {
            FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
          }
          if (alStack_78[0] != 0) {
            FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
          }
          self[0x10] = 1;
          self[0x12] = 0;
          return;
        }
        if (plStack_88 == (longlong *)0x0) break;
        uVar2 = (**(code **)(*plStack_88 + 0x228))(plStack_88,*(undefined8 *)(*plStack_88 + 0x230));
        if (plStack_88 == (longlong *)0x0) {
LAB_7ffe99a45ef9:
          FUN_7ffe9996d7a0();
          break;
        }
        uVar5 = (**(code **)(*plStack_88 + 0x298))(plStack_88,*(undefined8 *)(*plStack_88 + 0x2a0));
        lVar3 = *(longlong *)(self + 0x18);
        lVar6 = func_0x7ffe99940040(_DAT_7ffe9c964588);
        func_0x7ffe999c3920(lVar6,0);
        *(undefined8 *)(lVar6 + 0x10) = uVar5;
        il2cpp_write_barrier_0();
        if (lVar3 == 0) {
          FUN_7ffe9996d7a0();
          goto LAB_7ffe99a45ef9;
        }
        FUN_7ffe9ad5ed00(lVar3,uVar2,lVar6,_DAT_7ffe9c909890);
        iVar7 = iVar7 + 1;
      }
      FUN_7ffe9996d7a0();
    }
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
    FUN_7ffe998fa550();
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

