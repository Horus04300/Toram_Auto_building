
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerAttackBase_checkCriticalPercent
               (undefined *self,int criticalParcent,undefined *mobAction,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  ushort uVar4;
  longlong lVar5;
  longlong lVar6;
  int aiStackX_10 [2];
  undefined *puStackX_18;
  
  aiStackX_10[0] = criticalParcent;
  if (DAT_7ffe9caddede == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c928090);
    DAT_7ffe9caddede = '\x01';
  }
  lVar6 = _DAT_7ffe9c928090;
  uVar4 = 0;
  puStackX_18 = (undefined *)0x0;
  if (mobAction != (undefined *)0x0) {
    lVar5 = *(longlong *)mobAction;
    if (*(ushort *)(lVar5 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar5 + 0xb0) + (ulonglong)uVar4 * 0x10) ==
            *(longlong *)(_DAT_7ffe9c928090 + 0x20)) {
          lVar5 = (longlong)
                  (int)(*(int *)(*(longlong *)(lVar5 + 0xb0) + 8 + (ulonglong)uVar4 * 0x10) +
                       (uint)*(ushort *)(_DAT_7ffe9c928090 + 0x50)) * 0x10 + 0x138 + lVar5;
          goto LAB_7ffe9a4b3483;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(ushort *)(lVar5 + 0x12e));
    }
    lVar5 = FUN_7ffe998ce540(mobAction,*(longlong *)(_DAT_7ffe9c928090 + 0x20),
                             *(ushort *)(_DAT_7ffe9c928090 + 0x50));
LAB_7ffe9a4b3483:
    lVar6 = func_0x7ffe9996d210(*(undefined8 *)(lVar5 + 8),lVar6);
    cVar2 = (**(code **)(lVar6 + 8))(mobAction,6,&puStackX_18);
    if (cVar2 != '\0') {
      if (puStackX_18 == (undefined *)0x0) goto LAB_7ffe9a4b350a;
      MobPropertyCriticalResist_TryGetValue
                (puStackX_18,mobAction,(undefined *)aiStackX_10,(undefined *)0x0);
    }
    bVar3 = FUN_7ffe9a8fea70(self,100,aiStackX_10[0]);
    return bVar3;
  }
LAB_7ffe9a4b350a:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

