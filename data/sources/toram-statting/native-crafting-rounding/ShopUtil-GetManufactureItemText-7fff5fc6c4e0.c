
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
ShopUtil_GetManufactureItemText
          (undefined *itemData,undefined *systemTextManager,undefined *itemTextManager,
          undefined *itemPropertyTextManager,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  
  if (DAT_7fff625e41eb == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624606c8);
    DAT_7fff625e41eb = '\x01';
  }
  if (itemData != (undefined *)0x0) {
    cVar2 = func_0x7fff5fd830e0((int)*(short *)(itemData + 0x30),0);
    if (cVar2 == '\0') {
      puVar3 = (undefined *)**(undefined8 **)(_DAT_7fff624606c8 + 0xb8);
    }
    else {
      puVar3 = ShopUtil_GetManufactureItemPropertyText
                         (itemData,systemTextManager,itemTextManager,itemPropertyTextManager,
                          (undefined *)0x0);
    }
    return puVar3;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar1)();
  return puVar3;
}

