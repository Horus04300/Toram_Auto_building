
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void OldSong_SkillSongBufferDataBase_songbuff_lvup(undefined *thisObject,undefined *methodInfo)

{
  float fVar1;
  code *pcVar2;
  int iVar3;
  longlong *plVar4;
  undefined *puVar5;
  float fVar6;
  
  if (9 < *(int *)(thisObject + 0x2c)) {
    *(undefined4 *)(thisObject + 0x30) = 0;
    return;
  }
  fVar1 = *(float *)(thisObject + 0x30);
  fVar6 = (float)(**(code **)(*(longlong *)thisObject + 0x2f8))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x300));
  if (fVar1 <= fVar6) {
    return;
  }
  fVar1 = *(float *)(thisObject + 0x30);
  fVar6 = (float)(**(code **)(*(longlong *)thisObject + 0x2f8))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x300));
  *(int *)(thisObject + 0x2c) = *(int *)(thisObject + 0x2c) + 1;
  plVar4 = *(longlong **)(thisObject + 0x40);
  *(undefined4 *)(thisObject + 0x20) = *(undefined4 *)(thisObject + 0x2c);
  *(float *)(thisObject + 0x30) = fVar1 - fVar6;
  if (((plVar4 != (longlong *)0x0) &&
      (plVar4 = (longlong *)(**(code **)(*plVar4 + 0x298))(plVar4,*(undefined8 *)(*plVar4 + 0x2a0)),
      plVar4 != (longlong *)0x0)) &&
     (puVar5 = (undefined *)(**(code **)(*plVar4 + 0x218))(plVar4,*(undefined8 *)(*plVar4 + 0x220)),
     puVar5 != (undefined *)0x0)) {
    puVar5 = GemCartBufferManager_GetGemCartBuffer(puVar5,0x2e,(undefined *)0x0);
    if (puVar5 == (undefined *)0x0) {
      *(undefined4 *)(thisObject + 0x5c) = 0;
      return;
    }
    iVar3 = GemCartBufferBase_GetValue(puVar5,(undefined *)0x2,(undefined *)0x0);
    *(int *)(thisObject + 0x5c) = iVar3;
    return;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

