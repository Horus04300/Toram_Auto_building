
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UITreasureHuntEnterManager_SetDropItemList(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  float fVar3;
  undefined8 uStack_28;
  undefined4 uStack_20;
  
  if (*(longlong *)(self + 0xf8) != 0) {
    func_0x7ffe9a2c4e50(*(longlong *)(self + 0xf8),0);
    if (*(longlong *)(self + 0x198) == 0) {
      return;
    }
    if (*(longlong *)(self + 0x100) != 0) {
      FUN_7ffe9bd9b390(*(longlong *)(self + 0x100),1);
      if (*(longlong *)(self + 0x198) != 0) {
        fVar3 = UITreasureHuntEnterManager_DropCategoryBox
                          (self,_DAT_7ffe9c049e0c,(undefined *)0x0,
                           *(undefined **)(*(longlong *)(self + 0x198) + 0x20),(undefined *)0x0);
        if (*(longlong *)(self + 0x198) != 0) {
          fVar3 = UITreasureHuntEnterManager_DropCategoryBox
                            (self,fVar3,(undefined *)0x1,
                             *(undefined **)(*(longlong *)(self + 0x198) + 0x28),(undefined *)0x0);
          if (*(longlong *)(self + 0x198) != 0) {
            fVar3 = UITreasureHuntEnterManager_DropCategoryBox
                              (self,fVar3,(undefined *)0x2,
                               *(undefined **)(*(longlong *)(self + 0x198) + 0x30),(undefined *)0x0)
            ;
            if (*(longlong *)(self + 0x198) != 0) {
              fVar3 = UITreasureHuntEnterManager_DropCategoryBox
                                (self,fVar3,(undefined *)0x3,
                                 *(undefined **)(*(longlong *)(self + 0x198) + 0x38),
                                 (undefined *)0x0);
              if (*(longlong *)(self + 0x198) != 0) {
                fVar3 = UITreasureHuntEnterManager_DropCategoryBox
                                  (self,fVar3,(undefined *)0x4,
                                   *(undefined **)(*(longlong *)(self + 0x198) + 0x40),
                                   (undefined *)0x0);
                lVar1 = *(longlong *)(self + 0xf8);
                if (DAT_7ffe9cad9b47 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                  DAT_7ffe9cad9b47 = '\x01';
                }
                if (lVar1 != 0) {
                  uStack_28 = **(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8);
                  uStack_20 = *(undefined4 *)(*(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8) + 1);
                  FUN_7ffe9a2c53f0(lVar1,&uStack_28,
                                   (ulonglong)((uint)fVar3 ^ _DAT_7ffe9c049c00) << 0x20,0);
                  if (*(longlong *)(self + 0x100) != 0) {
                    FUN_7ffe9bd9b390(*(longlong *)(self + 0x100),0,0);
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

