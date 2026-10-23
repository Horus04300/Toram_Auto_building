
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GameManager__loadFieldData_d__125_MoveNext(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int fieldId;
  undefined8 uVar5;
  longlong lVar6;
  undefined *puVar7;
  undefined8 uVar8;
  longlong lVar9;
  
  if (DAT_7ffe9cadfea2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c956e00);
    FUN_7ffe9996d590(&DAT_7ffe9c953d70);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    FUN_7ffe9996d590(&DAT_7ffe9c962ec8);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ef10);
    FUN_7ffe9996d590(&DAT_7ffe9c949ff8);
    FUN_7ffe9996d590(&DAT_7ffe9c915820);
    FUN_7ffe9996d590(&DAT_7ffe9c9158f0);
    DAT_7ffe9cadfea2 = '\x01';
  }
  lVar9 = *(longlong *)(self + 0x28);
  if (*(int *)(self + 0x10) == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    uVar5 = func_0x7ffe99940040(_DAT_7ffe9c949ff8);
    func_0x7ffe999c3920(uVar5,0);
    *(undefined8 *)(self + 0x30) = uVar5;
    il2cpp_write_barrier_0();
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7ffe9a8e9e75;
    *(undefined1 *)(*(longlong *)(self + 0x30) + 0x10) = 1;
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar6 == 0) goto LAB_7ffe9a8e9e75;
    *(undefined8 *)(self + 0x40) = *(undefined8 *)(lVar6 + 0x20);
    il2cpp_write_barrier_0();
    uVar5 = *(undefined8 *)(self + 0x40);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda2160(uVar5,0,0);
    if (cVar3 != '\0') {
      puVar7 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953d70);
      lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
      if (lVar6 != 0) {
        fieldId = FUN_7ffe9a8721b0(lVar6,0);
        if ((*(longlong *)(self + 0x40) != 0) && (puVar7 != (undefined *)0x0)) {
          bVar4 = MobMaster_ReadMaster
                            (puVar7,fieldId,*(undefined **)(*(longlong *)(self + 0x40) + 0x48),
                             *(undefined **)(self + 0x20),(undefined *)0x0);
          if (bVar4 == 0) {
            func_0x7ffe999c3920(_DAT_7ffe9c9158f0,0);
          }
          lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c953d70);
          uVar5 = *(undefined8 *)(self + 0x20);
          uVar1 = *(undefined8 *)(self + 0x30);
          uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
          FUN_7ffe9ac2ed50(uVar8,uVar1,_DAT_7ffe9c93ef10,0);
          if ((lVar6 != 0) && (uVar5 = FUN_7ffe9a33e120(lVar6,uVar5,uVar8,0), lVar9 != 0)) {
            uVar5 = FUN_7ffe9bd9f640(lVar9,uVar5,0);
            *(undefined8 *)(self + 0x18) = uVar5;
            il2cpp_write_barrier_0();
            *(undefined4 *)(self + 0x10) = 1;
            return 1;
          }
        }
      }
      goto LAB_7ffe9a8e9e75;
    }
  }
  else {
    if (*(int *)(self + 0x10) != 1) {
      return 0;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7ffe9a8e9e75;
    if (*(char *)(*(longlong *)(self + 0x30) + 0x10) == '\0') {
      func_0x7ffe999c3920(_DAT_7ffe9c915820);
    }
    lVar6 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
    if ((*(undefined **)(self + 0x40) == (undefined *)0x0) ||
       (puVar7 = MapInfo_GetMobPopPoint(*(undefined **)(self + 0x40),(undefined *)0x0), lVar6 == 0))
    goto LAB_7ffe9a8e9e75;
    FUN_7ffe9a33cc70(lVar6,puVar7,0);
    lVar6 = FUN_7ffe9b15c270(_DAT_7ffe9c962ec8);
    if (lVar6 == 0) goto LAB_7ffe9a8e9e75;
    FUN_7ffe9a8550e0(lVar6,0);
    lVar6 = FUN_7ffe9b15c270(_DAT_7ffe9c962ec8);
    if ((*(longlong *)(self + 0x40) == 0) ||
       (uVar5 = FUN_7ffe9a88ed70(*(longlong *)(self + 0x40),0), lVar6 == 0)) goto LAB_7ffe9a8e9e75;
    FUN_7ffe9a855bf0(lVar6,uVar5,0);
  }
  if (lVar9 != 0) {
    *(undefined1 *)(lVar9 + 0x5a) = 1;
    if (self[0x38] != '\0') {
      FUN_7ffe9bb8add0(*(undefined8 *)(lVar9 + 0x30),0);
    }
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c956e00);
    if (lVar9 != 0) {
      FUN_7ffe9a2c77a0(lVar9,0,0);
      return 0;
    }
  }
LAB_7ffe9a8e9e75:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar4 = (*pcVar2)();
  return bVar4;
}

