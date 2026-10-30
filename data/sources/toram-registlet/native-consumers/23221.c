
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AirSlideAction_OnInitialize(undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  byte bVar3;
  ulonglong uVar4;
  code *pcVar5;
  bool bVar6;
  int iVar7;
  longlong *plVar8;
  undefined *puVar9;
  longlong lVar10;
  longlong lVar11;
  longlong *plVar12;
  uint uVar13;
  float fVar14;
  undefined4 uVar15;
  undefined8 uVar16;
  double dVar17;
  float fVar18;
  
  if (DAT_7ffe9cadec50 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadec50 = '\x01';
  }
  *(undefined4 *)(thisObject + 0x20) = 0xbf800000;
  if (actarAction == (undefined *)0x0) {
    plVar12 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    plVar12 = (longlong *)0x0;
    if (bVar6) {
      plVar12 = (longlong *)actarAction;
    }
  }
  fVar18 = (float)(byte)thisObject[0x14];
  *(undefined4 *)(thisObject + 0x30) = 3;
  *(undefined4 *)(thisObject + 0xfc) = 0;
  fVar14 = fVar18 * _DAT_7ffe9c04ab84;
  *(float *)(thisObject + 300) = fVar18 + fVar18 + _DAT_7ffe9c049e64;
  iVar7 = ((byte)thisObject[0x14] + 10) * 5;
  *(int *)(thisObject + 0x148) = iVar7;
  *(float *)(thisObject + 0x128) = (float)(0x7d - (int)fVar14);
  uVar16 = func_0x7ffe99a4d6a0(iVar7,0);
  *(int *)(thisObject + 0x124) = (int)uVar16;
  uVar15 = func_0x7ffe99a4d6a0(uVar16,0);
  *(undefined4 *)(thisObject + 0x124) = uVar15;
  if (((plVar12 != (longlong *)0x0) &&
      (plVar8 = (longlong *)
                (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0)),
      plVar8 != (longlong *)0x0)) &&
     (puVar9 = (undefined *)(**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220)),
     puVar9 != (undefined *)0x0)) {
    puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,0xd2,(undefined *)0x0);
    fVar14 = _DAT_7ffe9c049b18;
    thisObject[0x154] = puVar9 != (undefined *)0x0;
    if (puVar9 != (undefined *)0x0) {
      iVar7 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x4,(undefined *)0x0);
      *(float *)(thisObject + 0x128) = (float)iVar7 + *(float *)(thisObject + 0x128);
      *(float *)(thisObject + 300) = (float)iVar7 + *(float *)(thisObject + 300);
      iVar7 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x2,(undefined *)0x0);
      fVar14 = (float)iVar7 * _DAT_7ffe9c049b34;
    }
    fVar18 = _DAT_7ffe9c049cfc;
    *(undefined4 *)(thisObject + 0x120) = 4;
    *(undefined4 *)(thisObject + 0x28) = 4;
    *(float *)(thisObject + 0x124) = fVar14 * *(float *)(thisObject + 0x124);
    *(float *)(thisObject + 0x128) = *(float *)(thisObject + 0x128) / fVar18;
    *(float *)(thisObject + 300) = *(float *)(thisObject + 300) / fVar18;
    *(int *)(thisObject + 0x104) = (int)(fVar14 * fVar18);
    (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
    uVar15 = FUN_7ffe9a4a7fe0(thisObject);
    *(undefined4 *)(thisObject + 0x24) = uVar15;
    uVar16 = (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
    uVar15 = FUN_7ffe9a4aabb0(uVar16,0);
    *(undefined4 *)(thisObject + 0x78) = uVar15;
    FUN_7ffe9a4aacd0(thisObject,plVar12,0);
    bVar3 = thisObject[0x14];
    if (DAT_7ffe9cad9c12 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c968830);
      DAT_7ffe9cad9c12 = '\x01';
    }
    fVar18 = (float)bVar3 * _DAT_7ffe9c049dc4;
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    dVar17 = (double)func_0x7ffe999978b4((double)fVar18);
    *(int *)(thisObject + 0x150) = (int)dVar17 + 0xf;
    uVar16 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
    FUN_7ffe9a9002e0(uVar16,0xf6d39,0);
    *(undefined8 *)(thisObject + 0x58) = uVar16;
    il2cpp_write_barrier_0();
    if ((*(longlong *)(thisObject + 0x58) != 0) &&
       (lVar10 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar10 != 0)) {
      FUN_7ffe9ad10e00(lVar10,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
      lVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
      FUN_7ffe9a900240(lVar10,0x9ee7b0,0x9ee7b2,0);
      if ((lVar10 != 0) && (*(longlong *)(lVar10 + 0x50) != 0)) {
        FUN_7ffe9ad10e00(*(longlong *)(lVar10 + 0x50),7,*(undefined4 *)(thisObject + 0x30),
                         _DAT_7ffe9c949490);
        if (*(longlong *)(lVar10 + 0x50) != 0) {
          iVar7 = (int)(fVar14 * _DAT_7ffe9c049d00);
          FUN_7ffe9ad10e00(*(longlong *)(lVar10 + 0x50),6,iVar7,_DAT_7ffe9c949490);
          lVar11 = FUN_7ffe9a900070(lVar10,0x9ee7b1,0x9ee7b2,0);
          if ((lVar11 != 0) && (*(longlong *)(lVar11 + 0x50) != 0)) {
            FUN_7ffe9ad10e00(*(longlong *)(lVar11 + 0x50),1,*(int *)(thisObject + 0x120) + -1,
                             _DAT_7ffe9c949490);
            if (*(longlong *)(lVar11 + 0x50) != 0) {
              FUN_7ffe9ad10e00(*(longlong *)(lVar11 + 0x50),7,*(undefined4 *)(thisObject + 0x30),
                               _DAT_7ffe9c949490);
              if (*(longlong *)(lVar11 + 0x50) != 0) {
                FUN_7ffe9ad10e00(*(longlong *)(lVar11 + 0x50),6,iVar7,_DAT_7ffe9c949490);
                lVar11 = FUN_7ffe9a900160(lVar11,0x9ee7b2,0);
                if ((lVar11 != 0) && (*(longlong *)(lVar11 + 0x50) != 0)) {
                  FUN_7ffe9ad10e00(*(longlong *)(lVar11 + 0x50),7,*(undefined4 *)(thisObject + 0x30)
                                   ,_DAT_7ffe9c949490);
                  if (*(longlong *)(lVar11 + 0x50) != 0) {
                    FUN_7ffe9ad10e00(*(longlong *)(lVar11 + 0x50),6,iVar7,_DAT_7ffe9c949490);
                    if (*(longlong *)(thisObject + 0x58) != 0) {
                      plVar12 = (longlong *)(*(longlong *)(thisObject + 0x58) + 0x20);
                      *plVar12 = lVar10;
                      if (_DAT_7ffe9caee1a8 != 0) {
                        uVar13 = (uint)((ulonglong)plVar12 >> 0xc);
                        puVar1 = (ulonglong *)
                                 ((ulonglong)((uVar13 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
                        do {
                          uVar4 = *puVar1;
                          LOCK();
                          uVar2 = *puVar1;
                          if (uVar4 == uVar2) {
                            *puVar1 = uVar4 | 1L << (uVar13 & 0x3f);
                          }
                          UNLOCK();
                        } while (uVar4 != uVar2);
                      }
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
  }
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

