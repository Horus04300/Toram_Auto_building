
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobAttackBase_CheckUnavoidable(undefined *self,undefined *playerAction,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong *plStackX_10;
  
  if (DAT_7ffe9cadd7df == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c9481a0);
    FUN_7ffe9996d590(&DAT_7ffe9c933c20);
    DAT_7ffe9cadd7df = '\x01';
  }
  plStackX_10 = (longlong *)0x0;
  if (playerAction != (undefined *)0x0) {
    plVar5 = (longlong *)
             (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar5 != (longlong *)0x0) {
      lVar6 = (**(code **)(*plVar5 + 0x1c8))(plVar5,*(undefined8 *)(*plVar5 + 0x1d0));
      if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x50) != 0)) {
        cVar2 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x50),0x26f,&plStackX_10,_DAT_7ffe9c934418);
        bVar3 = 0;
        if (cVar2 != '\0') {
          if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a375068;
          if (((*(byte *)(*plStackX_10 + 0x130) < *(byte *)(_DAT_7ffe9c933c20 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStackX_10 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c933c20 + 0x130) * 8) != _DAT_7ffe9c933c20)) ||
             (plStackX_10 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStackX_10);
            pcVar1 = (code *)swi(3);
            bVar3 = (*pcVar1)();
            return bVar3;
          }
          if ((char)plStackX_10[4] != '\0') {
            bVar3 = 1;
          }
        }
        if ((*(longlong *)(playerAction + 0x30) != 0) &&
           (plVar5 = *(longlong **)(*(longlong *)(playerAction + 0x30) + 0x30),
           plVar5 != (longlong *)0x0)) {
          plVar5 = (longlong *)(**(code **)(*plVar5 + 0x188))(plVar5,*(undefined8 *)(*plVar5 + 400))
          ;
          cVar2 = FUN_7ffe9a8fecd0(plVar5,0,0);
          if (cVar2 != '\0') {
            if (plVar5 == (longlong *)0x0) goto LAB_7ffe9a375068;
            iVar4 = (**(code **)(*plVar5 + 0x188))(plVar5,*(undefined8 *)(*plVar5 + 400));
            if (iVar4 == 0x27d) {
              if ((*(byte *)(*plVar5 + 0x130) < *(byte *)(_DAT_7ffe9c9481a0 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*plVar5 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c9481a0 + 0x130) * 8) != _DAT_7ffe9c9481a0)) {
                FUN_7ffe9996c950(plVar5);
                pcVar1 = (code *)swi(3);
                bVar3 = (*pcVar1)();
                return bVar3;
              }
              if ((int)plVar5[0x2a] == 0) {
                bVar3 = 1;
              }
            }
          }
          return bVar3;
        }
      }
    }
  }
LAB_7ffe9a375068:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

