
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HandlingerOfGodspeedBuf_DamageFunction
               (undefined *thisObject,undefined *playerAction,undefined *damageData,
               undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  longlong *plVar4;
  undefined *thisObject_00;
  longlong lVar5;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadf3e6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c9182b0);
    DAT_7ffe9cadf3e6 = '\x01';
  }
  thisObject[0x12] = 1;
  plStackX_8 = (longlong *)0x0;
  if (((playerAction != (undefined *)0x0) &&
      (plVar4 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
      plVar4 != (longlong *)0x0)) &&
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar4 + 0x218))(plVar4,*(undefined8 *)(*plVar4 + 0x220)),
     thisObject_00 != (undefined *)0x0)) {
    bVar2 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x41e,(undefined *)0x0);
    if (bVar2 != 0) {
      if (damageData == (undefined *)0x0) goto LAB_7ffe9a78f6d2;
      if (damageData[0x5a] != '\0') {
        thisObject[0x12] = 0;
        return;
      }
    }
    plVar4 = *(longlong **)(thisObject + 0x40);
    if ((plVar4 != (longlong *)0x0) &&
       (lVar5 = (**(code **)(*plVar4 + 0x1f8))(plVar4,*(undefined8 *)(*plVar4 + 0x200)), lVar5 != 0)
       ) {
      lVar5 = FUN_7ffe99c090e0(lVar5,0);
      if (lVar5 == 0) {
        return;
      }
      if (*(int *)(lVar5 + 0x38) != 9) {
        return;
      }
      plVar4 = *(longlong **)(thisObject + 0x40);
      if (((plVar4 != (longlong *)0x0) &&
          (lVar5 = (**(code **)(*plVar4 + 0x1b8))(plVar4,*(undefined8 *)(*plVar4 + 0x1c0)),
          lVar5 != 0)) && (*(longlong *)(lVar5 + 0x68) != 0)) {
        cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar5 + 0x68),0x3d2,&plStackX_8,_DAT_7ffe9c935bd0);
        if (cVar3 == '\0') {
          return;
        }
        if (plStackX_8 != (longlong *)0x0) {
          if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c9182b0 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStackX_8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c9182b0 + 0x130) * 8) != _DAT_7ffe9c9182b0)) ||
             (plStackX_8 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStackX_8);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          cVar3 = FUN_7ffe9a7b12f0(plStackX_8,*(undefined8 *)(thisObject + 0x40),0);
          if (cVar3 == '\0') {
            return;
          }
          if ((damageData != (undefined *)0x0) &&
             (*(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x40,
             plStackX_8 != (longlong *)0x0)) {
            if ((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c9182b0 + 0x130)) ||
               ((*(longlong *)
                  (*(longlong *)(*plStackX_8 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c9182b0 + 0x130) * 8) != _DAT_7ffe9c9182b0 ||
                (plStackX_8 == (longlong *)0x0)))) {
              FUN_7ffe9996c950(plStackX_8);
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            FUN_7ffe9a7b1390(plStackX_8,0);
            lVar5 = (**(code **)(*(longlong *)playerAction + 0x2a8))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2b0));
            if (lVar5 != 0) {
              FUN_7ffe9a4d99d0(lVar5,_DAT_7ffe9c049b70,0,0);
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a78f6d2:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

