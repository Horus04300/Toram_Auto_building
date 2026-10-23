
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIEquipCristaPanel_GetPowerUpCristaOrderList(undefined *self,int startItemId,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  undefined *puVar4;
  longlong lVar5;
  longlong lVar6;
  undefined *puVar7;
  longlong lVar8;
  
  if (DAT_7ffe9cadb47e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c909ac8);
    FUN_7ffe9996d590(&DAT_7ffe9c93c8a8);
    FUN_7ffe9996d590(&DAT_7ffe9c92f5c0);
    FUN_7ffe9996d590(&DAT_7ffe9c92f438);
    FUN_7ffe9996d590(&DAT_7ffe9c96b698);
    FUN_7ffe9996d590(&DAT_7ffe9c93ef58);
    FUN_7ffe9996d590(&DAT_7ffe9c945f38);
    DAT_7ffe9cadb47e = '\x01';
  }
  puVar4 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c96b698);
  FUN_7ffe9af8a010(puVar4,_DAT_7ffe9c92f438);
  if ((*(longlong *)(self + 0x158) != 0) &&
     (lVar5 = FUN_7ffe9a47fce0(*(longlong *)(self + 0x158),0), lVar5 != 0)) {
    lVar5 = FUN_7ffe9a571300(lVar5,startItemId,0);
    if (lVar5 == 0) {
      return puVar4;
    }
    lVar6 = func_0x7ffe99940040(_DAT_7ffe9c945f38);
    func_0x7ffe999c3920(lVar6,0);
    lVar8 = _DAT_7ffe9c92f5c0;
    if (puVar4 == (undefined *)0x0) goto LAB_7ffe99dd3b45;
    *(int *)(puVar4 + 0x1c) = *(int *)(puVar4 + 0x1c) + 1;
    lVar2 = *(longlong *)(puVar4 + 0x10);
    uVar1 = *(uint *)(puVar4 + 0x18);
    if (lVar2 == 0) goto LAB_7ffe99dd3b45;
    if (uVar1 < *(uint *)(lVar2 + 0x18)) {
      *(uint *)(puVar4 + 0x18) = uVar1 + 1;
      if (*(uint *)(lVar2 + 0x18) <= uVar1) goto LAB_7ffe99dd3b4b;
      *(longlong *)(lVar2 + (longlong)(int)uVar1 * 8 + 0x20) = lVar5;
      il2cpp_write_barrier_0();
    }
    else {
      FUN_7ffe9afd58b0(puVar4,lVar5,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar8 + 0x20) + 0xc0) + 0x70));
    }
    if (lVar6 != 0) {
      *(int *)(lVar6 + 0x10) = startItemId;
      puVar7 = UIEquipCristaPanel_GetAllPowerUpCristaList(self,(undefined *)0x0);
      while( true ) {
        while( true ) {
          lVar5 = *(longlong *)(lVar6 + 0x18);
          if (lVar5 == 0) {
            lVar5 = func_0x7ffe99940040(_DAT_7ffe9c93c8a8);
            FUN_7ffe9af13420(lVar5,lVar6,_DAT_7ffe9c93ef58,0);
            *(longlong *)(lVar6 + 0x18) = lVar5;
            il2cpp_write_barrier_0();
          }
          lVar8 = FUN_7ffe9ab854c0(puVar7,lVar5,_DAT_7ffe9c909ac8);
          lVar5 = _DAT_7ffe9c92f5c0;
          if (lVar8 == 0) {
            return puVar4;
          }
          *(int *)(puVar4 + 0x1c) = *(int *)(puVar4 + 0x1c) + 1;
          lVar2 = *(longlong *)(puVar4 + 0x10);
          uVar1 = *(uint *)(puVar4 + 0x18);
          if (lVar2 == 0) goto LAB_7ffe99dd3b45;
          if (uVar1 < *(uint *)(lVar2 + 0x18)) break;
          FUN_7ffe9afd58b0(puVar4,lVar8,
                           *(undefined8 *)(*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70)
                          );
          *(undefined4 *)(lVar6 + 0x10) = *(undefined4 *)(lVar8 + 0x34);
        }
        *(uint *)(puVar4 + 0x18) = uVar1 + 1;
        if (*(uint *)(lVar2 + 0x18) <= uVar1) break;
        *(longlong *)(lVar2 + (longlong)(int)uVar1 * 8 + 0x20) = lVar8;
        il2cpp_write_barrier_0();
        *(undefined4 *)(lVar6 + 0x10) = *(undefined4 *)(lVar8 + 0x34);
      }
LAB_7ffe99dd3b4b:
      FUN_7ffe9996d790();
      pcVar3 = (code *)swi(3);
      puVar4 = (undefined *)(*pcVar3)();
      return puVar4;
    }
  }
LAB_7ffe99dd3b45:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  puVar4 = (undefined *)(*pcVar3)();
  return puVar4;
}

