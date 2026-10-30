
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicBlastAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  float fVar1;
  byte bVar2;
  code *pcVar3;
  bool bVar4;
  char cVar5;
  undefined2 uVar6;
  undefined4 uVar7;
  int iVar8;
  longlong lVar9;
  longlong *plVar10;
  undefined *puVar11;
  undefined8 uVar12;
  longlong *plVar13;
  undefined8 uVar14;
  longlong lStackX_10;
  
  if (DAT_7ffe9cadee61 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c92d500);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadee61 = '\x01';
  }
  lStackX_10 = 0;
  if (actarAction == (undefined *)0x0) {
    plVar13 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    plVar13 = (longlong *)0x0;
    if (bVar4) {
      plVar13 = (longlong *)actarAction;
    }
  }
  lVar9 = FUN_7ffe9a47bac0(0);
  if (lVar9 != 0) {
    lVar9 = FUN_7ffe9a47f670(lVar9,0);
    if (lVar9 != 0) {
      cVar5 = FUN_7ffe9ab94d80(lVar9,0x77,&lStackX_10,_DAT_7ffe9c92d500);
      if (cVar5 != '\0') {
        if (lStackX_10 == 0) goto LAB_7ffe9a6b7bcd;
        uVar6 = FUN_7ffe9a5212c0(lStackX_10,0x67);
        *(undefined2 *)(thisObject + 0x150) = uVar6;
      }
      if (plVar13 != (longlong *)0x0) {
        lVar9 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
        if (lVar9 != 0) {
          uVar7 = FUN_7ffe9a4a1cc0(lVar9,0);
          *(undefined4 *)(thisObject + 0x30) = uVar7;
          *(undefined4 *)(thisObject + 0xfc) = 0;
          cVar5 = FUN_7ffe9a4ad740(plVar13,0xe);
          if (cVar5 == '\0') {
            cVar5 = FUN_7ffe9a4ad740(plVar13,0xf);
            if (cVar5 != '\0') {
              *(undefined4 *)(thisObject + 0xfc) = 0xf;
            }
          }
          else {
            *(undefined4 *)(thisObject + 0xfc) = 0xe;
          }
          uVar7 = func_0x7ffe99a4d6a0();
          bVar2 = thisObject[0x14];
          *(undefined4 *)(thisObject + 0x20) = uVar7;
          *(undefined4 *)(thisObject + 0x24) = 0x40800000;
          *(uint *)(thisObject + 0x13c) = (bVar2 + 9) * 0x14;
          *(float *)(thisObject + 0x138) = (float)((uint)bVar2 * 0x1e + 700);
          *(uint *)(thisObject + 0x140) = (uint)bVar2 + (uint)bVar2 * 4;
          *(float *)(thisObject + 0x144) = (float)(bVar2 / 6) + _DAT_7ffe9c049b74;
          if (thisObject[0x150] != '\0') {
            *(undefined4 *)(thisObject + 0x24) = 0x40400000;
          }
          if (thisObject[0x151] != '\0') {
            *(float *)(thisObject + 0x24) = *(float *)(thisObject + 0x24) - _DAT_7ffe9c049b70;
          }
          plVar10 = (longlong *)
                    (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
          if (plVar10 != (longlong *)0x0) {
            puVar11 = (undefined *)
                      (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220));
            if (puVar11 != (undefined *)0x0) {
              puVar11 = GemCartBufferManager_GetGemCartBuffer(puVar11,0xce,(undefined *)0x0);
              if (puVar11 != (undefined *)0x0) {
                fVar1 = *(float *)(thisObject + 0x24);
                iVar8 = GemCartBufferBase_GetValue(puVar11,(undefined *)0x2,(undefined *)0x0);
                *(float *)(thisObject + 0x24) = fVar1 - (float)iVar8 * _DAT_7ffe9c049b40;
              }
              uVar7 = *(undefined4 *)(thisObject + 0x24);
              uVar12 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
              uVar7 = FUN_7ffe9a4a7fe0(thisObject,uVar7,uVar12,0);
              *(undefined4 *)(thisObject + 0x24) = uVar7;
              uVar12 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
              uVar7 = FUN_7ffe9a4aabb0(uVar12,0);
              *(undefined4 *)(thisObject + 0x78) = uVar7;
              FUN_7ffe9a4aacd0(thisObject,plVar13,0);
              uVar12 = 0x1d0d8;
              if (*(int *)(thisObject + 0xfc) == 0xe) {
                fVar1 = *(float *)(thisObject + 0x138);
                plVar13 = (longlong *)
                          (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0))
                ;
                if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a6b7bcd;
                lVar9 = (**(code **)(*plVar13 + 0x198))(plVar13,*(undefined8 *)(*plVar13 + 0x1a0));
                if (lVar9 == 0) goto LAB_7ffe9a6b7bcd;
                iVar8 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar9);
                uVar12 = 0x956a0;
                *(float *)(thisObject + 0x138) =
                     (float)iVar8 / _DAT_7ffe9c049ce0 + _DAT_7ffe9c049d98 + fVar1;
              }
              else if (*(int *)(thisObject + 0xfc) == 0xf) {
                fVar1 = *(float *)(thisObject + 0x138);
                plVar13 = (longlong *)
                          (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0))
                ;
                if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a6b7bcd;
                lVar9 = (**(code **)(*plVar13 + 0x198))(plVar13,*(undefined8 *)(*plVar13 + 0x1a0));
                if (lVar9 == 0) goto LAB_7ffe9a6b7bcd;
                iVar8 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar9);
                *(int *)(thisObject + 0x140) = *(int *)(thisObject + 0x140) + 0x32;
                uVar12 = 0xad958;
                *(float *)(thisObject + 0x138) = (float)iVar8 / _DAT_7ffe9c049ce0 + fVar1;
                *(float *)(thisObject + 0x144) = *(float *)(thisObject + 0x144) + _DAT_7ffe9c049b70;
              }
              if (thisObject[0x151] != '\0') {
                *(int *)(thisObject + 0x140) = *(int *)(thisObject + 0x140) / 5;
              }
              uVar7 = func_0x7ffe99a4d6a0();
              *(undefined4 *)(thisObject + 0x144) = uVar7;
              uVar14 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
              FUN_7ffe9a9002e0(uVar14,uVar12,0);
              *(undefined8 *)(thisObject + 0x58) = uVar14;
              il2cpp_write_barrier_0();
              if ((*(longlong *)(thisObject + 0x58) != 0) &&
                 (lVar9 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar9 != 0)) {
                FUN_7ffe9ad10e00(lVar9,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
                lVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                FUN_7ffe9a9002e0(lVar9,0x9d2a62,0);
                if ((lVar9 != 0) && (*(longlong *)(lVar9 + 0x50) != 0)) {
                  FUN_7ffe9ad10e00(*(longlong *)(lVar9 + 0x50),7,*(undefined4 *)(thisObject + 0x30),
                                   _DAT_7ffe9c949490);
                  if (*(longlong *)(thisObject + 0x58) != 0) {
                    *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20) = lVar9;
                    il2cpp_write_barrier_0();
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a6b7bcd:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

