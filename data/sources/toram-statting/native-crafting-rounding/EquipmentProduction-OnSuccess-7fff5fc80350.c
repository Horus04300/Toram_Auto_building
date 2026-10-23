
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EquipmentProduction_OnSuccess(undefined *self,undefined *response,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  ulonglong uVar5;
  char cVar6;
  longlong lVar7;
  uint uVar8;
  undefined8 unaff_RDI;
  
  if (DAT_7fff625e42ab == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62459938);
    DAT_7fff625e42ab = '\x01';
  }
  if (*(longlong *)(self + 0x28) != 0) {
    *(undefined **)(*(longlong *)(self + 0x28) + 0x1e8) = response;
    thunk_FUN_7fff5f491fd0();
    lVar7 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if ((response != (undefined *)0x0) && (lVar7 != 0)) {
      func_0x7fff603e4340(lVar7,*(undefined8 *)(response + 0x28),0);
      lVar7 = FUN_7fff60c4bc00(_DAT_7fff62459938);
      if (lVar7 != 0) {
        FUN_7fff603e4070(lVar7,*(undefined4 *)(response + 0x38),0);
        lVar7 = FUN_7fff60c4bc00(_DAT_7fff62459938);
        if (lVar7 != 0) {
          lVar1 = *(longlong *)(response + 0x30);
          if ((*(longlong *)(lVar7 + 0x70) == 0) ||
             (lVar7 = FUN_7fff5ff8a970(*(longlong *)(lVar7 + 0x70),0,0), lVar7 == 0)) {
            FUN_7fff5f47d660();
            pcVar4 = (code *)swi(3);
            (*pcVar4)();
            return;
          }
          if (lVar1 != 0) {
            uVar8 = 0;
            while ((int)uVar8 < (int)*(uint *)(lVar1 + 0x18)) {
              if (*(uint *)(lVar1 + 0x18) <= uVar8) {
                FUN_7fff5f47d650();
                pcVar4 = (code *)swi(3);
                (*pcVar4)();
                return;
              }
              lVar2 = *(longlong *)(lVar1 + 0x20 + (longlong)(int)uVar8 * 8);
              if (DAT_7fff625e5308 == '\0') {
                FUN_7fff5f47d450(&DAT_7fff62463550);
                FUN_7fff5f47d450(&DAT_7fff624636e8);
                FUN_7fff5f47d450(&DAT_7fff62463880);
                DAT_7fff625e5308 = '\x01';
              }
              if (lVar2 == 0) {
LAB_7fff5ff1aed0:
                FUN_7fff5f47d660();
                pcVar4 = (code *)swi(3);
                (*pcVar4)();
                return;
              }
              if (*(longlong *)(lVar7 + 0x10) == 0) goto LAB_7fff5ff1aed0;
              uVar5 = (ulonglong)
                      CONCAT14(*(undefined1 *)(lVar2 + 0x21),(uint)*(byte *)(lVar2 + 0x20));
              cVar6 = FUN_7fff608e3270(*(longlong *)(lVar7 + 0x10),uVar5,_DAT_7fff624636e8);
              lVar3 = *(longlong *)(lVar7 + 0x10);
              if (cVar6 == '\0') {
                if (lVar3 == 0) goto LAB_7fff5ff1aed0;
                FUN_7fff608e31b0(lVar3,uVar5,lVar2,_DAT_7fff62463550);
                uVar8 = uVar8 + 1;
              }
              else {
                if (lVar3 == 0) goto LAB_7fff5ff1aed0;
                FUN_7fff608fa1a0(lVar3,uVar5,lVar2,_DAT_7fff62463880,unaff_RDI);
                uVar8 = uVar8 + 1;
              }
            }
          }
          return;
        }
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

