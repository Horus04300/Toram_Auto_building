
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkillBufferManager_OnAbnormalDamaged(undefined *thisObject,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  char cVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong lVar6;
  undefined8 uStack_68;
  undefined8 uStack_60;
  longlong *plStack_58;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  longlong *plStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  longlong *plStack_28;
  
  if (DAT_7ffe9cadf568 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934728);
    FUN_7ffe9996d590(&DAT_7ffe9c946d08);
    FUN_7ffe9996d590(&DAT_7ffe9c904798);
    FUN_7ffe9996d590(&DAT_7ffe9c904868);
    FUN_7ffe9996d590(&DAT_7ffe9c946dc8);
    FUN_7ffe9996d590(0x7ffe9c946e90);
    FUN_7ffe9996d590(0x7ffe9c904938);
    FUN_7ffe9996d590(&DAT_7ffe9c953398);
    FUN_7ffe9996d590(&DAT_7ffe9c953530);
    FUN_7ffe9996d590(&DAT_7ffe9c9532d0);
    FUN_7ffe9996d590(&DAT_7ffe9c972860);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc400);
    DAT_7ffe9cadf568 = '\x01';
  }
  uStack_50 = 0;
  puStack_48 = (undefined8 *)0x0;
  plStack_40 = (longlong *)0x0;
  lVar5 = func_0x7ffe99940040(_DAT_7ffe9c972860);
  FUN_7ffe9af8a010(lVar5,_DAT_7ffe9c9532d0);
  if (*(longlong *)(thisObject + 0x40) != 0) {
    lVar6 = FUN_7ffe9acd27a0(*(longlong *)(thisObject + 0x40),_DAT_7ffe9c934728);
    if (lVar6 != 0) {
      FUN_7ffe9af415c0(&uStack_68,lVar6,_DAT_7ffe9c8fc400);
      uStack_38 = (undefined4)uStack_68;
      uStack_34 = uStack_68._4_4_;
      uStack_30 = (undefined4)uStack_60;
      uStack_2c = uStack_60._4_4_;
      plStack_28 = plStack_58;
      uStack_68 = 0;
      uStack_60 = (undefined8 *)&uStack_38;
LAB_7ffe9a7c9ce0:
      cVar3 = FUN_7ffe9ae37290(&uStack_38,_DAT_7ffe9c946dc8);
      plVar2 = plStack_28;
      if (cVar3 != '\0') {
        if (plStack_28 != (longlong *)0x0) goto code_r0x7ffe9a7c9d03;
        goto LAB_7ffe9a7c9e47;
      }
      func_0x7ffe999c3920(&uStack_38,_DAT_7ffe9c946d08);
      if (lVar5 != 0) {
        FUN_7ffe9af836a0(&uStack_68,lVar5,_DAT_7ffe9c953530);
        uStack_50 = uStack_68;
        puStack_48 = uStack_60;
        plStack_40 = plStack_58;
        uStack_68 = 0;
        uStack_60 = &uStack_50;
        while( true ) {
          cVar3 = FUN_7ffe9ae28ed0(&uStack_50,_DAT_7ffe9c904868);
          if (cVar3 == '\0') {
            func_0x7ffe999c3920(&uStack_50,_DAT_7ffe9c904798);
            return;
          }
          if (plStack_40 == (longlong *)0x0) break;
          uVar4 = (**(code **)(*plStack_40 + 0x178))
                            (plStack_40,*(undefined8 *)(*plStack_40 + 0x180));
          FUN_7ffe9a7cafa0(thisObject,uVar4,0);
        }
LAB_7ffe9a7c9e53:
        FUN_7ffe9996d7a0();
        FUN_7ffe998fa550();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
code_r0x7ffe9a7c9d03:
  cVar3 = (**(code **)(*plStack_28 + 0x1a8))(plStack_28,*(undefined8 *)(*plStack_28 + 0x1b0));
  if (cVar3 != '\0') {
    if (lVar5 == 0) {
      FUN_7ffe9996d7a0();
LAB_7ffe9a7c9e47:
      FUN_7ffe9996d7a0();
      FUN_7ffe998fa550();
      goto LAB_7ffe9a7c9e53;
    }
    FUN_7ffe99743100(lVar5,plVar2,_DAT_7ffe9c953398);
  }
  goto LAB_7ffe9a7c9ce0;
}

