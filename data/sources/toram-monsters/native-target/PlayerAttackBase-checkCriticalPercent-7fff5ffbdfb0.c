
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
  longlong lStackX_18;
  
  aiStackX_10[0] = criticalParcent;
  if (DAT_7fff625e5636 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242ef48);
    DAT_7fff625e5636 = '\x01';
  }
  lVar6 = _DAT_7fff6242ef48;
  uVar4 = 0;
  lStackX_18 = 0;
  if (mobAction != (undefined *)0x0) {
    lVar5 = *(longlong *)mobAction;
    if (*(ushort *)(lVar5 + 0x12e) != 0) {
      do {
        if (*(longlong *)(*(longlong *)(lVar5 + 0xb0) + (ulonglong)uVar4 * 0x10) ==
            *(longlong *)(_DAT_7fff6242ef48 + 0x20)) {
          lVar5 = (longlong)
                  (int)(*(int *)(*(longlong *)(lVar5 + 0xb0) + 8 + (ulonglong)uVar4 * 0x10) +
                       (uint)*(ushort *)(_DAT_7fff6242ef48 + 0x50)) * 0x10 + 0x138 + lVar5;
          goto LAB_7fff5ffbe043;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(ushort *)(lVar5 + 0x12e));
    }
    lVar5 = FUN_7fff5f3de400(mobAction,*(longlong *)(_DAT_7fff6242ef48 + 0x20),
                             *(ushort *)(_DAT_7fff6242ef48 + 0x50));
LAB_7fff5ffbe043:
    lVar6 = func_0x7fff5f47d0d0(*(undefined8 *)(lVar5 + 8),lVar6);
    cVar2 = (**(code **)(lVar6 + 8))(mobAction,6,&lStackX_18,lVar6);
    if (cVar2 != '\0') {
      if (lStackX_18 == 0) goto LAB_7fff5ffbe0ca;
      FUN_7fff5fe83b20(lStackX_18,mobAction,aiStackX_10,0);
    }
    bVar3 = FUN_7fff60408eb0(self,100,aiStackX_10[0]);
    return bVar3;
  }
LAB_7fff5ffbe0ca:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

