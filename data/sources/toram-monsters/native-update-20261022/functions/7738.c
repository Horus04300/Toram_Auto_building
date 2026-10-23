
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobActionManager_SetPartsMaster
               (undefined *self,byte id,undefined *master,int hp,undefined *methodInfo)

{
  longlong lVar1;
  longlong *plVar2;
  code *pcVar3;
  ushort uVar4;
  short difficulty;
  undefined8 *puVar5;
  undefined *puVar6;
  undefined8 unaff_RDI;
  
  if (DAT_7ffe9cadd505 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c952f98);
    FUN_7ffe9996d590(&DAT_7ffe9c936530);
    FUN_7ffe9996d590(&DAT_7ffe9c8eec18);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    DAT_7ffe9cadd505 = '\x01';
  }
  puVar6 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (puVar6 != (undefined *)0x0) {
    difficulty = RoomManager_GetAreaLevel(puVar6,(undefined *)0x0);
    puVar6 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8eec18);
    MobPartsStatus__ctor(puVar6,master,hp,difficulty,(undefined *)0x0);
    if (*(longlong *)(self + 0x168) != 0) {
      FUN_7ffe9aceb930(*(longlong *)(self + 0x168),id,puVar6,_DAT_7ffe9c952f98);
      plVar2 = *(longlong **)(self + 0x180);
      if (plVar2 != (longlong *)0x0) {
        lVar1 = *plVar2;
        uVar4 = 0;
        if (*(ushort *)(lVar1 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar4 * 0x10) ==
                _DAT_7ffe9c936530) {
              puVar5 = (undefined8 *)
                       ((longlong)
                        (*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar4 * 0x10) + 1) *
                        0x10 + 0x138 + lVar1);
              goto LAB_7ffe9974d4f3;
            }
            uVar4 = uVar4 + 1;
          } while (uVar4 < *(ushort *)(lVar1 + 0x12e));
        }
        puVar5 = (undefined8 *)FUN_7ffe998ce540(plVar2,_DAT_7ffe9c936530,1,id,unaff_RDI);
LAB_7ffe9974d4f3:
                    /* WARNING: Could not recover jumptable at 0x7ffe9974d510. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)*puVar5)(plVar2,id,puVar6,puVar5[1]);
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

