
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void StrikeBackOfSwordAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  float fVar1;
  uint uVar2;
  longlong lVar3;
  code *pcVar4;
  longlong lVar5;
  undefined1 uVar6;
  char cVar7;
  undefined4 uVar8;
  longlong *plVar9;
  longlong lVar10;
  undefined8 uVar11;
  longlong lVar12;
  undefined *puVar13;
  int iVar14;
  undefined4 uVar15;
  undefined4 auStackX_10 [2];
  undefined8 in_stack_ffffffffffffff98;
  undefined8 in_stack_ffffffffffffffa0;
  undefined4 uVar16;
  ulonglong in_stack_ffffffffffffffa8;
  
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffff98 >> 0x20);
  uVar16 = (undefined4)((ulonglong)in_stack_ffffffffffffffa0 >> 0x20);
  if (DAT_7ffe9cadf0ac == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    DAT_7ffe9cadf0ac = '\x01';
  }
  auStackX_10[0] = 0;
  if (playerAction != (undefined *)0x0) {
    plVar9 = (longlong *)
             (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar9 != (longlong *)0x0) {
      lVar10 = (**(code **)(*plVar9 + 0x1a8))(plVar9,*(undefined8 *)(*plVar9 + 0x1b0));
      if (lVar10 != 0) {
        uVar8 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,lVar10);
        uVar6 = FUN_7ffe9a4b33f0(thisObject,uVar8,mobAction,0);
        uVar11 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
        FUN_7ffe9a6596c0(uVar11,0);
        uVar8 = (**(code **)(*(longlong *)thisObject + 0x198))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
        if (*(longlong *)(thisObject + 0xb8) != 0) {
          lVar10 = FUN_7ffe9a4b1c10(thisObject,uVar11,playerAction,mobAction,CONCAT44(uVar15,uVar8),
                                    CONCAT44(uVar16,*(undefined4 *)
                                                     (*(longlong *)(thisObject + 0xb8) + 0x1c)),
                                    in_stack_ffffffffffffffa8 & 0xffffffff00000000,uVar6,0);
          if (lVar10 != 0) {
            FUN_7ffe9a657c40(lVar10,0x12);
            FUN_7ffe9a657a50(lVar10,8);
            uVar11 = func_0x7ffe99940040(_DAT_7ffe9c920098);
            FUN_7ffe9a8f6350(uVar11,mobAction,0);
            lVar10 = FUN_7ffe9a4b4370(thisObject,uVar11,lVar10,1,0);
            if (lVar10 != 0) {
              if ((*(int *)(lVar10 + 0x1c) != 0) && (*(int *)(lVar10 + 0x34) != 1)) {
                uVar15 = *(undefined4 *)(thisObject + 0x128);
                iVar14 = 6;
                if (mobAction == (undefined *)0x0) goto LAB_7ffe9a718211;
                lVar12 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
                if (lVar12 == 0) goto LAB_7ffe9a718211;
                cVar7 = FUN_7ffe9a4daa60(lVar12,6,0);
                if (cVar7 != '\0') {
                  uVar15 = *(undefined4 *)(thisObject + 300);
                  iVar14 = 3;
                }
                cVar7 = FUN_7ffe9a4b2fb0(thisObject,iVar14,uVar15,playerAction,mobAction,auStackX_10
                                         ,0);
                if (cVar7 != '\0') {
                  if (*(longlong *)(lVar10 + 0x38) == 0) goto LAB_7ffe9a718211;
                  FUN_7ffe9a8ffe30(*(longlong *)(lVar10 + 0x38),iVar14);
                  if (iVar14 == 6) {
                    plVar9 = (longlong *)
                             (**(code **)(*(longlong *)playerAction + 0x298))
                                       (playerAction,
                                        *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                    if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a718211;
                    puVar13 = (undefined *)
                              (**(code **)(*plVar9 + 0x218))
                                        (plVar9,*(undefined8 *)(*plVar9 + 0x220));
                    if (puVar13 == (undefined *)0x0) goto LAB_7ffe9a718211;
                    puVar13 = GemCartBufferManager_GetGemCartBuffer(puVar13,0x72,(undefined *)0x0);
                    if (puVar13 != (undefined *)0x0) {
                      lVar12 = *(longlong *)(lVar10 + 0x38);
                      if (lVar12 == 0) goto LAB_7ffe9a718211;
                      fVar1 = *(float *)(lVar12 + 0x94);
                      iVar14 = GemCartBufferBase_GetValue(puVar13,(undefined *)0x2,(undefined *)0x0)
                      ;
                      *(float *)(lVar12 + 0x94) = (float)iVar14 + fVar1;
                    }
                  }
                }
              }
              lVar5 = _DAT_7ffe9c913488;
              lVar12 = *(longlong *)(thisObject + 0x80);
              if (lVar12 != 0) {
                *(int *)(lVar12 + 0x1c) = *(int *)(lVar12 + 0x1c) + 1;
                lVar3 = *(longlong *)(lVar12 + 0x10);
                uVar2 = *(uint *)(lVar12 + 0x18);
                if (lVar3 != 0) {
                  if (uVar2 < *(uint *)(lVar3 + 0x18)) {
                    *(uint *)(lVar12 + 0x18) = uVar2 + 1;
                    if (*(uint *)(lVar3 + 0x18) <= uVar2) {
                      FUN_7ffe9996d790();
                      pcVar4 = (code *)swi(3);
                      (*pcVar4)();
                      return;
                    }
                    *(longlong *)(lVar3 + 0x20 + (longlong)(int)uVar2 * 8) = lVar10;
                    il2cpp_write_barrier_0();
                  }
                  else {
                    FUN_7ffe9afd58b0(lVar12,lVar10,
                                     *(undefined8 *)
                                      (*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
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
LAB_7ffe9a718211:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

