
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SleepTrapAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  int iVar1;
  longlong lVar2;
  bool bVar3;
  code *pcVar4;
  float fVar5;
  char cVar6;
  byte bVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  longlong *plVar10;
  longlong lVar11;
  undefined8 *puVar12;
  undefined8 uVar13;
  undefined *thisObject_00;
  longlong *plVar14;
  double dVar15;
  float fVar16;
  float fVar17;
  undefined1 auStack_38 [32];
  undefined8 uStack_18;
  
  if (DAT_7ffe9caded9b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c935988);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9caded9b = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    *(undefined4 *)(thisObject + 0x30) = 2;
    uVar9 = FUN_7ffe9a4ade20(0,0);
    *(undefined4 *)(thisObject + 0xfc) = uVar9;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    uVar9 = 0;
    *(undefined4 *)(thisObject + 0x30) = 2;
    plVar14 = (longlong *)0x0;
    if (bVar3) {
      plVar14 = (longlong *)actarAction;
    }
    uVar8 = FUN_7ffe9a4ade20(plVar14,0);
    *(undefined4 *)(thisObject + 0xfc) = uVar8;
    if ((((plVar14 != (longlong *)0x0) &&
         (plVar10 = (longlong *)
                    (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0)),
         plVar10 != (longlong *)0x0)) &&
        (lVar11 = (**(code **)(*plVar10 + 0x1b8))(plVar10,*(undefined8 *)(*plVar10 + 0x1c0)),
        lVar11 != 0)) && (*(longlong *)(lVar11 + 0x68) != 0)) {
      cVar6 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar11 + 0x68),0x22d,_DAT_7ffe9c935988);
      bVar3 = false;
      if ((cVar6 != '\0') && (cVar6 = FUN_7ffe9a4ad740(plVar14,0xd,0), bVar3 = false, cVar6 != '\0')
         ) {
        bVar3 = *(int *)(thisObject + 0xfc) != 0;
      }
      fVar5 = _DAT_7ffe9c049cfc;
      uVar8 = func_0x7ffe99a4d6a0();
      *(undefined4 *)(thisObject + 0x20) = uVar8;
      lVar11 = FUN_7ffe9bd98a10(actarAction,0);
      if (lVar11 != 0) {
        puVar12 = (undefined8 *)FUN_7ffe9bdbf710(auStack_38,lVar11,0);
        fVar17 = _DAT_7ffe9c049b4c;
        bVar7 = thisObject[0x14];
        uVar8 = *(undefined4 *)(puVar12 + 1);
        *(undefined8 *)(thisObject + 300) = *puVar12;
        *(undefined4 *)(thisObject + 0x134) = uVar8;
        *(uint *)(thisObject + 0x124) = (bVar7 + 10) * 5;
        *(float *)(thisObject + 0x120) = (float)bVar7;
        fVar16 = fVar17;
        if (bVar7 < 6) {
          fVar16 = 0.0;
        }
        *(float *)(thisObject + 0x138) = fVar16 + fVar17;
        bVar7 = thisObject[0x14];
        if (DAT_7ffe9cad9c12 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9c12 = '\x01';
        }
        fVar17 = (float)bVar7 * _DAT_7ffe9c049c7c + _DAT_7ffe9c04aba0;
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        dVar15 = (double)func_0x7ffe999978b4((double)fVar17);
        *(int *)(thisObject + 0x128) = (int)dVar15 * 10;
        if (*(int *)(thisObject + 0xfc) == 0x13) {
          bVar3 = true;
        }
        if (bVar3) {
          fVar17 = *(float *)(thisObject + 0x120);
          plVar10 = (longlong *)
                    (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
          if ((plVar10 == (longlong *)0x0) ||
             (lVar11 = (**(code **)(*plVar10 + 0x188))(plVar10,*(undefined8 *)(*plVar10 + 400)),
             lVar11 == 0)) goto LAB_7ffe9a699fe8;
          iVar1 = *(int *)(lVar11 + 0x24);
          fVar16 = *(float *)(thisObject + 0x138) + _DAT_7ffe9c049b18;
          *(int *)(thisObject + 0x128) = *(int *)(thisObject + 0x128) + 0x14;
          *(float *)(thisObject + 0x138) = fVar16;
          *(float *)(thisObject + 0x120) = (float)(iVar1 / 2) + fVar17;
        }
        *(float *)(thisObject + 0x120) = *(float *)(thisObject + 0x120) / fVar5;
        uVar8 = func_0x7ffe99a4d6a0();
        *(undefined4 *)(thisObject + 0x138) = uVar8;
        *(undefined4 *)(thisObject + 0x48) = uVar8;
        plVar10 = (longlong *)
                  (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
        if ((plVar10 != (longlong *)0x0) &&
           (lVar11 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200)),
           lVar11 != 0)) {
          lVar11 = FUN_7ffe99c08720(lVar11,1,0);
          if (lVar11 != 0) {
            uVar9 = *(undefined4 *)(lVar11 + 0x38);
          }
          *(undefined4 *)(thisObject + 0xfc) = uVar9;
          uVar13 = (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
          uVar9 = FUN_7ffe9a4aabb0(uVar13,0);
          *(undefined4 *)(thisObject + 0x78) = uVar9;
          plVar10 = (longlong *)
                    (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
          if ((plVar10 != (longlong *)0x0) &&
             (thisObject_00 =
                   (undefined *)
                   (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220)),
             thisObject_00 != (undefined *)0x0)) {
            bVar7 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x2d,(undefined *)0x0);
            thisObject[0x149] = bVar7;
            FUN_7ffe9a4aacd0(thisObject,plVar14,0);
            uVar13 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            FUN_7ffe9a9002e0(uVar13,0xbed7f51,0);
            *(undefined8 *)(thisObject + 0x58) = uVar13;
            il2cpp_write_barrier_0();
            if ((*(longlong *)(thisObject + 0x58) != 0) &&
               (lVar11 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar11 != 0)) {
              lVar2 = *(longlong *)(*(longlong *)(_DAT_7ffe9c949490 + 0x20) + 0xc0);
              uStack_18 = *(undefined8 *)(lVar2 + 0x118);
              FUN_7ffe9ad1fce0(lVar11,7,*(undefined4 *)(thisObject + 0x30),
                               CONCAT71((int7)((ulonglong)lVar2 >> 8),2));
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a699fe8:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

