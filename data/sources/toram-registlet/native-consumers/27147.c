
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PowerShootAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  float fVar1;
  uint uVar2;
  longlong lVar3;
  longlong lVar4;
  code *pcVar5;
  longlong lVar6;
  char cVar7;
  undefined1 uVar8;
  char cVar9;
  undefined4 uVar10;
  int iVar11;
  longlong *plVar12;
  longlong lVar13;
  undefined8 uVar14;
  undefined *puVar15;
  undefined4 uVar16;
  float afStackX_8 [2];
  undefined8 in_stack_ffffffffffffffa8;
  undefined8 in_stack_ffffffffffffffb0;
  undefined4 uVar17;
  ulonglong in_stack_ffffffffffffffb8;
  
  uVar16 = (undefined4)((ulonglong)in_stack_ffffffffffffffa8 >> 0x20);
  uVar17 = (undefined4)((ulonglong)in_stack_ffffffffffffffb0 >> 0x20);
  if (DAT_7ffe9cadf28e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    DAT_7ffe9cadf28e = '\x01';
  }
  uVar10 = FUN_7ffe9a4adee0(thisObject,playerAction,mobAction,0);
  *(undefined4 *)(thisObject + 0x30) = uVar10;
  if (playerAction != (undefined *)0x0) {
    plVar12 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar12 != (longlong *)0x0) {
      lVar13 = (**(code **)(*plVar12 + 0x1a8))(plVar12,*(undefined8 *)(*plVar12 + 0x1b0));
      if (lVar13 != 0) {
        iVar11 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,lVar13);
        if (mobAction != (undefined *)0x0) {
          lVar13 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
          if (lVar13 != 0) {
            cVar7 = FUN_7ffe9a4daa60(lVar13,0xb);
            if (cVar7 != '\0') {
              iVar11 = iVar11 + *(int *)(thisObject + 300);
            }
            uVar8 = FUN_7ffe9a4b33f0(thisObject,iVar11,mobAction,0);
            uVar14 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
            FUN_7ffe9a6596c0(uVar14,0);
            uVar10 = (**(code **)(*(longlong *)thisObject + 0x198))
                               (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
            if (*(longlong *)(thisObject + 0xb8) != 0) {
              lVar13 = FUN_7ffe9a4b1c10(thisObject,uVar14,playerAction,mobAction,
                                        CONCAT44(uVar16,uVar10),
                                        CONCAT44(uVar17,*(undefined4 *)
                                                         (*(longlong *)(thisObject + 0xb8) + 0x1c)),
                                        in_stack_ffffffffffffffb8 & 0xffffffff00000000,uVar8,0);
              cVar7 = '\0';
              afStackX_8[0] = 0.0;
              if (lVar13 != 0) {
                cVar9 = FUN_7ffe9a658020(lVar13,0,0);
                if (cVar9 != '\0') {
                  cVar7 = FUN_7ffe9a4b2fb0(thisObject,2,*(undefined4 *)(thisObject + 0x128),
                                           playerAction,mobAction,afStackX_8,0);
                  if (cVar7 != '\0') {
                    plVar12 = (longlong *)
                              (**(code **)(*(longlong *)playerAction + 0x298))
                                        (playerAction,
                                         *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                    if (plVar12 == (longlong *)0x0) goto LAB_7ffe9a75d7c8;
                    puVar15 = (undefined *)
                              (**(code **)(*plVar12 + 0x218))
                                        (plVar12,*(undefined8 *)(*plVar12 + 0x220));
                    if (puVar15 == (undefined *)0x0) goto LAB_7ffe9a75d7c8;
                    puVar15 = GemCartBufferManager_GetGemCartBuffer(puVar15,0x67,(undefined *)0x0);
                    if (puVar15 != (undefined *)0x0) {
                      fVar1 = *(float *)(thisObject + 0x120);
                      iVar11 = GemCartBufferBase_GetValue(puVar15,(undefined *)0x4,(undefined *)0x0)
                      ;
                      *(float *)(thisObject + 0x120) = (float)iVar11 + fVar1;
                    }
                  }
                }
                FUN_7ffe9a657c40(lVar13,0x12,*(float *)(thisObject + 0x120) / _DAT_7ffe9c049cfc);
                FUN_7ffe9a657a50(lVar13,8);
                uVar14 = func_0x7ffe99940040(_DAT_7ffe9c920098);
                FUN_7ffe9a8f6350(uVar14,mobAction,0);
                lVar13 = FUN_7ffe9a4b4370(thisObject,uVar14,lVar13,1,0);
                if (cVar7 != '\0') {
                  if ((lVar13 == 0) || (*(longlong *)(lVar13 + 0x38) == 0)) goto LAB_7ffe9a75d7c8;
                  *(undefined4 *)(*(longlong *)(lVar13 + 0x38) + 0x8c) = 2;
                  lVar3 = *(longlong *)(lVar13 + 0x38);
                  if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
                    func_0x7ffe9996d830();
                  }
                  uVar16 = FUN_7ffe9a4db1f0(2);
                  if (lVar3 == 0) goto LAB_7ffe9a75d7c8;
                  *(undefined4 *)(lVar3 + 0x98) = uVar16;
                  lVar3 = *(longlong *)(lVar13 + 0x38);
                  if (lVar3 == 0) goto LAB_7ffe9a75d7c8;
                  *(float *)(lVar3 + 0x9c) = afStackX_8[0] + *(float *)(lVar3 + 0x9c);
                }
                lVar6 = _DAT_7ffe9c913488;
                lVar3 = *(longlong *)(thisObject + 0x80);
                if (lVar3 != 0) {
                  *(int *)(lVar3 + 0x1c) = *(int *)(lVar3 + 0x1c) + 1;
                  lVar4 = *(longlong *)(lVar3 + 0x10);
                  uVar2 = *(uint *)(lVar3 + 0x18);
                  if (lVar4 != 0) {
                    if (uVar2 < *(uint *)(lVar4 + 0x18)) {
                      *(uint *)(lVar3 + 0x18) = uVar2 + 1;
                      if (*(uint *)(lVar4 + 0x18) <= uVar2) {
                        FUN_7ffe9996d790();
                        pcVar5 = (code *)swi(3);
                        (*pcVar5)();
                        return;
                      }
                      *(longlong *)(lVar4 + 0x20 + (longlong)(int)uVar2 * 8) = lVar13;
                      il2cpp_write_barrier_0();
                    }
                    else {
                      FUN_7ffe9afd58b0(lVar3,lVar13,
                                       *(undefined8 *)
                                        (*(longlong *)(*(longlong *)(lVar6 + 0x20) + 0xc0) + 0x70));
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
LAB_7ffe9a75d7c8:
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

