
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobAttackBase_checkHit(undefined *self,int mobFlee,int flee,int reduce,undefined *methodInfo)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  if (mobFlee == 0) {
    return 1;
  }
  iVar2 = reduce + 0x4b;
  fVar4 = (float)(flee - mobFlee) / _DAT_7ffe9c049b74;
  iVar3 = (int)fVar4;
  if (iVar3 < 0) {
    iVar3 = 0;
  }
  else if ((iVar2 < iVar3) && (iVar3 = iVar2, iVar2 < 0)) {
    return 1;
  }
  cVar1 = FUN_7ffe9a8fea70(fVar4,100,iVar3);
  return cVar1 == '\0';
}

