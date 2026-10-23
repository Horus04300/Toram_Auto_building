
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
SkillTextManagerData_GetName(undefined *self,undefined *elementType,undefined *methodInfo)

{
  longlong lVar1;
  undefined8 uVar2;
  code *pcVar3;
  char cVar4;
  undefined *puVar5;
  undefined *puVar6;
  ulonglong uVar7;
  undefined8 unaff_RDI;
  
  if (DAT_7ffe9cad9dfa == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94bf18);
    FUN_7ffe9996d590(&DAT_7ffe9c93a1c8);
    DAT_7ffe9cad9dfa = '\x01';
  }
  uVar7 = 0;
  if ((char)elementType != '\b') {
    uVar7 = (ulonglong)elementType & 0xff;
  }
  if (*(int *)(_DAT_7ffe9c94bf18 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  if (**(longlong **)(_DAT_7ffe9c94bf18 + 0xb8) != 0) {
    if (*(int *)(**(longlong **)(_DAT_7ffe9c94bf18 + 0xb8) + 0x18) <= (int)(uint)uVar7) {
      return _DAT_7ffe9c93a1c8;
    }
    if (*(int *)(_DAT_7ffe9c94bf18 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    lVar1 = **(longlong **)(_DAT_7ffe9c94bf18 + 0xb8);
    if (lVar1 != 0) {
      if (*(uint *)(lVar1 + 0x18) <= (uint)uVar7) {
        FUN_7ffe9996d790();
        pcVar3 = (code *)swi(3);
        puVar5 = (undefined *)(*pcVar3)();
        return puVar5;
      }
      uVar2 = *(undefined8 *)(lVar1 + 0x20 + uVar7 * 8);
      if (DAT_7ffe9cad9dfb == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c93fe88,uVar2,0);
        FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
        FUN_7ffe9996d590(&DAT_7ffe9c93a1c8);
        DAT_7ffe9cad9dfb = '\x01';
      }
      puVar5 = _DAT_7ffe9c8f1820;
      if (*(longlong *)(self + 0x28) != 0) {
        cVar4 = FUN_7ffe9adb0cf0(*(longlong *)(self + 0x28),uVar2,&stack0x00000008,_DAT_7ffe9c93fe88
                                 ,unaff_RDI);
        puVar6 = _DAT_7ffe9c93a1c8;
        if (cVar4 != '\0') {
          puVar6 = puVar5;
        }
        return puVar6;
      }
      return *(undefined **)(self + 0x18);
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  puVar5 = (undefined *)(*pcVar3)();
  return puVar5;
}

