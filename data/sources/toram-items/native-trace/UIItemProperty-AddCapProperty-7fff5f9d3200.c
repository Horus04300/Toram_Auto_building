
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIItemProperty_AddCapProperty
          (short id,short val,undefined *itemPropertyTextManager,undefined *systemManager,
          undefined *methodInfo)

{
  undefined *puVar1;
  
  if (DAT_7fff625e328d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623f57b0);
    DAT_7fff625e328d = '\x01';
  }
  if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  puVar1 = UIItemProperty_AddCapProperty
                     (1,id,val,itemPropertyTextManager,systemManager,(undefined *)0x0);
  return puVar1;
}

