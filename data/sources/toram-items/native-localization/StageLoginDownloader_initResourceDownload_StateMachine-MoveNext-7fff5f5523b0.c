
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte StageLoginDownloader_initResourceDownload_StateMachine_MoveNext
               (undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  byte bVar4;
  undefined *puVar5;
  undefined *puVar6;
  longlong lVar7;
  undefined8 uVar8;
  uint uVar9;
  
  if (DAT_7fff625e1495 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fb4c8);
    FUN_7fff5f47d450(&DAT_7fff62461b90);
    FUN_7fff5f47d450(&DAT_7fff624621e8);
    FUN_7fff5f47d450(&DAT_7fff62461860);
    FUN_7fff5f47d450(&DAT_7fff6247b650);
    FUN_7fff5f47d450(&DAT_7fff6240a800);
    FUN_7fff5f47d450(&DAT_7fff62421410);
    FUN_7fff5f47d450(&DAT_7fff624214e0);
    FUN_7fff5f47d450(&DAT_7fff6242fa60);
    FUN_7fff5f47d450(&DAT_7fff6242f998);
    FUN_7fff5f47d450(&DAT_7fff62406078);
    FUN_7fff5f47d450(&DAT_7fff6241f588);
    DAT_7fff625e1495 = '\x01';
  }
  lVar1 = *(longlong *)(self + 0x20);
  if (*(int *)(self + 0x10) != 0) {
    if (*(int *)(self + 0x10) == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5f552703;
      if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\0') {
        if (lVar1 == 0) goto LAB_7fff5f552703;
        *(undefined1 *)(lVar1 + 0x30) = 1;
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                  (_DAT_7fff6241f588,(undefined *)0x0);
      }
    }
    return 0;
  }
  *(undefined4 *)(self + 0x10) = 0xffffffff;
  puVar5 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242fa60);
  StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar5,(undefined *)0x0);
  *(undefined **)(self + 0x28) = puVar5;
  thunk_FUN_7fff5f491fd0();
  StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
            (_DAT_7fff62406078,(undefined *)0x0);
  puVar5 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6247b650);
  FUN_7fff60a943d0(puVar5,_DAT_7fff62461860);
  if (lVar1 != 0) {
    lVar2 = *(longlong *)(lVar1 + 0x60);
    uVar9 = 0;
    if (lVar2 != 0) {
      for (; (int)uVar9 < *(int *)(lVar2 + 0x18); uVar9 = uVar9 + 1) {
        if (*(uint *)(lVar2 + 0x18) <= uVar9) {
          FUN_7fff5f47d650();
          pcVar3 = (code *)swi(3);
          bVar4 = (*pcVar3)();
          return bVar4;
        }
        if (*(undefined **)(lVar1 + 0x50) == (undefined *)0x0) goto LAB_7fff5f552703;
        puVar6 = ResourceManager_GetAssetNamesContains
                           (*(undefined **)(lVar1 + 0x50),
                            *(undefined **)(lVar2 + 0x20 + (longlong)(int)uVar9 * 8),
                            (undefined *)0x0);
        if (*(int *)(_DAT_7fff6242f998 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        lVar7 = *(longlong *)(*(longlong *)(_DAT_7fff6242f998 + 0xb8) + 8);
        if (lVar7 == 0) {
          if (*(int *)(_DAT_7fff6242f998 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          uVar8 = **(undefined8 **)(_DAT_7fff6242f998 + 0xb8);
          lVar7 = func_0x7fff5f44ff00(_DAT_7fff6240a800);
          FUN_7fff60bd9cc0(lVar7,uVar8,_DAT_7fff62421410);
          *(longlong *)(*(longlong *)(_DAT_7fff6242f998 + 0xb8) + 8) = lVar7;
          thunk_FUN_7fff5f491fd0();
        }
        if ((puVar6 == (undefined *)0x0) ||
           (FUN_7fff60ae5b60(puVar6,lVar7,_DAT_7fff624621e8), puVar5 == (undefined *)0x0))
        goto LAB_7fff5f552703;
        func_0x7fff60adf9c0(puVar5,puVar6);
      }
      if (*(longlong *)(self + 0x28) != 0) {
        *(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 0;
        if (*(undefined **)(lVar1 + 0x50) != (undefined *)0x0) {
          ResourceManager_CreateDownloadList(*(undefined **)(lVar1 + 0x50),puVar5,(undefined *)0x0);
          puVar5 = *(undefined **)(lVar1 + 0x50);
          uVar8 = *(undefined8 *)(self + 0x28);
          puVar6 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
          FUN_7fff60739100(puVar6,uVar8,_DAT_7fff624214e0,0);
          if (puVar5 != (undefined *)0x0) {
            puVar5 = ResourceManager_UpdateResources(puVar5,puVar6,(undefined *)0x0);
            uVar8 = FUN_7fff618a87c0(lVar1,puVar5,0);
            *(undefined8 *)(self + 0x18) = uVar8;
            thunk_FUN_7fff5f491fd0();
            *(undefined4 *)(self + 0x10) = 1;
            return 1;
          }
        }
      }
    }
  }
LAB_7fff5f552703:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  bVar4 = (*pcVar3)();
  return bVar4;
}

