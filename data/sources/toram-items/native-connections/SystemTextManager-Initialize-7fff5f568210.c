
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SystemTextManager_Initialize(undefined *self,undefined *binary,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong lVar3;
  longlong *plVar4;
  undefined8 uVar5;
  longlong lVar6;
  int iVar7;
  longlong *plStackX_20;
  longlong lStack_88;
  undefined8 uStack_80;
  undefined8 uStack_58;
  longlong *plStack_50;
  undefined8 uStack_48;
  longlong **pplStack_40;
  
  if (DAT_7fff625e1582 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b500);
    FUN_7fff5f47d450(&DAT_7fff62448100);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff624717c0);
    FUN_7fff5f47d450(&DAT_7fff6246bad0);
    DAT_7fff625e1582 = '\x01';
  }
  iVar7 = 0;
  lStack_88 = 0;
  plStackX_20 = (longlong *)0x0;
  self[0x11] = 0;
  lVar3 = func_0x7fff5f44ff00(_DAT_7fff624717c0);
  FUN_7fff60fcae90(lVar3,binary,0);
  uStack_58 = 0;
  plStack_50 = &lStack_88;
  lStack_88 = lVar3;
  plVar4 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6244b500);
  FUN_7fff60fd77f0(plVar4,lVar3,0);
  uStack_48 = 0;
  pplStack_40 = &plStackX_20;
  plStackX_20 = plVar4;
  if (plVar4 != (longlong *)0x0) {
    iVar2 = (**(code **)(*plVar4 + 0x228))(plVar4,*(undefined8 *)(*plVar4 + 0x230));
    while( true ) {
      if (iVar2 <= iVar7) {
        if (plStackX_20 != (longlong *)0x0) {
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
        }
        if (lStack_88 != 0) {
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
        }
        self[0x10] = 1;
        self[0x12] = 0;
        return;
      }
      if (plStackX_20 == (longlong *)0x0) break;
      uStack_80 = (**(code **)(*plStackX_20 + 0x298))
                            (plStackX_20,*(undefined8 *)(*plStackX_20 + 0x2a0));
      if (plStackX_20 == (longlong *)0x0) {
LAB_7fff5f568496:
        FUN_7fff5f47d660();
        break;
      }
      uVar5 = (**(code **)(*plStackX_20 + 0x298))(plStackX_20,*(undefined8 *)(*plStackX_20 + 0x2a0))
      ;
      lVar3 = *(longlong *)(self + 0x18);
      lVar6 = func_0x7fff5f44ff00(_DAT_7fff6246bad0);
      func_0x7fff5f4d3920(lVar6,0);
      *(undefined8 *)(lVar6 + 0x10) = uVar5;
      thunk_FUN_7fff5f491fd0();
      if (lVar3 == 0) {
        FUN_7fff5f47d660();
        goto LAB_7fff5f568496;
      }
      FUN_7fff608c0a20(lVar3,uStack_80,lVar6,_DAT_7fff62448100);
      iVar7 = iVar7 + 1;
    }
    FUN_7fff5f47d660();
  }
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

