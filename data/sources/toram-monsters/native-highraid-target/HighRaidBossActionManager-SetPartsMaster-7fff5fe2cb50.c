
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidBossActionManager_SetPartsMaster
               (undefined *self,byte id,undefined *master,int hp,undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  longlong lVar3;
  longlong lVar4;
  ushort uVar5;
  short difficulty;
  undefined8 *puVar6;
  longlong lVar7;
  undefined *self_00;
  longlong lVar8;
  longlong *plVar9;
  undefined8 unaff_RDI;
  
  if (DAT_7fff625e4c8f == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62459e78);
    FUN_7fff5f47d450(&DAT_7fff624324b0);
    FUN_7fff5f47d450(&DAT_7fff6243dd98);
    FUN_7fff5f47d450(&DAT_7fff6245c360);
    DAT_7fff625e4c8f = '\x01';
  }
  lVar7 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
  if (lVar7 != 0) {
    difficulty = FUN_7fff6010c360(lVar7,0);
    uVar1 = *(undefined4 *)(self + 0x160);
    self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff624324b0);
    MobPartsStatus__ctor(self_00,master,hp,difficulty,(undefined *)0x0);
    *(undefined4 *)(self_00 + 0x38) = uVar1;
    if (*(longlong *)(self + 0x168) != 0) {
      FUN_7fff607f5cf0(*(longlong *)(self + 0x168),id,self_00,_DAT_7fff62459e78);
      lVar3 = _DAT_7fff6243dd98;
      lVar7 = *(longlong *)(self + 0x158);
      if (lVar7 != 0) {
        lVar8 = func_0x7fff5f47c7e0(lVar7,_DAT_7fff6243dd98);
        lVar4 = _DAT_7fff6243dd98;
        if (lVar8 == 0) {
          FUN_7fff5f47c810(lVar7,lVar3);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        plVar9 = (longlong *)func_0x7fff5f47c7e0(lVar7,_DAT_7fff6243dd98);
        if (plVar9 == (longlong *)0x0) {
          FUN_7fff5f47c810(lVar7,lVar4);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        lVar7 = *plVar9;
        uVar5 = 0;
        if (*(ushort *)(lVar7 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar7 + 0xb0) + (ulonglong)uVar5 * 0x10) ==
                _DAT_7fff6243dd98) {
              puVar6 = (undefined8 *)
                       ((longlong)
                        (*(int *)(*(longlong *)(lVar7 + 0xb0) + 8 + (ulonglong)uVar5 * 0x10) + 1) *
                        0x10 + 0x138 + lVar7);
              goto LAB_7fff5f25d4f3;
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < *(ushort *)(lVar7 + 0x12e));
        }
        puVar6 = (undefined8 *)FUN_7fff5f3de400(plVar9,_DAT_7fff6243dd98,1,id,unaff_RDI);
LAB_7fff5f25d4f3:
                    /* WARNING: Could not recover jumptable at 0x7fff5f25d510. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)*puVar6)(plVar9,id,self_00,puVar6[1]);
        return;
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

