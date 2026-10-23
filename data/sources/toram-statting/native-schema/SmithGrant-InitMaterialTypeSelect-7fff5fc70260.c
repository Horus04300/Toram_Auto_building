
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrant_InitMaterialTypeSelect(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  undefined *self_00;
  code *pcVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  uint uVar6;
  char cVar7;
  undefined2 uVar8;
  int iVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong *plVar13;
  undefined *requireMaterial;
  undefined1 uVar14;
  undefined4 uVar15;
  uint uVar16;
  uint uVar17;
  float fVar18;
  uint auStackX_8 [2];
  undefined8 uStack_e8;
  undefined8 uStack_d8;
  undefined4 uStack_d0;
  undefined8 uStack_c8;
  undefined4 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined1 auStack_a8 [112];
  
  if (DAT_7fff625e421d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62411d60);
    FUN_7fff5f47d450(&DAT_7fff6244ce08);
    FUN_7fff5f47d450(&DAT_7fff62404658);
    FUN_7fff5f47d450(&DAT_7fff6246bee0);
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    FUN_7fff5f47d450(&DAT_7fff6241f9e8);
    FUN_7fff5f47d450(&DAT_7fff62424ed0);
    FUN_7fff5f47d450(0x7fff62425128);
    FUN_7fff5f47d450(&DAT_7fff624013f0);
    FUN_7fff5f47d450(&DAT_7fff62443180);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(0x7fff62447400);
    FUN_7fff5f47d450(&DAT_7fff6245cb58);
    FUN_7fff5f47d450(&DAT_7fff62409dd8);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff623f6270);
    DAT_7fff625e421d = '\x01';
  }
  auStackX_8[0] = 0;
  if (*(longlong *)(self + 0x78) != 0) {
    func_0x7fff5fdcfc90(*(longlong *)(self + 0x78),0);
    lVar11 = *(longlong *)(self + 0x138);
    if (lVar11 != 0) {
      iVar9 = *(int *)(lVar11 + 0x18);
      *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
      *(undefined4 *)(lVar11 + 0x18) = 0;
      if (0 < iVar9) {
        FUN_7fff61022d30(*(undefined8 *)(lVar11 + 0x10),0,iVar9,0);
      }
      if (*(longlong *)(self + 0xe0) != 0) {
        FUN_7fff618a4510(*(longlong *)(self + 0xe0),0,0);
        uVar6 = _DAT_7fff61b52c00;
        fVar18 = _DAT_7fff61b52b4c;
        uVar16 = 0;
        do {
          lVar11 = *(longlong *)(self + 0x120);
          uVar14 = 1;
          if (lVar11 == 0) goto LAB_7fff5fc70b57;
          uVar17 = *(uint *)(lVar11 + 0x18);
          lVar11 = *(longlong *)(lVar11 + 0x10);
          if ((lVar11 == 0) || ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar17))
          goto LAB_7fff5fc70b57;
          if (*(uint *)(lVar11 + 0x18) <= uVar17) goto LAB_7fff5fc70b5d;
          lVar11 = *(longlong *)(lVar11 + 0x20 + (longlong)(int)uVar17 * 8);
          if (lVar11 == 0) goto LAB_7fff5fc70b57;
          if (*(char *)(lVar11 + 0x2c) != '\0') {
            if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
              func_0x7fff5f47d6f0(_DAT_7fff62420f50);
            }
            lVar11 = *(longlong *)(self + 0x120);
            if (lVar11 == 0) goto LAB_7fff5fc70b57;
            uVar17 = *(uint *)(lVar11 + 0x18);
            lVar11 = *(longlong *)(lVar11 + 0x10);
            if ((lVar11 == 0) || ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar17))
            goto LAB_7fff5fc70b57;
            if (*(uint *)(lVar11 + 0x18) <= uVar17) goto LAB_7fff5fc70b5d;
            lVar11 = *(longlong *)(lVar11 + 0x20 + (longlong)(int)uVar17 * 8);
            if (lVar11 == 0) goto LAB_7fff5fc70b57;
            if ((*(char *)(lVar11 + 0x2c) != '\0') ||
               (uVar15 = 0, *(int *)(lVar11 + 0x30) + *(int *)(lVar11 + 0x28) != 0)) {
              uVar15 = *(undefined4 *)(lVar11 + 0x20);
            }
            if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc70b57;
            FUN_7fff6088c670(auStack_a8,**(longlong **)(_DAT_7fff62420f50 + 0xb8),uVar15,
                             _DAT_7fff6244ce08);
            uVar14 = 1;
            if (SUB84(auStack_a8._8_8_,4) != uVar16 + 1) {
              uVar14 = 0;
            }
          }
          if (uVar16 == 10) {
            if (*(longlong *)(self + 0x140) == 0) goto LAB_7fff5fc70b57;
            lVar10 = FUN_7fff5ff8a8a0(*(longlong *)(self + 0x140),0);
            lVar11 = *(longlong *)(self + 0x128);
            if (lVar11 == 0) goto LAB_7fff5fc70b57;
            if (*(int *)(lVar11 + 0x18) == 0) goto LAB_7fff5fc70b5d;
            if (*(longlong *)(self + 0x70) == 0) goto LAB_7fff5fc70b57;
            lVar11 = FUN_7fff60a94f50(*(longlong *)(self + 0x70),*(undefined4 *)(lVar11 + 0x20),
                                      _DAT_7fff624013f0);
            if ((lVar11 == 0) || (lVar10 == 0)) goto LAB_7fff5fc70b57;
            lVar11 = FUN_7fff6007b880(lVar10,*(undefined4 *)(lVar11 + 0x18),0);
            if (lVar11 != 0) {
              lVar10 = func_0x7fff5f47c850(_DAT_7fff6241f9e8,10);
              uVar8 = FUN_7fff5fd06df0(lVar11,0);
              if (lVar10 == 0) goto LAB_7fff5fc70b57;
              if (*(int *)(lVar10 + 0x18) == 0) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x20) = uVar8;
              uVar8 = FUN_7fff5fd06e20(lVar11,0);
              if (*(uint *)(lVar10 + 0x18) < 2) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x22) = uVar8;
              uVar8 = FUN_7fff5fd06e50(lVar11,0);
              if (*(uint *)(lVar10 + 0x18) < 3) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x24) = uVar8;
              uVar8 = FUN_7fff5fd06e80(lVar11,0);
              if (*(uint *)(lVar10 + 0x18) < 4) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x26) = uVar8;
              uVar8 = FUN_7fff5fd06eb0(lVar11,0);
              if (*(uint *)(lVar10 + 0x18) < 5) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x28) = uVar8;
              uVar8 = FUN_7fff5fd06ee0(lVar11,0);
              if (*(uint *)(lVar10 + 0x18) < 6) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x2a) = uVar8;
              uVar8 = FUN_7fff5fd06f10(lVar11,0);
              if (*(uint *)(lVar10 + 0x18) < 7) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x2c) = uVar8;
              uVar8 = FUN_7fff5fd06f40(lVar11,0);
              if (*(uint *)(lVar10 + 0x18) < 8) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x2e) = uVar8;
              uVar8 = FUN_7fff5fd06f70(lVar11,0);
              if (*(uint *)(lVar10 + 0x18) < 9) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x30) = uVar8;
              uVar8 = FUN_7fff5fd06dc0(lVar11,0);
              if (*(uint *)(lVar10 + 0x18) < 10) goto LAB_7fff5fc70b5d;
              *(undefined2 *)(lVar10 + 0x32) = uVar8;
              cVar7 = FUN_7fff606894c0(lVar10,0x41,_DAT_7fff62404658);
              if (cVar7 != '\0') {
                uVar14 = 0;
              }
              cVar7 = FUN_7fff5fc6d540(*(undefined4 *)(lVar11 + 0x34),0);
              if (cVar7 == '\0') {
                uVar14 = 0;
              }
            }
            lVar11 = *(longlong *)(self + 0x120);
            if (lVar11 == 0) goto LAB_7fff5fc70b57;
            lVar10 = *(longlong *)(lVar11 + 0x10);
            uVar17 = *(uint *)(lVar11 + 0x18);
            if ((lVar10 == 0) || ((int)*(uint *)(lVar10 + 0x18) <= (int)uVar17))
            goto LAB_7fff5fc70b57;
            if (*(uint *)(lVar10 + 0x18) <= uVar17) {
LAB_7fff5fc70b5d:
              FUN_7fff5f47d650();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            lVar10 = *(longlong *)(lVar10 + 0x20 + (longlong)(int)uVar17 * 8);
            if (lVar10 == 0) goto LAB_7fff5fc70b57;
            if (((*(char *)(lVar10 + 0x2c) == '\0') &&
                (*(int *)(lVar10 + 0x30) + *(int *)(lVar10 + 0x28) == 0)) ||
               (*(int *)(lVar10 + 0x20) != 0x41)) {
              auStackX_8[0] = 0;
              while( true ) {
                uVar17 = *(uint *)(*(longlong *)(lVar11 + 0x10) + 0x18);
                if ((int)uVar17 <= (int)auStackX_8[0]) break;
                if (uVar17 <= auStackX_8[0]) goto LAB_7fff5fc70b5d;
                lVar10 = *(longlong *)
                          (*(longlong *)(lVar11 + 0x10) + 0x20 + (longlong)(int)auStackX_8[0] * 8);
                if (lVar10 == 0) goto LAB_7fff5fc70b57;
                if (((*(char *)(lVar10 + 0x2c) != '\0') ||
                    (*(int *)(lVar10 + 0x30) + *(int *)(lVar10 + 0x28) != 0)) &&
                   (*(int *)(lVar10 + 0x20) == 0x41)) {
                  uVar14 = 0;
                  break;
                }
                auStackX_8[0] = auStackX_8[0] + 1;
              }
            }
          }
          lVar11 = *(longlong *)(self + 0x88);
          uVar17 = uVar16 + 1;
          lVar10 = *(longlong *)(self + 0x30);
          auStackX_8[0] = uVar17;
          uVar12 = FUN_7fff6100e780(auStackX_8,0);
          uVar12 = FUN_7fff60e71970(_DAT_7fff623f6270,uVar12,0);
          if (lVar10 == 0) goto LAB_7fff5fc70b57;
          plVar13 = (longlong *)FUN_7fff5f2550e0(_DAT_7fff62409dd8,lVar10,uVar12);
          uVar12 = FUN_7fff5f2542c0(_DAT_7fff62411d60);
          if (plVar13 == (longlong *)0x0) goto LAB_7fff5fc70b57;
          uVar12 = (**(code **)(*plVar13 + 0x1a8))(plVar13,uVar12,*(undefined8 *)(*plVar13 + 0x1b0))
          ;
          if (lVar11 == 0) goto LAB_7fff5fc70b57;
          FUN_7fff5ff0eed0(lVar11,uVar12,0);
          uVar12 = *(undefined8 *)(self + 0x80);
          if (DAT_7fff625e12c7 == '\0') {
            FUN_7fff5f47d450(&DAT_7fff62403718);
            DAT_7fff625e12c7 = '\x01';
          }
          uVar1 = **(undefined8 **)(_DAT_7fff62403718 + 0xb8);
          uVar15 = *(undefined4 *)(*(undefined8 **)(_DAT_7fff62403718 + 0xb8) + 1);
          if (DAT_7fff625e12cf == '\0') {
            FUN_7fff5f47d450(&DAT_7fff624318b0);
            DAT_7fff625e12cf = '\x01';
          }
          uVar3 = **(undefined8 **)(_DAT_7fff624318b0 + 0xb8);
          uVar4 = (*(undefined8 **)(_DAT_7fff624318b0 + 0xb8))[1];
          if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          uStack_d8 = uVar1;
          uStack_d0 = uVar15;
          uStack_b8 = uVar3;
          uStack_b0 = uVar4;
          lVar11 = FUN_7fff606c5700(uVar12,&uStack_d8,&uStack_b8);
          uStack_e8 = CONCAT44((float)((uint)*(float *)(self + 0xa0) ^ uVar6) * (float)(int)uVar16 -
                               *(float *)(self + 0xa0) * fVar18,0x42c80000);
          if (lVar11 == 0) goto LAB_7fff5fc70b57;
          lVar10 = FUN_7fff618a4a10(lVar11,0);
          if (lVar10 == 0) goto LAB_7fff5fc70b57;
          uStack_c8 = uStack_e8;
          uStack_c0 = 0;
          FUN_7fff618c8e40(lVar10,&uStack_c8,0);
          lVar10 = FUN_7fff606a6750(lVar11,_DAT_7fff6246bee0);
          if (lVar10 == 0) goto LAB_7fff5fc70b57;
          *(undefined **)(lVar10 + 0x38) = self;
          *(uint *)(lVar10 + 0x28) = uVar16;
          thunk_FUN_7fff5f491fd0();
          *(undefined4 *)(lVar10 + 0x2c) = 2;
          FUN_7fff5fc84350(lVar10,uVar14,0);
          if (*(longlong *)(self + 0x78) == 0) goto LAB_7fff5fc70b57;
          FUN_7fff5fdcf5e0(*(longlong *)(self + 0x78),lVar11,0);
          if (*(longlong *)(self + 0x138) == 0) goto LAB_7fff5fc70b57;
          FUN_7fff5f253100(*(longlong *)(self + 0x138),lVar11);
          uVar16 = uVar17;
        } while ((int)uVar17 < 0xb);
        lVar11 = *(longlong *)(self + 0x78);
        if (DAT_7fff625e12ce == '\0') {
          FUN_7fff5f47d450(&DAT_7fff62403718);
          DAT_7fff625e12ce = '\x01';
        }
        uVar12 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0xc);
        uVar15 = *(undefined4 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x14);
        if (DAT_7fff625e142c == '\0') {
          FUN_7fff5f47d450(&DAT_7fff62403718);
          DAT_7fff625e142c = '\x01';
        }
        uStack_c8 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x18);
        uStack_c0 = *(undefined4 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x20);
        fVar18 = (float)uStack_c8;
        uVar5 = (ulonglong)uStack_c8 >> 0x20;
        if (lVar11 != 0) {
          uStack_c8 = uVar12;
          uStack_c0 = uVar15;
          FUN_7fff5fdd0230(lVar11,&uStack_c8,
                           CONCAT44((float)uVar5 * *(float *)(self + 0xa0) * _DAT_7fff61b52ce4,
                                    fVar18 * *(float *)(self + 0xa0) * _DAT_7fff61b52ce4));
          if (*(longlong *)(self + 0x78) != 0) {
            FUN_7fff5fdcfec0(*(longlong *)(self + 0x78),_DAT_7fff623fda58,0);
            self_00 = *(undefined **)(self + 0xb8);
            if (*(longlong *)(self + 0x120) != 0) {
              requireMaterial = (undefined *)FUN_7fff5fc69070(*(longlong *)(self + 0x120),0);
              iVar9 = FUN_7fff5fc6ed00(self,0,0);
              if (self_00 != (undefined *)0x0) {
                SmithGrantInfoWindow_SetRequire(self_00,requireMaterial,iVar9,(undefined *)0x0);
                if (*(longlong *)(self + 0x108) != 0) {
                  FUN_7fff618a4510(*(longlong *)(self + 0x108),0,0);
                  lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245cb58);
                  if (lVar11 != 0) {
                    FUN_7fff5f5414f0(lVar11,4,0);
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
LAB_7fff5fc70b57:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

