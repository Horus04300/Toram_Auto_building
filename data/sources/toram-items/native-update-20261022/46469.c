
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
SkillTextManager_GetSkillName(undefined *self,int skillId,undefined *key,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined8 unaff_RDI;
  
  if (DAT_7ffe9cad9df3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c905ba0);
    FUN_7ffe9996d590(&DAT_7ffe9c905d40);
    FUN_7ffe9996d590(&DAT_7ffe9c93a1c8);
    DAT_7ffe9cad9df3 = '\x01';
  }
  if (*(longlong *)(self + 0x18) != 0) {
    cVar2 = FUN_7ffe9ad24db0(*(longlong *)(self + 0x18),skillId,_DAT_7ffe9c905ba0);
    if (cVar2 == '\0') {
      return _DAT_7ffe9c93a1c8;
    }
    if (*(longlong *)(self + 0x18) != 0) {
      lVar3 = FUN_7ffe9ad356e0(*(longlong *)(self + 0x18),skillId,_DAT_7ffe9c905d40);
      if (lVar3 != 0) {
        if (DAT_7ffe9cad9dfb == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c93fe88,key,0);
          FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
          FUN_7ffe9996d590(&DAT_7ffe9c93a1c8);
          DAT_7ffe9cad9dfb = '\x01';
        }
        puVar4 = _DAT_7ffe9c8f1820;
        if (*(longlong *)(lVar3 + 0x28) != 0) {
          cVar2 = FUN_7ffe9adb0cf0(*(longlong *)(lVar3 + 0x28),key,&stack0x00000008,
                                   _DAT_7ffe9c93fe88,unaff_RDI);
          puVar5 = _DAT_7ffe9c93a1c8;
          if (cVar2 != '\0') {
            puVar5 = puVar4;
          }
          return puVar5;
        }
        return *(undefined **)(lVar3 + 0x18);
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar4 = (undefined *)(*pcVar1)();
  return puVar4;
}

