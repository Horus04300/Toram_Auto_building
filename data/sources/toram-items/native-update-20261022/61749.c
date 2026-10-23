
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIItemProperty_AddCapPropertyNoColor
          (short id,short val,undefined *itemPropertyTextManager,undefined *systemManager,
          undefined *methodInfo)

{
  undefined *puVar1;
  
  if (DAT_7ffe9cadbb11 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ee100);
    DAT_7ffe9cadbb11 = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  puVar1 = UIItemProperty_AddCapProperty
                     (0,id,val,itemPropertyTextManager,systemManager,(undefined *)0x0);
  return puVar1;
}

