
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIMobNameLabel_Initialize(undefined *self,undefined *traceObject,undefined *methodInfo)

{
  longlong *plVar1;
  longlong *plVar2;
  code *pcVar3;
  undefined1 uVar4;
  char cVar5;
  int iVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined4 uVar10;
  undefined4 auStackX_10 [2];
  undefined8 uStack_28;
  undefined4 uStack_20;
  
  if (DAT_7fff625e496e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62468250);
    FUN_7fff5f47d450(&DAT_7fff62469570);
    FUN_7fff5f47d450(&DAT_7fff624719b0);
    FUN_7fff5f47d450(&DAT_7fff624718e8);
    FUN_7fff5f47d450(&DAT_7fff624465a0);
    FUN_7fff5f47d450(&DAT_7fff62479db0);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff62458e78);
    FUN_7fff5f47d450(&DAT_7fff624606c8);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff62449e70);
    DAT_7fff625e496e = '\x01';
  }
  auStackX_10[0] = 0;
  if (traceObject == (undefined *)0x0) goto LAB_7fff5fdc1066;
  lVar7 = FUN_7fff618a1ae0(traceObject,0);
  if (lVar7 == 0) goto LAB_7fff5fdc1066;
  lVar7 = FUN_7fff606a6750(lVar7,_DAT_7fff62469570);
  plVar1 = (longlong *)(self + 0x88);
  *plVar1 = lVar7;
  thunk_FUN_7fff5f491fd0();
  if (*plVar1 == 0) goto LAB_7fff5fdc1066;
  uVar4 = FUN_7fff5f259320(0x17,_DAT_7fff62479db0,*plVar1,4);
  self[0xf8] = uVar4;
  lVar7 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
  if (lVar7 == 0) goto LAB_7fff5fdc1066;
  iVar6 = FUN_7fff6037cb10(lVar7,0);
  if (iVar6 == 3) {
LAB_7fff5fdc0c19:
    self[0x108] = 1;
  }
  else {
    lVar7 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
    if (lVar7 == 0) goto LAB_7fff5fdc1066;
    iVar6 = FUN_7fff6037cb10(lVar7,0);
    if (iVar6 == 0x19) goto LAB_7fff5fdc0c19;
    lVar7 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
    if (lVar7 == 0) goto LAB_7fff5fdc1066;
    iVar6 = FUN_7fff6037cb10(lVar7,0);
    if (iVar6 == 0x1a) goto LAB_7fff5fdc0c19;
  }
  if (DAT_7fff625e496d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fe590);
    FUN_7fff5f47d450(&DAT_7fff62458e78);
    DAT_7fff625e496d = '\x01';
  }
  lVar7 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
  if (lVar7 != 0) {
    iVar6 = FUN_7fff6037cb10(lVar7,0);
    if ((iVar6 == 0x20) && (plVar2 = (longlong *)*plVar1, plVar2 != (longlong *)0x0)) {
      if ((*(byte *)(_DAT_7fff623fe590 + 0x130) <= *(byte *)(*plVar2 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar2 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff623fe590 + 0x130) * 8)
          == _DAT_7fff623fe590)) {
        if ((*(byte *)(*plVar2 + 0x130) < *(byte *)(_DAT_7fff623fe590 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar2 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff623fe590 + 0x130) * 8) != _DAT_7fff623fe590)) {
          FUN_7fff5f47c810(plVar2);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        if ((char)plVar2[0x2d] != '\0') {
          self[0x108] = 1;
        }
      }
    }
    if (*plVar1 != 0) {
      lVar7 = FUN_7fff5f252ec0(7,_DAT_7fff62479db0);
      uVar9 = **(undefined8 **)(_DAT_7fff624606c8 + 0xb8);
      if (lVar7 != 0) {
        if (0 < *(int *)(lVar7 + 0x10)) {
          if (*plVar1 == 0) goto LAB_7fff5fdc1066;
          cVar5 = FUN_7fff5f259320(0x17,_DAT_7fff62479db0,*plVar1,0x10);
          if (cVar5 == '\0') {
            if (*plVar1 == 0) goto LAB_7fff5fdc1066;
            lVar8 = FUN_7fff5f252ec0(9,_DAT_7fff62479db0);
            if (lVar8 == 0) goto LAB_7fff5fdc1066;
            auStackX_10[0] = FUN_7fff5f252ec0(1,_DAT_7fff624465a0,lVar8);
            uVar9 = FUN_7fff6100e780(auStackX_10,0);
            uVar9 = FUN_7fff60e71650(_DAT_7fff62449e70,uVar9,_DAT_7fff623fda58,0);
          }
          uVar9 = FUN_7fff60e71970(uVar9,lVar7,0);
        }
        if (*plVar1 != 0) {
          uVar10 = FUN_7fff5f254d60(0,_DAT_7fff62479db0);
          FUN_7fff5fdc6140(self,traceObject,uVar10,uVar9,1,0,0);
          *(undefined4 *)(self + 0xfc) = 0x3f800000;
          if (*(longlong *)(self + 0x50) != 0) {
            lVar7 = FUN_7fff618a4a10(*(longlong *)(self + 0x50),0);
            if (DAT_7fff625e12cb == '\0') {
              FUN_7fff5f47d450(&DAT_7fff62403238);
              DAT_7fff625e12cb = '\x01';
            }
            if (lVar7 != 0) {
              uStack_20 = 0;
              uStack_28 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403238 + 0xb8) + 8);
              FUN_7fff618c8f80(lVar7,&uStack_28,0);
              if (*(longlong *)(self + 0x50) != 0) {
                FUN_7fff618a4510(*(longlong *)(self + 0x50),0,0);
                if (*(longlong *)(self + 0x90) != 0) {
                  uVar9 = FUN_7fff606a6750(*(longlong *)(self + 0x90),_DAT_7fff62468250);
                  *(undefined8 *)(self + 0x98) = uVar9;
                  thunk_FUN_7fff5f491fd0();
                  if (*(longlong *)(self + 0x90) != 0) {
                    FUN_7fff618a4510(*(longlong *)(self + 0x90),0,0);
                    uVar9 = *(undefined8 *)(self + 0xe0);
                    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
                      func_0x7fff5f47d6f0();
                    }
                    cVar5 = FUN_7fff618ab2e0(uVar9,0,0);
                    if (cVar5 != '\0') {
                      if (*(longlong *)(self + 0xe0) == 0) goto LAB_7fff5fdc1066;
                      uVar9 = FUN_7fff606a6750(*(longlong *)(self + 0xe0),_DAT_7fff62468250);
                      *(undefined8 *)(self + 0xe8) = uVar9;
                      thunk_FUN_7fff5f491fd0();
                      if (*(longlong *)(self + 0xe0) == 0) goto LAB_7fff5fdc1066;
                      FUN_7fff618a4510(*(longlong *)(self + 0xe0),0,0);
                    }
                    if (*(longlong *)(self + 0xa0) != 0) {
                      FUN_7fff618a4510(*(longlong *)(self + 0xa0),0,0);
                      if (*(longlong *)(self + 0xa0) != 0) {
                        uVar9 = FUN_7fff606a6750(*(longlong *)(self + 0xa0),_DAT_7fff624719b0);
                        *(undefined8 *)(self + 0xa8) = uVar9;
                        thunk_FUN_7fff5f491fd0();
                        if (*(longlong *)(self + 0xb8) != 0) {
                          FUN_7fff618a4510(*(longlong *)(self + 0xb8),0,0);
                          if (*(longlong *)(self + 0xc0) != 0) {
                            FUN_7fff618a4510(*(longlong *)(self + 0xc0),0,0);
                            if (*(longlong *)(self + 0xc0) != 0) {
                              uVar9 = FUN_7fff606a6750(*(longlong *)(self + 0xc0),_DAT_7fff624719b0)
                              ;
                              *(undefined8 *)(self + 200) = uVar9;
                              thunk_FUN_7fff5f491fd0();
                              if (*(longlong *)(self + 0x128) != 0) {
                                uVar9 = FUN_7fff606a6750(*(longlong *)(self + 0x128),
                                                         _DAT_7fff624718e8);
                                *(undefined8 *)(self + 0x130) = uVar9;
                                thunk_FUN_7fff5f491fd0();
                                (**(code **)(*(longlong *)self + 0x1d8))
                                          (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
                                return;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7fff5fdc1066:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

