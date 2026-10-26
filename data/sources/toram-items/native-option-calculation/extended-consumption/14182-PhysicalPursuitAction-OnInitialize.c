
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicPursuitAction_OnInitialize
               (undefined *self,undefined *actarAction,undefined *targetPos,int motionSpeed,
               float castTime,int loopCount,int element,undefined *methodInfo)

{
  *(undefined4 *)(self + 0x20) = 0xbf800000;
  return;
}

