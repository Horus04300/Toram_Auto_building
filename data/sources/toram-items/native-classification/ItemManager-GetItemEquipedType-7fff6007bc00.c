
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ItemManager_GetItemEquipedType(undefined *self,int uuid,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  
  lVar1 = *(longlong *)(self + 0x20);
  if (lVar1 == 0) {
    FUN_7fff5f47d660();
    pcVar2 = (code *)swi(3);
    iVar3 = (*pcVar2)();
    return iVar3;
  }
  if (*(int *)(lVar1 + 0x20) == uuid) {
    return 1;
  }
  if (*(int *)(lVar1 + 0x24) == uuid) {
    return 2;
  }
  if (*(int *)(lVar1 + 0x28) != uuid) {
    if (*(int *)(lVar1 + 0x2c) == uuid) {
      return 4;
    }
    if (*(int *)(lVar1 + 0x30) != uuid) {
      iVar3 = 6;
      if (*(int *)(lVar1 + 0x34) != uuid) {
        iVar3 = 0;
      }
      return iVar3;
    }
    return 5;
  }
  return 3;
}

