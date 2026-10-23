
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobPropertyStatusCollection_TryGetValue
               (undefined *self,undefined *type,undefined *constant,undefined *rate,
               undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  float fVar3;
  char cVar4;
  byte bVar5;
  undefined *self_00;
  undefined8 uVar6;
  longlong lVar7;
  longlong alStack_38 [2];
  undefined8 uStack_28;
  longlong *plStack_20;
  
  if (DAT_7fff625e4ef4 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242f860);
    FUN_7fff5f47d450(&DAT_7fff62446bf8);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff6245cc90);
    FUN_7fff5f47d450(&DAT_7fff62462768);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    FUN_7fff5f47d450(0x7fff624445d0);
    FUN_7fff5f47d450(&DAT_7fff6246ed18);
    FUN_7fff5f47d450(&DAT_7fff623f8b20);
    DAT_7fff625e4ef4 = '\x01';
  }
  self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623f8b20);
  GuildRaidRoomData_LoadAsset(self_00,(undefined *)0x0);
  if (self_00 == (undefined *)0x0) {
    FUN_7fff5f47d660();
LAB_7fff5fe86e8a:
    FUN_7fff5f47d650();
LAB_7fff5fe86e90:
    FUN_7fff5f47d650();
LAB_7fff5fe86e95:
    FUN_7fff5f47d660();
LAB_7fff5fe86e9a:
    FUN_7fff5f47d660();
LAB_7fff5fe86e9f:
    FUN_7fff5f47d660();
LAB_7fff5fe86ea4:
    FUN_7fff5f47d660();
LAB_7fff5fe86ea9:
    FUN_7fff5f47d660();
    FUN_7fff5f40a410();
    pcVar2 = (code *)swi(3);
    bVar5 = (*pcVar2)();
    return bVar5;
  }
  *(int *)(self_00 + 0x10) = (int)type;
  *(undefined4 *)constant = 0;
  *(undefined4 *)rate = 0;
  lVar7 = *(longlong *)(self + 0x10);
  if ((lVar7 != 0) && (0 < *(int *)(lVar7 + 0x18))) {
    uVar6 = func_0x7fff5f44ff00(_DAT_7fff62446bf8);
    FUN_7fff60a1d7e0(uVar6,self_00,_DAT_7fff6246ed18,0);
    lVar7 = FUN_7fff6069d430(lVar7,uVar6,_DAT_7fff6242f860);
    if (lVar7 != 0) {
      alStack_38[0] = FUN_7fff5f252ec0(0,_DAT_7fff6245cc90,lVar7);
      fVar3 = _DAT_7fff61b52cfc;
      uStack_28 = 0;
      plStack_20 = alStack_38;
      while (alStack_38[0] != 0) {
        cVar4 = FUN_7fff5f252ec0(0,_DAT_7fff62442498);
        if (cVar4 == '\0') {
          if (alStack_38[0] != 0) {
            FUN_7fff5f253010(0,_DAT_7fff624413c0);
          }
          return 1;
        }
        if (alStack_38[0] == 0) goto LAB_7fff5fe86ea4;
        lVar7 = FUN_7fff5f252ec0(0,_DAT_7fff62462768);
        if (lVar7 == 0) goto LAB_7fff5fe86e9f;
        lVar1 = *(longlong *)(lVar7 + 0x18);
        if (lVar1 == 0) goto LAB_7fff5fe86e9a;
        if (*(uint *)(lVar1 + 0x18) < 2) goto LAB_7fff5fe86e8a;
        *(int *)constant = *(int *)constant + *(int *)(lVar1 + 0x24);
        lVar7 = *(longlong *)(lVar7 + 0x18);
        if (lVar7 == 0) goto LAB_7fff5fe86e95;
        if (*(uint *)(lVar7 + 0x18) < 3) goto LAB_7fff5fe86e90;
        *(float *)rate = (float)*(int *)(lVar7 + 0x28) / fVar3 + *(float *)rate;
      }
      goto LAB_7fff5fe86ea9;
    }
  }
  return 0;
}

