
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_UpdateEquipLimitBonus(undefined *self,undefined *methodInfo)

{
  undefined *self_00;
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined8 uStack_40;
  undefined8 *puStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  if (DAT_7fff625e585e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fd6e8);
    FUN_7fff5f47d450(&DAT_7fff6247a258);
    FUN_7fff5f47d450(&DAT_7fff6247a328);
    FUN_7fff5f47d450(0x7fff6247a3f8);
    FUN_7fff5f47d450(&DAT_7fff62452300);
    FUN_7fff5f47d450(&DAT_7fff6240f020);
    FUN_7fff5f47d450(&DAT_7fff62420458);
    FUN_7fff5f47d450(&DAT_7fff6242c438);
    DAT_7fff625e585e = '\x01';
  }
  if (*(longlong *)(self + 0x78) == 0) {
    FUN_7fff5f47d660();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  FUN_7fff60a8da60(&uStack_40);
  uStack_28 = uStack_40;
  uStack_20 = puStack_38;
  uStack_18 = uStack_30;
  uStack_40 = 0;
  puStack_38 = &uStack_28;
LAB_7fff5fff7d24:
  cVar3 = FUN_7fff60933290(&uStack_28,_DAT_7fff6247a328);
  if (cVar3 == '\0') {
    func_0x7fff5f4d3920(&uStack_28,_DAT_7fff6247a258);
    return;
  }
  lVar4 = func_0x7fff5f44ff00(_DAT_7fff6242c438);
  func_0x7fff5f4d30f0(lVar4,0);
  if (lVar4 == 0) goto LAB_7fff5fff7e66;
  *(undefined **)(lVar4 + 0x18) = self;
  thunk_FUN_7fff5f491fd0();
  *(undefined8 *)(lVar4 + 0x10) = uStack_18;
  thunk_FUN_7fff5f491fd0();
  self_00 = *(undefined **)(lVar4 + 0x10);
  if (self_00 != (undefined *)0x0) goto code_r0x7fff5fff7d8d;
  goto LAB_7fff5fff7e61;
code_r0x7fff5fff7d8d:
  if (self_00[0x41] != '\0') {
    if (*(undefined **)(self + 0x18) != (undefined *)0x0) {
      BonusScriptManager_Run
                (*(undefined **)(self + 0x18),*(undefined **)(self_00 + 0x10),0,(undefined *)0x0);
      BonusData_UpdateBonusList(self_00,(undefined *)0x0);
      if (*(longlong *)(lVar4 + 0x10) != 0) {
        lVar1 = *(longlong *)(*(longlong *)(lVar4 + 0x10) + 0x20);
        uVar5 = func_0x7fff5f44ff00(_DAT_7fff623fd6e8);
        FUN_7fff5fdfedb0(uVar5,lVar4,_DAT_7fff62420458);
        if (lVar1 != 0) {
          FUN_7fff60a8d940(lVar1,uVar5);
          goto LAB_7fff5fff7d24;
        }
        FUN_7fff5f47d660();
      }
      FUN_7fff5f47d660();
    }
    FUN_7fff5f47d660();
LAB_7fff5fff7e61:
    FUN_7fff5f47d660();
LAB_7fff5fff7e66:
    FUN_7fff5f47d660();
    FUN_7fff5f40a410();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  goto LAB_7fff5fff7d24;
}

