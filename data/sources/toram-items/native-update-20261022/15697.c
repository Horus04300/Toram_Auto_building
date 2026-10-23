
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
BonusManager_CreateBonus
          (undefined *self,undefined *bonusLines,byte exec,int stack,undefined *methodInfo)

{
  undefined1 uVar1;
  undefined4 uVar2;
  uint uVar3;
  longlong lVar4;
  longlong lVar5;
  code *pcVar6;
  char cVar7;
  int iVar8;
  undefined *puVar9;
  longlong lVar10;
  undefined8 uVar11;
  int iVar12;
  undefined8 uStack_a8;
  undefined8 *puStack_a0;
  longlong lStack_98;
  undefined8 uStack_90;
  undefined8 *puStack_88;
  longlong lStack_80;
  longlong lStack_78;
  undefined8 uStack_70;
  undefined8 *puStack_68;
  longlong lStack_60;
  
  if (DAT_7ffe9cade102 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c902308);
    FUN_7ffe9996d590(&DAT_7ffe9c9735b8);
    FUN_7ffe9996d590(&DAT_7ffe9c973688);
    FUN_7ffe9996d590(&DAT_7ffe9c9023d8);
    FUN_7ffe9996d590(0x7ffe9c973758);
    FUN_7ffe9996d590(0x7ffe9c9024a8);
    FUN_7ffe9996d590(&DAT_7ffe9c94b220);
    FUN_7ffe9996d590(&DAT_7ffe9c94b160);
    FUN_7ffe9996d590(0x7ffe9c94b2e8);
    FUN_7ffe9996d590(&DAT_7ffe9c9089b0);
    FUN_7ffe9996d590(&DAT_7ffe9c94b470);
    FUN_7ffe9996d590(&DAT_7ffe9c94afd8);
    FUN_7ffe9996d590(&DAT_7ffe9c970cc0);
    FUN_7ffe9996d590(&DAT_7ffe9c92fc90);
    DAT_7ffe9cade102 = '\x01';
  }
  uStack_90 = 0;
  puStack_88 = (undefined8 *)0x0;
  lStack_80 = 0;
  puVar9 = BonusManager_CreateBonus(self,bonusLines,exec,(undefined *)0x0);
  if (stack < 2) {
    return puVar9;
  }
  lVar10 = func_0x7ffe99940040(_DAT_7ffe9c970cc0);
  FUN_7ffe9af8a010(lVar10,_DAT_7ffe9c94afd8);
  lStack_78 = lVar10;
  if ((puVar9 != (undefined *)0x0) && (*(longlong *)(puVar9 + 0x20) != 0)) {
    FUN_7ffe9af836a0(&uStack_a8,*(longlong *)(puVar9 + 0x20),_DAT_7ffe9c94b470);
    uStack_70 = uStack_a8;
    puStack_68 = puStack_a0;
    lStack_60 = lStack_98;
    uStack_a8 = 0;
    puStack_a0 = &uStack_70;
    while (cVar7 = FUN_7ffe9ae28ed0(&uStack_70,_DAT_7ffe9c9023d8), cVar7 != '\0') {
      if (lStack_60 == 0) goto LAB_7ffe9a4e9d1d;
      uVar2 = *(undefined4 *)(lStack_60 + 0x10);
      iVar12 = *(int *)(lStack_60 + 0x14);
      uVar1 = *(undefined1 *)(lStack_60 + 0x18);
      uVar11 = func_0x7ffe99940040(_DAT_7ffe9c92fc90);
      FUN_7ffe9a506750(uVar11,uVar2,iVar12 * stack,uVar1,0);
      lVar5 = _DAT_7ffe9c94b160;
      if (lVar10 == 0) goto LAB_7ffe9a4e9d18;
      *(int *)(lVar10 + 0x1c) = *(int *)(lVar10 + 0x1c) + 1;
      lVar4 = *(longlong *)(lVar10 + 0x10);
      uVar3 = *(uint *)(lVar10 + 0x18);
      if (lVar4 == 0) goto LAB_7ffe9a4e9d13;
      if (uVar3 < *(uint *)(lVar4 + 0x18)) {
        *(uint *)(lVar10 + 0x18) = uVar3 + 1;
        if (*(uint *)(lVar4 + 0x18) <= uVar3) goto LAB_7ffe9a4e9d0d;
        *(undefined8 *)(lVar4 + (longlong)(int)uVar3 * 8 + 0x20) = uVar11;
        il2cpp_write_barrier_0();
      }
      else {
        FUN_7ffe9afd58b0(lVar10,uVar11,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
      }
    }
    func_0x7ffe999c3920(&uStack_70,_DAT_7ffe9c902308);
    lVar5 = *(longlong *)(puVar9 + 0x20);
    if (lVar5 != 0) {
      *(int *)(lVar5 + 0x1c) = *(int *)(lVar5 + 0x1c) + 1;
      iVar12 = *(int *)(lVar5 + 0x18);
      *(undefined4 *)(lVar5 + 0x18) = 0;
      if (0 < iVar12) {
        FUN_7ffe9b518970(*(undefined8 *)(lVar5 + 0x10),0,iVar12,0);
      }
      if (*(longlong *)(puVar9 + 0x20) != 0) {
        func_0x7ffe9afd5600(*(longlong *)(puVar9 + 0x20),lVar10,_DAT_7ffe9c94b220);
        if (*(longlong *)(puVar9 + 0x30) != 0) {
          FUN_7ffe9af836a0(&uStack_a8,*(longlong *)(puVar9 + 0x30),_DAT_7ffe9c9089b0);
          uStack_90 = uStack_a8;
          puStack_88 = puStack_a0;
          lStack_80 = lStack_98;
          uStack_a8 = 0;
          puStack_a0 = &uStack_90;
          while (cVar7 = FUN_7ffe9ae28ed0(&uStack_90,_DAT_7ffe9c973688), cVar7 != '\0') {
            if (lStack_80 == 0) goto LAB_7ffe9a4e9d29;
            iVar8 = *(short *)(lStack_80 + 0x14) * stack;
            iVar12 = 0x7fff;
            if (iVar8 < 0x7fff) {
              iVar12 = iVar8;
            }
            *(short *)(lStack_80 + 0x14) = (short)iVar12;
          }
          func_0x7ffe999c3920(&uStack_90,_DAT_7ffe9c9735b8);
          if (*(longlong *)(puVar9 + 0x38) != 0) {
            FUN_7ffe9af836a0(&uStack_a8,*(longlong *)(puVar9 + 0x38),_DAT_7ffe9c9089b0);
            uStack_90 = uStack_a8;
            puStack_88 = puStack_a0;
            lStack_80 = lStack_98;
            uStack_a8 = 0;
            puStack_a0 = &uStack_90;
            while( true ) {
              cVar7 = FUN_7ffe9ae28ed0(&uStack_90,_DAT_7ffe9c973688);
              if (cVar7 == '\0') {
                func_0x7ffe999c3920(&uStack_90,_DAT_7ffe9c9735b8);
                return puVar9;
              }
              if (lStack_80 == 0) break;
              iVar8 = *(short *)(lStack_80 + 0x14) * stack;
              iVar12 = 0x7fff;
              if (0x7fff < iVar8) {
                iVar12 = iVar8;
              }
              *(short *)(lStack_80 + 0x14) = (short)iVar12;
            }
            goto LAB_7ffe9a4e9d35;
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
LAB_7ffe9a4e9d0d:
  FUN_7ffe9996d790();
LAB_7ffe9a4e9d13:
  FUN_7ffe9996d7a0();
LAB_7ffe9a4e9d18:
  FUN_7ffe9996d7a0();
LAB_7ffe9a4e9d1d:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a4e9d29:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a4e9d35:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar6 = (code *)swi(3);
  puVar9 = (undefined *)(*pcVar6)();
  return puVar9;
}

