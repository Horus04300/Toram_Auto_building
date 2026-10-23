
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerDataManager_UpdateStatusPoint(undefined *self,int point,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  longlong lVar3;
  undefined8 unaff_RBX;
  undefined8 in_R9;
  
  plVar2 = (longlong *)PlayerDataManager_get_PlayerStatus(self,(undefined *)0x0);
  if (plVar2 == (longlong *)0x0) {
    FUN_7fff5f47d660();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  lVar3 = (**(code **)(*plVar2 + 0x188))(plVar2,*(undefined8 *)(*plVar2 + 400),0,in_R9,unaff_RBX);
  if (lVar3 != 0) {
    *(int *)(lVar3 + 0x38) = point;
    return;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

