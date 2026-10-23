
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobPropertyBase_TryAddProperty(undefined *self,undefined *master,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  longlong lVar5;
  char cVar6;
  byte bVar7;
  
  if (DAT_7fff625e4edf == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62444388);
    DAT_7fff625e4edf = '\x01';
  }
  cVar6 = (**(code **)(*(longlong *)self + 0x188))
                    (self,master,*(undefined8 *)(*(longlong *)self + 400));
  lVar5 = _DAT_7fff62444388;
  if (cVar6 == '\0') {
    return 0;
  }
  lVar2 = *(longlong *)(self + 0x10);
  if (lVar2 != 0) {
    *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
    lVar3 = *(longlong *)(lVar2 + 0x10);
    uVar1 = *(uint *)(lVar2 + 0x18);
    if (lVar3 != 0) {
      if (*(uint *)(lVar3 + 0x18) <= uVar1) {
        FUN_7fff60adfc70(lVar2,master,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
        return 1;
      }
      *(uint *)(lVar2 + 0x18) = uVar1 + 1;
      if (uVar1 < *(uint *)(lVar3 + 0x18)) {
        *(undefined **)(lVar3 + 0x20 + (longlong)(int)uVar1 * 8) = master;
        thunk_FUN_7fff5f491fd0();
        return 1;
      }
      FUN_7fff5f47d650();
      pcVar4 = (code *)swi(3);
      bVar7 = (*pcVar4)();
      return bVar7;
    }
  }
  FUN_7fff5f47d660();
  pcVar4 = (code *)swi(3);
  bVar7 = (*pcVar4)();
  return bVar7;
}

