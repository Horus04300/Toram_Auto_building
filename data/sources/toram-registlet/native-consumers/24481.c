
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SonicThrustAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  undefined4 uVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  longlong lVar5;
  char cVar6;
  byte bVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 uVar10;
  longlong *plVar11;
  longlong lVar12;
  undefined *thisObject_00;
  undefined8 uVar13;
  byte bVar14;
  undefined4 auStackX_8 [2];
  undefined8 in_stack_ffffffffffffff98;
  undefined4 uVar15;
  undefined8 in_stack_ffffffffffffffa0;
  undefined4 uVar16;
  undefined8 in_stack_ffffffffffffffa8;
  uint uVar17;
  
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffff98 >> 0x20);
  uVar16 = (undefined4)((ulonglong)in_stack_ffffffffffffffa0 >> 0x20);
  uVar17 = (uint)((ulonglong)in_stack_ffffffffffffffa8 >> 0x20);
  if (DAT_7ffe9cadee1e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    DAT_7ffe9cadee1e = '\x01';
  }
  uVar1 = *(undefined4 *)(thisObject + 0x74);
  auStackX_8[0] = 0;
  *(undefined4 *)(thisObject + 0x74) = 0x42c80000;
  if (((playerAction != (undefined *)0x0) &&
      (plVar11 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
      plVar11 != (longlong *)0x0)) &&
     (lVar12 = (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*plVar11 + 0x1b0)),
     lVar12 != 0)) {
    uVar8 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,lVar12);
    cVar6 = FUN_7ffe9a4b33f0(thisObject,uVar8,mobAction,0);
    bVar14 = cVar6 != '\0';
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar11 != (longlong *)0x0) &&
       (thisObject_00 =
             (undefined *)(**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220))
       , thisObject_00 != (undefined *)0x0)) {
      bVar7 = GemCartBufferManager_ContainsBuffer(thisObject_00,0xd9,(undefined *)0x0);
      if (bVar7 != 0) {
        if ((mobAction == (undefined *)0x0) ||
           (lVar12 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction), lVar12 == 0))
        goto LAB_7ffe9a6af5c4;
        iVar9 = FUN_7ffe99742ec0(8,_DAT_7ffe9c93ed20,lVar12);
        if (iVar9 < 100) {
          bVar14 = bVar14 | 4;
        }
      }
      uVar13 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
      FUN_7ffe9a6596c0(uVar13,0);
      uVar8 = (**(code **)(*(longlong *)thisObject + 0x198))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      uVar10 = (**(code **)(*(longlong *)thisObject + 0x588))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x590));
      lVar12 = FUN_7ffe9a4b0940(thisObject,uVar13,playerAction,mobAction,CONCAT44(uVar15,uVar8),
                                CONCAT44(uVar16,uVar10),(ulonglong)uVar17 << 0x20,bVar14,0);
      if (lVar12 != 0) {
        FUN_7ffe9a657c40(lVar12,0x12,*(float *)(thisObject + 0x120) / _DAT_7ffe9c049cfc);
        FUN_7ffe9a657a50(lVar12,8);
        uVar13 = func_0x7ffe99940040(_DAT_7ffe9c920098);
        FUN_7ffe9a8f6350(uVar13,mobAction,0);
        lVar12 = FUN_7ffe9a4b4370(thisObject,uVar13,lVar12,1,0);
        if ((lVar12 != 0) && (lVar2 = *(longlong *)(lVar12 + 0x38), lVar2 != 0)) {
          if ((*(int *)(lVar2 + 0x14) != 0) &&
             ((*(int *)(lVar2 + 0x18) != 1 &&
              (cVar6 = FUN_7ffe9a4b2fb0(thisObject,2,*(undefined4 *)(thisObject + 0x128),
                                        playerAction,mobAction,auStackX_8,0), cVar6 != '\0')))) {
            if (*(longlong *)(lVar12 + 0x38) == 0) goto LAB_7ffe9a6af5c4;
            FUN_7ffe9a8ffe30(*(longlong *)(lVar12 + 0x38),2);
          }
          lVar5 = _DAT_7ffe9c913488;
          lVar2 = *(longlong *)(thisObject + 0x80);
          if (lVar2 != 0) {
            *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
            lVar3 = *(longlong *)(lVar2 + 0x10);
            uVar17 = *(uint *)(lVar2 + 0x18);
            if (lVar3 != 0) {
              if (uVar17 < *(uint *)(lVar3 + 0x18)) {
                *(uint *)(lVar2 + 0x18) = uVar17 + 1;
                if (*(uint *)(lVar3 + 0x18) <= uVar17) {
                  FUN_7ffe9996d790();
                  pcVar4 = (code *)swi(3);
                  (*pcVar4)();
                  return;
                }
                *(longlong *)(lVar3 + 0x20 + (longlong)(int)uVar17 * 8) = lVar12;
                il2cpp_write_barrier_0();
              }
              else {
                FUN_7ffe9afd58b0(lVar2,lVar12,
                                 *(undefined8 *)
                                  (*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
              }
              *(undefined4 *)(thisObject + 0x74) = uVar1;
              return;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a6af5c4:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

