
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
  
  if (DAT_7ffe9cade882 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c924168);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    DAT_7ffe9cade882 = '\x01';
  }
  lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
  if (lVar6 != 0) {
    iVar5 = FUN_7ffe9a872680(lVar6,0);
    if (iVar5 == 0x1d) {
      if (syncEvent == (undefined *)0x0) goto LAB_7ffe9a5d6804;
      plVar2 = *(longlong **)(syncEvent + 0x30);
      if (plVar2 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c924168 + 0x130) <= *(byte *)(*plVar2 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*plVar2 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c924168 + 0x130) * 8) == _DAT_7ffe9c924168)) {
          *(longlong *)(self + 0x70) = plVar2[5];
          il2cpp_write_barrier_0();
          *(ushort *)(self + 0xb2) = (ushort)*(byte *)(plVar2 + 6);
          bVar1 = *(byte *)((longlong)plVar2 + 0x39);
          *(ushort *)(self + 0xb4) = (ushort)bVar1;
          uVar7 = (uint)bVar1 << 2;
          if (uVar7 < 0x28) {
            uVar7 = 0x28;
          }
          *(uint *)(self + 0xac) = uVar7;
          *(ushort *)(self + 0xb6) = (ushort)*(byte *)((longlong)plVar2 + 0x31);
          FUN_7ffe9a5d4d90(self,0);
          self[0xc1] = (char)plVar2[7];
          *(float *)(self + 0x90) = (float)*(int *)((longlong)plVar2 + 0x34);
          lVar6 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (lVar6 == 0) goto LAB_7ffe9a5d6804;
          cVar4 = FUN_7ffe9a33db00(lVar6,0);
          if (cVar4 != '\0') {
            uVar8 = FUN_7ffe9bda7da0(0);
            *(undefined4 *)(self + 0x94) = uVar8;
          }
        }
      }
    }
    return;
  }
LAB_7ffe9a5d6804:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

