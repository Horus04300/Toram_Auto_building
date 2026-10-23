
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrant_OnGrantCheckButton(undefined *self,undefined *methodInfo)

{
  int iVar1;
  longlong lVar2;
  longlong lVar3;
  longlong *plVar4;
  bool bVar5;
  code *pcVar6;
  int iVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  uint uVar11;
  
  if (DAT_7fff625e4223 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62436790);
    FUN_7fff5f47d450(&DAT_7fff624732a8);
    FUN_7fff5f47d450(&DAT_7fff62408ab0);
    DAT_7fff625e4223 = '\x01';
  }
  if (*(longlong *)(self + 0xa8) != 0) {
    FUN_7fff5f51e550();
    lVar2 = *(longlong *)(self + 0xb8);
    lVar3 = *(longlong *)(self + 0x140);
    if (*(longlong *)(self + 0x120) != 0) {
      bVar5 = true;
      lVar8 = FUN_7fff5fc69070();
      uVar11 = 0;
      if (lVar8 != 0) {
        while ((int)uVar11 < (int)*(uint *)(lVar8 + 0x18)) {
          if (bVar5) {
            if (*(uint *)(lVar8 + 0x18) <= uVar11) {
              FUN_7fff5f47d650();
              pcVar6 = (code *)swi(3);
              (*pcVar6)();
              return;
            }
            iVar1 = *(int *)(lVar8 + 0x20 + (longlong)(int)uVar11 * 4);
            if ((lVar3 == 0) || (lVar9 = FUN_7fff5ff8a970(lVar3,0), lVar9 == 0))
            goto LAB_7fff5fc7290c;
            iVar7 = FUN_7fff5ff1ac40(lVar9,uVar11);
            bVar5 = iVar1 <= iVar7;
            uVar11 = uVar11 + 1;
          }
          else {
            bVar5 = false;
            uVar11 = uVar11 + 1;
          }
        }
        if (lVar2 != 0) {
          FUN_7fff5fc86a90(lVar2,bVar5,0);
          func_0x7fff5f4d3920(_DAT_7fff62408ab0,0);
          plVar4 = *(longlong **)(self + 0x28);
          uVar10 = func_0x7fff5f44ff00(_DAT_7fff62436790);
          FUN_7fff5f4f6880(uVar10,self,_DAT_7fff624732a8,0);
          if (plVar4 != (longlong *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x7fff5fc72905. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            (**(code **)(*plVar4 + 0x1c8))(plVar4,uVar10,*(undefined8 *)(*plVar4 + 0x1d0));
            return;
          }
        }
      }
    }
  }
LAB_7fff5fc7290c:
  FUN_7fff5f47d660();
  pcVar6 = (code *)swi(3);
  (*pcVar6)();
  return;
}

