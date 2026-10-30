
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIRegistletMainManager_ChangeActiveDetailWindow
               (undefined *self,byte isActive,undefined *data,undefined *isEquip,undefined *isChange
               ,undefined *action,undefined *methodInfo)

{
  short sVar1;
  code *pcVar2;
  undefined1 uVar3;
  char cVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined8 uVar8;
  undefined *puVar9;
  undefined8 uVar10;
  int iVar11;
  int aiStackX_8 [2];
  short asStackX_10 [4];
  int aiStack_58 [2];
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined8 uStack_38;
  float fStack_30;
  
  if (DAT_7ffe9cadc347 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94b8b0);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c954178);
    FUN_7ffe9996d590(&DAT_7ffe9c953a40);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f6be8);
    FUN_7ffe9996d590(&DAT_7ffe9c94c568);
    FUN_7ffe9996d590(&DAT_7ffe9c91f830);
    FUN_7ffe9996d590(&DAT_7ffe9c93b370);
    FUN_7ffe9996d590(&DAT_7ffe9c943c20);
    FUN_7ffe9996d590(&DAT_7ffe9c8f46c0);
    FUN_7ffe9996d590(&DAT_7ffe9c94c7b0);
    FUN_7ffe9996d590(&DAT_7ffe9c94c4a0);
    FUN_7ffe9996d590(&DAT_7ffe9c917038);
    DAT_7ffe9cadc347 = '\x01';
  }
  if (*(longlong *)(self + 0x58) != 0) {
    FUN_7ffe9bd9b390(*(longlong *)(self + 0x58),isActive,0);
    FUN_7ffe9a04e5e0(self,isActive ^ 1,0);
    FUN_7ffe9a04e7a0(self,0);
    *(undefined **)(self + 0xf0) = data;
    il2cpp_write_barrier_0();
    if (*(longlong *)(self + 0xf0) != 0) {
      uVar3 = func_0x7ffe9a549b10(*(longlong *)(self + 0xf0),0);
      self[0xf8] = uVar3;
    }
    if (isActive == 0) {
      return;
    }
    lVar5 = *(longlong *)(self + 0x78);
    if (action == (undefined *)0x0) {
      action = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8f6be8);
      FUN_7ffe999e6880(action,self,*(undefined8 *)(*(longlong *)self + 400),0);
    }
    if (lVar5 != 0) {
      FUN_7ffe999e7830(lVar5,action,0);
      if (*(longlong *)(self + 0x80) != 0) {
        FUN_7ffe9a404310(*(longlong *)(self + 0x80),**(undefined8 **)(_DAT_7ffe9c9590b8 + 0xb8),0);
        if ((*(longlong *)(self + 0x88) != 0) &&
           (lVar5 = FUN_7ffe9bd98960(*(longlong *)(self + 0x88),0), lVar5 != 0)) {
          FUN_7ffe9bd9b390(lVar5,0,0);
          if (data != (undefined *)0x0) {
            asStackX_10[0] = *(short *)(data + 0x22);
            uVar6 = func_0x7ffe9996c8e0(_DAT_7ffe9c94b8b0,asStackX_10);
            uVar6 = FUN_7ffe9b36a740(_DAT_7ffe9c8f46c0,uVar6,0);
            plVar7 = *(longlong **)(self + 0xe0);
            sVar1 = *(short *)(data + 0x20);
            if (plVar7 == (longlong *)0x0) {
LAB_7ffe9a04c612:
              FUN_7ffe9996d7a0();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            lVar5 = func_0x7ffe9996d210(*(undefined8 *)
                                         (*plVar7 +
                                         ((ulonglong)*(ushort *)(_DAT_7ffe9c954178 + 0x50) + 0x14) *
                                         0x10));
            plVar7 = (longlong *)(**(code **)(lVar5 + 8))(plVar7,(int)sVar1,lVar5);
            lVar5 = *(longlong *)(self + 0x60);
            if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a04c612;
            uVar8 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
            uVar6 = FUN_7ffe9b36a9f0(_DAT_7ffe9c943c20,uVar6,uVar8,0);
            if (lVar5 == 0) goto LAB_7ffe9a04c612;
            FUN_7ffe9a404310(lVar5,uVar6);
            uVar6 = (**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0));
            iVar11 = (int)plVar7[5];
            if (iVar11 != -1) {
              if ((int)*(short *)(data + 0x20) == 0x3ec) {
                iVar11 = *(short *)(data + 0x22) * iVar11;
                aiStackX_8[0] = iVar11;
                uVar8 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
                aiStack_58[0] = iVar11 * 10;
                uVar10 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStack_58);
                uVar6 = FUN_7ffe9b36a9f0(uVar6,uVar8,uVar10,0);
              }
              else {
                puVar9 = UIRegistletMainManager_GetDescriptionValueText
                                   (self,(undefined *)(ulonglong)(uint)(int)*(short *)(data + 0x20),
                                    (int)*(short *)(data + 0x22),iVar11,(undefined *)0x0);
                uVar6 = FUN_7ffe9b36a740(uVar6,puVar9);
              }
            }
            if (*(longlong *)(self + 0x68) == 0) goto LAB_7ffe9a04c606;
            FUN_7ffe9a404310(*(longlong *)(self + 0x68),uVar6);
            puVar9 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953a40);
            if (puVar9 == (undefined *)0x0) goto LAB_7ffe9a04c606;
            puVar9 = MasterRegistletManager_GetGemCartMaster
                               (puVar9,*(short *)(data + 0x20),(undefined *)0x0);
            if (puVar9 != (undefined *)0x0) {
              sVar1 = *(short *)(puVar9 + 0x18);
              uVar6 = _DAT_7ffe9c91f830;
              if (sVar1 == *(short *)(data + 0x22)) {
                uVar6 = _DAT_7ffe9c917038;
              }
              lVar5 = *(longlong *)(self + 0x80);
              if (*(longlong *)(self + 0x20) == 0) {
LAB_7ffe9a04c60c:
                FUN_7ffe9996d7a0();
                pcVar2 = (code *)swi(3);
                (*pcVar2)();
                return;
              }
              uVar8 = FUN_7ffe99a58320(*(longlong *)(self + 0x20),_DAT_7ffe9c94c7b0,0);
              asStackX_10[0] = sVar1;
              uVar10 = func_0x7ffe9996c8e0(_DAT_7ffe9c94b8b0,asStackX_10);
              uVar8 = FUN_7ffe9b36a740(uVar8,uVar10,0);
              uVar6 = FUN_7ffe9b3675b0(uVar6,uVar8,0);
              if (lVar5 == 0) goto LAB_7ffe9a04c60c;
              FUN_7ffe9a404310(lVar5,uVar6,0);
              if (*(longlong *)(self + 0x80) == 0) goto LAB_7ffe9a04c60c;
              lVar5 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x80),0);
              if (DAT_7ffe9cad9b4e == '\0') {
                FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                DAT_7ffe9cad9b4e = '\x01';
              }
              uStack_38 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0xc);
              fStack_30 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x14);
              fStack_50 = (float)uStack_38 * _DAT_7ffe9c049e54;
              fStack_4c = (float)((ulonglong)uStack_38 >> 0x20) * _DAT_7ffe9c049e54;
              fStack_48 = fStack_30 * _DAT_7ffe9c049e54;
              if (lVar5 == 0) goto LAB_7ffe9a04c60c;
              uStack_38 = CONCAT44(fStack_4c,fStack_50);
              fStack_30 = fStack_48;
              FUN_7ffe9bdbfe00(lVar5,&uStack_38,0);
            }
            if ((*(longlong *)(self + 0x88) == 0) ||
               (lVar5 = FUN_7ffe9bd98960(*(longlong *)(self + 0x88),0), lVar5 == 0))
            goto LAB_7ffe9a04c606;
            FUN_7ffe9bd9b390(lVar5,1,0);
            lVar5 = *(longlong *)(self + 0x88);
            cVar4 = func_0x7ffe9a549b10(data,0);
            if (DAT_7ffe9cadc350 == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c956ea8);
              FUN_7ffe9996d590(&DAT_7ffe9c956f78);
              DAT_7ffe9cadc350 = '\x01';
            }
            uVar6 = _DAT_7ffe9c956f78;
            if (cVar4 != '\0') {
              uVar6 = _DAT_7ffe9c956ea8;
            }
            if (lVar5 == 0) goto LAB_7ffe9a04c606;
            FUN_7ffe9a515470(lVar5,uVar6,0);
          }
          lVar5 = *(longlong *)(self + 0x70);
          uVar6 = _DAT_7ffe9c94c568;
          if (((char)isEquip == '\0') && (uVar6 = _DAT_7ffe9c94c4a0, (char)isChange == '\0')) {
            uVar6 = _DAT_7ffe9c93b370;
          }
          if ((*(longlong *)(self + 0x20) != 0) &&
             (uVar6 = FUN_7ffe99a58320(*(longlong *)(self + 0x20),uVar6,0), lVar5 != 0)) {
            FUN_7ffe9a404310(lVar5,uVar6,0);
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a04c606:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

