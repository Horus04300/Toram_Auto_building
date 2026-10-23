
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIStatusBar_SetMaxPoint(undefined *self,byte isLimitBreak,undefined *methodInfo)

{
  int iVar1;
  int iVar2;
  longlong *plVar3;
  longlong lVar4;
  code *pcVar5;
  char cVar6;
  longlong lVar7;
  int *piVar8;
  undefined8 unaff_RDI;
  undefined8 in_R9;
  
  if (DAT_7fff625e3c59 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62478a78);
    DAT_7fff625e3c59 = '\x01';
  }
  if (isLimitBreak == 0) {
    if (*(int *)(_DAT_7fff62478a78 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff62478a78);
    }
    piVar8 = *(int **)(_DAT_7fff62478a78 + 0xb8);
  }
  else {
    if (*(int *)(_DAT_7fff62478a78 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff62478a78);
    }
    piVar8 = (int *)(*(longlong *)(_DAT_7fff62478a78 + 0xb8) + 4);
  }
  if (self != (undefined *)0x0) {
    iVar1 = *piVar8;
    *(int *)(self + 0x6c) = iVar1;
    iVar2 = *(int *)(self + 0x68);
    if (*(longlong *)(self + 0x20) != 0) {
      if (iVar1 <= iVar2) {
        iVar2 = iVar1;
      }
      func_0x7fff5f509ce0(*(longlong *)(self + 0x20),(float)iVar2 / (float)iVar1,0);
      plVar3 = *(longlong **)(self + 0x38);
      lVar7 = FUN_7fff6100e780(self + 0x68,0);
      if (plVar3 != (longlong *)0x0) {
        if (DAT_7fff625e5260 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff6240e4b0,lVar7,0,in_R9,unaff_RDI);
          FUN_7fff5f47d450(&DAT_7fff623f7f60);
          DAT_7fff625e5260 = '\x01';
        }
        cVar6 = func_0x7fff60e76090(lVar7,0);
        if (cVar6 == '\0') {
          cVar6 = FUN_7fff60e7b970(plVar3[0x23],lVar7,0);
          if (cVar6 != '\0') {
            plVar3[0x23] = lVar7;
            thunk_FUN_7fff5f491fd0();
            *(undefined1 *)(plVar3 + 0xb) = 1;
            *(undefined1 *)((longlong)plVar3 + 0x161) = 1;
            lVar4 = plVar3[0x22];
            if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
              func_0x7fff5f47d6f0();
            }
            cVar6 = FUN_7fff618ab2e0(lVar4,0,0);
            if (cVar6 != '\0') {
              if (plVar3[0x22] == 0) {
                FUN_7fff5f47d660();
                pcVar5 = (code *)swi(3);
                (*pcVar5)();
                return;
              }
              FUN_7fff5ff06840(plVar3[0x22],lVar7,0);
            }
            if (*(int *)((longlong)plVar3 + 0x14c) == 0) {
                    /* WARNING: Could not recover jumptable at 0x7fff5ff0efc3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
              (**(code **)(*plVar3 + 0x2b8))(plVar3,*(undefined8 *)(*plVar3 + 0x2c0));
              return;
            }
          }
        }
        else {
          cVar6 = func_0x7fff60e76090(plVar3[0x23],0);
          if (cVar6 == '\0') {
            plVar3[0x23] = _DAT_7fff623f7f60;
            thunk_FUN_7fff5f491fd0();
          }
          *(undefined1 *)(plVar3 + 0xb) = 1;
          *(undefined1 *)((longlong)plVar3 + 0x161) = 1;
        }
        return;
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

