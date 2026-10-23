
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIEquipCristaPanel_GetPowerUpCristaOrderList
          (undefined *self,undefined *startItemData,int endItemId,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  undefined *puVar4;
  longlong lVar5;
  int iVar6;
  
  if (DAT_7ffe9cadb47d == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94ecc0);
    FUN_7ffe9996d590(&DAT_7ffe9c92f5c0);
    FUN_7ffe9996d590(&DAT_7ffe9c92fef0);
    FUN_7ffe9996d590(&DAT_7ffe9c92f438);
    FUN_7ffe9996d590(&DAT_7ffe9c96b698);
    DAT_7ffe9cadb47d = '\x01';
  }
  puVar4 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c96b698);
  FUN_7ffe9af8a010(puVar4,_DAT_7ffe9c92f438);
  lVar5 = _DAT_7ffe9c92f5c0;
  if (puVar4 != (undefined *)0x0) {
    if (startItemData == (undefined *)0x0) goto LAB_7ffe99dd38b5;
    *(int *)(puVar4 + 0x1c) = *(int *)(puVar4 + 0x1c) + 1;
    lVar2 = *(longlong *)(puVar4 + 0x10);
    uVar1 = *(uint *)(puVar4 + 0x18);
    if (lVar2 != 0) {
      if (uVar1 < *(uint *)(lVar2 + 0x18)) {
        *(uint *)(puVar4 + 0x18) = uVar1 + 1;
        if (*(uint *)(lVar2 + 0x18) <= uVar1) {
          FUN_7ffe9996d790();
          pcVar3 = (code *)swi(3);
          puVar4 = (undefined *)(*pcVar3)();
          return puVar4;
        }
        *(undefined **)(lVar2 + (longlong)(int)uVar1 * 8 + 0x20) = startItemData;
        il2cpp_write_barrier_0();
      }
      else {
        FUN_7ffe9afd58b0(puVar4,startItemData,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
      }
      if (*(longlong *)(startItemData + 0x28) != 0) {
        iVar6 = *(int *)(*(longlong *)(startItemData + 0x28) + 0x48);
        if (iVar6 != endItemId) {
          do {
            if ((*(longlong *)(self + 0x158) == 0) ||
               (lVar5 = FUN_7ffe9a47fce0(*(longlong *)(self + 0x158),0), lVar5 == 0))
            goto LAB_7ffe99dd38e2;
            lVar5 = FUN_7ffe9a571300(lVar5,iVar6,0);
            if (lVar5 == 0) {
              if (*(int *)(_DAT_7ffe9c94ecc0 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              lVar5 = FUN_7ffe9a56ed40(iVar6,0);
              if (lVar5 == 0) break;
            }
            FUN_7ffe99743100(puVar4);
            if (*(longlong *)(lVar5 + 0x28) == 0) goto LAB_7ffe99dd38e2;
            iVar6 = *(int *)(*(longlong *)(lVar5 + 0x28) + 0x48);
            if ((iVar6 == 0) || (iVar6 == endItemId)) break;
          } while( true );
        }
        if (endItemId != 0) {
          if ((*(longlong *)(self + 0x158) == 0) ||
             (lVar5 = FUN_7ffe9a47fce0(*(longlong *)(self + 0x158),0), lVar5 == 0))
          goto LAB_7ffe99dd38e2;
          lVar5 = FUN_7ffe9a571300(lVar5,endItemId,0);
          if (lVar5 == 0) {
            if (*(int *)(_DAT_7ffe9c94ecc0 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            lVar5 = FUN_7ffe9a56ed40(endItemId,0);
          }
          FUN_7ffe99743100(puVar4,lVar5,_DAT_7ffe9c92f5c0);
        }
LAB_7ffe99dd38b5:
        FUN_7ffe9afdc670(puVar4,_DAT_7ffe9c92fef0);
        return puVar4;
      }
    }
  }
LAB_7ffe99dd38e2:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  puVar4 = (undefined *)(*pcVar3)();
  return puVar4;
}

