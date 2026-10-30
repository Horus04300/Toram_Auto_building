
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerAttackBase_CalcPlayerDamageUpLimit
              (undefined *thisObject,int baseDamage,undefined *playerAction,undefined *mobAction,
              undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  longlong *plVar5;
  undefined *thisObject_00;
  longlong lVar6;
  
  if (DAT_7ffe9caddeda == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    DAT_7ffe9caddeda = '\x01';
  }
  if (((playerAction != (undefined *)0x0) &&
      (plVar5 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
      plVar5 != (longlong *)0x0)) &&
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
     thisObject_00 != (undefined *)0x0)) {
    bVar2 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x45,(undefined *)0x0);
    if (bVar2 == 0) {
      return baseDamage;
    }
    if (mobAction != (undefined *)0x0) {
      cVar3 = FUN_7ffe99749320(0x17,_DAT_7ffe9c9724e0,mobAction,0x10);
      if (cVar3 == '\0') {
        lVar6 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        if (lVar6 != 0) {
          iVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar6);
          iVar4 = (int)((float)iVar4 / _DAT_7ffe9c049cfc);
          if (iVar4 < 1) {
            iVar4 = 1;
          }
          if (baseDamage < iVar4) {
            iVar4 = baseDamage;
          }
          return iVar4;
        }
      }
      else {
        lVar6 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        if (lVar6 != 0) {
          iVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar6);
          iVar4 = (int)((float)iVar4 / _DAT_7ffe9c049cfc);
          if (iVar4 < 1) {
            iVar4 = 1;
          }
          if (iVar4 <= baseDamage) {
            return iVar4;
          }
          return baseDamage;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar4 = (*pcVar1)();
  return iVar4;
}

