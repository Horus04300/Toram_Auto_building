
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobPropertyManager_SetMasterData
               (undefined *self,int mobUuid,int mobId,undefined *master,undefined *methodInfo)

{
  undefined *master_00;
  code *pcVar1;
  char cVar2;
  undefined *self_00;
  undefined4 in_register_00000014;
  uint uVar3;
  undefined4 in_register_00000084;
  
  if (DAT_7ffe9cadd77f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92a6a0,CONCAT44(in_register_00000014,mobUuid),
                     CONCAT44(in_register_00000084,mobId));
    FUN_7ffe9996d590(&DAT_7ffe9c92a828);
    FUN_7ffe9996d590(&DAT_7ffe9c92aa70);
    DAT_7ffe9cadd77f = '\x01';
  }
  uVar3 = 0;
  if (master != (undefined *)0x0) {
    while( true ) {
      if ((int)*(uint *)(master + 0x18) <= (int)uVar3) {
        return;
      }
      if (*(uint *)(master + 0x18) <= uVar3) {
        FUN_7ffe9996d790();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      master_00 = *(undefined **)(master + (longlong)(int)uVar3 * 8 + 0x20);
      if ((master_00 == (undefined *)0x0) || (*(longlong *)(self + 0x10) == 0)) break;
      cVar2 = FUN_7ffe9ad5f0a0(*(longlong *)(self + 0x10),*(undefined4 *)(master_00 + 0x14),
                               _DAT_7ffe9c92a828);
      if (cVar2 == '\0') {
        self_00 = (undefined *)FUN_7ffe9a379850(*(undefined4 *)(master_00 + 0x14),0);
        if (self_00 != (undefined *)0x0) {
          if (*(longlong *)(self + 0x10) != 0) {
            FUN_7ffe9ad82760(*(longlong *)(self + 0x10),*(undefined4 *)(master_00 + 0x14),self_00,
                             _DAT_7ffe9c92a6a0);
            goto LAB_7ffe9a37acc9;
          }
          break;
        }
      }
      else {
        if (*(longlong *)(self + 0x10) == 0) break;
        self_00 = (undefined *)
                  FUN_7ffe9ad723c0(*(longlong *)(self + 0x10),*(undefined4 *)(master_00 + 0x14));
        if (self_00 != (undefined *)0x0) {
LAB_7ffe9a37acc9:
          MobPropertyBase_TryAddProperty(self_00,master_00,(undefined *)0x0);
        }
      }
      uVar3 = uVar3 + 1;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

