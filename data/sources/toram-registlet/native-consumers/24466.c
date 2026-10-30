
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RageSwordAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  float fVar1;
  uint uVar2;
  longlong lVar3;
  code *pcVar4;
  longlong lVar5;
  char cVar6;
  undefined1 uVar7;
  int iVar8;
  undefined4 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  longlong *plVar12;
  undefined *puVar13;
  longlong lVar14;
  undefined8 in_stack_ffffffffffffffb8;
  undefined4 uVar15;
  
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffffb8 >> 0x20);
  if (DAT_7ffe9cadee19 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    DAT_7ffe9cadee19 = '\x01';
  }
  if (playerAction != (undefined *)0x0) {
    uVar10 = FUN_7ffe9bd98960(playerAction,0);
    if (mobAction != (undefined *)0x0) {
      uVar11 = FUN_7ffe99742ec0(0xd,_DAT_7ffe9c9724e0,mobAction);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar6 = FUN_7ffe9bda1fa0(uVar10,uVar11,0);
      if (cVar6 != '\0') {
        *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 1;
        thisObject[0x128] = 1;
      }
      plVar12 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (plVar12 != (longlong *)0x0) {
        puVar13 = (undefined *)
                  (**(code **)(*plVar12 + 0x218))(plVar12,*(undefined8 *)(*plVar12 + 0x220));
        if (puVar13 != (undefined *)0x0) {
          puVar13 = GemCartBufferManager_GetGemCartBuffer(puVar13,0x3fb,(undefined *)0x0);
          if (puVar13 != (undefined *)0x0) {
            fVar1 = *(float *)(thisObject + 0x120);
            iVar8 = GemCartBufferBase_GetValue(puVar13,(undefined *)0x4,(undefined *)0x0);
            *(float *)(thisObject + 0x120) = (float)iVar8 + fVar1;
          }
          plVar12 = (longlong *)
                    (**(code **)(*(longlong *)playerAction + 0x298))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          if (plVar12 != (longlong *)0x0) {
            lVar14 = (**(code **)(*plVar12 + 0x1a8))(plVar12,*(undefined8 *)(*plVar12 + 0x1b0));
            if (thisObject[0x128] == '\0') {
              if (lVar14 == 0) goto LAB_7ffe9a6aec23;
              uVar9 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,lVar14);
              uVar7 = FUN_7ffe9a4b33f0(thisObject,uVar9,mobAction,0);
            }
            else {
              uVar7 = 1;
            }
            uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
            FUN_7ffe9a6596c0(uVar10,0);
            uVar9 = (**(code **)(*(longlong *)thisObject + 0x198))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
            if (*(longlong *)(thisObject + 0xb8) != 0) {
              lVar14 = FUN_7ffe9a4b1c10(thisObject,uVar10,playerAction,mobAction,
                                        CONCAT44(uVar15,uVar9),
                                        *(undefined4 *)(*(longlong *)(thisObject + 0xb8) + 0x1c),0,
                                        uVar7,0);
              if (lVar14 != 0) {
                FUN_7ffe9a657c40(lVar14,0x12,*(float *)(thisObject + 0x120) / _DAT_7ffe9c049cfc);
                FUN_7ffe9a657a50(lVar14,8);
                uVar10 = func_0x7ffe99940040(_DAT_7ffe9c920098);
                FUN_7ffe9a8f6350(uVar10,mobAction,0);
                uVar10 = FUN_7ffe9a4b4370(thisObject,uVar10,lVar14,1,0);
                lVar5 = _DAT_7ffe9c913488;
                lVar14 = *(longlong *)(thisObject + 0x80);
                if (lVar14 != 0) {
                  *(int *)(lVar14 + 0x1c) = *(int *)(lVar14 + 0x1c) + 1;
                  lVar3 = *(longlong *)(lVar14 + 0x10);
                  uVar2 = *(uint *)(lVar14 + 0x18);
                  if (lVar3 != 0) {
                    if (uVar2 < *(uint *)(lVar3 + 0x18)) {
                      *(uint *)(lVar14 + 0x18) = uVar2 + 1;
                      if (*(uint *)(lVar3 + 0x18) <= uVar2) {
                        FUN_7ffe9996d790();
                        pcVar4 = (code *)swi(3);
                        (*pcVar4)();
                        return;
                      }
                      *(undefined8 *)(lVar3 + 0x20 + (longlong)(int)uVar2 * 8) = uVar10;
                      il2cpp_write_barrier_0();
                    }
                    else {
                      FUN_7ffe9afd58b0(lVar14,uVar10,
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
  }
LAB_7ffe9a6aec23:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

