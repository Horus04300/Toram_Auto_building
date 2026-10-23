
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BossMobActionManager_SetPartsMaster
               (undefined *self,byte id,undefined *master,int hp,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  longlong lVar3;
  ushort uVar4;
  short difficulty;
  undefined8 *puVar5;
  longlong lVar6;
  undefined *self_00;
  longlong lVar7;
  longlong *plVar8;
  undefined8 unaff_RDI;
  
  if (DAT_7fff625e491f == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62459e78);
    FUN_7fff5f47d450(&DAT_7fff6243dd98);
    FUN_7fff5f47d450(&DAT_7fff623f6608);
    FUN_7fff5f47d450(&DAT_7fff6245c360);
    DAT_7fff625e491f = '\x01';
  }
  lVar6 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
  if (lVar6 != 0) {
    difficulty = FUN_7fff6010c360(lVar6,0);
    self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623f6608);
    MobPartsStatus__ctor(self_00,master,hp,difficulty,(undefined *)0x0);
    if (*(longlong *)(self + 0x168) != 0) {
      FUN_7fff607f5cf0(*(longlong *)(self + 0x168),id,self_00,_DAT_7fff62459e78);
      lVar2 = _DAT_7fff6243dd98;
      lVar6 = *(longlong *)(self + 0x158);
      if (lVar6 != 0) {
        lVar7 = func_0x7fff5f47c7e0(lVar6,_DAT_7fff6243dd98);
        lVar3 = _DAT_7fff6243dd98;
        if (lVar7 == 0) {
          FUN_7fff5f47c810(lVar6,lVar2);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        plVar8 = (longlong *)func_0x7fff5f47c7e0(lVar6,_DAT_7fff6243dd98);
        if (plVar8 == (longlong *)0x0) {
          FUN_7fff5f47c810(lVar6,lVar3);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        lVar6 = *plVar8;
        uVar4 = 0;
        if (*(ushort *)(lVar6 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar6 + 0xb0) + (ulonglong)uVar4 * 0x10) ==
                _DAT_7fff6243dd98) {
              puVar5 = (undefined8 *)
                       ((longlong)
                        (*(int *)(*(longlong *)(lVar6 + 0xb0) + 8 + (ulonglong)uVar4 * 0x10) + 1) *
                        0x10 + 0x138 + lVar6);
              goto LAB_7fff5f25d4f3;
            }
            uVar4 = uVar4 + 1;
          } while (uVar4 < *(ushort *)(lVar6 + 0x12e));
        }
        puVar5 = (undefined8 *)FUN_7fff5f3de400(plVar8,_DAT_7fff6243dd98,1,id,unaff_RDI);
LAB_7fff5f25d4f3:
                    /* WARNING: Could not recover jumptable at 0x7fff5f25d510. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)*puVar5)(plVar8,id,self_00,puVar5[1]);
        return;
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

