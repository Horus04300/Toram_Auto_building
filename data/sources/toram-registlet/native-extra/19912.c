
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void DarkTalentBuff_SetSlotNo(undefined *thisObject,byte slotNo,undefined *methodInfo)

{
  thisObject[0x18] = slotNo;
  return;
}

