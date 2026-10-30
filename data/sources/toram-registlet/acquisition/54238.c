
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UITreasureHuntEnterManager_GetDropItemName
          (undefined *self,undefined *type,int rewardValue,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  longlong *plVar4;
  undefined *puVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  int iVar8;
  undefined2 auStackX_10 [4];
  undefined4 auStack_28 [4];
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (DAT_7ffe9cadab90 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90af60);
    FUN_7ffe9996d590(&DAT_7ffe9c954178);
    FUN_7ffe9996d590(&DAT_7ffe9c953a40);
    FUN_7ffe9996d590(&DAT_7ffe9c953710);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c94c6f0);
    FUN_7ffe9996d590(&DAT_7ffe9c944598);
    FUN_7ffe9996d590(&DAT_7ffe9c9651f8);
    FUN_7ffe9996d590(&DAT_7ffe9c909ae8);
    DAT_7ffe9cadab90 = '\x01';
  }
  iVar8 = (int)type;
  if (iVar8 < 9) {
    if (iVar8 != 0) {
      if (iVar8 == 8) {
        puVar5 = (undefined *)FUN_7ffe9a15cc50(rewardValue,*(undefined8 *)(self + 0x20),0);
        return puVar5;
      }
      goto LAB_7ffe99c713b6;
    }
    lVar3 = *(longlong *)(self + 0x20);
    auStack_28[0] = 1;
    uVar7 = FUN_7ffe9b5043c0(auStack_28,0);
    uVar6 = _DAT_7ffe9c944598;
LAB_7ffe99c71367:
    uVar6 = FUN_7ffe9b3675b0(uVar6,uVar7,0);
    if (lVar3 != 0) {
LAB_7ffe99c7137b:
      puVar5 = (undefined *)FUN_7ffe99a58320(lVar3,uVar6,0);
      return puVar5;
    }
  }
  else {
    if (iVar8 == 0x17) {
      lVar3 = FUN_7ffe9b141840(_DAT_7ffe9c953a40);
      if (lVar3 == 0) goto LAB_7ffe99c714a6;
      lVar3 = FUN_7ffe9a5b4af0(lVar3,rewardValue & 0xffff,0);
      if (lVar3 == 0) goto LAB_7ffe99c7128d;
      plVar4 = *(longlong **)(self + 0x1f8);
      rewardValue = (int)*(short *)(lVar3 + 0x10);
      if (plVar4 == (longlong *)0x0) goto LAB_7ffe99c714a6;
      lVar3 = func_0x7ffe9996d210(*(undefined8 *)
                                   (*plVar4 +
                                   ((ulonglong)*(ushort *)(_DAT_7ffe9c954178 + 0x50) + 0x14) * 0x10)
                                 );
    }
    else {
      if (iVar8 == 0x18) {
        lVar3 = *(longlong *)(self + 0x20);
        uVar6 = _DAT_7ffe9c94c6f0;
        if (lVar3 == 0) goto LAB_7ffe99c714a6;
        goto LAB_7ffe99c7137b;
      }
LAB_7ffe99c713b6:
      lVar3 = FUN_7ffe9b141840(_DAT_7ffe9c953710);
      if (lVar3 == 0) goto LAB_7ffe99c714a6;
      lVar3 = FUN_7ffe9a57a320(lVar3,rewardValue,0);
      if (lVar3 == 0) {
LAB_7ffe99c7128d:
        return (undefined *)**(undefined8 **)(_DAT_7ffe9c9590b8 + 0xb8);
      }
      cVar2 = func_0x7ffe9a2782b0((int)*(short *)(lVar3 + 0x30),0);
      if (cVar2 != '\0') {
        plVar4 = *(longlong **)(self + 0x108);
        if (plVar4 == (longlong *)0x0) goto LAB_7ffe99c714a6;
        uStack_18 = _DAT_7ffe9c049be0;
        uStack_14 = _UNK_7ffe9c049be4;
        uStack_10 = _UNK_7ffe9c049be8;
        uStack_c = _UNK_7ffe9c049bec;
        (**(code **)(*plVar4 + 0x1a8))
                  (plVar4,_DAT_7ffe9c909ae8,&uStack_18,*(undefined8 *)(*plVar4 + 0x1b0));
      }
      cVar2 = func_0x7ffe9a2782a0((int)*(short *)(lVar3 + 0x30),0);
      if ((cVar2 != '\0') ||
         (cVar2 = func_0x7ffe9a278280((int)*(short *)(lVar3 + 0x30),0), cVar2 != '\0')) {
        auStackX_10[0] = *(undefined2 *)(lVar3 + 0x30);
        lVar3 = *(longlong *)(self + 0x20);
        uVar7 = FUN_7ffe9b503430(auStackX_10,0);
        uVar6 = _DAT_7ffe9c9651f8;
        goto LAB_7ffe99c71367;
      }
      plVar4 = *(longlong **)(self + 0x1b8);
      if (plVar4 == (longlong *)0x0) goto LAB_7ffe99c714a6;
      lVar3 = func_0x7ffe9996d210(*(undefined8 *)
                                   (*plVar4 +
                                   ((ulonglong)*(ushort *)(_DAT_7ffe9c90af60 + 0x50) + 0x14) * 0x10)
                                 );
    }
    plVar4 = (longlong *)(**(code **)(lVar3 + 8))(plVar4,rewardValue,lVar3);
    if (plVar4 != (longlong *)0x0) {
      puVar5 = (undefined *)(**(code **)(*plVar4 + 0x188))(plVar4,*(undefined8 *)(*plVar4 + 400));
      return puVar5;
    }
  }
LAB_7ffe99c714a6:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar5 = (undefined *)(*pcVar1)();
  return puVar5;
}

