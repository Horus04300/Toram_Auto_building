
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MapInfo_Initialize(undefined *self,undefined *roomType,byte roomId,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  ushort uVar3;
  undefined8 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 *puVar9;
  longlong *plVar10;
  ushort uVar11;
  byte abStackX_10 [8];
  byte abStackX_18 [16];
  longlong *plStack_68;
  undefined8 auStack_60 [2];
  longlong **pplStack_50;
  undefined8 *puStack_48;
  undefined8 uStack_40;
  longlong **pplStack_38;
  undefined8 uStack_30;
  
  abStackX_18[0] = roomId;
  if (DAT_7ffe9cadfb15 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94c948);
    FUN_7ffe9996d590(&DAT_7ffe9c901458);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c96ad18);
    FUN_7ffe9996d590(0x7ffe9c91feb8);
    FUN_7ffe9996d590(0x7ffe9c91fa08);
    FUN_7ffe9996d590(0x7ffe9c8eeab0);
    FUN_7ffe9996d590(0x7ffe9c940e80);
    FUN_7ffe9996d590(0x7ffe9c8f0990);
    FUN_7ffe9996d590(0x7ffe9c921308);
    FUN_7ffe9996d590(0x7ffe9c94fc90);
    FUN_7ffe9996d590(0x7ffe9c8f7738);
    FUN_7ffe9996d590(0x7ffe9c94ef88);
    FUN_7ffe9996d590(0x7ffe9c8fb7e8);
    FUN_7ffe9996d590(0x7ffe9c8f1f78);
    FUN_7ffe9996d590(0x7ffe9c94bb30);
    FUN_7ffe9996d590(0x7ffe9c935660);
    FUN_7ffe9996d590(0x7ffe9c940dc0);
    FUN_7ffe9996d590(0x7ffe9c9233d8);
    FUN_7ffe9996d590(0x7ffe9c924ff8);
    FUN_7ffe9996d590(0x7ffe9c94e968);
    FUN_7ffe9996d590(0x7ffe9c91ea68);
    FUN_7ffe9996d590(0x7ffe9c922690);
    FUN_7ffe9996d590(0x7ffe9c91f940);
    FUN_7ffe9996d590(0x7ffe9c8f1640);
    FUN_7ffe9996d590(0x7ffe9c91e9a0);
    FUN_7ffe9996d590(0x7ffe9c945320);
    FUN_7ffe9996d590(&DAT_7ffe9c94d6b8);
    DAT_7ffe9cadfb15 = '\x01';
  }
  auStack_60[0] = 0;
  uVar6 = **(undefined8 **)(_DAT_7ffe9c9590b8 + 0xb8);
  switch((int)roomType) {
  case 0:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c91fa08;
    break;
  case 1:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c94ef88;
    break;
  case 2:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c91feb8;
    break;
  case 3:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c921308;
    break;
  default:
    goto LAB_7ffe9a88f4ac;
  case 5:
  case 0x1e:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c8f1f78;
    break;
  case 7:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c8eeab0;
    break;
  case 10:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c922690;
    break;
  case 0xc:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c91ea68;
    break;
  case 0xd:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c91e9a0;
    break;
  case 0xe:
  case 0x23:
  case 0x27:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c940dc0;
    break;
  case 0x10:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c8f0990;
    break;
  case 0x13:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c94bb30;
    break;
  case 0x16:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c945320;
    break;
  case 0x17:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c91f940;
    break;
  case 0x19:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c940e80;
    break;
  case 0x1a:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c924ff8;
    break;
  case 0x1b:
    uVar6 = uRam00007ffe9c94fc90;
    goto LAB_7ffe9a88f4ac;
  case 0x1c:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c8f7738;
    break;
  case 0x1d:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c8f1640;
    break;
  case 0x22:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c935660;
    break;
  case 0x25:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c8fb7e8;
    break;
  case 0x28:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c94e968;
    break;
  case 0x29:
    uVar4 = FUN_7ffe9b485060(abStackX_18,0);
    uVar6 = uRam00007ffe9c9233d8;
  }
  uVar6 = FUN_7ffe9b3675b0(uVar6,uVar4,0);
LAB_7ffe9a88f4ac:
  lVar5 = FUN_7ffe9bd98a10(self,0);
  if (lVar5 != 0) {
    uVar6 = FUN_7ffe9bdbdd60(lVar5,uVar6,0);
    *(undefined8 *)(self + 0x20) = uVar6;
    il2cpp_write_barrier_0();
    uVar6 = *(undefined8 *)(self + 0x20);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    plVar10 = (longlong *)0x0;
    cVar2 = FUN_7ffe9bda2160(uVar6,0,0);
    if (cVar2 == '\0') {
      plVar7 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,2);
      uStack_40 = _DAT_7ffe9c901458;
      pplStack_38 = (longlong **)0xffffffffffffffff;
      uStack_30._0_4_ = (int)roomType;
      lVar5 = FUN_7ffe9b5439f0(&uStack_40,0);
      if (plVar7 != (longlong *)0x0) {
        if ((lVar5 != 0) &&
           (lVar8 = func_0x7ffe9996c920(lVar5,*(undefined8 *)(*plVar7 + 0x40)), lVar8 == 0)) {
          uVar6 = func_0x7ffe9996d1f0();
          FUN_7ffe9996d760(uVar6,0);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        if ((int)plVar7[3] != 0) {
          plVar7[4] = lVar5;
          il2cpp_write_barrier_0();
          abStackX_10[0] = abStackX_18[0];
          lVar5 = func_0x7ffe9996c8e0(_DAT_7ffe9c94c948,abStackX_10);
          if ((lVar5 != 0) &&
             (lVar8 = func_0x7ffe9996c920(lVar5,*(undefined8 *)(*plVar7 + 0x40)), lVar8 == 0)) {
            uVar6 = func_0x7ffe9996d1f0();
            FUN_7ffe9996d760(uVar6,0);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          if (1 < *(uint *)(plVar7 + 3)) {
            plVar7[5] = lVar5;
            il2cpp_write_barrier_0();
            func_0x7ffe999c3920(_DAT_7ffe9c94d6b8,plVar7,0);
            uVar6 = FUN_7ffe9bd98a10(self,0);
            *(undefined8 *)(self + 0x20) = uVar6;
            il2cpp_write_barrier_0();
            return;
          }
        }
        FUN_7ffe9996d790();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      FUN_7ffe9996d7a0();
LAB_7ffe9a88f870:
      FUN_7ffe9996d7a0();
LAB_7ffe9a88f876:
      FUN_7ffe9996d7a0();
LAB_7ffe9a88f87b:
      FUN_7ffe9996c950(plVar10);
LAB_7ffe9a88f883:
      FUN_7ffe9996d7a0();
    }
    else {
      lVar5 = FUN_7ffe9bd98a10(self,0);
      if (lVar5 == 0) goto LAB_7ffe9a88f83e;
      plStack_68 = (longlong *)FUN_7ffe9bdbde40(lVar5,0);
      pplStack_50 = &plStack_68;
      puStack_48 = auStack_60;
      uStack_40 = 0;
      pplStack_38 = pplStack_50;
      uStack_30 = puStack_48;
      while (plVar10 = plStack_68, plStack_68 != (longlong *)0x0) {
        lVar5 = *plStack_68;
        uVar11 = 0;
        if (*(ushort *)(lVar5 + 0x12e) != 0) {
          uVar3 = uVar11;
          do {
            if (*(longlong *)(*(longlong *)(lVar5 + 0xb0) + (ulonglong)uVar3 * 0x10) ==
                _DAT_7ffe9c93ac18) {
              puVar9 = (undefined8 *)
                       (lVar5 + 0x138 +
                       (longlong)*(int *)(*(longlong *)(lVar5 + 0xb0) + 8 + (ulonglong)uVar3 * 0x10)
                       * 0x10);
              goto LAB_7ffe9a88f6c9;
            }
            uVar3 = uVar3 + 1;
          } while (uVar3 < *(ushort *)(lVar5 + 0x12e));
        }
        puVar9 = (undefined8 *)FUN_7ffe998ce540(plStack_68,_DAT_7ffe9c93ac18,0);
LAB_7ffe9a88f6c9:
        cVar2 = (*(code *)*puVar9)(plVar10,puVar9[1]);
        plVar10 = plStack_68;
        if (cVar2 == '\0') {
          FUN_7ffe99b9cad0(&pplStack_38);
          if (*(longlong *)(self + 0x20) != 0) {
            lVar5 = FUN_7ffe9bd98960(*(longlong *)(self + 0x20),0);
            if (lVar5 != 0) {
              FUN_7ffe9bd9b390(lVar5,1,0);
              return;
            }
          }
          goto LAB_7ffe9a88f83e;
        }
        if (plStack_68 == (longlong *)0x0) goto LAB_7ffe9a88f883;
        lVar5 = *plStack_68;
        if (*(ushort *)(lVar5 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar5 + 0xb0) + (ulonglong)uVar11 * 0x10) ==
                _DAT_7ffe9c93ac18) {
              puVar9 = (undefined8 *)
                       (lVar5 + 0x138 +
                       (longlong)
                       (*(int *)(*(longlong *)(lVar5 + 0xb0) + 8 + (ulonglong)uVar11 * 0x10) + 1) *
                       0x10);
              goto LAB_7ffe9a88f738;
            }
            uVar11 = uVar11 + 1;
          } while (uVar11 < *(ushort *)(lVar5 + 0x12e));
        }
        puVar9 = (undefined8 *)FUN_7ffe998ce540(plStack_68,_DAT_7ffe9c93ac18,1);
LAB_7ffe9a88f738:
        plVar10 = (longlong *)(*(code *)*puVar9)(plVar10,puVar9[1]);
        if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a88f870;
        if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c96ad18 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar10 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c96ad18 + 0x130) * 8) != _DAT_7ffe9c96ad18))
        goto LAB_7ffe9a88f87b;
        lVar5 = FUN_7ffe9bd98960(plVar10,0);
        if (lVar5 == 0) goto LAB_7ffe9a88f876;
        FUN_7ffe9bd9b390(lVar5,0);
      }
    }
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
LAB_7ffe9a88f83e:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

