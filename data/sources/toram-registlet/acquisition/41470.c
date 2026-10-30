
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte _OnChallengeDungeon2ResultCommand_d__293_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  byte bVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  
  if (DAT_7ffe9cae064c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f1108);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    DAT_7ffe9cae064c = '\x01';
  }
  lVar1 = *(longlong *)(self + 0x20);
  if (*(int *)(self + 0x10) == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if ((lVar1 == 0) || (*(longlong *)(lVar1 + 0x40) == 0)) goto LAB_7ffe9aa300c6;
    FUN_7ffe9a9fc190(*(longlong *)(lVar1 + 0x40),0);
    if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7ffe9aa300c6;
    FUN_7ffe9a9fc190(*(longlong *)(lVar1 + 0x40),0);
    plVar4 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
    if (plVar4 == (longlong *)0x0) goto LAB_7ffe9aa300c6;
    (**(code **)(*plVar4 + 0x278))(plVar4,0x9b,*(undefined8 *)(*plVar4 + 0x280));
    lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
    if ((lVar5 == 0) || (lVar5 = FUN_7ffe9a29dca0(lVar5,0), lVar5 == 0)) goto LAB_7ffe9aa300c6;
    uVar6 = FUN_7ffe9ab9c3a0(lVar5,_DAT_7ffe9c8f1108);
    *(undefined8 *)(self + 0x28) = uVar6;
    il2cpp_write_barrier_0();
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe9aa300c6;
    FUN_7ffe99c86620(*(longlong *)(self + 0x28),0,0);
  }
  else {
    if (*(int *)(self + 0x10) != 1) {
      return 0;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
  }
  if (*(longlong *)(self + 0x28) != 0) {
    if (*(char *)(*(longlong *)(self + 0x28) + 0x148) == '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
    plVar4 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
    if ((plVar4 != (longlong *)0x0) &&
       ((**(code **)(*plVar4 + 0x278))(plVar4,2,*(undefined8 *)(*plVar4 + 0x280)), lVar1 != 0)) {
      FUN_7ffe9aa10230(lVar1,3);
      plVar4 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if (plVar4 != (longlong *)0x0) {
        (**(code **)(*plVar4 + 0x248))(plVar4,0,5,*(undefined8 *)(*plVar4 + 0x250));
        return 0;
      }
    }
  }
LAB_7ffe9aa300c6:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar3 = (*pcVar2)();
  return bVar3;
}

