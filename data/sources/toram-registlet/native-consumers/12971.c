
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerActionManager_AddAbnormalState
               (undefined *thisObject,undefined *actor,undefined *type,float time,float resist,
               float addResist,byte localId,byte force,undefined *methodInfo)

{
  undefined1 uVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  undefined *puVar7;
  longlong *plVar8;
  longlong lVar9;
  longlong lVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined *puVar14;
  ulonglong uVar15;
  longlong *plStack_88;
  longlong lStack_80;
  longlong lStack_78;
  longlong alStack_70 [3];
  undefined8 uStack_58;
  undefined4 uStack_50;
  undefined1 auStack_48 [32];
  
  uVar15 = (ulonglong)type & 0xffffffff;
  if (DAT_7ffe9caddcaa == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f32b8);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c8f4048);
    FUN_7ffe9996d590(&DAT_7ffe9c9227e8);
    FUN_7ffe9996d590(&DAT_7ffe9c92e5b8);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c967748);
    FUN_7ffe9996d590(&DAT_7ffe9c96a188);
    FUN_7ffe9996d590(&DAT_7ffe9c8fb118);
    FUN_7ffe9996d590(0x7ffe9c8fb1e8);
    FUN_7ffe9996d590(0x7ffe9c8fb2b8);
    FUN_7ffe9996d590(&DAT_7ffe9c8fb388);
    FUN_7ffe9996d590(&DAT_7ffe9c8fb458);
    FUN_7ffe9996d590(&DAT_7ffe9c90fe58);
    DAT_7ffe9caddcaa = '\x01';
  }
  lVar10 = 0;
  plStack_88 = (longlong *)0x0;
  alStack_70[1] = 0;
  lStack_78 = 0;
  alStack_70[0] = 0;
  lStack_80 = 0;
  puVar7 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c90fe58);
  GemCartMasterData__ctor(puVar7,(undefined *)0x0);
  if (puVar7 == (undefined *)0x0) goto LAB_7ffe9a444703;
  *(undefined **)(puVar7 + 0x10) = thisObject;
  il2cpp_write_barrier_0();
  puVar7[0x18] = localId;
  iVar6 = (int)type;
  if (force == 0) {
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (((plVar8 == (longlong *)0x0) ||
        (lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)), lVar9 == 0
        )) || (*(longlong *)(lVar9 + 0x50) == 0)) goto LAB_7ffe9a444703;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x50),0xe7,&plStack_88,_DAT_7ffe9c934418);
    if (((cVar3 != '\0') && (3 < iVar6 - 1U)) && (iVar6 != 0x2b)) {
      plVar8 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if (((plVar8 == (longlong *)0x0) ||
          (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
          lVar10 == 0)) || (FUN_7ffe9a7ca6f0(lVar10,0xe7,0), plStack_88 == (longlong *)0x0))
      goto LAB_7ffe9a444703;
      if (((*(byte *)(*plStack_88 + 0x130) < *(byte *)(_DAT_7ffe9c92e5b8 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_88 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c92e5b8 + 0x130) * 8) != _DAT_7ffe9c92e5b8)) ||
         (plStack_88 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_88);
        pcVar2 = (code *)swi(3);
        bVar4 = (*pcVar2)();
        return bVar4;
      }
      cVar3 = func_0x7ffe9a79fb10(plStack_88,0);
      if (cVar3 != '\0') {
        if (plStack_88 == (longlong *)0x0) goto LAB_7ffe9a444703;
        uVar5 = (**(code **)(*plStack_88 + 0x1f8))
                          (plStack_88,0x32,*(undefined8 *)(*plStack_88 + 0x200));
        if (*(longlong *)(thisObject + 0x128) == 0) goto LAB_7ffe9a444703;
        FUN_7ffe9a6fbaa0(*(longlong *)(thisObject + 0x128),0xcc,uVar5,0);
      }
      lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
      if ((*(longlong *)(thisObject + 0x20) != 0) &&
         (puVar11 = (undefined8 *)FUN_7ffe9bdbf710(auStack_48,*(longlong *)(thisObject + 0x20),0),
         lVar10 != 0)) {
        uStack_58 = *puVar11;
        uStack_50 = *(undefined4 *)(puVar11 + 1);
        FUN_7ffe99ca30e0(lVar10,uVar15,&uStack_58,0);
        return 0;
      }
      goto LAB_7ffe9a444703;
    }
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)), lVar9 == 0)
       ) goto LAB_7ffe9a444703;
    cVar3 = FUN_7ffe9abc2210(lVar9,0x34d,alStack_70 + 1,_DAT_7ffe9c967748);
    if ((cVar3 != '\0') && ((3 < iVar6 - 1U && (iVar6 != 0x2b)))) {
      plVar8 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar8 != (longlong *)0x0) &&
         (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
         lVar10 != 0)) {
        FUN_7ffe9a7cafa0(lVar10,0x34d,0);
        return 0;
      }
      goto LAB_7ffe9a444703;
    }
  }
  else {
    cVar3 = FUN_7ffe99b1ccd0(thisObject,0);
    if ((cVar3 == '\0') && (iVar6 == 4)) {
      plVar8 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar8 == (longlong *)0x0) ||
         (lVar9 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)),
         lVar9 == 0)) goto LAB_7ffe9a444703;
      cVar3 = FUN_7ffe9a4d9f40(lVar9,uVar15,0);
      if (cVar3 != '\0') {
        return 0;
      }
    }
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar9 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)), lVar9 == 0)
       ) goto LAB_7ffe9a444703;
    FUN_7ffe9a4dbbb0(lVar9,uVar15,force,0);
  }
  uVar12 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
  FUN_7ffe9a2f3fb0(uVar12,puVar7,_DAT_7ffe9c8fb118,0);
  if (0x14 < iVar6) {
    if (iVar6 != 0x2b) {
      if (iVar6 == 0x2c) {
        lVar10 = (**(code **)(*(longlong *)thisObject + 0x2a8))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2b0));
        if (lVar10 != 0) {
          cVar3 = FUN_7ffe9a4d8d20(lVar10,uVar15,_DAT_7ffe9c049b40,resist,puVar7[0x18],force,uVar12,
                                   0);
          if (cVar3 == '\0') {
            return 0;
          }
          if (*(longlong *)(thisObject + 0x90) != 0) {
            FUN_7ffe9a47aa30();
            plVar8 = (longlong *)
                     (**(code **)(*(longlong *)thisObject + 0x298))
                               (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
            if ((plVar8 != (longlong *)0x0) &&
               (puVar7 = (undefined *)
                         (**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220)),
               puVar7 != (undefined *)0x0)) {
              plVar8 = (longlong *)
                       GemCartBufferManager_GetGemCartBuffer
                                 (puVar7,(short)type + 0x21,(undefined *)0x0);
              if (plVar8 == (longlong *)0x0) {
                return 1;
              }
              if (*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c8f4048 + 0x130)) {
                return 1;
              }
              if (*(longlong *)
                   (*(longlong *)(*plVar8 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c8f4048 + 0x130) * 8) != _DAT_7ffe9c8f4048) {
                return 1;
              }
              *(undefined1 *)(plVar8 + 3) = 1;
              return 1;
            }
          }
        }
        goto LAB_7ffe9a444703;
      }
      goto LAB_7ffe9a44405b;
    }
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
    FUN_7ffe9a2f3fb0(uVar13,puVar7,_DAT_7ffe9c8fb458,0);
    lVar9 = FUN_7ffe9b5595f0(uVar12,uVar13,0);
    uVar12 = _DAT_7ffe9c8f32b8;
    if ((lVar9 != 0) && (lVar10 = func_0x7ffe9996c920(lVar9,_DAT_7ffe9c8f32b8), lVar10 == 0)) {
      FUN_7ffe9996c950(lVar9,uVar12);
      pcVar2 = (code *)swi(3);
      bVar4 = (*pcVar2)();
      return bVar4;
    }
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar9 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)), lVar9 == 0)
       ) goto LAB_7ffe9a444703;
    cVar3 = FUN_7ffe9a4d8d20(lVar9,0x2b,time,resist,puVar7[0x18],force,lVar10,0);
    if (cVar3 == '\0') {
      return 0;
    }
    if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a444703;
    cVar3 = *(char *)(*(longlong *)(thisObject + 0x28) + 0x142);
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
       lVar10 == 0)) goto LAB_7ffe9a444703;
    func_0x7ffe9a7cba00(lVar10,0);
    if (*(longlong *)(thisObject + 0xc0) == 0) goto LAB_7ffe9a444703;
    FUN_7ffe9a40e460(*(longlong *)(thisObject + 0xc0),0);
    (**(code **)(*(longlong *)thisObject + 0x388))
              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x390));
    plVar8 = *(longlong **)(thisObject + 0x38);
    *(undefined2 *)(thisObject + 0xce) = 0;
    if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a444703;
    if ((*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c9227e8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9227e8 + 0x130) * 8)
        != _DAT_7ffe9c9227e8)) {
      FUN_7ffe9996c950(plVar8);
      pcVar2 = (code *)swi(3);
      bVar4 = (*pcVar2)();
      return bVar4;
    }
    func_0x7ffe9a7e60b0(plVar8,0);
    goto LAB_7ffe9a4443e5;
  }
  switch(iVar6) {
  case 1:
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
    FUN_7ffe9a2f3fb0(uVar13,puVar7,uRam00007ffe9c8fb1e8,0);
    lVar9 = FUN_7ffe9b5595f0(uVar12,uVar13,0);
    uStack_58 = _DAT_7ffe9c8f32b8;
    if ((lVar9 != 0) && (lVar10 = func_0x7ffe9996c920(lVar9,_DAT_7ffe9c8f32b8), lVar10 == 0)) {
      FUN_7ffe9996c950(lVar9,uStack_58);
      pcVar2 = (code *)swi(3);
      bVar4 = (*pcVar2)();
      return bVar4;
    }
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar9 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)), lVar9 == 0)
       ) goto LAB_7ffe9a444703;
    cVar3 = FUN_7ffe9a4d8d20(lVar9,uVar15,time,resist,puVar7[0x18],force,lVar10,0);
    if (cVar3 == '\0') {
      return 0;
    }
    if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a444703;
    cVar3 = *(char *)(*(longlong *)(thisObject + 0x28) + 0x142);
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
       lVar10 == 0)) goto LAB_7ffe9a444703;
    func_0x7ffe9a7cba00(lVar10,0);
    if (*(longlong *)(thisObject + 0xc0) == 0) goto LAB_7ffe9a444703;
    FUN_7ffe9a40e460(*(longlong *)(thisObject + 0xc0),0);
    (**(code **)(*(longlong *)thisObject + 0x388))
              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x390));
    plVar8 = *(longlong **)(thisObject + 0x38);
    *(undefined2 *)(thisObject + 0xce) = 0;
    if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a444703;
    uVar12 = 100;
    uVar13 = 1;
    break;
  case 2:
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
    FUN_7ffe9a2f3fb0(uVar13,puVar7,uRam00007ffe9c8fb2b8,0);
    lVar9 = FUN_7ffe9b5595f0(uVar12,uVar13,0);
    uStack_58 = _DAT_7ffe9c8f32b8;
    if ((lVar9 != 0) && (lVar10 = func_0x7ffe9996c920(lVar9,_DAT_7ffe9c8f32b8), lVar10 == 0)) {
      FUN_7ffe9996c950(lVar9,uStack_58);
      pcVar2 = (code *)swi(3);
      bVar4 = (*pcVar2)();
      return bVar4;
    }
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar9 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)), lVar9 == 0)
       ) goto LAB_7ffe9a444703;
    cVar3 = FUN_7ffe9a4d8d20(lVar9,uVar15,time,resist,puVar7[0x18],force,lVar10,0);
    if (cVar3 == '\0') {
      return 0;
    }
    if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a444703;
    cVar3 = *(char *)(*(longlong *)(thisObject + 0x28) + 0x142);
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
       lVar10 == 0)) goto LAB_7ffe9a444703;
    func_0x7ffe9a7cba00(lVar10,0);
    if (*(longlong *)(thisObject + 0xc0) == 0) goto LAB_7ffe9a444703;
    FUN_7ffe9a40e460(*(longlong *)(thisObject + 0xc0),0);
    (**(code **)(*(longlong *)thisObject + 0x388))
              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x390));
    plVar8 = *(longlong **)(thisObject + 0x38);
    *(undefined2 *)(thisObject + 0xce) = 0;
    if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a444703;
    uVar12 = 0x65;
    uVar13 = 1;
    break;
  case 3:
code_r0x7ffe9a444163:
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8f32b8);
    FUN_7ffe9a2f3fb0(uVar13,puVar7,_DAT_7ffe9c8fb388,0);
    lVar9 = FUN_7ffe9b5595f0(uVar12,uVar13,0);
    uVar12 = _DAT_7ffe9c8f32b8;
    if ((lVar9 != 0) && (lVar10 = func_0x7ffe9996c920(lVar9,_DAT_7ffe9c8f32b8), lVar10 == 0)) {
      FUN_7ffe9996c950(lVar9,uVar12);
      pcVar2 = (code *)swi(3);
      bVar4 = (*pcVar2)();
      return bVar4;
    }
    if (iVar6 == 0x14) {
      plVar8 = (longlong *)
               (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar8 == (longlong *)0x0) ||
         (puVar14 = (undefined *)
                    (**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220)),
         puVar14 == (undefined *)0x0)) goto LAB_7ffe9a444703;
      puVar14 = GemCartBufferManager_GetGemCartBuffer(puVar14,(short)type + 2,(undefined *)0x0);
      if (puVar14 != (undefined *)0x0) {
        iVar6 = GemCartBufferBase_GetValue(puVar14,(undefined *)0x2,(undefined *)0x0);
        time = time * (_DAT_7ffe9c049b18 - (float)iVar6 * _DAT_7ffe9c049b34);
      }
    }
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar9 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)), lVar9 == 0)
       ) goto LAB_7ffe9a444703;
    cVar3 = FUN_7ffe9a4d8d20(lVar9,uVar15,time,resist,puVar7[0x18],force,lVar10,0);
    if (cVar3 == '\0') {
      return 0;
    }
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
       lVar10 == 0)) goto LAB_7ffe9a444703;
    cVar3 = FUN_7ffe9abc2210(lVar10,0x52,&lStack_78,_DAT_7ffe9c96a188);
    if (cVar3 != '\0') {
      if (lStack_78 == 0) goto LAB_7ffe9a444703;
      FUN_7ffe9a7a5660(lStack_78,uVar15,0);
    }
    if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a444703;
    cVar3 = *(char *)(*(longlong *)(thisObject + 0x28) + 0x142);
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 == (longlong *)0x0) ||
       (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
       lVar10 == 0)) goto LAB_7ffe9a444703;
    func_0x7ffe9a7cba00(lVar10,0);
    if (*(longlong *)(thisObject + 0xc0) == 0) goto LAB_7ffe9a444703;
    FUN_7ffe9a40e460(*(longlong *)(thisObject + 0xc0),0);
    (**(code **)(*(longlong *)thisObject + 0x388))
              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x390));
    plVar8 = *(longlong **)(thisObject + 0x38);
    *(undefined2 *)(thisObject + 0xce) = 0;
    if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a444703;
    uVar12 = 0x69;
    uVar13 = 2;
    break;
  case 4:
    uVar1 = puVar7[0x18];
    if (DAT_7ffe9cad9b47 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
      DAT_7ffe9cad9b47 = '\x01';
    }
    uStack_50 = *(undefined4 *)(*(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8) + 1);
    uStack_58 = **(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8);
    cVar3 = FUN_7ffe9a445170(thisObject,actor,time,resist,uVar1,force,&uStack_58,0);
    if (cVar3 == '\0') {
      return 0;
    }
    return 1;
  case 5:
  case 6:
  case 7:
  case 8:
  case 10:
    goto LAB_7ffe9a44405b;
  case 9:
    lVar10 = *(longlong *)thisObject;
    if (time == 0.0) {
      plVar8 = (longlong *)(**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0))
      ;
      if ((plVar8 == (longlong *)0x0) ||
         (lVar10 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)),
         lVar10 == 0)) goto LAB_7ffe9a444703;
      bVar4 = FUN_7ffe9a4d8ee0(lVar10,uVar15,puVar7[0x18],force,uVar12,0);
    }
    else {
      plVar8 = (longlong *)(**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0))
      ;
      if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a444703;
      lVar10 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0));
      if (lVar10 == 0) goto LAB_7ffe9a444703;
      bVar4 = FUN_7ffe9a4d8d20(lVar10,uVar15,time,resist,puVar7[0x18],force,uVar12,0);
    }
    if (bVar4 == 0) {
      return 0;
    }
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar8 != (longlong *)0x0) &&
       (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
       lVar10 != 0)) {
      cVar3 = FUN_7ffe9abc2210(lVar10,0x52,&lStack_80,_DAT_7ffe9c96a188);
      if (cVar3 == '\0') {
        return bVar4;
      }
      if (lStack_80 != 0) {
        FUN_7ffe9a7a5660(lStack_80,uVar15,0);
        return bVar4;
      }
    }
    goto LAB_7ffe9a444703;
  case 0xb:
    FUN_7ffe9a44b9a0(thisObject,0);
    lVar10 = *(longlong *)(thisObject + 0xc0);
    if (lVar10 == 0) goto LAB_7ffe9a444703;
    if (*(int *)(lVar10 + 0x40) == 0x201) {
      FUN_7ffe9a40e460(lVar10,0);
    }
    goto LAB_7ffe9a44405b;
  default:
    if (iVar6 == 0x10) {
      lVar10 = *(longlong *)thisObject;
      if (time == 0.0) {
        plVar8 = (longlong *)
                 (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
        if ((plVar8 == (longlong *)0x0) ||
           (lVar10 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)),
           lVar10 == 0)) goto LAB_7ffe9a444703;
        bVar4 = FUN_7ffe9a4d8ee0(lVar10,uVar15,puVar7[0x18],force,uVar12,0);
      }
      else {
        plVar8 = (longlong *)
                 (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
        if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a444703;
        lVar10 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0));
        if (lVar10 == 0) goto LAB_7ffe9a444703;
        bVar4 = FUN_7ffe9a4d8d20(lVar10,uVar15,time,resist,puVar7[0x18],force,uVar12,0);
      }
      lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if (lVar10 != 0) {
        FUN_7ffe9a29adb0(lVar10,0);
        return bVar4;
      }
      goto LAB_7ffe9a444703;
    }
    if (iVar6 != 0x11) {
      if (iVar6 == 0x12) {
        plVar8 = (longlong *)
                 (**(code **)(*(longlong *)thisObject + 0x298))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar8 == (longlong *)0x0) ||
           (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
           lVar10 == 0)) goto LAB_7ffe9a444703;
        cVar3 = FUN_7ffe9a7c6d00(lVar10,0x34c,0);
        if (cVar3 != '\0') {
          plVar8 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar8 == (longlong *)0x0) ||
             (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
             lVar10 == 0)) goto LAB_7ffe9a444703;
          FUN_7ffe9a7cafa0(lVar10,0x34c,0);
        }
      }
      else {
        if (iVar6 == 0x13) {
          lVar10 = *(longlong *)thisObject;
          if (time == 0.0) {
            plVar8 = (longlong *)
                     (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
            if ((plVar8 == (longlong *)0x0) ||
               (lVar10 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)),
               lVar10 == 0)) goto LAB_7ffe9a444703;
            bVar4 = FUN_7ffe9a4d8ee0(lVar10,uVar15,puVar7[0x18],force,uVar12,0);
          }
          else {
            plVar8 = (longlong *)
                     (**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0));
            if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a444703;
            lVar10 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0));
            if (lVar10 == 0) goto LAB_7ffe9a444703;
            bVar4 = FUN_7ffe9a4d8d20(lVar10,uVar15,time,resist,puVar7[0x18],force,uVar12,0);
          }
          if (bVar4 == 0) {
            return 0;
          }
          plVar8 = (longlong *)
                   (**(code **)(*(longlong *)thisObject + 0x298))
                             (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar8 != (longlong *)0x0) &&
             (lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
             lVar10 != 0)) {
            cVar3 = FUN_7ffe9abc2210(lVar10,0x52,alStack_70,_DAT_7ffe9c96a188);
            if (cVar3 == '\0') {
              return bVar4;
            }
            if (alStack_70[0] != 0) {
              FUN_7ffe9a7a5660(alStack_70[0],uVar15,0);
              return bVar4;
            }
          }
          goto LAB_7ffe9a444703;
        }
        if (iVar6 == 0x14) goto code_r0x7ffe9a444163;
      }
    }
LAB_7ffe9a44405b:
    lVar10 = *(longlong *)thisObject;
    if (time == 0.0) {
      plVar8 = (longlong *)(**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0))
      ;
      if ((plVar8 != (longlong *)0x0) &&
         (lVar10 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0)),
         lVar10 != 0)) {
        bVar4 = FUN_7ffe9a4d8ee0(lVar10,uVar15,puVar7[0x18],force,uVar12,0);
        return bVar4;
      }
    }
    else {
      plVar8 = (longlong *)(**(code **)(lVar10 + 0x298))(thisObject,*(undefined8 *)(lVar10 + 0x2a0))
      ;
      if (plVar8 != (longlong *)0x0) {
        lVar10 = (**(code **)(*plVar8 + 0x1e8))(plVar8,*(undefined8 *)(*plVar8 + 0x1f0));
        if (lVar10 != 0) {
          bVar4 = FUN_7ffe9a4d8d20(lVar10,uVar15,time,resist,puVar7[0x18],force,uVar12,0);
          return bVar4;
        }
      }
    }
    goto LAB_7ffe9a444703;
  }
  (**(code **)(*plVar8 + 0x178))(plVar8,uVar12,uVar13,*(undefined8 *)(*plVar8 + 0x180));
LAB_7ffe9a4443e5:
  if (*(longlong *)(thisObject + 0x28) == 0) {
LAB_7ffe9a444703:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    bVar4 = (*pcVar2)();
    return bVar4;
  }
  *(undefined1 *)(*(longlong *)(thisObject + 0x28) + 0x139) = 0;
  if (cVar3 != '\0') {
    if (*(longlong *)(thisObject + 0x28) == 0) goto LAB_7ffe9a444703;
    *(undefined1 *)(*(longlong *)(thisObject + 0x28) + 0x138) = 1;
  }
  return 1;
}

