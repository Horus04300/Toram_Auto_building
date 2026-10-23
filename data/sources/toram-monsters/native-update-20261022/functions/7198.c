
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BossMobActionManager_SetPartsMaster
               (undefined *self,byte id,undefined *master,int hp,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  longlong lVar3;
  longlong lVar4;
  ushort uVar5;
  short difficulty;
  undefined8 *puVar6;
  undefined *puVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined8 unaff_RDI;
  
  if (DAT_7ffe9cadd1c4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c952f98);
    FUN_7ffe9996d590(&DAT_7ffe9c936530);
    FUN_7ffe9996d590(&DAT_7ffe9c8eec18);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    DAT_7ffe9cadd1c4 = '\x01';
  }
  puVar7 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (puVar7 != (undefined *)0x0) {
    difficulty = RoomManager_GetAreaLevel(puVar7,(undefined *)0x0);
    puVar7 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8eec18);
    MobPartsStatus__ctor(puVar7,master,hp,difficulty,(undefined *)0x0);
    if (*(longlong *)(self + 0x168) != 0) {
      FUN_7ffe9aceb930(*(longlong *)(self + 0x168),id,puVar7,_DAT_7ffe9c952f98);
      lVar3 = _DAT_7ffe9c936530;
      lVar1 = *(longlong *)(self + 0x158);
      if (lVar1 != 0) {
        lVar8 = func_0x7ffe9996c920(lVar1,_DAT_7ffe9c936530);
        lVar4 = _DAT_7ffe9c936530;
        if (lVar8 == 0) {
          FUN_7ffe9996c950(lVar1,lVar3);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        plVar9 = (longlong *)func_0x7ffe9996c920(lVar1,_DAT_7ffe9c936530);
        if (plVar9 == (longlong *)0x0) {
          FUN_7ffe9996c950(lVar1,lVar4);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        lVar1 = *plVar9;
        uVar5 = 0;
        if (*(ushort *)(lVar1 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar5 * 0x10) ==
                _DAT_7ffe9c936530) {
              puVar6 = (undefined8 *)
                       ((longlong)
                        (*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar5 * 0x10) + 1) *
                        0x10 + 0x138 + lVar1);
              goto LAB_7ffe9974d4f3;
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < *(ushort *)(lVar1 + 0x12e));
        }
        puVar6 = (undefined8 *)FUN_7ffe998ce540(plVar9,_DAT_7ffe9c936530,1,id,unaff_RDI);
LAB_7ffe9974d4f3:
                    /* WARNING: Could not recover jumptable at 0x7ffe9974d510. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)*puVar6)(plVar9,id,puVar7,puVar6[1]);
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

