
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobActionManager_OnSetStatus(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  longlong *plVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  code *pcVar6;
  char cVar7;
  int iVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  ulonglong uVar12;
  longlong lVar13;
  undefined8 *puVar14;
  ushort uVar15;
  longlong lVar16;
  uint uVar17;
  longlong lStackX_18;
  undefined8 uStackX_20;
  undefined8 in_stack_ffffffffffffff48;
  undefined4 uVar18;
  undefined8 uStack_80;
  undefined8 uStack_78;
  ulonglong uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  ulonglong uStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  
  uVar18 = (undefined4)((ulonglong)in_stack_ffffffffffffff48 >> 0x20);
  if (DAT_7fff625e4c59 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245a0e0);
    FUN_7fff5f47d450(&DAT_7fff6245a1a8);
    FUN_7fff5f47d450(&DAT_7fff623f8de8);
    FUN_7fff5f47d450(&DAT_7fff624306e0);
    FUN_7fff5f47d450(&DAT_7fff624307a8);
    FUN_7fff5f47d450(0x7fff62430868);
    FUN_7fff5f47d450(&DAT_7fff6242b1b0);
    FUN_7fff5f47d450(&DAT_7fff6242b278);
    FUN_7fff5f47d450(&DAT_7fff6242ba48);
    FUN_7fff5f47d450(&DAT_7fff6243dd98);
    FUN_7fff5f47d450(0x7fff62470e40);
    FUN_7fff5f47d450(0x7fff6246c428);
    FUN_7fff5f47d450(0x7fff6246c4f8);
    FUN_7fff5f47d450(0x7fff62470f08);
    FUN_7fff5f47d450(&DAT_7fff6245c360);
    FUN_7fff5f47d450(&DAT_7fff6246a1a8);
    DAT_7fff625e4c59 = '\x01';
  }
  lStackX_18 = 0;
  uStack_80 = 0;
  uStack_78 = 0;
  uStack_70 = 0;
  uStack_68 = 0;
  uStack_60 = 0;
  lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
  if (lVar9 != 0) {
    plVar2 = *(longlong **)(lVar9 + 0x28);
    uVar10 = 0;
    if (plVar2 != (longlong *)0x0) {
      uVar10 = 0;
      if ((*(byte *)(_DAT_7fff6242ba48 + 0x130) <= *(byte *)(*plVar2 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar2 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff6242ba48 + 0x130) * 8)
          == _DAT_7fff6242ba48)) {
        uVar10 = FUN_7fff600df780(plVar2,0);
        uVar18 = 0;
        FUN_7fff600e0ce0(plVar2,self + 0x194,self + 0x198,self + 0x19c,0);
      }
    }
    uVar3 = *(undefined8 *)(self + 0x70);
    uVar4 = *(undefined8 *)(self + 0x80);
    uVar5 = *(undefined8 *)(self + 0x88);
    uVar1 = *(undefined4 *)(self + 400);
    uVar11 = func_0x7fff5f44ff00(_DAT_7fff6242b278);
    FUN_7fff5fe27910(uVar11,uVar3,uVar4,uVar5,CONCAT44(uVar18,uVar1),uVar10,0);
    *(undefined8 *)(self + 0x180) = uVar11;
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0x180) != 0) {
      *(undefined4 *)(*(longlong *)(self + 0x180) + 0x50) = *(undefined4 *)(self + 0x178);
      if (*(longlong *)(self + 0x180) != 0) {
        *(undefined8 *)(*(longlong *)(self + 0x180) + 0x38) = *(undefined8 *)(self + 0x78);
        thunk_FUN_7fff5f491fd0();
        cVar7 = FUN_7fff60683c50(self,0x5a,&lStackX_18,_DAT_7fff623f8de8);
        if (cVar7 != '\0') {
          if (lStackX_18 == 0) goto LAB_7fff5fe25ea2;
          *(undefined **)(lStackX_18 + 0x18) = self;
          thunk_FUN_7fff5f491fd0();
          if (lStackX_18 == 0) goto LAB_7fff5fe25ea2;
          uVar12 = FUN_7fff5fe85290(lStackX_18,0);
          uStackX_20 = uVar12;
          lVar9 = FUN_7fff60c66630(_DAT_7fff6246a1a8);
          if (lVar9 == 0) goto LAB_7fff5fe25ea2;
          lVar9 = FUN_7fff5fe44150(lVar9,uVar12 & 0xffffffff,0);
          uVar17 = 0;
          if ((lVar9 != 0) && (*(longlong *)(lVar9 + 0x18) != 0)) {
            iVar8 = uStackX_20._4_4_;
            lVar16 = _DAT_7fff6242b1b0;
            for (; (int)uVar17 < (int)*(uint *)(lVar9 + 0x18); uVar17 = uVar17 + 1) {
              if (*(uint *)(lVar9 + 0x18) <= uVar17) {
                FUN_7fff5f47d650();
                goto LAB_7fff5fe25e96;
              }
              plVar2 = *(longlong **)(lVar9 + 0x20 + (longlong)(int)uVar17 * 8);
              if (plVar2 == (longlong *)0x0) goto LAB_7fff5fe25ea2;
              if (*(char *)((longlong)plVar2 + 0x151) == '\0') {
                lVar13 = plVar2[0xe];
              }
              else {
                if (plVar2[0x1f] == 0) goto LAB_7fff5fe25ea2;
                lVar13 = FUN_7fff5fe22f70(plVar2[0x1f],0);
                lVar16 = _DAT_7fff6242b1b0;
              }
              if (lVar13 == 0) goto LAB_7fff5fe25ea2;
              if (*(int *)(lVar13 + 0x10) != iVar8) {
                lVar13 = *plVar2;
                if ((*(byte *)(lVar16 + 0x130) <= *(byte *)(lVar13 + 0x130)) &&
                   (*(longlong *)
                     (*(longlong *)(lVar13 + 200) + -8 + (ulonglong)*(byte *)(lVar16 + 0x130) * 8)
                    == lVar16)) {
                  if (lStackX_18 == 0) goto LAB_7fff5fe25ea2;
                  if ((*(byte *)(lVar13 + 0x130) < *(byte *)(lVar16 + 0x130)) ||
                     (*(longlong *)
                       (*(longlong *)(lVar13 + 200) + -8 + (ulonglong)*(byte *)(lVar16 + 0x130) * 8)
                      != lVar16)) {
                    FUN_7fff5f47c810(plVar2);
                    pcVar6 = (code *)swi(3);
                    (*pcVar6)();
                    return;
                  }
                  *(longlong **)(lStackX_18 + 0x20) = plVar2;
                  thunk_FUN_7fff5f491fd0();
                  lVar16 = _DAT_7fff6242b1b0;
                }
              }
            }
          }
        }
        if (*(longlong *)(self + 0x168) != 0) {
          iVar8 = func_0x7fff607e24e0(*(longlong *)(self + 0x168),_DAT_7fff6245a1a8);
          if (0 < iVar8) {
            if (*(longlong *)(self + 0x168) == 0) goto LAB_7fff5fe25ea2;
            FUN_7fff607d9c20(&uStack_58,*(longlong *)(self + 0x168),_DAT_7fff6245a0e0);
            uStack_80 = uStack_58;
            uStack_78 = uStack_50;
            uStack_70 = uStack_48;
            uStack_68 = uStack_40;
            uStack_60 = uStack_38;
            while (cVar7 = FUN_7fff60941a70(&uStack_80,_DAT_7fff624307a8), uVar10 = uStack_68,
                  cVar7 != '\0') {
              plVar2 = *(longlong **)(self + 0x180);
              uVar12 = uStack_70 & 0xff;
              if (plVar2 == (longlong *)0x0) {
LAB_7fff5fe25e96:
                FUN_7fff5f47d660();
                FUN_7fff5f40a410();
                pcVar6 = (code *)swi(3);
                (*pcVar6)();
                return;
              }
              lVar9 = *plVar2;
              uVar15 = 0;
              if (*(ushort *)(lVar9 + 0x12e) != 0) {
                do {
                  if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar15 * 0x10) ==
                      _DAT_7fff6243dd98) {
                    puVar14 = (undefined8 *)
                              (lVar9 + 0x138 +
                              (longlong)
                              (*(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar15 * 0x10)
                              + 1) * 0x10);
                    goto LAB_7fff5fe25e08;
                  }
                  uVar15 = uVar15 + 1;
                } while (uVar15 < *(ushort *)(lVar9 + 0x12e));
              }
              puVar14 = (undefined8 *)FUN_7fff5f3de400(plVar2,_DAT_7fff6243dd98,1);
LAB_7fff5fe25e08:
              (*(code *)*puVar14)(plVar2,uVar12,uVar10,puVar14[1]);
            }
            func_0x7fff5f4d3920(&uStack_80,_DAT_7fff624306e0);
          }
          return;
        }
      }
    }
  }
LAB_7fff5fe25ea2:
  FUN_7fff5f47d660();
  pcVar6 = (code *)swi(3);
  (*pcVar6)();
  return;
}

