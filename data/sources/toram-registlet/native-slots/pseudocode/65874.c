
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIRegistletEditPanel_CreateEquipGemButton
          (undefined *self,int param,undefined *pos,undefined *data,undefined *addSlot,
          undefined *methodInfo)

{
  longlong lVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  code *pcVar6;
  undefined *puVar7;
  longlong lVar8;
  undefined8 uVar9;
  longlong lVar10;
  longlong *plVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  int aiStackX_8 [2];
  undefined8 uStack_38;
  undefined4 uStack_30;
  
  if (DAT_7ffe9cadc322 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c967c98);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee118);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c93a5d8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c954178);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c93eaf8);
    FUN_7ffe9996d590(&DAT_7ffe9c93ebb8);
    FUN_7ffe9996d590(&DAT_7ffe9c93ec80);
    FUN_7ffe9996d590(&DAT_7ffe9c90b9d0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f5700);
    FUN_7ffe9996d590(&DAT_7ffe9c971d80);
    FUN_7ffe9996d590(&DAT_7ffe9c94c318);
    FUN_7ffe9996d590(&DAT_7ffe9c91e3e0);
    FUN_7ffe9996d590(&DAT_7ffe9c920190);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0d0);
    DAT_7ffe9cadc322 = '\x01';
  }
  uVar9 = *(undefined8 *)(self + 0x98);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  puVar7 = (undefined *)FUN_7ffe9abbb520(uVar9,_DAT_7ffe9c93a5d8);
  if ((puVar7 != (undefined *)0x0) && (lVar8 = FUN_7ffe9bd9b890(puVar7,0), lVar8 != 0)) {
    uStack_30 = *(undefined4 *)(pos + 8);
    uStack_38 = *(undefined8 *)pos;
    FUN_7ffe9bdbfcc0(lVar8,&uStack_38,0);
    lVar8 = FUN_7ffe9bd9b890(puVar7,0);
    if (DAT_7ffe9cad9b4e == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
      DAT_7ffe9cad9b4e = '\x01';
    }
    if (lVar8 != 0) {
      uStack_38 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0xc);
      uStack_30 = *(undefined4 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x14);
      FUN_7ffe9bdbfe00(lVar8,&uStack_38,0);
      lVar8 = FUN_7ffe9ab9c3a0(puVar7,_DAT_7ffe9c8ee118);
      uVar9 = func_0x7ffe99940040(_DAT_7ffe9c90b9d0);
      if (data == (undefined *)0x0) {
        if ((char)addSlot == '\0') {
          FUN_7ffe9aaf85f0(uVar9,self,_DAT_7ffe9c93ebb8,0);
          if ((*(longlong *)(self + 0x70) == 0) ||
             (uVar12 = FUN_7ffe99a58320(*(longlong *)(self + 0x70),_DAT_7ffe9c94c318,0), lVar8 == 0)
             ) goto LAB_7ffe9a0480e8;
          if (DAT_7ffe9cadc334 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c966950);
            DAT_7ffe9cadc334 = '\x01';
          }
          *(undefined8 *)(lVar8 + 0x38) = 0;
          il2cpp_write_barrier_0();
          if (*(longlong *)(lVar8 + 0x20) == 0) goto LAB_7ffe9a0480e8;
          FUN_7ffe9a515470(*(longlong *)(lVar8 + 0x20),_DAT_7ffe9c966950,0);
          if (*(longlong *)(lVar8 + 0x28) == 0) goto LAB_7ffe9a0480e8;
          FUN_7ffe9bd97d00(*(longlong *)(lVar8 + 0x28),0,0);
          if (*(longlong *)(lVar8 + 0x30) == 0) goto LAB_7ffe9a0480e8;
          FUN_7ffe9bd97d00(*(longlong *)(lVar8 + 0x30),1,0);
          if (*(longlong *)(lVar8 + 0x30) == 0) goto LAB_7ffe9a0480e8;
          FUN_7ffe9a404310(*(longlong *)(lVar8 + 0x30),uVar12,0);
        }
        else {
          FUN_7ffe9aaf85f0(uVar9,self,_DAT_7ffe9c93eaf8,0);
          param = -1;
          if ((*(longlong *)(self + 0xa0) == 0) ||
             (lVar10 = FUN_7ffe9a480320(*(longlong *)(self + 0xa0),0), lVar10 == 0))
          goto LAB_7ffe9a0480e8;
          iVar4 = *(int *)(lVar10 + 0x14);
          if ((*(longlong *)(self + 0xa0) == 0) ||
             ((lVar10 = FUN_7ffe9a480320(*(longlong *)(self + 0xa0),0), lVar10 == 0 ||
              (*(longlong *)(lVar10 + 0x18) == 0)))) goto LAB_7ffe9a0480e8;
          bVar2 = *(byte *)(*(longlong *)(lVar10 + 0x18) + 0x20);
          if ((*(longlong *)(self + 0xa0) == 0) ||
             ((lVar10 = FUN_7ffe9a480320(*(longlong *)(self + 0xa0),0), lVar10 == 0 ||
              (lVar10 = *(longlong *)(lVar10 + 0x30), lVar10 == 0)))) goto LAB_7ffe9a0480e8;
          lVar1 = (ulonglong)bVar2 - 1;
          if (*(uint *)(lVar10 + 0x18) <= (uint)lVar1) {
            FUN_7ffe9996d790();
            pcVar6 = (code *)swi(3);
            puVar7 = (undefined *)(*pcVar6)();
            return puVar7;
          }
          iVar5 = *(int *)(lVar10 + 0x20 + lVar1 * 4);
          self[0xc0] = iVar5 <= iVar4;
          uVar12 = _DAT_7ffe9c91e3e0;
          uVar15 = _DAT_7ffe9c8f5700;
          if (iVar5 <= iVar4) {
            uVar12 = **(undefined8 **)(_DAT_7ffe9c9590b8 + 0xb8);
            uVar15 = _DAT_7ffe9c920190;
          }
          if (*(longlong *)(self + 0x70) == 0) {
LAB_7ffe9a0480f4:
            FUN_7ffe9996d7a0();
            pcVar6 = (code *)swi(3);
            puVar7 = (undefined *)(*pcVar6)();
            return puVar7;
          }
          uVar13 = FUN_7ffe99a58320(*(longlong *)(self + 0x70),_DAT_7ffe9c94c0d0,0);
          aiStackX_8[0] = iVar5;
          uVar14 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_8);
          uVar15 = FUN_7ffe9b36a740(uVar15,uVar14,0);
          uVar15 = FUN_7ffe9b36a740(uVar13,uVar15,0);
          uVar12 = FUN_7ffe9b3675b0(uVar12,uVar15,0);
          if (lVar8 == 0) goto LAB_7ffe9a0480f4;
          if (DAT_7ffe9cadc335 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c961ef0);
            DAT_7ffe9cadc335 = '\x01';
          }
          if (*(longlong *)(lVar8 + 0x28) == 0) goto LAB_7ffe9a0480f4;
          FUN_7ffe9bd97d00(*(longlong *)(lVar8 + 0x28),0,0);
          if (*(longlong *)(lVar8 + 0x30) == 0) goto LAB_7ffe9a0480f4;
          FUN_7ffe9bd97d00(*(longlong *)(lVar8 + 0x30),1,0);
          if (*(longlong *)(lVar8 + 0x30) == 0) goto LAB_7ffe9a0480f4;
          FUN_7ffe9a404310(*(longlong *)(lVar8 + 0x30),uVar12,0);
          if (*(longlong *)(lVar8 + 0x20) == 0) goto LAB_7ffe9a0480f4;
          FUN_7ffe9a515470(*(longlong *)(lVar8 + 0x20),_DAT_7ffe9c961ef0,0);
        }
      }
      else {
        FUN_7ffe9aaf85f0(uVar9,self,_DAT_7ffe9c93ec80,0);
        plVar11 = *(longlong **)(self + 0x78);
        sVar3 = *(short *)(data + 0x20);
        if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a0480e8;
        lVar10 = func_0x7ffe9996d210(*(undefined8 *)
                                      (*plVar11 +
                                      ((ulonglong)*(ushort *)(_DAT_7ffe9c954178 + 0x50) + 0x14) *
                                      0x10));
        plVar11 = (longlong *)(**(code **)(lVar10 + 8))(plVar11,(int)sVar3,lVar10);
        if ((plVar11 == (longlong *)0x0) ||
           (uVar12 = (**(code **)(*plVar11 + 0x188))(plVar11,*(undefined8 *)(*plVar11 + 400)),
           lVar8 == 0)) goto LAB_7ffe9a0480e8;
        if (DAT_7ffe9cadc332 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c920578);
          DAT_7ffe9cadc332 = '\x01';
        }
        FUN_7ffe9a04ac90(lVar8,data,uVar12,_DAT_7ffe9c920578,0);
      }
      lVar8 = FUN_7ffe9ab9c3a0(puVar7,_DAT_7ffe9c967c98);
      if (lVar8 != 0) {
        FUN_7ffe999ea560(lVar8,uVar9,param,0);
        FUN_7ffe99ab4130(puVar7,_DAT_7ffe9c971d80,0);
        return puVar7;
      }
    }
  }
LAB_7ffe9a0480e8:
  FUN_7ffe9996d7a0();
  pcVar6 = (code *)swi(3);
  puVar7 = (undefined *)(*pcVar6)();
  return puVar7;
}

