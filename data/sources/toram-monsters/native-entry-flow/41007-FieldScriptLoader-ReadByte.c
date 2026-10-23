
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte FieldScriptLoader_ReadByte(undefined *self,byte val,undefined *methodInfo)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  undefined *self_00;
  undefined4 *puVar5;
  float *pfVar6;
  undefined8 *puVar7;
  longlong *plVar8;
  longlong lVar9;
  longlong lVar10;
  undefined8 uVar11;
  uint uVar12;
  undefined4 uVar13;
  ushort uVar14;
  undefined4 uVar15;
  code *pcVar16;
  float fVar17;
  uint auStackX_10 [4];
  longlong lStackX_20;
  longlong lStack_58;
  longlong lStack_50;
  undefined8 uStack_48;
  float fStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined8 uStack_30;
  undefined1 auStack_28 [16];
  
  lVar9 = *(longlong *)(self + 0x20);
  bVar2 = 0;
  if (lVar9 != 0) {
    uVar12 = *(uint *)(self + 0x2c);
    if (*(uint *)(lVar9 + 0x18) <= uVar12) {
      uStack_30 = 0x7ffe9a9fc18b;
      FUN_7ffe9996d790();
      pcVar16 = (code *)swi(3);
      bVar2 = (*pcVar16)();
      return bVar2;
    }
    bVar2 = *(byte *)((longlong)(int)uVar12 + 0x20 + lVar9);
    *(uint *)(self + 0x2c) = uVar12 + 1;
  }
  if (val == 0) {
    return bVar2;
  }
  uVar12 = (uint)bVar2;
  if (DAT_7ffe9cae0531 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9499d0);
    FUN_7ffe9996d590(0x7ffe9c971e18);
    FUN_7ffe9996d590(&DAT_7ffe9c9240a0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(0x7ffe9c901b68);
    FUN_7ffe9996d590(0x7ffe9c901f78);
    FUN_7ffe9996d590(&DAT_7ffe9c91a848);
    DAT_7ffe9cae0531 = '\x01';
  }
  if (uVar12 < 0x15) {
    lVar9 = *(longlong *)(self + 0x30);
    if (lVar9 != 0) {
      if (uVar12 < *(uint *)(lVar9 + 0x18)) {
        return (byte)*(undefined4 *)(lVar9 + 0x20 + (longlong)(int)uVar12 * 4);
      }
      FUN_7ffe9996d790();
      pcVar16 = (code *)swi(3);
      bVar2 = (*pcVar16)();
      return bVar2;
    }
    goto LAB_7ffe9a9fba74;
  }
  switch(uVar12) {
  case 0xe0:
    self_00 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (self_00 != (undefined *)0x0) {
      sVar3 = RoomManager_GetAreaLevel(self_00,-1,(undefined *)0x0);
      return (byte)sVar3;
    }
    break;
  case 0xe1:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 100;
    }
    lVar9 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar9 != 0) && (plVar8 = (longlong *)FUN_7ffe9a47fe30(lVar9,0), plVar8 != (longlong *)0x0))
    {
      fVar17 = (float)(**(code **)(*plVar8 + 0x1d8))(plVar8,*(undefined8 *)(*plVar8 + 0x1e0));
      return (byte)(int)((fVar17 * _DAT_7ffe9c049cfc) / _UNK_7ffe9c049b80);
    }
    break;
  case 0xe2:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    lVar9 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar9 != 0) && (lVar9 = FUN_7ffe9a480940(lVar9,0), lVar9 != 0)) {
      puVar5 = (undefined4 *)FUN_7ffe9bdbf880(auStack_28,lVar9,0);
      uStack_38 = *puVar5;
      uStack_34 = puVar5[1];
      uStack_30._0_4_ = puVar5[2];
      uStack_30._4_4_ = puVar5[3];
      puVar7 = (undefined8 *)FUN_7ffe9bda3580(auStack_28,&uStack_38,0);
      fStack_40 = *(float *)(puVar7 + 1) * _DAT_7ffe9c049d68;
      uStack_30 = CONCAT44(uStack_30._4_4_,fStack_40);
      uStack_48 = CONCAT44((float)((ulonglong)*puVar7 >> 0x20) * _DAT_7ffe9c049d68,
                           (float)*puVar7 * _DAT_7ffe9c049d68);
      lVar9 = func_0x7ffe9bda34a0(&uStack_38,&uStack_48,0);
      return (byte)(int)(*(float *)(lVar9 + 4) + _DAT_7ffe9c049b4c);
    }
    break;
  case 0xe3:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    lVar9 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar9 != 0) && (lVar9 = FUN_7ffe9a480940(lVar9,0), lVar9 != 0)) {
      lVar9 = FUN_7ffe9bdbf710(auStack_28,lVar9,0);
      return (byte)(int)((*(float *)(lVar9 + 8) + _UNK_7ffe9c049b3c) * _DAT_7ffe9c049ce4);
    }
    break;
  case 0xe4:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    lVar9 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar9 != 0) && (lVar9 = FUN_7ffe9a480940(lVar9,0), lVar9 != 0)) {
      lVar9 = FUN_7ffe9bdbf710(auStack_28,lVar9,0);
      return (byte)(int)((*(float *)(lVar9 + 4) + _UNK_7ffe9c049b3c) * _DAT_7ffe9c049ce4);
    }
    break;
  case 0xe5:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    lVar9 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar9 != 0) && (lVar9 = FUN_7ffe9a480940(lVar9,0), lVar9 != 0)) {
      pfVar6 = (float *)FUN_7ffe9bdbf710(auStack_28,lVar9,0);
      return (byte)(int)((*pfVar6 + _UNK_7ffe9c049b3c) * _DAT_7ffe9c049ce4);
    }
    break;
  case 0xe6:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    lVar9 = FUN_7ffe9a9fcab0(self,0);
    if (lVar9 != 0) {
      fVar17 = (float)FUN_7ffe9a47ff30(lVar9,0);
      return (byte)(int)(fVar17 * _DAT_7ffe9c049c90);
    }
    break;
  case 0xe7:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (lVar9 != 0) {
      plVar8 = *(longlong **)(lVar9 + 0x28);
      if (plVar8 == (longlong *)0x0) {
        return 0;
      }
      if (*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c9499d0 + 0x130)) {
        return 0;
      }
      if (*(longlong *)
           (*(longlong *)(*plVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9499d0 + 0x130) * 8)
          != _DAT_7ffe9c9499d0) {
        return 0;
      }
      bVar2 = (**(code **)(*plVar8 + 0x1a8))(plVar8,*(undefined8 *)(*plVar8 + 0x1b0));
      return bVar2;
    }
    break;
  case 0xe8:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar9 != 0) {
      iVar4 = FUN_7ffe9a872680(lVar9,0);
      if (iVar4 == 0x19) {
        lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
        if (lVar9 != 0) {
          plVar8 = *(longlong **)(lVar9 + 0x28);
          if (plVar8 == (longlong *)0x0) {
            return 0;
          }
          if (*(byte *)(*plVar8 + 0x130) < *(byte *)(lRam00007ffe9c901b68 + 0x130)) {
            return 0;
          }
          if (*(longlong *)
               (*(longlong *)(*plVar8 + 200) + -8 +
               (ulonglong)*(byte *)(lRam00007ffe9c901b68 + 0x130) * 8) != lRam00007ffe9c901b68) {
            return 0;
          }
          return (byte)(int)plVar8[0xd];
        }
      }
      else {
        lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
        if (lVar9 != 0) {
          plVar8 = *(longlong **)(lVar9 + 0x28);
          if (plVar8 == (longlong *)0x0) {
            return 0;
          }
          if (*(byte *)(*plVar8 + 0x130) < *(byte *)(lRam00007ffe9c901f78 + 0x130)) {
            return 0;
          }
          if (*(longlong *)
               (*(longlong *)(*plVar8 + 200) + -8 +
               (ulonglong)*(byte *)(lRam00007ffe9c901f78 + 0x130) * 8) != lRam00007ffe9c901f78) {
            return 0;
          }
          return (byte)(int)plVar8[0xd];
        }
      }
    }
    break;
  case 0xe9:
    return 3;
  case 0xea:
    lStackX_20 = 0;
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar9 != 0) {
      cVar1 = FUN_7ffe9a5a1920(lVar9,&lStackX_20,0);
      if (cVar1 == '\0') {
        return 0xff;
      }
      if (lStackX_20 != 0) {
        return (byte)*(undefined4 *)(lStackX_20 + 0x40);
      }
    }
    break;
  case 0xeb:
    lStack_58 = 0;
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar9 != 0) {
      cVar1 = FUN_7ffe9a5a1920(lVar9,&lStack_58,0);
      if (cVar1 == '\0') {
        return 0xff;
      }
      if (lStack_58 != 0) {
        return (byte)*(undefined4 *)(lStack_58 + 0x44);
      }
    }
    break;
  case 0xec:
    lStack_50 = 0;
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar9 != 0) {
      cVar1 = FUN_7ffe9a5a1920(lVar9,&lStack_50,0);
      if (cVar1 == '\0') {
        return 0xff;
      }
      if (lStack_50 != 0) {
        return (byte)*(undefined4 *)(lStack_50 + 0x3c);
      }
    }
    break;
  case 0xed:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar9 != 0) {
      cVar1 = FUN_7ffe9a5a4230(lVar9,0);
code_r0x7ffe9a9fb012:
      if (cVar1 == '\0') {
        return 0;
      }
      return 1;
    }
    break;
  case 0xee:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    lVar9 = FUN_7ffe9a9fcab0(self,0);
    if (lVar9 != 0) {
      cVar1 = FUN_7ffe9a47fb00(lVar9,0);
code_r0x7ffe9a9fb07f:
      if (cVar1 != '\0') {
        return 0;
      }
      return 1;
    }
    break;
  case 0xef:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar9 != 0) {
      bVar2 = FUN_7ffe9a59baf0(lVar9,4,0);
      return bVar2;
    }
    break;
  case 0xf0:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar9 != 0) {
      bVar2 = FUN_7ffe9a59baf0(lVar9,5,0);
      return bVar2;
    }
    break;
  case 0xf1:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar9 != 0) {
      bVar2 = FUN_7ffe9a59baf0(lVar9,6,0);
      return bVar2;
    }
    break;
  case 0xf2:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar9 != 0) {
      cVar1 = FUN_7ffe9a59b9e0(lVar9,0,0);
      return cVar1 - 1;
    }
    break;
  case 0xf3:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    if (*(longlong *)(self + 0x10) != 0) {
      lVar9 = FUN_7ffe9a480070(*(longlong *)(self + 0x10),0);
      if (lVar9 == 0) {
        return 0xff;
      }
      if ((*(longlong *)(self + 0x10) != 0) &&
         (plVar8 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
         plVar8 != (longlong *)0x0)) {
        lVar9 = (**(code **)(*plVar8 + 0x188))(plVar8,*(undefined8 *)(*plVar8 + 400));
        if (lVar9 == 0) {
          return 0xff;
        }
        if (((*(longlong *)(self + 0x10) != 0) &&
            (plVar8 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
            plVar8 != (longlong *)0x0)) &&
           (lVar9 = (**(code **)(*plVar8 + 0x188))(plVar8,*(undefined8 *)(*plVar8 + 400)),
           lVar9 != 0)) {
          return (byte)*(undefined4 *)(lVar9 + 0x3c);
        }
      }
    }
    break;
  case 0xf4:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    if (*(longlong *)(self + 0x10) != 0) {
      lVar9 = FUN_7ffe9a480070(*(longlong *)(self + 0x10),0);
      if (lVar9 == 0) {
        return 0xff;
      }
      if ((*(longlong *)(self + 0x10) != 0) &&
         (plVar8 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
         plVar8 != (longlong *)0x0)) {
        lVar9 = (**(code **)(*plVar8 + 0x188))(plVar8,*(undefined8 *)(*plVar8 + 400));
        if (lVar9 == 0) {
          return 0xff;
        }
        if (((*(longlong *)(self + 0x10) != 0) &&
            (plVar8 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
            plVar8 != (longlong *)0x0)) &&
           (lVar9 = (**(code **)(*plVar8 + 0x188))(plVar8,*(undefined8 *)(*plVar8 + 400)),
           lVar9 != 0)) {
          return (byte)*(undefined4 *)(lVar9 + 0x38);
        }
      }
    }
    break;
  case 0xf5:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (lVar9 != 0) {
      plVar8 = *(longlong **)(lVar9 + 0x28);
      if (plVar8 == (longlong *)0x0) {
        return 0;
      }
      if (*(byte *)(*plVar8 + 0x130) < *(byte *)(lRam00007ffe9c971e18 + 0x130)) {
        return 0;
      }
      if (*(longlong *)
           (*(longlong *)(*plVar8 + 200) + -8 +
           (ulonglong)*(byte *)(lRam00007ffe9c971e18 + 0x130) * 8) != lRam00007ffe9c971e18) {
        return 0;
      }
      cVar1 = func_0x7ffe9a5d2150(plVar8,0);
      if (cVar1 != '\0') {
        return 2;
      }
      cVar1 = func_0x7ffe9a5d2160(plVar8,0);
      goto code_r0x7ffe9a9fb012;
    }
    break;
  case 0xf6:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0;
    }
    if ((*(longlong *)(self + 0x10) == 0) ||
       (plVar8 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
       plVar8 == (longlong *)0x0)) break;
    pcVar16 = *(code **)(*plVar8 + 0x188);
    uVar11 = *(undefined8 *)(*plVar8 + 400);
    goto code_r0x7ffe9a9fb571;
  case 0xf7:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    if (((*(longlong *)(self + 0x10) != 0) &&
        (plVar8 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
        plVar8 != (longlong *)0x0)) &&
       (plVar8 = (longlong *)(**(code **)(*plVar8 + 0x198))(plVar8,*(undefined8 *)(*plVar8 + 0x1a0))
       , plVar8 != (longlong *)0x0)) {
      lVar9 = *plVar8;
      uVar14 = 0;
      if (*(ushort *)(lVar9 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar14 * 0x10) ==
              _DAT_7ffe9c940d40) {
            puVar7 = (undefined8 *)
                     ((longlong)
                      (*(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar14 * 0x10) + 10) *
                      0x10 + 0x138 + lVar9);
            goto code_r0x7ffe9a9fb4d5;
          }
          uVar14 = uVar14 + 1;
        } while (uVar14 < *(ushort *)(lVar9 + 0x12e));
      }
      puVar7 = (undefined8 *)FUN_7ffe998ce540(plVar8,_DAT_7ffe9c940d40,10);
code_r0x7ffe9a9fb4d5:
      bVar2 = (*(code *)*puVar7)(plVar8,puVar7[1]);
      return bVar2;
    }
    break;
  case 0xf8:
    uVar11 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar11,0,0);
    if (cVar1 != '\0') {
      return 0xff;
    }
    if ((*(longlong *)(self + 0x10) == 0) ||
       (plVar8 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
       plVar8 == (longlong *)0x0)) break;
    pcVar16 = *(code **)(*plVar8 + 0x178);
    uVar11 = *(undefined8 *)(*plVar8 + 0x180);
code_r0x7ffe9a9fb571:
    lVar9 = (*pcVar16)(plVar8,uVar11);
    if (lVar9 != 0) {
      return (byte)*(undefined4 *)(lVar9 + 0x10);
    }
    break;
  case 0xf9:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar9 != 0) {
      iVar4 = FUN_7ffe9a872680(lVar9,0);
      if (iVar4 == 0x19) {
        lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
        if (lVar9 != 0) {
          plVar8 = *(longlong **)(lVar9 + 0x28);
          if (plVar8 == (longlong *)0x0) {
            return 0;
          }
          if (*(byte *)(*plVar8 + 0x130) < *(byte *)(lRam00007ffe9c901b68 + 0x130)) {
            return 0;
          }
          if (*(longlong *)
               (*(longlong *)(*plVar8 + 200) + -8 +
               (ulonglong)*(byte *)(lRam00007ffe9c901b68 + 0x130) * 8) != lRam00007ffe9c901b68) {
            return 0;
          }
          cVar1 = func_0x7ffe9a62ff60(plVar8,0);
          goto code_r0x7ffe9a9fb012;
        }
      }
      else {
        lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
        if (lVar9 != 0) {
          iVar4 = FUN_7ffe9a872680(lVar9,0);
          if (iVar4 == 3) {
            lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
            if (lVar9 != 0) {
              plVar8 = *(longlong **)(lVar9 + 0x28);
              if (plVar8 == (longlong *)0x0) {
                return 0;
              }
              if (*(byte *)(*plVar8 + 0x130) < *(byte *)(lRam00007ffe9c901f78 + 0x130)) {
                return 0;
              }
              if (*(longlong *)
                   (*(longlong *)(*plVar8 + 200) + -8 +
                   (ulonglong)*(byte *)(lRam00007ffe9c901f78 + 0x130) * 8) != lRam00007ffe9c901f78)
              {
                return 0;
              }
              cVar1 = func_0x7ffe9a62ff60(plVar8,0);
              goto code_r0x7ffe9a9fb012;
            }
          }
          else {
            lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
            if (lVar9 != 0) {
              iVar4 = FUN_7ffe9a872680(lVar9,0);
              if (iVar4 == 0x1d) {
                lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
                if (lVar9 != 0) {
                  plVar8 = *(longlong **)(lVar9 + 0x28);
                  if (plVar8 == (longlong *)0x0) {
                    return 0;
                  }
                  if (*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c9240a0 + 0x130)) {
                    return 0;
                  }
                  if (*(longlong *)
                       (*(longlong *)(*plVar8 + 200) + -8 +
                       (ulonglong)*(byte *)(_DAT_7ffe9c9240a0 + 0x130) * 8) != _DAT_7ffe9c9240a0) {
                    return 0;
                  }
                  cVar1 = func_0x7ffe9a5d7390(plVar8,0);
                  goto code_r0x7ffe9a9fb07f;
                }
              }
              else {
                lVar9 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                if (lVar9 != 0) {
                  if (*(longlong *)(lVar9 + 0x38) == 0) {
                    return 0;
                  }
                  lVar9 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                  if ((lVar9 != 0) && (*(longlong *)(lVar9 + 0x38) != 0)) {
                    return *(byte *)(*(longlong *)(lVar9 + 0x38) + 0x10);
                  }
                }
              }
            }
          }
        }
      }
    }
    break;
  case 0xfa:
    if (cRam00007ffe9cae0532 == '\0') {
      FUN_7ffe9996d590(0x7ffe9c9227e8);
      cRam00007ffe9cae0532 = '\x01';
    }
    uVar15 = 0;
    uVar13 = 0;
    lVar9 = FUN_7ffe9a9fcab0(self,0);
    if (((lVar9 != 0) && (plVar8 = (longlong *)FUN_7ffe9a480070(lVar9,0), plVar8 != (longlong *)0x0)
        ) && (lVar9 = (**(code **)(*plVar8 + 0x1f8))(plVar8,*(undefined8 *)(*plVar8 + 0x200)),
             lVar9 != 0)) {
      lVar9 = FUN_7ffe99c090e0(lVar9,0);
      if (lVar9 != 0) {
        uVar15 = *(undefined4 *)(lVar9 + 0x38);
      }
      lVar9 = FUN_7ffe9a9fcab0(self,0);
      if (((lVar9 != 0) &&
          (plVar8 = (longlong *)FUN_7ffe9a480070(lVar9,0), plVar8 != (longlong *)0x0)) &&
         (lVar9 = (**(code **)(*plVar8 + 0x1f8))(plVar8,*(undefined8 *)(*plVar8 + 0x200)),
         lVar9 != 0)) {
        lVar9 = FUN_7ffe99c08fe0(lVar9,0);
        if (lVar9 != 0) {
          uVar13 = *(undefined4 *)(lVar9 + 0x38);
        }
        if (*(int *)(lRam00007ffe9c9227e8 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        bVar2 = FUN_7ffe9a7e62b0(uVar15,uVar13,0);
        return bVar2;
      }
    }
    break;
  case 0xfb:
    lVar9 = FUN_7ffe9a9fcab0(self,0);
    if (((lVar9 != 0) && (plVar8 = (longlong *)FUN_7ffe9a480070(lVar9,0), plVar8 != (longlong *)0x0)
        ) && (lVar9 = (**(code **)(*plVar8 + 0x1f8))(plVar8,*(undefined8 *)(*plVar8 + 0x200)),
             lVar9 != 0)) {
      lVar9 = FUN_7ffe99c090e0(lVar9,0);
      if ((lVar9 == 0) || (iVar4 = *(int *)(lVar9 + 0x38), iVar4 == 0)) {
        return 6;
      }
      if (iVar4 == 8) {
        return 8;
      }
      if (iVar4 != 9) {
        return (char)iVar4 - 10;
      }
      return 7;
    }
    break;
  case 0xfc:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar9 != 0) {
      bVar2 = FUN_7ffe9a872660(lVar9,0);
      return bVar2;
    }
    break;
  case 0xfd:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar9 != 0) {
      bVar2 = FUN_7ffe9a872680(lVar9,0);
      return bVar2;
    }
    break;
  case 0xfe:
    lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar9 != 0) {
      bVar2 = FUN_7ffe9a8721b0(lVar9,0);
      return bVar2;
    }
    break;
  default:
    plVar8 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
    auStackX_10[0] = uVar12;
    lVar9 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,auStackX_10);
    if (plVar8 == (longlong *)0x0) {
      FUN_7ffe9996d7a0();
      pcVar16 = (code *)swi(3);
      bVar2 = (*pcVar16)();
      return bVar2;
    }
    if ((lVar9 != 0) &&
       (lVar10 = func_0x7ffe9996c920(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0)) {
      uVar11 = func_0x7ffe9996d1f0();
      FUN_7ffe9996d760(uVar11,0);
      pcVar16 = (code *)swi(3);
      bVar2 = (*pcVar16)();
      return bVar2;
    }
    if ((int)plVar8[3] != 0) {
      plVar8[4] = lVar9;
      il2cpp_write_barrier_0();
      func_0x7ffe999c3920(_DAT_7ffe9c91a848,plVar8,0);
      return 0;
    }
    FUN_7ffe9996d790();
    pcVar16 = (code *)swi(3);
    bVar2 = (*pcVar16)();
    return bVar2;
  }
LAB_7ffe9a9fba74:
  FUN_7ffe9996d7a0();
  pcVar16 = (code *)swi(3);
  bVar2 = (*pcVar16)();
  return bVar2;
}

