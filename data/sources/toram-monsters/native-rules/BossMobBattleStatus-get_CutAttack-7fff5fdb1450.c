
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_CutAttack(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  int iVar5;
  undefined8 uStack_50;
  undefined8 uStack_48;
  longlong lStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  longlong lStack_28;
  
  if (DAT_7fff625e4930 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff6243e768);
    FUN_7fff5f47d450(&DAT_7fff6243e830);
    FUN_7fff5f47d450(0x7fff6243e8f0);
    FUN_7fff5f47d450(&DAT_7fff62400b90);
    DAT_7fff625e4930 = '\x01';
  }
  iVar5 = 0;
  if ((*(longlong *)(self + 0x30) != 0) &&
     (lVar4 = FUN_7fff607dcb60(*(longlong *)(self + 0x30),_DAT_7fff62406640), lVar4 != 0)) {
    FUN_7fff60a4b980(&uStack_50,lVar4,_DAT_7fff62400b90);
    uStack_38 = (undefined4)uStack_50;
    uStack_34 = uStack_50._4_4_;
    uStack_30 = (undefined4)uStack_48;
    uStack_2c = uStack_48._4_4_;
    lStack_28 = lStack_40;
    uStack_50 = 0;
    uStack_48 = &uStack_38;
    while (cVar2 = FUN_7fff60941650(&uStack_38,_DAT_7fff6243e830), lVar4 = lStack_28, cVar2 != '\0')
    {
      if (lStack_28 == 0) goto LAB_7fff5fdb15e6;
      if ((*(longlong *)(lStack_28 + 0x20) != 0) &&
         (cVar2 = func_0x7fff5fe666a0(lStack_28,0), cVar2 == '\0')) {
        if (*(longlong *)(lVar4 + 0x20) == 0) goto LAB_7fff5fdb15e0;
        iVar3 = FUN_7fff5fe83bb0(*(longlong *)(lVar4 + 0x20),0);
        iVar5 = iVar5 + iVar3;
      }
    }
    func_0x7fff5f4d3920(&uStack_38,_DAT_7fff6243e768);
    if (*(longlong *)(self + 0x10) != 0) {
      return *(int *)(*(longlong *)(self + 0x10) + 0x44) + iVar5;
    }
  }
  FUN_7fff5f47d660();
LAB_7fff5fdb15e0:
  FUN_7fff5f47d660();
LAB_7fff5fdb15e6:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

