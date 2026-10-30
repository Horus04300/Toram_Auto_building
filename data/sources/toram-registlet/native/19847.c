
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferManager_UpdateEquipGemCartData
               (undefined *self,short id,short updateLv,undefined *methodInfo)

{
  short id_00;
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined *puVar7;
  undefined8 uVar8;
  longlong lVar9;
  longlong *plVar10;
  undefined8 uStack_28;
  undefined8 uStack_20;
  
  if (DAT_7ffe9cade796 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9654b8);
    FUN_7ffe9996d590(&DAT_7ffe9c965650);
    FUN_7ffe9996d590(&DAT_7ffe9c9657e8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f88f8);
    FUN_7ffe9996d590(&DAT_7ffe9c907f28);
    FUN_7ffe9996d590(&DAT_7ffe9c93b270);
    FUN_7ffe9996d590(&DAT_7ffe9c9375f8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c9462a0);
    FUN_7ffe9996d590(&DAT_7ffe9c946368);
    FUN_7ffe9996d590(&DAT_7ffe9c9465b0);
    FUN_7ffe9996d590(&DAT_7ffe9c946678);
    FUN_7ffe9996d590(&DAT_7ffe9c956ac0);
    FUN_7ffe9996d590(&DAT_7ffe9c956928);
    DAT_7ffe9cade796 = '\x01';
  }
  uStack_20 = 0;
  uStack_28 = 0;
  lVar5 = func_0x7ffe99940040(_DAT_7ffe9c956ac0);
  func_0x7ffe999c3920(lVar5,0);
  if (lVar5 != 0) {
    *(short *)(lVar5 + 0x10) = id;
    if (*(longlong *)(self + 0x18) != 0) {
      cVar3 = FUN_7ffe9ad11000(*(longlong *)(self + 0x18),id,_DAT_7ffe9c965650);
      if (cVar3 != '\0') {
        if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b3e6a;
        FUN_7ffe9ad161b0(*(longlong *)(self + 0x18),*(undefined2 *)(lVar5 + 0x10),_DAT_7ffe9c9657e8)
        ;
      }
      id_00 = *(short *)(lVar5 + 0x10);
      if (*(longlong *)(self + 0x10) == 0) {
        puVar7 = (undefined *)0x0;
      }
      else {
        plVar6 = (longlong *)FUN_7ffe9a47fe30(*(longlong *)(self + 0x10),0);
        if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a5b3e6a;
        puVar7 = (undefined *)
                 (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
      }
      plVar6 = (longlong *)GemCartBufferFactory_Create(id_00,updateLv,puVar7,(undefined *)0x0);
      if (plVar6 != (longlong *)0x0) {
        if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b3e6a;
        FUN_7ffe9ad10e30(*(longlong *)(self + 0x18),*(undefined2 *)(lVar5 + 0x10),plVar6);
        uVar1 = *(undefined8 *)(self + 0x10);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar3 = FUN_7ffe9bda2160(uVar1,0,0);
        if (cVar3 != '\0') {
          uVar1 = *(undefined8 *)(self + 0x20);
          uVar8 = func_0x7ffe99940040(_DAT_7ffe9c93b270);
          FUN_7ffe9af155b0(uVar8,lVar5,_DAT_7ffe9c9465b0);
          cVar3 = FUN_7ffe9ab7a900(uVar1,uVar8,_DAT_7ffe9c8f88f8);
          if (cVar3 != '\0') {
            if ((*(longlong *)(self + 0x10) == 0) ||
               (lVar9 = *(longlong *)(*(longlong *)(self + 0x10) + 0x70), lVar9 == 0))
            goto LAB_7ffe9a5b3e6a;
            uVar1 = *(undefined8 *)(lVar9 + 0x10);
            if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            lVar9 = *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x20);
            if (lVar9 == 0) {
              if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              uVar8 = **(undefined8 **)(_DAT_7ffe9c956928 + 0xb8);
              lVar9 = func_0x7ffe99940040(_DAT_7ffe9c9375f8);
              FUN_7ffe9af13420(lVar9,uVar8,_DAT_7ffe9c9462a0);
              *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x20) = lVar9;
              il2cpp_write_barrier_0();
            }
            lVar9 = FUN_7ffe9ab854c0(uVar1,lVar9,_DAT_7ffe9c907f28);
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar3 = FUN_7ffe9bda2160(lVar9,0,0);
            if (cVar3 != '\0') {
              if (lVar9 == 0) goto LAB_7ffe9a5b3e6a;
              plVar10 = (longlong *)FUN_7ffe9a4ca6d0(lVar9,0);
              if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a5b3e6a;
              plVar10 = (longlong *)
                        (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
              if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a5b3e6a;
              puVar7 = (undefined *)
                       (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220));
              if (puVar7 == (undefined *)0x0) goto LAB_7ffe9a5b3e6a;
              GemCartBufferManager_UpdateEquipGemCartData
                        (puVar7,*(short *)(lVar5 + 0x10),updateLv,(undefined *)0x0);
            }
          }
          uVar1 = *(undefined8 *)(self + 0x28);
          uVar8 = func_0x7ffe99940040(_DAT_7ffe9c93b270);
          FUN_7ffe9af155b0(uVar8,lVar5,_DAT_7ffe9c946678);
          cVar3 = FUN_7ffe9ab7a900(uVar1,uVar8,_DAT_7ffe9c8f88f8);
          if (cVar3 != '\0') {
            if ((*(longlong *)(self + 0x10) == 0) ||
               (lVar9 = *(longlong *)(*(longlong *)(self + 0x10) + 0x70), lVar9 == 0))
            goto LAB_7ffe9a5b3e6a;
            uVar1 = *(undefined8 *)(lVar9 + 0x10);
            if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            lVar9 = *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x28);
            if (lVar9 == 0) {
              if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              uVar8 = **(undefined8 **)(_DAT_7ffe9c956928 + 0xb8);
              lVar9 = func_0x7ffe99940040(_DAT_7ffe9c9375f8);
              FUN_7ffe9af13420(lVar9,uVar8,_DAT_7ffe9c946368);
              *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x28) = lVar9;
              il2cpp_write_barrier_0();
            }
            lVar9 = FUN_7ffe9ab854c0(uVar1,lVar9,_DAT_7ffe9c907f28);
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar3 = FUN_7ffe9bda2160(lVar9,0,0);
            if (cVar3 != '\0') {
              if (lVar9 == 0) goto LAB_7ffe9a5b3e6a;
              plVar10 = (longlong *)FUN_7ffe9a4ca6d0(lVar9,0);
              if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a5b3e6a;
              plVar10 = (longlong *)
                        (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
              if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a5b3e6a;
              puVar7 = (undefined *)
                       (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220));
              if (puVar7 == (undefined *)0x0) goto LAB_7ffe9a5b3e6a;
              GemCartBufferManager_UpdateEquipGemCartData
                        (puVar7,*(short *)(lVar5 + 0x10),updateLv,(undefined *)0x0);
            }
          }
        }
        cVar3 = (**(code **)(*plVar6 + 0x1a8))
                          (plVar6,&uStack_20,&uStack_28,*(undefined8 *)(*plVar6 + 0x1b0));
        if (cVar3 != '\0') {
          uVar1 = *(undefined8 *)(self + 0x10);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar3 = FUN_7ffe9bda2160(uVar1,0,0);
          if (cVar3 != '\0') {
            if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a5b3e6a;
            lVar9 = FUN_7ffe9a47f190(*(longlong *)(self + 0x10),0);
            if (lVar9 == 0) goto LAB_7ffe9a5b3e6a;
            FUN_7ffe9a4ed2c0(lVar9,*(undefined2 *)(lVar5 + 0x10),uStack_20,uStack_28,0);
          }
        }
        iVar4 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180));
        if (iVar4 == 0x3ef) {
          lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
          if (lVar5 == 0) goto LAB_7ffe9a5b3e6a;
          FUN_7ffe9a29adb0(lVar5,0);
        }
      }
      return;
    }
  }
LAB_7ffe9a5b3e6a:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

