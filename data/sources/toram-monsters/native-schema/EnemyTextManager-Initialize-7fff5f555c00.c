
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EnemyTextManager_Initialize(undefined *self,undefined *binary,undefined *methodInfo)

{
  code *pcVar1;
  undefined4 uVar2;
  longlong lVar3;
  longlong *plVar4;
  undefined8 uVar5;
  undefined *self_00;
  int iVar6;
  longlong *plStack_88;
  int iStack_80;
  longlong alStack_78 [2];
  longlong *plStack_68;
  undefined8 uStack_60;
  longlong **pplStack_58;
  
  if (DAT_7fff625e14f5 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b500);
    FUN_7fff5f47d450(&DAT_7fff624103e0);
    FUN_7fff5f47d450(&DAT_7fff624108c0);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff624717c0);
    FUN_7fff5f47d450(&DAT_7fff6246bad0);
    DAT_7fff625e14f5 = '\x01';
  }
  iVar6 = 0;
  alStack_78[0] = 0;
  plStack_88 = (longlong *)0x0;
  self[0x11] = 0;
  if (*(longlong *)(self + 0x18) != 0) {
    FUN_7fff607d86f0(*(longlong *)(self + 0x18),_DAT_7fff624103e0);
    lVar3 = func_0x7fff5f44ff00(_DAT_7fff624717c0);
    FUN_7fff60fcae90(lVar3,binary,0);
    alStack_78[1] = 0;
    plStack_68 = alStack_78;
    alStack_78[0] = lVar3;
    plVar4 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6244b500);
    FUN_7fff60fd77f0(plVar4,lVar3,0);
    uStack_60 = 0;
    pplStack_58 = &plStack_88;
    plStack_88 = plVar4;
    if (plVar4 != (longlong *)0x0) {
      iStack_80 = (**(code **)(*plVar4 + 0x228))(plVar4,*(undefined8 *)(*plVar4 + 0x230));
      while( true ) {
        if (iStack_80 <= iVar6) {
          if (plStack_88 != (longlong *)0x0) {
            FUN_7fff5f253010(0,_DAT_7fff624413c0);
          }
          if (alStack_78[0] != 0) {
            FUN_7fff5f253010(0,_DAT_7fff624413c0);
          }
          self[0x10] = 1;
          self[0x12] = 0;
          return;
        }
        if (plStack_88 == (longlong *)0x0) break;
        uVar2 = (**(code **)(*plStack_88 + 0x228))(plStack_88,*(undefined8 *)(*plStack_88 + 0x230));
        if (plStack_88 == (longlong *)0x0) {
LAB_7fff5f555ed9:
          FUN_7fff5f47d660();
          break;
        }
        uVar5 = (**(code **)(*plStack_88 + 0x298))();
        lVar3 = *(longlong *)(self + 0x18);
        self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6246bad0);
        _loadFieldData_d__125_System_IDisposable_Dispose(self_00,(undefined *)0x0);
        *(undefined8 *)(self_00 + 0x10) = uVar5;
        thunk_FUN_7fff5f491fd0();
        if (lVar3 == 0) {
          FUN_7fff5f47d660();
          goto LAB_7fff5f555ed9;
        }
        FUN_7fff608690c0(lVar3,uVar2,self_00,_DAT_7fff624108c0);
        iVar6 = iVar6 + 1;
      }
      FUN_7fff5f47d660();
    }
    FUN_7fff5f47d660();
    FUN_7fff5f40a410();
    FUN_7fff5f40a410();
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

