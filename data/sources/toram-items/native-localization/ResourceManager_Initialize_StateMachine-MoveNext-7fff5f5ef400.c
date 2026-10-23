
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ResourceManager_Initialize_StateMachine_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined8 uVar9;
  undefined *puVar10;
  undefined *verFile;
  undefined *result;
  undefined8 uStackX_8;
  undefined8 uStackX_18;
  
  if (DAT_7fff625e1892 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fb4c8);
    FUN_7fff5f47d450(&DAT_7fff62474d00);
    FUN_7fff5f47d450(&DAT_7fff62472b68);
    FUN_7fff5f47d450(&DAT_7fff62472aa0);
    FUN_7fff5f47d450(&DAT_7fff62473030);
    FUN_7fff5f47d450(0x7fff62473100);
    FUN_7fff5f47d450(&DAT_7fff6242f200);
    FUN_7fff5f47d450(&DAT_7fff6246a948);
    FUN_7fff5f47d450(&DAT_7fff6240a688);
    FUN_7fff5f47d450(&DAT_7fff6241f488);
    FUN_7fff5f47d450(&DAT_7fff624405a0);
    FUN_7fff5f47d450(&DAT_7fff6245b758);
    FUN_7fff5f47d450(&DAT_7fff624105a0);
    FUN_7fff5f47d450(&DAT_7fff62401a10);
    FUN_7fff5f47d450(&DAT_7fff624104d0);
    FUN_7fff5f47d450(&DAT_7fff6245b5c0);
    DAT_7fff625e1892 = '\x01';
  }
  iVar6 = *(int *)(self + 0x10);
  lVar1 = *(longlong *)(self + 0x20);
  if (iVar6 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    puVar8 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6241f488);
    TextManagerDataBase__ctor(puVar8,(undefined *)0x0);
    *(undefined **)(self + 0x30) = puVar8;
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0x30) == 0) {
LAB_7fff5f5ef922:
      FUN_7fff5f47d660();
      pcVar3 = (code *)swi(3);
      bVar5 = (*pcVar3)();
      return bVar5;
    }
    *(undefined1 *)(*(longlong *)(self + 0x30) + 0x10) = 0;
    if (lVar1 == 0) goto LAB_7fff5f5ef922;
    *(undefined8 *)(lVar1 + 0x38) = *(undefined8 *)(self + 0x28);
    thunk_FUN_7fff5f491fd0();
    if (*(int *)(_DAT_7fff62474d00 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    uStackX_8 = FUN_7fff61006310(0);
    uStackX_18 = FUN_7fff610065a0(&uStackX_8,0);
    uVar9 = FUN_7fff6100f660(&uStackX_18,0);
    uVar9 = FUN_7fff60e71970(_DAT_7fff624405a0,uVar9,0);
    puVar8 = *(undefined **)(lVar1 + 0x20);
    puVar10 = *(undefined **)(lVar1 + 0x38);
    verFile = (undefined *)FUN_7fff60e71970(_DAT_7fff6245b758,uVar9,0);
    uVar9 = *(undefined8 *)(self + 0x30);
    result = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
    FUN_7fff60739100(result,uVar9,_DAT_7fff6240a688,0);
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f5ef922;
    puVar8 = AssetBundleManager_Initialize(puVar8,puVar10,verFile,result,(undefined *)0x0);
    uVar9 = FUN_7fff618a87c0(lVar1,puVar8,0);
    *(undefined8 *)(self + 0x18) = uVar9;
    thunk_FUN_7fff5f491fd0();
    *(undefined4 *)(self + 0x10) = 1;
LAB_7fff5f5ef684:
    bVar5 = 1;
  }
  else {
    if (iVar6 == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5f5ef922;
      if (*(char *)(*(longlong *)(self + 0x30) + 0x10) != '\0') {
        puVar8 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242f200);
        TextManagerDataBase__ctor(puVar8,_DAT_7fff62472aa0);
        *(undefined **)(self + 0x40) = puVar8;
        thunk_FUN_7fff5f491fd0();
        puVar8 = ResourceManager_get_CommonAssetbundleName((undefined *)0x0);
        *(undefined **)(self + 0x48) = puVar8;
        thunk_FUN_7fff5f491fd0();
        if (lVar1 == 0) goto LAB_7fff5f5ef922;
        puVar8 = *(undefined **)(lVar1 + 0x30);
        puVar10 = (undefined *)
                  FUN_7fff60e74db0(_DAT_7fff62401a10,*(undefined8 *)(lVar1 + 0x38),
                                   *(undefined8 *)(self + 0x48));
        if (puVar8 == (undefined *)0x0) goto LAB_7fff5f5ef922;
        puVar8 = DownloadManager_DownloadAssetBundle
                           (puVar8,puVar10,*(undefined **)(self + 0x40),(undefined *)0x0);
        uVar9 = FUN_7fff618a87c0(lVar1,puVar8,0);
        *(undefined8 *)(self + 0x18) = uVar9;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 2;
        goto LAB_7fff5f5ef684;
      }
      StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                (_DAT_7fff6245b5c0,(undefined *)0x0);
      lVar1 = *(longlong *)(self + 0x38);
      if (lVar1 != 0) {
        if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5f5ef922;
        (**(code **)(lVar1 + 0x18))
                  (*(undefined8 *)(lVar1 + 0x40),*(undefined1 *)(*(longlong *)(self + 0x30) + 0x10),
                   *(undefined8 *)(lVar1 + 0x28));
      }
    }
    else {
      if (iVar6 == 2) {
        *(undefined4 *)(self + 0x10) = 0xffffffff;
        if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff5f5ef922;
        cVar4 = FUN_7fff60905130();
        if (cVar4 != '\0') {
          StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                    (_DAT_7fff624105a0,(undefined *)0x0);
          lVar1 = *(longlong *)(self + 0x38);
          if (lVar1 != 0) {
            (**(code **)(lVar1 + 0x18))
                      (*(undefined8 *)(lVar1 + 0x40),0,*(undefined8 *)(lVar1 + 0x28));
          }
          if (*(longlong *)(self + 0x40) != 0) {
            FUN_7fff60904b60(*(longlong *)(self + 0x40),_DAT_7fff62472b68);
            return 0;
          }
          goto LAB_7fff5f5ef922;
        }
        if (((*(longlong *)(self + 0x40) == 0) ||
            (lVar2 = *(longlong *)(*(longlong *)(self + 0x40) + 0x10), lVar2 == 0)) ||
           (plVar7 = (longlong *)FUN_7fff6187d520(lVar2,_DAT_7fff624104d0,0),
           plVar7 == (longlong *)0x0)) goto LAB_7fff5f5ef922;
        if (((*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7fff6246a948 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plVar7 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7fff6246a948 + 0x130) * 8) != _DAT_7fff6246a948)) ||
           ((puVar8 = (undefined *)FUN_7fff618b0e20(plVar7,0), lVar1 == 0 ||
            (*(undefined **)(lVar1 + 0x20) == (undefined *)0x0)))) goto LAB_7fff5f5ef922;
        iVar6 = AssetBundleManager_GetVersion
                          (*(undefined **)(lVar1 + 0x20),*(undefined **)(self + 0x48),
                           (undefined *)0x0);
        ResourceManager_AssetDecrypt(puVar8,iVar6,(undefined *)0x0);
        FUN_7fff618af180(plVar7,0);
        if ((*(longlong *)(self + 0x40) == 0) ||
           (lVar2 = *(longlong *)(*(longlong *)(self + 0x40) + 0x10), lVar2 == 0))
        goto LAB_7fff5f5ef922;
        FUN_7fff6187d7f0(lVar2,1);
        if (*(undefined **)(lVar1 + 0x20) == (undefined *)0x0) goto LAB_7fff5f5ef922;
        puVar8 = AssetBundleManager_AddAssetBundleBuffer
                           (*(undefined **)(lVar1 + 0x20),*(undefined **)(self + 0x48),
                            (undefined *)0x0,puVar8,(undefined *)0x0);
        uVar9 = FUN_7fff618a87c0(lVar1,puVar8,0);
        *(undefined8 *)(self + 0x18) = uVar9;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 3;
        goto LAB_7fff5f5ef684;
      }
      if (iVar6 == 3) {
        lVar1 = *(longlong *)(self + 0x38);
        *(undefined4 *)(self + 0x10) = 0xffffffff;
        if (lVar1 != 0) {
          (**(code **)(lVar1 + 0x18))(*(undefined8 *)(lVar1 + 0x40),1,*(undefined8 *)(lVar1 + 0x28))
          ;
          return 0;
        }
      }
    }
    bVar5 = 0;
  }
  return bVar5;
}

