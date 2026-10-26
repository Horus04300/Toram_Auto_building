
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobAttackBase_CheckAbnormalDamageIncrease
               (undefined *self,undefined *mobAction,undefined *rate,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uVar6;
  ushort uVar7;
  longlong lStackX_10;
  ulonglong uVar8;
  
  if (DAT_7ffe9cadd7dd == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c927e38);
    FUN_7ffe9996d590();
    DAT_7ffe9cadd7dd = '\x01';
  }
  uVar8 = 0;
  lStackX_10 = 0;
  *(undefined4 *)rate = 0x3f800000;
  lVar5 = _DAT_7ffe9c927e38;
  if (mobAction != (undefined *)0x0) {
    lVar4 = *(longlong *)mobAction;
    if (*(ushort *)(lVar4 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar4 + 0xb0) + uVar8 * 0x10) ==
            *(longlong *)(_DAT_7ffe9c927e38 + 0x20)) {
          lVar4 = (longlong)
                  (int)(*(int *)(*(longlong *)(lVar4 + 0xb0) + 8 + uVar8 * 0x10) +
                       (uint)*(ushort *)(_DAT_7ffe9c927e38 + 0x50)) * 0x10 + 0x138 + lVar4;
          goto LAB_7ffe9a3743a3;
        }
        uVar7 = (short)uVar8 + 1;
        uVar8 = (ulonglong)uVar7;
      } while (uVar7 < *(ushort *)(lVar4 + 0x12e));
    }
    lVar4 = FUN_7ffe998ce540(mobAction,*(longlong *)(_DAT_7ffe9c927e38 + 0x20),
                             *(ushort *)(_DAT_7ffe9c927e38 + 0x50));
LAB_7ffe9a3743a3:
    lVar5 = func_0x7ffe9996d210(*(undefined8 *)(lVar4 + 8),lVar5);
    cVar2 = (**(code **)(lVar5 + 8))(mobAction,2,&lStackX_10,lVar5);
    lVar5 = lStackX_10;
    if (cVar2 == '\0') {
      return 0;
    }
    uVar6 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
    if (lVar5 != 0) {
      bVar3 = FUN_7ffe9a378730(lVar5,uVar6,rate,0);
      return bVar3;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

