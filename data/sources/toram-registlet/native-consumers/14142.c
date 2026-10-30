
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int NormalAttackAction_calcRampageConstantDamage
              (undefined *thisObject,undefined *playerAction,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined *thisObject_00;
  longlong *aplStackX_10 [3];
  
  if (DAT_7ffe9cadde94 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    DAT_7ffe9cadde94 = '\x01';
  }
  aplStackX_10[0] = (longlong *)0x0;
  if ((((playerAction != (undefined *)0x0) &&
       (plVar5 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
       plVar5 != (longlong *)0x0)) &&
      (lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0)), lVar6 != 0))
     && (*(longlong *)(lVar6 + 0x40) != 0)) {
    cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x40),0x29,aplStackX_10,_DAT_7ffe9c934418);
    if (cVar2 == '\0') {
      return 0;
    }
    if (aplStackX_10[0] != (longlong *)0x0) {
      if (*(char *)((longlong)aplStackX_10[0] + 0x1c) == '\0') {
        return 0;
      }
      iVar4 = (**(code **)(*aplStackX_10[0] + 0x1f8))
                        (aplStackX_10[0],0x32,*(undefined8 *)(*aplStackX_10[0] + 0x200));
      plVar5 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar5 != (longlong *)0x0) &&
         (thisObject_00 =
               (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
         thisObject_00 != (undefined *)0x0)) {
        bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x12e,(undefined *)0x0);
        if ((bVar3 == 0) && (iVar4 == 1)) {
          if (aplStackX_10[0] != (longlong *)0x0) {
            return (*(byte *)(aplStackX_10[0] + 2) + 0xf) * 0x14;
          }
        }
        else if (aplStackX_10[0] != (longlong *)0x0) {
          return ((uint)*(byte *)(aplStackX_10[0] + 2) + (uint)*(byte *)(aplStackX_10[0] + 2) * 4) *
                 2;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar4 = (*pcVar1)();
  return iVar4;
}

