
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ReceiveBattleResult_Attack
               (undefined *returnCode,byte archetypeType,int archetypeId,undefined *response,
               undefined *methodInfo)

{
  byte bVar1;
  short sVar2;
  code *pcVar3;
  char cVar4;
  undefined4 uVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  undefined *thisObject;
  longlong lVar9;
  longlong *plVar10;
  undefined8 uVar11;
  uint uVar12;
  uint uVar13;
  undefined8 uStack_58;
  longlong lStack_50;
  longlong lStack_48;
  longlong lStack_40;
  longlong alStack_38 [2];
  
  if (DAT_7ffe9cae0cab == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c968270);
    FUN_7ffe9996d590(&DAT_7ffe9c955028);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    DAT_7ffe9cae0cab = '\x01';
  }
  uVar13 = 0;
  alStack_38[0] = 0;
  lStack_40 = 0;
  lStack_48 = 0;
  lStack_50 = 0;
  lVar6 = FUN_7ffe9a47bac0(0);
  if (archetypeType == 0) {
    if (DAT_7ffe9cae0caa == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c952a50);
      DAT_7ffe9cae0caa = '\x01';
    }
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if ((response == (undefined *)0x0) || (lVar7 == 0)) {
LAB_7ffe9aade9f9:
      FUN_7ffe9996d7a0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    FUN_7ffe9a8da6c0(lVar7,*(undefined8 *)(response + 0x30));
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(lVar6,0);
    if (cVar4 != '\0') {
      if ((lVar6 == 0) ||
         (thisObject = (undefined *)FUN_7ffe9a47f780(lVar6,0), thisObject == (undefined *)0x0))
      goto LAB_7ffe9aade9f9;
      plVar10 = (longlong *)GemCartBufferManager_GetGemCartBuffer(thisObject,0x23,(undefined *)0x0);
      if (plVar10 != (longlong *)0x0) {
        if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c955028 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar10 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c955028 + 0x130) * 8) != _DAT_7ffe9c955028)) {
          FUN_7ffe9996c950(plVar10);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        GemCartBuffer_StartDashBuff_Synchronization
                  ((undefined *)plVar10,*(short *)(response + 0x4a),(undefined *)0x0);
      }
    }
  }
  else if (archetypeType == 9) {
    if (DAT_7ffe9cae0caa == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c952a50);
      DAT_7ffe9cae0caa = '\x01';
    }
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if ((response == (undefined *)0x0) || (lVar7 == 0)) goto LAB_7ffe9aade9f9;
    FUN_7ffe9a8da6c0(lVar7,*(undefined8 *)(response + 0x30),0);
  }
  else {
    if (DAT_7ffe9cae0caa == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c952a50);
      DAT_7ffe9cae0caa = '\x01';
    }
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    uStack_58 = 0;
    func_0x7ffe9bb9e840(&uStack_58,archetypeType,archetypeId,0);
    if ((response == (undefined *)0x0) || (lVar7 == 0)) {
      FUN_7ffe9996d7a0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    FUN_7ffe9a8da220(lVar7,uStack_58,*(undefined8 *)(response + 0x30),0);
  }
  bVar1 = response[0x48];
  if (DAT_7ffe9cae0cd7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922d60);
    DAT_7ffe9cae0cd7 = '\x01';
  }
  *(byte *)(*(longlong *)(_DAT_7ffe9c922d60 + 0xb8) + 0x10) = bVar1 & 1;
  if ((int)returnCode == 0) {
    lVar7 = *(longlong *)(response + 0x38);
    sVar2 = *(short *)(response + 0x20);
    if ((lVar7 != 0) && (*(longlong *)(lVar7 + 0x18) != 0)) {
LAB_7ffe9aade4dd:
      if ((int)uVar13 < (int)*(uint *)(lVar7 + 0x18)) {
        if (*(uint *)(lVar7 + 0x18) <= uVar13) goto LAB_7ffe9aadea0e;
        lVar8 = *(longlong *)(lVar7 + 0x20 + (longlong)(int)uVar13 * 8);
        if (lVar8 == 0) goto LAB_7ffe9aade9f9;
        if (*(char *)(lVar8 + 0x20) == '\0') {
          if (sVar2 == 0x366) {
            if (archetypeType == 0) {
              FUN_7ffe9a6a8780(response[0x22],0);
            }
          }
          else if (sVar2 == 0x368) {
            if (archetypeType == 0) {
              if (lVar6 == 0) goto LAB_7ffe9aade9f9;
              uVar11 = FUN_7ffe9a480070(lVar6,0);
              FUN_7ffe9a6a67a0(uVar11,response,lVar8);
            }
          }
          else if (sVar2 == 0x6c) {
            if (archetypeType == 0) {
              if (((lVar6 == 0) ||
                  (plVar10 = (longlong *)FUN_7ffe9a480070(lVar6,0), plVar10 == (longlong *)0x0)) ||
                 (lVar9 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0))
                 , lVar9 == 0)) goto LAB_7ffe9aade9f9;
              cVar4 = FUN_7ffe9abc2210(lVar9,0x368,alStack_38);
              if (cVar4 != '\0') {
                if (alStack_38[0] == 0) goto LAB_7ffe9aade9f9;
                FUN_7ffe9a7877a0(alStack_38[0],0x6c,response[0x22]);
              }
            }
          }
          else if (sVar2 == 0x6d) {
            if (archetypeType == 0) {
              if (((lVar6 == 0) ||
                  (plVar10 = (longlong *)FUN_7ffe9a480070(lVar6,0), plVar10 == (longlong *)0x0)) ||
                 (lVar9 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0))
                 , lVar9 == 0)) goto LAB_7ffe9aade9f9;
              cVar4 = FUN_7ffe9abc2210(lVar9,0x368,&lStack_40);
              if (cVar4 != '\0') {
                if (lStack_40 == 0) goto LAB_7ffe9aade9f9;
                FUN_7ffe9a7877a0(lStack_40,0x6d,response[0x22]);
              }
            }
          }
          else if (sVar2 == 0x70) {
            if (archetypeType == 0) {
              if (((lVar6 == 0) ||
                  (plVar10 = (longlong *)FUN_7ffe9a480070(lVar6,0), plVar10 == (longlong *)0x0)) ||
                 (lVar9 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0))
                 , lVar9 == 0)) goto LAB_7ffe9aade9f9;
              cVar4 = FUN_7ffe9abc2210(lVar9,0x368,&lStack_48);
              if (cVar4 != '\0') {
                if (lStack_48 == 0) goto LAB_7ffe9aade9f9;
                FUN_7ffe9a7877a0(lStack_48,0x70,response[0x22]);
              }
            }
          }
          else if ((sVar2 == 0x71) && (archetypeType == 0)) {
            if ((lVar6 == 0) ||
               ((plVar10 = (longlong *)FUN_7ffe9a480070(lVar6,0), plVar10 == (longlong *)0x0 ||
                (lVar9 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
                lVar9 == 0)))) goto LAB_7ffe9aade9f9;
            cVar4 = FUN_7ffe9abc2210(lVar9,0x368,&lStack_50);
            if (cVar4 != '\0') {
              if (lStack_50 == 0) goto LAB_7ffe9aade9f9;
              FUN_7ffe9a7877a0(lStack_50,0x71,response[0x22]);
            }
          }
          lVar9 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (lVar9 == 0) goto LAB_7ffe9aade9f9;
          FUN_7ffe9a33d5b0(lVar9,response[0x28],lVar8);
          if (sVar2 == 0x50) {
            if (archetypeType == 0) {
              FUN_7ffe9a754ac0(lVar8,0);
              uVar13 = uVar13 + 1;
              goto LAB_7ffe9aade4dd;
            }
          }
          else if (sVar2 == 0x10d) {
            if (archetypeType == 0) {
              FUN_7ffe9a73b5a0(lVar8,0);
              uVar13 = uVar13 + 1;
              goto LAB_7ffe9aade4dd;
            }
          }
          else if (sVar2 == 0x3eb) {
            if (((archetypeType == 0) && (*(longlong *)(response + 0x58) != 0)) &&
               (cVar4 = FUN_7ffe9bc60070(*(longlong *)(response + 0x58),0x3eb,0), cVar4 != '\0')) {
              if ((*(longlong *)(response + 0x58) == 0) ||
                 (uVar5 = FUN_7ffe9bc601e0(*(longlong *)(response + 0x58),0x3eb,0), lVar6 == 0))
              goto LAB_7ffe9aade9f9;
              uVar11 = FUN_7ffe9a47fe30(lVar6,0);
              FUN_7ffe9a63de80(uVar11,uVar5,0);
              uVar13 = uVar13 + 1;
              goto LAB_7ffe9aade4dd;
            }
          }
          else if (sVar2 == 0x3ec) {
            if (archetypeType == 0) {
              FUN_7ffe9a635ff0(lVar8,0);
              uVar13 = uVar13 + 1;
              goto LAB_7ffe9aade4dd;
            }
          }
          else if (sVar2 == 0x2d1) {
            if (archetypeType == 0) {
              FUN_7ffe9a7674c0(lVar8,0);
              uVar13 = uVar13 + 1;
              goto LAB_7ffe9aade4dd;
            }
          }
          else if (sVar2 == 0x2d2) {
            if (archetypeType == 0) {
              FUN_7ffe9a76e660(lVar8,0);
              uVar13 = uVar13 + 1;
              goto LAB_7ffe9aade4dd;
            }
          }
          else if (sVar2 == 0x231) {
            if (archetypeType == 0) {
              FUN_7ffe9a68ecf0(lVar8,0);
              uVar13 = uVar13 + 1;
              goto LAB_7ffe9aade4dd;
            }
          }
          else if ((sVar2 == 0x465) && (archetypeType == 0)) {
            FUN_7ffe9a716970(lVar8,0);
          }
          uVar13 = uVar13 + 1;
          goto LAB_7ffe9aade4dd;
        }
        if (*(char *)(lVar8 + 0x20) == -1) {
          lVar9 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (lVar9 == 0) goto LAB_7ffe9aade9f9;
          FUN_7ffe9a33d5b0(lVar9,response[0x28],lVar8);
          uVar13 = uVar13 + 1;
        }
        else {
          lVar9 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (lVar9 == 0) goto LAB_7ffe9aade9f9;
          FUN_7ffe9a33ab00(lVar9,lVar8,0);
          uVar13 = uVar13 + 1;
        }
        goto LAB_7ffe9aade4dd;
      }
    }
    FUN_7ffe9aadddf0(archetypeType,archetypeId,response,0);
    if (sVar2 == 0x87) {
      FUN_7ffe9a6cafd0(response[0x22],0);
    }
    else if (sVar2 == 0x9f) {
      FUN_7ffe9a6da940(response[0x22],0);
    }
  }
  else {
    lVar6 = *(longlong *)(response + 0x38);
    uVar12 = uVar13;
    if (lVar6 != 0) {
      while ((int)uVar12 < (int)*(uint *)(lVar6 + 0x18)) {
        if (*(uint *)(lVar6 + 0x18) <= uVar12) goto LAB_7ffe9aadea0e;
        lVar7 = *(longlong *)(lVar6 + 0x20 + (longlong)(int)uVar12 * 8);
        if (lVar7 == 0) goto LAB_7ffe9aade9f9;
        if (*(char *)(lVar7 + 0x20) == '\0') {
          lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (lVar8 == 0) goto LAB_7ffe9aade9f9;
          FUN_7ffe9a33d5b0(lVar8,response[0x28],lVar7,0);
          uVar12 = uVar12 + 1;
        }
        else {
          lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (lVar8 == 0) goto LAB_7ffe9aade9f9;
          FUN_7ffe9a33ab00(lVar8,lVar7);
          uVar12 = uVar12 + 1;
        }
      }
    }
    lVar6 = *(longlong *)(response + 0x40);
    if (lVar6 != 0) {
      while ((int)uVar13 < (int)*(uint *)(lVar6 + 0x18)) {
        if (*(uint *)(lVar6 + 0x18) <= uVar13) {
LAB_7ffe9aadea0e:
          FUN_7ffe9996d790();
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        lVar7 = *(longlong *)(lVar6 + 0x20 + (longlong)(int)uVar13 * 8);
        if (lVar7 == 0) goto LAB_7ffe9aade9f9;
        if (*(char *)(lVar7 + 0x20) == '\0') {
          lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (lVar8 == 0) goto LAB_7ffe9aade9f9;
          FUN_7ffe9a33d390(lVar8,lVar7,0);
          uVar13 = uVar13 + 1;
        }
        else {
          lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
          if (lVar8 == 0) goto LAB_7ffe9aade9f9;
          FUN_7ffe9a33abb0(lVar8,lVar7);
          uVar13 = uVar13 + 1;
        }
      }
    }
  }
  return;
}

