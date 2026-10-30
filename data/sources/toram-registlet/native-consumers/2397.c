
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte AvoidActionManager_CheckAvoidEquip(undefined *thisObject,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined *thisObject_00;
  
  if (DAT_7ffe9cadf5d7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935988);
    DAT_7ffe9cadf5d7 = '\x01';
  }
  plVar5 = *(longlong **)(thisObject + 0x28);
  if ((plVar5 != (longlong *)0x0) &&
     (plVar5 = (longlong *)(**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
     plVar5 != (longlong *)0x0)) {
    lVar6 = (**(code **)(*plVar5 + 0x1f8))(plVar5,*(undefined8 *)(*plVar5 + 0x200));
    if (lVar6 == 0) {
      return 0;
    }
    lVar7 = FUN_7ffe99c08fe0(lVar6,0);
    if (lVar7 != 0) {
      lVar7 = FUN_7ffe99c08fe0(lVar6,0);
      if (lVar7 == 0) goto LAB_7ffe9a7d5b0d;
      if (*(int *)(lVar7 + 0x38) == 0x12) {
        return 1;
      }
    }
    lVar7 = FUN_7ffe99c090e0(lVar6,0);
    if (lVar7 != 0) {
      lVar7 = FUN_7ffe99c090e0(lVar6,0);
      if (lVar7 == 0) goto LAB_7ffe9a7d5b0d;
      if (*(int *)(lVar7 + 0x38) == 0x10) {
        return 1;
      }
    }
    lVar7 = FUN_7ffe99c090e0(lVar6,0);
    if (lVar7 != 0) {
      lVar7 = FUN_7ffe99c090e0(lVar6,0);
      if (lVar7 == 0) goto LAB_7ffe9a7d5b0d;
      if (*(int *)(lVar7 + 0x38) == 0xf) {
        return 1;
      }
    }
    lVar7 = FUN_7ffe99c08fe0(lVar6,0);
    if (lVar7 != 0) {
      lVar7 = FUN_7ffe99c08fe0(lVar6,0);
      if (lVar7 == 0) goto LAB_7ffe9a7d5b0d;
      if (*(int *)(lVar7 + 0x38) == 0xf) {
        return 1;
      }
    }
    lVar7 = FUN_7ffe99c090e0(lVar6,0);
    if (lVar7 != 0) {
      lVar7 = FUN_7ffe99c090e0(lVar6,0);
      if (lVar7 == 0) goto LAB_7ffe9a7d5b0d;
      if ((*(int *)(lVar7 + 0x38) == 10) && (lVar7 = FUN_7ffe99c08fe0(lVar6,0), lVar7 != 0)) {
        lVar7 = FUN_7ffe99c08fe0(lVar6,0);
        if (lVar7 == 0) goto LAB_7ffe9a7d5b0d;
        if (*(int *)(lVar7 + 0x38) == 10) {
          return 1;
        }
      }
    }
    uVar8 = FUN_7ffe99c08d90(lVar6,0);
    cVar2 = func_0x7ffe9a569860(uVar8,1);
    if (cVar2 != '\0') {
      return 1;
    }
    iVar4 = FUN_7ffe99c09050(lVar6,0);
    if ((iVar4 == 0) && (iVar4 = FUN_7ffe99c08f50(lVar6,0), iVar4 == 0)) {
      plVar5 = *(longlong **)(thisObject + 0x28);
      if ((plVar5 == (longlong *)0x0) ||
         (((plVar5 = (longlong *)
                     (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
           plVar5 == (longlong *)0x0 ||
           (lVar6 = (**(code **)(*plVar5 + 0x1b8))(plVar5,*(undefined8 *)(*plVar5 + 0x1c0)),
           lVar6 == 0)) || (*(longlong *)(lVar6 + 0x68) == 0)))) goto LAB_7ffe9a7d5b0d;
      cVar2 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar6 + 0x68),0x44c,_DAT_7ffe9c935988);
      if (cVar2 != '\0') {
        return 1;
      }
    }
    plVar5 = *(longlong **)(thisObject + 0x28);
    if (((plVar5 != (longlong *)0x0) &&
        (plVar5 = (longlong *)
                  (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
        plVar5 != (longlong *)0x0)) &&
       (thisObject_00 =
             (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
       thisObject_00 != (undefined *)0x0)) {
      bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x32,(undefined *)0x0);
      if (bVar3 != 0) {
        return 1;
      }
      return 0;
    }
  }
LAB_7ffe9a7d5b0d:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

