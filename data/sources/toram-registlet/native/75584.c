
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBuffer_HealStockpileBuff__ctor
               (undefined *self,short lv,undefined *status,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  uint uVar3;
  longlong lVar4;
  longlong *plVar5;
  uint uVar6;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadd3d8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90dea0);
    DAT_7ffe9cadd3d8 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  GemCartBufferBase__ctor(self,lv,(undefined *)0x0);
  *(undefined **)(self + 0x18) = status;
  il2cpp_write_barrier_0();
  if ((status != (undefined *)0x0) &&
     (lVar4 = (**(code **)(*(longlong *)status + 0x1c8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x1d0)), lVar4 != 0)) {
    cVar2 = FUN_7ffe9a7cbb30(lVar4,0x17,&plStackX_8);
    if (cVar2 == '\0') {
      return;
    }
    if (plStackX_8 != (longlong *)0x0) {
      uVar3 = (**(code **)(*plStackX_8 + 0x1f8))
                        (plStackX_8,0x14,*(undefined8 *)(*plStackX_8 + 0x200));
      lVar4 = (**(code **)(*(longlong *)status + 0x1c8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
      if (lVar4 != 0) {
        FUN_7ffe9a7cafa0(lVar4,0x17);
        uVar6 = (uint)*(short *)(self + 0x14);
        if ((int)uVar6 < (int)uVar3) {
          uVar3 = uVar6;
        }
        plVar5 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c90dea0);
        FUN_7ffe9a78d3c0(plVar5,uVar6 & 0xff,uVar3,status,0);
        plStackX_8 = plVar5;
        lVar4 = (**(code **)(*(longlong *)status + 0x1c8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
        if (lVar4 != 0) {
          FUN_7ffe9a7c26c0(lVar4,plStackX_8,0,0);
          return;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

