
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrantInfoWindow_SetRequire
               (undefined *self,undefined *requireMaterial,int requirePotential,
               undefined *methodInfo)

{
  undefined4 uVar1;
  undefined4 uVar2;
  code *pcVar3;
  longlong **pplVar4;
  uint uVar5;
  char cVar6;
  int iVar7;
  longlong lVar8;
  undefined8 *puVar9;
  longlong *plVar10;
  undefined8 uVar11;
  longlong *plVar12;
  longlong lVar13;
  undefined8 uVar14;
  ushort uVar15;
  ushort uVar16;
  uint uVar17;
  undefined *puVar18;
  undefined4 in_register_00000084;
  int iStack_118;
  longlong *aplStack_110 [2];
  undefined *puStack_100;
  longlong lStack_f8;
  longlong **pplStack_f0;
  longlong **pplStack_e8;
  longlong *aplStack_d8 [2];
  undefined8 uStack_c8;
  undefined4 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined1 auStack_80 [72];
  
  plVar10 = (longlong *)CONCAT44(in_register_00000084,requirePotential);
  puStack_100 = requireMaterial;
  if (DAT_7fff625e4259 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b3d0);
    FUN_7fff5f47d450(&DAT_7fff6244fc80);
    FUN_7fff5f47d450(&DAT_7fff623fdea0);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    FUN_7fff5f47d450(&DAT_7fff62443180);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff62472258);
    FUN_7fff5f47d450(&DAT_7fff6243f290);
    FUN_7fff5f47d450(&DAT_7fff62422b28);
    FUN_7fff5f47d450(&DAT_7fff62402110);
    FUN_7fff5f47d450(&DAT_7fff623ffd48);
    FUN_7fff5f47d450(&DAT_7fff62426620);
    FUN_7fff5f47d450(&DAT_7fff62426170);
    FUN_7fff5f47d450(&DAT_7fff624760f0);
    DAT_7fff625e4259 = '\x01';
  }
  uVar17 = 0;
  aplStack_110[0] = (longlong *)0x0;
  aplStack_d8[0] = (longlong *)0x0;
  iStack_118 = 0;
  if ((*(longlong *)(self + 0x70) != 0) &&
     (lVar8 = FUN_7fff618a4a10(*(longlong *)(self + 0x70),0), lVar8 != 0)) {
    iVar7 = FUN_7fff618c81e0(lVar8,0);
    puVar18 = requireMaterial;
    if (iVar7 < 1) {
LAB_7fff5fc8606c:
      if (*(longlong *)(self + 0x78) != 0) {
        plVar10 = (longlong *)0x0;
        FUN_7fff618a4510(*(longlong *)(self + 0x78),1,0);
        uVar5 = _DAT_7fff61b52c00;
        if (requireMaterial != (undefined *)0x0) {
          for (; (int)uVar17 < *(int *)(puVar18 + 0x18); uVar17 = uVar17 + 1) {
            if (*(uint *)(requireMaterial + 0x18) <= uVar17) {
LAB_7fff5fc86544:
              FUN_7fff5f47d650();
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            if (*(int *)(requireMaterial + (longlong)(int)uVar17 * 4 + 0x20) != 0) {
              if (DAT_7fff625e12c7 == '\0') {
                FUN_7fff5f47d450(&DAT_7fff62403718);
                DAT_7fff625e12c7 = '\x01';
              }
              uVar11 = **(undefined8 **)(_DAT_7fff62403718 + 0xb8);
              uVar1 = *(undefined4 *)(*(undefined8 **)(_DAT_7fff62403718 + 0xb8) + 1);
              uStack_b8 = CONCAT44((float)(*(uint *)(self + 0x68) ^ uVar5) * (float)iStack_118 +
                                   (float)((ulonglong)uVar11 >> 0x20),(int)uVar11);
              if ((*(longlong *)(self + 0x78) == 0) ||
                 (lVar8 = FUN_7fff618a4a10(*(longlong *)(self + 0x78),0), lVar8 == 0))
              goto LAB_7fff5fc8651f;
              plVar10 = (longlong *)0x0;
              lVar8 = FUN_7fff618c6ee0(lVar8,_DAT_7fff624760f0,0);
              if ((lVar8 == 0) || (lVar8 = FUN_7fff60678610(lVar8,_DAT_7fff6244b3d0), lVar8 == 0))
              goto LAB_7fff5fc8651f;
              FUN_7fff5fc309f0(lVar8,1,0);
              uVar11 = FUN_7fff5fc6c580(uVar17,0);
              FUN_7fff5fc30f60(lVar8,uVar11,0);
              uVar11 = FUN_7fff5fc6bf10(uVar17,*(undefined8 *)(self + 0xe8),0);
              plVar10 = (longlong *)0x0;
              FUN_7fff5f6d4090(lVar8,uVar11,0);
              if ((*(longlong *)(self + 0x78) == 0) ||
                 (lVar8 = FUN_7fff618a4a10(*(longlong *)(self + 0x78),0), lVar8 == 0))
              goto LAB_7fff5fc8651f;
              plVar10 = (longlong *)0x0;
              lVar8 = FUN_7fff618c6ee0(lVar8,_DAT_7fff62402110,0);
              if (lVar8 == 0) goto LAB_7fff5fc8651f;
              lVar8 = FUN_7fff60678610(lVar8,_DAT_7fff6244fc80);
              if ((*(longlong *)(self + 0xe0) == 0) ||
                 (lVar13 = FUN_7fff5ff8a970(*(longlong *)(self + 0xe0),0), lVar13 == 0))
              goto LAB_7fff5fc8651f;
              iVar7 = FUN_7fff5ff1ac40(lVar13,uVar17,1);
              uVar11 = FUN_7fff5fc6ce20((longlong)iVar7,_DAT_7fff6243f290,0);
              if (*(uint *)(requireMaterial + 0x18) <= uVar17) goto LAB_7fff5fc86544;
              plVar10 = (longlong *)
                        FUN_7fff5fc6cea0(6,*(undefined4 *)
                                            (requireMaterial + (longlong)(int)uVar17 * 4 + 0x20),
                                         _DAT_7fff6243f290);
              uVar11 = FUN_7fff60e71650(uVar11,_DAT_7fff623ffd48,plVar10,0);
              if (lVar8 == 0) goto LAB_7fff5fc8651f;
              FUN_7fff5ff0eed0(lVar8,uVar11,0);
              uVar11 = *(undefined8 *)(self + 0x78);
              if (DAT_7fff625e12c7 == '\0') {
                FUN_7fff5f47d450(&DAT_7fff62403718);
                DAT_7fff625e12c7 = '\x01';
              }
              uVar14 = **(undefined8 **)(_DAT_7fff62403718 + 0xb8);
              uVar2 = *(undefined4 *)(*(undefined8 **)(_DAT_7fff62403718 + 0xb8) + 1);
              if (DAT_7fff625e12cf == '\0') {
                FUN_7fff5f47d450(&DAT_7fff624318b0);
                DAT_7fff625e12cf = '\x01';
              }
              lVar8 = **(longlong **)(_DAT_7fff624318b0 + 0xb8);
              pplVar4 = (longlong **)(*(longlong **)(_DAT_7fff624318b0 + 0xb8))[1];
              if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
                func_0x7fff5f47d6f0();
              }
              plVar10 = &lStack_f8;
              lStack_f8 = lVar8;
              pplStack_f0 = pplVar4;
              uStack_c8 = uVar14;
              uStack_c0 = uVar2;
              lVar8 = FUN_7fff606c5700(uVar11,&uStack_c8);
              if (lVar8 == 0) goto LAB_7fff5fc8651f;
              lVar13 = FUN_7fff618a4a10(lVar8,0);
              if ((*(longlong *)(self + 0x70) == 0) ||
                 (uVar11 = FUN_7fff618a4a10(*(longlong *)(self + 0x70),0), lVar13 == 0))
              goto LAB_7fff5fc8651f;
              plVar10 = (longlong *)0x0;
              FUN_7fff618c8fd0(lVar13,uVar11);
              lVar13 = FUN_7fff618a4a10(lVar8,0);
              if (lVar13 == 0) goto LAB_7fff5fc8651f;
              uStack_a8 = uStack_b8;
              plVar10 = (longlong *)0x0;
              uStack_a0 = uVar1;
              FUN_7fff618c8e40(lVar13,&uStack_a8);
              lVar8 = FUN_7fff618a4a10(lVar8,0);
              if ((*(longlong *)(self + 0x78) == 0) ||
                 (lVar13 = FUN_7fff618a4a10(*(longlong *)(self + 0x78),0), lVar13 == 0))
              goto LAB_7fff5fc8651f;
              plVar10 = (longlong *)0x0;
              puVar9 = (undefined8 *)FUN_7fff618c86a0(auStack_80,lVar13);
              if (lVar8 == 0) goto LAB_7fff5fc8651f;
              uStack_98 = *puVar9;
              uStack_90 = *(undefined4 *)(puVar9 + 1);
              plVar10 = (longlong *)0x0;
              FUN_7fff618c8f80(lVar8);
              iStack_118 = iStack_118 + 1;
            }
            puVar18 = puStack_100;
          }
          if (*(longlong *)(self + 0x78) != 0) {
            FUN_7fff618a4510(*(longlong *)(self + 0x78),0,0);
            *(int *)(self + 0xd0) = *(int *)(self + 200) - requirePotential;
            lVar8 = *(longlong *)(self + 0x60);
            uVar11 = FUN_7fff5fc6ce20((longlong)(*(int *)(self + 200) - requirePotential),
                                      _DAT_7fff6243f290,0);
            uVar14 = FUN_7fff5fc6ce20((longlong)*(int *)(self + 200),_DAT_7fff6243f290,0);
            plVar10 = _DAT_7fff62426620;
            uVar11 = FUN_7fff60e71050(_DAT_7fff62426170,uVar11,_DAT_7fff62426620,uVar14,0);
            if (lVar8 != 0) {
              FUN_7fff5ff0eed0(lVar8,uVar11,0);
              SmithGrantInfoWindow_Start(_DAT_7fff62422b28,(undefined *)0x0);
              return;
            }
          }
        }
      }
    }
    else if (*(longlong *)(self + 0x70) != 0) {
      FUN_7fff606a6990(*(longlong *)(self + 0x70),_DAT_7fff623fdea0);
      if ((*(longlong *)(self + 0x70) != 0) &&
         (lVar8 = FUN_7fff618a4a10(*(longlong *)(self + 0x70),0), lVar8 != 0)) {
        aplStack_110[0] = (longlong *)FUN_7fff618c6fc0(lVar8,0);
        lStack_f8 = 0;
        pplStack_f0 = aplStack_110;
        pplStack_e8 = aplStack_d8;
        while (plVar12 = aplStack_110[0], aplStack_110[0] != (longlong *)0x0) {
          lVar8 = *aplStack_110[0];
          uVar16 = 0;
          if (*(ushort *)(lVar8 + 0x12e) != 0) {
            plVar10 = *(longlong **)(lVar8 + 0xb0);
            uVar15 = uVar16;
            do {
              if (plVar10[(ulonglong)uVar15 * 2] == _DAT_7fff62442498) {
                puVar9 = (undefined8 *)
                         (lVar8 + 0x138 + (longlong)(int)plVar10[(ulonglong)uVar15 * 2 + 1] * 0x10);
                goto LAB_7fff5fc85ea9;
              }
              uVar15 = uVar15 + 1;
            } while (uVar15 < *(ushort *)(lVar8 + 0x12e));
          }
          plVar10 = (longlong *)0x0;
          puVar9 = (undefined8 *)FUN_7fff5f3de400(aplStack_110[0],_DAT_7fff62442498,0);
LAB_7fff5fc85ea9:
          cVar6 = (*(code *)*puVar9)(plVar12,puVar9[1]);
          plVar12 = aplStack_110[0];
          if (cVar6 == '\0') {
            plVar12 = (longlong *)func_0x7fff5f47c7e0(aplStack_110[0],_DAT_7fff624413c0);
            puVar18 = puStack_100;
            aplStack_d8[0] = plVar12;
            if (plVar12 != (longlong *)0x0) {
              FUN_7fff5f253010(0,_DAT_7fff624413c0,plVar12);
              puVar18 = puStack_100;
              plVar10 = plVar12;
            }
            goto LAB_7fff5fc8606c;
          }
          if (aplStack_110[0] == (longlong *)0x0) goto LAB_7fff5fc86533;
          lVar8 = *aplStack_110[0];
          if (*(ushort *)(lVar8 + 0x12e) != 0) {
            do {
              if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + (ulonglong)uVar16 * 0x10) ==
                  _DAT_7fff62442498) {
                puVar9 = (undefined8 *)
                         (lVar8 + 0x138 +
                         (longlong)
                         (*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + (ulonglong)uVar16 * 0x10) + 1)
                         * 0x10);
                goto LAB_7fff5fc85f18;
              }
              uVar16 = uVar16 + 1;
            } while (uVar16 < *(ushort *)(lVar8 + 0x12e));
          }
          puVar9 = (undefined8 *)FUN_7fff5f3de400(aplStack_110[0],_DAT_7fff62442498,1);
LAB_7fff5fc85f18:
          plVar10 = (longlong *)(*(code *)*puVar9)(plVar12,puVar9[1]);
          if (plVar10 == (longlong *)0x0) goto LAB_7fff5fc86525;
          if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7fff62472258 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar10 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7fff62472258 + 0x130) * 8) != _DAT_7fff62472258))
          goto LAB_7fff5fc8652b;
          uVar11 = FUN_7fff618a1ae0(plVar10,0);
          if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          FUN_7fff618a99c0(uVar11,0);
        }
        goto LAB_7fff5fc86538;
      }
    }
  }
LAB_7fff5fc8651f:
  FUN_7fff5f47d660();
LAB_7fff5fc86525:
  FUN_7fff5f47d660();
LAB_7fff5fc8652b:
  FUN_7fff5f47c810(plVar10);
LAB_7fff5fc86533:
  FUN_7fff5f47d660();
LAB_7fff5fc86538:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

