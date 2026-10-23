
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte StageLoginDownloader_initLocalizeData_StateMachine_MoveNext
               (undefined *self,undefined *methodInfo)

{
  int iVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  byte bVar5;
  longlong *plVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  longlong lVar11;
  undefined8 uVar12;
  
  if (DAT_7fff625e1493 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fb4c8);
    FUN_7fff5f47d450(&DAT_7fff62472440);
    FUN_7fff5f47d450(&DAT_7fff62472370);
    FUN_7fff5f47d450(&DAT_7fff62472908);
    FUN_7fff5f47d450(0x7fff624729d0);
    FUN_7fff5f47d450(&DAT_7fff6242f138);
    FUN_7fff5f47d450(&DAT_7fff62458858);
    FUN_7fff5f47d450(&DAT_7fff6245ce88);
    FUN_7fff5f47d450(&DAT_7fff62421680);
    FUN_7fff5f47d450(&DAT_7fff62421750);
    FUN_7fff5f47d450(&DAT_7fff6242fbf0);
    FUN_7fff5f47d450(&DAT_7fff6244e880);
    FUN_7fff5f47d450(&DAT_7fff624589b0);
    FUN_7fff5f47d450(&DAT_7fff6243f200);
    FUN_7fff5f47d450(&DAT_7fff62457e78);
    FUN_7fff5f47d450(&DAT_7fff6242d448);
    FUN_7fff5f47d450(&DAT_7fff623f8ac0);
    FUN_7fff5f47d450(&DAT_7fff62403cf8);
    FUN_7fff5f47d450(&DAT_7fff6245f238);
    FUN_7fff5f47d450(&DAT_7fff62415610);
    FUN_7fff5f47d450(&DAT_7fff6243a910);
    FUN_7fff5f47d450(&DAT_7fff624252d0);
    FUN_7fff5f47d450(&DAT_7fff62405ed8);
    FUN_7fff5f47d450(&DAT_7fff62434bc8);
    FUN_7fff5f47d450(&DAT_7fff624255f0);
    FUN_7fff5f47d450(&DAT_7fff6243a788);
    FUN_7fff5f47d450(&DAT_7fff62412558);
    FUN_7fff5f47d450(&DAT_7fff62460488);
    FUN_7fff5f47d450(&DAT_7fff62406b00);
    FUN_7fff5f47d450(&DAT_7fff62446cb0);
    FUN_7fff5f47d450(&DAT_7fff62478838);
    DAT_7fff625e1493 = '\x01';
  }
  iVar1 = *(int *)(self + 0x10);
  lVar2 = *(longlong *)(self + 0x20);
  if (iVar1 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    puVar8 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242fbf0);
    StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar8,(undefined *)0x0);
    *(undefined **)(self + 0x28) = puVar8;
    thunk_FUN_7fff5f491fd0();
    StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
              (_DAT_7fff62405ed8,(undefined *)0x0);
    if ((*(longlong *)(self + 0x28) == 0) ||
       (*(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 0, lVar2 == 0)) {
LAB_7fff5f551fb3:
      FUN_7fff5f47d660();
      pcVar3 = (code *)swi(3);
      bVar5 = (*pcVar3)();
      return bVar5;
    }
    puVar8 = *(undefined **)(lVar2 + 0x50);
    puVar10 = (undefined *)
              FUN_7fff60e71650(_DAT_7fff62446cb0,*(undefined8 *)(lVar2 + 0x68),_DAT_7fff624255f0,0);
    uVar12 = *(undefined8 *)(self + 0x28);
    puVar7 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
    FUN_7fff60739100(puVar7,uVar12,_DAT_7fff62421680,0);
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f551fb3;
    puVar8 = ResourceManager_LoadAssetBundle
                       (puVar8,puVar10,(undefined *)0x1,_DAT_7fff62403cf8,puVar7,(undefined *)0x0);
    uVar12 = FUN_7fff618a87c0(lVar2,puVar8,0);
    *(undefined8 *)(self + 0x18) = uVar12;
    thunk_FUN_7fff5f491fd0();
    *(undefined4 *)(self + 0x10) = 1;
LAB_7fff5f551d8c:
    bVar5 = 1;
  }
  else {
    if (iVar1 == 1) {
      lVar11 = *(longlong *)(self + 0x28);
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (lVar11 == 0) goto LAB_7fff5f551fb3;
      if (*(char *)(lVar11 + 0x10) != '\0') {
        *(undefined1 *)(lVar11 + 0x10) = 0;
        if (lVar2 == 0) goto LAB_7fff5f551fb3;
        uVar12 = FUN_7fff60e71050(_DAT_7fff62446cb0,*(undefined8 *)(lVar2 + 0x68),_DAT_7fff624252d0,
                                  *(undefined8 *)(lVar2 + 0x68),0);
        *(undefined8 *)(self + 0x30) = uVar12;
        thunk_FUN_7fff5f491fd0();
        uVar12 = FUN_7fff60e71970(_DAT_7fff6242d448,*(undefined8 *)(lVar2 + 0x68),0);
        *(undefined8 *)(self + 0x38) = uVar12;
        thunk_FUN_7fff5f491fd0();
        puVar8 = *(undefined **)(lVar2 + 0x50);
        puVar10 = *(undefined **)(self + 0x30);
        uVar12 = *(undefined8 *)(self + 0x28);
        puVar7 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
        FUN_7fff60739100(puVar7,uVar12,_DAT_7fff62421750,0);
        if (puVar8 == (undefined *)0x0) goto LAB_7fff5f551fb3;
        puVar8 = ResourceManager_LoadAssetBundle
                           (puVar8,puVar10,(undefined *)0x1,_DAT_7fff62403cf8,puVar7,
                            (undefined *)0x0);
        uVar12 = FUN_7fff618a87c0(lVar2,puVar8,0);
        *(undefined8 *)(self + 0x18) = uVar12;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 2;
        goto LAB_7fff5f551d8c;
      }
      if (lVar2 == 0) goto LAB_7fff5f551fb3;
LAB_7fff5f551eb7:
      *(undefined1 *)(lVar2 + 0x30) = 1;
    }
    else if (iVar1 == 2) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if ((*(longlong *)(self + 0x28) == 0) || (lVar2 == 0)) goto LAB_7fff5f551fb3;
      if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\0') goto LAB_7fff5f551eb7;
      if (*(char *)(lVar2 + 0x30) == '\0') {
        if (*(undefined **)(lVar2 + 0x40) == (undefined *)0x0) goto LAB_7fff5f551fb3;
        plVar6 = (longlong *)
                 LocalizeManager_Get(*(undefined **)(lVar2 + 0x40),(undefined *)0x0,(undefined *)0x0
                                    );
        puVar8 = *(undefined **)(lVar2 + 0x50);
        puVar10 = *(undefined **)(self + 0x30);
        puVar7 = (undefined *)FUN_7fff60e71970(_DAT_7fff62415610,*(undefined8 *)(self + 0x38),0);
        if ((puVar8 == (undefined *)0x0) ||
           (puVar8 = ResourceManager_GetAssetBinary(puVar8,puVar10,puVar7,(undefined *)0x0),
           plVar6 == (longlong *)0x0)) goto LAB_7fff5f551fb3;
        (**(code **)(*plVar6 + 0x198))(plVar6,puVar8,*(undefined8 *)(*plVar6 + 0x1a0));
        puVar8 = *(undefined **)(lVar2 + 0x50);
        puVar10 = *(undefined **)(self + 0x30);
        puVar7 = (undefined *)FUN_7fff60e71970(_DAT_7fff6245f238,*(undefined8 *)(self + 0x38),0);
        if (puVar8 == (undefined *)0x0) goto LAB_7fff5f551fb3;
        puVar8 = ResourceManager_GetAssetBinary(puVar8,puVar10,puVar7,(undefined *)0x0);
        if (puVar8 != (undefined *)0x0) {
          (**(code **)(*plVar6 + 0x198))(plVar6,puVar8,*(undefined8 *)(*plVar6 + 0x1a0));
        }
        puVar8 = *(undefined **)(lVar2 + 0x50);
        puVar10 = *(undefined **)(self + 0x30);
        puVar7 = (undefined *)FUN_7fff60e71970(_DAT_7fff62460488,*(undefined8 *)(self + 0x38),0);
        if (puVar8 == (undefined *)0x0) goto LAB_7fff5f551fb3;
        puVar8 = ResourceManager_GetAssetBinary(puVar8,puVar10,puVar7,(undefined *)0x0);
        if (puVar8 != (undefined *)0x0) {
          (**(code **)(*plVar6 + 0x198))(plVar6,puVar8,*(undefined8 *)(*plVar6 + 0x1a0));
        }
        puVar8 = *(undefined **)(lVar2 + 0x40);
        puVar10 = *(undefined **)(lVar2 + 0x50);
        puVar7 = *(undefined **)(self + 0x30);
        puVar9 = (undefined *)FUN_7fff60e71970(_DAT_7fff62434bc8,*(undefined8 *)(self + 0x38),0);
        if ((puVar10 == (undefined *)0x0) ||
           (puVar10 = ResourceManager_GetAssetBinary(puVar10,puVar7,puVar9,(undefined *)0x0),
           puVar8 == (undefined *)0x0)) goto LAB_7fff5f551fb3;
        LocalizeManager_Initialize(puVar8,puVar10,(undefined *)0x1,(undefined *)0x0);
        puVar8 = *(undefined **)(lVar2 + 0x40);
        puVar10 = *(undefined **)(lVar2 + 0x50);
        puVar7 = *(undefined **)(self + 0x30);
        puVar9 = (undefined *)FUN_7fff60e71970(_DAT_7fff6243a910,*(undefined8 *)(self + 0x38),0);
        if ((puVar10 == (undefined *)0x0) ||
           (puVar10 = ResourceManager_GetAssetBinary(puVar10,puVar7,puVar9,(undefined *)0x0),
           puVar8 == (undefined *)0x0)) goto LAB_7fff5f551fb3;
        LocalizeManager_Initialize(puVar8,puVar10,(undefined *)0xe,(undefined *)0x0);
        puVar8 = *(undefined **)(lVar2 + 0x40);
        puVar10 = *(undefined **)(lVar2 + 0x50);
        puVar7 = *(undefined **)(self + 0x30);
        puVar9 = (undefined *)FUN_7fff60e71970(_DAT_7fff62478838,*(undefined8 *)(self + 0x38),0);
        if ((puVar10 == (undefined *)0x0) ||
           (puVar10 = ResourceManager_GetAssetBinary(puVar10,puVar7,puVar9,(undefined *)0x0),
           puVar8 == (undefined *)0x0)) goto LAB_7fff5f551fb3;
        LocalizeManager_Initialize(puVar8,puVar10,(undefined *)0x2,(undefined *)0x0);
        puVar8 = *(undefined **)(lVar2 + 0x40);
        puVar10 = *(undefined **)(lVar2 + 0x50);
        puVar7 = *(undefined **)(self + 0x30);
        puVar9 = (undefined *)FUN_7fff60e71970(_DAT_7fff6243f200,*(undefined8 *)(self + 0x38),0);
        if ((puVar10 == (undefined *)0x0) ||
           (puVar10 = ResourceManager_GetAssetBinary(puVar10,puVar7,puVar9,(undefined *)0x0),
           puVar8 == (undefined *)0x0)) goto LAB_7fff5f551fb3;
        LocalizeManager_Initialize(puVar8,puVar10,(undefined *)0x7,(undefined *)0x0);
        puVar8 = *(undefined **)(lVar2 + 0x40);
        puVar10 = *(undefined **)(lVar2 + 0x50);
        puVar7 = *(undefined **)(self + 0x30);
        puVar9 = (undefined *)FUN_7fff60e71970(_DAT_7fff6243a788,*(undefined8 *)(self + 0x38),0);
        if ((puVar10 == (undefined *)0x0) ||
           (puVar10 = ResourceManager_GetAssetBinary(puVar10,puVar7,puVar9,(undefined *)0x0),
           puVar8 == (undefined *)0x0)) goto LAB_7fff5f551fb3;
        LocalizeManager_Initialize(puVar8,puVar10,(undefined *)0x3,(undefined *)0x0);
        puVar8 = *(undefined **)(lVar2 + 0x40);
        puVar10 = *(undefined **)(lVar2 + 0x50);
        puVar7 = *(undefined **)(self + 0x30);
        puVar9 = (undefined *)FUN_7fff60e71970(_DAT_7fff62457e78,*(undefined8 *)(self + 0x38),0);
        if ((puVar10 == (undefined *)0x0) ||
           (puVar10 = ResourceManager_GetAssetBinary(puVar10,puVar7,puVar9,(undefined *)0x0),
           puVar8 == (undefined *)0x0)) goto LAB_7fff5f551fb3;
        LocalizeManager_Initialize(puVar8,puVar10,(undefined *)0x4,(undefined *)0x0);
        puVar8 = *(undefined **)(lVar2 + 0x40);
        puVar10 = *(undefined **)(lVar2 + 0x50);
        puVar7 = *(undefined **)(self + 0x30);
        puVar9 = (undefined *)FUN_7fff60e71970(_DAT_7fff6244e880,*(undefined8 *)(self + 0x38),0);
        if ((puVar10 == (undefined *)0x0) ||
           (puVar10 = ResourceManager_GetAssetBinary(puVar10,puVar7,puVar9,(undefined *)0x0),
           puVar8 == (undefined *)0x0)) goto LAB_7fff5f551fb3;
        LocalizeManager_Initialize(puVar8,puVar10,(undefined *)0x8,(undefined *)0x0);
        if (*(longlong *)(lVar2 + 0x40) == 0) goto LAB_7fff5f551fb3;
        lVar11 = *(longlong *)(*(longlong *)(lVar2 + 0x40) + 0x28);
        puVar8 = *(undefined **)(lVar2 + 0x50);
        puVar10 = *(undefined **)(self + 0x30);
        puVar7 = (undefined *)FUN_7fff60e71970(_DAT_7fff623f8ac0,*(undefined8 *)(self + 0x38),0);
        if (puVar8 == (undefined *)0x0) goto LAB_7fff5f551fb3;
        puVar7 = ResourceManager_GetAssetBinary(puVar8,puVar10,puVar7,(undefined *)0x0);
        puVar8 = *(undefined **)(lVar2 + 0x50);
        puVar10 = *(undefined **)(self + 0x30);
        puVar9 = (undefined *)FUN_7fff60e71970(_DAT_7fff62406b00,*(undefined8 *)(self + 0x38),0);
        if ((puVar8 == (undefined *)0x0) ||
           (puVar8 = ResourceManager_GetAssetBinary(puVar8,puVar10,puVar9,(undefined *)0x0),
           lVar11 == 0)) goto LAB_7fff5f551fb3;
        FUN_7fff5f5d1b20(lVar11,puVar7,puVar8);
        puVar8 = *(undefined **)(lVar2 + 0x40);
        puVar10 = *(undefined **)(lVar2 + 0x50);
        puVar7 = *(undefined **)(self + 0x30);
        puVar9 = (undefined *)FUN_7fff60e71970(_DAT_7fff624589b0,*(undefined8 *)(self + 0x38),0);
        if ((puVar10 == (undefined *)0x0) ||
           (puVar10 = ResourceManager_GetAssetBinary(puVar10,puVar7,puVar9,(undefined *)0x0),
           puVar8 == (undefined *)0x0)) goto LAB_7fff5f551fb3;
        LocalizeManager_Initialize(puVar8,puVar10,(undefined *)0xb,(undefined *)0x0);
        puVar8 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242f138);
        TextManagerDataBase__ctor(puVar8,_DAT_7fff62472370);
        *(undefined **)(self + 0x40) = puVar8;
        thunk_FUN_7fff5f491fd0();
        puVar8 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff62458858);
        lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245ce88);
        if (lVar11 == 0) goto LAB_7fff5f551fb3;
        uVar12 = FUN_7fff5f5e7dc0(lVar11,0);
        puVar10 = (undefined *)FUN_7fff60e71970(uVar12,_DAT_7fff62412558,0);
        if (puVar8 == (undefined *)0x0) goto LAB_7fff5f551fb3;
        puVar8 = DownloadManager_DownloadBinary
                           (puVar8,puVar10,*(undefined **)(self + 0x40),(undefined *)0x0);
        uVar12 = FUN_7fff618a87c0(lVar2,puVar8,0);
        *(undefined8 *)(self + 0x18) = uVar12;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 3;
        goto LAB_7fff5f551d8c;
      }
    }
    else if (iVar1 == 3) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (*(longlong *)(self + 0x40) != 0) {
        cVar4 = FUN_7fff60905130(*(longlong *)(self + 0x40),_DAT_7fff62472908);
        if (cVar4 != '\0') {
LAB_7fff5f55183e:
          *(undefined8 *)(self + 0x40) = 0;
          thunk_FUN_7fff5f491fd0();
          *(undefined8 *)(self + 0x40) = 0;
          thunk_FUN_7fff5f491fd0();
          return 0;
        }
        if ((((lVar2 != 0) && (*(longlong *)(lVar2 + 0x40) != 0)) &&
            (*(longlong *)(self + 0x40) != 0)) &&
           (lVar2 = *(longlong *)(*(longlong *)(lVar2 + 0x40) + 0x28), lVar2 != 0)) {
          FUN_7fff5f5d1810(lVar2,*(undefined8 *)(*(longlong *)(self + 0x40) + 0x10),0);
          if (*(longlong *)(self + 0x40) != 0) {
            FUN_7fff60904b60(*(longlong *)(self + 0x40),_DAT_7fff62472440);
            goto LAB_7fff5f55183e;
          }
        }
      }
      goto LAB_7fff5f551fb3;
    }
    bVar5 = 0;
  }
  return bVar5;
}

