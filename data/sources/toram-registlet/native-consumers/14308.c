
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
PlayerAttackBase_TemplateAssignment
          (undefined *thisObject,undefined *template,undefined *playerAction,undefined *mobAction,
          undefined *attackType,undefined *TreeType,int addRegist,undefined *methodInfo)

{
  code *pcVar1;
  float fVar2;
  ulonglong uVar3;
  undefined1 uVar4;
  char cVar5;
  byte bVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  longlong *plVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong lVar13;
  undefined *puVar14;
  ushort uVar15;
  ushort uVar16;
  undefined4 uVar17;
  ulonglong uVar18;
  ulonglong uStackX_8;
  ulonglong uStackX_10;
  undefined8 in_stack_ffffffffffffff48;
  ulonglong *puVar19;
  int iStack_98;
  int iStack_94;
  int aiStack_90 [2];
  longlong lStack_88;
  longlong *plStack_80;
  undefined8 uStack_78;
  longlong alStack_70 [7];
  
  uVar8 = (undefined4)((ulonglong)in_stack_ffffffffffffff48 >> 0x20);
  if (DAT_7ffe9caddecf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f1e88);
    FUN_7ffe9996d590(&DAT_7ffe9c923808);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c953410);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c91d5d0);
    FUN_7ffe9996d590(&DAT_7ffe9c9680d8);
    DAT_7ffe9caddecf = '\x01';
  }
  uVar18 = 0;
  uVar17 = 0;
  iStack_94 = 0;
  aiStack_90[0] = 0;
  iStack_98 = 0;
  lStack_88 = 0;
  plStack_80 = (longlong *)0x0;
  alStack_70[0] = 0;
  uVar7 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  if ((((template == (undefined *)0x0) ||
       (*(undefined4 *)(template + 0x20) = uVar7, playerAction == (undefined *)0x0)) ||
      (plVar10 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
      plVar10 == (longlong *)0x0)) ||
     (lVar11 = (**(code **)(*plVar10 + 0x1a8))(plVar10,*(undefined8 *)(*plVar10 + 0x1b0)),
     mobAction == (undefined *)0x0)) goto LAB_7ffe9a4b1bcf;
  uStack_78 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
  if (*(longlong *)(thisObject + 0xb8) != 0) {
    uVar17 = *(undefined4 *)(*(longlong *)(thisObject + 0xb8) + 0x24);
  }
  uVar4 = FUN_7ffe9a658020(template,6);
  uVar12 = CONCAT44(uVar8,uVar17);
  (**(code **)(*(longlong *)thisObject + 0x698))
            (thisObject,playerAction,mobAction,(ulonglong)attackType & 0xffffffff,uVar12,uVar4,
             *(undefined8 *)(*(longlong *)thisObject + 0x6a0));
  uVar8 = (undefined4)((ulonglong)uVar12 >> 0x20);
  FUN_7ffe9a657a50(template,7);
  uVar12 = (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  fVar2 = _DAT_7ffe9c049cfc;
  FUN_7ffe9a4ab1a0(thisObject,(ulonglong)attackType & 0xffffffff,uVar12,uStack_78,
                   CONCAT44(uVar8,(float)addRegist / _DAT_7ffe9c049cfc),0);
  FUN_7ffe9a657a50(template,10);
  plVar10 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar10 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a4b1bcf;
  FUN_7ffe9a7c8da0(lVar13,0x54);
  FUN_7ffe9a657a50(template,9);
  FUN_7ffe9a7a6a60(playerAction,mobAction,0);
  FUN_7ffe9a657a50(template,9);
  lVar13 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
  if (lVar13 == 0) goto LAB_7ffe9a4b1bcf;
  uVar8 = FUN_7ffe99742ec0(9,_DAT_7ffe9c93ed20,lVar13);
  uStackX_10 = uStackX_10 & 0xffffffffffffff00;
  uStackX_8 = uStackX_8 & 0xffffffffffffff00;
  uVar12 = (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  puVar19 = &uStackX_10;
  FUN_7ffe9a4a9110(thisObject,uVar12,(ulonglong)attackType & 0xffffffff,uVar8,puVar19,0);
  uVar17 = (undefined4)((ulonglong)puVar19 >> 0x20);
  if (*(int *)(thisObject + 0x34) == 0) {
    cVar5 = FUN_7ffe9a7ac580(playerAction,&iStack_98,0);
    if (((cVar5 != '\0') && (cVar5 = FUN_7ffe9a7abb70(thisObject,0), cVar5 != '\0')) &&
       (iStack_98 != 0)) {
      uVar12 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      iVar9 = iStack_98;
      goto LAB_7ffe9a4b0e37;
    }
  }
  else {
    uVar12 = (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    iVar9 = *(int *)(thisObject + 0x34);
LAB_7ffe9a4b0e37:
    FUN_7ffe9a4a93f0(thisObject,uVar12,(ulonglong)attackType & 0xffffffff,iVar9,
                     CONCAT44(uVar17,uVar8),&uStackX_8,0);
  }
  FUN_7ffe9a658f90(template,0xe,(char)uStackX_8 != '\0' || (char)uStackX_10 != '\0');
  FUN_7ffe9a657c40(template,0xf);
  uVar12 = (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  FUN_7ffe9a4aad20(uVar12,mobAction,0);
  FUN_7ffe9a657c40(template,0x10);
  if (lVar11 == 0) goto LAB_7ffe9a4b1bcf;
  iVar9 = FUN_7ffe99742ec0(0x1c,_DAT_7ffe9c940d40,lVar11);
  if ((int)attackType == 2) {
    plVar10 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar10 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a4b1bcf;
    cVar5 = FUN_7ffe9abc2210(lVar13,0x369,&lStack_88,_DAT_7ffe9c9680d8);
    if (cVar5 != '\0') {
      uVar12 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      cVar5 = FUN_7ffe9a781d00(thisObject,uVar12,0);
      if (cVar5 != '\0') {
        lVar13 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
        if (lVar13 == 0) goto LAB_7ffe9a4b1bcf;
        cVar5 = FUN_7ffe9a4d9f40(lVar13,0x10);
        if (cVar5 != '\0') {
          if (lStack_88 == 0) goto LAB_7ffe9a4b1bcf;
          iVar9 = FUN_7ffe9a781dc0(lStack_88,0);
          if (iVar9 == 1) {
            if (lStack_88 == 0) goto LAB_7ffe9a4b1bcf;
            func_0x7ffe99add780(lStack_88,0);
          }
        }
        iVar9 = FUN_7ffe99742ec0(0x1d,_DAT_7ffe9c940d40,lVar11);
        if (lStack_88 == 0) goto LAB_7ffe9a4b1bcf;
        func_0x7ffe99add750(lStack_88,0);
        goto LAB_7ffe9a4b1015;
      }
    }
    iVar9 = FUN_7ffe99742ec0(0x1d,_DAT_7ffe9c940d40,lVar11);
  }
LAB_7ffe9a4b1015:
  FUN_7ffe9a657c40(template,0xd,(float)iVar9 / fVar2);
  uVar8 = FUN_7ffe99742ec0(0xf,_DAT_7ffe9c940d40,lVar11);
  uVar4 = FUN_7ffe9a658020(template,4);
  uVar12 = (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  (**(code **)(*(longlong *)thisObject + 0x6a8))
            (thisObject,(ulonglong)attackType & 0xffffffff,uVar8,uVar4,uVar12,
             *(undefined8 *)(*(longlong *)thisObject + 0x6b0));
  FUN_7ffe9a657c40(template,0x15);
  uVar8 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  FUN_7ffe9a2d1cb0((ulonglong)attackType & 0xffffffff,uVar8,uStack_78);
  FUN_7ffe9a657c40(template,0x17);
  iVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  if ((((iVar9 == 0) ||
       (iVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)), iVar9 == 8))
      || (iVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
         iVar9 == 0xc)) ||
     (((iVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)), iVar9 == 0xb
       || (iVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
          iVar9 == 0x19)) ||
      ((iVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)), iVar9 == 0x1a
       || ((iVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
           iVar9 == 0x1b ||
           (iVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
           iVar9 == 0x1c)))))))) {
    uVar12 = (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    FUN_7ffe9a4a7d60(thisObject,uVar12,0);
    FUN_7ffe9a657c40(template,0x19);
  }
  else {
    iVar9 = (**(code **)(*(longlong *)thisObject + 0x588))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x590));
    if ((iVar9 == 3) ||
       (iVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
       iVar9 == 0x407)) {
      plVar10 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar10 == (longlong *)0x0) ||
         (lVar11 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
         lVar11 == 0)) goto LAB_7ffe9a4b1bcf;
      cVar5 = FUN_7ffe9a7cbb30(lVar11,0x76,&plStack_80);
      if (cVar5 != '\0') {
        plVar10 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (((plVar10 == (longlong *)0x0) ||
            (lVar11 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200)),
            lVar11 == 0)) || (*(longlong *)(lVar11 + 0x18) == 0)) goto LAB_7ffe9a4b1bcf;
        iVar9 = func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x18),0);
        plVar10 = plStack_80;
        if (iVar9 == 0xe) {
          uVar8 = (**(code **)(*(longlong *)thisObject + 0x188))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
          if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a4b1bcf;
          if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c953410 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar10 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c953410 + 0x130) * 8) != _DAT_7ffe9c953410)) {
            FUN_7ffe9996c950(plVar10,_DAT_7ffe9c953410);
            pcVar1 = (code *)swi(3);
            puVar14 = (undefined *)(*pcVar1)();
            return puVar14;
          }
          cVar5 = FUN_7ffe9a7943e0(plVar10,uVar8,thisObject[0x10]);
          if (cVar5 == '\0') {
            if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a4b1bcf;
            if (((*(byte *)(*plStack_80 + 0x130) < *(byte *)(_DAT_7ffe9c953410 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStack_80 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c953410 + 0x130) * 8) != _DAT_7ffe9c953410)) ||
               (plStack_80 == (longlong *)0x0)) {
              FUN_7ffe9996c950(plStack_80);
              pcVar1 = (code *)swi(3);
              puVar14 = (undefined *)(*pcVar1)();
              return puVar14;
            }
            func_0x7ffe9a794e10(plStack_80,0);
          }
        }
      }
    }
    puVar14 = (undefined *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    PlayerAttackBase_CalcLastDamageRate
              (thisObject,puVar14,(undefined *)((ulonglong)attackType & 0xffffffff),(undefined *)0x0
              );
    FUN_7ffe9a657c40(template,0x19);
    if (plStack_80 != (longlong *)0x0) {
      if (((*(byte *)(*plStack_80 + 0x130) < *(byte *)(_DAT_7ffe9c953410 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_80 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c953410 + 0x130) * 8) != _DAT_7ffe9c953410)) ||
         (plStack_80 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_80);
        pcVar1 = (code *)swi(3);
        puVar14 = (undefined *)(*pcVar1)();
        return puVar14;
      }
      func_0x7ffe9a794a00(plStack_80,0);
    }
  }
  lVar11 = *(longlong *)mobAction;
  if ((*(byte *)(_DAT_7ffe9c923808 + 0x130) <= *(byte *)(lVar11 + 0x130)) &&
     (*(longlong *)
       (*(longlong *)(lVar11 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8) ==
      _DAT_7ffe9c923808)) {
    if ((*(byte *)(lVar11 + 0x130) < *(byte *)(_DAT_7ffe9c923808 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar11 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8) !=
        _DAT_7ffe9c923808)) {
      FUN_7ffe9996c950(mobAction);
      pcVar1 = (code *)swi(3);
      puVar14 = (undefined *)(*pcVar1)();
      return puVar14;
    }
    cVar5 = FUN_7ffe9ab798a0(mobAction,0x5a,alStack_70,_DAT_7ffe9c8f1e88);
    if (cVar5 != '\0') {
      if (alStack_70[0] == 0) goto LAB_7ffe9a4b1bcf;
      FUN_7ffe9a37a550(alStack_70[0],0);
      FUN_7ffe9a657c40(template,0x19);
    }
  }
  if (DAT_7ffe9caddec0 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c928220);
    DAT_7ffe9caddec0 = '\x01';
  }
  lVar13 = _DAT_7ffe9c928220;
  uVar16 = 0;
  lVar11 = *(longlong *)mobAction;
  uStackX_8 = 0;
  if (*(ushort *)(lVar11 + 0x12e) != 0) {
    uVar15 = uVar16;
    do {
      if (*(longlong *)(*(longlong *)(lVar11 + 0xb0) + (ulonglong)uVar15 * 0x10) ==
          *(longlong *)(_DAT_7ffe9c928220 + 0x20)) {
        lVar11 = (longlong)
                 (int)(*(int *)(*(longlong *)(lVar11 + 0xb0) + 8 + (ulonglong)uVar15 * 0x10) +
                      (uint)*(ushort *)(_DAT_7ffe9c928220 + 0x50)) * 0x10 + 0x138 + lVar11;
        goto LAB_7ffe9a4b1553;
      }
      uVar15 = uVar15 + 1;
    } while (uVar15 < *(ushort *)(lVar11 + 0x12e));
  }
  lVar11 = FUN_7ffe998ce540(mobAction,*(longlong *)(_DAT_7ffe9c928220 + 0x20),
                            *(ushort *)(_DAT_7ffe9c928220 + 0x50));
LAB_7ffe9a4b1553:
  lVar11 = func_0x7ffe9996d210(*(undefined8 *)(lVar11 + 8),lVar13);
  cVar5 = (**(code **)(lVar11 + 8))(mobAction,0xf,&uStackX_8,lVar11);
  fVar2 = _DAT_7ffe9c049b18;
  if (cVar5 != '\0') {
    if (uStackX_8 == 0) {
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      puVar14 = (undefined *)(*pcVar1)();
      return puVar14;
    }
    FUN_7ffe9a379430(uStackX_8,playerAction,mobAction,0);
  }
  FUN_7ffe9a657c40(template,0x1a);
  plVar10 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  uVar8 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  uVar8 = func_0x7ffe9a2d1bd0((ulonglong)attackType & 0xffffffff,uVar8,0);
  uStackX_8 = CONCAT44(uStackX_8._4_4_,uVar8);
  uVar8 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  iVar9 = func_0x7ffe9a2d1c00((ulonglong)TreeType & 0xffffffff,uVar8,0);
  if ((float)uStackX_8 != 0.0) {
    if ((plVar10 == (longlong *)0x0) ||
       (lVar11 = (**(code **)(*plVar10 + 0x1d8))(plVar10,*(undefined8 *)(*plVar10 + 0x1e0)),
       lVar11 == 0)) goto LAB_7ffe9a4b1bcf;
    FUN_7ffe9a4eb220(lVar11,uStackX_8 & 0xffffffff,0);
  }
  if (iVar9 != 0) {
    if ((plVar10 == (longlong *)0x0) ||
       (lVar11 = (**(code **)(*plVar10 + 0x1d8))(plVar10,*(undefined8 *)(*plVar10 + 0x1e0)),
       lVar11 == 0)) goto LAB_7ffe9a4b1bcf;
    FUN_7ffe9a4eb220(lVar11,iVar9,0);
  }
  FUN_7ffe9a657c40(template,0x18);
  plVar10 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (DAT_7ffe9caddec7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    DAT_7ffe9caddec7 = '\x01';
  }
  lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
  if (lVar11 != 0) {
    iVar9 = FUN_7ffe9a872680(lVar11,0);
    if (iVar9 != 0) {
      lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
      if (lVar11 == 0) goto LAB_7ffe9a4b1bcf;
      iVar9 = FUN_7ffe9a872680(lVar11,0);
      if (iVar9 != 7) {
        if ((plVar10 == (longlong *)0x0) ||
           (lVar11 = (**(code **)(*plVar10 + 0x1d8))(plVar10,*(undefined8 *)(*plVar10 + 0x1e0)),
           lVar11 == 0)) goto LAB_7ffe9a4b1bcf;
        FUN_7ffe9a4eade0(lVar11,0xbf,0);
      }
    }
    FUN_7ffe9a657c40(template,0x1c);
    if (DAT_7ffe9cadded9 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
      FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
      DAT_7ffe9cadded9 = '\x01';
    }
    plVar10 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar10 != (longlong *)0x0) &&
       (puVar14 = (undefined *)
                  (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220)),
       puVar14 != (undefined *)0x0)) {
      bVar6 = GemCartBufferManager_ContainsBuffer(puVar14,0x45,(undefined *)0x0);
      if (bVar6 != 0) {
        FUN_7ffe99749320(0x17,_DAT_7ffe9c9724e0,mobAction,0x10);
        lVar11 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        if (lVar11 == 0) goto LAB_7ffe9a4b1bcf;
        FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar11);
        FUN_7ffe9a6590f0(template,0x23);
      }
      cVar5 = FUN_7ffe9a4ac310(thisObject,mobAction,&iStack_94,aiStack_90,0);
      if (cVar5 != '\0') {
        if (iStack_94 != -1) {
          FUN_7ffe9a657a50(template,0x24);
        }
        if (aiStack_90[0] != -1) {
          FUN_7ffe9a657a50(template,0x25);
        }
      }
      if (DAT_7ffe9caddedc == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c927e38);
        FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
        DAT_7ffe9caddedc = '\x01';
      }
      lVar13 = _DAT_7ffe9c927e38;
      lVar11 = *(longlong *)mobAction;
      uStackX_8 = 0;
      aiStack_90[1] = 0x3f800000;
      if (*(ushort *)(lVar11 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar11 + 0xb0) + (ulonglong)uVar16 * 0x10) ==
              *(longlong *)(_DAT_7ffe9c927e38 + 0x20)) {
            lVar11 = (longlong)
                     (int)(*(int *)(*(longlong *)(lVar11 + 0xb0) + 8 + (ulonglong)uVar16 * 0x10) +
                          (uint)*(ushort *)(_DAT_7ffe9c927e38 + 0x50)) * 0x10 + 0x138 + lVar11;
            goto LAB_7ffe9a4b1967;
          }
          uVar16 = uVar16 + 1;
        } while (uVar16 < *(ushort *)(lVar11 + 0x12e));
      }
      lVar11 = FUN_7ffe998ce540(mobAction,*(longlong *)(_DAT_7ffe9c927e38 + 0x20),
                                *(ushort *)(_DAT_7ffe9c927e38 + 0x50));
LAB_7ffe9a4b1967:
      lVar11 = func_0x7ffe9996d210(*(undefined8 *)(lVar11 + 8),lVar13);
      cVar5 = (**(code **)(lVar11 + 8))(mobAction,2,&uStackX_8,lVar11);
      uVar3 = uStackX_8;
      if (cVar5 != '\0') {
        uVar12 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
        if (uVar3 == 0) {
          FUN_7ffe9996d7a0();
          pcVar1 = (code *)swi(3);
          puVar14 = (undefined *)(*pcVar1)();
          return puVar14;
        }
        cVar5 = FUN_7ffe9a378730(uVar3,uVar12,aiStack_90 + 1,0);
        if (cVar5 != '\0') {
          FUN_7ffe9a657c40(template,0x1d);
        }
      }
      if ((int)TreeType == 0x1d) {
        if ((*(byte *)(*(longlong *)playerAction + 0x130) < *(byte *)(_DAT_7ffe9c91d5d0 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)playerAction + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c91d5d0 + 0x130) * 8) != _DAT_7ffe9c91d5d0))
        goto LAB_7ffe9a4b1bcf;
        FUN_7ffe9a3e4bf0(playerAction,0);
        FUN_7ffe9a657c40(template,0x19);
      }
      if (DAT_7ffe9caddecd == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c9286d0);
        DAT_7ffe9caddecd = '\x01';
      }
      uStackX_8 = uStackX_8 & 0xffffffff00000000;
      uStackX_10 = 0;
      plVar10 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (((plVar10 != (longlong *)0x0) &&
          (lVar11 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200)),
          lVar11 != 0)) && (*(longlong *)(lVar11 + 0x18) != 0)) {
        uVar8 = func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x18),0);
        lVar13 = _DAT_7ffe9c9286d0;
        lVar11 = *(longlong *)mobAction;
        if (*(ushort *)(lVar11 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar11 + 0xb0) + uVar18 * 0x10) ==
                *(longlong *)(_DAT_7ffe9c9286d0 + 0x20)) {
              lVar11 = (longlong)
                       (int)(*(int *)(*(longlong *)(lVar11 + 0xb0) + 8 + uVar18 * 0x10) +
                            (uint)*(ushort *)(_DAT_7ffe9c9286d0 + 0x50)) * 0x10 + 0x138 + lVar11;
              goto LAB_7ffe9a4b1af8;
            }
            uVar16 = (short)uVar18 + 1;
            uVar18 = (ulonglong)uVar16;
          } while (uVar16 < *(ushort *)(lVar11 + 0x12e));
        }
        lVar11 = FUN_7ffe998ce540(mobAction,*(longlong *)(_DAT_7ffe9c9286d0 + 0x20),
                                  *(ushort *)(_DAT_7ffe9c9286d0 + 0x50));
LAB_7ffe9a4b1af8:
        lVar11 = func_0x7ffe9996d210(*(undefined8 *)(lVar11 + 8),lVar13);
        cVar5 = (**(code **)(lVar11 + 8))(mobAction,0x29,&uStackX_10,lVar11);
        if (cVar5 != '\0') {
          if (uStackX_10 == 0) goto LAB_7ffe9a4b1c02;
          FUN_7ffe9a37bec0(uStackX_10,uVar8,&uStackX_8,0);
        }
        FUN_7ffe9a657c40(template,0x28,(float)uStackX_8 + fVar2);
        return template;
      }
LAB_7ffe9a4b1c02:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      puVar14 = (undefined *)(*pcVar1)();
      return puVar14;
    }
  }
LAB_7ffe9a4b1bcf:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar14 = (undefined *)(*pcVar1)();
  return puVar14;
}

