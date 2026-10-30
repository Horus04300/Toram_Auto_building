
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_SaviourBuff_CheckTrigger(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lStackX_20;
  
  if (DAT_7ffe9cadd3d4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c955818);
    FUN_7ffe9996d590(&DAT_7ffe9c95b2f0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    DAT_7ffe9cadd3d4 = '\x01';
  }
  lStackX_20 = 0;
  lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
  if (lVar4 == 0) {
LAB_7ffe9a2f06d7:
    FUN_7ffe9996d7a0();
LAB_7ffe9a2f06dd:
    FUN_7ffe9996d7a0();
LAB_7ffe9a2f06e3:
    FUN_7ffe9996d7a0();
LAB_7ffe9a2f06e8:
    FUN_7ffe9996d7a0();
LAB_7ffe9a2f06ed:
    FUN_7ffe9996d7a0();
LAB_7ffe9a2f06f2:
    FUN_7ffe9996d7a0();
LAB_7ffe9a2f06f7:
    FUN_7ffe9996d7a0();
LAB_7ffe9a2f06fc:
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
    pcVar1 = (code *)swi(3);
    bVar3 = (*pcVar1)();
    return bVar3;
  }
  cVar2 = FUN_7ffe9a5a4650(lVar4,0);
  if (cVar2 != '\0') {
    lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar4 == 0) goto LAB_7ffe9a2f06d7;
    cVar2 = FUN_7ffe9a5a4670(lVar4,0);
    if (cVar2 == '\0') {
      lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
      if ((lVar4 == 0) || (lVar4 = FUN_7ffe9a5a46f0(lVar4,0), lVar4 == 0)) goto LAB_7ffe9a2f06d7;
      lVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c955818,lVar4);
LAB_7ffe9a2f0561:
      do {
        do {
          if (lVar4 == 0) goto LAB_7ffe9a2f06fc;
          cVar2 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
          if (cVar2 == '\0') {
            if (lVar4 != 0) {
              FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
            }
            return 1;
          }
          if (lVar4 == 0) goto LAB_7ffe9a2f06f7;
          lVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c95b2f0);
          if (lVar5 == 0) goto LAB_7ffe9a2f06f2;
        } while (*(char *)(lVar5 + 0x4c) != '\0');
        lVar6 = *(longlong *)(lVar5 + 0x20);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar2 = FUN_7ffe9bda1fa0(lVar6,0,0);
        if (cVar2 != '\0') {
          if (*(char *)(lVar5 + 0x1c) == '\0') goto LAB_7ffe9a2f0561;
          lVar6 = FUN_7ffe9a47bac0(0);
          if (lVar6 == 0) goto LAB_7ffe9a2f06ed;
          if (*(longlong *)(lVar6 + 0x70) == 0) goto LAB_7ffe9a2f06e8;
          cVar2 = FUN_7ffe99a231d0(*(longlong *)(lVar6 + 0x70),*(undefined1 *)(lVar5 + 0x1c),
                                   *(undefined4 *)(lVar5 + 0x18),&lStackX_20,0);
          if (cVar2 == '\0') goto LAB_7ffe9a2f0561;
          if (lStackX_20 == 0) goto LAB_7ffe9a2f06e3;
          lVar6 = FUN_7ffe9a4ca6d0(lStackX_20,0);
        }
        if (lVar6 == 0) goto LAB_7ffe9a2f06dd;
        cVar2 = FUN_7ffe99b1ccd0(lVar6,0);
      } while (cVar2 != '\0');
      if (lVar4 != 0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
    }
  }
  return 0;
}

