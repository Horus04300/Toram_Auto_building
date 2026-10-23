
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * SkillTextManagerData_GetName(undefined *self,int elementType,undefined *methodInfo)

{
  longlong lVar1;
  undefined8 uVar2;
  code *pcVar3;
  uint uVar4;
  char cVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined8 unaff_RDI;
  
  if (DAT_7fff625e1576 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62453610);
    FUN_7fff5f47d450(&DAT_7fff624408b0);
    DAT_7fff625e1576 = '\x01';
  }
  uVar4 = 0;
  if ((char)elementType != '\b') {
    uVar4 = elementType & 0xff;
  }
  if (*(int *)(_DAT_7fff62453610 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  if (**(longlong **)(_DAT_7fff62453610 + 0xb8) != 0) {
    if (*(int *)(**(longlong **)(_DAT_7fff62453610 + 0xb8) + 0x18) <= (int)uVar4) {
      return _DAT_7fff624408b0;
    }
    if (*(int *)(_DAT_7fff62453610 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    lVar1 = **(longlong **)(_DAT_7fff62453610 + 0xb8);
    if (lVar1 != 0) {
      if (*(uint *)(lVar1 + 0x18) <= uVar4) {
        FUN_7fff5f47d650();
        pcVar3 = (code *)swi(3);
        puVar6 = (undefined *)(*pcVar3)();
        return puVar6;
      }
      uVar2 = *(undefined8 *)(lVar1 + 0x20 + (ulonglong)uVar4 * 8);
      if (DAT_7fff625e1577 == '\0') {
        FUN_7fff5f47d450(&DAT_7fff62446dd8,uVar2,0);
        FUN_7fff5f47d450(&DAT_7fff623f7f60);
        FUN_7fff5f47d450(&DAT_7fff624408b0);
        DAT_7fff625e1577 = '\x01';
      }
      puVar6 = _DAT_7fff623f7f60;
      if (*(longlong *)(self + 0x28) != 0) {
        cVar5 = FUN_7fff608bb0b0(*(longlong *)(self + 0x28),uVar2,&stack0x00000008,_DAT_7fff62446dd8
                                 ,unaff_RDI);
        puVar7 = _DAT_7fff624408b0;
        if (cVar5 != '\0') {
          puVar7 = puVar6;
        }
        return puVar7;
      }
      return *(undefined **)(self + 0x18);
    }
  }
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  puVar6 = (undefined *)(*pcVar3)();
  return puVar6;
}

