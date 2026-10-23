
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

short FieldScriptLoader_ReadShort(undefined *self,byte val,undefined *methodInfo)

{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined *self_00;
  undefined4 *puVar4;
  float *pfVar5;
  undefined8 *puVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  uint uVar11;
  undefined4 uVar12;
  ushort uVar13;
  undefined4 uVar14;
  byte bVar15;
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
  
  lVar8 = *(longlong *)(self + 0x20);
  if (val == 0) {
    if (lVar8 != 0) {
      uStack_30 = 0x7ffe9a9fc616;
      sVar2 = FUN_7ffe9b482c10(lVar8,*(undefined4 *)(self + 0x2c),0);
      *(int *)(self + 0x2c) = *(int *)(self + 0x2c) + 2;
      return sVar2;
    }
    return -1;
  }
  if (lVar8 == 0) {
    bVar15 = 0;
  }
  else {
    uVar11 = *(uint *)(self + 0x2c);
    if (*(uint *)(lVar8 + 0x18) <= uVar11) {
      uStack_30 = 0x7ffe9a9fc630;
      FUN_7ffe9996d790();
      pcVar16 = (code *)swi(3);
      sVar2 = (*pcVar16)();
      return sVar2;
    }
    bVar15 = *(byte *)((longlong)(int)uVar11 + 0x20 + lVar8);
    *(uint *)(self + 0x2c) = uVar11 + 1;
  }
  uVar11 = (uint)bVar15;
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
  if (bVar15 < 0x15) {
    lVar8 = *(longlong *)(self + 0x30);
    if (lVar8 != 0) {
      if (uVar11 < *(uint *)(lVar8 + 0x18)) {
        return (short)*(undefined4 *)(lVar8 + 0x20 + (longlong)(int)uVar11 * 4);
      }
      FUN_7ffe9996d790();
      pcVar16 = (code *)swi(3);
      sVar2 = (*pcVar16)();
      return sVar2;
    }
    goto LAB_7ffe9a9fba74;
  }
  switch(uVar11) {
  case 0xe0:
    self_00 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (self_00 != (undefined *)0x0) {
      sVar2 = RoomManager_GetAreaLevel(self_00,-1,(undefined *)0x0);
      return sVar2;
    }
    break;
  case 0xe1:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return 100;
    }
    lVar8 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar8 != 0) && (plVar7 = (longlong *)FUN_7ffe9a47fe30(lVar8,0), plVar7 != (longlong *)0x0))
    {
      fVar17 = (float)(**(code **)(*plVar7 + 0x1d8))(plVar7,*(undefined8 *)(*plVar7 + 0x1e0));
      return (short)(int)((fVar17 * _DAT_7ffe9c049cfc) / _UNK_7ffe9c049b80);
    }
    break;
  case 0xe2:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    lVar8 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar8 != 0) && (lVar8 = FUN_7ffe9a480940(lVar8,0), lVar8 != 0)) {
      puVar4 = (undefined4 *)FUN_7ffe9bdbf880(auStack_28,lVar8,0);
      uStack_38 = *puVar4;
      uStack_34 = puVar4[1];
      uStack_30._0_4_ = puVar4[2];
      uStack_30._4_4_ = puVar4[3];
      puVar6 = (undefined8 *)FUN_7ffe9bda3580(auStack_28,&uStack_38,0);
      fStack_40 = *(float *)(puVar6 + 1) * _DAT_7ffe9c049d68;
      uStack_30 = CONCAT44(uStack_30._4_4_,fStack_40);
      uStack_48 = CONCAT44((float)((ulonglong)*puVar6 >> 0x20) * _DAT_7ffe9c049d68,
                           (float)*puVar6 * _DAT_7ffe9c049d68);
      lVar8 = func_0x7ffe9bda34a0(&uStack_38,&uStack_48,0);
      return (short)(int)(*(float *)(lVar8 + 4) + _DAT_7ffe9c049b4c);
    }
    break;
  case 0xe3:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    lVar8 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar8 != 0) && (lVar8 = FUN_7ffe9a480940(lVar8,0), lVar8 != 0)) {
      lVar8 = FUN_7ffe9bdbf710(auStack_28,lVar8,0);
      return (short)(int)((*(float *)(lVar8 + 8) + _UNK_7ffe9c049b3c) * _DAT_7ffe9c049ce4);
    }
    break;
  case 0xe4:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    lVar8 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar8 != 0) && (lVar8 = FUN_7ffe9a480940(lVar8,0), lVar8 != 0)) {
      lVar8 = FUN_7ffe9bdbf710(auStack_28,lVar8,0);
      return (short)(int)((*(float *)(lVar8 + 4) + _UNK_7ffe9c049b3c) * _DAT_7ffe9c049ce4);
    }
    break;
  case 0xe5:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    lVar8 = FUN_7ffe9a9fcab0(self,0);
    if ((lVar8 != 0) && (lVar8 = FUN_7ffe9a480940(lVar8,0), lVar8 != 0)) {
      pfVar5 = (float *)FUN_7ffe9bdbf710(auStack_28,lVar8,0);
      return (short)(int)((*pfVar5 + _UNK_7ffe9c049b3c) * _DAT_7ffe9c049ce4);
    }
    break;
  case 0xe6:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    lVar8 = FUN_7ffe9a9fcab0(self,0);
    if (lVar8 != 0) {
      fVar17 = (float)FUN_7ffe9a47ff30(lVar8,0);
      return (short)(int)(fVar17 * _DAT_7ffe9c049c90);
    }
    break;
  case 0xe7:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (lVar8 != 0) {
      plVar7 = *(longlong **)(lVar8 + 0x28);
      if (plVar7 == (longlong *)0x0) {
        return 0;
      }
      if (*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7ffe9c9499d0 + 0x130)) {
        return 0;
      }
      if (*(longlong *)
           (*(longlong *)(*plVar7 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9499d0 + 0x130) * 8)
          != _DAT_7ffe9c9499d0) {
        return 0;
      }
      sVar2 = (**(code **)(*plVar7 + 0x1a8))(plVar7,*(undefined8 *)(*plVar7 + 0x1b0));
      return sVar2;
    }
    break;
  case 0xe8:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar8 != 0) {
      iVar3 = FUN_7ffe9a872680(lVar8,0);
      if (iVar3 == 0x19) {
        lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
        if (lVar8 != 0) {
          plVar7 = *(longlong **)(lVar8 + 0x28);
          if (plVar7 == (longlong *)0x0) {
            return 0;
          }
          if (*(byte *)(*plVar7 + 0x130) < *(byte *)(lRam00007ffe9c901b68 + 0x130)) {
            return 0;
          }
          if (*(longlong *)
               (*(longlong *)(*plVar7 + 200) + -8 +
               (ulonglong)*(byte *)(lRam00007ffe9c901b68 + 0x130) * 8) != lRam00007ffe9c901b68) {
            return 0;
          }
          return (short)(int)plVar7[0xd];
        }
      }
      else {
        lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
        if (lVar8 != 0) {
          plVar7 = *(longlong **)(lVar8 + 0x28);
          if (plVar7 == (longlong *)0x0) {
            return 0;
          }
          if (*(byte *)(*plVar7 + 0x130) < *(byte *)(lRam00007ffe9c901f78 + 0x130)) {
            return 0;
          }
          if (*(longlong *)
               (*(longlong *)(*plVar7 + 200) + -8 +
               (ulonglong)*(byte *)(lRam00007ffe9c901f78 + 0x130) * 8) != lRam00007ffe9c901f78) {
            return 0;
          }
          return (short)(int)plVar7[0xd];
        }
      }
    }
    break;
  case 0xe9:
    return 3;
  case 0xea:
    lStackX_20 = 0;
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar8 != 0) {
      cVar1 = FUN_7ffe9a5a1920(lVar8,&lStackX_20,0);
      if (cVar1 == '\0') {
        return -1;
      }
      if (lStackX_20 != 0) {
        return (short)*(undefined4 *)(lStackX_20 + 0x40);
      }
    }
    break;
  case 0xeb:
    lStack_58 = 0;
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar8 != 0) {
      cVar1 = FUN_7ffe9a5a1920(lVar8,&lStack_58,0);
      if (cVar1 == '\0') {
        return -1;
      }
      if (lStack_58 != 0) {
        return (short)*(undefined4 *)(lStack_58 + 0x44);
      }
    }
    break;
  case 0xec:
    lStack_50 = 0;
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar8 != 0) {
      cVar1 = FUN_7ffe9a5a1920(lVar8,&lStack_50,0);
      if (cVar1 == '\0') {
        return -1;
      }
      if (lStack_50 != 0) {
        return (short)*(undefined4 *)(lStack_50 + 0x3c);
      }
    }
    break;
  case 0xed:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar8 != 0) {
      cVar1 = FUN_7ffe9a5a4230(lVar8,0);
code_r0x7ffe9a9fb012:
      if (cVar1 == '\0') {
        return 0;
      }
      return 1;
    }
    break;
  case 0xee:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    lVar8 = FUN_7ffe9a9fcab0(self,0);
    if (lVar8 != 0) {
      cVar1 = FUN_7ffe9a47fb00(lVar8,0);
code_r0x7ffe9a9fb07f:
      if (cVar1 != '\0') {
        return 0;
      }
      return 1;
    }
    break;
  case 0xef:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar8 != 0) {
      sVar2 = FUN_7ffe9a59baf0(lVar8,4,0);
      return sVar2;
    }
    break;
  case 0xf0:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar8 != 0) {
      sVar2 = FUN_7ffe9a59baf0(lVar8,5,0);
      return sVar2;
    }
    break;
  case 0xf1:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar8 != 0) {
      sVar2 = FUN_7ffe9a59baf0(lVar8,6,0);
      return sVar2;
    }
    break;
  case 0xf2:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar8 != 0) {
      sVar2 = FUN_7ffe9a59b9e0(lVar8,0,0);
      return sVar2 + -1;
    }
    break;
  case 0xf3:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    if (*(longlong *)(self + 0x10) != 0) {
      lVar8 = FUN_7ffe9a480070(*(longlong *)(self + 0x10),0);
      if (lVar8 == 0) {
        return -1;
      }
      if ((*(longlong *)(self + 0x10) != 0) &&
         (plVar7 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
         plVar7 != (longlong *)0x0)) {
        lVar8 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
        if (lVar8 == 0) {
          return -1;
        }
        if (((*(longlong *)(self + 0x10) != 0) &&
            (plVar7 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
            plVar7 != (longlong *)0x0)) &&
           (lVar8 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400)),
           lVar8 != 0)) {
          return (short)*(undefined4 *)(lVar8 + 0x3c);
        }
      }
    }
    break;
  case 0xf4:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    if (*(longlong *)(self + 0x10) != 0) {
      lVar8 = FUN_7ffe9a480070(*(longlong *)(self + 0x10),0);
      if (lVar8 == 0) {
        return -1;
      }
      if ((*(longlong *)(self + 0x10) != 0) &&
         (plVar7 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
         plVar7 != (longlong *)0x0)) {
        lVar8 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
        if (lVar8 == 0) {
          return -1;
        }
        if (((*(longlong *)(self + 0x10) != 0) &&
            (plVar7 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
            plVar7 != (longlong *)0x0)) &&
           (lVar8 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400)),
           lVar8 != 0)) {
          return (short)*(undefined4 *)(lVar8 + 0x38);
        }
      }
    }
    break;
  case 0xf5:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (lVar8 != 0) {
      plVar7 = *(longlong **)(lVar8 + 0x28);
      if (plVar7 == (longlong *)0x0) {
        return 0;
      }
      if (*(byte *)(*plVar7 + 0x130) < *(byte *)(lRam00007ffe9c971e18 + 0x130)) {
        return 0;
      }
      if (*(longlong *)
           (*(longlong *)(*plVar7 + 200) + -8 +
           (ulonglong)*(byte *)(lRam00007ffe9c971e18 + 0x130) * 8) != lRam00007ffe9c971e18) {
        return 0;
      }
      cVar1 = func_0x7ffe9a5d2150(plVar7,0);
      if (cVar1 != '\0') {
        return 2;
      }
      cVar1 = func_0x7ffe9a5d2160(plVar7,0);
      goto code_r0x7ffe9a9fb012;
    }
    break;
  case 0xf6:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return 0;
    }
    if ((*(longlong *)(self + 0x10) == 0) ||
       (plVar7 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
       plVar7 == (longlong *)0x0)) break;
    pcVar16 = *(code **)(*plVar7 + 0x188);
    uVar10 = *(undefined8 *)(*plVar7 + 400);
    goto code_r0x7ffe9a9fb571;
  case 0xf7:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    if (((*(longlong *)(self + 0x10) != 0) &&
        (plVar7 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
        plVar7 != (longlong *)0x0)) &&
       (plVar7 = (longlong *)(**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0))
       , plVar7 != (longlong *)0x0)) {
      lVar8 = *plVar7;
      uVar13 = 0;
      if (*(ushort *)(lVar8 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + (ulonglong)uVar13 * 0x10) ==
              _DAT_7ffe9c940d40) {
            puVar6 = (undefined8 *)
                     ((longlong)
                      (*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + (ulonglong)uVar13 * 0x10) + 10) *
                      0x10 + 0x138 + lVar8);
            goto code_r0x7ffe9a9fb4d5;
          }
          uVar13 = uVar13 + 1;
        } while (uVar13 < *(ushort *)(lVar8 + 0x12e));
      }
      puVar6 = (undefined8 *)FUN_7ffe998ce540(plVar7,_DAT_7ffe9c940d40,10);
code_r0x7ffe9a9fb4d5:
      sVar2 = (*(code *)*puVar6)(plVar7,puVar6[1]);
      return sVar2;
    }
    break;
  case 0xf8:
    uVar10 = FUN_7ffe9a9fcab0(self,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar1 = FUN_7ffe9bda1fa0(uVar10,0,0);
    if (cVar1 != '\0') {
      return -1;
    }
    if ((*(longlong *)(self + 0x10) == 0) ||
       (plVar7 = (longlong *)FUN_7ffe9a480070(*(longlong *)(self + 0x10),0),
       plVar7 == (longlong *)0x0)) break;
    pcVar16 = *(code **)(*plVar7 + 0x178);
    uVar10 = *(undefined8 *)(*plVar7 + 0x180);
code_r0x7ffe9a9fb571:
    lVar8 = (*pcVar16)(plVar7,uVar10);
    if (lVar8 != 0) {
      return (short)*(undefined4 *)(lVar8 + 0x10);
    }
    break;
  case 0xf9:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar8 != 0) {
      iVar3 = FUN_7ffe9a872680(lVar8,0);
      if (iVar3 == 0x19) {
        lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
        if (lVar8 != 0) {
          plVar7 = *(longlong **)(lVar8 + 0x28);
          if (plVar7 == (longlong *)0x0) {
            return 0;
          }
          if (*(byte *)(*plVar7 + 0x130) < *(byte *)(lRam00007ffe9c901b68 + 0x130)) {
            return 0;
          }
          if (*(longlong *)
               (*(longlong *)(*plVar7 + 200) + -8 +
               (ulonglong)*(byte *)(lRam00007ffe9c901b68 + 0x130) * 8) != lRam00007ffe9c901b68) {
            return 0;
          }
          cVar1 = func_0x7ffe9a62ff60(plVar7,0);
          goto code_r0x7ffe9a9fb012;
        }
      }
      else {
        lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
        if (lVar8 != 0) {
          iVar3 = FUN_7ffe9a872680(lVar8,0);
          if (iVar3 == 3) {
            lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
            if (lVar8 != 0) {
              plVar7 = *(longlong **)(lVar8 + 0x28);
              if (plVar7 == (longlong *)0x0) {
                return 0;
              }
              if (*(byte *)(*plVar7 + 0x130) < *(byte *)(lRam00007ffe9c901f78 + 0x130)) {
                return 0;
              }
              if (*(longlong *)
                   (*(longlong *)(*plVar7 + 200) + -8 +
                   (ulonglong)*(byte *)(lRam00007ffe9c901f78 + 0x130) * 8) != lRam00007ffe9c901f78)
              {
                return 0;
              }
              cVar1 = func_0x7ffe9a62ff60(plVar7,0);
              goto code_r0x7ffe9a9fb012;
            }
          }
          else {
            lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
            if (lVar8 != 0) {
              iVar3 = FUN_7ffe9a872680(lVar8,0);
              if (iVar3 == 0x1d) {
                lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
                if (lVar8 != 0) {
                  plVar7 = *(longlong **)(lVar8 + 0x28);
                  if (plVar7 == (longlong *)0x0) {
                    return 0;
                  }
                  if (*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7ffe9c9240a0 + 0x130)) {
                    return 0;
                  }
                  if (*(longlong *)
                       (*(longlong *)(*plVar7 + 200) + -8 +
                       (ulonglong)*(byte *)(_DAT_7ffe9c9240a0 + 0x130) * 8) != _DAT_7ffe9c9240a0) {
                    return 0;
                  }
                  cVar1 = func_0x7ffe9a5d7390(plVar7,0);
                  goto code_r0x7ffe9a9fb07f;
                }
              }
              else {
                lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                if (lVar8 != 0) {
                  if (*(longlong *)(lVar8 + 0x38) == 0) {
                    return 0;
                  }
                  lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                  if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x38) != 0)) {
                    return (short)*(byte *)(*(longlong *)(lVar8 + 0x38) + 0x10);
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
    uVar14 = 0;
    uVar12 = 0;
    lVar8 = FUN_7ffe9a9fcab0(self,0);
    if (((lVar8 != 0) && (plVar7 = (longlong *)FUN_7ffe9a480070(lVar8,0), plVar7 != (longlong *)0x0)
        ) && (lVar8 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200)),
             lVar8 != 0)) {
      lVar8 = FUN_7ffe99c090e0(lVar8,0);
      if (lVar8 != 0) {
        uVar14 = *(undefined4 *)(lVar8 + 0x38);
      }
      lVar8 = FUN_7ffe9a9fcab0(self,0);
      if (((lVar8 != 0) &&
          (plVar7 = (longlong *)FUN_7ffe9a480070(lVar8,0), plVar7 != (longlong *)0x0)) &&
         (lVar8 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200)),
         lVar8 != 0)) {
        lVar8 = FUN_7ffe99c08fe0(lVar8,0);
        if (lVar8 != 0) {
          uVar12 = *(undefined4 *)(lVar8 + 0x38);
        }
        if (*(int *)(lRam00007ffe9c9227e8 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        sVar2 = FUN_7ffe9a7e62b0(uVar14,uVar12,0);
        return sVar2;
      }
    }
    break;
  case 0xfb:
    lVar8 = FUN_7ffe9a9fcab0(self,0);
    if (((lVar8 != 0) && (plVar7 = (longlong *)FUN_7ffe9a480070(lVar8,0), plVar7 != (longlong *)0x0)
        ) && (lVar8 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200)),
             lVar8 != 0)) {
      lVar8 = FUN_7ffe99c090e0(lVar8,0);
      if ((lVar8 == 0) || (iVar3 = *(int *)(lVar8 + 0x38), iVar3 == 0)) {
        return 6;
      }
      if (iVar3 == 8) {
        return 8;
      }
      if (iVar3 != 9) {
        return (short)iVar3 + -10;
      }
      return 7;
    }
    break;
  case 0xfc:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar8 != 0) {
      sVar2 = FUN_7ffe9a872660(lVar8,0);
      return sVar2;
    }
    break;
  case 0xfd:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar8 != 0) {
      sVar2 = FUN_7ffe9a872680(lVar8,0);
      return sVar2;
    }
    break;
  case 0xfe:
    lVar8 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar8 != 0) {
      sVar2 = FUN_7ffe9a8721b0(lVar8,0);
      return sVar2;
    }
    break;
  default:
    plVar7 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
    auStackX_10[0] = uVar11;
    lVar8 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,auStackX_10);
    if (plVar7 == (longlong *)0x0) {
      FUN_7ffe9996d7a0();
      pcVar16 = (code *)swi(3);
      sVar2 = (*pcVar16)();
      return sVar2;
    }
    if ((lVar8 != 0) &&
       (lVar9 = func_0x7ffe9996c920(lVar8,*(undefined8 *)(*plVar7 + 0x40)), lVar9 == 0)) {
      uVar10 = func_0x7ffe9996d1f0();
      FUN_7ffe9996d760(uVar10,0);
      pcVar16 = (code *)swi(3);
      sVar2 = (*pcVar16)();
      return sVar2;
    }
    if ((int)plVar7[3] != 0) {
      plVar7[4] = lVar8;
      il2cpp_write_barrier_0();
      func_0x7ffe999c3920(_DAT_7ffe9c91a848,plVar7,0);
      return 0;
    }
    FUN_7ffe9996d790();
    pcVar16 = (code *)swi(3);
    sVar2 = (*pcVar16)();
    return sVar2;
  }
LAB_7ffe9a9fba74:
  FUN_7ffe9996d7a0();
  pcVar16 = (code *)swi(3);
  sVar2 = (*pcVar16)();
  return sVar2;
}

