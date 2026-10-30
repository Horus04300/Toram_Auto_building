
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicArrowAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined8 uVar9;
  longlong *plVar10;
  undefined *puVar11;
  undefined8 uVar12;
  float fVar13;
  longlong lStackX_10;
  
  if (DAT_7ffe9cadee55 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c92d500);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadee55 = '\x01';
  }
  plVar10 = (longlong *)0x0;
  lStackX_10 = 0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    plVar10 = (longlong *)0x0;
    if (bVar2) {
      plVar10 = (longlong *)actarAction;
    }
  }
  lVar8 = FUN_7ffe9a47bac0(0);
  if ((lVar8 != 0) && (lVar8 = FUN_7ffe9a47f670(lVar8,0), lVar8 != 0)) {
    cVar3 = FUN_7ffe9ab94d80(lVar8,0x77,&lStackX_10,_DAT_7ffe9c92d500);
    if (cVar3 != '\0') {
      if (lStackX_10 == 0) goto LAB_7ffe9a6b614e;
      uVar4 = FUN_7ffe9a5212c0(lStackX_10,0x61);
      *(undefined2 *)(thisObject + 0x138) = uVar4;
    }
    if ((plVar10 != (longlong *)0x0) &&
       (lVar8 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
       lVar8 != 0)) {
      uVar5 = FUN_7ffe9a4a1cc0(lVar8,0);
      *(undefined4 *)(thisObject + 0x30) = uVar5;
      *(undefined4 *)(thisObject + 0xfc) = 0;
      cVar3 = FUN_7ffe9a4ad740(plVar10,0xe);
      if (cVar3 == '\0') {
        cVar3 = FUN_7ffe9a4ad740(plVar10,0xf);
        if (cVar3 != '\0') {
          *(undefined4 *)(thisObject + 0xfc) = 0xf;
        }
      }
      else {
        *(undefined4 *)(thisObject + 0xfc) = 0xe;
      }
      uVar5 = func_0x7ffe99a4d6a0();
      *(undefined4 *)(thisObject + 0x20) = uVar5;
      fVar13 = (float)(byte)thisObject[0x14] * _DAT_7ffe9c049b78 + _DAT_7ffe9c049cf8;
      *(float *)(thisObject + 0x124) = fVar13;
      if (*(int *)(thisObject + 0xfc) == 0xe) {
        *(float *)(thisObject + 0x124) = fVar13 + _DAT_7ffe9c049f04;
      }
      *(uint *)(thisObject + 0x128) = ((byte)thisObject[0x14] + 0x12) * 5;
      uVar9 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
      uVar5 = FUN_7ffe9a4a7fe0(thisObject,_DAT_7ffe9c049b70,uVar9,0);
      *(undefined4 *)(thisObject + 0x24) = uVar5;
      uVar9 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
      uVar5 = FUN_7ffe9a4aabb0(uVar9,0);
      *(undefined4 *)(thisObject + 0x78) = uVar5;
      FUN_7ffe9a4aacd0(thisObject,plVar10,0);
      iVar6 = (int)((byte)thisObject[0x14] - 1) / 2;
      *(int *)(thisObject + 0x120) = iVar6 + 2;
      if (*(int *)(thisObject + 0xfc) == 0xf) {
        *(int *)(thisObject + 0x120) = iVar6 + 4;
      }
      plVar10 = (longlong *)
                (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
      if ((plVar10 != (longlong *)0x0) &&
         (puVar11 = (undefined *)
                    (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220)),
         puVar11 != (undefined *)0x0)) {
        puVar11 = GemCartBufferManager_GetGemCartBuffer(puVar11,0x69,(undefined *)0x0);
        if (puVar11 != (undefined *)0x0) {
          iVar6 = *(int *)(thisObject + 0x120);
          iVar7 = GemCartBufferBase_GetValue(puVar11,(undefined *)0x2,(undefined *)0x0);
          *(int *)(thisObject + 0x120) = iVar7 + iVar6;
        }
        *(undefined4 *)(thisObject + 0x28) = *(undefined4 *)(thisObject + 0x120);
        if (*(int *)(thisObject + 0xfc) == 0xe) {
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          uVar12 = 610000;
        }
        else if (*(int *)(thisObject + 0xfc) == 0xf) {
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          uVar12 = 710000;
        }
        else {
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          uVar12 = 0x1d0d8;
        }
        FUN_7ffe9a9002e0(uVar9,uVar12,0);
        *(undefined8 *)(thisObject + 0x58) = uVar9;
        il2cpp_write_barrier_0();
        if ((*(longlong *)(thisObject + 0x58) != 0) &&
           (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar8 != 0)) {
          FUN_7ffe9ad10e00(lVar8,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
          lVar8 = *(longlong *)(thisObject + 0x58);
          uVar9 = FUN_7ffe9a6b5530(thisObject,0);
          if (lVar8 != 0) {
            *(undefined8 *)(lVar8 + 0x20) = uVar9;
            il2cpp_write_barrier_0();
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a6b614e:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

