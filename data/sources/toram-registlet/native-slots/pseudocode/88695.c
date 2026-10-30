
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void Toram_Common_Registlet_RegistletData__ctor
               (undefined *self,undefined *binary,undefined *methodInfo)

{
  longlong lVar1;
  
  func_0x7ffe999c3920(self,0,0);
  self[0x18] = 1;
  if (DAT_7ffe9cad9998 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c939b40,binary,0);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    DAT_7ffe9cad9998 = '\x01';
  }
  lVar1 = func_0x7ffe99940040(_DAT_7ffe9c969f48);
  FUN_7ffe9b4c0ad0(lVar1,binary,0);
  (**(code **)(*(longlong *)self + 0x178))(self,lVar1,1,*(undefined8 *)(*(longlong *)self + 0x180));
  if (lVar1 != 0) {
    FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
  }
  return;
}

