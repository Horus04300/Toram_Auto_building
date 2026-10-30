
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float SmokeDustAction_CalcBufferTime(undefined *status,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  undefined *puVar3;
  float fVar4;
  
  fVar4 = _DAT_7ffe9c049ce4;
  if (status != (undefined *)0x0) {
    puVar3 = (undefined *)
             (**(code **)(*(longlong *)status + 0x218))
                       (status,*(undefined8 *)(*(longlong *)status + 0x220));
    if (puVar3 != (undefined *)0x0) {
      puVar3 = GemCartBufferManager_GetGemCartBuffer(puVar3,0x12f,(undefined *)0x0);
      if (puVar3 != (undefined *)0x0) {
        iVar2 = GemCartBufferBase_GetValue(puVar3,(undefined *)0x2,(undefined *)0x0);
        fVar4 = (float)iVar2 + fVar4;
      }
      return fVar4;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar4 = (float)(*pcVar1)();
  return fVar4;
}

