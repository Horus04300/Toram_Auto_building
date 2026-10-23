
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte FunctionLimitManager_GetValue
               (undefined *self,undefined *limitedType,undefined *param,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  longlong lStackX_8;
  
  lVar1 = *(longlong *)(self + 0x28);
  if (DAT_7fff625e75aa == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fd260);
    DAT_7fff625e75aa = '\x01';
  }
  *(undefined4 *)param = 0;
  lStackX_8 = 0;
  if (lVar1 != 0) {
    cVar3 = FUN_7fff60862d70(lVar1,(ulonglong)limitedType & 0xffffffff,&lStackX_8,_DAT_7fff623fd260)
    ;
    if ((cVar3 != '\0') && (lStackX_8 != 0)) {
      *(undefined4 *)param = *(undefined4 *)(lStackX_8 + 0x28);
      return 1;
    }
    return 0;
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  bVar4 = (*pcVar2)();
  return bVar4;
}

