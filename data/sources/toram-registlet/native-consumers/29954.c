
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FamiliaMeteorStrikeAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  float fVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined *thisObject_00;
  undefined8 uVar10;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadf4a6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf4a6 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  plVar9 = (longlong *)0x0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    if (bVar3) {
      plVar9 = (longlong *)actarAction;
    }
  }
  *(undefined4 *)(thisObject + 0x20) = 0xbf800000;
  *(undefined4 *)(thisObject + 0x30) = 1;
  *(undefined4 *)(thisObject + 0x34) = 4;
  *(undefined4 *)(thisObject + 0x78) = 100;
  *(undefined4 *)(thisObject + 0x24) = 0x40000000;
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(plVar9,0,0);
  if (cVar4 != '\0') {
    if (plVar9 != (longlong *)0x0) {
      plVar7 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
      if (plVar7 != (longlong *)0x0) {
        lVar8 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
        if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x68) != 0)) {
          cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x40e,&plStackX_8,_DAT_7ffe9c935bd0);
          if (cVar4 != '\0') {
            fVar1 = *(float *)(thisObject + 0x24);
            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a7aeaad;
            iVar6 = (**(code **)(*plStackX_8 + 0x178))
                              (plStackX_8,0x26,*(undefined8 *)(*plStackX_8 + 0x180));
            *(float *)(thisObject + 0x24) = fVar1 - (float)iVar6 / _DAT_7ffe9c049ce4;
          }
          plVar9 = (longlong *)
                   (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
          if (plVar9 != (longlong *)0x0) {
            thisObject_00 =
                 (undefined *)
                 (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220));
            if (thisObject_00 != (undefined *)0x0) {
              bVar5 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3fe,(undefined *)0x0);
              if (bVar5 != 0) {
                *(undefined4 *)(thisObject + 0x28) = 1;
              }
              goto LAB_7ffe9a7aea6f;
            }
          }
        }
      }
    }
LAB_7ffe9a7aeaad:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
LAB_7ffe9a7aea6f:
  uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
  FUN_7ffe9a9002e0(uVar10,0x1e65f79b,0);
  *(undefined8 *)(thisObject + 0x58) = uVar10;
  il2cpp_write_barrier_0();
  return;
}

