
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
  
  if (DAT_7ffe9cadd213 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c961438);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c96ab98);
    FUN_7ffe9996d590(&DAT_7ffe9c96aad0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7318);
    FUN_7ffe9996d590(&DAT_7ffe9c943788);
    DAT_7ffe9cadd213 = '\x01';
  }
  auStackX_10[0] = 0;
  if (traceObject == (undefined *)0x0) goto LAB_7ffe9a2b6226;
  lVar7 = FUN_7ffe9bd98960(traceObject,0);
  if (lVar7 == 0) goto LAB_7ffe9a2b6226;
  lVar7 = FUN_7ffe9ab9c3a0(lVar7,_DAT_7ffe9c962758);
  plVar1 = (longlong *)(self + 0x88);
  *plVar1 = lVar7;
  il2cpp_write_barrier_0();
  if (*plVar1 == 0) goto LAB_7ffe9a2b6226;
  uVar4 = FUN_7ffe99749320(0x17,_DAT_7ffe9c9724e0,*plVar1,4);
  self[0xf8] = uVar4;
  lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
  if (lVar7 == 0) goto LAB_7ffe9a2b6226;
  iVar6 = FUN_7ffe9a872680(lVar7,0);
  if (iVar6 == 3) {
LAB_7ffe9a2b5dd9:
    self[0x108] = 1;
  }
  else {
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar7 == 0) goto LAB_7ffe9a2b6226;
    iVar6 = FUN_7ffe9a872680(lVar7,0);
    if (iVar6 == 0x19) goto LAB_7ffe9a2b5dd9;
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar7 == 0) goto LAB_7ffe9a2b6226;
    iVar6 = FUN_7ffe9a872680(lVar7,0);
    if (iVar6 == 0x1a) goto LAB_7ffe9a2b5dd9;
  }
  if (DAT_7ffe9cadd212 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f6ba0);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    DAT_7ffe9cadd212 = '\x01';
  }
  lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
  if (lVar7 != 0) {
    iVar6 = FUN_7ffe9a872680(lVar7,0);
    if ((iVar6 == 0x20) && (plVar2 = (longlong *)*plVar1, plVar2 != (longlong *)0x0)) {
      if ((*(byte *)(_DAT_7ffe9c8f6ba0 + 0x130) <= *(byte *)(*plVar2 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar2 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f6ba0 + 0x130) * 8)
          == _DAT_7ffe9c8f6ba0)) {
        if ((*(byte *)(*plVar2 + 0x130) < *(byte *)(_DAT_7ffe9c8f6ba0 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar2 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c8f6ba0 + 0x130) * 8) != _DAT_7ffe9c8f6ba0)) {
          FUN_7ffe9996c950(plVar2);
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
      lVar7 = FUN_7ffe99742ec0(7,_DAT_7ffe9c9724e0);
      uVar9 = **(undefined8 **)(_DAT_7ffe9c9590b8 + 0xb8);
      if (lVar7 != 0) {
        if (0 < *(int *)(lVar7 + 0x10)) {
          if (*plVar1 == 0) goto LAB_7ffe9a2b6226;
          cVar5 = FUN_7ffe99749320(0x17,_DAT_7ffe9c9724e0,*plVar1,0x10);
          if (cVar5 == '\0') {
            if (*plVar1 == 0) goto LAB_7ffe9a2b6226;
            lVar8 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0);
            if (lVar8 == 0) goto LAB_7ffe9a2b6226;
            auStackX_10[0] = FUN_7ffe99742ec0(1,_DAT_7ffe9c93ed20,lVar8);
            uVar9 = FUN_7ffe9b5043c0(auStackX_10,0);
            uVar9 = FUN_7ffe9b367290(_DAT_7ffe9c943788,uVar9,_DAT_7ffe9c8f7318,0);
          }
          uVar9 = FUN_7ffe9b3675b0(uVar9,lVar7,0);
        }
        if (*plVar1 != 0) {
          uVar10 = FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0);
          FUN_7ffe9a2bb300(self,traceObject,uVar10,uVar9,1,0,0);
          *(undefined4 *)(self + 0xfc) = 0x3f800000;
          if (*(longlong *)(self + 0x50) != 0) {
            lVar7 = FUN_7ffe9bd9b890(*(longlong *)(self + 0x50),0);
            if (DAT_7ffe9cad9b4b == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c8fbb88);
              DAT_7ffe9cad9b4b = '\x01';
            }
            if (lVar7 != 0) {
              uStack_20 = 0;
              uStack_28 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fbb88 + 0xb8) + 8);
              FUN_7ffe9bdbfe00(lVar7,&uStack_28,0);
              if (*(longlong *)(self + 0x50) != 0) {
                FUN_7ffe9bd9b390(*(longlong *)(self + 0x50),0,0);
                if (*(longlong *)(self + 0x90) != 0) {
                  uVar9 = FUN_7ffe9ab9c3a0(*(longlong *)(self + 0x90),_DAT_7ffe9c961438);
                  *(undefined8 *)(self + 0x98) = uVar9;
                  il2cpp_write_barrier_0();
                  if (*(longlong *)(self + 0x90) != 0) {
                    FUN_7ffe9bd9b390(*(longlong *)(self + 0x90),0,0);
                    uVar9 = *(undefined8 *)(self + 0xe0);
                    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    cVar5 = FUN_7ffe9bda2160(uVar9,0,0);
                    if (cVar5 != '\0') {
                      if (*(longlong *)(self + 0xe0) == 0) goto LAB_7ffe9a2b6226;
                      uVar9 = FUN_7ffe9ab9c3a0(*(longlong *)(self + 0xe0),_DAT_7ffe9c961438);
                      *(undefined8 *)(self + 0xe8) = uVar9;
                      il2cpp_write_barrier_0();
                      if (*(longlong *)(self + 0xe0) == 0) goto LAB_7ffe9a2b6226;
                      FUN_7ffe9bd9b390(*(longlong *)(self + 0xe0),0,0);
                    }
                    if (*(longlong *)(self + 0xa0) != 0) {
                      FUN_7ffe9bd9b390(*(longlong *)(self + 0xa0),0,0);
                      if (*(longlong *)(self + 0xa0) != 0) {
                        uVar9 = FUN_7ffe9ab9c3a0(*(longlong *)(self + 0xa0),_DAT_7ffe9c96ab98);
                        *(undefined8 *)(self + 0xa8) = uVar9;
                        il2cpp_write_barrier_0();
                        if (*(longlong *)(self + 0xb8) != 0) {
                          FUN_7ffe9bd9b390(*(longlong *)(self + 0xb8),0,0);
                          if (*(longlong *)(self + 0xc0) != 0) {
                            FUN_7ffe9bd9b390(*(longlong *)(self + 0xc0),0,0);
                            if (*(longlong *)(self + 0xc0) != 0) {
                              uVar9 = FUN_7ffe9ab9c3a0(*(longlong *)(self + 0xc0),_DAT_7ffe9c96ab98)
                              ;
                              *(undefined8 *)(self + 200) = uVar9;
                              il2cpp_write_barrier_0();
                              if (*(longlong *)(self + 0x128) != 0) {
                                uVar9 = FUN_7ffe9ab9c3a0(*(longlong *)(self + 0x128),
                                                         _DAT_7ffe9c96aad0);
                                *(undefined8 *)(self + 0x130) = uVar9;
                                il2cpp_write_barrier_0();
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
LAB_7ffe9a2b6226:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

