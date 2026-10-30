
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_StandingWithArmsCrossedBuff_CheckTrigger(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  longlong lVar5;
  undefined8 uVar6;
  double dVar7;
  undefined1 auVar8 [16];
  float fStackX_8;
  float fStackX_c;
  
  if (DAT_7ffe9cadd3d5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9530b0);
    DAT_7ffe9cadd3d5 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x18);
  if ((plVar1 != (longlong *)0x0) &&
     (lVar5 = (**(code **)(*plVar1 + 0x1e8))(plVar1,*(undefined8 *)(*plVar1 + 0x1f0)), lVar5 != 0))
  {
    cVar3 = FUN_7ffe9a4daa60(lVar5,0xc);
    if (cVar3 == '\0') {
      return 0;
    }
    lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c9530b0);
    if (lVar5 != 0) {
      cVar3 = FUN_7ffe99ab28b0(lVar5,0);
      if (cVar3 != '\0') {
        lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c9530b0);
        if (lVar5 == 0) goto LAB_7ffe9a2f2127;
        uVar6 = FUN_7ffe99ab2b10(lVar5,0);
        if (DAT_7ffe9cad9b4a == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9b4a = '\x01';
        }
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        fStackX_c = (float)((ulonglong)uVar6 >> 0x20);
        fStackX_8 = (float)uVar6;
        dVar7 = (double)(fStackX_c * fStackX_c + fStackX_8 * fStackX_8);
        if (dVar7 < 0.0) {
          dVar7 = (double)FUN_7ffe999979e0();
        }
        else {
          auVar8._8_8_ = 0;
          auVar8._0_8_ = dVar7;
          auVar8 = sqrtpd(ZEXT816(0),auVar8);
          dVar7 = auVar8._0_8_;
        }
        if (_DAT_7ffe9c049d60 <= (float)dVar7) {
          return 0;
        }
      }
      return 1;
    }
  }
LAB_7ffe9a2f2127:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar4 = (*pcVar2)();
  return bVar4;
}

