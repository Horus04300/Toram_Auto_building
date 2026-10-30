
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PhysicalPursuit_Calc
              (undefined *thisObject,int value,undefined *playerAct,undefined *mobAct,
              undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined *thisObject_00;
  undefined8 uVar10;
  undefined4 in_register_00000014;
  int iVar11;
  longlong lStackX_8;
  longlong *aplStack_28 [2];
  
  if (DAT_7ffe9cade245 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418,CONCAT44(in_register_00000014,value));
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7560);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    DAT_7ffe9cade245 = '\x01';
  }
  aplStack_28[0] = (longlong *)0x0;
  lStackX_8 = 0;
  if (thisObject[0x12] == '\0') {
    return 0;
  }
  iVar11 = 0x19;
  if ((((playerAct == (undefined *)0x0) ||
       (plVar8 = (longlong *)
                 (**(code **)(*(longlong *)playerAct + 0x298))
                           (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0)),
       plVar8 == (longlong *)0x0)) ||
      (lVar9 = (**(code **)(*plVar8 + 0x1b8))(plVar8,*(undefined8 *)(*plVar8 + 0x1c0)), lVar9 == 0))
     || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a52cfea;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x1ed,aplStack_28,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    if (aplStack_28[0] == (longlong *)0x0) goto LAB_7ffe9a52cfea;
    iVar11 = (**(code **)(*aplStack_28[0] + 0x178))
                       (aplStack_28[0],0x1b,*(undefined8 *)(*aplStack_28[0] + 0x180));
    iVar11 = iVar11 + 0x19;
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)playerAct + 0x298))
                       (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (thisObject_00 =
             (undefined *)(**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220)),
       thisObject_00 == (undefined *)0x0)) goto LAB_7ffe9a52cfea;
    bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3f2,(undefined *)0x0);
    if (bVar4 != 0) {
      if ((aplStack_28[0] == (longlong *)0x0) || (aplStack_28[0][2] == 0)) goto LAB_7ffe9a52cfea;
      iVar11 = iVar11 + (uint)*(byte *)(aplStack_28[0][2] + 0x18);
    }
  }
  plVar8 = (longlong *)
           (**(code **)(*(longlong *)playerAct + 0x298))
                     (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
  if (((plVar8 != (longlong *)0x0) &&
      (lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)), lVar9 != 0))
     && (*(longlong *)(lVar9 + 0x50) != 0)) {
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x50),0x448,&lStackX_8,_DAT_7ffe9c934418);
    if (cVar3 != '\0') {
      if (lStackX_8 == 0) goto LAB_7ffe9a52cfea;
      iVar5 = func_0x7ffe9a7a2140(lStackX_8,0x34);
      iVar11 = iVar11 + iVar5;
    }
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)playerAct + 0x298))
                       (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
    if ((plVar8 != (longlong *)0x0) &&
       (lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)), lVar9 != 0)
       ) {
      cVar3 = FUN_7ffe9a7cbb30(lVar9,0x3d3,&lStackX_8,0);
      if (cVar3 != '\0') {
        plVar8 = (longlong *)
                 (**(code **)(*(longlong *)playerAct + 0x298))
                           (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
        if ((plVar8 == (longlong *)0x0) ||
           (lVar9 = (**(code **)(*plVar8 + 0x198))(plVar8,*(undefined8 *)(*plVar8 + 0x1a0)),
           lVar9 == 0)) goto LAB_7ffe9a52cfea;
        iVar5 = FUN_7ffe99742ec0(0xe,_DAT_7ffe9c940d40,lVar9);
        plVar8 = (longlong *)
                 (**(code **)(*(longlong *)playerAct + 0x298))
                           (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
        if ((plVar8 == (longlong *)0x0) ||
           (lVar9 = (**(code **)(*plVar8 + 0x198))(plVar8,*(undefined8 *)(*plVar8 + 0x1a0)),
           lVar9 == 0)) goto LAB_7ffe9a52cfea;
        iVar6 = FUN_7ffe99742ec0(0x10,_DAT_7ffe9c940d40,lVar9);
        if (iVar6 <= iVar5) {
          if (lStackX_8 == 0) goto LAB_7ffe9a52cfea;
          iVar5 = func_0x7ffe9a7a2140(lStackX_8,0x34);
          iVar11 = iVar11 + iVar5;
        }
      }
      cVar3 = FUN_7ffe99a4d1d0(iVar11,0);
      if (cVar3 == '\0') {
        return 0;
      }
      plVar8 = *(longlong **)(playerAct + 0x30);
      if (plVar8 != (longlong *)0x0) {
        if ((*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar8 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) != _DAT_7ffe9c922a40)) {
          if ((*(byte *)(_DAT_7ffe9c8f7560 + 0x130) <= *(byte *)(*plVar8 + 0x130)) &&
             (*(longlong *)
               (*(longlong *)(*plVar8 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) == _DAT_7ffe9c8f7560)) {
            if ((*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c8f7560 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar8 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) != _DAT_7ffe9c8f7560)) {
              FUN_7ffe9996c950(plVar8);
              pcVar2 = (code *)swi(3);
              iVar11 = (*pcVar2)();
              return iVar11;
            }
            if ((plVar8[9] == 0) ||
               (uVar1 = *(undefined8 *)(plVar8[9] + 0x18), mobAct == (undefined *)0x0))
            goto LAB_7ffe9a52cfea;
            uVar10 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAct);
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar3 = FUN_7ffe9bda1fa0(uVar1,uVar10,0);
            if (cVar3 != '\0') {
              uVar7 = (**(code **)(*(longlong *)thisObject + 0x178))
                                (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x180));
              FUN_7ffe9a4318b0(plVar8,uVar7,mobAct,0);
              return 1;
            }
          }
        }
        else {
          if ((*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar8 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) != _DAT_7ffe9c922a40)) {
            FUN_7ffe9996c950(plVar8);
            pcVar2 = (code *)swi(3);
            iVar11 = (*pcVar2)();
            return iVar11;
          }
          if ((plVar8[9] == 0) ||
             (uVar1 = *(undefined8 *)(plVar8[9] + 0x18), mobAct == (undefined *)0x0))
          goto LAB_7ffe9a52cfea;
          uVar10 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAct);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar3 = FUN_7ffe9bda1fa0(uVar1,uVar10,0);
          if (cVar3 != '\0') {
            uVar7 = (**(code **)(*(longlong *)thisObject + 0x178))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x180));
            FUN_7ffe9a45bf30(plVar8,uVar7,mobAct,0);
          }
        }
      }
      return 1;
    }
  }
LAB_7ffe9a52cfea:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar11 = (*pcVar2)();
  return iVar11;
}

