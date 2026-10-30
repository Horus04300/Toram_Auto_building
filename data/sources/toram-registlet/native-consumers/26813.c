
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ShieldBashAction_CheckAbnormalSubEffect
               (undefined *thisObject,undefined *abnormalType,undefined *actor,undefined *methodInfo
               )

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong *plVar4;
  undefined *puVar5;
  longlong lVar6;
  
  if (DAT_7ffe9cadf217 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c963da8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadf217 = '\x01';
  }
  func_0x7ffe9a4ac300(thisObject,(ulonglong)abnormalType & 0xffffffff,actor,0);
  if ((int)abnormalType != 3) {
    return;
  }
  if (actor != (undefined *)0x0) {
    plVar4 = (longlong *)FUN_7ffe9ab9c3a0(actor,_DAT_7ffe9c963da8);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar2 = FUN_7ffe9bda2160(plVar4,0,0);
    if (cVar2 == '\0') {
      return;
    }
    if (((plVar4 != (longlong *)0x0) &&
        (plVar4 = (longlong *)
                  (**(code **)(*plVar4 + 0x298))(plVar4,*(undefined8 *)(*plVar4 + 0x2a0)),
        plVar4 != (longlong *)0x0)) &&
       (puVar5 = (undefined *)
                 (**(code **)(*plVar4 + 0x218))(plVar4,*(undefined8 *)(*plVar4 + 0x220)),
       puVar5 != (undefined *)0x0)) {
      puVar5 = GemCartBufferManager_GetGemCartBuffer(puVar5,0x3e9,(undefined *)0x0);
      if (puVar5 == (undefined *)0x0) {
        return;
      }
      iVar3 = GemCartBufferBase_GetValue(puVar5,(undefined *)0x2,(undefined *)0x0);
      lVar6 = FUN_7ffe9a47bac0(0);
      if ((lVar6 != 0) && (lVar6 = FUN_7ffe9a47f400(lVar6,0), lVar6 != 0)) {
        FUN_7ffe9a6fbaa0(lVar6,0xcc,iVar3,0);
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

