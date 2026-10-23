
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidRoomData_RoomSynchronization
               (undefined *self,undefined *syncEvent,undefined *methodInfo)

{
  byte bVar1;
  longlong *plVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  uint uVar7;
  undefined4 uVar8;
  
  if (DAT_7fff625e5fd9 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242bb10);
    FUN_7fff5f47d450(&DAT_7fff62458e78);
    FUN_7fff5f47d450(&DAT_7fff6246a1a8);
    DAT_7fff625e5fd9 = '\x01';
  }
  lVar6 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
  if (lVar6 != 0) {
    iVar5 = FUN_7fff6037cb10(lVar6,0);
    if (iVar5 == 0x1d) {
      if (syncEvent == (undefined *)0x0) goto LAB_7fff600e0c94;
      plVar2 = *(longlong **)(syncEvent + 0x30);
      if (plVar2 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7fff6242bb10 + 0x130) <= *(byte *)(*plVar2 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*plVar2 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff6242bb10 + 0x130) * 8) == _DAT_7fff6242bb10)) {
          *(longlong *)(self + 0x70) = plVar2[5];
          thunk_FUN_7fff5f491fd0();
          *(ushort *)(self + 0xb2) = (ushort)*(byte *)(plVar2 + 6);
          bVar1 = *(byte *)((longlong)plVar2 + 0x39);
          *(ushort *)(self + 0xb4) = (ushort)bVar1;
          uVar7 = (uint)bVar1 << 2;
          if (uVar7 < 0x28) {
            uVar7 = 0x28;
          }
          *(uint *)(self + 0xac) = uVar7;
          *(ushort *)(self + 0xb6) = (ushort)*(byte *)((longlong)plVar2 + 0x31);
          GuildRaidRoomData_CheckItemUseProhibited(self,(undefined *)0x0);
          self[0xc1] = (char)plVar2[7];
          *(float *)(self + 0x90) = (float)*(int *)((longlong)plVar2 + 0x34);
          lVar6 = FUN_7fff60c66630(_DAT_7fff6246a1a8);
          if (lVar6 == 0) goto LAB_7fff600e0c94;
          cVar4 = FUN_7fff5fe487d0(lVar6,0);
          if (cVar4 != '\0') {
            uVar8 = FUN_7fff618b0f20(0);
            *(undefined4 *)(self + 0x94) = uVar8;
          }
        }
      }
    }
    return;
  }
LAB_7fff600e0c94:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

