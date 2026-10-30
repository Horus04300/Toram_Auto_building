
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkullShakerAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  int iVar1;
  code *pcVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined *self;
  longlong *plStackX_10;
  
  if (DAT_7ffe9cadf0f7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    DAT_7ffe9cadf0f7 = '\x01';
  }
  plStackX_10 = (longlong *)0x0;
  PlayerAttackBase_ActionPreparation(thisObject,actarAction,target,(undefined *)0x0);
  if (target != (undefined *)0x0) {
    uVar7 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c962758);
    *(undefined8 *)(thisObject + 0x138) = uVar7;
    il2cpp_write_barrier_0();
    if (*(longlong *)(thisObject + 0x138) != 0) {
      self = (undefined *)FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0);
      if (self == (undefined *)0x0) goto LAB_7ffe9a71657d;
      bVar4 = FUN_7ffe9a2ac880(self,0x12,(undefined *)&plStackX_10,(undefined *)0x0);
      if (bVar4 != 0) {
        if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a71657d;
        iVar5 = (**(code **)(*plStackX_10 + 0x1a8))
                          (plStackX_10,*(undefined8 *)(*plStackX_10 + 0x1b0));
        iVar1 = *(int *)(thisObject + 0x124);
        iVar3 = (int)((float)(byte)thisObject[0x14] * 7.5) + 0x19;
        if (*(int *)(thisObject + 0xfc) != 0xe) {
          iVar3 = (int)((float)(byte)thisObject[0x14] * 7.5);
        }
        if (*(undefined **)(thisObject + 0x140) != (undefined *)0x0) {
          iVar6 = GemCartBufferBase_GetValue
                            (*(undefined **)(thisObject + 0x140),(undefined *)0x2,(undefined *)0x0);
          if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          iVar5 = func_0x7ffe9b506d80(iVar5,iVar6,0);
          *(undefined4 *)(thisObject + 0x130) = 0;
          *(int *)(thisObject + 0x124) = iVar5 * iVar3 + iVar1;
          return;
        }
        *(int *)(thisObject + 0x124) = iVar3 * iVar5 + iVar1;
        *(int *)(thisObject + 0x130) = iVar5 * 10;
      }
    }
    return;
  }
LAB_7ffe9a71657d:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

