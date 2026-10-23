
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte StageLoginDownloader_Start_StateMachine_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  bool bVar3;
  byte bVar4;
  undefined8 uVar5;
  longlong *plVar6;
  longlong *plVar7;
  undefined *puVar8;
  
  if (DAT_7fff625e148e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62459938);
    FUN_7fff5f47d450(&DAT_7fff6245bdd8);
    FUN_7fff5f47d450(&DAT_7fff6245a460);
    FUN_7fff5f47d450(&DAT_7fff62468308);
    FUN_7fff5f47d450(&DAT_7fff62406568);
    DAT_7fff625e148e = '\x01';
  }
  lVar1 = *(longlong *)(self + 0x20);
  if (*(int *)(self + 0x10) == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    uVar5 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if (lVar1 != 0) {
      *(undefined8 *)(lVar1 + 0x58) = uVar5;
      thunk_FUN_7fff5f491fd0();
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        FUN_7fff5f7f6060(*(longlong *)(lVar1 + 0x20),0);
        uVar5 = FUN_7fff60c4bc00(_DAT_7fff6245a460);
        *(undefined8 *)(lVar1 + 0x40) = uVar5;
        thunk_FUN_7fff5f491fd0();
        if (*(undefined **)(lVar1 + 0x40) != (undefined *)0x0) {
          plVar6 = (longlong *)
                   LocalizeManager_Get(*(undefined **)(lVar1 + 0x40),(undefined *)0x0,
                                       (undefined *)0x0);
          if (plVar6 == (longlong *)0x0) {
            *(undefined8 *)(lVar1 + 0x48) = 0;
          }
          else {
            if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7fff62468308 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar6 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7fff62468308 + 0x130) * 8) != _DAT_7fff62468308)) {
              bVar3 = false;
            }
            else {
              bVar3 = true;
            }
            plVar7 = (longlong *)0x0;
            if (bVar3) {
              plVar7 = plVar6;
            }
            *(longlong **)(lVar1 + 0x48) = plVar7;
          }
          thunk_FUN_7fff5f491fd0();
          if (*(undefined **)(lVar1 + 0x40) != (undefined *)0x0) {
            puVar8 = LocalizeManager_GetLocalizeCode(*(undefined **)(lVar1 + 0x40),(undefined *)0x0)
            ;
            *(undefined **)(lVar1 + 0x68) = puVar8;
            thunk_FUN_7fff5f491fd0();
            uVar5 = FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
            *(undefined8 *)(lVar1 + 0x50) = uVar5;
            thunk_FUN_7fff5f491fd0();
            if (DAT_7fff625e1482 == '\0') {
              FUN_7fff5f47d450(&DAT_7fff6242ffd8);
              DAT_7fff625e1482 = '\x01';
            }
            puVar8 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242ffd8);
            StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                      (puVar8,(undefined *)0x0);
            *(longlong *)(puVar8 + 0x20) = lVar1;
            *(undefined4 *)(puVar8 + 0x10) = 0;
            thunk_FUN_7fff5f491fd0();
            FUN_7fff618a87c0(lVar1,puVar8,0);
            uVar5 = func_0x7fff5f44ff00(_DAT_7fff62406568);
            FUN_7fff618b74f0(uVar5,_DAT_7fff61b52b40,0);
            *(undefined8 *)(self + 0x18) = uVar5;
            thunk_FUN_7fff5f491fd0();
            *(undefined4 *)(self + 0x10) = 1;
            return 1;
          }
        }
      }
    }
  }
  else {
    if (*(int *)(self + 0x10) != 1) {
      return 0;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if ((lVar1 != 0) && (*(longlong *)(lVar1 + 0x20) != 0)) {
      FUN_7fff5f7f54f0(*(longlong *)(lVar1 + 0x20),0);
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        FUN_7fff5f7f5ec0(*(longlong *)(lVar1 + 0x20),7);
        if (*(longlong *)(lVar1 + 0x20) != 0) {
          *(undefined1 *)(*(longlong *)(lVar1 + 0x20) + 0x68) = 1;
          if (*(longlong *)(lVar1 + 0x20) != 0) {
            FUN_7fff5f7f6060(*(longlong *)(lVar1 + 0x20),1,0);
            return 0;
          }
        }
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  bVar4 = (*pcVar2)();
  return bVar4;
}

