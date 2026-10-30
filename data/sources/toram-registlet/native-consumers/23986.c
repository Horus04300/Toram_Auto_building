
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ExplossiveAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  code *pcVar5;
  float fVar6;
  char cVar7;
  byte bVar8;
  undefined4 uVar9;
  uint uVar10;
  undefined4 uVar11;
  longlong *plVar12;
  longlong lVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  undefined *thisObject_00;
  longlong *plVar16;
  float fVar17;
  float fVar18;
  undefined1 auStack_48 [8];
  undefined8 uStack_40;
  
  if (DAT_7ffe9caded63 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c935988);
    FUN_7ffe9996d590(&DAT_7ffe9c917f28);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    FUN_7ffe9996d590(&DAT_7ffe9c946f68);
    DAT_7ffe9caded63 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    *(undefined4 *)(thisObject + 0x30) = 1;
    uVar11 = FUN_7ffe9a4ade20(0,0);
    *(undefined4 *)(thisObject + 0xfc) = uVar11;
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
    uVar11 = 0;
    *(undefined4 *)(thisObject + 0x30) = 1;
    plVar16 = (longlong *)0x0;
    if (bVar4) {
      plVar16 = (longlong *)actarAction;
    }
    uVar9 = FUN_7ffe9a4ade20(plVar16,0);
    *(undefined4 *)(thisObject + 0xfc) = uVar9;
    if ((((plVar16 != (longlong *)0x0) &&
         (plVar12 = (longlong *)
                    (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
         plVar12 != (longlong *)0x0)) &&
        (lVar13 = (**(code **)(*plVar12 + 0x1b8))(plVar12,*(undefined8 *)(*plVar12 + 0x1c0)),
        lVar13 != 0)) && (*(longlong *)(lVar13 + 0x68) != 0)) {
      cVar7 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar13 + 0x68),0x22d,_DAT_7ffe9c935988);
      bVar4 = false;
      if ((cVar7 != '\0') && (cVar7 = FUN_7ffe9a4ad740(plVar16,0xd,0), bVar4 = false, cVar7 != '\0')
         ) {
        bVar4 = *(int *)(thisObject + 0xfc) != 0;
      }
      fVar6 = _DAT_7ffe9c049cfc;
      uVar9 = func_0x7ffe99a4d6a0();
      *(undefined4 *)(thisObject + 0x20) = uVar9;
      lVar13 = FUN_7ffe9bd98a10(actarAction,0);
      if (lVar13 != 0) {
        puVar14 = (undefined8 *)FUN_7ffe9bdbf710(auStack_48,lVar13,0);
        uVar9 = *(undefined4 *)(puVar14 + 1);
        *(undefined8 *)(thisObject + 300) = *puVar14;
        *(undefined4 *)(thisObject + 0x134) = uVar9;
        bVar8 = thisObject[0x14];
        *(uint *)(thisObject + 0x124) = (uint)bVar8 * 0x1e + 100;
        *(float *)(thisObject + 0x120) = (float)((uint)bVar8 * 0x3c) + _DAT_7ffe9c049d00;
        fVar17 = _DAT_7ffe9c049b4c;
        if (bVar8 < 6) {
          fVar17 = 0.0;
        }
        *(float *)(thisObject + 0x138) = fVar17 + _DAT_7ffe9c049cd8;
        lVar13 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,10);
        FUN_7ffe9b436460(lVar13,_DAT_7ffe9c946f68,0);
        uVar1 = thisObject[0x14];
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        bVar8 = func_0x7ffe9b506d70(uVar1,10,0);
        uVar10 = func_0x7ffe9b506b70(0,bVar8 - 1,0);
        if (lVar13 != 0) {
          if (*(uint *)(lVar13 + 0x18) <= uVar10) {
            FUN_7ffe9996d790();
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
          if (*(int *)(thisObject + 0xfc) == 0x13) {
            bVar4 = true;
          }
          *(undefined4 *)(thisObject + 0x128) =
               *(undefined4 *)(lVar13 + 0x20 + (longlong)(int)uVar10 * 4);
          if (bVar4) {
            fVar17 = *(float *)(thisObject + 0x120);
            plVar12 = (longlong *)
                      (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
            if ((plVar12 == (longlong *)0x0) ||
               (lVar13 = (**(code **)(*plVar12 + 0x188))(plVar12,*(undefined8 *)(*plVar12 + 400)),
               lVar13 == 0)) goto LAB_7ffe9a68e01f;
            iVar2 = *(int *)(lVar13 + 0x24);
            plVar12 = (longlong *)
                      (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
            if ((plVar12 == (longlong *)0x0) ||
               (lVar13 = (**(code **)(*plVar12 + 0x188))(plVar12,*(undefined8 *)(*plVar12 + 400)),
               lVar13 == 0)) goto LAB_7ffe9a68e01f;
            iVar3 = *(int *)(lVar13 + 0x34);
            fVar18 = *(float *)(thisObject + 0x138) + _DAT_7ffe9c049b18;
            *(int *)(thisObject + 0x128) = *(int *)(thisObject + 0x128) + 0x50;
            *(float *)(thisObject + 0x138) = fVar18;
            *(float *)(thisObject + 0x120) = (float)((iVar3 + iVar2) * 2) + fVar17;
          }
          *(float *)(thisObject + 0x120) = *(float *)(thisObject + 0x120) / fVar6;
          uVar9 = func_0x7ffe99a4d6a0();
          *(undefined4 *)(thisObject + 0x138) = uVar9;
          *(undefined4 *)(thisObject + 0x48) = 0x3f800000;
          plVar12 = (longlong *)
                    (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
          if ((plVar12 != (longlong *)0x0) &&
             (lVar13 = (**(code **)(*plVar12 + 0x1f8))(plVar12,*(undefined8 *)(*plVar12 + 0x200)),
             lVar13 != 0)) {
            lVar13 = FUN_7ffe99c08720(lVar13,1,0);
            if (lVar13 != 0) {
              uVar11 = *(undefined4 *)(lVar13 + 0x38);
            }
            *(undefined4 *)(thisObject + 0xfc) = uVar11;
            uVar15 = (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
            uVar11 = FUN_7ffe9a4aabb0(uVar15,0);
            *(undefined4 *)(thisObject + 0x78) = uVar11;
            plVar12 = (longlong *)
                      (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
            if ((plVar12 != (longlong *)0x0) &&
               (thisObject_00 =
                     (undefined *)
                     (**(code **)(*plVar12 + 0x218))(plVar12,*(undefined8 *)(*plVar12 + 0x220)),
               thisObject_00 != (undefined *)0x0)) {
              bVar8 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x2d,(undefined *)0x0);
              thisObject[0x149] = bVar8;
              FUN_7ffe9a4aacd0(thisObject,plVar16,0);
              uVar15 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
              FUN_7ffe9a9002e0(uVar15,0xbed7f51,0);
              *(undefined8 *)(thisObject + 0x58) = uVar15;
              il2cpp_write_barrier_0();
              if ((*(longlong *)(thisObject + 0x58) != 0) &&
                 (lVar13 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar13 != 0)) {
                uStack_40 = 0x7ffe9ad10e23;
                FUN_7ffe9ad1fce0(lVar13,7,*(undefined4 *)(thisObject + 0x30),
                                 CONCAT71((int7)((ulonglong)
                                                 *(undefined8 *)
                                                  (*(longlong *)(_DAT_7ffe9c949490 + 0x20) + 0xc0)
                                                >> 8),2));
                return;
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a68e01f:
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

