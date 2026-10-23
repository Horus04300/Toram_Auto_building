
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidBossActionManager_SetPartsMaster
               (undefined *self,byte id,undefined *master,int hp,undefined *methodInfo)

{
  undefined4 uVar1;
  longlong lVar2;
  code *pcVar3;
  longlong lVar4;
  longlong lVar5;
  ushort uVar6;
  short difficulty;
  undefined8 *puVar7;
  undefined *puVar8;
  longlong lVar9;
  longlong *plVar10;
  undefined8 unaff_RDI;
  
  if (DAT_7ffe9cadd537 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c952f98);
    FUN_7ffe9996d590(&DAT_7ffe9c92ac28);
    FUN_7ffe9996d590(&DAT_7ffe9c936530);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    DAT_7ffe9cadd537 = '\x01';
  }
  puVar8 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (puVar8 != (undefined *)0x0) {
    difficulty = RoomManager_GetAreaLevel(puVar8,(undefined *)0x0);
    uVar1 = *(undefined4 *)(self + 0x160);
    puVar8 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c92ac28);
    MobPartsStatus__ctor(puVar8,master,hp,difficulty,(undefined *)0x0);
    *(undefined4 *)(puVar8 + 0x38) = uVar1;
    if (*(longlong *)(self + 0x168) != 0) {
      FUN_7ffe9aceb930(*(longlong *)(self + 0x168),id,puVar8,_DAT_7ffe9c952f98);
      lVar4 = _DAT_7ffe9c936530;
      lVar2 = *(longlong *)(self + 0x158);
      if (lVar2 != 0) {
        lVar9 = func_0x7ffe9996c920(lVar2,_DAT_7ffe9c936530);
        lVar5 = _DAT_7ffe9c936530;
        if (lVar9 == 0) {
          FUN_7ffe9996c950(lVar2,lVar4);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        plVar10 = (longlong *)func_0x7ffe9996c920(lVar2,_DAT_7ffe9c936530);
        if (plVar10 == (longlong *)0x0) {
          FUN_7ffe9996c950(lVar2,lVar5);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        lVar2 = *plVar10;
        uVar6 = 0;
        if (*(ushort *)(lVar2 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar2 + 0xb0) + (ulonglong)uVar6 * 0x10) ==
                _DAT_7ffe9c936530) {
              puVar7 = (undefined8 *)
                       ((longlong)
                        (*(int *)(*(longlong *)(lVar2 + 0xb0) + 8 + (ulonglong)uVar6 * 0x10) + 1) *
                        0x10 + 0x138 + lVar2);
              goto LAB_7ffe9974d4f3;
            }
            uVar6 = uVar6 + 1;
          } while (uVar6 < *(ushort *)(lVar2 + 0x12e));
        }
        puVar7 = (undefined8 *)FUN_7ffe998ce540(plVar10,_DAT_7ffe9c936530,1,id,unaff_RDI);
LAB_7ffe9974d4f3:
                    /* WARNING: Could not recover jumptable at 0x7ffe9974d510. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)*puVar7)(plVar10,id,puVar8,puVar7[1]);
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

