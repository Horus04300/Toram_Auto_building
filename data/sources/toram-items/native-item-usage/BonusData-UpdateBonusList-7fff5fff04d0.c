
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusData_UpdateBonusList(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  uint uVar2;
  longlong lVar3;
  longlong lVar4;
  code *pcVar5;
  int iVar6;
  undefined *puVar7;
  longlong lVar8;
  undefined8 uVar9;
  longlong *plVar10;
  undefined8 *puVar11;
  ushort uVar12;
  int iVar14;
  ulonglong uVar13;
  
  if (DAT_7fff625e584c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450498);
    FUN_7fff5f47d450(&DAT_7fff624585a8);
    FUN_7fff5f47d450(&DAT_7fff62465d90);
    FUN_7fff5f47d450(&DAT_7fff62452178);
    FUN_7fff5f47d450(&DAT_7fff6240f5d0);
    FUN_7fff5f47d450(0x7fff62452238);
    FUN_7fff5f47d450(0x7fff6240f840);
    FUN_7fff5f47d450(0x7fff624526d0);
    FUN_7fff5f47d450(&DAT_7fff62452798);
    DAT_7fff625e584c = '\x01';
  }
  lVar8 = *(longlong *)(self + 0x20);
  if (lVar8 != 0) {
    iVar14 = *(int *)(lVar8 + 0x18);
    *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
    *(undefined4 *)(lVar8 + 0x18) = 0;
    if (0 < iVar14) {
      FUN_7fff61022d30(*(undefined8 *)(lVar8 + 0x10),0,iVar14,0);
    }
    lVar8 = *(longlong *)(self + 0x20);
    if ((*(undefined **)(self + 0x10) != (undefined *)0x0) &&
       (puVar7 = BonusScriptData_get_Bonus(*(undefined **)(self + 0x10),(undefined *)0x0),
       lVar8 != 0)) {
      func_0x7fff60adf9c0(lVar8,puVar7,_DAT_7fff62452178);
      lVar8 = *(longlong *)(self + 0x30);
      if (lVar8 != 0) {
        iVar14 = *(int *)(lVar8 + 0x18);
        *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
        *(undefined4 *)(lVar8 + 0x18) = 0;
        if (0 < iVar14) {
          FUN_7fff61022d30(*(undefined8 *)(lVar8 + 0x10),0,iVar14,0);
        }
        puVar7 = *(undefined **)(self + 0x10);
        iVar14 = 0;
        if (puVar7 != (undefined *)0x0) {
          while (puVar7 = BonusScriptData_get_Buff(puVar7,(undefined *)0x0),
                puVar7 != (undefined *)0x0) {
            if (*(int *)(puVar7 + 0x18) <= iVar14) {
              lVar8 = *(longlong *)(self + 0x38);
              if (lVar8 != 0) {
                iVar14 = *(int *)(lVar8 + 0x18);
                *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
                *(undefined4 *)(lVar8 + 0x18) = 0;
                if (0 < iVar14) {
                  FUN_7fff61022d30(*(undefined8 *)(lVar8 + 0x10),0,iVar14,0);
                }
                puVar7 = *(undefined **)(self + 0x10);
                iVar14 = 0;
                if (puVar7 != (undefined *)0x0) goto LAB_7fff5fff0781;
              }
              break;
            }
            if (((*(undefined **)(self + 0x10) == (undefined *)0x0) ||
                (puVar7 = BonusScriptData_get_Buff(*(undefined **)(self + 0x10),(undefined *)0x0),
                puVar7 == (undefined *)0x0)) ||
               (lVar8 = FUN_7fff60a94f50(puVar7,iVar14,_DAT_7fff62452798), lVar8 == 0)) break;
            uVar1 = *(undefined4 *)(lVar8 + 0x10);
            if (((*(undefined **)(self + 0x10) == (undefined *)0x0) ||
                (puVar7 = BonusScriptData_get_Buff(*(undefined **)(self + 0x10),(undefined *)0x0),
                puVar7 == (undefined *)0x0)) ||
               (lVar8 = FUN_7fff60a94f50(puVar7,iVar14,_DAT_7fff62452798), lVar8 == 0)) break;
            uVar2 = *(uint *)(lVar8 + 0x14);
            uVar9 = func_0x7fff5f44ff00(_DAT_7fff62450498);
            FUN_7fff605f3160(uVar9,uVar1,uVar2 & 0xffff);
            lVar4 = _DAT_7fff6240f5d0;
            lVar8 = *(longlong *)(self + 0x30);
            if (lVar8 == 0) break;
            *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
            lVar3 = *(longlong *)(lVar8 + 0x10);
            uVar2 = *(uint *)(lVar8 + 0x18);
            if (lVar3 == 0) break;
            if (uVar2 < *(uint *)(lVar3 + 0x18)) {
              *(uint *)(lVar8 + 0x18) = uVar2 + 1;
              if (*(uint *)(lVar3 + 0x18) <= uVar2) goto LAB_7fff5fff0a2d;
              *(undefined8 *)(lVar3 + 0x20 + (longlong)(int)uVar2 * 8) = uVar9;
              thunk_FUN_7fff5f491fd0();
            }
            else {
              FUN_7fff60adfc70(lVar8,uVar9,
                               *(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
            }
            puVar7 = *(undefined **)(self + 0x10);
            iVar14 = iVar14 + 1;
            if (puVar7 == (undefined *)0x0) break;
          }
        }
      }
    }
  }
LAB_7fff5fff0a27:
  FUN_7fff5f47d660();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
LAB_7fff5fff0781:
  plVar10 = (longlong *)BonusScriptData_get_Debuff(puVar7,(undefined *)0x0);
  if (plVar10 == (longlong *)0x0) goto LAB_7fff5fff0a27;
  lVar8 = *plVar10;
  uVar13 = 0;
  if (*(ushort *)(lVar8 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + uVar13 * 0x10) == _DAT_7fff624585a8) {
        puVar11 = (undefined8 *)
                  (lVar8 + 0x138 +
                  (longlong)*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + uVar13 * 0x10) * 0x10);
        goto LAB_7fff5fff07e6;
      }
      uVar12 = (short)uVar13 + 1;
      uVar13 = (ulonglong)uVar12;
    } while (uVar12 < *(ushort *)(lVar8 + 0x12e));
  }
  puVar11 = (undefined8 *)FUN_7fff5f3de400(plVar10,_DAT_7fff624585a8,0);
LAB_7fff5fff07e6:
  iVar6 = (*(code *)*puVar11)(plVar10);
  if (iVar6 <= iVar14) {
    return;
  }
  if ((*(undefined **)(self + 0x10) == (undefined *)0x0) ||
     (plVar10 = (longlong *)
                BonusScriptData_get_Debuff(*(undefined **)(self + 0x10),(undefined *)0x0),
     plVar10 == (longlong *)0x0)) goto LAB_7fff5fff0a27;
  lVar8 = *plVar10;
  uVar13 = 0;
  if (*(ushort *)(lVar8 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + uVar13 * 0x10) == _DAT_7fff62465d90) {
        puVar11 = (undefined8 *)
                  (lVar8 + 0x138 +
                  (longlong)*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + uVar13 * 0x10) * 0x10);
        goto LAB_7fff5fff0866;
      }
      uVar12 = (short)uVar13 + 1;
      uVar13 = (ulonglong)uVar12;
    } while (uVar12 < *(ushort *)(lVar8 + 0x12e));
  }
  puVar11 = (undefined8 *)FUN_7fff5f3de400(plVar10,_DAT_7fff62465d90,0);
LAB_7fff5fff0866:
  lVar8 = (*(code *)*puVar11)(plVar10,iVar14,puVar11[1]);
  if (lVar8 == 0) goto LAB_7fff5fff0a27;
  uVar1 = *(undefined4 *)(lVar8 + 0x10);
  if ((*(undefined **)(self + 0x10) == (undefined *)0x0) ||
     (plVar10 = (longlong *)
                BonusScriptData_get_Debuff(*(undefined **)(self + 0x10),(undefined *)0x0),
     plVar10 == (longlong *)0x0)) goto LAB_7fff5fff0a27;
  lVar8 = *plVar10;
  uVar13 = 0;
  if (*(ushort *)(lVar8 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + uVar13 * 0x10) == _DAT_7fff62465d90) {
        puVar11 = (undefined8 *)
                  (lVar8 + 0x138 +
                  (longlong)*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + uVar13 * 0x10) * 0x10);
        goto LAB_7fff5fff08f6;
      }
      uVar12 = (short)uVar13 + 1;
      uVar13 = (ulonglong)uVar12;
    } while (uVar12 < *(ushort *)(lVar8 + 0x12e));
  }
  puVar11 = (undefined8 *)FUN_7fff5f3de400(plVar10,_DAT_7fff62465d90,0);
LAB_7fff5fff08f6:
  lVar8 = (*(code *)*puVar11)(plVar10,iVar14,puVar11[1]);
  if (lVar8 == 0) goto LAB_7fff5fff0a27;
  uVar2 = *(uint *)(lVar8 + 0x14);
  uVar9 = func_0x7fff5f44ff00(_DAT_7fff62450498);
  FUN_7fff605f3160(uVar9,uVar1,uVar2 & 0xffff,0);
  lVar8 = *(longlong *)(self + 0x38);
  if (lVar8 == 0) goto LAB_7fff5fff0a27;
  *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
  lVar4 = *(longlong *)(lVar8 + 0x10);
  uVar2 = *(uint *)(lVar8 + 0x18);
  if (lVar4 == 0) goto LAB_7fff5fff0a27;
  if (uVar2 < *(uint *)(lVar4 + 0x18)) {
    *(uint *)(lVar8 + 0x18) = uVar2 + 1;
    if (*(uint *)(lVar4 + 0x18) <= uVar2) {
LAB_7fff5fff0a2d:
      FUN_7fff5f47d650();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    *(undefined8 *)(lVar4 + 0x20 + (longlong)(int)uVar2 * 8) = uVar9;
    thunk_FUN_7fff5f491fd0();
  }
  else {
    FUN_7fff60adfc70();
  }
  puVar7 = *(undefined **)(self + 0x10);
  iVar14 = iVar14 + 1;
  if (puVar7 == (undefined *)0x0) goto LAB_7fff5fff0a27;
  goto LAB_7fff5fff0781;
}

