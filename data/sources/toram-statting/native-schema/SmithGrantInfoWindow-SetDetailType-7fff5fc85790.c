
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
SmithGrantInfoWindow_SetDetailType
          (undefined *self,int enhanceType,byte isElement,undefined *methodInfo)

{
  undefined *self_00;
  
  if (DAT_7fff625e425a == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242a790);
    DAT_7fff625e425a = '\x01';
  }
  self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242a790);
  SmithGrantInfoWindow_Start(self_00,(undefined *)0x0);
  *(undefined **)(self_00 + 0x20) = self;
  *(undefined4 *)(self_00 + 0x10) = 0;
  thunk_FUN_7fff5f491fd0();
  *(int *)(self_00 + 0x28) = enhanceType;
  self_00[0x2c] = isElement;
  return self_00;
}

