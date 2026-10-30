
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerAttackBase_CheckGemCartEmergencyMpRecovery
               (undefined *thisObject,undefined *status,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  undefined *thisObject_00;
  
  if (DAT_7ffe9caddee1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9caddee1 = '\x01';
  }
  if (status != (undefined *)0x0) {
    lVar5 = (**(code **)(*(longlong *)status + 0x218))
                      (status,*(undefined8 *)(*(longlong *)status + 0x220));
    if (lVar5 != 0) {
      thisObject_00 =
           (undefined *)
           (**(code **)(*(longlong *)status + 0x218))
                     (status,*(undefined8 *)(*(longlong *)status + 0x220));
      if (thisObject_00 == (undefined *)0x0) {
LAB_7ffe9a4ac947:
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        bVar2 = (*pcVar1)();
        return bVar2;
      }
      bVar2 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x1e,(undefined *)0x0);
      if (bVar2 != 0) {
        lVar5 = (**(code **)(*(longlong *)status + 0x198))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
        if (lVar5 == 0) goto LAB_7ffe9a4ac947;
        iVar3 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c940d40,lVar5);
        iVar4 = (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if (iVar4 <= iVar3) {
          *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 0x800;
          return 1;
        }
      }
    }
  }
  return 0;
}

