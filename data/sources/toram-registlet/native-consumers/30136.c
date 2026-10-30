
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ISwordMove_CheckSwordMoveStart(undefined *playerAction,undefined *skill,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  undefined4 uVar4;
  longlong *plVar5;
  undefined *thisObject;
  longlong lVar6;
  
  if (DAT_7ffe9cadf4ce == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940af8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadf4ce = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar2 = FUN_7ffe9bda1fa0(playerAction,0,0);
  if (cVar2 != '\0') {
    return 0;
  }
  if (((playerAction != (undefined *)0x0) &&
      (plVar5 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
      plVar5 != (longlong *)0x0)) &&
     (thisObject = (undefined *)
                   (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
     thisObject != (undefined *)0x0)) {
    bVar3 = GemCartBufferManager_ContainsBuffer(thisObject,0x197,(undefined *)0x0);
    if ((bVar3 != 0) || (lVar6 = func_0x7ffe9996c920(playerAction,_DAT_7ffe9c940af8), lVar6 == 0)) {
      return 0;
    }
    if (skill != (undefined *)0x0) {
      uVar4 = (**(code **)(*(longlong *)skill + 0x188))
                        (skill,*(undefined8 *)(*(longlong *)skill + 400));
      cVar2 = FUN_7ffe99749320(0xc,_DAT_7ffe9c940af8,lVar6,uVar4);
      if (cVar2 != '\0') {
        uVar4 = (**(code **)(*(longlong *)skill + 0x188))
                          (skill,*(undefined8 *)(*(longlong *)skill + 400));
        cVar2 = FUN_7ffe99749320(0xd,_DAT_7ffe9c940af8,lVar6,uVar4);
        if (cVar2 == '\0') {
          return 0;
        }
      }
      lVar6 = (**(code **)(*(longlong *)playerAction + 0x2a8))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2b0));
      if (lVar6 != 0) {
        cVar2 = FUN_7ffe9a4daa60(lVar6,0xc);
        if (cVar2 != '\0') {
          return 0;
        }
        lVar6 = (**(code **)(*(longlong *)playerAction + 0x2a8))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2b0));
        if (lVar6 != 0) {
          cVar2 = FUN_7ffe9a4daa60(lVar6,0xb);
          if (cVar2 != '\0') {
            return 0;
          }
          return 1;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

