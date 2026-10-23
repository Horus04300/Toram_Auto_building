
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
  
  lVar1 = *(longlong *)(self + 0x20);
  if (DAT_7ffe9cadfe53 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f6230);
    DAT_7ffe9cadfe53 = '\x01';
  }
  *(undefined4 *)param = 0;
  lStackX_8 = 0;
  if (lVar1 != 0) {
    cVar3 = FUN_7ffe9ad589b0(lVar1,(ulonglong)limitedType & 0xffffffff,&lStackX_8,_DAT_7ffe9c8f6230)
    ;
    if ((cVar3 != '\0') && (lStackX_8 != 0)) {
      *(undefined4 *)param = *(undefined4 *)(lStackX_8 + 0x28);
      return 1;
    }
    return 0;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar4 = (*pcVar2)();
  return bVar4;
}

