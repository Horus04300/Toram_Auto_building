
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
  if (DAT_7fff625e726c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62454290);
    FUN_7fff5f47d450(&DAT_7fff62408f18);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff624606c8);
    FUN_7fff5f47d450(&DAT_7fff62472258);
    FUN_7fff5f47d450(0x7fff62425d08);
    FUN_7fff5f47d450(0x7fff62425858);
    FUN_7fff5f47d450(0x7fff6247b988);
    FUN_7fff5f47d450(0x7fff62446d00);
    FUN_7fff5f47d450(0x7fff623f67e0);
    FUN_7fff5f47d450(0x7fff62427158);
    FUN_7fff5f47d450(0x7fff62455b08);
    FUN_7fff5f47d450(0x7fff623fd588);
    FUN_7fff5f47d450(0x7fff62454e08);
    FUN_7fff5f47d450(0x7fff62401f28);
    FUN_7fff5f47d450(0x7fff623f7dd0);
    FUN_7fff5f47d450(0x7fff624519b0);
    FUN_7fff5f47d450(0x7fff6243b4d8);
    FUN_7fff5f47d450(0x7fff62446c38);
    FUN_7fff5f47d450(0x7fff62429228);
    FUN_7fff5f47d450(0x7fff6242ae48);
    FUN_7fff5f47d450(0x7fff624547e8);
    FUN_7fff5f47d450(0x7fff624248b8);
    FUN_7fff5f47d450(0x7fff624284e0);
    FUN_7fff5f47d450(0x7fff62425790);
    FUN_7fff5f47d450(0x7fff623f7d80);
    FUN_7fff5f47d450(0x7fff624247f0);
    FUN_7fff5f47d450(0x7fff6244b1a0);
    FUN_7fff5f47d450(&DAT_7fff62453da0);
    DAT_7fff625e726c = '\x01';
  }
  auStack_60[0] = 0;
  uVar6 = **(undefined8 **)(_DAT_7fff624606c8 + 0xb8);
  switch((int)roomType) {
  case 0:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff62425858;
    break;
  case 1:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff62454e08;
    break;
  case 2:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff62425d08;
    break;
  case 3:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff62427158;
    break;
  default:
    goto LAB_7fff6039993c;
  case 5:
  case 0x1e:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff623f7dd0;
    break;
  case 7:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff6247b988;
    break;
  case 10:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff624284e0;
    break;
  case 0xc:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff624248b8;
    break;
  case 0xd:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff624247f0;
    break;
  case 0xe:
  case 0x23:
  case 0x27:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff62446c38;
    break;
  case 0x10:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff623f67e0;
    break;
  case 0x13:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff624519b0;
    break;
  case 0x16:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff6244b1a0;
    break;
  case 0x17:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff62425790;
    break;
  case 0x19:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff62446d00;
    break;
  case 0x1a:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff6242ae48;
    break;
  case 0x1b:
    uVar6 = uRam00007fff62455b08;
    goto LAB_7fff6039993c;
  case 0x1c:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff623fd588;
    break;
  case 0x1d:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff623f7d80;
    break;
  case 0x22:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff6243b4d8;
    break;
  case 0x25:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff62401f28;
    break;
  case 0x28:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff624547e8;
    break;
  case 0x29:
    uVar4 = FUN_7fff60f8f420(abStackX_18,0);
    uVar6 = uRam00007fff62429228;
  }
  uVar6 = FUN_7fff60e71970(uVar6,uVar4,0);
LAB_7fff6039993c:
  lVar5 = FUN_7fff618a1b90(self,0);
  if (lVar5 != 0) {
    uVar6 = FUN_7fff618c6ee0(lVar5,uVar6,0);
    *(undefined8 *)(self + 0x20) = uVar6;
    thunk_FUN_7fff5f491fd0();
    uVar6 = *(undefined8 *)(self + 0x20);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    plVar10 = (longlong *)0x0;
    cVar2 = FUN_7fff618ab2e0(uVar6,0,0);
    if (cVar2 == '\0') {
      plVar7 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,2);
      uStack_40 = _DAT_7fff62408f18;
      pplStack_38 = (longlong **)0xffffffffffffffff;
      uStack_30._0_4_ = (int)roomType;
      lVar5 = FUN_7fff6104ddb0(&uStack_40,0);
      if (plVar7 != (longlong *)0x0) {
        if ((lVar5 != 0) &&
           (lVar8 = func_0x7fff5f47c7e0(lVar5,*(undefined8 *)(*plVar7 + 0x40)), lVar8 == 0)) {
          uVar6 = func_0x7fff5f47d0b0();
          FUN_7fff5f47d620(uVar6,0);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        if ((int)plVar7[3] != 0) {
          plVar7[4] = lVar5;
          thunk_FUN_7fff5f491fd0();
          abStackX_10[0] = abStackX_18[0];
          lVar5 = func_0x7fff5f47c7a0(_DAT_7fff62454290,abStackX_10);
          if ((lVar5 != 0) &&
             (lVar8 = func_0x7fff5f47c7e0(lVar5,*(undefined8 *)(*plVar7 + 0x40)), lVar8 == 0)) {
            uVar6 = func_0x7fff5f47d0b0();
            FUN_7fff5f47d620(uVar6,0);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          if (1 < *(uint *)(plVar7 + 3)) {
            plVar7[5] = lVar5;
            thunk_FUN_7fff5f491fd0();
            func_0x7fff5f4d3920(_DAT_7fff62453da0,plVar7,0);
            uVar6 = FUN_7fff618a1b90(self,0);
            *(undefined8 *)(self + 0x20) = uVar6;
            thunk_FUN_7fff5f491fd0();
            return;
          }
        }
        FUN_7fff5f47d650();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      FUN_7fff5f47d660();
LAB_7fff60399d00:
      FUN_7fff5f47d660();
LAB_7fff60399d06:
      FUN_7fff5f47d660();
LAB_7fff60399d0b:
      FUN_7fff5f47c810(plVar10);
LAB_7fff60399d13:
      FUN_7fff5f47d660();
    }
    else {
      lVar5 = FUN_7fff618a1b90(self,0);
      if (lVar5 == 0) goto LAB_7fff60399cce;
      plStack_68 = (longlong *)FUN_7fff618c6fc0(lVar5,0);
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
                _DAT_7fff62442498) {
              puVar9 = (undefined8 *)
                       (lVar5 + 0x138 +
                       (longlong)*(int *)(*(longlong *)(lVar5 + 0xb0) + 8 + (ulonglong)uVar3 * 0x10)
                       * 0x10);
              goto LAB_7fff60399b59;
            }
            uVar3 = uVar3 + 1;
          } while (uVar3 < *(ushort *)(lVar5 + 0x12e));
        }
        puVar9 = (undefined8 *)FUN_7fff5f3de400(plStack_68,_DAT_7fff62442498,0);
LAB_7fff60399b59:
        cVar2 = (*(code *)*puVar9)(plVar10,puVar9[1]);
        plVar10 = plStack_68;
        if (cVar2 == '\0') {
          FUN_7fff5f6ac790(&pplStack_38);
          if (*(longlong *)(self + 0x20) != 0) {
            lVar5 = FUN_7fff618a1ae0(*(longlong *)(self + 0x20),0);
            if (lVar5 != 0) {
              FUN_7fff618a4510(lVar5,1,0);
              return;
            }
          }
          goto LAB_7fff60399cce;
        }
        if (plStack_68 == (longlong *)0x0) goto LAB_7fff60399d13;
        lVar5 = *plStack_68;
        if (*(ushort *)(lVar5 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar5 + 0xb0) + (ulonglong)uVar11 * 0x10) ==
                _DAT_7fff62442498) {
              puVar9 = (undefined8 *)
                       (lVar5 + 0x138 +
                       (longlong)
                       (*(int *)(*(longlong *)(lVar5 + 0xb0) + 8 + (ulonglong)uVar11 * 0x10) + 1) *
                       0x10);
              goto LAB_7fff60399bc8;
            }
            uVar11 = uVar11 + 1;
          } while (uVar11 < *(ushort *)(lVar5 + 0x12e));
        }
        puVar9 = (undefined8 *)FUN_7fff5f3de400(plStack_68,_DAT_7fff62442498,1);
LAB_7fff60399bc8:
        plVar10 = (longlong *)(*(code *)*puVar9)(plVar10,puVar9[1]);
        if (plVar10 == (longlong *)0x0) goto LAB_7fff60399d00;
        if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7fff62472258 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar10 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff62472258 + 0x130) * 8) != _DAT_7fff62472258))
        goto LAB_7fff60399d0b;
        lVar5 = FUN_7fff618a1ae0(plVar10,0);
        if (lVar5 == 0) goto LAB_7fff60399d06;
        FUN_7fff618a4510(lVar5,0);
      }
    }
    FUN_7fff5f47d660();
    FUN_7fff5f40a410();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
LAB_7fff60399cce:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

