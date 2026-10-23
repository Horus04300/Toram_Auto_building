
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus_get_MagicDef(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  int iVar8;
  float afStackX_8 [4];
  int aiStackX_18 [2];
  undefined *puStackX_20;
  longlong *aplStack_38 [2];
  
  if (DAT_7ffe9cadd50f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c91bcc0);
    FUN_7ffe9996d590(&DAT_7ffe9c93f070);
    FUN_7ffe9996d590(&DAT_7ffe9c9488e8);
    FUN_7ffe9996d590(&DAT_7ffe9c95a5b8);
    DAT_7ffe9cadd50f = '\x01';
  }
  aplStack_38[0] = (longlong *)0x0;
  if (*(longlong *)(self + 0x20) != 0) {
    iVar8 = (int)((float)(*(int *)(*(longlong *)(self + 0x20) + 0x40) * *(int *)(self + 0x10)) *
                 _DAT_7ffe9c049b34);
    if (DAT_7ffe9cadd51a == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c929d78);
      DAT_7ffe9cadd51a = '\x01';
    }
    afStackX_8[0] = 0.0;
    puStackX_20 = (undefined *)0x0;
    aiStackX_18[0] = 0;
    if (*(longlong *)(self + 0x40) == 0) {
LAB_7ffe9a31dc17:
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      iVar8 = (*pcVar2)();
      return iVar8;
    }
    cVar3 = FUN_7ffe9abb86e0(*(longlong *)(self + 0x40),0x28,&puStackX_20,_DAT_7ffe9c929d78);
    if (cVar3 != '\0') {
      if (puStackX_20 == (undefined *)0x0) goto LAB_7ffe9a31dc17;
      bVar4 = MobPropertyStatusCollection_TryGetValue
                        (puStackX_20,(undefined *)0x2,(undefined *)aiStackX_18,
                         (undefined *)afStackX_8,(undefined *)0x0);
      if (bVar4 != 0) {
        iVar8 = (int)((afStackX_8[0] + _DAT_7ffe9c049b18) * (float)iVar8 + (float)aiStackX_18[0]);
      }
    }
    if (*(longlong *)(self + 0x18) != 0) {
      uVar6 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x18),_DAT_7ffe9c8ff610);
      if (*(int *)(_DAT_7ffe9c95a5b8 + 0xe0) == 0) {
        func_0x7ffe9996d830(_DAT_7ffe9c95a5b8);
      }
      lVar7 = *(longlong *)(*(longlong *)(_DAT_7ffe9c95a5b8 + 0xb8) + 0x18);
      if (lVar7 == 0) {
        if (*(int *)(_DAT_7ffe9c95a5b8 + 0xe0) == 0) {
          func_0x7ffe9996d830(_DAT_7ffe9c95a5b8);
        }
        uVar1 = **(undefined8 **)(_DAT_7ffe9c95a5b8 + 0xb8);
        lVar7 = func_0x7ffe99940040(_DAT_7ffe9c93f070);
        FUN_7ffe9af15670(lVar7,uVar1,_DAT_7ffe9c9488e8,0);
        *(longlong *)(*(longlong *)(_DAT_7ffe9c95a5b8 + 0xb8) + 0x18) = lVar7;
        il2cpp_write_barrier_0();
      }
      iVar5 = FUN_7ffe9ab8ff30(uVar6,lVar7,_DAT_7ffe9c91bcc0);
      iVar8 = iVar8 + iVar5;
      if (*(longlong *)(self + 0x30) != 0) {
        cVar3 = FUN_7ffe9a2ac880(*(longlong *)(self + 0x30),3,aplStack_38);
        if (cVar3 != '\0') {
          if (aplStack_38[0] == (longlong *)0x0) goto LAB_7ffe9a31dc11;
          iVar5 = (**(code **)(*aplStack_38[0] + 0x1a8))
                            (aplStack_38[0],*(undefined8 *)(*aplStack_38[0] + 0x1b0));
          iVar8 = (int)(((float)(iVar5 + 100) / _DAT_7ffe9c049cfc) * (float)iVar8);
        }
        if (*(longlong *)(self + 0x28) != 0) {
          cVar3 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x28),10);
          if (cVar3 != '\0') {
            iVar8 = (int)((float)iVar8 * _DAT_7ffe9c049b4c);
          }
          if (*(longlong *)(self + 0x28) != 0) {
            cVar3 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x28),0x16);
            if (cVar3 != '\0') {
              iVar8 = (int)((float)iVar8 * _DAT_7ffe9c049b4c);
            }
            return iVar8;
          }
        }
      }
    }
  }
LAB_7ffe9a31dc11:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar8 = (*pcVar2)();
  return iVar8;
}

