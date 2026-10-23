
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobActionManager_SetPartsMaster
               (undefined *self,byte id,undefined *master,int hp,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  ushort uVar3;
  short difficulty;
  undefined8 *puVar4;
  longlong lVar5;
  undefined *self_00;
  undefined8 unaff_RDI;
  
  if (DAT_7fff625e4c5d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62459e78);
    FUN_7fff5f47d450(&DAT_7fff6243dd98);
    FUN_7fff5f47d450(&DAT_7fff623f6608);
    FUN_7fff5f47d450(&DAT_7fff6245c360);
    DAT_7fff625e4c5d = '\x01';
  }
  lVar5 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
  if (lVar5 != 0) {
    difficulty = FUN_7fff6010c360(lVar5,0);
    self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623f6608);
    MobPartsStatus__ctor(self_00,master,hp,difficulty,(undefined *)0x0);
    if (*(longlong *)(self + 0x168) != 0) {
      FUN_7fff607f5cf0(*(longlong *)(self + 0x168),id,self_00,_DAT_7fff62459e78);
      plVar1 = *(longlong **)(self + 0x180);
      if (plVar1 != (longlong *)0x0) {
        lVar5 = *plVar1;
        uVar3 = 0;
        if (*(ushort *)(lVar5 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar5 + 0xb0) + (ulonglong)uVar3 * 0x10) ==
                _DAT_7fff6243dd98) {
              puVar4 = (undefined8 *)
                       ((longlong)
                        (*(int *)(*(longlong *)(lVar5 + 0xb0) + 8 + (ulonglong)uVar3 * 0x10) + 1) *
                        0x10 + 0x138 + lVar5);
              goto LAB_7fff5f25d4f3;
            }
            uVar3 = uVar3 + 1;
          } while (uVar3 < *(ushort *)(lVar5 + 0x12e));
        }
        puVar4 = (undefined8 *)FUN_7fff5f3de400(plVar1,_DAT_7fff6243dd98,1,id,unaff_RDI);
LAB_7fff5f25d4f3:
                    /* WARNING: Could not recover jumptable at 0x7fff5f25d510. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)*puVar4)(plVar1,id,self_00,puVar4[1]);
        return;
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

