
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusData__cctor(undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong lVar4;
  code *pcVar5;
  longlong lVar6;
  longlong lVar7;
  uint uVar8;
  
  if (DAT_7fff625e584d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244ff38);
    FUN_7fff5f47d450(&DAT_7fff6245c758);
    FUN_7fff5f47d450(&DAT_7fff6245c688);
    FUN_7fff5f47d450(&DAT_7fff6242a958);
    FUN_7fff5f47d450(&DAT_7fff6240fec0);
    FUN_7fff5f47d450(&DAT_7fff6240fd20);
    FUN_7fff5f47d450(&DAT_7fff6246bf90);
    DAT_7fff625e584d = '\x01';
  }
  lVar6 = func_0x7fff5f44ff00(_DAT_7fff6246bf90);
  FUN_7fff60a943d0(lVar6,_DAT_7fff6240fd20);
  lVar7 = _DAT_7fff6240fec0;
  if (lVar6 != 0) {
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar4 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar4 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar4 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar4 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar4 + 0x20 + (longlong)(int)uVar8 * 4) = 1;
    }
    else {
      FUN_7fff60ad1100(lVar6,1,*(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 2;
    }
    else {
      FUN_7fff60ad1100(lVar6,2,*(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 3;
    }
    else {
      FUN_7fff60ad1100(lVar6,3,*(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 4;
    }
    else {
      FUN_7fff60ad1100(lVar6,4,*(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 5;
    }
    else {
      FUN_7fff60ad1100(lVar6,5,*(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 6;
    }
    else {
      FUN_7fff60ad1100(lVar6,6,*(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 7;
    }
    else {
      FUN_7fff60ad1100(lVar6,7,*(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 8;
    }
    else {
      FUN_7fff60ad1100(lVar6,8,*(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 9;
    }
    else {
      FUN_7fff60ad1100(lVar6,9,*(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 10;
    }
    else {
      FUN_7fff60ad1100(lVar6,10,*(undefined8 *)
                                 (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0xb;
    }
    else {
      FUN_7fff60ad1100(lVar6,0xb,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0xc;
    }
    else {
      FUN_7fff60ad1100(lVar6,0xc,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0xd;
    }
    else {
      FUN_7fff60ad1100(lVar6,0xd,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0xe;
    }
    else {
      FUN_7fff60ad1100(lVar6,0xe,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0xf;
    }
    else {
      FUN_7fff60ad1100(lVar6,0xf,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x10;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x10,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x11;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x11,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x12;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x12,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x13;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x13,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x14;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x14,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x15;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x15,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x16;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x16,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x17;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x17,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x18;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x18,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x19;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x19,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x1a;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x1a,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x1b;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x1b,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x1c;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x1c,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x1d;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x1d,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x1e;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x1e,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x1f;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x1f,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x20;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x20,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x21;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x21,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x22;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x22,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7fff5fff258f;
    if (uVar8 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar8 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar8) goto LAB_7fff5fff2595;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x23;
    }
    else {
      FUN_7fff60ad1100(lVar6,0x23,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
    }
    lVar4 = _DAT_7fff6240fec0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar8 = *(uint *)(lVar6 + 0x18);
    if (lVar7 != 0) {
      if (uVar8 < *(uint *)(lVar7 + 0x18)) {
        *(uint *)(lVar6 + 0x18) = uVar8 + 1;
        if (*(uint *)(lVar7 + 0x18) <= uVar8) {
LAB_7fff5fff2595:
          FUN_7fff5f47d650();
          pcVar5 = (code *)swi(3);
          (*pcVar5)();
          return;
        }
        *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar8 * 4) = 0x24;
      }
      else {
        FUN_7fff60ad1100(lVar6,0x24,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
      }
      FUN_7fff5f254640(lVar6,0x25,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x26,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x27,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x28,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x29,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x2a,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x2b,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x2c,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x2d,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x2e,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x2f,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x30,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x31,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x32,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x33,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x34,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x35,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x36,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x37,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x38,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x39,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x3a,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x3b,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x3c,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x3d,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x3e,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x3f,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x40,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x41,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x42,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x43,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x44,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x45,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x46,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x47,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x48,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x49,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x4a,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x4b,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x4c,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x4d,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x4e,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x4f,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x50,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x51,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x52,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x53,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x54,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x55,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x56,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x68,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x69,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x6a,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x6b,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x6e,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x6f,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x70,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x71,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x79,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x7a,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x7b,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x7c,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x7d,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x7e,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x7f,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x80,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x81,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x82,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0x83,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xa6,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xa7,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xa8,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xa9,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xaa,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xab,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xac,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xad,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xae,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xaf,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xb0,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xb1,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xb4,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xb5,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xb6,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xb7,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xb8,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xb9,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xba,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xbb,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xbc,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xbd,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xbe,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xbf,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xc0,_DAT_7fff6240fec0);
      FUN_7fff5f254640(lVar6,0xc1,_DAT_7fff6240fec0);
      **(longlong **)(_DAT_7fff6244ff38 + 0xb8) = lVar6;
      thunk_FUN_7fff5f491fd0();
      lVar7 = func_0x7fff5f44ff00(_DAT_7fff6246bf90);
      FUN_7fff60a943d0(lVar7,_DAT_7fff6240fd20);
      if (lVar7 != 0) {
        FUN_7fff5f254640(lVar7,0xd1,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xd2,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xd3,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xd4,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xd5,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xd6,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xd7,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xd8,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xd9,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xda,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xdb,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xdc,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xdd,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xde,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xdf,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xff,_DAT_7fff6240fec0);
        FUN_7fff5f254640(lVar7,0xe0,_DAT_7fff6240fec0);
        *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 8) = lVar7;
        thunk_FUN_7fff5f491fd0();
        lVar7 = func_0x7fff5f44ff00(_DAT_7fff6246bf90);
        FUN_7fff60a943d0(lVar7,_DAT_7fff6240fd20);
        if (lVar7 != 0) {
          FUN_7fff5f254640(lVar7,0xf2,_DAT_7fff6240fec0);
          *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x10) = lVar7;
          thunk_FUN_7fff5f491fd0();
          lVar7 = func_0x7fff5f44ff00(_DAT_7fff6246bf90);
          FUN_7fff60a943d0(lVar7,_DAT_7fff6240fd20);
          if (lVar7 != 0) {
            FUN_7fff5f254640(lVar7,0x61,_DAT_7fff6240fec0);
            FUN_7fff5f254640(lVar7,0x62,_DAT_7fff6240fec0);
            FUN_7fff5f254640(lVar7,99,_DAT_7fff6240fec0);
            FUN_7fff5f254640(lVar7,100,_DAT_7fff6240fec0);
            FUN_7fff5f254640(lVar7,0x65,_DAT_7fff6240fec0);
            FUN_7fff5f254640(lVar7,0x66,_DAT_7fff6240fec0);
            FUN_7fff5f254640(lVar7,0x67,_DAT_7fff6240fec0);
            FUN_7fff5f254640(lVar7,0x73,_DAT_7fff6240fec0);
            FUN_7fff5f254640(lVar7,0x74,_DAT_7fff6240fec0);
            *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x18) = lVar7;
            thunk_FUN_7fff5f491fd0();
            lVar7 = func_0x7fff5f44ff00(_DAT_7fff6246bf90);
            FUN_7fff60a943d0(lVar7,_DAT_7fff6240fd20);
            if (lVar7 != 0) {
              FUN_7fff5f254640(lVar7,0x87,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x88,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x89,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x8a,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x8b,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x8c,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x8d,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x8e,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x8f,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x90,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x91,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x92,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x93,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x94,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x95,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x96,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x97,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x98,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x99,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x9a,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x9b,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0x9f,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0xa0,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0xa1,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0xa2,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0xa3,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0xa4,_DAT_7fff6240fec0);
              FUN_7fff5f254640(lVar7,0xa5,_DAT_7fff6240fec0);
              *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x20) = lVar7;
              thunk_FUN_7fff5f491fd0();
              lVar7 = func_0x7fff5f44ff00(_DAT_7fff6246bf90);
              FUN_7fff60a943d0(lVar7,_DAT_7fff6240fd20);
              if (lVar7 != 0) {
                FUN_7fff5f254640(lVar7,0xf8,_DAT_7fff6240fec0);
                *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x28) = lVar7;
                thunk_FUN_7fff5f491fd0();
                lVar7 = func_0x7fff5f44ff00(_DAT_7fff6242a958);
                FUN_7fff608789f0(lVar7,_DAT_7fff6245c688);
                if (lVar7 != 0) {
                  FUN_7fff6088cb20(lVar7,0,**(undefined8 **)(_DAT_7fff6244ff38 + 0xb8),
                                   _DAT_7fff6245c758);
                  FUN_7fff6088cb20(lVar7,1,*(undefined8 *)
                                            (*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 8),
                                   _DAT_7fff6245c758);
                  FUN_7fff6088cb20(lVar7,2,*(undefined8 *)
                                            (*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x10),
                                   _DAT_7fff6245c758);
                  FUN_7fff6088cb20(lVar7,3,*(undefined8 *)
                                            (*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x18),
                                   _DAT_7fff6245c758);
                  FUN_7fff6088cb20(lVar7,4,*(undefined8 *)
                                            (*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x20),
                                   _DAT_7fff6245c758);
                  FUN_7fff6088cb20(lVar7,5,*(undefined8 *)
                                            (*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x28),
                                   _DAT_7fff6245c758);
                  *(longlong *)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x30) = lVar7;
                  if (_DAT_7fff625f58f8 != 0) {
                    uVar8 = (uint)(*(longlong *)(_DAT_7fff6244ff38 + 0xb8) + 0x30U >> 0xc);
                    puVar1 = (ulonglong *)
                             ((ulonglong)((uVar8 & 0x1fffff) >> 6) * 8 + 0x7fff6263d720);
                    do {
                      uVar3 = *puVar1;
                      LOCK();
                      uVar2 = *puVar1;
                      if (uVar3 == uVar2) {
                        *puVar1 = uVar3 | 1L << (uVar8 & 0x3f);
                      }
                      UNLOCK();
                    } while (uVar3 != uVar2);
                  }
                  return;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7fff5fff258f:
  FUN_7fff5f47d660();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

