
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidRewardData__ctor
               (undefined *self,byte no,byte rewardNo,int cost,byte type,int value,int num,byte flag
               ,undefined *methodInfo)

{
  func_0x7ffe999c3920(self,0);
  self[0x18] = type;
  *(int *)(self + 0x1c) = value;
  *(int *)(self + 0x20) = num;
  self[0x10] = no;
  *(int *)(self + 0x14) = cost;
  self[0x24] = flag;
  self[0x11] = rewardNo;
  return;
}

