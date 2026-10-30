
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void NormalAttackAction_calcRampageFinish
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  longlong lVar3;
  char cVar4;
  byte bVar5;
  undefined1 uVar6;
  int iVar7;
  undefined4 uVar8;
  longlong *plVar9;
  longlong lVar10;
  undefined *puVar11;
  undefined8 uVar12;
  longlong lVar13;
  uint uVar14;
  longlong *plStackX_10;
  undefined *puStackX_18;
  undefined8 uStack_78;
  undefined8 *puStack_70;
  longlong lStack_68;
  undefined8 uStack_60;
  undefined8 *puStack_58;
  longlong lStack_50;
  
  puStackX_18 = mobAction;
  if (DAT_7ffe9cadde96 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c904a08);
    FUN_7ffe9996d590(&DAT_7ffe9c904ad8);
    FUN_7ffe9996d590(0x7ffe9c904ba8);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c953798);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9539f8);
    FUN_7ffe9996d590(&DAT_7ffe9c9536c8);
    FUN_7ffe9996d590(&DAT_7ffe9c972930);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    DAT_7ffe9cadde96 = '\x01';
  }
  plStackX_10 = (longlong *)0x0;
  uStack_60 = 0;
  puStack_58 = (undefined8 *)0x0;
  lStack_50 = 0;
  if ((((playerAction != (undefined *)0x0) &&
       (plVar9 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
       plVar9 != (longlong *)0x0)) &&
      (lVar10 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)), lVar10 != 0
      )) && (*(longlong *)(lVar10 + 0x40) != 0)) {
    cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x40),0x29,&plStackX_10);
    if (cVar4 == '\0') {
      return;
    }
    if (plStackX_10 != (longlong *)0x0) {
      if (*(char *)((longlong)plStackX_10 + 0x1c) == '\0') {
        return;
      }
      iVar7 = (**(code **)(*plStackX_10 + 0x1f8))
                        (plStackX_10,0x32,*(undefined8 *)(*plStackX_10 + 0x200));
      plVar9 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar9 != (longlong *)0x0) &&
         (puVar11 = (undefined *)
                    (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220)),
         puVar11 != (undefined *)0x0)) {
        bVar5 = GemCartBufferManager_ContainsBuffer(puVar11,0x12e,(undefined *)0x0);
        if (bVar5 != 0) {
          return;
        }
        if (iVar7 != 1) {
          return;
        }
        plVar9 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (plVar9 != (longlong *)0x0) {
          lVar10 = (**(code **)(*plVar9 + 0x1a8))(plVar9,*(undefined8 *)(*plVar9 + 0x1b0));
          uVar12 = func_0x7ffe99940040(_DAT_7ffe9c972930);
          FUN_7ffe9af8a010(uVar12,_DAT_7ffe9c9536c8);
          *(undefined8 *)(thisObject + 0x110) = uVar12;
          il2cpp_write_barrier_0();
          puVar11 = (undefined *)0x1;
          do {
            NormalAttackAction_calcRampageSkillRate
                      (thisObject,playerAction,puVar11,(undefined *)0x0);
            NormalAttackAction_calcRampageConstantDamage(thisObject,playerAction,(undefined *)0x0);
            if (lVar10 == 0) goto LAB_7ffe9a49cc09;
            uVar8 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,lVar10);
            uVar6 = FUN_7ffe9a4b33f0(thisObject,uVar8,puStackX_18,0);
            uVar12 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
            FUN_7ffe9a6596c0(uVar12,0);
            uVar8 = (**(code **)(*(longlong *)thisObject + 0x198))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
            lVar13 = FUN_7ffe9a4b07c0(thisObject,uVar12,playerAction,puStackX_18,uVar8,1,
                                      *(undefined4 *)(thisObject + 0x18c),uVar6,1,0);
            if (lVar13 == 0) goto LAB_7ffe9a49cc09;
            FUN_7ffe9a657c40(lVar13,0x12);
            FUN_7ffe9a657a50(lVar13,8);
            cVar4 = FUN_7ffe9a658020(lVar13,3);
            if (cVar4 != '\0') {
              lVar13 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
              FUN_7ffe9a6596c0(lVar13,0);
              if (lVar13 == 0) goto LAB_7ffe9a49cc09;
              FUN_7ffe9a658f90(lVar13,0,1);
              FUN_7ffe9a658f90(lVar13,3,1);
            }
            if (*(longlong *)(thisObject + 0x110) == 0) goto LAB_7ffe9a49cc09;
            FUN_7ffe99743100(*(longlong *)(thisObject + 0x110),lVar13,_DAT_7ffe9c953798);
            uVar14 = (int)puVar11 + 1;
            puVar11 = (undefined *)(ulonglong)uVar14;
          } while ((int)uVar14 < 4);
          uVar12 = func_0x7ffe99940040(_DAT_7ffe9c920098);
          puVar11 = puStackX_18;
          FUN_7ffe9a8f6350(uVar12,puStackX_18,0);
          lVar10 = FUN_7ffe9a4b3a80(thisObject,uVar12,*(undefined8 *)(thisObject + 0x110),0);
          if (puVar11 != (undefined *)0x0) {
            cVar4 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,puVar11);
            if (cVar4 == '\0') {
              if (lVar10 == 0) goto LAB_7ffe9a49cc09;
              lVar13 = *(longlong *)(lVar10 + 0x38);
              if (*(longlong *)(thisObject + 0x110) == 0) goto LAB_7ffe9a49cc09;
              FUN_7ffe9af836a0(&uStack_78,*(longlong *)(thisObject + 0x110),_DAT_7ffe9c9539f8);
              uStack_60 = uStack_78;
              puStack_58 = puStack_70;
              lStack_50 = lStack_68;
              uStack_78 = 0;
              puStack_70 = &uStack_60;
              while (cVar4 = FUN_7ffe9ae28ed0(&uStack_60,_DAT_7ffe9c904ad8), cVar4 != '\0') {
                if (lVar13 == 0) goto LAB_7ffe9a49cc15;
                if (lStack_50 == 0) goto LAB_7ffe9a49cc0f;
                cVar4 = FUN_7ffe9a658020(lStack_50,3);
                if (cVar4 != '\0') {
                  *(undefined4 *)(lVar13 + 0x18) = 1;
                }
                lVar13 = *(longlong *)(lVar13 + 0x28);
              }
              func_0x7ffe999c3920(&uStack_60,_DAT_7ffe9c904a08);
            }
            lVar3 = _DAT_7ffe9c913488;
            lVar13 = *(longlong *)(thisObject + 0x80);
            if (lVar13 != 0) {
              *(int *)(lVar13 + 0x1c) = *(int *)(lVar13 + 0x1c) + 1;
              lVar1 = *(longlong *)(lVar13 + 0x10);
              uVar14 = *(uint *)(lVar13 + 0x18);
              if (lVar1 != 0) {
                if (*(uint *)(lVar1 + 0x18) <= uVar14) {
                  FUN_7ffe9afd58b0(lVar13,lVar10,
                                   *(undefined8 *)
                                    (*(longlong *)(*(longlong *)(lVar3 + 0x20) + 0xc0) + 0x70));
                  return;
                }
                *(uint *)(lVar13 + 0x18) = uVar14 + 1;
                if (uVar14 < *(uint *)(lVar1 + 0x18)) {
                  *(longlong *)(lVar1 + ((longlong)(int)uVar14 + 4) * 8) = lVar10;
                  il2cpp_write_barrier_0();
                  return;
                }
                FUN_7ffe9996d790();
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a49cc09:
  FUN_7ffe9996d7a0();
LAB_7ffe9a49cc0f:
  FUN_7ffe9996d7a0();
LAB_7ffe9a49cc15:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

