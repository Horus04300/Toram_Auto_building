
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
  
  if (DAT_7fff625e156f == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6240cbd0);
    FUN_7fff5f47d450(&DAT_7fff6240cd70);
    FUN_7fff5f47d450(&DAT_7fff624408b0);
    DAT_7fff625e156f = '\x01';
  }
  if (*(longlong *)(self + 0x18) != 0) {
    cVar2 = FUN_7fff6082f170(*(longlong *)(self + 0x18),skillId,_DAT_7fff6240cbd0);
    if (cVar2 == '\0') {
      return _DAT_7fff624408b0;
    }
    if (*(longlong *)(self + 0x18) != 0) {
      lVar3 = FUN_7fff6083faa0(*(longlong *)(self + 0x18),skillId,_DAT_7fff6240cd70);
      if (lVar3 != 0) {
        if (DAT_7fff625e1577 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff62446dd8,key,0);
          FUN_7fff5f47d450(&DAT_7fff623f7f60);
          FUN_7fff5f47d450(&DAT_7fff624408b0);
          DAT_7fff625e1577 = '\x01';
        }
        puVar4 = _DAT_7fff623f7f60;
        if (*(longlong *)(lVar3 + 0x28) != 0) {
          cVar2 = FUN_7fff608bb0b0(*(longlong *)(lVar3 + 0x28),key,&stack0x00000008,
                                   _DAT_7fff62446dd8,unaff_RDI);
          puVar5 = _DAT_7fff624408b0;
          if (cVar2 != '\0') {
            puVar5 = puVar4;
          }
          return puVar5;
        }
        return *(undefined **)(lVar3 + 0x18);
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar4 = (undefined *)(*pcVar1)();
  return puVar4;
}

