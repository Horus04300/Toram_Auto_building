
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float GemCartBufferManager_GetBufferValue(undefined *self,undefined *id,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  char cVar3;
  int iVar4;
  float fVar5;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  longlong *plStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  longlong *plStack_40;
  undefined8 uStack_38;
  
  if (DAT_7ffe9cade79b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c965718);
    FUN_7ffe9996d590(&DAT_7ffe9c92ea20);
    FUN_7ffe9996d590(&DAT_7ffe9c92eae0);
    FUN_7ffe9996d590(0x7ffe9c92eba8);
    FUN_7ffe9996d590(0x7ffe9c9676b8);
    DAT_7ffe9cade79b = '\x01';
  }
  fVar5 = 0.0;
  if (*(longlong *)(self + 0x18) == 0) {
    FUN_7ffe9996d7a0();
  }
  else {
    FUN_7ffe9accf860(&uStack_58,*(longlong *)(self + 0x18),_DAT_7ffe9c965718);
    uStack_80 = uStack_58;
    uStack_78 = uStack_50;
    uStack_70 = uStack_48;
    plStack_68 = plStack_40;
    uStack_60 = uStack_38;
    while( true ) {
      cVar3 = FUN_7ffe9ae385a0(&uStack_80,_DAT_7ffe9c92eae0);
      plVar2 = plStack_68;
      if (cVar3 == '\0') {
        func_0x7ffe999c3920(&uStack_80,_DAT_7ffe9c92ea20);
        return fVar5;
      }
      if (plStack_68 == (longlong *)0x0) break;
      iVar4 = (**(code **)(*plStack_68 + 0x1d8))
                        (plStack_68,(ulonglong)id & 0xffffffff,*(undefined8 *)(*plStack_68 + 0x1e0))
      ;
      if ((iVar4 == 0) || (0.0 < *(float *)(plVar2 + 2))) {
LAB_7ffe9a5b230b:
        iVar4 = 0;
      }
      else {
        cVar3 = (**(code **)(*plVar2 + 0x1c8))(plVar2,*(undefined8 *)(*plVar2 + 0x1d0));
        if (cVar3 == '\0') goto LAB_7ffe9a5b230b;
      }
      fVar5 = fVar5 + (float)iVar4;
    }
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  fVar5 = (float)(*pcVar1)();
  return fVar5;
}

