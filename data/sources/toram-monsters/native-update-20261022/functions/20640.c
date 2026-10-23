
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * GuildRaidRoomData_GetMobGuildRaidBonus(undefined *self,undefined *methodInfo)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  longlong lVar4;
  code *pcVar5;
  char cVar6;
  longlong lVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong lVar10;
  undefined *puVar11;
  uint uVar12;
  uint uVar13;
  char cVar14;
  
  if (DAT_7ffe9cade886 == '\0') {
    FUN_7ffe9996d590(0x7ffe9c954a58);
    FUN_7ffe9996d590(&DAT_7ffe9c9602a8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f82e8);
    FUN_7ffe9996d590(0x7ffe9c8fc1d8);
    FUN_7ffe9996d590(&DAT_7ffe9c91cf68);
    FUN_7ffe9996d590(&DAT_7ffe9c917f28);
    FUN_7ffe9996d590(&DAT_7ffe9c93d430);
    FUN_7ffe9996d590(&DAT_7ffe9c93d5b8);
    FUN_7ffe9996d590(&DAT_7ffe9c93d370);
    FUN_7ffe9996d590(&DAT_7ffe9c96de78);
    FUN_7ffe9996d590(&DAT_7ffe9c8efec8);
    FUN_7ffe9996d590(&DAT_7ffe9c96ec48);
    FUN_7ffe9996d590(0x7ffe9c932cb0);
    FUN_7ffe9996d590(0x7ffe9c933458);
    FUN_7ffe9996d590(0x7ffe9c940d68);
    DAT_7ffe9cade886 = '\x01';
  }
  uVar12 = 0;
  lVar7 = func_0x7ffe99940040(_DAT_7ffe9c96de78);
  FUN_7ffe9af8a010(lVar7,_DAT_7ffe9c93d370);
  lVar4 = *(longlong *)(self + 0x70);
  if (lVar4 == 0) {
LAB_7ffe9a5d5b61:
    if (lVar7 != 0) {
      puVar11 = (undefined *)FUN_7ffe9af89d20(lVar7,_DAT_7ffe9c93d5b8);
      return puVar11;
    }
LAB_7ffe9a5d5b9f:
    FUN_7ffe9996d7a0();
    pcVar5 = (code *)swi(3);
    puVar11 = (undefined *)(*pcVar5)();
    return puVar11;
  }
  cVar14 = 'd';
LAB_7ffe9a5d5435:
  if ((int)uVar12 < *(int *)(lVar4 + 0x18)) {
    if (*(uint *)(lVar4 + 0x18) <= uVar12) goto LAB_7ffe9a5d5ba5;
    lVar10 = *(longlong *)(lVar4 + 0x20 + (longlong)(int)uVar12 * 8);
    if (lVar10 == 0) goto LAB_7ffe9a5d5b9f;
    cVar6 = func_0x7ffe9a7991c0(lVar10,0);
    uVar8 = uRam00007ffe9c954a58;
    if (cVar6 != '\0') goto LAB_7ffe9a5d5b53;
    iVar3 = *(int *)(lVar10 + 0x24);
    if (iVar3 - 1U < 9) {
      if (*(longlong *)(self + 0x68) != 0) {
        cVar6 = FUN_7ffe9ad7c520();
        if (cVar6 == '\0') goto LAB_7ffe9a5d5b53;
        uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8);
        FUN_7ffe9a37b0f0(uVar8,cVar14,0x29,0,100,0,0,0,0);
        if (lVar7 != 0) goto code_r0x7ffe9a5d5503;
      }
      goto LAB_7ffe9a5d5b9f;
    }
    switch(iVar3) {
    case 0xc9:
      lVar9 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,3);
      FUN_7ffe9b436460(lVar9,uRam00007ffe9c932cb0,0);
      if (lVar9 == 0) goto LAB_7ffe9a5d5b9f;
      lVar10 = (ulonglong)*(byte *)(lVar10 + 0x28) - 1;
      if (*(uint *)(lVar9 + 0x18) <= (uint)lVar10) goto LAB_7ffe9a5d5ba5;
      sVar2 = *(short *)(self + 0xb0);
      lVar10 = (longlong)*(int *)(lVar9 + 0x20 + lVar10 * 4);
      uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8,(longlong)(int)sVar2 % lVar10 & 0xffffffff);
      FUN_7ffe9a37b0f0(uVar8,cVar14,6,(longlong)(int)sVar2 / lVar10 & 0xffffffff,0,0,0,0,0);
      if (lVar7 == 0) goto LAB_7ffe9a5d5b9f;
      FUN_7ffe99743100(lVar7);
      uVar12 = uVar12 + 1;
      cVar14 = cVar14 + '\x01';
      goto LAB_7ffe9a5d5435;
    case 0xca:
      sVar2 = *(short *)(self + 0xb0);
      bVar1 = *(byte *)(lVar10 + 0x28);
      uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8);
      FUN_7ffe9a37b0f0(uVar8,cVar14,0x28,1,(int)sVar2 * (uint)bVar1,0,0,0,0);
      if (lVar7 == 0) goto LAB_7ffe9a5d5b9f;
      FUN_7ffe99743100(lVar7);
      uVar12 = uVar12 + 1;
      cVar14 = cVar14 + '\x01';
      goto LAB_7ffe9a5d5435;
    case 0xcb:
      sVar2 = *(short *)(self + 0xb0);
      bVar1 = *(byte *)(lVar10 + 0x28);
      uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8);
      FUN_7ffe9a37b0f0(uVar8,cVar14,0x28,2,(int)sVar2 * (uint)bVar1,0,0,0,0);
      if (lVar7 == 0) goto LAB_7ffe9a5d5b9f;
      FUN_7ffe99743100(lVar7);
      uVar12 = uVar12 + 1;
      cVar14 = cVar14 + '\x01';
      goto LAB_7ffe9a5d5435;
    case 0xcc:
      sVar2 = *(short *)(self + 0xb0);
      bVar1 = *(byte *)(lVar10 + 0x28);
      uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8);
      FUN_7ffe9a37b0f0(uVar8,cVar14,0x28,7,(int)sVar2 * (uint)bVar1,0,0,0,0);
      if (lVar7 == 0) goto LAB_7ffe9a5d5b9f;
      FUN_7ffe99743100(lVar7);
      uVar12 = uVar12 + 1;
      cVar14 = cVar14 + '\x01';
      goto LAB_7ffe9a5d5435;
    case 0xcd:
      lVar9 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,3);
      FUN_7ffe9b436460(lVar9,uRam00007ffe9c940d68,0);
      if (lVar9 == 0) goto LAB_7ffe9a5d5b9f;
      lVar10 = (ulonglong)*(byte *)(lVar10 + 0x28) - 1;
      if (*(uint *)(lVar9 + 0x18) <= (uint)lVar10) goto LAB_7ffe9a5d5ba5;
      sVar2 = *(short *)(self + 0xb0);
      iVar3 = *(int *)(lVar9 + 0x20 + lVar10 * 4);
      uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8,
                                  (longlong)(int)sVar2 % (longlong)iVar3 & 0xffffffff);
      FUN_7ffe9a37b0f0(uVar8,cVar14,0x28,5,(int)sVar2 / iVar3,0,0,0,0);
      if (lVar7 == 0) goto LAB_7ffe9a5d5b9f;
      FUN_7ffe99743100(lVar7);
      uVar12 = uVar12 + 1;
      cVar14 = cVar14 + '\x01';
      goto LAB_7ffe9a5d5435;
    case 0xce:
      lVar9 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,3);
      FUN_7ffe9b436460(lVar9,uRam00007ffe9c933458,0);
      if (lVar9 == 0) goto LAB_7ffe9a5d5b9f;
      lVar10 = (ulonglong)*(byte *)(lVar10 + 0x28) - 1;
      if (*(uint *)(lVar9 + 0x18) <= (uint)lVar10) {
LAB_7ffe9a5d5ba5:
        FUN_7ffe9996d790();
        pcVar5 = (code *)swi(3);
        puVar11 = (undefined *)(*pcVar5)();
        return puVar11;
      }
      sVar2 = *(short *)(self + 0xb0);
      iVar3 = *(int *)(lVar9 + 0x20 + lVar10 * 4);
      uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8,
                                  (longlong)(int)sVar2 % (longlong)iVar3 & 0xffffffff);
      FUN_7ffe9a37b0f0(uVar8,cVar14,0x28,6,(int)sVar2 / iVar3,0,0,0,0);
      if (lVar7 == 0) goto LAB_7ffe9a5d5b9f;
      FUN_7ffe99743100(lVar7);
      uVar12 = uVar12 + 1;
      cVar14 = cVar14 + '\x01';
      goto LAB_7ffe9a5d5435;
    case 0xcf:
    case 0xd0:
      break;
    case 0xd1:
      bVar1 = *(byte *)(lVar10 + 0x28);
      uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8);
      FUN_7ffe9a37b0f0(uVar8,cVar14,0xf,8,300,((uint)bVar1 + (uint)bVar1 * 4) * 2,0,0,0);
      if (lVar7 == 0) goto LAB_7ffe9a5d5b9f;
      FUN_7ffe99743100(lVar7,uVar8,_DAT_7ffe9c93d430);
      uVar12 = uVar12 + 1;
      cVar14 = cVar14 + '\x01';
      goto LAB_7ffe9a5d5435;
    case 0xd2:
      bVar1 = *(byte *)(lVar10 + 0x28);
      if (*(int *)(_DAT_7ffe9c96ec48 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar8 = FUN_7ffe9b52cc00(uVar8,0);
      if (*(int *)(_DAT_7ffe9c8f82e8 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar8 = FUN_7ffe9b5406b0(uVar8,0);
      uVar8 = FUN_7ffe9ab7b790(uVar8,uRam00007ffe9c8fc1d8);
      lVar10 = FUN_7ffe9ab90890(uVar8);
      uVar13 = 0;
      while( true ) {
        if (lVar10 == 0) goto LAB_7ffe9a5d5b9f;
        if ((int)*(uint *)(lVar10 + 0x18) <= (int)uVar13) break;
        if (*(uint *)(lVar10 + 0x18) <= uVar13) goto LAB_7ffe9a5d5ba5;
        iVar3 = *(int *)(lVar10 + 0x20 + (longlong)(int)uVar13 * 4);
        if ((((1 < iVar3 + 1U) && (cVar6 = func_0x7ffe9a4deb00(iVar3), cVar6 == '\0')) &&
            (cVar6 = func_0x7ffe9a4deb90(iVar3), cVar6 == '\0')) &&
           (cVar6 = func_0x7ffe9a4deb20(iVar3), cVar6 == '\0')) {
          uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8);
          FUN_7ffe9a37b0f0(uVar8,cVar14,1,iVar3,0,(uint)bVar1 * 0xf,0,0,0);
          if (lVar7 == 0) goto LAB_7ffe9a5d5b9f;
          FUN_7ffe99743100(lVar7,uVar8,_DAT_7ffe9c93d430);
          cVar14 = cVar14 + '\x01';
        }
        uVar13 = uVar13 + 1;
      }
      break;
    default:
      if (iVar3 == 0x131) {
        uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8efec8);
        FUN_7ffe9a37b0f0(uVar8,cVar14,0x2a,7,0x5a,0,0,0,0);
        if (lVar7 == 0) goto LAB_7ffe9a5d5b9f;
        FUN_7ffe99743100(lVar7,uVar8,_DAT_7ffe9c93d430);
        uVar12 = uVar12 + 1;
        cVar14 = cVar14 + '\x01';
        goto LAB_7ffe9a5d5435;
      }
    }
LAB_7ffe9a5d5b53:
    uVar12 = uVar12 + 1;
    goto LAB_7ffe9a5d5435;
  }
  goto LAB_7ffe9a5d5b61;
code_r0x7ffe9a5d5503:
  FUN_7ffe99743100(lVar7);
  uVar12 = uVar12 + 1;
  cVar14 = cVar14 + '\x01';
  goto LAB_7ffe9a5d5435;
}

