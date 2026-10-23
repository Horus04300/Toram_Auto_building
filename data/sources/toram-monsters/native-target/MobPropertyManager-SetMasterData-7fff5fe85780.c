
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
  
  if (DAT_7fff625e4ed7 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624315f0,CONCAT44(in_register_00000014,mobUuid),
                     CONCAT44(in_register_00000084,mobId));
    FUN_7fff5f47d450(&DAT_7fff62431778);
    FUN_7fff5f47d450(&DAT_7fff624319c8);
    DAT_7fff625e4ed7 = '\x01';
  }
  uVar3 = 0;
  if (master != (undefined *)0x0) {
    while( true ) {
      if ((int)*(uint *)(master + 0x18) <= (int)uVar3) {
        return;
      }
      if (*(uint *)(master + 0x18) <= uVar3) {
        FUN_7fff5f47d650();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      master_00 = *(undefined **)(master + (longlong)(int)uVar3 * 8 + 0x20);
      if ((master_00 == (undefined *)0x0) || (*(longlong *)(self + 0x10) == 0)) break;
      cVar2 = FUN_7fff60869460(*(longlong *)(self + 0x10),*(undefined4 *)(master_00 + 0x14),
                               _DAT_7fff62431778);
      if (cVar2 == '\0') {
        self_00 = (undefined *)FUN_7fff5fe84400(*(undefined4 *)(master_00 + 0x14),0);
        if (self_00 != (undefined *)0x0) {
          if (*(longlong *)(self + 0x10) != 0) {
            FUN_7fff6088cb20(*(longlong *)(self + 0x10),*(undefined4 *)(master_00 + 0x14),self_00,
                             _DAT_7fff624315f0);
            goto LAB_7fff5fe85879;
          }
          break;
        }
      }
      else {
        if (*(longlong *)(self + 0x10) == 0) break;
        self_00 = (undefined *)
                  FUN_7fff6087c780(*(longlong *)(self + 0x10),*(undefined4 *)(master_00 + 0x14));
        if (self_00 != (undefined *)0x0) {
LAB_7fff5fe85879:
          MobPropertyBase_TryAddProperty(self_00,master_00,(undefined *)0x0);
        }
      }
      uVar3 = uVar3 + 1;
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

