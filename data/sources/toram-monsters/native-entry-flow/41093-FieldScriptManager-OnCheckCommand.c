
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FieldScriptManager_OnCheckCommand(undefined *self,undefined *command,undefined *methodInfo)

{
  int *piVar1;
  undefined *self_00;
  code *pcVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  
  if (*(undefined **)(self + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa1802a;
  bVar3 = FieldScriptLoader_ReadByte(*(undefined **)(self + 0x40),(undefined *)0x0);
  if (*(undefined **)(self + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa1802a;
  bVar4 = FieldScriptLoader_ReadByte(*(undefined **)(self + 0x40),(undefined *)0x0);
  if (*(undefined **)(self + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa1802a;
  uVar5 = FieldScriptLoader_ReadInt(*(undefined **)(self + 0x40),bVar4 >> 7,(undefined *)0x0);
  if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe9aa1802a;
  uVar6 = FUN_7ffe9a9fa880(*(longlong *)(self + 0x40),bVar3,0);
  switch(bVar4 & 0xf) {
  case 0:
  case 9:
    bVar8 = uVar6 == uVar5;
    break;
  default:
    goto LAB_7ffe9aa17ff2;
  case 5:
    bVar8 = (int)uVar5 <= (int)uVar6;
    break;
  case 6:
    bVar8 = (int)uVar6 <= (int)uVar5;
    break;
  case 7:
  case 0xc:
    bVar8 = uVar6 != uVar5;
    break;
  case 8:
    bVar8 = uVar6 == 0 && uVar5 == 0;
    goto code_r0x7ffe9aa17feb;
  case 10:
    bVar8 = (int)uVar6 < (int)uVar5;
    break;
  case 0xb:
    bVar8 = (int)uVar5 < (int)uVar6;
    break;
  case 0xd:
    bVar8 = (uVar5 & uVar6) == 0;
    goto code_r0x7ffe9aa17feb;
  case 0xe:
    bVar8 = uVar6 == uVar5;
code_r0x7ffe9aa17feb:
    bVar8 = !bVar8;
  }
  if (!bVar8) {
LAB_7ffe9aa17ff2:
    if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe9aa1802a;
    piVar1 = (int *)(*(longlong *)(self + 0x40) + 0x2c);
    *piVar1 = *piVar1 + 4;
  }
  self_00 = *(undefined **)(self + 0x40);
  if (self_00 != (undefined *)0x0) {
    iVar7 = FieldScriptLoader_ReadInt(self_00,(undefined *)0x0);
    *(int *)(self_00 + 0x2c) = iVar7;
    return;
  }
LAB_7ffe9aa1802a:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

