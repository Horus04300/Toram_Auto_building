
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void OldSong_SkillSongBufferDataBase__ctor
               (undefined *thisObject,byte lv,byte self,int notice_song_buff_lv,
               undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong *plVar5;
  undefined *puVar6;
  undefined7 in_register_00000011;
  undefined7 in_register_00000081;
  undefined4 uVar7;
  float fVar8;
  float fVar9;
  
  *(undefined4 *)(thisObject + 0x28) = 0x3f800000;
  *(undefined4 *)(thisObject + 0x50) = 0xffffffff;
  thisObject[0x58] = 1;
  FUN_7ffe9a77f020(thisObject,CONCAT71(in_register_00000011,lv),CONCAT71(in_register_00000081,self),
                   10,0);
  thisObject[0x68] = 1;
  *(int *)(thisObject + 0x2c) = notice_song_buff_lv;
  *(int *)(thisObject + 0x20) = notice_song_buff_lv;
  uVar7 = (**(code **)(*(longlong *)thisObject + 0x318))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 800));
  *(undefined4 *)(thisObject + 0x38) = uVar7;
  uVar7 = (**(code **)(*(longlong *)thisObject + 0x308))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x310));
  fVar9 = *(float *)(thisObject + 0x38);
  *(undefined4 *)(thisObject + 0x54) = uVar7;
  fVar8 = (float)(**(code **)(*(longlong *)thisObject + 0x308))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x310));
  if (fVar9 <= fVar8) {
    fVar9 = *(float *)(thisObject + 0x38);
  }
  else if (thisObject[0x60] == '\0') {
    fVar9 = *(float *)(thisObject + 0x54);
  }
  else {
    fVar9 = *(float *)(thisObject + 0x38) + _DAT_7ffe9c049b18;
  }
  *(float *)(thisObject + 0x14) = fVar9;
  lVar3 = FUN_7ffe9a47bac0(0);
  if (lVar3 != 0) {
    uVar4 = FUN_7ffe9a47fe30(lVar3,0);
    *(undefined8 *)(thisObject + 0x40) = uVar4;
    il2cpp_write_barrier_0();
    if (*(longlong *)(thisObject + 0x40) != 0) {
      *(undefined8 *)(thisObject + 0x48) = *(undefined8 *)(*(longlong *)(thisObject + 0x40) + 0x58);
      il2cpp_write_barrier_0();
      plVar5 = *(longlong **)(thisObject + 0x40);
      *(undefined4 *)(thisObject + 0x24) = 10;
      if (plVar5 != (longlong *)0x0) {
        plVar5 = (longlong *)(**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0))
        ;
        if (plVar5 != (longlong *)0x0) {
          puVar6 = (undefined *)
                   (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220));
          if (puVar6 != (undefined *)0x0) {
            puVar6 = GemCartBufferManager_GetGemCartBuffer(puVar6,0x2e,(undefined *)0x0);
            if (puVar6 != (undefined *)0x0) {
              iVar2 = GemCartBufferBase_GetValue(puVar6,(undefined *)0x2,(undefined *)0x0);
              *(int *)(thisObject + 0x5c) = iVar2;
            }
            return;
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

