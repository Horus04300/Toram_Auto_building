
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * GemCartBufferManager_GetTalentElementType(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  ushort uVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined8 *puVar10;
  longlong *plVar11;
  undefined *puVar12;
  ushort uVar13;
  longlong *plVar14;
  
  if (DAT_7ffe9cade79e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c965a48);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc928);
    FUN_7ffe9996d590(&DAT_7ffe9c927ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac50);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c954770);
    FUN_7ffe9996d590(&DAT_7ffe9c95a0a0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c9448f8);
    FUN_7ffe9996d590(&DAT_7ffe9c946058);
    FUN_7ffe9996d590(&DAT_7ffe9c956928);
    DAT_7ffe9cade79e = '\x01';
  }
  bVar5 = 0xff;
  if (*(longlong *)(self + 0x18) != 0) {
    uVar7 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x18),_DAT_7ffe9c965a48);
    if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x30);
    if (lVar8 == 0) {
      if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar1 = **(undefined8 **)(_DAT_7ffe9c956928 + 0xb8);
      lVar8 = func_0x7ffe99940040(_DAT_7ffe9c93ac50);
      FUN_7ffe9af13420(lVar8,uVar1,_DAT_7ffe9c946058,0);
      *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x30) = lVar8;
      il2cpp_write_barrier_0();
    }
    uVar7 = FUN_7ffe9ab93080(uVar7,lVar8,_DAT_7ffe9c927ad0);
    lVar8 = FUN_7ffe9ab7b880(uVar7,_DAT_7ffe9c8fc928);
    if (lVar8 != 0) {
      plVar9 = (longlong *)FUN_7ffe99742ec0(0,_DAT_7ffe9c954770,lVar8);
      plVar14 = (longlong *)0x0;
      while (plVar9 != (longlong *)0x0) {
        cVar3 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
        if (cVar3 == '\0') {
          if (plVar9 != (longlong *)0x0) {
            FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
          }
          if (plVar14 == (longlong *)0x0) {
            return (undefined *)0x0;
          }
          puVar12 = (undefined *)FUN_7ffe99742ec0(2,_DAT_7ffe9c9448f8,plVar14);
          return puVar12;
        }
        if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a5b3127;
        lVar8 = *plVar9;
        uVar6 = 0;
        if (*(ushort *)(lVar8 + 0x12e) != 0) {
          uVar13 = uVar6;
          do {
            if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + (ulonglong)uVar13 * 0x10) ==
                _DAT_7ffe9c95a0a0) {
              puVar10 = (undefined8 *)
                        (lVar8 + 0x138 +
                        (longlong)
                        *(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + (ulonglong)uVar13 * 0x10) * 0x10)
              ;
              goto LAB_7ffe9a5b2fb9;
            }
            uVar13 = uVar13 + 1;
          } while (uVar13 < *(ushort *)(lVar8 + 0x12e));
        }
        puVar10 = (undefined8 *)FUN_7ffe998ce540(plVar9,_DAT_7ffe9c95a0a0,0);
LAB_7ffe9a5b2fb9:
        plVar11 = (longlong *)(*(code *)*puVar10)(plVar9,puVar10[1]);
        if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a5b3121;
        lVar8 = *plVar11;
        if (*(ushort *)(lVar8 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + (ulonglong)uVar6 * 0x10) ==
                _DAT_7ffe9c9448f8) {
              puVar10 = (undefined8 *)
                        (lVar8 + 0x138 +
                        (longlong)
                        (*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + (ulonglong)uVar6 * 0x10) + 1) *
                        0x10);
              goto LAB_7ffe9a5b301c;
            }
            uVar6 = uVar6 + 1;
          } while (uVar6 < *(ushort *)(lVar8 + 0x12e));
        }
        puVar10 = (undefined8 *)FUN_7ffe998ce540(plVar11,_DAT_7ffe9c9448f8,1);
LAB_7ffe9a5b301c:
        bVar4 = (*(code *)*puVar10)(plVar11,puVar10[1]);
        if (bVar4 < bVar5) {
          bVar5 = FUN_7ffe99742ec0(1,_DAT_7ffe9c9448f8,plVar11);
          plVar14 = plVar11;
        }
      }
      goto LAB_7ffe9a5b312c;
    }
  }
  FUN_7ffe9996d7a0();
LAB_7ffe9a5b3121:
  FUN_7ffe9996d7a0();
LAB_7ffe9a5b3127:
  FUN_7ffe9996d7a0();
LAB_7ffe9a5b312c:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar2 = (code *)swi(3);
  puVar12 = (undefined *)(*pcVar2)();
  return puVar12;
}

