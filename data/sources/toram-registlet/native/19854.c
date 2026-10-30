
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float GemCartBufferManager_GetLastDamageRate
                (undefined *self,undefined *status,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong *plVar4;
  float fVar5;
  float fVar6;
  undefined *puStackX_8;
  
  if (DAT_7ffe9cade79d == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9658b0);
    FUN_7ffe9996d590(&DAT_7ffe9c920330);
    FUN_7ffe9996d590(&DAT_7ffe9c923468);
    DAT_7ffe9cade79d = '\x01';
  }
  fVar5 = GemCartBufferManager_GetBufferValue(self,(undefined *)0x5,(undefined *)0x0);
  fVar6 = GemCartBufferManager_GetBufferValue(self,(undefined *)0x6,(undefined *)0x0);
  fVar6 = (fVar5 + 0.0) - fVar6;
  puStackX_8 = (undefined *)0x0;
  if (*(longlong *)(self + 0x18) != 0) {
    cVar2 = FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),0x1b,&puStackX_8,_DAT_7ffe9c9658b0);
    if (cVar2 != '\0') {
      if (status == (undefined *)0x0) goto LAB_7ffe9a5b25e4;
      plVar4 = (longlong *)
               (**(code **)(*(longlong *)status + 0x198))
                         (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
      if (plVar4 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c923468 + 0x130) <= *(byte *)(*plVar4 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*plVar4 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c923468 + 0x130) * 8) == _DAT_7ffe9c923468)) {
          if (puStackX_8 != (undefined *)0x0) {
            iVar3 = GemCartBufferBase_GetValue(puStackX_8,(undefined *)0x5,(undefined *)0x0);
            return fVar6 - (float)iVar3;
          }
          goto LAB_7ffe9a5b25e4;
        }
      }
      plVar4 = (longlong *)
               (**(code **)(*(longlong *)status + 0x198))
                         (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
      if (plVar4 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c920330 + 0x130) <= *(byte *)(*plVar4 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*plVar4 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c920330 + 0x130) * 8) == _DAT_7ffe9c920330)) {
          if (puStackX_8 == (undefined *)0x0) goto LAB_7ffe9a5b25e4;
          iVar3 = GemCartBufferBase_GetValue(puStackX_8,(undefined *)0x6,(undefined *)0x0);
          fVar6 = fVar6 + (float)iVar3;
        }
      }
    }
    return fVar6;
  }
LAB_7ffe9a5b25e4:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar5 = (float)(*pcVar1)();
  return fVar5;
}

