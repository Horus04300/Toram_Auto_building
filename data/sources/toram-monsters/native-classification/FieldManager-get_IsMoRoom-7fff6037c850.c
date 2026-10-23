
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte FieldManager_get_IsMoRoom(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  byte bVar3;
  
  lVar1 = *(longlong *)(self + 0x28);
  if (lVar1 == 0) {
    FUN_7fff5f47d660();
    pcVar2 = (code *)swi(3);
    bVar3 = (*pcVar2)();
    return bVar3;
  }
  if (((((*(int *)(lVar1 + 0x2c) != 2) && (*(int *)(lVar1 + 0x2c) != 0xe)) &&
       (*(int *)(lVar1 + 0x2c) != 0x1d)) &&
      (((*(int *)(lVar1 + 0x2c) != 3 && (*(int *)(lVar1 + 0x2c) != 4)) &&
       ((*(int *)(lVar1 + 0x2c) != 8 &&
        ((*(int *)(lVar1 + 0x2c) != 0x12 && (*(int *)(lVar1 + 0x2c) != 0x13)))))))) &&
     ((*(int *)(lVar1 + 0x2c) != 0x19 &&
      (((((*(int *)(lVar1 + 0x2c) != 0x1a && (*(int *)(lVar1 + 0x2c) != 0x1c)) &&
         (*(int *)(lVar1 + 0x2c) != 0x20)) &&
        ((*(int *)(lVar1 + 0x2c) != 0x23 && (*(int *)(lVar1 + 0x2c) != 0x27)))) &&
       ((*(int *)(lVar1 + 0x2c) != 0x28 && (*(int *)(lVar1 + 0x2c) != 0x29)))))))) {
    return 0;
  }
  return 1;
}

