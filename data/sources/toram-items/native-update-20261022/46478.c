
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkillTextManagerData_CheckNameText(undefined *self,undefined *name,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  undefined8 uVar5;
  uint uVar6;
  uint uVar7;
  
  if (DAT_7ffe9cad9df9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c911e80);
    FUN_7ffe9996d590(&DAT_7ffe9c93fab0);
    FUN_7ffe9996d590(&DAT_7ffe9c93f6e0);
    FUN_7ffe9996d590(&DAT_7ffe9c91e708);
    FUN_7ffe9996d590(&DAT_7ffe9c91c178);
    DAT_7ffe9cad9df9 = '\x01';
  }
  uVar7 = 0;
  if (name == (undefined *)0x0) {
LAB_7ffe99a54374:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  cVar3 = FUN_7ffe9b36ff60(name,_DAT_7ffe9c91c178,0);
  if (cVar3 == '\0') {
    lVar4 = FUN_7ffe9b36fb60(name,0x24,0,0);
    if (lVar4 == 0) {
      return;
    }
    uVar6 = *(uint *)(lVar4 + 0x18);
    if ((uVar6 & 1) != 0) {
      return;
    }
    if (*(longlong *)(lVar4 + 0x18) == 0) {
      return;
    }
  }
  else {
    lVar4 = func_0x7ffe9996c990(_DAT_7ffe9c911e80,2);
    if (lVar4 == 0) goto LAB_7ffe99a54374;
    if ((*(int *)(lVar4 + 0x18) == 0) ||
       (*(undefined2 *)(lVar4 + 0x20) = 0x5b, *(uint *)(lVar4 + 0x18) < 2)) goto LAB_7ffe99a5437a;
    *(undefined2 *)(lVar4 + 0x22) = 0x5d;
    lVar4 = FUN_7ffe9b36f930(name,lVar4,0);
    uVar7 = 1;
    if (lVar4 == 0) goto LAB_7ffe99a54374;
    uVar6 = *(int *)(lVar4 + 0x18) - 2;
  }
  uVar5 = func_0x7ffe99940040(_DAT_7ffe9c91e708);
  FUN_7ffe9ada4840(uVar5,_DAT_7ffe9c93f6e0);
  *(undefined8 *)(self + 0x28) = uVar5;
  il2cpp_write_barrier_0();
  while( true ) {
    if ((int)uVar6 <= (int)uVar7) {
      return;
    }
    if (*(uint *)(lVar4 + 0x18) <= uVar7) break;
    lVar1 = (longlong)(int)uVar7 + 1;
    if (*(uint *)(lVar4 + 0x18) <= (uint)lVar1) break;
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99a54374;
    FUN_7ffe9ada6d80(*(longlong *)(self + 0x28),
                     *(undefined8 *)(lVar4 + 0x20 + (longlong)(int)uVar7 * 8),
                     *(undefined8 *)(lVar4 + 0x20 + lVar1 * 8),_DAT_7ffe9c93fab0);
    uVar7 = uVar7 + 2;
  }
LAB_7ffe99a5437a:
  FUN_7ffe9996d790();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

