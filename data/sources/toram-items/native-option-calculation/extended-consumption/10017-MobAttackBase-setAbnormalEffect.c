
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobAttackBase_setAbnormalEffect
               (undefined *self,undefined *skillDamageData,undefined *methodInfo)

{
  int iVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  undefined4 uVar5;
  float fVar6;
  
  if (DAT_7ffe9cadd7db == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    DAT_7ffe9cadd7db = '\x01';
  }
  lVar2 = *(longlong *)(self + 0xa0);
  if (lVar2 == 0) goto LAB_7ffe9a3784b8;
  if (0 < *(int *)(lVar2 + 0x30)) {
    cVar4 = FUN_7ffe9a8fea70(self,100,*(undefined4 *)(lVar2 + 0x34));
    if (cVar4 != '\0') {
      if ((*(longlong *)(self + 0xa0) == 0) || (skillDamageData == (undefined *)0x0)) {
LAB_7ffe9a3784b8:
        FUN_7ffe9996d7a0();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      iVar1 = *(int *)(*(longlong *)(self + 0xa0) + 0x30);
      *(int *)(skillDamageData + 0x8c) = iVar1;
      lVar2 = *(longlong *)(self + 0xa0);
      if (iVar1 == 4) {
        if (lVar2 == 0) goto LAB_7ffe9a3784b8;
        fVar6 = (float)*(int *)(lVar2 + 0x38) / _DAT_7ffe9c049ce4;
      }
      else {
        if (lVar2 == 0) goto LAB_7ffe9a3784b8;
        fVar6 = (float)*(int *)(lVar2 + 0x38);
      }
      *(float *)(skillDamageData + 0x94) = fVar6;
      if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar5 = FUN_7ffe9a4daf00(iVar1,fVar6,0);
      *(undefined4 *)(skillDamageData + 0x98) = uVar5;
    }
  }
  return;
}

