
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte StageLoginDownloader_StartDownload_StateMachine_MoveNext(undefined *self,undefined *methodInfo)

{
  undefined *self_00;
  code *pcVar1;
  byte bVar2;
  undefined *puVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  if (DAT_7fff625e148f == '\0') {
    FUN_7fff5f47d450(0x7fff6245c4f8);
    FUN_7fff5f47d450(&DAT_7fff6245af88);
    FUN_7fff5f47d450(&DAT_7fff6245adf0);
    FUN_7fff5f47d450(0x7fff624606f8);
    FUN_7fff5f47d450(&DAT_7fff62403cf8);
    FUN_7fff5f47d450(0x7fff62404108);
    FUN_7fff5f47d450(0x7fff62403f68);
    FUN_7fff5f47d450(0x7fff62460628);
    FUN_7fff5f47d450(0x7fff624041d8);
    FUN_7fff5f47d450(0x7fff62460890);
    FUN_7fff5f47d450(0x7fff62404038);
    FUN_7fff5f47d450(0x7fff624607c0);
    FUN_7fff5f47d450(0x7fff624042a8);
    DAT_7fff625e148f = '\x01';
  }
  self_00 = *(undefined **)(self + 0x20);
  switch(*(undefined4 *)(self + 0x10)) {
  case 0:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if ((self_00 != (undefined *)0x0) && (*(longlong *)(self_00 + 0x20) != 0)) {
      func_0x7fff5f7f54d0();
      if (DAT_7fff625e1483 == '\0') {
        FUN_7fff5f47d450(&DAT_7fff62430488);
        DAT_7fff625e1483 = '\x01';
      }
      puVar3 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62430488);
      StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar3,(undefined *)0x0);
      *(undefined **)(puVar3 + 0x20) = self_00;
      *(undefined4 *)(puVar3 + 0x10) = 0;
      thunk_FUN_7fff5f491fd0();
      uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
      *(undefined8 *)(self + 0x18) = uVar4;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
    break;
  case 1:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (self_00 != (undefined *)0x0) {
      if (self_00[0x30] != '\0') {
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                  (puRam00007fff62403f68,(undefined *)0x0);
        puVar3 = StageLoginDownloader_showDownloadError
                           (self_00,puRam00007fff62460628,(undefined *)0x0);
        uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 2;
        return 1;
      }
      if (*(longlong *)(self_00 + 0x20) != 0) {
        func_0x7fff5f7f54d0();
        if (DAT_7fff625e1484 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff62430168);
          DAT_7fff625e1484 = '\x01';
        }
        puVar3 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62430168);
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar3,(undefined *)0x0);
        *(undefined **)(puVar3 + 0x20) = self_00;
        *(undefined4 *)(puVar3 + 0x10) = 0;
        thunk_FUN_7fff5f491fd0();
        uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 3;
        return 1;
      }
    }
    break;
  case 2:
  case 4:
  case 6:
  case 8:
  case 10:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    return 0;
  case 3:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (self_00 != (undefined *)0x0) {
      if (self_00[0x30] != '\0') {
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                  (puRam00007fff62404038,(undefined *)0x0);
        puVar3 = StageLoginDownloader_showDownloadError
                           (self_00,puRam00007fff624606f8,(undefined *)0x0);
        uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 4;
        return 1;
      }
      if (*(longlong *)(self_00 + 0x20) != 0) {
        func_0x7fff5f7f54d0();
        if (DAT_7fff625e1485 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff624302f8);
          DAT_7fff625e1485 = '\x01';
        }
        puVar3 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff624302f8);
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar3,(undefined *)0x0);
        *(undefined **)(puVar3 + 0x20) = self_00;
        *(undefined4 *)(puVar3 + 0x10) = 0;
        thunk_FUN_7fff5f491fd0();
        uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 5;
        return 1;
      }
    }
    break;
  case 5:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (self_00 != (undefined *)0x0) {
      if (self_00[0x30] != '\0') {
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                  (puRam00007fff62404108,(undefined *)0x0);
        puVar3 = StageLoginDownloader_showDownloadError
                           (self_00,puRam00007fff624607c0,(undefined *)0x0);
        uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 6;
        return 1;
      }
      if (*(longlong *)(self_00 + 0x20) != 0) {
        func_0x7fff5f7f54d0();
        if (DAT_7fff625e1486 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff62430230);
          DAT_7fff625e1486 = '\x01';
        }
        puVar3 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62430230);
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar3,(undefined *)0x0);
        *(undefined **)(puVar3 + 0x20) = self_00;
        *(undefined4 *)(puVar3 + 0x10) = 0;
        thunk_FUN_7fff5f491fd0();
        uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 7;
        return 1;
      }
    }
    break;
  case 7:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (self_00 != (undefined *)0x0) {
      if (self_00[0x30] != '\0') {
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                  (puRam00007fff624041d8,(undefined *)0x0);
        puVar3 = StageLoginDownloader_showDownloadError
                           (self_00,puRam00007fff62460890,(undefined *)0x0);
        uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 8;
        return 1;
      }
      lVar5 = FUN_7fff60c4bc00(_DAT_7fff6245adf0);
      if (lVar5 != 0) {
        uVar4 = FUN_7fff5f5898c0(lVar5,0,0);
        uVar4 = FUN_7fff618a87c0(self_00,uVar4,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 9;
        return 1;
      }
    }
    break;
  case 9:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (self_00 != (undefined *)0x0) {
      if (self_00[0x30] != '\0') {
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                  (puRam00007fff624041d8,(undefined *)0x0);
        puVar3 = StageLoginDownloader_showDownloadError
                           (self_00,puRam00007fff62460890,(undefined *)0x0);
        uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 10;
        return 1;
      }
      if (*(longlong *)(self_00 + 0x20) != 0) {
        func_0x7fff5f7f54d0();
        if (DAT_7fff625e1487 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff624303c0);
          DAT_7fff625e1487 = '\x01';
        }
        puVar3 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff624303c0);
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar3,(undefined *)0x0);
        *(undefined **)(puVar3 + 0x20) = self_00;
        *(undefined4 *)(puVar3 + 0x10) = 0;
        thunk_FUN_7fff5f491fd0();
        uVar4 = FUN_7fff618a87c0(self_00,puVar3,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 0xb;
        return 1;
      }
    }
    break;
  case 0xb:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (self_00 != (undefined *)0x0) {
      if (self_00[0x30] != '\0') {
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                  (puRam00007fff624042a8,(undefined *)0x0);
      }
      if (*(longlong *)(self_00 + 0x20) != 0) {
        func_0x7fff5f7f54d0(*(longlong *)(self_00 + 0x20),0);
        if (*(undefined **)(self_00 + 0x50) != (undefined *)0x0) {
          ResourceManager_RemoveAssetBundleTag
                    (*(undefined **)(self_00 + 0x50),_DAT_7fff62403cf8,0,(undefined *)0x0);
          lVar5 = FUN_7fff60c4bc00(_DAT_7fff6245af88);
          if (lVar5 != 0) {
            FUN_7fff5f592840(lVar5,0);
            lVar5 = FUN_7fff60c4bc00(uRam00007fff6245c4f8);
            if (lVar5 != 0) {
              FUN_7fff5f5e65f0(lVar5,4);
              if (*(longlong *)(self_00 + 0x58) != 0) {
                func_0x7fff603c57b0(*(longlong *)(self_00 + 0x58),0);
                return 0;
              }
            }
          }
        }
      }
    }
    break;
  default:
    return 0;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

