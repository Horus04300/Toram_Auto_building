
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * SkillTextManagerData_GetName(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  undefined8 uVar2;
  code *pcVar3;
  char cVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined8 unaff_RDI;
  
  if (DAT_7fff625e1576 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62453610,0,0);
    FUN_7fff5f47d450(&DAT_7fff624408b0);
    DAT_7fff625e1576 = '\x01';
  }
  if (*(int *)(_DAT_7fff62453610 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  if (**(longlong **)(_DAT_7fff62453610 + 0xb8) != 0) {
    if (*(int *)(**(longlong **)(_DAT_7fff62453610 + 0xb8) + 0x18) < 1) {
      return _DAT_7fff624408b0;
    }
    if (*(int *)(_DAT_7fff62453610 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    lVar1 = **(longlong **)(_DAT_7fff62453610 + 0xb8);
    if (lVar1 != 0) {
      if (*(int *)(lVar1 + 0x18) == 0) {
        FUN_7fff5f47d650();
        pcVar3 = (code *)swi(3);
        puVar5 = (undefined *)(*pcVar3)();
        return puVar5;
      }
      uVar2 = *(undefined8 *)(lVar1 + 0x20);
      if (DAT_7fff625e1577 == '\0') {
        FUN_7fff5f47d450(&DAT_7fff62446dd8,uVar2,0);
        FUN_7fff5f47d450(&DAT_7fff623f7f60);
        FUN_7fff5f47d450(&DAT_7fff624408b0);
        DAT_7fff625e1577 = '\x01';
      }
      puVar5 = _DAT_7fff623f7f60;
      if (*(longlong *)(self + 0x28) == 0) {
        return *(undefined **)(self + 0x18);
      }
      cVar4 = FUN_7fff608bb0b0(*(longlong *)(self + 0x28),uVar2,&stack0x00000008,_DAT_7fff62446dd8,
                               unaff_RDI);
      puVar6 = _DAT_7fff624408b0;
      if (cVar4 != '\0') {
        puVar6 = puVar5;
      }
      return puVar6;
    }
  }
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  puVar5 = (undefined *)(*pcVar3)();
  return puVar5;
}

