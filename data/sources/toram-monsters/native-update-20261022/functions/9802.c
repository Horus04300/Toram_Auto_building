
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
  longlong lVar6;
  undefined8 uVar7;
  longlong alStack_38 [2];
  undefined8 uStack_28;
  longlong *plStack_20;
  
  if (DAT_7ffe9cadd79c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9289a8);
    FUN_7ffe9996d590(&DAT_7ffe9c93f1f8);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c955288);
    FUN_7ffe9996d590(&DAT_7ffe9c95ad60);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(0x7ffe9c93d680);
    FUN_7ffe9996d590(&DAT_7ffe9c9683c8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f16e8);
    DAT_7ffe9cadd79c = '\x01';
  }
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c8f16e8);
  func_0x7ffe999c3920(lVar6,0);
  if (lVar6 == 0) {
    FUN_7ffe9996d7a0();
LAB_7ffe9a37c2da:
    FUN_7ffe9996d790();
LAB_7ffe9a37c2e0:
    FUN_7ffe9996d790();
LAB_7ffe9a37c2e5:
    FUN_7ffe9996d7a0();
LAB_7ffe9a37c2ea:
    FUN_7ffe9996d7a0();
LAB_7ffe9a37c2ef:
    FUN_7ffe9996d7a0();
LAB_7ffe9a37c2f4:
    FUN_7ffe9996d7a0();
LAB_7ffe9a37c2f9:
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
    pcVar2 = (code *)swi(3);
    bVar5 = (*pcVar2)();
    return bVar5;
  }
  *(int *)(lVar6 + 0x10) = (int)type;
  *(undefined4 *)constant = 0;
  *(undefined4 *)rate = 0;
  lVar1 = *(longlong *)(self + 0x10);
  if ((lVar1 != 0) && (0 < *(int *)(lVar1 + 0x18))) {
    uVar7 = func_0x7ffe99940040(_DAT_7ffe9c93f1f8);
    FUN_7ffe9af13420(uVar7,lVar6,_DAT_7ffe9c9683c8,0);
    lVar6 = FUN_7ffe9ab93080(lVar1,uVar7,_DAT_7ffe9c9289a8);
    if (lVar6 != 0) {
      alStack_38[0] = FUN_7ffe99742ec0(0,_DAT_7ffe9c955288,lVar6);
      fVar3 = _DAT_7ffe9c049cfc;
      uStack_28 = 0;
      plStack_20 = alStack_38;
      while (alStack_38[0] != 0) {
        cVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
        if (cVar4 == '\0') {
          if (alStack_38[0] != 0) {
            FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
          }
          return 1;
        }
        if (alStack_38[0] == 0) goto LAB_7ffe9a37c2f4;
        lVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c95ad60);
        if (lVar6 == 0) goto LAB_7ffe9a37c2ef;
        lVar1 = *(longlong *)(lVar6 + 0x18);
        if (lVar1 == 0) goto LAB_7ffe9a37c2ea;
        if (*(uint *)(lVar1 + 0x18) < 2) goto LAB_7ffe9a37c2da;
        *(int *)constant = *(int *)constant + *(int *)(lVar1 + 0x24);
        lVar6 = *(longlong *)(lVar6 + 0x18);
        if (lVar6 == 0) goto LAB_7ffe9a37c2e5;
        if (*(uint *)(lVar6 + 0x18) < 3) goto LAB_7ffe9a37c2e0;
        *(float *)rate = (float)*(int *)(lVar6 + 0x28) / fVar3 + *(float *)rate;
      }
      goto LAB_7ffe9a37c2f9;
    }
  }
  return 0;
}

