
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
MobAttackBase_checkMobReaction(undefined *self,int guard,int avoid,undefined *methodInfo)

{
  char cVar1;
  undefined4 in_register_00000084;
  
  cVar1 = FUN_7ffe9a8fea70(self,100,CONCAT44(in_register_00000084,avoid));
  if (cVar1 == '\0') {
    cVar1 = FUN_7ffe9a8fea70(self,100,guard);
    return (undefined *)(ulonglong)(-(uint)(cVar1 != '\0') & 2);
  }
  return (undefined *)0x1;
}

