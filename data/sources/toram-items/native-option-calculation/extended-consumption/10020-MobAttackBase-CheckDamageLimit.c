
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobAttackBase_CheckDamageLimit
               (undefined *self,undefined *mobAction,undefined *min,undefined *max,
               undefined *methodInfo)

{
  code *pcVar1;
  float fVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  longlong lVar7;
  longlong lVar8;
  ushort uVar9;
  ushort uVar10;
  ulonglong uVar11;
  bool bVar12;
  longlong lStackX_10;
  longlong lStackX_18;
  longlong lStackX_20;
  
  if (DAT_7ffe9cadd7dc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c928158);
    FUN_7ffe9996d590(&DAT_7ffe9c9283b0);
    FUN_7ffe9996d590(&DAT_7ffe9c928478);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    DAT_7ffe9cadd7dc = '\x01';
  }
  uVar11 = 0;
  *(undefined4 *)min = 0xffffffff;
  lStackX_10 = 0;
  lStackX_18 = 0;
  lStackX_20 = 0;
  *(undefined4 *)max = 0xffffffff;
  lVar8 = _DAT_7ffe9c928158;
  if (mobAction == (undefined *)0x0) goto LAB_7ffe9a374bda;
  uVar10 = 0;
  lVar7 = *(longlong *)mobAction;
  if (*(ushort *)(lVar7 + 0x12e) != 0) {
    uVar9 = uVar10;
    do {
      if (*(longlong *)(*(longlong *)(lVar7 + 0xb0) + (ulonglong)uVar9 * 0x10) ==
          *(longlong *)(_DAT_7ffe9c928158 + 0x20)) {
        lVar7 = (longlong)
                (int)(*(int *)(*(longlong *)(lVar7 + 0xb0) + 8 + (ulonglong)uVar9 * 0x10) +
                     (uint)*(ushort *)(_DAT_7ffe9c928158 + 0x50)) * 0x10 + 0x138 + lVar7;
        goto LAB_7ffe9a374857;
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(ushort *)(lVar7 + 0x12e));
  }
  lVar7 = FUN_7ffe998ce540(mobAction,*(longlong *)(_DAT_7ffe9c928158 + 0x20),
                           *(ushort *)(_DAT_7ffe9c928158 + 0x50));
LAB_7ffe9a374857:
  lVar8 = func_0x7ffe9996d210(*(undefined8 *)(lVar7 + 8),lVar8);
  cVar3 = (**(code **)(lVar8 + 8))(mobAction,5,&lStackX_10,lVar8);
  lVar8 = lStackX_10;
  if (cVar3 != '\0') {
    lVar7 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
    if (lVar7 == 0) goto LAB_7ffe9a374bda;
    iVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar7);
    if (lVar8 == 0) goto LAB_7ffe9a374bda;
    bVar12 = DAT_7ffe9cadd788 == '\0';
    *(undefined4 *)min = 0;
    *(undefined4 *)max = 0;
    if (bVar12) {
      FUN_7ffe9996d590(&DAT_7ffe9c906868);
      DAT_7ffe9cadd788 = '\x01';
    }
    lVar8 = FUN_7ffe9ab85290(*(undefined8 *)(lVar8 + 0x10),_DAT_7ffe9c906868);
    if (lVar8 != 0) {
      lVar7 = *(longlong *)(lVar8 + 0x18);
      if (lVar7 == 0) goto LAB_7ffe9a374bda;
      if (*(int *)(lVar7 + 0x18) == 0) {
LAB_7ffe9a374be0:
        FUN_7ffe9996d790();
        pcVar1 = (code *)swi(3);
        bVar4 = (*pcVar1)();
        return bVar4;
      }
      *(undefined4 *)min = *(undefined4 *)(lVar7 + 0x20);
      lVar7 = *(longlong *)(lVar8 + 0x18);
      if (lVar7 == 0) goto LAB_7ffe9a374bda;
      if (*(uint *)(lVar7 + 0x18) < 2) goto LAB_7ffe9a374be0;
      *(undefined4 *)max = *(undefined4 *)(lVar7 + 0x24);
      fVar2 = _DAT_7ffe9c049cfc;
      lVar7 = *(longlong *)(lVar8 + 0x18);
      if (lVar7 == 0) goto LAB_7ffe9a374bda;
      if (*(uint *)(lVar7 + 0x18) < 4) goto LAB_7ffe9a374be0;
      if ((*(byte *)(lVar7 + 0x2c) & 0x20) != 0) {
        if (*(int *)(lVar7 + 0x18) == 0) goto LAB_7ffe9a374be0;
        *(int *)min = (int)(((float)*(int *)(lVar7 + 0x20) / _DAT_7ffe9c049cfc) * (float)iVar5);
        lVar8 = *(longlong *)(lVar8 + 0x18);
        if (lVar8 == 0) goto LAB_7ffe9a374bda;
        if (*(uint *)(lVar8 + 0x18) < 2) goto LAB_7ffe9a374be0;
        *(int *)max = (int)(((float)*(int *)(lVar8 + 0x24) / fVar2) * (float)iVar5);
      }
    }
  }
  lVar7 = _DAT_7ffe9c9283b0;
  lVar8 = *(longlong *)mobAction;
  if (*(ushort *)(lVar8 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + (ulonglong)uVar10 * 0x10) ==
          *(longlong *)(_DAT_7ffe9c9283b0 + 0x20)) {
        lVar8 = (longlong)
                (int)(*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + (ulonglong)uVar10 * 0x10) +
                     (uint)*(ushort *)(_DAT_7ffe9c9283b0 + 0x50)) * 0x10 + 0x138 + lVar8;
        goto LAB_7ffe9a374a07;
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 < *(ushort *)(lVar8 + 0x12e));
  }
  lVar8 = FUN_7ffe998ce540(mobAction,*(longlong *)(_DAT_7ffe9c9283b0 + 0x20),
                           *(ushort *)(_DAT_7ffe9c9283b0 + 0x50));
LAB_7ffe9a374a07:
  lVar8 = func_0x7ffe9996d210(*(undefined8 *)(lVar8 + 8),lVar7);
  cVar3 = (**(code **)(lVar8 + 8))(mobAction,0x21,&lStackX_18,lVar8);
  lVar8 = lStackX_18;
  if (cVar3 != '\0') {
    lVar7 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
    if (lVar7 == 0) goto LAB_7ffe9a374bda;
    uVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar7);
    if (lVar8 == 0) goto LAB_7ffe9a374bda;
    FUN_7ffe9a37b2c0(lVar8,uVar6,max,0);
  }
  lVar7 = _DAT_7ffe9c928478;
  lVar8 = *(longlong *)mobAction;
  if (*(ushort *)(lVar8 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + uVar11 * 0x10) ==
          *(longlong *)(_DAT_7ffe9c928478 + 0x20)) {
        lVar8 = (longlong)
                (int)(*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + uVar11 * 0x10) +
                     (uint)*(ushort *)(_DAT_7ffe9c928478 + 0x50)) * 0x10 + 0x138 + lVar8;
        goto LAB_7ffe9a374ad7;
      }
      uVar10 = (short)uVar11 + 1;
      uVar11 = (ulonglong)uVar10;
    } while (uVar10 < *(ushort *)(lVar8 + 0x12e));
  }
  lVar8 = FUN_7ffe998ce540(mobAction,*(longlong *)(_DAT_7ffe9c928478 + 0x20),
                           *(ushort *)(_DAT_7ffe9c928478 + 0x50));
LAB_7ffe9a374ad7:
  lVar8 = func_0x7ffe9996d210(*(undefined8 *)(lVar8 + 8),lVar7);
  cVar3 = (**(code **)(lVar8 + 8))(mobAction,0x22,&lStackX_20,lVar8);
  lVar8 = lStackX_20;
  if (cVar3 != '\0') {
    lVar7 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
    if (lVar7 != 0) {
      uVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar7);
      if (lVar8 != 0) {
        FUN_7ffe9a37b470(lVar8,uVar6,min,0);
        goto LAB_7ffe9a374b4a;
      }
    }
LAB_7ffe9a374bda:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    bVar4 = (*pcVar1)();
    return bVar4;
  }
LAB_7ffe9a374b4a:
  if ((*(int *)min == -1) && (*(int *)max == -1)) {
    bVar4 = 0;
  }
  else {
    bVar4 = 1;
  }
  return bVar4;
}

