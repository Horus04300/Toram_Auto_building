
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ItemDBData_SetItemDataProperty(undefined *item,undefined *reader,undefined *methodInfo)

{
  longlong lVar1;
  undefined2 uVar2;
  longlong lVar3;
  longlong lVar4;
  code *pcVar5;
  undefined2 uVar6;
  undefined8 uVar7;
  uint uVar8;
  
  if (DAT_7ffe9cade54d == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948b58);
    FUN_7ffe9996d590(&DAT_7ffe9c9085a0);
    DAT_7ffe9cade54d = '\x01';
  }
  uVar8 = 0;
  while ((item != (undefined *)0x0 &&
         (lVar3 = *(longlong *)(item + 0x10), reader != (undefined *)0x0))) {
    uVar6 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    if (lVar3 == 0) break;
    if (*(uint *)(lVar3 + 0x18) <= uVar8) {
LAB_7ffe9a569cbb:
      FUN_7ffe9996d790();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    lVar1 = (longlong)(int)uVar8 * 2 + 0x20;
    *(undefined2 *)(lVar1 + lVar3) = uVar6;
    lVar3 = *(longlong *)(item + 0x18);
    uVar6 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    if (lVar3 == 0) break;
    if (*(uint *)(lVar3 + 0x18) <= uVar8) goto LAB_7ffe9a569cbb;
    *(undefined2 *)(lVar1 + lVar3) = uVar6;
    lVar3 = *(longlong *)(item + 0x10);
    if (lVar3 == 0) break;
    if (*(uint *)(lVar3 + 0x18) <= uVar8) goto LAB_7ffe9a569cbb;
    if (0 < *(short *)(lVar1 + lVar3)) {
      uVar6 = *(undefined2 *)(lVar1 + lVar3);
      lVar3 = *(longlong *)(item + 0x18);
      lVar4 = *(longlong *)(item + 0x20);
      if (lVar3 == 0) break;
      if (*(uint *)(lVar3 + 0x18) <= uVar8) goto LAB_7ffe9a569cbb;
      uVar2 = *(undefined2 *)(lVar1 + lVar3);
      uVar7 = func_0x7ffe99940040(_DAT_7ffe9c948b58);
      FUN_7ffe9aae8db0(uVar7,uVar6,uVar2,0);
      if (lVar4 == 0) break;
      FUN_7ffe99743100(lVar4,uVar7,_DAT_7ffe9c9085a0);
    }
    uVar8 = uVar8 + 1;
    if (9 < (int)uVar8) {
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

