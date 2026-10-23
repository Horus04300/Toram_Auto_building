
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte AssetBundleManager_LoadCacheAssetBundle64_StateMachine_MoveNext
               (undefined *self,undefined *methodInfo)

{
  int iVar1;
  undefined4 uVar2;
  undefined *self_00;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  undefined1 uVar6;
  byte bVar7;
  longlong *methodInfo_00;
  longlong lVar8;
  undefined8 uVar9;
  undefined *puVar10;
  undefined *puVar11;
  undefined8 uVar12;
  undefined8 *puVar13;
  
  if (DAT_7fff625e1762 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62424670);
    FUN_7fff5f47d450(&DAT_7fff6243f4e0);
    FUN_7fff5f47d450(&DAT_7fff6244a438);
    FUN_7fff5f47d450(&DAT_7fff6244aa58);
    FUN_7fff5f47d450(&DAT_7fff6244abe0);
    FUN_7fff5f47d450(&DAT_7fff62472dd0);
    FUN_7fff5f47d450(&DAT_7fff62472aa0);
    FUN_7fff5f47d450(0x7fff62472f68);
    FUN_7fff5f47d450(&DAT_7fff62473030);
    FUN_7fff5f47d450(0x7fff62473100);
    FUN_7fff5f47d450(&DAT_7fff6242f200);
    FUN_7fff5f47d450(&DAT_7fff62461ac0);
    FUN_7fff5f47d450(&DAT_7fff62461df0);
    FUN_7fff5f47d450(&DAT_7fff62462120);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff62458858);
    FUN_7fff5f47d450(&DAT_7fff62459838);
    DAT_7fff625e1762 = '\x01';
  }
  iVar1 = *(int *)(self + 0x10);
  self_00 = *(undefined **)(self + 0x28);
  if (iVar1 == 0) {
    puVar13 = (undefined8 *)(self + 0x20);
    *(undefined8 *)(self + 0x50) = *(undefined8 *)(self + 0x20);
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    thunk_FUN_7fff5f491fd0();
    uVar12 = *puVar13;
    if (*(int *)(_DAT_7fff6243f4e0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff6243f4e0);
    }
    uVar12 = FUN_7fff60e71970(uVar12,**(undefined8 **)(_DAT_7fff6243f4e0 + 0xb8),0);
    *puVar13 = uVar12;
    thunk_FUN_7fff5f491fd0();
    if ((self_00 == (undefined *)0x0) || (*(longlong *)(self_00 + 0x30) == 0))
    goto LAB_7fff5f5ce0e1;
    cVar5 = FUN_7fff608b11a0(*(longlong *)(self_00 + 0x30),*puVar13,_DAT_7fff6244aa58);
    if (cVar5 == '\0') {
      return 0;
    }
    if (*(longlong *)(self_00 + 0x40) == 0) goto LAB_7fff5f5ce0e1;
    cVar5 = FUN_7fff608b11a0(*(longlong *)(self_00 + 0x40),*puVar13,_DAT_7fff6244a438);
    if (cVar5 != '\0') goto LAB_7fff5f5ce0a2;
    if (*(longlong *)(self_00 + 0x50) == 0) goto LAB_7fff5f5ce0e1;
    cVar5 = FUN_7fff60ae1480(*(longlong *)(self_00 + 0x50),*puVar13,_DAT_7fff62461df0);
    if (cVar5 != '\0') goto LAB_7fff5f5cdf3f;
  }
  else {
    if (iVar1 != 1) {
      if (iVar1 == 2) {
        *(undefined4 *)(self + 0x10) = 0xffffffff;
        if (*(longlong *)(self + 0x60) == 0) goto LAB_7fff5f5ce0e1;
        cVar5 = FUN_7fff60905130(*(longlong *)(self + 0x60),_DAT_7fff62473030);
        lVar3 = *(longlong *)(self + 0x60);
        if (cVar5 == '\0') {
          if ((lVar3 == 0) || (puVar10 = *(undefined **)(lVar3 + 0x10), self_00 == (undefined *)0x0)
             ) goto LAB_7fff5f5ce0e1;
          if (*(longlong *)(self_00 + 0x80) != 0) {
            lVar3 = *(longlong *)(self + 0x58);
            if (lVar3 == 0) goto LAB_7fff5f5ce0e1;
            if (*(char *)(lVar3 + 0x14) == '\0') {
              uVar2 = *(undefined4 *)(lVar3 + 0x10);
              uVar12 = *(undefined8 *)(self + 0x50);
              uVar9 = func_0x7fff5f44ff00(_DAT_7fff62424670);
              FUN_7fff5f5bc1d0(uVar9,puVar10,uVar2,uVar12,0);
              *(undefined8 *)(self + 0x68) = uVar9;
              thunk_FUN_7fff5f491fd0();
              lVar3 = *(longlong *)(self_00 + 0x80);
              if (lVar3 != 0) {
                uVar12 = (**(code **)(lVar3 + 0x18))
                                   (*(undefined8 *)(lVar3 + 0x40),*(undefined8 *)(self + 0x68),
                                    *(undefined8 *)(lVar3 + 0x28));
                uVar12 = FUN_7fff618a87c0(self_00,uVar12,0);
                *(undefined8 *)(self + 0x18) = uVar12;
                thunk_FUN_7fff5f491fd0();
                *(undefined4 *)(self + 0x10) = 3;
                return 1;
              }
              goto LAB_7fff5f5ce0e1;
            }
            goto LAB_7fff5f5cdd38;
          }
          goto LAB_7fff5f5cdd41;
        }
        if (lVar3 == 0) goto LAB_7fff5f5ce0e1;
        uVar12 = *(undefined8 *)(lVar3 + 0x10);
        if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        cVar5 = FUN_7fff618ab2e0(uVar12,0,0);
        if (cVar5 != '\0') {
          if ((*(longlong *)(self + 0x60) == 0) ||
             (lVar3 = *(longlong *)(*(longlong *)(self + 0x60) + 0x10), lVar3 == 0))
          goto LAB_7fff5f5ce0e1;
          FUN_7fff6187d7f0(lVar3,1,0);
          if (*(longlong *)(self + 0x60) == 0) goto LAB_7fff5f5ce0e1;
          func_0x7fff5f4d30e0(*(longlong *)(self + 0x60),0,_DAT_7fff62472dd0);
          FUN_7fff618af1f0(0);
        }
        methodInfo_00 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,2);
        lVar3 = *(longlong *)(self + 0x20);
        if (methodInfo_00 == (longlong *)0x0) goto LAB_7fff5f5ce0e1;
        if ((lVar3 != 0) &&
           (lVar8 = func_0x7fff5f47c7e0(lVar3,*(undefined8 *)(*methodInfo_00 + 0x40)), lVar8 == 0))
        {
          uVar12 = func_0x7fff5f47d0b0();
          FUN_7fff5f47d620(uVar12,0);
          pcVar4 = (code *)swi(3);
          bVar7 = (*pcVar4)();
          return bVar7;
        }
        if ((int)methodInfo_00[3] == 0) {
LAB_7fff5f5ce0e7:
          FUN_7fff5f47d650();
          pcVar4 = (code *)swi(3);
          bVar7 = (*pcVar4)();
          return bVar7;
        }
        methodInfo_00[4] = lVar3;
        thunk_FUN_7fff5f491fd0();
        if (*(longlong *)(self + 0x60) == 0) goto LAB_7fff5f5ce0e1;
        lVar3 = *(longlong *)(*(longlong *)(self + 0x60) + 0x20);
        if ((lVar3 != 0) &&
           (lVar8 = func_0x7fff5f47c7e0(lVar3,*(undefined8 *)(*methodInfo_00 + 0x40)), lVar8 == 0))
        {
          uVar12 = func_0x7fff5f47d0b0();
          FUN_7fff5f47d620(uVar12,0);
          pcVar4 = (code *)swi(3);
          bVar7 = (*pcVar4)();
          return bVar7;
        }
        if (*(uint *)(methodInfo_00 + 3) < 2) goto LAB_7fff5f5ce0e7;
        methodInfo_00[5] = lVar3;
        thunk_FUN_7fff5f491fd0();
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                  (_DAT_7fff62459838,(undefined *)methodInfo_00);
        if (self_00 == (undefined *)0x0) goto LAB_7fff5f5ce0e1;
      }
      else {
        if (iVar1 != 3) {
          return 0;
        }
        *(undefined4 *)(self + 0x10) = 0xffffffff;
        if (*(longlong *)(self + 0x68) == 0) goto LAB_7fff5f5ce0e1;
        puVar10 = *(undefined **)(*(longlong *)(self + 0x68) + 0x10);
        *(undefined8 *)(self + 0x68) = 0;
        thunk_FUN_7fff5f491fd0();
LAB_7fff5f5cdd38:
        if (self_00 == (undefined *)0x0) goto LAB_7fff5f5ce0e1;
LAB_7fff5f5cdd41:
        AssetBundleManager_AddAssetBundle
                  (self_00,*(undefined **)(self + 0x50),
                   (undefined *)(ulonglong)*(uint *)(self + 0x40),puVar10,
                   *(undefined **)(self + 0x48),(undefined *)0x0);
      }
      if (*(longlong *)(self_00 + 0x50) != 0) {
        FUN_7fff60ae6370(*(longlong *)(self_00 + 0x50),*(undefined8 *)(self + 0x20),
                         _DAT_7fff62462120);
        lVar3 = *(longlong *)(self + 0x30);
        if (lVar3 != 0) {
          if (*(longlong *)(self_00 + 0x40) == 0) goto LAB_7fff5f5ce0e1;
          uVar6 = FUN_7fff608b11a0(*(longlong *)(self_00 + 0x40),*(undefined8 *)(self + 0x20),
                                   _DAT_7fff6244a438);
          (**(code **)(lVar3 + 0x18))
                    (*(undefined8 *)(lVar3 + 0x40),uVar6,*(undefined8 *)(lVar3 + 0x28));
        }
        return 0;
      }
      goto LAB_7fff5f5ce0e1;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7fff5f5cdf3f:
    if ((self_00 == (undefined *)0x0) || (*(longlong *)(self_00 + 0x50) == 0))
    goto LAB_7fff5f5ce0e1;
    cVar5 = FUN_7fff60ae1480(*(longlong *)(self_00 + 0x50),*(undefined8 *)(self + 0x20),
                             _DAT_7fff62461df0);
    if (cVar5 != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
    if (*(longlong *)(self_00 + 0x40) == 0) goto LAB_7fff5f5ce0e1;
    cVar5 = FUN_7fff608b11a0(*(longlong *)(self_00 + 0x40),*(undefined8 *)(self + 0x20),
                             _DAT_7fff6244a438);
    if (cVar5 != '\0') {
LAB_7fff5f5ce0a2:
      lVar3 = *(longlong *)(self + 0x30);
      if (lVar3 == 0) {
        return 0;
      }
      (**(code **)(lVar3 + 0x18))(*(undefined8 *)(lVar3 + 0x40),1,*(undefined8 *)(lVar3 + 0x28));
      return 0;
    }
  }
  puVar13 = (undefined8 *)(self + 0x20);
  if (*(longlong *)(self_00 + 0x50) != 0) {
    FUN_7fff5f253100(*(longlong *)(self_00 + 0x50),*puVar13,_DAT_7fff62461ac0);
    if (*(longlong *)(self_00 + 0x30) != 0) {
      uVar12 = FUN_7fff608c0820(*(longlong *)(self_00 + 0x30),*puVar13,_DAT_7fff6244abe0);
      *(undefined8 *)(self + 0x58) = uVar12;
      thunk_FUN_7fff5f491fd0();
      puVar10 = (undefined *)FUN_7fff60e71970(*(undefined8 *)(self + 0x38),*puVar13,0);
      puVar11 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242f200);
      TextManagerDataBase__ctor(puVar11,_DAT_7fff62472aa0);
      *(undefined **)(self + 0x60) = puVar11;
      thunk_FUN_7fff5f491fd0();
      puVar11 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff62458858);
      if ((*(longlong *)(self + 0x58) != 0) && (puVar11 != (undefined *)0x0)) {
        puVar10 = DownloadManager_DownloadCacheAssetBundle
                            (puVar11,puVar10,*(int *)(*(longlong *)(self + 0x58) + 0x10),
                             *(undefined **)(self + 0x60),(undefined *)0x0);
        uVar12 = FUN_7fff618a87c0(self_00,puVar10,0);
        *(undefined8 *)(self + 0x18) = uVar12;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 2;
        return 1;
      }
    }
  }
LAB_7fff5f5ce0e1:
  FUN_7fff5f47d660();
  pcVar4 = (code *)swi(3);
  bVar7 = (*pcVar4)();
  return bVar7;
}

