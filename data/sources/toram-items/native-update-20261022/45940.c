
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte StageLoginDownloader__initResourceDownload_d__14_MoveNext
               (undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  byte bVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uVar9;
  uint uVar10;
  
  if (DAT_7ffe9cad9d15 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c95aca8);
    FUN_7ffe9996d590(&DAT_7ffe9c95b308);
    FUN_7ffe9996d590(&DAT_7ffe9c95a978);
    FUN_7ffe9996d590(&DAT_7ffe9c973be0);
    FUN_7ffe9996d590(&DAT_7ffe9c902c70);
    FUN_7ffe9996d590(&DAT_7ffe9c91acd0);
    FUN_7ffe9996d590(&DAT_7ffe9c91ada0);
    FUN_7ffe9996d590(&DAT_7ffe9c928ae0);
    FUN_7ffe9996d590(&DAT_7ffe9c928a18);
    FUN_7ffe9996d590(&DAT_7ffe9c900228);
    FUN_7ffe9996d590(&DAT_7ffe9c919738);
    DAT_7ffe9cad9d15 = '\x01';
  }
  lVar1 = *(longlong *)(self + 0x20);
  if (*(int *)(self + 0x10) != 0) {
    if (*(int *)(self + 0x10) == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99a42703;
      if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\0') {
        if (lVar1 == 0) goto LAB_7ffe99a42703;
        *(undefined1 *)(lVar1 + 0x30) = 1;
        func_0x7ffe999c3920(_DAT_7ffe9c919738,0);
      }
    }
    return 0;
  }
  *(undefined4 *)(self + 0x10) = 0xffffffff;
  uVar5 = func_0x7ffe99940040(_DAT_7ffe9c928ae0);
  func_0x7ffe999c3920(uVar5,0);
  *(undefined8 *)(self + 0x28) = uVar5;
  il2cpp_write_barrier_0();
  func_0x7ffe999c3920(_DAT_7ffe9c900228,0);
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c973be0);
  FUN_7ffe9af8a010(lVar6,_DAT_7ffe9c95a978);
  if (lVar1 != 0) {
    lVar2 = *(longlong *)(lVar1 + 0x60);
    uVar10 = 0;
    if (lVar2 != 0) {
      for (; (int)uVar10 < *(int *)(lVar2 + 0x18); uVar10 = uVar10 + 1) {
        if (*(uint *)(lVar2 + 0x18) <= uVar10) {
          FUN_7ffe9996d790();
          pcVar3 = (code *)swi(3);
          bVar4 = (*pcVar3)();
          return bVar4;
        }
        if (*(longlong *)(lVar1 + 0x50) == 0) goto LAB_7ffe99a42703;
        lVar7 = FUN_7ffe99ace9b0(*(longlong *)(lVar1 + 0x50),
                                 *(undefined8 *)(lVar2 + 0x20 + (longlong)(int)uVar10 * 8),0);
        if (*(int *)(_DAT_7ffe9c928a18 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c928a18 + 0xb8) + 8);
        if (lVar8 == 0) {
          if (*(int *)(_DAT_7ffe9c928a18 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          uVar5 = **(undefined8 **)(_DAT_7ffe9c928a18 + 0xb8);
          lVar8 = func_0x7ffe99940040(_DAT_7ffe9c902c70);
          FUN_7ffe9b0cf900(lVar8,uVar5,_DAT_7ffe9c91acd0);
          *(longlong *)(*(longlong *)(_DAT_7ffe9c928a18 + 0xb8) + 8) = lVar8;
          il2cpp_write_barrier_0();
        }
        if ((lVar7 == 0) || (FUN_7ffe9afdb7a0(lVar7,lVar8,_DAT_7ffe9c95b308), lVar6 == 0))
        goto LAB_7ffe99a42703;
        func_0x7ffe9afd5600(lVar6,lVar7);
      }
      if (*(longlong *)(self + 0x28) != 0) {
        *(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 0;
        if (*(longlong *)(lVar1 + 0x50) != 0) {
          FUN_7ffe99ace640(*(longlong *)(lVar1 + 0x50),lVar6,0);
          lVar6 = *(longlong *)(lVar1 + 0x50);
          uVar5 = *(undefined8 *)(self + 0x28);
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
          FUN_7ffe9ac2ed50(uVar9,uVar5,_DAT_7ffe9c91ada0,0);
          if (lVar6 != 0) {
            uVar5 = FUN_7ffe99ad1450(lVar6,uVar9,0);
            uVar5 = FUN_7ffe9bd9f640(lVar1,uVar5,0);
            *(undefined8 *)(self + 0x18) = uVar5;
            il2cpp_write_barrier_0();
            *(undefined4 *)(self + 0x10) = 1;
            return 1;
          }
        }
      }
    }
  }
LAB_7ffe99a42703:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  bVar4 = (*pcVar3)();
  return bVar4;
}

