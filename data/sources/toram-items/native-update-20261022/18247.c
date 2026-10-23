
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * ItemManager_GetItemEquipedType(undefined *self,int uuid,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  undefined *puVar3;
  
  lVar1 = *(longlong *)(self + 0x20);
  if (lVar1 == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    puVar3 = (undefined *)(*pcVar2)();
    return puVar3;
  }
  if (*(int *)(lVar1 + 0x20) == uuid) {
    return (undefined *)0x1;
  }
  if (*(int *)(lVar1 + 0x24) == uuid) {
    return (undefined *)0x2;
  }
  if (*(int *)(lVar1 + 0x28) != uuid) {
    if (*(int *)(lVar1 + 0x2c) == uuid) {
      return (undefined *)0x4;
    }
    if (*(int *)(lVar1 + 0x30) != uuid) {
      puVar3 = (undefined *)0x6;
      if (*(int *)(lVar1 + 0x34) != uuid) {
        puVar3 = (undefined *)0x0;
      }
      return puVar3;
    }
    return (undefined *)0x5;
  }
  return (undefined *)0x3;
}

