
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferManager_Initialize
               (undefined *self,undefined *cartData,undefined *equips,undefined *methodInfo)

{
  code *pcVar1;
  undefined8 uVar2;
  char cVar3;
  longlong lVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong lVar7;
  uint uVar8;
  longlong alStackX_18 [2];
  
  if (DAT_7ffe9cade78f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9658b0);
    FUN_7ffe9996d590(&DAT_7ffe9c909108);
    FUN_7ffe9996d590(&DAT_7ffe9c93b028);
    FUN_7ffe9996d590(&DAT_7ffe9c9448f8);
    FUN_7ffe9996d590(&DAT_7ffe9c946738);
    FUN_7ffe9996d590(&DAT_7ffe9c956b88);
    DAT_7ffe9cade78f = '\x01';
  }
  uVar8 = 0;
  alStackX_18[0] = 0;
  GemCartBufferManager_ClearBuffer(self,(undefined *)0x0);
  if ((equips != (undefined *)0x0) && (cartData != (undefined *)0x0)) {
    for (; (int)uVar8 < *(int *)(equips + 0x18); uVar8 = uVar8 + 1) {
      lVar4 = func_0x7ffe99940040(_DAT_7ffe9c956b88);
      func_0x7ffe999c3920(lVar4,0);
      if (*(uint *)(equips + 0x18) <= uVar8) {
        FUN_7ffe9996d790();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if (lVar4 == 0) {
LAB_7ffe9a5b3350:
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      *(undefined8 *)(lVar4 + 0x10) = *(undefined8 *)(equips + (longlong)(int)uVar8 * 8 + 0x20);
      il2cpp_write_barrier_0();
      uVar5 = func_0x7ffe99940040(_DAT_7ffe9c93b028);
      FUN_7ffe9af13420(uVar5,lVar4,_DAT_7ffe9c946738);
      lVar6 = FUN_7ffe9ab854c0(cartData,uVar5,_DAT_7ffe9c909108);
      if (lVar6 != 0) {
        GemCartBufferManager_UpdateEquipGemCartData
                  (self,*(short *)(lVar6 + 0x30),*(short *)(lVar6 + 0x32),(undefined *)0x0);
        if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b3350;
        cVar3 = FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),*(undefined2 *)(lVar6 + 0x30),
                                 alStackX_18);
        if ((cVar3 != '\0') &&
           (lVar7 = func_0x7ffe9996c920(alStackX_18[0]), lVar6 = alStackX_18[0],
           uVar5 = _DAT_7ffe9c9448f8, lVar7 != 0)) {
          if ((*(longlong *)(lVar4 + 0x10) == 0) || (alStackX_18[0] == 0)) goto LAB_7ffe9a5b3350;
          lVar4 = func_0x7ffe9996c920(alStackX_18[0],_DAT_7ffe9c9448f8);
          uVar2 = _DAT_7ffe9c9448f8;
          if (lVar4 == 0) {
            FUN_7ffe9996c950(lVar6,uVar5);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          lVar4 = func_0x7ffe9996c920(lVar6,_DAT_7ffe9c9448f8);
          if (lVar4 == 0) {
            FUN_7ffe9996c950(lVar6,uVar2);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          FUN_7ffe99742cf0(0,_DAT_7ffe9c9448f8,lVar4);
        }
      }
    }
  }
  return;
}

