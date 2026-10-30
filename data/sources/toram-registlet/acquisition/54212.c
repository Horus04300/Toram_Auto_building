
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UITreasureHuntEnterManager_Initialize
               (undefined *self,int fieldId,byte roomId,int level,undefined *pos,float rot,
               undefined *emergency,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined *puVar8;
  undefined *self_00;
  bool bVar9;
  undefined8 uStack_28;
  undefined4 uStack_20;
  
  if (DAT_7ffe9cadab7a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c900548);
    FUN_7ffe9996d590(&DAT_7ffe9c928f20);
    FUN_7ffe9996d590(&DAT_7ffe9c9409a8);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c954238);
    FUN_7ffe9996d590(&DAT_7ffe9c96c9c0);
    FUN_7ffe9996d590(&DAT_7ffe9c9170f8);
    FUN_7ffe9996d590(&DAT_7ffe9c90a958);
    DAT_7ffe9cadab7a = '\x01';
  }
  lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar6 == 0) goto LAB_7ffe99c71a00;
  FUN_7ffe9a601cc0(lVar6,0);
  lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c954238);
  if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x70) == 0)) goto LAB_7ffe99c71a00;
  uVar4 = FUN_7ffe9a5962a0(*(longlong *)(lVar6 + 0x70),0xf42fe);
  *(undefined4 *)(self + 0x1e4) = uVar4;
  self[0x150] = 0;
  if (*(longlong *)(self + 0x178) == 0) goto LAB_7ffe99c71a00;
  lVar6 = FUN_7ffe9a47fce0(*(longlong *)(self + 0x178),0);
  if (lVar6 == 0) goto LAB_7ffe99c71a00;
  cVar3 = FUN_7ffe9a575dc0(lVar6,0);
  if (cVar3 == '\0') {
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar6 == 0) goto LAB_7ffe99c71a00;
    uVar7 = FUN_7ffe9a5a4710(lVar6,0);
    if (*(int *)(_DAT_7ffe9c90a958 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c90a958);
    }
    lVar6 = *(longlong *)(*(longlong *)(_DAT_7ffe9c90a958 + 0xb8) + 8);
    if (lVar6 == 0) {
      if (*(int *)(_DAT_7ffe9c90a958 + 0xe0) == 0) {
        func_0x7ffe9996d830(_DAT_7ffe9c90a958);
      }
      uVar1 = **(undefined8 **)(_DAT_7ffe9c90a958 + 0xb8);
      lVar6 = func_0x7ffe99940040(_DAT_7ffe9c9409a8);
      FUN_7ffe9af13420(lVar6,uVar1,_DAT_7ffe9c9170f8);
      *(longlong *)(*(longlong *)(_DAT_7ffe9c90a958 + 0xb8) + 8) = lVar6;
      il2cpp_write_barrier_0();
    }
    uVar7 = FUN_7ffe9ab93080(uVar7,lVar6);
    iVar5 = FUN_7ffe9ab80670(uVar7,_DAT_7ffe9c900548);
    if (0 < iVar5) {
      if (*(longlong *)(self + 0xa8) == 0) goto LAB_7ffe99c71a00;
      FUN_7ffe9bd9b390(*(longlong *)(self + 0xa8),1);
      lVar6 = *(longlong *)(self + 0xb0);
      if (lVar6 == 0) goto LAB_7ffe99c71a00;
      uVar7 = 0;
      goto LAB_7ffe99c718e9;
    }
    uVar7 = func_0x7ffe99940040(_DAT_7ffe9c96c9c0);
    FUN_7ffe9a628390(uVar7,0);
    *(undefined8 *)(self + 0x180) = uVar7;
    il2cpp_write_barrier_0();
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (lVar6 == 0) goto LAB_7ffe99c71a00;
    *(undefined8 *)(lVar6 + 0x28) = *(undefined8 *)(self + 0x180);
    il2cpp_write_barrier_0();
    puVar8 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (puVar8 == (undefined *)0x0) goto LAB_7ffe99c71a00;
    GameManager_CheckTreasureHuntRoom(puVar8,fieldId,roomId,(undefined *)0x0);
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x28) == 0)) goto LAB_7ffe99c71a00;
    uStack_28 = *(undefined8 *)pos;
    uStack_20 = *(undefined4 *)(pos + 8);
    func_0x7ffe9a601560(*(longlong *)(lVar6 + 0x28),fieldId,roomId,&uStack_28,rot,emergency,0);
    *(int *)(self + 0x188) = fieldId;
    self[0x18c] = roomId;
    *(int *)(self + 400) = level;
    if (*(longlong *)(self + 0xa8) == 0) goto LAB_7ffe99c71a00;
    FUN_7ffe9bd9b390(*(longlong *)(self + 0xa8),0);
    if (*(longlong *)(self + 0xb0) == 0) goto LAB_7ffe99c71a00;
    FUN_7ffe9bd9b390(*(longlong *)(self + 0xb0),0);
  }
  else {
    if (*(longlong *)(self + 0xa8) == 0) goto LAB_7ffe99c71a00;
    FUN_7ffe9bd9b390(*(longlong *)(self + 0xa8),0);
    lVar6 = *(longlong *)(self + 0xb0);
    if (lVar6 == 0) goto LAB_7ffe99c71a00;
    uVar7 = 1;
LAB_7ffe99c718e9:
    FUN_7ffe9bd9b390(lVar6,uVar7);
    self[0x150] = 1;
  }
  bVar9 = self[0x150] == '\0';
  if (*(longlong *)(self + 0x58) != 0) {
    FUN_7ffe9bd97d00(*(longlong *)(self + 0x58),bVar9);
    if (*(longlong *)(self + 0x40) != 0) {
      FUN_7ffe9bd9b390(*(longlong *)(self + 0x40),bVar9);
      if (*(longlong *)(self + 0x98) != 0) {
        puVar8 = (undefined *)0x0;
        FUN_7ffe9bd9b390(*(longlong *)(self + 0x98),bVar9);
        if (*(longlong *)(self + 0x178) != 0) {
          uVar7 = FUN_7ffe9a480320(*(longlong *)(self + 0x178),0);
          *(undefined8 *)(self + 0x1f0) = uVar7;
          il2cpp_write_barrier_0();
          if (self[0x150] == '\0') {
            if (DAT_7ffe9cadab7b == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c90ae38);
              DAT_7ffe9cadab7b = '\x01';
            }
            self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c90ae38);
            PhotonListener_OnGmTreasureHuntTrialPointMax(self_00,(undefined *)0x0,puVar8);
            *(undefined **)(self_00 + 0x20) = self;
            *(undefined4 *)(self_00 + 0x10) = 0;
            il2cpp_write_barrier_0();
            FUN_7ffe9bd9f640(self,self_00,0);
          }
          else {
            FUN_7ffe99c73400(self,0);
          }
          return;
        }
      }
    }
  }
LAB_7ffe99c71a00:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

