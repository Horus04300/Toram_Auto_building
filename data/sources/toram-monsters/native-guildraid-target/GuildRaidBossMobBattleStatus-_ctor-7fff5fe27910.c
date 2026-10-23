
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobBattleStatus__ctor
               (undefined *self,undefined *statusMaster,undefined *abnormalManager,
               undefined *buffManager,int level,undefined *randomProperty,undefined *methodInfo)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  uint uVar4;
  uint uVar5;
  
  if (DAT_7fff625e4c6d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406160);
    FUN_7fff5f47d450(&DAT_7fff6241a798);
    FUN_7fff5f47d450(&DAT_7fff623f77e8);
    DAT_7fff625e4c6d = '\x01';
  }
  *(undefined4 *)(self + 0x50) = 1;
  GuildRaidRoomData_LoadAsset(self,(undefined *)0x0);
  *(undefined **)(self + 0x20) = statusMaster;
  thunk_FUN_7fff5f491fd0();
  *(undefined **)(self + 0x28) = abnormalManager;
  thunk_FUN_7fff5f491fd0();
  *(undefined **)(self + 0x30) = buffManager;
  thunk_FUN_7fff5f491fd0();
  *(undefined **)(self + 0x48) = randomProperty;
  *(int *)(self + 0x10) = level;
  thunk_FUN_7fff5f491fd0();
  uVar2 = func_0x7fff5f44ff00(_DAT_7fff6241a798);
  FUN_7fff6082b860(uVar2,_DAT_7fff62406160);
  *(undefined8 *)(self + 0x18) = uVar2;
  thunk_FUN_7fff5f491fd0();
  uVar2 = func_0x7fff5f44ff00(_DAT_7fff623f77e8);
  FUN_7fff5fe858c0(uVar2,0);
  *(undefined8 *)(self + 0x40) = uVar2;
  thunk_FUN_7fff5f491fd0();
  if (*(longlong *)(self + 0x40) != 0) {
    FUN_7fff5fe85400(*(longlong *)(self + 0x40),0);
    if ((*(longlong *)(self + 0x20) != 0) &&
       (lVar3 = *(longlong *)(*(longlong *)(self + 0x20) + 0xa0), lVar3 != 0)) {
      lVar3 = FUN_7fff5fe85450(lVar3,0);
      uVar4 = 0;
      if ((lVar3 != 0) && (uVar5 = uVar4, *(longlong *)(lVar3 + 0x18) != 0)) {
        for (; (int)uVar5 < (int)*(uint *)(lVar3 + 0x18); uVar5 = uVar5 + 1) {
          if (*(uint *)(lVar3 + 0x18) <= uVar5) goto LAB_7fff5fe27ae0;
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff5fe27ae6;
          FUN_7fff5fe85330(*(longlong *)(self + 0x40),
                           *(undefined8 *)(lVar3 + 0x20 + (longlong)(int)uVar5 * 8),0);
        }
      }
      lVar3 = *(longlong *)(self + 0x48);
      if ((lVar3 != 0) && (*(longlong *)(lVar3 + 0x18) != 0)) {
        for (; (int)uVar4 < *(int *)(lVar3 + 0x18); uVar4 = uVar4 + 1) {
          if (*(uint *)(lVar3 + 0x18) <= uVar4) {
LAB_7fff5fe27ae0:
            FUN_7fff5f47d650();
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff5fe27ae6;
          FUN_7fff5fe85330(*(longlong *)(self + 0x40),
                           *(undefined8 *)(lVar3 + 0x20 + (longlong)(int)uVar4 * 8),0);
        }
      }
      return;
    }
  }
LAB_7fff5fe27ae6:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

