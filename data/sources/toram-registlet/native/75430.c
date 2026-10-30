
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_LastResistanceBuff_CheckTrigger(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lStackX_18;
  undefined8 uStackX_20;
  longlong alStack_38 [2];
  undefined8 uStack_28;
  longlong *plStack_20;
  
  if (DAT_7ffe9cadd3cd == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c955818);
    FUN_7ffe9996d590(&DAT_7ffe9c95b2f0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    DAT_7ffe9cadd3cd = '\x01';
  }
  uStackX_20 = 0;
  alStack_38[0] = 0;
  lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
  if (lVar4 != 0) {
    cVar2 = FUN_7ffe9a5a4650(lVar4,0);
    if (cVar2 != '\0') {
      lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
      if (lVar4 == 0) goto LAB_7ffe9a2ed4c8;
      cVar2 = FUN_7ffe9a5a4670(lVar4,0);
      if (cVar2 == '\0') {
        lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
        if ((lVar4 == 0) || (lVar4 = FUN_7ffe9a5a4710(lVar4,0), lVar4 == 0)) goto LAB_7ffe9a2ed4c8;
        lStackX_18 = FUN_7ffe99742ec0(0,_DAT_7ffe9c955818,lVar4);
        uStack_28 = 0;
        plStack_20 = &lStackX_18;
LAB_7ffe9a2ed330:
        do {
          do {
            if (lStackX_18 == 0) goto LAB_7ffe9a2ed4f2;
            cVar2 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
            if (cVar2 == '\0') {
              if (lStackX_18 != 0) {
                FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
              }
              return 1;
            }
            if (lStackX_18 == 0) goto LAB_7ffe9a2ed4ed;
            lVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c95b2f0);
            if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a2ed4e8;
            uStackX_20 = *(undefined8 *)(*(longlong *)(self + 0x18) + 0x50);
            if (lVar4 == 0) goto LAB_7ffe9a2ed4e3;
            cVar2 = func_0x7ffe9bb9e750(&uStackX_20,*(undefined1 *)(lVar4 + 0x1c),
                                        *(undefined4 *)(lVar4 + 0x18),0);
          } while (cVar2 != '\0');
          lVar5 = *(longlong *)(lVar4 + 0x20);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar2 = FUN_7ffe9bda1fa0(lVar5,0,0);
          if (cVar2 != '\0') {
            if (*(char *)(lVar4 + 0x1c) == '\0') goto LAB_7ffe9a2ed330;
            if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a2ed4de;
            lVar5 = *(longlong *)(*(longlong *)(self + 0x18) + 0x70);
            if (lVar5 == 0) goto LAB_7ffe9a2ed4d9;
            cVar2 = FUN_7ffe99a231d0(lVar5,*(char *)(lVar4 + 0x1c),*(undefined4 *)(lVar4 + 0x18),
                                     alStack_38,0);
            if (cVar2 == '\0') goto LAB_7ffe9a2ed330;
            if (alStack_38[0] == 0) goto LAB_7ffe9a2ed4d4;
            lVar5 = FUN_7ffe9a4ca6d0(alStack_38[0],0);
          }
          if (lVar5 == 0) goto LAB_7ffe9a2ed4ce;
          cVar2 = FUN_7ffe99b1ccd0(lVar5,0);
        } while (cVar2 != '\0');
        if (lStackX_18 != 0) {
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
        }
      }
    }
    return 0;
  }
LAB_7ffe9a2ed4c8:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2ed4ce:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2ed4d4:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2ed4d9:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2ed4de:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2ed4e3:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2ed4e8:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2ed4ed:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2ed4f2:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

