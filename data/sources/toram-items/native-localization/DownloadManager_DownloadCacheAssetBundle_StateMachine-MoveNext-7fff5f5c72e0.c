
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte DownloadManager_DownloadCacheAssetBundle_StateMachine_MoveNext
               (undefined *self,undefined *methodInfo)

{
  float timeout;
  undefined *self_00;
  code *pcVar1;
  char cVar2;
  undefined1 uVar3;
  byte bVar4;
  int iVar5;
  longlong *methodInfo_00;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined *puVar9;
  undefined *timeoutCallback;
  undefined8 uVar10;
  int iVar11;
  undefined *apuStackX_8 [2];
  undefined1 uStackX_18;
  undefined4 auStackX_20 [2];
  undefined8 in_stack_ffffffffffffff68;
  undefined4 uVar12;
  undefined8 uStack_88;
  undefined8 auStack_80 [2];
  undefined8 uStack_70;
  undefined **appuStack_68 [2];
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  
  uVar12 = (undefined4)((ulonglong)in_stack_ffffffffffffff68 >> 0x20);
  apuStackX_8[0] = self;
  if (DAT_7fff625e1790 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fe0a8);
    FUN_7fff5f47d450(&DAT_7fff62474d00);
    FUN_7fff5f47d450(&DAT_7fff62472c38);
    FUN_7fff5f47d450(&DAT_7fff62472d00);
    FUN_7fff5f47d450(&DAT_7fff62472dd0);
    FUN_7fff5f47d450(&DAT_7fff62472e98);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff62430100);
    FUN_7fff5f47d450(&DAT_7fff6243bd58);
    FUN_7fff5f47d450(&DAT_7fff62406088);
    FUN_7fff5f47d450(&DAT_7fff62406568);
    FUN_7fff5f47d450(&DAT_7fff62434940);
    FUN_7fff5f47d450(&DAT_7fff624347c0);
    FUN_7fff5f47d450(&DAT_7fff62434a00);
    FUN_7fff5f47d450(&DAT_7fff624405a0);
    DAT_7fff625e1790 = '\x01';
  }
  uStackX_18 = 0;
  uStack_88 = 0;
  auStack_80[0] = 0;
  uStack_70 = 0;
  appuStack_68[0] = apuStackX_8;
  iVar11 = *(int *)(apuStackX_8[0] + 0x10);
  self_00 = *(undefined **)(apuStackX_8[0] + 0x20);
  if (iVar11 == 0) {
    *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xffffffff;
    *(undefined4 *)(apuStackX_8[0] + 0x48) = 0;
LAB_7fff5f5c7834:
    if (self_00 == (undefined *)0x0) goto LAB_7fff5f5c7c8d;
    if (*(int *)(self_00 + 0x30) <= *(int *)(self_00 + 0x2c)) {
      auStackX_20[0] = 0;
      uVar10 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,auStackX_20);
      *(undefined8 *)(apuStackX_8[0] + 0x18) = uVar10;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(apuStackX_8[0] + 0x10) = 1;
      return 1;
    }
    if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
      func_0x7fff5fc01a30(*(longlong *)(apuStackX_8[0] + 0x28),_DAT_7fff62472e98);
      *(int *)(self_00 + 0x2c) = *(int *)(self_00 + 0x2c) + 1;
      apuStackX_8[0][0x4c] = 0;
      goto LAB_7fff5f5c78ce;
    }
  }
  else {
    if (iVar11 == 1) {
      *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xffffffff;
      goto LAB_7fff5f5c7834;
    }
    if (iVar11 == 2) {
      *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xffffffff;
LAB_7fff5f5c78ce:
      cVar2 = FUN_7fff61882b40(0);
      if (cVar2 == '\0') {
        *(undefined8 *)(apuStackX_8[0] + 0x18) = 0;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(apuStackX_8[0] + 0x10) = 2;
        return 1;
      }
      apuStackX_8[0][0x4c] = 1;
      uVar10 = *(undefined8 *)(apuStackX_8[0] + 0x30);
      uStack_58 = 0;
      uStack_50 = 0;
      func_0x7fff6188cc90(&uStack_58,0,0,0,CONCAT44(uVar12,*(undefined4 *)(apuStackX_8[0] + 0x38)),0
                         );
      uStack_48 = (undefined4)uStack_58;
      uStack_44 = uStack_58._4_4_;
      uStack_40 = (undefined4)uStack_50;
      uStack_3c = uStack_50._4_4_;
      uVar3 = FUN_7fff61882a70(uVar10,&uStack_48,0);
      if (self_00 != (undefined *)0x0) {
        self_00[0x41] = uVar3;
        if (self_00[0x48] != '\0') {
          uVar10 = *(undefined8 *)(apuStackX_8[0] + 0x30);
          if (*(int *)(_DAT_7fff62474d00 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          uStack_88 = FUN_7fff61006310(0);
          auStack_80[0] = FUN_7fff610065a0(&uStack_88,0);
          uVar8 = FUN_7fff6100f660(auStack_80,0);
          uVar10 = FUN_7fff60e71650(uVar10,_DAT_7fff624405a0,uVar8,0);
          *(undefined8 *)(apuStackX_8[0] + 0x30) = uVar10;
          thunk_FUN_7fff5f491fd0();
        }
        goto LAB_7fff5f5c79f7;
      }
    }
    else {
      if (iVar11 == 3) {
        *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xfffffffd;
        if (self_00 == (undefined *)0x0) {
LAB_7fff5f5c7c10:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c15:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c1a:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c1f:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c24:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c29:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c2e:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c33:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c38:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c3d:
          uVar10 = func_0x7fff5f47d0b0();
          FUN_7fff5f47d620(uVar10,0);
LAB_7fff5f5c7c4c:
          FUN_7fff5f47d650();
LAB_7fff5f5c7c51:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c56:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c5b:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c60:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c65:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c6a:
          FUN_7fff5f47d660();
          goto LAB_7fff5f5c7c6f;
        }
        if (self_00[0x40] == '\0') {
          if (*(longlong *)(apuStackX_8[0] + 0x40) == 0) goto LAB_7fff5f5c7c65;
          cVar2 = func_0x7fff60e76090(*(undefined8 *)(*(longlong *)(apuStackX_8[0] + 0x40) + 0x10),0
                                     );
          if (cVar2 == '\0') {
            if (*(longlong *)(apuStackX_8[0] + 0x40) != 0) {
              if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
                func_0x7fff5f4d30b0(*(longlong *)(apuStackX_8[0] + 0x28),
                                    *(undefined8 *)(*(longlong *)(apuStackX_8[0] + 0x40) + 0x10),
                                    _DAT_7fff62472d00);
                iVar11 = *(int *)(self_00 + 0x3c);
                *(int *)(self_00 + 0x3c) = iVar11 + 1;
                if (*(int *)(self_00 + 0x38) <= iVar11 + 1) {
                  iVar11 = *(int *)(self_00 + 0x34);
                  if (iVar11 < *(int *)(self_00 + 0x30)) {
                    iVar5 = *(int *)(self_00 + 0x30) / 2;
                    if (iVar11 <= iVar5) {
                      iVar11 = iVar5;
                    }
                    *(int *)(self_00 + 0x30) = iVar11;
                    *(undefined4 *)(self_00 + 0x3c) = 0;
                  }
                }
                iVar11 = *(int *)(apuStackX_8[0] + 0x48);
                *(int *)(apuStackX_8[0] + 0x48) = iVar11 + 1;
                if (iVar11 + 1 < *(int *)(self_00 + 0x24)) goto LAB_7fff5f5c75bf;
                methodInfo_00 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
                if (*(longlong *)(apuStackX_8[0] + 0x40) != 0) {
                  lVar6 = *(longlong *)(*(longlong *)(apuStackX_8[0] + 0x40) + 0x10);
                  if (methodInfo_00 != (longlong *)0x0) {
                    if ((lVar6 != 0) &&
                       (lVar7 = func_0x7fff5f47c7e0(lVar6,*(undefined8 *)(*methodInfo_00 + 0x40)),
                       lVar7 == 0)) goto LAB_7fff5f5c7c3d;
                    if ((int)methodInfo_00[3] != 0) {
                      methodInfo_00[4] = lVar6;
                      thunk_FUN_7fff5f491fd0();
                      puVar9 = _DAT_7fff62434940;
LAB_7fff5f5c75ae:
                      StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                                (puVar9,(undefined *)methodInfo_00);
                      goto LAB_7fff5f5c75bb;
                    }
                    goto LAB_7fff5f5c7c4c;
                  }
                  goto LAB_7fff5f5c7c51;
                }
                goto LAB_7fff5f5c7c56;
              }
              goto LAB_7fff5f5c7c5b;
            }
            goto LAB_7fff5f5c7c60;
          }
          if (*(longlong *)(apuStackX_8[0] + 0x50) == 0) goto LAB_7fff5f5c7c38;
          uVar10 = FUN_7fff61b14910(*(longlong *)(apuStackX_8[0] + 0x50),0);
          cVar2 = func_0x7fff60e76090(uVar10,0);
          if (cVar2 != '\0') {
            lVar6 = *(longlong *)(apuStackX_8[0] + 0x28);
            if (*(longlong *)(apuStackX_8[0] + 0x50) != 0) {
              uVar10 = FUN_7fff61b146e0(*(longlong *)(apuStackX_8[0] + 0x50),0);
              if (lVar6 != 0) {
                func_0x7fff5f4d30e0(lVar6,uVar10,_DAT_7fff62472dd0);
                if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
                  func_0x7fff5f4d30b0(*(longlong *)(apuStackX_8[0] + 0x28),0,_DAT_7fff62472d00);
                  if (0 < *(int *)(self_00 + 0x3c)) {
                    *(int *)(self_00 + 0x3c) = *(int *)(self_00 + 0x3c) + -1;
                  }
                  goto LAB_7fff5f5c75bb;
                }
                goto LAB_7fff5f5c7c29;
              }
              goto LAB_7fff5f5c7c2e;
            }
            goto LAB_7fff5f5c7c33;
          }
          iVar11 = *(int *)(self_00 + 0x3c);
          *(int *)(self_00 + 0x3c) = iVar11 + 1;
          if (*(int *)(self_00 + 0x38) <= iVar11 + 1) {
            iVar11 = *(int *)(self_00 + 0x34);
            if (iVar11 < *(int *)(self_00 + 0x30)) {
              iVar5 = *(int *)(self_00 + 0x30) / 2;
              if (iVar11 <= iVar5) {
                iVar11 = iVar5;
              }
              *(int *)(self_00 + 0x30) = iVar11;
              *(undefined4 *)(self_00 + 0x3c) = 0;
            }
          }
          lVar6 = *(longlong *)(apuStackX_8[0] + 0x28);
          if (*(longlong *)(apuStackX_8[0] + 0x50) == 0) goto LAB_7fff5f5c7c24;
          uVar10 = FUN_7fff61b14910(*(longlong *)(apuStackX_8[0] + 0x50),0);
          if (lVar6 == 0) goto LAB_7fff5f5c7c1f;
          func_0x7fff5f4d30b0(lVar6,uVar10,_DAT_7fff62472d00);
          iVar11 = *(int *)(apuStackX_8[0] + 0x48);
          *(int *)(apuStackX_8[0] + 0x48) = iVar11 + 1;
          if (*(int *)(self_00 + 0x24) <= iVar11 + 1) {
            methodInfo_00 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
            if (*(longlong *)(apuStackX_8[0] + 0x50) != 0) {
              lVar6 = FUN_7fff61b14910(*(longlong *)(apuStackX_8[0] + 0x50),0);
              if (methodInfo_00 != (longlong *)0x0) {
                if ((lVar6 == 0) ||
                   (lVar7 = func_0x7fff5f47c7e0(lVar6,*(undefined8 *)(*methodInfo_00 + 0x40)),
                   lVar7 != 0)) {
                  if ((int)methodInfo_00[3] != 0) {
                    methodInfo_00[4] = lVar6;
                    thunk_FUN_7fff5f491fd0();
                    puVar9 = _DAT_7fff62434a00;
                    goto LAB_7fff5f5c75ae;
                  }
                }
                else {
                  uVar10 = func_0x7fff5f47d0b0();
                  FUN_7fff5f47d620(uVar10,0);
                }
                FUN_7fff5f47d650();
                goto LAB_7fff5f5c7c10;
              }
              goto LAB_7fff5f5c7c15;
            }
            goto LAB_7fff5f5c7c1a;
          }
        }
        else {
LAB_7fff5f5c75bb:
          apuStackX_8[0][0x4d] = 1;
        }
LAB_7fff5f5c75bf:
        *(undefined8 *)(apuStackX_8[0] + 0x40) = 0;
        thunk_FUN_7fff5f491fd0();
        puVar9 = apuStackX_8[0];
        if (DAT_7fff625e1791 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff624413c0);
          DAT_7fff625e1791 = '\x01';
        }
        *(undefined4 *)(puVar9 + 0x10) = 0xffffffff;
        if (*(longlong *)(puVar9 + 0x50) != 0) {
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
        }
        *(undefined8 *)(apuStackX_8[0] + 0x50) = 0;
        thunk_FUN_7fff5f491fd0();
        if (apuStackX_8[0][0x4d] == '\0') {
          uVar12 = *(undefined4 *)(self_00 + 0x28);
          uVar10 = func_0x7fff5f44ff00(_DAT_7fff62406568);
          FUN_7fff618b74f0(uVar10,uVar12,0);
          *(undefined8 *)(apuStackX_8[0] + 0x18) = uVar10;
          thunk_FUN_7fff5f491fd0();
          *(undefined4 *)(apuStackX_8[0] + 0x10) = 4;
          return 1;
        }
LAB_7fff5f5c7b75:
        if (self_00[0x40] == '\0') {
LAB_7fff5f5c7b9b:
          self_00[0x41] = 0;
          *(int *)(self_00 + 0x2c) = *(int *)(self_00 + 0x2c) + -1;
          if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
            func_0x7fff60042160(*(longlong *)(apuStackX_8[0] + 0x28),_DAT_7fff62472c38);
            return 0;
          }
          goto LAB_7fff5f5c7c74;
        }
        if (*(longlong *)(apuStackX_8[0] + 0x28) != 0) {
          func_0x7fff5f4d30b0(*(longlong *)(apuStackX_8[0] + 0x28),_DAT_7fff624347c0,
                              _DAT_7fff62472d00);
          goto LAB_7fff5f5c7b9b;
        }
LAB_7fff5f5c7c79:
        FUN_7fff5f47d660();
      }
      else {
        if (iVar11 != 4) {
          return 0;
        }
        *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xffffffff;
LAB_7fff5f5c79f7:
        puVar9 = apuStackX_8[0];
        if (self_00 != (undefined *)0x0) {
          if (*(int *)(self_00 + 0x24) <= *(int *)(apuStackX_8[0] + 0x48)) goto LAB_7fff5f5c7b75;
          apuStackX_8[0][0x4d] = 0;
          if (apuStackX_8[0][0x4c] == '\0') {
            uVar10 = *(undefined8 *)(apuStackX_8[0] + 0x30);
            uVar8 = func_0x7fff5f44ff00(_DAT_7fff62406088);
            FUN_7fff61b14540(uVar8,uVar10,0);
          }
          else {
            uVar8 = FUN_7fff61b14220(*(undefined8 *)(apuStackX_8[0] + 0x30),
                                     *(undefined4 *)(apuStackX_8[0] + 0x38),0);
          }
          if (puVar9 != (undefined *)0x0) {
            *(undefined8 *)(puVar9 + 0x50) = uVar8;
            thunk_FUN_7fff5f491fd0();
            *(undefined4 *)(apuStackX_8[0] + 0x10) = 0xfffffffd;
            puVar9 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6243bd58);
            StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                      (puVar9,(undefined *)0x0);
            *(undefined **)(apuStackX_8[0] + 0x40) = puVar9;
            thunk_FUN_7fff5f491fd0();
            if (*(longlong *)(apuStackX_8[0] + 0x40) != 0) {
              *(undefined8 *)(*(longlong *)(apuStackX_8[0] + 0x40) + 0x10) = 0;
              thunk_FUN_7fff5f491fd0();
              puVar9 = *(undefined **)(apuStackX_8[0] + 0x50);
              timeout = *(float *)(self_00 + 0x20);
              uVar10 = *(undefined8 *)(apuStackX_8[0] + 0x40);
              timeoutCallback = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623fe0a8);
              FUN_7fff5fdfedb0(timeoutCallback,uVar10,_DAT_7fff62430100,0);
              puVar9 = DownloadManager_downloadCheckTimeOut
                                 (self_00,puVar9,timeout,timeoutCallback,(undefined *)0x0);
              uVar10 = FUN_7fff618a87c0(self_00,puVar9,0);
              *(undefined8 *)(apuStackX_8[0] + 0x18) = uVar10;
              thunk_FUN_7fff5f491fd0();
              *(undefined4 *)(apuStackX_8[0] + 0x10) = 3;
              return 1;
            }
            goto LAB_7fff5f5c7c6a;
          }
LAB_7fff5f5c7c6f:
          FUN_7fff5f47d660();
LAB_7fff5f5c7c74:
          FUN_7fff5f47d660();
          goto LAB_7fff5f5c7c79;
        }
      }
      FUN_7fff5f47d660();
    }
    FUN_7fff5f47d660();
  }
  FUN_7fff5f47d660();
LAB_7fff5f5c7c8d:
  FUN_7fff5f47d660();
  func_0x7fff5f5bc150(appuStack_68);
  FUN_7fff5f40a410(self_00);
  pcVar1 = (code *)swi(3);
  bVar4 = (*pcVar1)();
  return bVar4;
}

