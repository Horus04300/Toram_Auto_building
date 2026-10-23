
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte _loadFieldData_d__125_MoveNext(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int fieldId;
  undefined *puVar4;
  longlong lVar5;
  undefined *self_00;
  undefined *callback;
  undefined8 uVar6;
  longlong lVar7;
  
  if (DAT_7fff625e75f9 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fb4c8);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff6245dce0);
    FUN_7fff5f47d450(&DAT_7fff6245ac58);
    FUN_7fff5f47d450(&DAT_7fff62458e78);
    FUN_7fff5f47d450(&DAT_7fff62469da8);
    FUN_7fff5f47d450(&DAT_7fff6246a1a8);
    FUN_7fff5f47d450(&DAT_7fff62445a88);
    FUN_7fff5f47d450(&DAT_7fff624513e8);
    FUN_7fff5f47d450(&DAT_7fff6241b678);
    FUN_7fff5f47d450(&DAT_7fff6241b748);
    DAT_7fff625e75f9 = '\x01';
  }
  lVar7 = *(longlong *)(self + 0x28);
  if (*(int *)(self + 0x10) == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    puVar4 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff624513e8);
    _loadFieldData_d__125_System_IDisposable_Dispose(puVar4,(undefined *)0x0);
    *(undefined **)(self + 0x30) = puVar4;
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff603f42b5;
    *(undefined1 *)(*(longlong *)(self + 0x30) + 0x10) = 1;
    lVar5 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
    if (lVar5 == 0) goto LAB_7fff603f42b5;
    *(undefined8 *)(self + 0x40) = *(undefined8 *)(lVar5 + 0x20);
    thunk_FUN_7fff5f491fd0();
    uVar6 = *(undefined8 *)(self + 0x40);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar2 = FUN_7fff618ab2e0(uVar6,0,0);
    if (cVar2 != '\0') {
      puVar4 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245ac58);
      lVar5 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
      if (lVar5 != 0) {
        fieldId = FUN_7fff6037c640(lVar5,0);
        if ((*(longlong *)(self + 0x40) != 0) && (puVar4 != (undefined *)0x0)) {
          bVar3 = MobMaster_ReadMaster
                            (puVar4,fieldId,*(undefined **)(*(longlong *)(self + 0x40) + 0x48),
                             *(undefined **)(self + 0x20),(undefined *)0x0);
          if (bVar3 == 0) {
            _loadFieldData_d__125_System_IDisposable_Dispose(_DAT_7fff6241b748,(undefined *)0x0);
          }
          self_00 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245ac58);
          puVar4 = *(undefined **)(self + 0x20);
          uVar6 = *(undefined8 *)(self + 0x30);
          callback = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
          FUN_7fff60739100(callback,uVar6,_DAT_7fff62445a88);
          if ((self_00 != (undefined *)0x0) &&
             (puVar4 = MobMaster_LoadMobResource(self_00,puVar4,callback,(undefined *)0x0),
             lVar7 != 0)) {
            uVar6 = FUN_7fff618a87c0(lVar7,puVar4,0);
            *(undefined8 *)(self + 0x18) = uVar6;
            thunk_FUN_7fff5f491fd0();
            *(undefined4 *)(self + 0x10) = 1;
            return 1;
          }
        }
      }
      goto LAB_7fff603f42b5;
    }
  }
  else {
    if (*(int *)(self + 0x10) != 1) {
      return 0;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff603f42b5;
    if (*(char *)(*(longlong *)(self + 0x30) + 0x10) == '\0') {
      _loadFieldData_d__125_System_IDisposable_Dispose(_DAT_7fff6241b678,(undefined *)0x0);
    }
    lVar5 = FUN_7fff60c66630(_DAT_7fff6246a1a8);
    if ((*(longlong *)(self + 0x40) == 0) ||
       (uVar6 = FUN_7fff60399400(*(longlong *)(self + 0x40),0), lVar5 == 0)) goto LAB_7fff603f42b5;
    FUN_7fff5fe47940(lVar5,uVar6,0);
    lVar5 = FUN_7fff60c66630(_DAT_7fff62469da8);
    if (lVar5 == 0) goto LAB_7fff603f42b5;
    FUN_7fff6035f570(lVar5,0);
    lVar5 = FUN_7fff60c66630(_DAT_7fff62469da8);
    if ((*(longlong *)(self + 0x40) == 0) ||
       (uVar6 = FUN_7fff60399200(*(longlong *)(self + 0x40),0), lVar5 == 0)) goto LAB_7fff603f42b5;
    FUN_7fff60360080(lVar5,uVar6,0);
  }
  if (lVar7 != 0) {
    *(undefined1 *)(lVar7 + 0x5a) = 1;
    if (self[0x38] != '\0') {
      FUN_7fff61695180(*(undefined8 *)(lVar7 + 0x30),0);
    }
    lVar7 = FUN_7fff60c4bc00(_DAT_7fff6245dce0);
    if (lVar7 != 0) {
      FUN_7fff5fdd25e0(lVar7,0,0);
      return 0;
    }
  }
LAB_7fff603f42b5:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

