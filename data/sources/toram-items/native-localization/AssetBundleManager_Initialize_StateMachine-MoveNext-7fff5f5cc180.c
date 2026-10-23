
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte AssetBundleManager_Initialize_StateMachine_MoveNext(undefined *self,undefined *methodInfo)

{
  undefined *self_00;
  code *pcVar1;
  char cVar2;
  byte bVar3;
  undefined *puVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  longlong *methodInfo_00;
  longlong lVar8;
  
  if (DAT_7fff625e175e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62472440);
    FUN_7fff5f47d450(&DAT_7fff62472370);
    FUN_7fff5f47d450(0x7fff62472838);
    FUN_7fff5f47d450(&DAT_7fff62472908);
    FUN_7fff5f47d450(0x7fff624729d0);
    FUN_7fff5f47d450(&DAT_7fff6242f138);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff62458858);
    FUN_7fff5f47d450(&DAT_7fff624596b0);
    FUN_7fff5f47d450(&DAT_7fff624595f0);
    FUN_7fff5f47d450(&DAT_7fff62459528);
    DAT_7fff625e175e = '\x01';
  }
  self_00 = *(undefined **)(self + 0x20);
  if (*(int *)(self + 0x10) == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (self_00 != (undefined *)0x0) {
      if (self_00[0x68] != '\0') {
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                  (_DAT_7fff62459528,(undefined *)0x0);
        return 0;
      }
      *(undefined8 *)(self_00 + 0x58) = *(undefined8 *)(self + 0x28);
      thunk_FUN_7fff5f491fd0();
      *(undefined8 *)(self_00 + 0x60) = *(undefined8 *)(self + 0x30);
      thunk_FUN_7fff5f491fd0();
      puVar4 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242f138);
      TextManagerDataBase__ctor(puVar4,_DAT_7fff62472370);
      *(undefined **)(self + 0x40) = puVar4;
      thunk_FUN_7fff5f491fd0();
      lVar5 = FUN_7fff60c4bc00(_DAT_7fff62458858);
      uVar6 = FUN_7fff60e71970(*(undefined8 *)(self_00 + 0x58),*(undefined8 *)(self_00 + 0x60),0);
      uVar7 = *(undefined8 *)(self + 0x40);
      if (lVar5 != 0) {
        if (DAT_7fff625e1783 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff6243c068);
          DAT_7fff625e1783 = '\x01';
        }
        puVar4 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6243c068);
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar4,(undefined *)0x0);
        *(longlong *)(puVar4 + 0x20) = lVar5;
        *(undefined4 *)(puVar4 + 0x10) = 0;
        thunk_FUN_7fff5f491fd0();
        *(undefined8 *)(puVar4 + 0x30) = uVar6;
        thunk_FUN_7fff5f491fd0();
        *(undefined8 *)(puVar4 + 0x28) = uVar7;
        thunk_FUN_7fff5f491fd0();
        uVar7 = FUN_7fff618a87c0(self_00,puVar4,0);
        *(undefined8 *)(self + 0x18) = uVar7;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 1;
        return 1;
      }
    }
    goto LAB_7fff5f5cc538;
  }
  if (*(int *)(self + 0x10) == 1) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff5f5cc538;
    cVar2 = FUN_7fff60905130(*(longlong *)(self + 0x40),_DAT_7fff62472908);
    if (cVar2 == '\0') {
      if ((*(longlong *)(self + 0x40) == 0) || (self_00 == (undefined *)0x0)) goto LAB_7fff5f5cc538;
      bVar3 = AssetBundleManager_createVersionTable
                        (self_00,*(undefined **)(*(longlong *)(self + 0x40) + 0x10),
                         *(undefined **)(self_00 + 0x30),(undefined *)0x0);
      lVar5 = *(longlong *)(self + 0x40);
      if (bVar3 != 0) {
        if (lVar5 != 0) {
          FUN_7fff60904b60(lVar5,_DAT_7fff62472440);
          *(undefined8 *)(self + 0x40) = 0;
          thunk_FUN_7fff5f491fd0();
          lVar5 = *(longlong *)(self + 0x38);
          if (lVar5 != 0) {
            (**(code **)(lVar5 + 0x18))
                      (*(undefined8 *)(lVar5 + 0x40),1,*(undefined8 *)(lVar5 + 0x28));
            self_00[0x68] = 1;
            return 0;
          }
        }
        goto LAB_7fff5f5cc538;
      }
      if (lVar5 == 0) goto LAB_7fff5f5cc538;
      FUN_7fff60904b60();
      *(undefined8 *)(self + 0x40) = 0;
      thunk_FUN_7fff5f491fd0();
      StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                (_DAT_7fff624596b0,(undefined *)0x0);
    }
    else {
      methodInfo_00 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
      if ((*(longlong *)(self + 0x40) == 0) ||
         (lVar5 = *(longlong *)(*(longlong *)(self + 0x40) + 0x20), methodInfo_00 == (longlong *)0x0
         )) goto LAB_7fff5f5cc538;
      if ((lVar5 != 0) &&
         (lVar8 = func_0x7fff5f47c7e0(lVar5,*(undefined8 *)(*methodInfo_00 + 0x40)), lVar8 == 0)) {
        uVar7 = func_0x7fff5f47d0b0();
        FUN_7fff5f47d620(uVar7,0);
        pcVar1 = (code *)swi(3);
        bVar3 = (*pcVar1)();
        return bVar3;
      }
      if ((int)methodInfo_00[3] == 0) {
        FUN_7fff5f47d650();
        pcVar1 = (code *)swi(3);
        bVar3 = (*pcVar1)();
        return bVar3;
      }
      methodInfo_00[4] = lVar5;
      thunk_FUN_7fff5f491fd0();
      StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                (_DAT_7fff624595f0,(undefined *)methodInfo_00);
      if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff5f5cc538;
      FUN_7fff60904b60(*(longlong *)(self + 0x40),_DAT_7fff62472440);
      *(undefined8 *)(self + 0x40) = 0;
      thunk_FUN_7fff5f491fd0();
    }
    lVar5 = *(longlong *)(self + 0x38);
    if (lVar5 == 0) {
LAB_7fff5f5cc538:
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      bVar3 = (*pcVar1)();
      return bVar3;
    }
    (**(code **)(lVar5 + 0x18))(*(undefined8 *)(lVar5 + 0x40),0,*(undefined8 *)(lVar5 + 0x28));
  }
  return 0;
}

