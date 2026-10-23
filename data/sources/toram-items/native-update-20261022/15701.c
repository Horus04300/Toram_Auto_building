
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_SetEquipBonus
               (undefined *self,undefined *type,undefined *bonus,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  uVar6 = (ulonglong)type & 0xffffffff;
  if (DAT_7ffe9cade104 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c959438);
    FUN_7ffe9996d590(&DAT_7ffe9c959108);
    FUN_7ffe9996d590(&DAT_7ffe9c9595d0);
    FUN_7ffe9996d590(&DAT_7ffe9c959768);
    FUN_7ffe9996d590(&DAT_7ffe9c9591d0);
    FUN_7ffe9996d590(&DAT_7ffe9c959900);
    FUN_7ffe9996d590(&DAT_7ffe9c9592a0);
    FUN_7ffe9996d590(&DAT_7ffe9c959a98);
    FUN_7ffe9996d590(&DAT_7ffe9c973348);
    FUN_7ffe9996d590(&DAT_7ffe9c973418);
    FUN_7ffe9996d590(0x7ffe9c9734e8);
    FUN_7ffe9996d590(&DAT_7ffe9c907d80);
    FUN_7ffe9996d590(&DAT_7ffe9c907ff0);
    FUN_7ffe9996d590(&DAT_7ffe9c9080c0);
    FUN_7ffe9996d590(0x7ffe9c9092a0);
    DAT_7ffe9cade104 = '\x01';
  }
  lVar5 = *(longlong *)(self + 0x20);
  if (bonus == (undefined *)0x0) {
    if (lVar5 == 0) goto LAB_7ffe9a4ecb34;
    cVar3 = FUN_7ffe9ad5f0a0(lVar5,uVar6,_DAT_7ffe9c9595d0);
    if (cVar3 != '\0') {
      lVar5 = *(longlong *)(self + 0x78);
      if ((*(longlong *)(self + 0x20) == 0) ||
         (uVar4 = FUN_7ffe9ad723c0(*(longlong *)(self + 0x20),uVar6,_DAT_7ffe9c959900), lVar5 == 0))
      goto LAB_7ffe9a4ecb34;
      FUN_7ffe9afdbfb0(lVar5,uVar4,_DAT_7ffe9c9080c0);
      if (*(longlong *)(self + 0x20) == 0) goto LAB_7ffe9a4ecb34;
      FUN_7ffe9ad86f60(*(longlong *)(self + 0x20),uVar6,_DAT_7ffe9c959768);
    }
  }
  else {
    if (lVar5 == 0) goto LAB_7ffe9a4ecb34;
    cVar3 = FUN_7ffe9ad5f0a0(lVar5,uVar6,_DAT_7ffe9c9595d0);
    lVar5 = *(longlong *)(self + 0x20);
    if (cVar3 == '\0') {
      if (lVar5 == 0) goto LAB_7ffe9a4ecb34;
      FUN_7ffe9ad82760(lVar5,uVar6,bonus,_DAT_7ffe9c959438);
    }
    else {
      lVar1 = *(longlong *)(self + 0x78);
      if ((lVar5 == 0) || (uVar4 = FUN_7ffe9ad723c0(lVar5,uVar6,_DAT_7ffe9c959900), lVar1 == 0))
      goto LAB_7ffe9a4ecb34;
      FUN_7ffe9afdbfb0(lVar1,uVar4,_DAT_7ffe9c9080c0);
      if (*(longlong *)(self + 0x20) == 0) goto LAB_7ffe9a4ecb34;
      FUN_7ffe9ad94d20(*(longlong *)(self + 0x20),uVar6,bonus,_DAT_7ffe9c959a98);
    }
    if (*(longlong *)(bonus + 0x18) == 0) goto LAB_7ffe9a4ecb34;
    if (0 < *(int *)(*(longlong *)(bonus + 0x18) + 0x18)) {
      if (*(longlong *)(self + 0x78) == 0) goto LAB_7ffe9a4ecb34;
      FUN_7ffe99743100(*(longlong *)(self + 0x78),bonus,_DAT_7ffe9c907d80);
    }
  }
  if (*(longlong *)(self + 0x28) != 0) {
    cVar3 = FUN_7ffe9ad5f0a0(*(longlong *)(self + 0x28),uVar6,_DAT_7ffe9c959108);
    if (cVar3 == '\0') {
      return;
    }
    if ((*(longlong *)(self + 0x28) != 0) &&
       (lVar5 = FUN_7ffe9ad723c0(*(longlong *)(self + 0x28),uVar6,_DAT_7ffe9c9592a0), lVar5 != 0)) {
      FUN_7ffe9af836a0(&uStack_50,lVar5,_DAT_7ffe9c907ff0);
      uStack_38 = (undefined4)uStack_50;
      uStack_34 = uStack_50._4_4_;
      uStack_30 = (undefined4)uStack_48;
      uStack_2c = uStack_48._4_4_;
      uStack_28 = uStack_40;
      uStack_50 = 0;
      uStack_48 = &uStack_38;
      while (cVar3 = FUN_7ffe9ae28ed0(&uStack_38,_DAT_7ffe9c973418), cVar3 != '\0') {
        if (*(longlong *)(self + 0x78) == 0) goto LAB_7ffe9a4ecb3a;
        FUN_7ffe9afdbfb0(*(longlong *)(self + 0x78),uStack_28,_DAT_7ffe9c9080c0);
      }
      func_0x7ffe999c3920(&uStack_38,_DAT_7ffe9c973348);
      if (*(longlong *)(self + 0x28) != 0) {
        FUN_7ffe9ad86f60(*(longlong *)(self + 0x28),uVar6,_DAT_7ffe9c9591d0);
        return;
      }
    }
  }
LAB_7ffe9a4ecb34:
  FUN_7ffe9996d7a0();
LAB_7ffe9a4ecb3a:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

