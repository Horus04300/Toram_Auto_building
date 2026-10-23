
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int UIBuildPanel_GetOverBuildPoint(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong *plVar3;
  longlong lVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  if (DAT_7fff625e3c22 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62478a78);
    DAT_7fff625e3c22 = '\x01';
  }
  if (*(undefined **)(self + 0xd0) != (undefined *)0x0) {
    plVar3 = (longlong *)
             PlayerDataManager_get_PlayerStatus(*(undefined **)(self + 0xd0),(undefined *)0x0);
    if (plVar3 != (longlong *)0x0) {
      lVar4 = (**(code **)(*plVar3 + 0x188))(plVar3,*(undefined8 *)(*plVar3 + 400));
      if (lVar4 != 0) {
        iVar7 = *(int *)(lVar4 + 0x14);
        if (*(int *)(_DAT_7fff62478a78 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(_DAT_7fff62478a78);
        }
        iVar2 = **(int **)(_DAT_7fff62478a78 + 0xb8);
        iVar7 = iVar7 - iVar2;
        iVar9 = *(int *)(lVar4 + 0x18) - iVar2;
        iVar8 = *(int *)(lVar4 + 0x1c) - iVar2;
        iVar6 = *(int *)(lVar4 + 0x20) - iVar2;
        iVar2 = *(int *)(lVar4 + 0x24) - iVar2;
        iVar5 = 0;
        if (iVar7 < 1) {
          iVar7 = iVar5;
        }
        if (iVar2 < 1) {
          iVar2 = iVar5;
        }
        if (iVar6 < 1) {
          iVar6 = iVar5;
        }
        if (iVar8 < 1) {
          iVar8 = iVar5;
        }
        if (iVar9 < 1) {
          iVar9 = iVar5;
        }
        return iVar2 + iVar7 + iVar6 + iVar8 + iVar9;
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar7 = (*pcVar1)();
  return iVar7;
}

