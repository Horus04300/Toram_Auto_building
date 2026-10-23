
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusData__ctor(undefined *self,undefined *bonusLines,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  ushort uVar3;
  undefined8 uVar4;
  undefined *self_00;
  longlong *plVar5;
  undefined8 *puVar6;
  longlong lVar7;
  longlong lVar8;
  
  if (DAT_7fff625e584b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244ff38);
    FUN_7fff5f47d450(&DAT_7fff62450498);
    FUN_7fff5f47d450(&DAT_7fff62450620);
    FUN_7fff5f47d450(&DAT_7fff6245c820);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff6245ad90);
    FUN_7fff5f47d450(&DAT_7fff624605f0);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    FUN_7fff5f47d450(&DAT_7fff6240fec0);
    FUN_7fff5f47d450(&DAT_7fff6240f5d0);
    FUN_7fff5f47d450(&DAT_7fff62410060);
    FUN_7fff5f47d450(&DAT_7fff62451f28);
    FUN_7fff5f47d450(&DAT_7fff6240f360);
    FUN_7fff5f47d450(&DAT_7fff6240fd20);
    FUN_7fff5f47d450(&DAT_7fff62478730);
    FUN_7fff5f47d450(&DAT_7fff6246bec0);
    FUN_7fff5f47d450(&DAT_7fff6246bf90);
    DAT_7fff625e584b = '\x01';
  }
  uVar4 = func_0x7fff5f44ff00(_DAT_7fff6246bf90);
  FUN_7fff60a943d0(uVar4,_DAT_7fff6240fd20);
  *(undefined8 *)(self + 0x18) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f44ff00(_DAT_7fff62478730);
  FUN_7fff60a943d0(uVar4,_DAT_7fff62451f28);
  *(undefined8 *)(self + 0x20) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f44ff00(_DAT_7fff6246bf90);
  FUN_7fff60a943d0(uVar4,_DAT_7fff6240fd20);
  *(undefined8 *)(self + 0x28) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f44ff00(_DAT_7fff6246bec0);
  FUN_7fff60a943d0(uVar4,_DAT_7fff6240f360);
  *(undefined8 *)(self + 0x30) = uVar4;
  thunk_FUN_7fff5f491fd0();
  uVar4 = func_0x7fff5f44ff00(_DAT_7fff6246bec0);
  FUN_7fff60a943d0(uVar4,_DAT_7fff6240f360);
  *(undefined8 *)(self + 0x38) = uVar4;
  thunk_FUN_7fff5f491fd0();
  MainPlayer_OnSkillDelayStandbyOk(self,0,methodInfo);
  self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62450620);
  BonusScriptData__ctor(self_00,bonusLines,(undefined *)0x0);
  *(undefined **)(self + 0x10) = self_00;
  thunk_FUN_7fff5f491fd0();
  *(undefined4 *)(self + 0x44) = 0;
  self[0x40] = 0;
  if ((*(longlong *)(self + 0x10) == 0) || (*(longlong *)(*(longlong *)(self + 0x10) + 0x28) == 0))
  {
    FUN_7fff5f47d660();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  plVar5 = (longlong *)FUN_7fff5f252ec0(0,_DAT_7fff6245ad90);
  do {
    if (plVar5 == (longlong *)0x0) {
LAB_7fff5fff2cc6:
      FUN_7fff5f47d660();
      FUN_7fff5f40a410();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    cVar2 = FUN_7fff5f252ec0(0,_DAT_7fff62442498);
    if (cVar2 == '\0') {
      if (plVar5 != (longlong *)0x0) {
        FUN_7fff5f253010(0,_DAT_7fff624413c0);
      }
      return;
    }
    if (plVar5 == (longlong *)0x0) {
LAB_7fff5fff2cc1:
      FUN_7fff5f47d660();
      goto LAB_7fff5fff2cc6;
    }
    lVar7 = *plVar5;
    uVar3 = 0;
    if (*(ushort *)(lVar7 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar7 + 0xb0) + (ulonglong)uVar3 * 0x10) ==
            _DAT_7fff624605f0) {
          puVar6 = (undefined8 *)
                   (lVar7 + 0x138 +
                   (longlong)*(int *)(*(longlong *)(lVar7 + 0xb0) + 8 + (ulonglong)uVar3 * 0x10) *
                   0x10);
          goto LAB_7fff5fff2889;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(ushort *)(lVar7 + 0x12e));
    }
    puVar6 = (undefined8 *)FUN_7fff5f3de400(plVar5,_DAT_7fff624605f0,0);
LAB_7fff5fff2889:
    lVar7 = (*(code *)*puVar6)(plVar5,puVar6[1]);
    if (*(int *)(_DAT_7fff6244ff38 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff6244ff38);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x30);
    if (lVar8 == 0) {
LAB_7fff5fff2cbc:
      FUN_7fff5f47d660();
      goto LAB_7fff5fff2cc1;
    }
    lVar8 = FUN_7fff6087c780(lVar8,0,_DAT_7fff6245c820);
    if (lVar7 == 0) {
LAB_7fff5fff2cb7:
      FUN_7fff5f47d660();
      goto LAB_7fff5fff2cbc;
    }
    if (lVar8 == 0) {
LAB_7fff5fff2cb2:
      FUN_7fff5f47d660();
      goto LAB_7fff5fff2cb7;
    }
    cVar2 = FUN_7fff60ad2d00(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7fff62410060);
    if (cVar2 != '\0') {
      if (*(longlong *)(self + 0x18) != 0) {
        FUN_7fff5f254640(*(longlong *)(self + 0x18),*(undefined4 *)(lVar7 + 0x10),_DAT_7fff6240fec0)
        ;
        goto LAB_7fff5fff291d;
      }
      FUN_7fff5f47d660();
LAB_7fff5fff2c6c:
      FUN_7fff5f47d660();
LAB_7fff5fff2c71:
      FUN_7fff5f47d660();
LAB_7fff5fff2c76:
      FUN_7fff5f47d660();
LAB_7fff5fff2c7b:
      FUN_7fff5f47d660();
LAB_7fff5fff2c80:
      FUN_7fff5f47d660();
LAB_7fff5fff2c85:
      FUN_7fff5f47d660();
LAB_7fff5fff2c8a:
      FUN_7fff5f47d660();
LAB_7fff5fff2c8f:
      FUN_7fff5f47d660();
LAB_7fff5fff2c94:
      FUN_7fff5f47d660();
LAB_7fff5fff2c99:
      FUN_7fff5f47d660();
LAB_7fff5fff2c9e:
      FUN_7fff5f47d660();
LAB_7fff5fff2ca3:
      FUN_7fff5f47d660();
LAB_7fff5fff2ca8:
      FUN_7fff5f47d660();
LAB_7fff5fff2cad:
      FUN_7fff5f47d660();
      goto LAB_7fff5fff2cb2;
    }
LAB_7fff5fff291d:
    if (*(int *)(_DAT_7fff6244ff38 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff6244ff38);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7fff5fff2cad;
    lVar8 = FUN_7fff6087c780(lVar8,4,_DAT_7fff6245c820);
    if (lVar8 == 0) goto LAB_7fff5fff2ca8;
    cVar2 = FUN_7fff60ad2d00(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7fff62410060);
    if (cVar2 != '\0') {
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5fff2c6c;
      FUN_7fff5f254640(*(longlong *)(self + 0x28),*(undefined4 *)(lVar7 + 0x10),_DAT_7fff6240fec0);
    }
    if (*(int *)(_DAT_7fff6244ff38 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff6244ff38);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7fff5fff2ca3;
    lVar8 = FUN_7fff6087c780(lVar8,1,_DAT_7fff6245c820);
    if (lVar8 == 0) goto LAB_7fff5fff2c9e;
    cVar2 = FUN_7fff60ad2d00(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7fff62410060);
    if (cVar2 != '\0') {
      *(undefined4 *)(self + 0x44) = *(undefined4 *)(lVar7 + 0x10);
    }
    if (*(int *)(_DAT_7fff6244ff38 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff6244ff38);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7fff5fff2c99;
    lVar8 = FUN_7fff6087c780(lVar8,5,_DAT_7fff6245c820);
    if (lVar8 == 0) goto LAB_7fff5fff2c94;
    cVar2 = FUN_7fff60ad2d00(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7fff62410060);
    if (cVar2 != '\0') {
      if (*(longlong *)(self + 0x38) == 0) goto LAB_7fff5fff2c71;
      FUN_7fff5f253100(*(longlong *)(self + 0x38),lVar7,_DAT_7fff6240f5d0);
    }
    if (*(int *)(_DAT_7fff6244ff38 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff6244ff38);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7fff5fff2c8f;
    lVar8 = FUN_7fff6087c780(lVar8,1,_DAT_7fff6245c820);
    if (lVar8 == 0) goto LAB_7fff5fff2c8a;
    cVar2 = FUN_7fff60ad2d00(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7fff62410060);
    if (cVar2 == '\0') {
      if (*(int *)(_DAT_7fff6244ff38 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(_DAT_7fff6244ff38);
      }
      lVar8 = *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x30);
      if (lVar8 == 0) goto LAB_7fff5fff2c7b;
      lVar8 = FUN_7fff6087c780(lVar8,2,_DAT_7fff6245c820);
      if (lVar8 == 0) goto LAB_7fff5fff2c76;
      cVar2 = FUN_7fff60ad2d00(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7fff62410060);
      if (cVar2 != '\0') goto LAB_7fff5fff2b4a;
    }
    else {
LAB_7fff5fff2b4a:
      self[0x40] = 1;
    }
    if (*(int *)(_DAT_7fff6244ff38 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff6244ff38);
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x30);
    if (lVar8 == 0) goto LAB_7fff5fff2c85;
    lVar8 = FUN_7fff6087c780(lVar8,3,_DAT_7fff6245c820);
    if (lVar8 == 0) goto LAB_7fff5fff2c80;
    cVar2 = FUN_7fff60ad2d00(lVar8,*(undefined4 *)(lVar7 + 0x10),_DAT_7fff62410060);
    if (cVar2 != '\0') {
      self[0x41] = 1;
    }
    if (*(int *)(lVar7 + 0x10) == 0xbd) {
      self[0x48] = 1;
      uVar4 = func_0x7fff5f44ff00(_DAT_7fff62450498);
      FUN_7fff61775990(uVar4,lVar7,0);
      *(undefined8 *)(self + 0x50) = uVar4;
      thunk_FUN_7fff5f491fd0();
    }
  } while( true );
}

