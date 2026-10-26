
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EquipBuffManager_SetBonus(undefined *self,byte type,undefined *bonus,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uStack_58;
  undefined8 *puStack_50;
  longlong lStack_48;
  undefined8 uStack_40;
  undefined8 *puStack_38;
  longlong lStack_30;
  
  if (DAT_7ffe9cade24d == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949508);
    FUN_7ffe9996d590(&DAT_7ffe9c949690);
    FUN_7ffe9996d590(&DAT_7ffe9c949818);
    FUN_7ffe9996d590(&DAT_7ffe9c9735b8);
    FUN_7ffe9996d590(&DAT_7ffe9c973688);
    FUN_7ffe9996d590(0x7ffe9c973758);
    FUN_7ffe9996d590(&DAT_7ffe9c9183d8);
    FUN_7ffe9996d590(&DAT_7ffe9c9089b0);
    FUN_7ffe9996d590(&DAT_7ffe9c918238);
    FUN_7ffe9996d590(&DAT_7ffe9c966ee8);
    DAT_7ffe9cade24d = '\x01';
  }
  uStack_40 = 0;
  puStack_38 = (undefined8 *)0x0;
  lStack_30 = 0;
  lVar3 = func_0x7ffe99940040(_DAT_7ffe9c966ee8);
  FUN_7ffe9af8a010(lVar3,_DAT_7ffe9c918238);
  lVar5 = lVar3;
  if (bonus != (undefined *)0x0) {
    if (*(longlong *)(bonus + 0x30) == 0) goto LAB_7ffe9a51e899;
    FUN_7ffe9af836a0(&uStack_58,*(longlong *)(bonus + 0x30),_DAT_7ffe9c9089b0);
    uStack_40 = uStack_58;
    puStack_38 = puStack_50;
    lStack_30 = lStack_48;
    uStack_58 = 0;
    puStack_50 = &uStack_40;
    while( true ) {
      cVar2 = FUN_7ffe9ae28ed0(&uStack_40,_DAT_7ffe9c973688);
      if (cVar2 == '\0') break;
      if (lStack_30 == 0) goto LAB_7ffe9a51e8a5;
      lVar4 = FUN_7ffe9a51ca50(type,*(undefined4 *)(lStack_30 + 0x10),
                               *(undefined2 *)(lStack_30 + 0x14),0);
      if (lVar4 != 0) {
        if (lVar3 == 0) goto LAB_7ffe9a51e89f;
        FUN_7ffe99743100(lVar3,lVar4,_DAT_7ffe9c9183d8);
      }
    }
    _GetDurationBonusTime_d__7_System_IDisposable_Dispose((undefined *)&uStack_40,_DAT_7ffe9c9735b8)
    ;
  }
  if (*(longlong *)(self + 0x10) != 0) {
    cVar2 = FUN_7ffe9acd86a0(*(longlong *)(self + 0x10),type,_DAT_7ffe9c949690);
    if (cVar2 != '\0') {
      if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a51e899;
      FUN_7ffe9acf0120(*(longlong *)(self + 0x10),type,_DAT_7ffe9c949818);
    }
    if (bonus != (undefined *)0x0) {
      if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a51e899;
      FUN_7ffe9aceb930(*(longlong *)(self + 0x10),type,lVar3,_DAT_7ffe9c949508,lVar5);
    }
    return;
  }
LAB_7ffe9a51e899:
  FUN_7ffe9996d7a0();
LAB_7ffe9a51e89f:
  FUN_7ffe9996d7a0();
LAB_7ffe9a51e8a5:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

