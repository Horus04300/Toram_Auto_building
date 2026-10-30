
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MasterRegistletManager_ReadRegistletData(undefined *self,undefined *data,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  short sVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong lVar8;
  int iVar9;
  longlong *plStack_80;
  longlong *plStack_78;
  undefined8 uStack_70;
  longlong **pplStack_68;
  undefined8 uStack_60;
  longlong **pplStack_58;
  
  if (DAT_7ffe9cade7c2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943bb8);
    FUN_7ffe9996d590(&DAT_7ffe9c965be0);
    FUN_7ffe9996d590(&DAT_7ffe9c965cb0);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    DAT_7ffe9cade7c2 = '\x01';
  }
  iVar9 = 0;
  plStack_78 = (longlong *)0x0;
  plStack_80 = (longlong *)0x0;
  if (*(longlong *)(self + 0x20) == 0) {
    FUN_7ffe9996d7a0();
LAB_7ffe9a5b4ed6:
    FUN_7ffe9996d7a0();
LAB_7ffe9a5b4edc:
    FUN_7ffe9996d7a0();
LAB_7ffe9a5b4ee1:
    FUN_7ffe9996d7a0();
LAB_7ffe9a5b4ee6:
    FUN_7ffe9996d7a0();
LAB_7ffe9a5b4eeb:
    FUN_7ffe9996d7a0();
  }
  else {
    FUN_7ffe9acce330(*(longlong *)(self + 0x20),_DAT_7ffe9c965cb0);
    plVar6 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c969f48);
    FUN_7ffe9b4c0ad0(plVar6,data,0);
    uStack_70 = 0;
    pplStack_68 = &plStack_78;
    plStack_78 = plVar6;
    plVar7 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c943bb8);
    FUN_7ffe9b4cd430(plVar7,plVar6,0);
    uStack_60 = 0;
    pplStack_58 = &plStack_80;
    plStack_80 = plVar7;
    if (plVar7 != (longlong *)0x0) {
      (**(code **)(*plVar7 + 0x228))(plVar7,*(undefined8 *)(*plVar7 + 0x230));
      if (plStack_80 != (longlong *)0x0) {
        sVar3 = (**(code **)(*plStack_80 + 0x208))(plStack_80,*(undefined8 *)(*plStack_80 + 0x210));
        for (; plVar6 = plStack_80, iVar9 < sVar3; iVar9 = iVar9 + 1) {
          if (DAT_7ffe9cade7c1 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c90df70);
            DAT_7ffe9cade7c1 = '\x01';
          }
          lVar8 = func_0x7ffe99940040(_DAT_7ffe9c90df70);
          func_0x7ffe999c3920(lVar8,0);
          if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a5b4ee1;
          uVar4 = (**(code **)(*plVar6 + 0x208))(plVar6,*(undefined8 *)(*plVar6 + 0x210));
          if (lVar8 == 0) goto LAB_7ffe9a5b4edc;
          *(undefined2 *)(lVar8 + 0x10) = uVar4;
          uVar4 = (**(code **)(*plVar6 + 0x208))(plVar6,*(undefined8 *)(*plVar6 + 0x210));
          *(undefined2 *)(lVar8 + 0x18) = uVar4;
          uVar5 = (**(code **)(*plVar6 + 0x228))(plVar6,*(undefined8 *)(*plVar6 + 0x230));
          *(undefined4 *)(lVar8 + 0x14) = uVar5;
          if (-1 < *(short *)(lVar8 + 0x10)) {
            if (*(longlong *)(self + 0x20) == 0) goto LAB_7ffe9a5b4ed6;
            FUN_7ffe9ad10e30(*(longlong *)(self + 0x20),*(short *)(lVar8 + 0x10),lVar8,
                             _DAT_7ffe9c965be0);
          }
        }
        if (plStack_80 != (longlong *)0x0) {
          (**(code **)(*plStack_80 + 0x198))(plStack_80,*(undefined8 *)(*plStack_80 + 0x1a0));
          if (plStack_80 != (longlong *)0x0) {
            FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
          }
          if (plStack_78 != (longlong *)0x0) {
            (**(code **)(*plStack_78 + 600))(plStack_78,*(undefined8 *)(*plStack_78 + 0x260));
            if (plStack_78 != (longlong *)0x0) {
              FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
            }
            return 1;
          }
          goto LAB_7ffe9a5b4efb;
        }
        goto LAB_7ffe9a5b4ee6;
      }
      goto LAB_7ffe9a5b4eeb;
    }
  }
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a5b4efb:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

