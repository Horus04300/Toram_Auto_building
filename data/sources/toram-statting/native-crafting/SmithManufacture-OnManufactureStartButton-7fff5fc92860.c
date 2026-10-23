
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithManufacture_OnManufactureStartButton(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  uint uVar9;
  
  if (DAT_7fff625e4298 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62436790);
    FUN_7fff5f47d450(&DAT_7fff6244eec0);
    FUN_7fff5f47d450(&DAT_7fff62401e80);
    FUN_7fff5f47d450(&DAT_7fff62473dd0);
    FUN_7fff5f47d450(&DAT_7fff62416c98);
    DAT_7fff625e4298 = '\x01';
  }
  if (*(longlong *)(self + 200) != 0) {
    FUN_7fff5f63f5a0(*(longlong *)(self + 200),0);
    if ((*(longlong *)(self + 0x70) != 0) &&
       (lVar4 = *(longlong *)(*(longlong *)(self + 0x70) + 0x20), lVar4 != 0)) {
      lVar4 = FUN_7fff60678610(lVar4,_DAT_7fff6244eec0);
      if (lVar4 != 0) {
        uVar9 = 0;
        *(undefined4 *)(lVar4 + 0x2c) = 0x3f800000;
        *(undefined4 *)(lVar4 + 0x28) = 0;
        plVar5 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62416c98,4);
        do {
          if (*(longlong *)(self + 0x1d0) == 0) goto LAB_7fff5fc92a58;
          lVar4 = FUN_7fff60a94f50(*(longlong *)(self + 0x1d0),uVar9 + *(int *)(self + 0x168) * 4);
          if (plVar5 == (longlong *)0x0) goto LAB_7fff5fc92a58;
          if (lVar4 != 0) {
            lVar6 = func_0x7fff5f47c7e0(lVar4,*(undefined8 *)(*plVar5 + 0x40));
            if (lVar6 == 0) {
              uVar7 = func_0x7fff5f47d0b0();
              FUN_7fff5f47d620(uVar7,0);
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
          }
          if (*(uint *)(plVar5 + 3) <= uVar9) {
            FUN_7fff5f47d650();
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          plVar5[(longlong)(int)uVar9 + 4] = lVar4;
          thunk_FUN_7fff5f491fd0();
          uVar9 = uVar9 + 1;
        } while ((int)uVar9 < 4);
        bVar2 = SmithManufacture_isSkipType(self,*(int *)(self + 0x160),(undefined *)0x0);
        plVar5 = *(longlong **)(self + 0x28);
        if (plVar5 != (longlong *)0x0) {
          (**(code **)(*plVar5 + 0x1e8))
                    (plVar5,3 - (uint)(bVar2 != 0),*(undefined8 *)(*plVar5 + 0x1f0));
          plVar5 = *(longlong **)(self + 0x28);
          uVar7 = func_0x7fff5f44ff00(_DAT_7fff62436790);
          FUN_7fff5f4f6880(uVar7,self,_DAT_7fff62473dd0,0);
          if (plVar5 != (longlong *)0x0) {
            (**(code **)(*plVar5 + 0x1c8))(plVar5,uVar7,*(undefined8 *)(*plVar5 + 0x1d0));
            lVar4 = (**(code **)(*(longlong *)self + 0x238))
                              (self,*(undefined8 *)(*(longlong *)self + 0x240));
            if (lVar4 == 0) {
              uVar7 = func_0x7fff5f47d470(0x7fff6240da20,0,0);
              uVar7 = func_0x7fff5f44ff00(uVar7);
              uVar8 = func_0x7fff5f47d470(0x7fff62447258);
              FUN_7fff61012af0(uVar7,uVar8,0);
              uVar8 = func_0x7fff5f47d470(0x7fff624343d8);
              FUN_7fff5f47d620(uVar7,uVar8);
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            if (_DAT_7fff625f0f98 == (code *)0x0) {
              _DAT_7fff625f0f98 = (code *)FUN_7fff5f47d6c0(&UNK_7fff61c3cbf0);
            }
            cVar3 = (*_DAT_7fff625f0f98)(self);
            if (cVar3 != '\0') {
              if (_DAT_7fff625f0fa8 == (code *)0x0) {
                _DAT_7fff625f0fa8 = (code *)FUN_7fff5f47d6c0(&UNK_7fff61c3cc90);
              }
                    /* WARNING: Could not recover jumptable at 0x7fff618a882c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
              (*_DAT_7fff625f0fa8)(self,lVar4);
              return;
            }
            uVar7 = func_0x7fff5f47d470(&DAT_7fff6243cee8);
            uVar7 = func_0x7fff5f44ff00(uVar7);
            uVar8 = func_0x7fff5f47d470(0x7fff62415fc8);
            FUN_7fff60f8bb30(uVar7,uVar8,0);
            uVar8 = func_0x7fff5f47d470(0x7fff624343d8);
            FUN_7fff5f47d620(uVar7,uVar8);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
        }
      }
    }
  }
LAB_7fff5fc92a58:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

