
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
  
  if (DAT_7fff625e5ca4 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450498);
    FUN_7fff5f47d450(&DAT_7fff6240f5d0);
    DAT_7fff625e5ca4 = '\x01';
  }
  uVar8 = 0;
  while ((item != (undefined *)0x0 &&
         (lVar3 = *(longlong *)(item + 0x10), reader != (undefined *)0x0))) {
    uVar6 = (**(code **)(*(longlong *)reader + 0x208))
                      (reader,*(undefined8 *)(*(longlong *)reader + 0x210));
    if (lVar3 == 0) break;
    if (*(uint *)(lVar3 + 0x18) <= uVar8) {
LAB_7fff6007446b:
      FUN_7fff5f47d650();
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
    if (*(uint *)(lVar3 + 0x18) <= uVar8) goto LAB_7fff6007446b;
    *(undefined2 *)(lVar1 + lVar3) = uVar6;
    lVar3 = *(longlong *)(item + 0x10);
    if (lVar3 == 0) break;
    if (*(uint *)(lVar3 + 0x18) <= uVar8) goto LAB_7fff6007446b;
    if (0 < *(short *)(lVar1 + lVar3)) {
      uVar6 = *(undefined2 *)(lVar1 + lVar3);
      lVar3 = *(longlong *)(item + 0x18);
      lVar4 = *(longlong *)(item + 0x20);
      if (lVar3 == 0) break;
      if (*(uint *)(lVar3 + 0x18) <= uVar8) goto LAB_7fff6007446b;
      uVar2 = *(undefined2 *)(lVar1 + lVar3);
      uVar7 = func_0x7fff5f44ff00(_DAT_7fff62450498);
      FUN_7fff605f3160(uVar7,uVar6,uVar2,0);
      if (lVar4 == 0) break;
      FUN_7fff5f253100(lVar4,uVar7,_DAT_7fff6240f5d0);
    }
    uVar8 = uVar8 + 1;
    if (9 < (int)uVar8) {
      return;
    }
  }
  FUN_7fff5f47d660();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

