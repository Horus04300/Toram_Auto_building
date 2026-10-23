
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus___c__get_CutAttack_b__13_0
              (undefined *self,undefined *p,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  int iVar9;
  
  if (p == (undefined *)0x0) {
LAB_7fff5fe3af90:
    FUN_7fff5f47d660(self);
    pcVar1 = (code *)swi(3);
    iVar9 = (*pcVar1)();
    return iVar9;
  }
  if (*(longlong *)(p + 0x20) != 0) {
    bVar3 = MobPartsStatus_get_IsDead(p,(undefined *)0x0);
    if (bVar3 == 0) {
      lVar6 = *(longlong *)(p + 0x20);
      self = (undefined *)0x0;
      if (lVar6 != 0) {
        if (DAT_7fff625e4ee4 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff62422cf0,0);
          FUN_7fff5f47d450(&DAT_7fff62446cc0);
          FUN_7fff5f47d450(&DAT_7fff6246eab8);
          FUN_7fff5f47d450(&DAT_7fff623f8980);
          DAT_7fff625e4ee4 = '\x01';
        }
        uVar7 = *(undefined8 *)(lVar6 + 0x10);
        if (*(int *)(_DAT_7fff623f8980 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        lVar6 = *(longlong *)(*(longlong *)(_DAT_7fff623f8980 + 0xb8) + 8);
        if (lVar6 == 0) {
          if (*(int *)(_DAT_7fff623f8980 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          uVar8 = **(undefined8 **)(_DAT_7fff623f8980 + 0xb8);
          lVar6 = func_0x7fff5f44ff00(_DAT_7fff62446cc0);
          FUN_7fff60a1fa30(lVar6,uVar8,_DAT_7fff6246eab8,0);
          *(longlong *)(*(longlong *)(_DAT_7fff623f8980 + 0xb8) + 8) = lVar6;
          thunk_FUN_7fff5f491fd0();
        }
        lVar2 = _DAT_7fff62422cf0;
        if (*(longlong *)(_DAT_7fff62422cf0 + 0x38) == 0) {
          FUN_7fff5f3dec80(_DAT_7fff62422cf0);
        }
        lVar6 = FUN_7fff606965b0(uVar7,lVar6,*(undefined8 *)(*(longlong *)(lVar2 + 0x38) + 0x10));
        if (DAT_7fff625ebcf6 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff624329a0,0);
          FUN_7fff5f47d450(&DAT_7fff624413c0);
          FUN_7fff5f47d450(&DAT_7fff6245c238);
          FUN_7fff5f47d450(&DAT_7fff62461b78);
          FUN_7fff5f47d450(&DAT_7fff62442498);
          DAT_7fff625ebcf6 = '\x01';
        }
        if (lVar6 == 0) {
          uVar7 = func_0x7fff5f47d470(0x7fff624551d8);
          uVar7 = FUN_7fff6116bfb0(uVar7,0);
          uVar8 = func_0x7fff5f47d470(&DAT_7fff624329a0);
          FUN_7fff5f47d620(uVar7,uVar8);
LAB_7fff6116bdac:
          uVar7 = _DAT_7fff624329a0;
          uVar8 = func_0x7fff5f47d240();
          FUN_7fff5f47d620(uVar8,uVar7);
LAB_7fff6116bdc3:
          FUN_7fff5f47d660();
        }
        else {
          iVar9 = 0;
          lVar6 = FUN_7fff5f252ec0(0,_DAT_7fff6245c238,lVar6);
          while (lVar6 != 0) {
            cVar4 = FUN_7fff5f252ec0(0,_DAT_7fff62442498);
            if (cVar4 == '\0') {
              if (lVar6 != 0) {
                FUN_7fff5f253010(0,_DAT_7fff624413c0);
              }
              return iVar9;
            }
            if (lVar6 == 0) goto LAB_7fff6116bdc3;
            iVar5 = FUN_7fff5f252ec0(0,_DAT_7fff62461b78);
            if (0xffffffff < (ulonglong)((longlong)iVar9 + (longlong)iVar5 + 0x80000000))
            goto LAB_7fff6116bdac;
            iVar9 = iVar9 + iVar5;
          }
        }
        FUN_7fff5f47d660();
        FUN_7fff5f40a410();
        pcVar1 = (code *)swi(3);
        iVar9 = (*pcVar1)();
        return iVar9;
      }
      goto LAB_7fff5fe3af90;
    }
  }
  return 0;
}

