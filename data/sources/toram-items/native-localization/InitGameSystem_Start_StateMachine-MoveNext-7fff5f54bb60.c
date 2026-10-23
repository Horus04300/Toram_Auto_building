
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte InitGameSystem_Start_StateMachine_MoveNext(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  undefined1 uVar3;
  char cVar4;
  byte bVar5;
  undefined4 uVar6;
  int iVar7;
  undefined8 uVar8;
  longlong *plVar9;
  undefined *flags;
  longlong *plVar10;
  undefined *puVar11;
  undefined *puVar12;
  longlong lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  longlong lVar16;
  undefined *puVar17;
  longlong *plVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  longlong lVar21;
  ulonglong in_stack_ffffffffffffffb8;
  undefined8 in_stack_ffffffffffffffc0;
  
  uVar6 = (undefined4)((ulonglong)in_stack_ffffffffffffffc0 >> 0x20);
  if (DAT_7fff625e147c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fb4c8);
    FUN_7fff5f47d450(0x7fff623ffc48);
    FUN_7fff5f47d450(0x7fff62436790);
    FUN_7fff5f47d450(&DAT_7fff6243b8b8);
    FUN_7fff5f47d450(0x7fff62419530);
    FUN_7fff5f47d450(0x7fff62404e78);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff62441468);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(0x7fff62418720);
    FUN_7fff5f47d450(&DAT_7fff62459938);
    FUN_7fff5f47d450(0x7fff6245c4f8);
    FUN_7fff5f47d450(0x7fff624575f8);
    FUN_7fff5f47d450(0x7fff6245dce0);
    FUN_7fff5f47d450(&DAT_7fff62458858);
    FUN_7fff5f47d450(&DAT_7fff6245ce88);
    FUN_7fff5f47d450(&DAT_7fff6245bdd8);
    FUN_7fff5f47d450(&DAT_7fff6245a460);
    FUN_7fff5f47d450(0x7fff6245b120);
    FUN_7fff5f47d450(0x7fff62457160);
    FUN_7fff5f47d450(0x7fff62457908);
    FUN_7fff5f47d450(&DAT_7fff62426990);
    FUN_7fff5f47d450(&DAT_7fff62468308);
    FUN_7fff5f47d450(&DAT_7fff6246a948);
    FUN_7fff5f47d450(0x7fff6246c5f8);
    FUN_7fff5f47d450(0x7fff62454eb0);
    FUN_7fff5f47d450(0x7fff62454f78);
    FUN_7fff5f47d450(0x7fff62455038);
    FUN_7fff5f47d450(0x7fff62455100);
    FUN_7fff5f47d450(0x7fff62455410);
    FUN_7fff5f47d450(0x7fff624554d0);
    FUN_7fff5f47d450(0x7fff62467db8);
    FUN_7fff5f47d450(0x7fff62455598);
    FUN_7fff5f47d450(0x7fff62455658);
    FUN_7fff5f47d450(0x7fff62467e88);
    FUN_7fff5f47d450(0x7fff62455720);
    FUN_7fff5f47d450(0x7fff62467f50);
    FUN_7fff5f47d450(0x7fff624557e0);
    FUN_7fff5f47d450(0x7fff624558a8);
    FUN_7fff5f47d450(0x7fff62468020);
    FUN_7fff5f47d450(0x7fff62455968);
    FUN_7fff5f47d450(0x7fff624680e8);
    FUN_7fff5f47d450(0x7fff62467ce8);
    FUN_7fff5f47d450(&DAT_7fff62406568);
    FUN_7fff5f47d450(0x7fff6241e060);
    FUN_7fff5f47d450(0x7fff6241b2b0);
    FUN_7fff5f47d450(0x7fff62412b00);
    FUN_7fff5f47d450(0x7fff62474668);
    FUN_7fff5f47d450(0x7fff62458a70);
    FUN_7fff5f47d450(0x7fff62437e80);
    FUN_7fff5f47d450(0x7fff624070f8);
    FUN_7fff5f47d450(0x7fff6246f1f8);
    FUN_7fff5f47d450(0x7fff6241e540);
    FUN_7fff5f47d450(0x7fff62447080);
    FUN_7fff5f47d450(0x7fff623fc538);
    FUN_7fff5f47d450(0x7fff62412a30);
    FUN_7fff5f47d450(0x7fff6241e130);
    FUN_7fff5f47d450(0x7fff6244ac00);
    FUN_7fff5f47d450(0x7fff623f8858);
    FUN_7fff5f47d450(0x7fff6241f3e8);
    FUN_7fff5f47d450(0x7fff6240f1a0);
    FUN_7fff5f47d450(0x7fff6243e130);
    FUN_7fff5f47d450(&DAT_7fff62424b00);
    FUN_7fff5f47d450(0x7fff62474738);
    FUN_7fff5f47d450(0x7fff62460800);
    FUN_7fff5f47d450(0x7fff624735b0);
    FUN_7fff5f47d450(0x7fff6244ad88);
    FUN_7fff5f47d450(0x7fff62460998);
    FUN_7fff5f47d450(0x7fff6240f0d0);
    FUN_7fff5f47d450(0x7fff6241e2d0);
    FUN_7fff5f47d450(0x7fff6241e3a0);
    FUN_7fff5f47d450(0x7fff6241e470);
    FUN_7fff5f47d450(0x7fff6244af10);
    FUN_7fff5f47d450(0x7fff6241f0a8);
    FUN_7fff5f47d450(0x7fff6244ae48);
    FUN_7fff5f47d450(0x7fff62474808);
    FUN_7fff5f47d450(0x7fff624257d0);
    FUN_7fff5f47d450(0x7fff62425898);
    FUN_7fff5f47d450(&DAT_7fff62446cb0);
    FUN_7fff5f47d450(0x7fff6245a038);
    DAT_7fff625e147c = '\x01';
  }
  lVar16 = *(longlong *)(self + 0x20);
  plVar9 = (longlong *)0x0;
  switch(*(undefined4 *)(self + 0x10)) {
  case 0:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    puVar17 = (undefined *)func_0x7fff5f44ff00(uRam00007fff62467db8);
    StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar17,(undefined *)0x0);
    *(undefined **)(self + 0x30) = puVar17;
    thunk_FUN_7fff5f491fd0();
    cVar4 = func_0x7fff5f4e1200(0);
    if (cVar4 != '\0') {
      if (lVar16 == 0) goto code_r0x7fff5f54dee4;
      uVar19 = *(undefined8 *)(lVar16 + 0xb0);
      if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      puVar17 = _DAT_7fff62441468;
      FUN_7fff606c58d0(uVar19,_DAT_7fff62441468);
    }
    puVar12 = (undefined *)FUN_7fff60c4bc00(uRam00007fff6245c4f8);
    if (puVar12 == (undefined *)0x0) goto code_r0x7fff5f54dee4;
    StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
              (puVar12,(undefined *)CONCAT71((int7)((ulonglong)puVar17 >> 8),1));
    FUN_7fff6189a090(0xffffffff);
    lVar21 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if ((lVar21 == 0) || (func_0x7fff5f5784b0(lVar21,0,0), lVar16 == 0)) goto code_r0x7fff5f54dee4;
    FUN_7fff5f53f2e0(lVar16,0);
    uVar19 = FUN_7fff5f53cbb0(0);
    uVar19 = FUN_7fff60e71970(uVar19,uRam00007fff62437e80,0);
    lVar21 = *(longlong *)(lVar16 + 0x38);
    uVar19 = FUN_7fff60e71970(uRam00007fff624735b0,uVar19,0);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    FUN_7fff5ff0eed0(lVar21,uVar19,0);
    StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
              (puRam00007fff624070f8,(undefined *)0x0);
    cVar4 = FUN_7fff5fddc3e0(0);
    if (cVar4 == '\0') {
      lVar21 = FUN_7fff60c4bc00(_DAT_7fff62459938);
      if (lVar21 == 0) goto code_r0x7fff5f54dee4;
      FUN_7fff603cdcf0(lVar21,0);
      goto code_r0x7fff5f54c0dd;
    }
    break;
  case 1:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
code_r0x7fff5f54c0dd:
    lVar21 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(lVar21 + 0x38) != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
    break;
  case 2:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    goto code_r0x7fff5f54c160;
  case 3:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    goto code_r0x7fff5f54c1e2;
  case 4:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    goto code_r0x7fff5f54c3fc;
  case 5:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
    if (*(longlong *)(self + 0x70) != 0) {
      uVar19 = FUN_7fff5f568150(*(longlong *)(self + 0x70),uRam00007fff62474808,0);
      if ((*(longlong *)(self + 0x70) != 0) &&
         (uVar20 = FUN_7fff5f568150(*(longlong *)(self + 0x70),uRam00007fff62474738,0), lVar16 != 0)
         ) {
        FUN_7fff5fdd4590(lVar16,uVar19,uVar20,0);
        *(undefined8 *)(self + 0x18) = *(undefined8 *)(self + 0x78);
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 6;
        return 1;
      }
    }
    goto code_r0x7fff5f54dee4;
  case 6:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    FUN_7fff618828c0(0);
    puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
    if (puVar17 == (undefined *)0x0) goto code_r0x7fff5f54dee4;
    ResourceManager_ClearBreakAssetsData(puVar17,(undefined *)0x0);
    goto code_r0x7fff5f54c68b;
  case 7:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    lVar21 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(lVar21 + 0x20) == '\0') {
      if (lVar16 != 0) {
        if (cRam00007fff625e1463 == '\0') {
          FUN_7fff5f47d450(0x7fff62468c10);
          cRam00007fff625e1463 = '\x01';
        }
        puVar17 = (undefined *)func_0x7fff5f44ff00(uRam00007fff62468c10);
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar17,(undefined *)0x0)
        ;
        *(longlong *)(puVar17 + 0x20) = lVar16;
        *(undefined4 *)(puVar17 + 0x10) = 0;
        thunk_FUN_7fff5f491fd0();
        uVar19 = FUN_7fff618a87c0(lVar16,puVar17,0);
        *(undefined8 *)(self + 0x18) = uVar19;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 8;
        return 1;
      }
      goto code_r0x7fff5f54dee4;
    }
    goto code_r0x7fff5f54c77f;
  case 8:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
code_r0x7fff5f54c77f:
    if (lVar16 != 0) {
      lVar21 = *(longlong *)(lVar16 + 0x30);
      if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
         (uVar19 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6241e130,0),
         lVar21 != 0)) {
        FUN_7fff5ff0eed0(lVar21,uVar19,0);
        lVar21 = FUN_7fff60c4bc00(uRam00007fff62457160);
        lVar13 = FUN_7fff60c4bc00(_DAT_7fff6245ce88);
        if (lVar13 != 0) {
          uVar3 = func_0x7fff5f4e1200(lVar13,0);
          lVar13 = FUN_7fff60c4bc00(_DAT_7fff6245ce88);
          if (lVar13 != 0) {
            uVar19 = *(undefined8 *)(lVar13 + 0x88);
            lVar13 = FUN_7fff60c4bc00(_DAT_7fff6245ce88);
            if (lVar13 != 0) {
              if (cRam00007fff625e14cc == '\0') {
                FUN_7fff5f47d450(&DAT_7fff624606c8);
                cRam00007fff625e14cc = '\x01';
              }
              if (lVar21 != 0) {
                uVar19 = FUN_7fff5f5a24e0(lVar21,uVar3,uVar19,
                                          **(undefined8 **)(_DAT_7fff624606c8 + 0xb8),0);
                uVar19 = FUN_7fff618a87c0(lVar16,uVar19,0);
                *(undefined8 *)(self + 0x18) = uVar19;
                thunk_FUN_7fff5f491fd0();
                *(undefined4 *)(self + 0x10) = 9;
                return 1;
              }
            }
          }
        }
      }
    }
    goto code_r0x7fff5f54dee4;
  case 9:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    lVar21 = FUN_7fff60c4bc00(uRam00007fff62457160);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    uVar19 = *(undefined8 *)(lVar21 + 0x30);
    lVar21 = FUN_7fff60c4bc00(uRam00007fff624575f8);
    uVar20 = FUN_7fff5f5a1300(0);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    uVar6 = FUN_7fff5f5a3260(lVar21,uVar20,0);
    lVar21 = FUN_7fff60c4bc00(uRam00007fff624575f8);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    FUN_7fff5f5a35c0(lVar21,uVar19,uVar6,0,in_stack_ffffffffffffffb8 & 0xffffffffffffff00,0);
    lVar21 = FUN_7fff60c4bc00(uRam00007fff62457160);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(lVar21 + 0x3b) != '\0') {
      puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
      if (puVar17 != (undefined *)0x0) {
        plVar18 = (longlong *)LocalizeManager_Get(puVar17,(undefined *)0x0,(undefined *)0x0);
        lVar16 = FUN_7fff60c4bc00(uRam00007fff62457160);
        if (lVar16 != 0) {
          if (plVar18 != (longlong *)0x0) {
            if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7fff62468308 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar18 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7fff62468308 + 0x130) * 8) != _DAT_7fff62468308)) {
              bVar2 = false;
            }
            else {
              bVar2 = true;
            }
            if (bVar2) {
              plVar9 = plVar18;
            }
          }
          FUN_7fff5fde51e0(plVar9,uRam00007fff6240f1a0,uRam00007fff6240f0d0,
                           *(undefined8 *)(lVar16 + 0x40),0);
          return 0;
        }
      }
      goto code_r0x7fff5f54dee4;
    }
    lVar21 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(lVar21 + 0x20) != '\0') {
      if (lVar16 != 0) {
        if (cRam00007fff625e1461 == '\0') {
          FUN_7fff5f47d450(0x7fff62468818);
          cRam00007fff625e1461 = '\x01';
        }
        puVar17 = (undefined *)func_0x7fff5f44ff00(uRam00007fff62468818);
        StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar17,(undefined *)0x0)
        ;
        *(longlong *)(puVar17 + 0x20) = lVar16;
        *(undefined4 *)(puVar17 + 0x10) = 0;
        thunk_FUN_7fff5f491fd0();
        uVar19 = FUN_7fff618a87c0(lVar16,puVar17,0);
        *(undefined8 *)(self + 0x18) = uVar19;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 10;
        return 1;
      }
      goto code_r0x7fff5f54dee4;
    }
    goto code_r0x7fff5f54ca74;
  case 10:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
code_r0x7fff5f54ca74:
    if (lVar16 != 0) {
      lVar21 = *(longlong *)(lVar16 + 0x30);
      if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
         (uVar19 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6241e3a0,0),
         lVar21 != 0)) {
        FUN_7fff5ff0eed0(lVar21,uVar19,0);
        plVar9 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
        lVar21 = FUN_7fff60c4bc00(_DAT_7fff6245ce88);
        if ((lVar21 != 0) && (lVar21 = FUN_7fff5f5e7aa0(lVar21,0), plVar9 != (longlong *)0x0)) {
          if ((lVar21 != 0) &&
             (lVar13 = func_0x7fff5f47c7e0(lVar21,*(undefined8 *)(*plVar9 + 0x40)), lVar13 == 0)) {
            uVar19 = func_0x7fff5f47d0b0();
            FUN_7fff5f47d620(uVar19,0);
            pcVar1 = (code *)swi(3);
            bVar5 = (*pcVar1)();
            return bVar5;
          }
          if ((int)plVar9[3] == 0) {
code_r0x7fff5f54deea:
            FUN_7fff5f47d650();
            pcVar1 = (code *)swi(3);
            bVar5 = (*pcVar1)();
            return bVar5;
          }
          plVar9[4] = lVar21;
          thunk_FUN_7fff5f491fd0();
          StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                    (puRam00007fff6245a038,(undefined *)plVar9);
          if (*(longlong *)(self + 0x30) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x30) + 0x10) = 0;
            if (*(int *)(_DAT_7fff6243b8b8 + 0xe0) == 0) {
              func_0x7fff5f47d6f0();
            }
            FUN_7fff61881040(2);
            puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff62458858);
            if (puVar17 != (undefined *)0x0) {
              DownloadManager_Reset(puVar17,(undefined *)0x0);
              puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
              lVar21 = FUN_7fff60c4bc00(_DAT_7fff6245ce88);
              if (lVar21 != 0) {
                puVar12 = (undefined *)FUN_7fff5f5e7aa0(lVar21,0);
                uVar19 = *(undefined8 *)(self + 0x30);
                puVar11 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
                FUN_7fff60739100(puVar11,uVar19,uRam00007fff62455410);
                if (puVar17 != (undefined *)0x0) {
                  puVar17 = ResourceManager_Initialize(puVar17,puVar12,puVar11,(undefined *)0x0);
                  uVar19 = FUN_7fff618a87c0(lVar16,puVar17,0);
                  *(undefined8 *)(self + 0x18) = uVar19;
                  thunk_FUN_7fff5f491fd0();
                  *(undefined4 *)(self + 0x10) = 0xb;
                  return 1;
                }
              }
            }
          }
        }
      }
    }
    goto code_r0x7fff5f54dee4;
  case 0xb:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x30) == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(*(longlong *)(self + 0x30) + 0x10) == '\0') {
      puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
      if (puVar17 == (undefined *)0x0) goto code_r0x7fff5f54dee4;
      plVar18 = (longlong *)LocalizeManager_Get(puVar17,(undefined *)0x0,(undefined *)0x0);
      if (plVar18 == (longlong *)0x0) {
        FUN_7fff60c4bc00(uRam00007fff6245dce0);
        goto code_r0x7fff5f54dee4;
      }
      if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7fff62468308 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar18 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff62468308 + 0x130) * 8
           ) != _DAT_7fff62468308)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        plVar9 = plVar18;
      }
      lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
      if (plVar9 == (longlong *)0x0) goto code_r0x7fff5f54dee4;
      uVar19 = FUN_7fff5f568150(plVar9,uRam00007fff6244af10,0);
      uVar20 = FUN_7fff5f568150(plVar9,uRam00007fff6244ae48,0);
      if (*(int *)(lRam00007fff62467ce8 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(lRam00007fff62467ce8);
      }
      lVar21 = *(longlong *)(*(longlong *)(lRam00007fff62467ce8 + 0xb8) + 8);
      if (lVar21 == 0) {
        if (*(int *)(lRam00007fff62467ce8 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(lRam00007fff62467ce8);
        }
        uVar14 = **(undefined8 **)(lRam00007fff62467ce8 + 0xb8);
        lVar21 = func_0x7fff5f44ff00(uRam00007fff62436790);
        FUN_7fff5f4f6880(lVar21,uVar14,uRam00007fff62455038,0);
        *(longlong *)(*(longlong *)(lRam00007fff62467ce8 + 0xb8) + 8) = lVar21;
        goto code_r0x7fff5f54cf73;
      }
      goto code_r0x7fff5f54cf7b;
    }
    lVar21 = FUN_7fff60c4bc00(uRam00007fff62457908);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    lVar21 = *(longlong *)(lVar21 + 0x28);
    uVar19 = FUN_7fff60c4bc00(uRam00007fff6245b120);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    FUN_7fff5f4e2a50(lVar21,uVar19,0);
    lVar21 = FUN_7fff60c4bc00(uRam00007fff62457908);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    cVar4 = FUN_7fff5fdd5e80(lVar21);
    if (cVar4 != '\0') {
      if (lVar16 != 0) {
        lVar21 = *(longlong *)(lVar16 + 0x30);
        if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
           (uVar19 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6241e060,0),
           lVar21 != 0)) {
          FUN_7fff5ff0eed0(lVar21,uVar19,0);
          puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
          if (puVar17 != (undefined *)0x0) {
            puVar17 = LocalizeManager_GetLocalizeCode(puVar17,(undefined *)0x0);
            *(undefined **)(self + 0x50) = puVar17;
            thunk_FUN_7fff5f491fd0();
            uVar19 = FUN_7fff60e74db0(uRam00007fff62447080,*(undefined8 *)(self + 0x50),
                                      *(undefined8 *)(self + 0x50),0);
            *(undefined8 *)(self + 0x58) = uVar19;
            thunk_FUN_7fff5f491fd0();
            *(undefined8 *)(self + 0x60) = 0;
            thunk_FUN_7fff5f491fd0();
            *(undefined8 *)(self + 0x68) = 0;
            thunk_FUN_7fff5f491fd0();
            puVar17 = (undefined *)func_0x7fff5f44ff00(uRam00007fff62467f50);
            StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                      (puVar17,(undefined *)0x0);
            *(undefined **)(self + 0x38) = puVar17;
            thunk_FUN_7fff5f491fd0();
            if (*(longlong *)(self + 0x38) != 0) {
              *(undefined1 *)(*(longlong *)(self + 0x38) + 0x10) = 0;
              puVar12 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
              puVar17 = *(undefined **)(self + 0x58);
              uVar19 = *(undefined8 *)(self + 0x38);
              puVar11 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
              FUN_7fff60739100(puVar11,uVar19,uRam00007fff62455720,0);
              if (puVar12 != (undefined *)0x0) {
                puVar17 = ResourceManager_LoadAssetBundle
                                    (puVar12,puVar17,(undefined *)0x1,puVar11,(undefined *)0x0);
                uVar19 = FUN_7fff618a87c0(lVar16,puVar17,0);
                *(undefined8 *)(self + 0x18) = uVar19;
                thunk_FUN_7fff5f491fd0();
                *(undefined4 *)(self + 0x10) = 0xc;
                return 1;
              }
            }
          }
        }
      }
      goto code_r0x7fff5f54dee4;
    }
    StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
              (puRam00007fff6241b2b0,(undefined *)0x0);
code_r0x7fff5f54c68b:
    lVar16 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if (lVar16 != 0) {
      FUN_7fff603d25b0(lVar16,0);
LAB_7fff5f54c6aa:
      return 0;
    }
    goto code_r0x7fff5f54dee4;
  case 0xc:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x38) == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(*(longlong *)(self + 0x38) + 0x10) != '\0') {
      puVar12 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
      puVar17 = *(undefined **)(self + 0x58);
      puVar11 = (undefined *)func_0x7fff5f47c850(_DAT_7fff62426990,2);
      uVar19 = FUN_7fff60e71970(uRam00007fff62460800,*(undefined8 *)(self + 0x50),0);
      if (puVar11 == (undefined *)0x0) goto code_r0x7fff5f54dee4;
      if (*(int *)(puVar11 + 0x18) == 0) goto code_r0x7fff5f54deea;
      *(undefined8 *)(puVar11 + 0x20) = uVar19;
      thunk_FUN_7fff5f491fd0();
      uVar19 = FUN_7fff60e71970(uRam00007fff62460998,*(undefined8 *)(self + 0x50),0);
      if (*(uint *)(puVar11 + 0x18) < 2) goto code_r0x7fff5f54deea;
      *(undefined8 *)(puVar11 + 0x28) = uVar19;
      thunk_FUN_7fff5f491fd0();
      flags = (undefined *)func_0x7fff5f47c850(uRam00007fff62419530,2);
      if (flags == (undefined *)0x0) goto code_r0x7fff5f54dee4;
      if ((*(int *)(flags + 0x18) == 0) ||
         (*(undefined4 *)(flags + 0x20) = 2, *(uint *)(flags + 0x18) < 2))
      goto code_r0x7fff5f54deea;
      *(undefined4 *)(flags + 0x24) = 2;
      if ((puVar12 == (undefined *)0x0) ||
         (puVar17 = ResourceManager_GetAssetObjects
                              (puVar12,puVar17,puVar11,flags,0,(undefined *)CONCAT44(uVar6,1),
                               (undefined *)0x0), puVar17 == (undefined *)0x0))
      goto code_r0x7fff5f54dee4;
      if (*(int *)(puVar17 + 0x18) == 0) goto code_r0x7fff5f54deea;
      plVar18 = *(longlong **)(puVar17 + 0x20);
      if (plVar18 == (longlong *)0x0) {
        *(undefined8 *)(self + 0x60) = 0;
      }
      else {
        if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7fff6246a948 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar18 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff6246a948 + 0x130) * 8) != _DAT_7fff6246a948)) {
          bVar2 = false;
        }
        else {
          bVar2 = true;
        }
        plVar10 = plVar9;
        if (bVar2) {
          plVar10 = plVar18;
        }
        *(longlong **)(self + 0x60) = plVar10;
      }
      thunk_FUN_7fff5f491fd0();
      if (*(uint *)(puVar17 + 0x18) < 2) goto code_r0x7fff5f54deea;
      plVar18 = *(longlong **)(puVar17 + 0x28);
      if (plVar18 == (longlong *)0x0) {
        *(undefined8 *)(self + 0x68) = 0;
      }
      else {
        if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(lRam00007fff6246c5f8 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar18 + 200) + -8 +
             (ulonglong)*(byte *)(lRam00007fff6246c5f8 + 0x130) * 8) != lRam00007fff6246c5f8)) {
          bVar2 = false;
        }
        else {
          bVar2 = true;
        }
        if (bVar2) {
          plVar9 = plVar18;
        }
        *(longlong **)(self + 0x68) = plVar9;
      }
      thunk_FUN_7fff5f491fd0();
      uVar19 = *(undefined8 *)(self + 0x60);
      if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      cVar4 = FUN_7fff618ab120(uVar19,0,0);
      if (cVar4 == '\0') {
        uVar19 = *(undefined8 *)(self + 0x68);
        if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        cVar4 = FUN_7fff618ab120(uVar19,0,0);
        if (cVar4 == '\0') goto code_r0x7fff5f54d256;
      }
      if (*(longlong *)(self + 0x38) == 0) goto code_r0x7fff5f54dee4;
      *(undefined1 *)(*(longlong *)(self + 0x38) + 0x10) = 0;
    }
code_r0x7fff5f54d256:
    if (*(longlong *)(self + 0x38) == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(*(longlong *)(self + 0x38) + 0x10) != '\0') {
      *(undefined8 *)(self + 0x38) = 0;
      thunk_FUN_7fff5f491fd0();
      puVar17 = (undefined *)func_0x7fff5f44ff00(uRam00007fff62468020);
      StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar17,(undefined *)0x0);
      *(undefined **)(self + 0x40) = puVar17;
      thunk_FUN_7fff5f491fd0();
      if (*(longlong *)(self + 0x40) != 0) {
        *(undefined1 *)(*(longlong *)(self + 0x40) + 0x18) = 0;
        if (*(longlong *)(self + 0x40) != 0) {
          *(undefined1 *)(*(longlong *)(self + 0x40) + 0x10) = 0;
          if ((*(longlong *)(self + 0x40) != 0) &&
             (*(undefined4 *)(*(longlong *)(self + 0x40) + 0x14) = 0, lVar16 != 0)) {
            lVar21 = *(longlong *)(lVar16 + 0x30);
            if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
               (uVar19 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6241e2d0,0),
               lVar21 != 0)) {
              FUN_7fff5ff0eed0(lVar21,uVar19,0);
              uVar19 = *(undefined8 *)(self + 0x40);
              uVar20 = func_0x7fff5f44ff00(uRam00007fff623ffc48);
              FUN_7fff60739f30(uVar20,uVar19,uRam00007fff624557e0,0);
              if (cRam00007fff625e145f == '\0') {
                FUN_7fff5f47d450(0x7fff624688e0);
                cRam00007fff625e145f = '\x01';
              }
              puVar17 = (undefined *)func_0x7fff5f44ff00(uRam00007fff624688e0);
              StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                        (puVar17,(undefined *)0x0);
              *(longlong *)(puVar17 + 0x20) = lVar16;
              *(undefined4 *)(puVar17 + 0x10) = 0;
              thunk_FUN_7fff5f491fd0();
              *(undefined8 *)(puVar17 + 0x30) = uVar20;
              thunk_FUN_7fff5f491fd0();
              uVar19 = FUN_7fff618a87c0(lVar16,puVar17,0);
              *(undefined8 *)(self + 0x18) = uVar19;
              thunk_FUN_7fff5f491fd0();
              *(undefined4 *)(self + 0x10) = 0xd;
              return 1;
            }
          }
        }
      }
      goto code_r0x7fff5f54dee4;
    }
    StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
              (puRam00007fff6241f0a8,(undefined *)0x0);
    if ((lVar16 == 0) || (*(longlong *)(lVar16 + 0xb8) == 0)) goto code_r0x7fff5f54dee4;
    uVar19 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6244ac00,0);
    if (*(longlong *)(lVar16 + 0xb8) == 0) goto code_r0x7fff5f54dee4;
    uVar20 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6244ad88,0);
    lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
    if (*(int *)(lRam00007fff62467ce8 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(lRam00007fff62467ce8);
    }
    lVar21 = *(longlong *)(*(longlong *)(lRam00007fff62467ce8 + 0xb8) + 0x10);
    if (lVar21 == 0) {
      if (*(int *)(lRam00007fff62467ce8 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(lRam00007fff62467ce8);
      }
      uVar14 = **(undefined8 **)(lRam00007fff62467ce8 + 0xb8);
      lVar21 = func_0x7fff5f44ff00(uRam00007fff62436790);
      FUN_7fff5f4f6880(lVar21,uVar14,uRam00007fff62455100,0);
      *(longlong *)(*(longlong *)(lRam00007fff62467ce8 + 0xb8) + 0x10) = lVar21;
code_r0x7fff5f54cf73:
      thunk_FUN_7fff5f491fd0();
    }
code_r0x7fff5f54cf7b:
    if (lVar16 != 0) {
code_r0x7fff5f54cf84:
      FUN_7fff5fdd4a60(lVar16,uVar19,uVar20,lVar21,0);
      return 0;
    }
    goto code_r0x7fff5f54dee4;
  case 0xd:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x40) == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(*(longlong *)(self + 0x40) + 0x10) != '\0') {
      puVar17 = (undefined *)func_0x7fff5f44ff00(uRam00007fff624680e8);
      StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar17,(undefined *)0x0);
      *(undefined **)(self + 0x48) = puVar17;
      thunk_FUN_7fff5f491fd0();
      uVar19 = FUN_7fff60e71970(uRam00007fff62458a70,*(undefined8 *)(self + 0x50),0);
      *(undefined8 *)(self + 0x80) = uVar19;
      thunk_FUN_7fff5f491fd0();
      uVar19 = FUN_7fff60e71050(_DAT_7fff62446cb0,*(undefined8 *)(self + 0x50),_DAT_7fff62424b00,
                                *(undefined8 *)(self + 0x80),0);
      *(undefined8 *)(self + 0x58) = uVar19;
      thunk_FUN_7fff5f491fd0();
      puVar12 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
      puVar17 = *(undefined **)(self + 0x58);
      uVar19 = *(undefined8 *)(self + 0x40);
      puVar11 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
      FUN_7fff60739100(puVar11,uVar19,uRam00007fff624558a8,0);
      if ((puVar12 != (undefined *)0x0) &&
         (puVar17 = ResourceManager_LoadAssetBundle
                              (puVar12,puVar17,(undefined *)0x1,puVar11,(undefined *)0x0),
         lVar16 != 0)) {
        uVar19 = FUN_7fff618a87c0(lVar16,puVar17,0);
        *(undefined8 *)(self + 0x18) = uVar19;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 0xe;
        return 1;
      }
      goto code_r0x7fff5f54def0;
    }
    puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
    if (*(longlong *)(self + 0x60) == 0) goto code_r0x7fff5f54def0;
    puVar12 = (undefined *)FUN_7fff618b0e20(*(longlong *)(self + 0x60),0);
    if ((*(longlong *)(self + 0x40) == 0) || (puVar17 == (undefined *)0x0))
    goto code_r0x7fff5f54def0;
    LocalizeManager_LoadFontAtlas
              (puVar17,puVar12,*(undefined **)(self + 0x68),
               *(byte *)(*(longlong *)(self + 0x40) + 0x10),(undefined *)0x0);
    goto code_r0x7fff5f54dbe5;
  case 0xe:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
    if (puVar17 == (undefined *)0x0) goto code_r0x7fff5f54def0;
    plVar18 = (longlong *)
              ResourceManager_GetAssetObject
                        (puVar17,*(undefined **)(self + 0x58),*(undefined **)(self + 0x80),
                         (undefined *)0x2,0,(undefined *)CONCAT44(uVar6,1),(undefined *)0x0);
    if (plVar18 != (longlong *)0x0) {
      if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7fff6246a948 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar18 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff6246a948 + 0x130) * 8
           ) != _DAT_7fff6246a948)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        plVar9 = plVar18;
      }
    }
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar4 = FUN_7fff618ab2e0(plVar9,0,0);
    if (cVar4 == '\0') {
      StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                (puRam00007fff6241f3e8,(undefined *)0x0);
      if ((lVar16 == 0) || (*(longlong *)(lVar16 + 0xb8) == 0)) goto code_r0x7fff5f54def0;
      uVar19 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6244ac00,0);
      if (*(longlong *)(lVar16 + 0xb8) == 0) goto code_r0x7fff5f54def0;
      uVar20 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6244ad88,0);
      lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
      if (*(int *)(lRam00007fff62467ce8 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(lRam00007fff62467ce8);
      }
      lVar21 = *(longlong *)(*(longlong *)(lRam00007fff62467ce8 + 0xb8) + 0x18);
      if (lVar21 == 0) {
        if (*(int *)(lRam00007fff62467ce8 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(lRam00007fff62467ce8);
        }
        uVar14 = **(undefined8 **)(lRam00007fff62467ce8 + 0xb8);
        lVar21 = func_0x7fff5f44ff00(uRam00007fff62436790);
        FUN_7fff5f4f6880(lVar21,uVar14,uRam00007fff62454eb0,0);
        *(longlong *)(*(longlong *)(lRam00007fff62467ce8 + 0xb8) + 0x18) = lVar21;
code_r0x7fff5f54d806:
        thunk_FUN_7fff5f491fd0();
      }
code_r0x7fff5f54d80e:
      if (lVar16 == 0) goto code_r0x7fff5f54def0;
      goto code_r0x7fff5f54cf84;
    }
    if ((plVar9 == (longlong *)0x0) || (lVar21 = FUN_7fff618b0c90(plVar9,0), lVar21 == 0))
    goto code_r0x7fff5f54def0;
    iVar7 = FUN_7fff60e75c50(lVar21,uRam00007fff623fc538,0);
    lVar21 = FUN_7fff618b0c90(plVar9,0);
    if (lVar21 == 0) goto code_r0x7fff5f54def0;
    uVar19 = FUN_7fff60e7a440(lVar21,0,iVar7,0);
    lVar21 = FUN_7fff618b0c90(plVar9,0);
    if (lVar21 == 0) goto code_r0x7fff5f54def0;
    uVar20 = func_0x7fff60e7a430(lVar21,iVar7 + 1,0);
    puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
    if (*(longlong *)(self + 0x60) == 0) goto code_r0x7fff5f54def0;
    puVar12 = (undefined *)FUN_7fff618b0e20(*(longlong *)(self + 0x60),0);
    if (((*(longlong *)(self + 0x40) == 0) || (puVar17 == (undefined *)0x0)) ||
       (LocalizeManager_LoadFontAtlas
                  (puVar17,puVar12,*(undefined **)(self + 0x68),
                   *(byte *)(*(longlong *)(self + 0x40) + 0x10),(undefined *)0x0), lVar16 == 0))
    goto code_r0x7fff5f54def0;
    lVar21 = *(longlong *)(lVar16 + 0x50);
    if (*(longlong *)(lVar16 + 0xb8) == 0) goto code_r0x7fff5f54def0;
    uVar14 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff62425898,0);
    uVar19 = FUN_7fff60e74b00(uVar14,uVar19,0);
    if (lVar21 == 0) goto code_r0x7fff5f54def0;
    FUN_7fff5ff0eed0(lVar21,uVar19,0);
    lVar21 = *(longlong *)(lVar16 + 0x58);
    if ((*(longlong *)(lVar16 + 0xb8) == 0) ||
       (uVar19 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff624257d0,0), lVar21 == 0)
       ) goto code_r0x7fff5f54def0;
    FUN_7fff5ff0eed0(lVar21,uVar19,0);
    if (*(longlong *)(lVar16 + 0x48) == 0) goto code_r0x7fff5f54def0;
    FUN_7fff618a4510(*(longlong *)(lVar16 + 0x48),1,0);
    if (*(longlong *)(lVar16 + 0x60) == 0) goto code_r0x7fff5f54def0;
    func_0x7fff5fe103b0(*(longlong *)(lVar16 + 0x60),uVar20,0);
    lVar21 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
    if (lVar21 == 0) goto code_r0x7fff5f54def0;
    FUN_7fff5fdd25e0(lVar21,0,0);
    goto code_r0x7fff5f54d9d8;
  case 0xf:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar16 == 0) goto code_r0x7fff5f54def0;
code_r0x7fff5f54d9d8:
    if (*(char *)(lVar16 + 0x68) == '\0') {
      cVar4 = FUN_7fff618f0970(0x1b);
      if (cVar4 == '\0') goto code_r0x7fff5f54da40;
      lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
      if (lVar16 != 0) {
        if (*(char *)(lVar16 + 0x38) == '\0') {
          lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
          if (lVar16 != 0) {
            FUN_7fff5fdd2340(lVar16,0);
            goto code_r0x7fff5f54da40;
          }
        }
        else {
          lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
          if (lVar16 != 0) {
            FUN_7fff5fdd1cd0(lVar16,0);
code_r0x7fff5f54da40:
            *(undefined8 *)(self + 0x18) = 0;
            thunk_FUN_7fff5f491fd0();
            *(undefined4 *)(self + 0x10) = 0xf;
            return 1;
          }
        }
      }
    }
    else {
      lVar21 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
      if (lVar21 != 0) {
        FUN_7fff5fdd25e0(lVar21,1,0);
        if (*(longlong *)(lVar16 + 0x48) != 0) {
          FUN_7fff618a4510(*(longlong *)(lVar16 + 0x48),0,0);
          if (*(longlong *)(self + 0x48) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x48) + 0x10) = 0;
            lVar21 = FUN_7fff60c4bc00(uRam00007fff62457908);
            if ((lVar21 != 0) && (plVar9 = *(longlong **)(lVar21 + 0x28), plVar9 != (longlong *)0x0)
               ) {
              if ((*(byte *)(*plVar9 + 0x130) < *(byte *)(lRam00007fff62418720 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*plVar9 + 200) + -8 +
                   (ulonglong)*(byte *)(lRam00007fff62418720 + 0x130) * 8) != lRam00007fff62418720))
              {
                FUN_7fff5f47c810(plVar9);
                pcVar1 = (code *)swi(3);
                bVar5 = (*pcVar1)();
                return bVar5;
              }
              FUN_7fff5fdd8c30(plVar9,0);
              if (*(longlong *)(self + 0x40) != 0) {
                uVar6 = *(undefined4 *)(*(longlong *)(self + 0x40) + 0x14);
                uVar19 = *(undefined8 *)(self + 0x48);
                uVar20 = func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
                FUN_7fff60739100(uVar20,uVar19,uRam00007fff62455968,0);
                if (cRam00007fff625e1460 == '\0') {
                  FUN_7fff5f47d450(0x7fff62468680);
                  cRam00007fff625e1460 = '\x01';
                }
                puVar17 = (undefined *)func_0x7fff5f44ff00(uRam00007fff62468680);
                StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
                          (puVar17,(undefined *)0x0);
                *(longlong *)(puVar17 + 0x28) = lVar16;
                *(undefined4 *)(puVar17 + 0x10) = 0;
                thunk_FUN_7fff5f491fd0();
                *(undefined8 *)(puVar17 + 0x38) = uVar20;
                *(undefined4 *)(puVar17 + 0x20) = uVar6;
                thunk_FUN_7fff5f491fd0();
                uVar19 = FUN_7fff618a87c0(lVar16,puVar17,0);
                *(undefined8 *)(self + 0x18) = uVar19;
                thunk_FUN_7fff5f491fd0();
                *(undefined4 *)(self + 0x10) = 0x10;
                return 1;
              }
            }
          }
        }
      }
    }
    goto code_r0x7fff5f54def0;
  case 0x10:
    *(undefined8 *)(self + 0x48) = 0;
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    thunk_FUN_7fff5f491fd0();
    *(undefined8 *)(self + 0x80) = 0;
    thunk_FUN_7fff5f491fd0();
code_r0x7fff5f54dbe5:
    *(undefined8 *)(self + 0x40) = 0;
    thunk_FUN_7fff5f491fd0();
    if (lVar16 != 0) {
      lVar21 = *(longlong *)(lVar16 + 0x30);
      if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
         (uVar19 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6241e470,0),
         lVar21 != 0)) {
        FUN_7fff5ff0eed0(lVar21,uVar19,0);
        lVar21 = FUN_7fff60c4bc00(uRam00007fff6245c4f8);
        if (lVar21 != 0) {
          *(undefined1 *)(lVar21 + 0x34) = *(undefined1 *)(lVar16 + 0x68);
          if (*(longlong *)(self + 0x30) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x30) + 0x11) = 0;
            lVar21 = FUN_7fff60c4bc00(_DAT_7fff62459938);
            lVar13 = FUN_7fff60c4bc00(uRam00007fff62457160);
            if (lVar13 != 0) {
              uVar19 = *(undefined8 *)(lVar13 + 0x30);
              lVar13 = FUN_7fff60c4bc00(uRam00007fff62457160);
              if (lVar13 != 0) {
                uVar14 = FUN_7fff5f5a2af0(lVar13,0);
                uVar20 = *(undefined8 *)(self + 0x30);
                uVar15 = func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
                FUN_7fff60739100(uVar15,uVar20,uRam00007fff624554d0,0);
                if (lVar21 != 0) {
                  uVar19 = FUN_7fff603e0bb0(lVar21,uVar19,uVar14,0,uVar15,0);
                  uVar19 = FUN_7fff618a87c0(lVar16,uVar19,0);
                  *(undefined8 *)(self + 0x18) = uVar19;
                  thunk_FUN_7fff5f491fd0();
                  *(undefined4 *)(self + 0x10) = 0x11;
                  return 1;
                }
              }
            }
          }
        }
      }
    }
code_r0x7fff5f54def0:
    FUN_7fff5f47d660();
    pcVar1 = (code *)swi(3);
    bVar5 = (*pcVar1)();
    return bVar5;
  case 0x11:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (*(longlong *)(self + 0x30) == 0) goto code_r0x7fff5f54def0;
    if (*(char *)(*(longlong *)(self + 0x30) + 0x11) == '\0') {
      lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
      if (lVar16 == 0) goto code_r0x7fff5f54def0;
      if (*(char *)(lVar16 + 0x38) == '\0') {
        puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
        if (puVar17 == (undefined *)0x0) goto code_r0x7fff5f54def0;
        plVar18 = (longlong *)LocalizeManager_Get(puVar17,(undefined *)0x0,(undefined *)0x0);
        if (plVar18 == (longlong *)0x0) {
          FUN_7fff60c4bc00(uRam00007fff6245dce0);
          goto code_r0x7fff5f54def0;
        }
        if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7fff62468308 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar18 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff62468308 + 0x130) * 8) != _DAT_7fff62468308)) {
          bVar2 = false;
        }
        else {
          bVar2 = true;
        }
        if (bVar2) {
          plVar9 = plVar18;
        }
        lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
        if (plVar9 == (longlong *)0x0) goto code_r0x7fff5f54def0;
        uVar19 = FUN_7fff5f568150(plVar9,uRam00007fff62412b00,0);
        uVar20 = FUN_7fff5f568150(plVar9,uRam00007fff62412a30,0);
        if (*(int *)(lRam00007fff62467ce8 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(lRam00007fff62467ce8);
        }
        lVar21 = *(longlong *)(*(longlong *)(lRam00007fff62467ce8 + 0xb8) + 0x20);
        if (lVar21 == 0) {
          if (*(int *)(lRam00007fff62467ce8 + 0xe0) == 0) {
            func_0x7fff5f47d6f0(lRam00007fff62467ce8);
          }
          uVar14 = **(undefined8 **)(lRam00007fff62467ce8 + 0xb8);
          lVar21 = func_0x7fff5f44ff00(uRam00007fff62436790);
          FUN_7fff5f4f6880(lVar21,uVar14,uRam00007fff62454f78,0);
          *(longlong *)(*(longlong *)(lRam00007fff62467ce8 + 0xb8) + 0x20) = lVar21;
          goto code_r0x7fff5f54d806;
        }
        goto code_r0x7fff5f54d80e;
      }
    }
    StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose
              (puRam00007fff6243e130,(undefined *)0x0);
  default:
    goto LAB_7fff5f54c6aa;
  }
  uVar19 = func_0x7fff610664f0(0);
  cVar4 = FUN_7fff6068a530(uVar19);
  if (cVar4 == '\0') {
    lVar21 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    FUN_7fff603ce180(lVar21);
code_r0x7fff5f54c160:
    lVar21 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(lVar21 + 0x38) != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 2;
      return 1;
    }
  }
  lVar21 = FUN_7fff60c4bc00(uRam00007fff62457908);
  if (lVar21 == 0) goto code_r0x7fff5f54dee4;
  cVar4 = FUN_7fff5fdd5e50(lVar21);
  if (cVar4 == '\0') {
    lVar21 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    FUN_7fff603cdf30(lVar21);
code_r0x7fff5f54c1e2:
    lVar21 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(lVar21 + 0x38) != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 3;
      return 1;
    }
  }
  puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
  if (puVar17 == (undefined *)0x0) goto code_r0x7fff5f54dee4;
  bVar5 = ResourceManager_CheckBreakAssetsData(puVar17,(undefined *)0x0);
  if (bVar5 != 0) {
    puVar17 = (undefined *)func_0x7fff5f44ff00(uRam00007fff62467e88);
    StageLoginDownloader_Start_StateMachine_System_IDisposable_Dispose(puVar17,(undefined *)0x0);
    *(undefined **)(self + 0x28) = puVar17;
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0x28) == 0) goto code_r0x7fff5f54dee4;
    *(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 0;
    puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
    if (puVar17 == (undefined *)0x0) goto code_r0x7fff5f54dee4;
    plVar18 = (longlong *)LocalizeManager_Get(puVar17,(undefined *)0x0,(undefined *)0x0);
    if (plVar18 == (longlong *)0x0) {
      *(undefined8 *)(self + 0x70) = 0;
    }
    else {
      if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7fff62468308 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar18 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff62468308 + 0x130) * 8
           ) != _DAT_7fff62468308)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        plVar9 = plVar18;
      }
      *(longlong **)(self + 0x70) = plVar9;
    }
    thunk_FUN_7fff5f491fd0();
    lVar13 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
    lVar21 = *(longlong *)(self + 0x70);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    uVar19 = FUN_7fff5f568150(lVar21,uRam00007fff62474808,0);
    lVar21 = *(longlong *)(self + 0x70);
    if (lVar21 == 0) goto code_r0x7fff5f54dee4;
    uVar14 = FUN_7fff5f568150(lVar21,uRam00007fff62474668,0);
    uVar20 = *(undefined8 *)(self + 0x28);
    uVar15 = func_0x7fff5f44ff00(uRam00007fff62436790);
    FUN_7fff5f4f6880(uVar15,uVar20,uRam00007fff62455598,0);
    uVar20 = *(undefined8 *)(self + 0x28);
    uVar8 = func_0x7fff5f44ff00(uRam00007fff62436790);
    FUN_7fff5f4f6880(uVar8,uVar20,uRam00007fff62455658,0);
    if (lVar13 == 0) goto code_r0x7fff5f54dee4;
    FUN_7fff5fdd4990(lVar13,uVar19,uVar14,uVar15,uVar8,0);
code_r0x7fff5f54c3fc:
    if (*(longlong *)(self + 0x28) == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\0') {
      lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
      if (lVar16 != 0) {
        if ((*(char *)(lVar16 + 0x38) == '\0') || (cVar4 = FUN_7fff618f0970(0x1b), cVar4 == '\0')) {
code_r0x7fff5f54c468:
          *(undefined8 *)(self + 0x18) = 0;
          thunk_FUN_7fff5f491fd0();
          *(undefined4 *)(self + 0x10) = 4;
          return 1;
        }
        lVar16 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
        if (lVar16 != 0) {
          FUN_7fff5fdd1cd0(lVar16,0);
          if (*(longlong *)(self + 0x28) != 0) {
            *(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 2;
            goto code_r0x7fff5f54c468;
          }
        }
      }
      goto code_r0x7fff5f54dee4;
    }
    puVar17 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
    if (puVar17 == (undefined *)0x0) goto code_r0x7fff5f54dee4;
    ResourceManager_ClearBreakAssetsData(puVar17,(undefined *)0x0);
    if (*(longlong *)(self + 0x28) == 0) goto code_r0x7fff5f54dee4;
    if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\x01') {
      uVar19 = func_0x7fff5f44ff00(_DAT_7fff62406568);
      FUN_7fff618b74f0(uVar19,_DAT_7fff61b52cc0,0);
      *(undefined8 *)(self + 0x78) = uVar19;
      thunk_FUN_7fff5f491fd0();
      *(undefined8 *)(self + 0x18) = *(undefined8 *)(self + 0x78);
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 5;
      return 1;
    }
    *(undefined8 *)(self + 0x28) = 0;
    thunk_FUN_7fff5f491fd0();
    *(undefined8 *)(self + 0x70) = 0;
    thunk_FUN_7fff5f491fd0();
  }
  lVar21 = FUN_7fff60c4bc00(uRam00007fff6245dce0);
  if (((lVar21 != 0) && (FUN_7fff5fdd25e0(lVar21,1,0), lVar16 != 0)) &&
     (*(longlong *)(lVar16 + 0xb8) != 0)) {
    func_0x7fff5f5684c0(*(longlong *)(lVar16 + 0xb8),0);
    lVar21 = *(longlong *)(lVar16 + 0x30);
    if ((*(longlong *)(lVar16 + 0xb8) != 0) &&
       (uVar19 = FUN_7fff5f568150(*(longlong *)(lVar16 + 0xb8),uRam00007fff6241e540,0), lVar21 != 0)
       ) {
      FUN_7fff5ff0eed0(lVar21,uVar19,0);
      uVar19 = FUN_7fff5f53ecb0(lVar16,0);
      uVar19 = FUN_7fff618a87c0(lVar16,uVar19,0);
      *(undefined8 *)(self + 0x18) = uVar19;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 7;
      return 1;
    }
  }
code_r0x7fff5f54dee4:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  bVar5 = (*pcVar1)();
  return bVar5;
}

