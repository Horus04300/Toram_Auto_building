
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerDataManager_OnAbnormalDamage
               (undefined *thisObject,undefined *response,undefined *methodInfo)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  code *pcVar4;
  char cVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  longlong alStackX_10 [2];
  undefined8 uStackX_20;
  undefined8 in_stack_ffffffffffffff98;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined8 uStack_48;
  undefined4 uStack_40;
  undefined1 auStack_38 [16];
  
  uVar12 = (undefined4)((ulonglong)in_stack_ffffffffffffff98 >> 0x20);
  if (DAT_7ffe9cadddf9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fb7f8);
    FUN_7ffe9996d590(&DAT_7ffe9c941198);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c969bf0);
    FUN_7ffe9996d590(&DAT_7ffe9c903908);
    DAT_7ffe9cadddf9 = '\x01';
  }
  uVar11 = 0;
  uStackX_20 = 0;
  alStackX_10[0] = 0;
  if ((response != (undefined *)0x0) && (lVar6 = *(longlong *)(response + 0x30), lVar6 != 0)) {
    uVar13 = *(undefined4 *)(lVar6 + 0x20);
    uVar3 = *(undefined4 *)(lVar6 + 0x28);
    if (DAT_7ffe9caddde3 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c93e0e0);
      DAT_7ffe9caddde3 = '\x01';
    }
    if (*(longlong *)(thisObject + 0x60) != 0) {
      uVar10 = CONCAT44(uVar12,uVar3);
      FUN_7ffe9974b4e0(0x39,_DAT_7ffe9c93e0e0,*(longlong *)(thisObject + 0x60),uVar13,uVar10);
      uVar12 = (undefined4)((ulonglong)uVar10 >> 0x20);
      lVar6 = *(longlong *)(response + 0x30);
      if (lVar6 != 0) {
        sVar1 = *(short *)(lVar6 + 0x24);
        sVar2 = *(short *)(lVar6 + 0x2c);
        if (DAT_7ffe9caddde4 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c93e0e0);
          DAT_7ffe9caddde4 = '\x01';
        }
        if (*(longlong *)(thisObject + 0x60) != 0) {
          uVar10 = CONCAT44(uVar12,(int)sVar2);
          FUN_7ffe9974b4e0(0x38,_DAT_7ffe9c93e0e0,*(longlong *)(thisObject + 0x60),(int)sVar1,uVar10
                          );
          uVar12 = (undefined4)((ulonglong)uVar10 >> 0x20);
          if (response[0x25] == '\b') {
            lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
            uVar13 = *(undefined4 *)(response + 0x28);
            if (DAT_7ffe9caddda3 == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c93e0e0);
              DAT_7ffe9caddda3 = '\x01';
            }
            if (((*(longlong *)(thisObject + 0x60) != 0) &&
                (lVar7 = FUN_7ffe99742ec0(0x1c,_DAT_7ffe9c93e0e0), lVar7 != 0)) &&
               (puVar8 = (undefined8 *)FUN_7ffe9bdbf710(auStack_38,lVar7,0), lVar6 != 0)) {
              uStack_48 = *puVar8;
              uStack_40 = *(undefined4 *)(puVar8 + 1);
              FUN_7ffe99ca8990(lVar6,1,uVar13,&uStack_48,CONCAT44(uVar12,_DAT_7ffe9c049b18),0);
              return;
            }
          }
          else {
            if (response[0x25] != '%') {
              return;
            }
            lVar6 = FUN_7ffe9a47fe30(thisObject,0);
            if (lVar6 != 0) {
              lVar6 = *(longlong *)(lVar6 + 0x58);
              lVar7 = FUN_7ffe9a47fe30(thisObject,0);
              if (lVar7 != 0) {
                uVar10 = *(undefined8 *)(lVar7 + 0x58);
                uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8fb7f8);
                FUN_7ffe9ad35a70(uVar9,uVar10,_DAT_7ffe9c903908,0);
                if (DAT_7ffe9caddda2 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c93e0e0);
                  DAT_7ffe9caddda2 = '\x01';
                }
                uVar10 = uVar11;
                if (*(longlong *)(thisObject + 0x60) != 0) {
                  uVar10 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c93e0e0);
                }
                if (DAT_7ffe9caddda2 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c93e0e0);
                  DAT_7ffe9caddda2 = '\x01';
                }
                if (*(longlong *)(thisObject + 0x60) != 0) {
                  uVar11 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c93e0e0);
                }
                if (lVar6 != 0) {
                  FUN_7ffe9a9b7770(lVar6,0x11f26be0,uVar9,uVar10,uVar11,0,0);
                  uVar13 = (undefined4)((ulonglong)uVar11 >> 0x20);
                  uVar12 = *(undefined4 *)(response + 0x28);
                  if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
                    func_0x7ffe9996d830();
                  }
                  FUN_7ffe9a7dd720(uVar12,0);
                  lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
                  uVar12 = *(undefined4 *)(response + 0x28);
                  if (DAT_7ffe9caddda2 == '\0') {
                    FUN_7ffe9996d590(&DAT_7ffe9c93e0e0);
                    DAT_7ffe9caddda2 = '\x01';
                  }
                  if (((*(longlong *)(thisObject + 0x60) != 0) &&
                      (lVar7 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c93e0e0), lVar7 != 0)) &&
                     ((lVar7 = FUN_7ffe9bd9b890(lVar7,0), lVar7 != 0 &&
                      (puVar8 = (undefined8 *)FUN_7ffe9bdbf710(auStack_38,lVar7,0), lVar6 != 0)))) {
                    uStack_48 = *puVar8;
                    uStack_40 = *(undefined4 *)(puVar8 + 1);
                    FUN_7ffe99ca74a0(lVar6,1,uVar12,&uStack_48,CONCAT44(uVar13,_DAT_7ffe9c049b18),0)
                    ;
                    lVar6 = FUN_7ffe9a4803f0(thisObject,0);
                    if (lVar6 != 0) {
                      cVar5 = FUN_7ffe9a7cbb30(lVar6,0x70,&uStackX_20);
                      if (cVar5 != '\0') {
                        lVar6 = FUN_7ffe9a4803f0(thisObject,0);
                        if (lVar6 == 0) goto LAB_7ffe9a47cd44;
                        FUN_7ffe9a7cafa0(lVar6,0x70);
                        lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
                        if (lVar6 == 0) goto LAB_7ffe9a47cd44;
                        FUN_7ffe9a29adb0(lVar6,0);
                      }
                      lVar6 = FUN_7ffe9a4803f0(thisObject,0);
                      if (lVar6 != 0) {
                        cVar5 = FUN_7ffe9abc2210(lVar6,0x2ce,alStackX_10,_DAT_7ffe9c969bf0);
                        if (cVar5 != '\0') {
                          if (alStackX_10[0] == 0) goto LAB_7ffe9a47cd44;
                          FUN_7ffe9a7a2220(alStackX_10[0],0);
                        }
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
LAB_7ffe9a47cd44:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

