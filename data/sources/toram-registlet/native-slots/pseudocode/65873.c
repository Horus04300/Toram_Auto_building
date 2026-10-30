
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIRegistletEditPanel_SetEquipList(undefined *self,undefined *methodInfo)

{
  int iVar1;
  byte bVar2;
  undefined4 uVar3;
  code *pcVar4;
  float fVar5;
  longlong lVar6;
  undefined *puVar7;
  undefined8 uVar8;
  longlong lVar9;
  undefined *puVar10;
  int iVar11;
  int iVar12;
  float fVar13;
  float fVar14;
  uint7 in_stack_ffffffffffffff69;
  undefined8 uStack_78;
  float fStack_70;
  float fStack_60;
  
  if (DAT_7ffe9cadc321 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c909038);
    FUN_7ffe9996d590(&DAT_7ffe9c9091d8);
    FUN_7ffe9996d590(&DAT_7ffe9c93b0e8);
    FUN_7ffe9996d590(&DAT_7ffe9c93ad18);
    FUN_7ffe9996d590(&DAT_7ffe9c931cb8);
    FUN_7ffe9996d590(&DAT_7ffe9c902c10);
    FUN_7ffe9996d590(&DAT_7ffe9c902ce0);
    FUN_7ffe9996d590(&DAT_7ffe9c8faf18);
    DAT_7ffe9cadc321 = '\x01';
  }
  if (*(longlong *)(self + 0x90) != 0) {
    func_0x7ffe9a2c4e50(*(longlong *)(self + 0x90),0);
    UIRegistletEditPanel_SetEnableEquipGemCartListWindow(self,1,(undefined *)0x0);
    if (*(longlong *)(self + 0xa0) != 0) {
      lVar6 = FUN_7ffe9a480320();
      if ((lVar6 != 0) && (*(undefined **)(lVar6 + 0x18) != (undefined *)0x0)) {
        puVar7 = GemCartBag_GetEquipGemCarts(*(undefined **)(lVar6 + 0x18),(undefined *)0x0);
        iVar12 = 0;
        if ((puVar7 != (undefined *)0x0) && (*(longlong *)(self + 0xa0) != 0)) {
          lVar6 = FUN_7ffe9a480320(*(longlong *)(self + 0xa0),0);
          fVar5 = _DAT_7ffe9c04a0b0;
          fVar14 = _DAT_7ffe9c049e80;
          if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x18) != 0)) {
            bVar2 = *(byte *)(*(longlong *)(lVar6 + 0x18) + 0x20);
            if (bVar2 != 0) {
              iVar11 = -1;
              do {
                lVar6 = func_0x7ffe99940040(_DAT_7ffe9c8faf18);
                func_0x7ffe999c3920(lVar6,0);
                puVar10 = (undefined *)0x0;
                if (lVar6 == 0) goto LAB_7ffe9a049fba;
                *(int *)(lVar6 + 0x10) = iVar11 + 2;
                uVar8 = func_0x7ffe99940040(_DAT_7ffe9c93b0e8);
                FUN_7ffe9af13420(uVar8,lVar6,_DAT_7ffe9c902c10,0);
                uVar8 = FUN_7ffe9ab854c0(puVar7,uVar8,_DAT_7ffe9c9091d8);
                *(undefined8 *)(lVar6 + 0x18) = uVar8;
                il2cpp_write_barrier_0();
                if (*(longlong *)(lVar6 + 0x18) != 0) {
                  if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a049fba;
                  lVar9 = FUN_7ffe9a480320();
                  if ((lVar9 == 0) || (*(undefined **)(lVar9 + 0x18) == (undefined *)0x0))
                  goto LAB_7ffe9a049fba;
                  puVar10 = GemCartBag_get_Bag(*(undefined **)(lVar9 + 0x18),(undefined *)0x0);
                  uVar8 = func_0x7ffe99940040(_DAT_7ffe9c93ad18);
                  FUN_7ffe9af13420(uVar8,lVar6,_DAT_7ffe9c902ce0,0);
                  puVar10 = (undefined *)FUN_7ffe9ab854c0(puVar10,uVar8,_DAT_7ffe9c909038);
                }
                if (DAT_7ffe9cad9cac == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                  DAT_7ffe9cad9cac = '\x01';
                }
                if (*(longlong *)(self + 0x68) == 0) goto LAB_7ffe9a049fba;
                uVar8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
                fVar13 = (float)iVar11 * fVar14;
                fStack_70 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20) * fVar13 +
                            0.0;
                uStack_78 = CONCAT44((float)((ulonglong)uVar8 >> 0x20) * fVar13 - fVar5,
                                     (float)uVar8 * fVar13 + 0.0);
                fStack_60 = fStack_70;
                puVar10 = UIRegistletEditPanel_CreateEquipGemButton
                                    (self,*(int *)(lVar6 + 0x10),(undefined *)&uStack_78,puVar10,
                                     (undefined *)((ulonglong)in_stack_ffffffffffffff69 << 8),
                                     (undefined *)0x0);
                if (*(longlong *)(self + 0x90) == 0) goto LAB_7ffe9a049fba;
                FUN_7ffe9a2c47a0(*(longlong *)(self + 0x90),puVar10,0);
                iVar12 = iVar12 + 1;
                iVar1 = iVar11 + 2;
                iVar11 = iVar11 + 1;
              } while (iVar1 < (int)(uint)bVar2);
            }
            if (*(longlong *)(self + 0xa0) != 0) {
              lVar6 = FUN_7ffe9a480320(*(longlong *)(self + 0xa0),0);
              if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x18) != 0)) {
                bVar2 = *(byte *)(*(longlong *)(lVar6 + 0x18) + 0x20);
                if (*(int *)(_DAT_7ffe9c931cb8 + 0xe0) == 0) {
                  func_0x7ffe9996d830(_DAT_7ffe9c931cb8);
                }
                if (bVar2 < *(byte *)(*(longlong *)(_DAT_7ffe9c931cb8 + 0xb8) + 4)) {
                  if (DAT_7ffe9cad9cac == '\0') {
                    FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                    DAT_7ffe9cad9cac = '\x01';
                  }
                  if (*(longlong *)(self + 0x68) == 0) goto LAB_7ffe9a049fba;
                  uVar8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
                  fVar14 = (float)(iVar12 + -1) * fVar14;
                  fStack_70 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20) * fVar14 +
                              0.0;
                  uStack_78 = CONCAT44((float)((ulonglong)uVar8 >> 0x20) * fVar14 - fVar5,
                                       (float)uVar8 * fVar14 + 0.0);
                  fStack_60 = fStack_70;
                  puVar7 = UIRegistletEditPanel_CreateEquipGemButton
                                     (self,-1,(undefined *)&uStack_78,(undefined *)0x0,
                                      (undefined *)CONCAT71(in_stack_ffffffffffffff69,1),
                                      (undefined *)0x0);
                  if (*(longlong *)(self + 0x90) == 0) goto LAB_7ffe9a049fba;
                  FUN_7ffe9a2c47a0(*(longlong *)(self + 0x90),puVar7,0);
                  iVar12 = iVar12 + 1;
                }
                lVar6 = *(longlong *)(self + 0x90);
                if (DAT_7ffe9cad9b47 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                  DAT_7ffe9cad9b47 = '\x01';
                }
                uVar8 = **(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8);
                uVar3 = *(undefined4 *)(*(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8) + 1);
                if (DAT_7ffe9cada1be == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c8fbb88);
                  DAT_7ffe9cada1be = '\x01';
                }
                if (*(longlong *)(self + 0x68) != 0) {
                  if (lVar6 != 0) {
                    uStack_78 = uVar8;
                    fStack_70 = (float)uVar3;
                    FUN_7ffe9a2c53f0(lVar6,&uStack_78,
                                     CONCAT44((float)(iVar12 + -1) *
                                              *(float *)(*(longlong *)(_DAT_7ffe9c8fbb88 + 0xb8) +
                                                        0x14) * _DAT_7ffe9c049cfc,
                                              (float)(iVar12 + -1) *
                                              *(float *)(*(longlong *)(_DAT_7ffe9c8fbb88 + 0xb8) +
                                                        0x10) * _DAT_7ffe9c049cfc),0);
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
LAB_7ffe9a049fba:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

