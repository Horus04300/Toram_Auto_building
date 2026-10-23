
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
  
  if (DAT_7fff625e1575 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62419a10);
    FUN_7fff5f47d450(&DAT_7fff62446a08);
    FUN_7fff5f47d450(&DAT_7fff62446630);
    FUN_7fff5f47d450(&DAT_7fff62426178);
    FUN_7fff5f47d450(&DAT_7fff62421fc8);
    DAT_7fff625e1575 = '\x01';
  }
  uVar7 = 0;
  if (name == (undefined *)0x0) {
LAB_7fff5f5641a4:
    FUN_7fff5f47d660();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  cVar3 = FUN_7fff60e7a320(name,_DAT_7fff62421fc8,0);
  if (cVar3 == '\0') {
    lVar4 = FUN_7fff60e79f20(name,0x24,0,0);
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
    lVar4 = func_0x7fff5f47c850(_DAT_7fff62419a10,2);
    if (lVar4 == 0) goto LAB_7fff5f5641a4;
    if ((*(int *)(lVar4 + 0x18) == 0) ||
       (*(undefined2 *)(lVar4 + 0x20) = 0x5b, *(uint *)(lVar4 + 0x18) < 2)) goto LAB_7fff5f5641aa;
    *(undefined2 *)(lVar4 + 0x22) = 0x5d;
    lVar4 = FUN_7fff60e79cf0(name,lVar4,0);
    uVar7 = 1;
    if (lVar4 == 0) goto LAB_7fff5f5641a4;
    uVar6 = *(int *)(lVar4 + 0x18) - 2;
  }
  uVar5 = func_0x7fff5f44ff00(_DAT_7fff62426178);
  FUN_7fff608aec00(uVar5,_DAT_7fff62446630);
  *(undefined8 *)(self + 0x28) = uVar5;
  thunk_FUN_7fff5f491fd0();
  while( true ) {
    if ((int)uVar6 <= (int)uVar7) {
      return;
    }
    if (*(uint *)(lVar4 + 0x18) <= uVar7) break;
    lVar1 = (longlong)(int)uVar7 + 1;
    if (*(uint *)(lVar4 + 0x18) <= (uint)lVar1) break;
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5f5641a4;
    FUN_7fff608b1140(*(longlong *)(self + 0x28),
                     *(undefined8 *)(lVar4 + 0x20 + (longlong)(int)uVar7 * 8),
                     *(undefined8 *)(lVar4 + 0x20 + lVar1 * 8),_DAT_7fff62446a08);
    uVar7 = uVar7 + 2;
  }
LAB_7fff5f5641aa:
  FUN_7fff5f47d650();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

