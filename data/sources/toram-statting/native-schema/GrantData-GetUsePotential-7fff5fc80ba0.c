
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GrantData_GetUsePotential(int key,int itemUuid,undefined *playerData,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  int aiStack_38 [9];
  int iStack_14;
  
  if (DAT_7fff625e424a == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244ce08);
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    DAT_7fff625e424a = '\x01';
  }
  if ((playerData != (undefined *)0x0) && (lVar4 = FUN_7fff5ff8a8a0(playerData,0), lVar4 != 0)) {
    lVar4 = FUN_7fff6007b880(lVar4,itemUuid,0);
    if (lVar4 == 0) {
      return 9999;
    }
    if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff62420f50);
    }
    if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
      FUN_7fff6088c670(aiStack_38,**(longlong **)(_DAT_7fff62420f50 + 0xb8),key,_DAT_7fff6244ce08);
      if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
        FUN_7fff6088c670(aiStack_38,**(longlong **)(_DAT_7fff62420f50 + 0xb8),key,_DAT_7fff6244ce08)
        ;
        if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
          FUN_7fff6088c670(aiStack_38,**(longlong **)(_DAT_7fff62420f50 + 0xb8),key,
                           _DAT_7fff6244ce08);
          cVar2 = func_0x7fff5fc6d340(*(undefined4 *)(lVar4 + 0x38),0);
          if ((cVar2 == '\0') || (iStack_14 != 1)) {
            cVar2 = FUN_7fff5fc6d540(*(undefined4 *)(lVar4 + 0x34),0);
            if (cVar2 == '\0') {
              return aiStack_38[0];
            }
            if (iStack_14 != 2) {
              return aiStack_38[0];
            }
          }
          return aiStack_38[0] * 2;
        }
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar3 = (*pcVar1)();
  return iVar3;
}

