
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerAttackBase_CheckPlayerDamageUpLimit
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *limitDamage,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  int iVar3;
  longlong *plVar4;
  undefined *thisObject_00;
  longlong lVar5;
  
  if (DAT_7ffe9cadded9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    DAT_7ffe9cadded9 = '\x01';
  }
  *(undefined4 *)limitDamage = 0;
  if (playerAction != (undefined *)0x0) {
    plVar4 = (longlong *)
             (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar4 != (longlong *)0x0) {
      thisObject_00 =
           (undefined *)(**(code **)(*plVar4 + 0x218))(plVar4,*(undefined8 *)(*plVar4 + 0x220));
      if (thisObject_00 != (undefined *)0x0) {
        bVar2 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x45,(undefined *)0x0);
        if (bVar2 == 0) {
          return 0;
        }
        if (mobAction != (undefined *)0x0) {
          FUN_7ffe99749320(0x17,_DAT_7ffe9c9724e0,mobAction,0x10);
          lVar5 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
          if (lVar5 != 0) {
            iVar3 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar5);
            iVar3 = (int)((float)iVar3 / _DAT_7ffe9c049cfc);
            if (iVar3 < 1) {
              iVar3 = 1;
            }
            *(int *)limitDamage = iVar3;
            return 1;
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

