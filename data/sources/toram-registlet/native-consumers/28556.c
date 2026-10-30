
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartHealStockpileBuf_Updata(undefined *thisObject,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  byte bVar3;
  undefined *thisObject_00;
  
  plVar1 = *(longlong **)(thisObject + 0x28);
  if (plVar1 != (longlong *)0x0) {
    thisObject_00 =
         (undefined *)(**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220));
    if (thisObject_00 != (undefined *)0x0) {
      bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x402,(undefined *)0x0);
      if (bVar3 == 0) {
        thisObject[0x13] = 1;
        return;
      }
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

