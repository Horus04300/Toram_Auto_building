
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
BonusManager_CreateBonusParameter
          (undefined *self,undefined *type,undefined *val,undefined *methodInfo)

{
  undefined2 uVar1;
  undefined2 uVar2;
  uint uVar3;
  longlong lVar4;
  code *pcVar5;
  longlong lVar6;
  undefined *puVar7;
  undefined8 uVar8;
  uint uVar9;
  
  if (DAT_7fff625e5873 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450498);
    FUN_7fff5f47d450(&DAT_7fff6240f5d0);
    FUN_7fff5f47d450(&DAT_7fff6240f500);
    FUN_7fff5f47d450(&DAT_7fff6246bec0);
    DAT_7fff625e5873 = '\x01';
  }
  if ((type != (undefined *)0x0) && (val != (undefined *)0x0)) {
    if (*(int *)(type + 0x18) == *(int *)(val + 0x18)) {
      puVar7 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6246bec0);
      FUN_7fff60a942f0(puVar7,*(undefined4 *)(type + 0x18),_DAT_7fff6240f500);
      uVar9 = 0;
      while ((int)uVar9 < (int)*(uint *)(type + 0x18)) {
        if (*(uint *)(type + 0x18) <= uVar9) {
LAB_7fff5fff4429:
          FUN_7fff5f47d650();
          pcVar5 = (code *)swi(3);
          puVar7 = (undefined *)(*pcVar5)();
          return puVar7;
        }
        uVar1 = *(undefined2 *)(type + (longlong)(int)uVar9 * 2 + 0x20);
        if (*(uint *)(val + 0x18) <= uVar9) goto LAB_7fff5fff4429;
        uVar2 = *(undefined2 *)(val + (longlong)(int)uVar9 * 2 + 0x20);
        uVar8 = func_0x7fff5f44ff00(_DAT_7fff62450498);
        FUN_7fff617759d0(uVar8,uVar1,uVar2,0);
        lVar6 = _DAT_7fff6240f5d0;
        if (puVar7 == (undefined *)0x0) goto LAB_7fff5fff4423;
        *(int *)(puVar7 + 0x1c) = *(int *)(puVar7 + 0x1c) + 1;
        lVar4 = *(longlong *)(puVar7 + 0x10);
        uVar3 = *(uint *)(puVar7 + 0x18);
        if (lVar4 == 0) goto LAB_7fff5fff4423;
        if (uVar3 < *(uint *)(lVar4 + 0x18)) {
          *(uint *)(puVar7 + 0x18) = uVar3 + 1;
          if (*(uint *)(lVar4 + 0x18) <= uVar3) goto LAB_7fff5fff4429;
          *(undefined8 *)(lVar4 + (longlong)(int)uVar3 * 8 + 0x20) = uVar8;
          thunk_FUN_7fff5f491fd0();
          uVar9 = uVar9 + 1;
        }
        else {
          FUN_7fff60adfc70(puVar7,uVar8,
                           *(undefined8 *)(*(longlong *)(*(longlong *)(lVar6 + 0x20) + 0xc0) + 0x70)
                          );
          uVar9 = uVar9 + 1;
        }
      }
    }
    else {
      puVar7 = (undefined *)0x0;
    }
    return puVar7;
  }
LAB_7fff5fff4423:
  FUN_7fff5f47d660();
  pcVar5 = (code *)swi(3);
  puVar7 = (undefined *)(*pcVar5)();
  return puVar7;
}

