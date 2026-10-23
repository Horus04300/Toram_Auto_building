
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte StageLoginDownloader__StartDownload_d__13_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  byte bVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  if (DAT_7ffe9cad9d0f == '\0') {
    FUN_7ffe9996d590(0x7ffe9c955618);
    FUN_7ffe9996d590(&DAT_7ffe9c9540a0);
    FUN_7ffe9996d590(&DAT_7ffe9c953f08);
    FUN_7ffe9996d590(0x7ffe9c95a0d8);
    FUN_7ffe9996d590(&DAT_7ffe9c8fddd8);
    FUN_7ffe9996d590(0x7ffe9c8fe1e8);
    FUN_7ffe9996d590(0x7ffe9c8fe048);
    FUN_7ffe9996d590(0x7ffe9c95a008);
    FUN_7ffe9996d590(0x7ffe9c8fe2b8);
    FUN_7ffe9996d590(0x7ffe9c95a270);
    FUN_7ffe9996d590(0x7ffe9c8fe118);
    FUN_7ffe9996d590(0x7ffe9c95a1a0);
    FUN_7ffe9996d590(0x7ffe9c8fe388);
    DAT_7ffe9cad9d0f = '\x01';
  }
  lVar1 = *(longlong *)(self + 0x20);
  switch(*(undefined4 *)(self + 0x10)) {
  case 0:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if ((lVar1 != 0) && (*(longlong *)(lVar1 + 0x20) != 0)) {
      func_0x7ffe99ce5840(*(longlong *)(lVar1 + 0x20),0);
      if (cRam00007ffe9cad9d03 == '\0') {
        FUN_7ffe9996d590(0x7ffe9c929508);
        cRam00007ffe9cad9d03 = '\x01';
      }
      lVar5 = func_0x7ffe99940040(uRam00007ffe9c929508);
      func_0x7ffe999c3920(lVar5,0);
      *(longlong *)(lVar5 + 0x20) = lVar1;
      *(undefined4 *)(lVar5 + 0x10) = 0;
      il2cpp_write_barrier_0();
      uVar4 = FUN_7ffe9bd9f640(lVar1,lVar5,0);
      *(undefined8 *)(self + 0x18) = uVar4;
      il2cpp_write_barrier_0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
    break;
  case 1:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar1 != 0) {
      if (*(char *)(lVar1 + 0x30) != '\0') {
        func_0x7ffe999c3920(uRam00007ffe9c8fe048,0);
        uVar4 = FUN_7ffe99a34980(lVar1,uRam00007ffe9c95a008,0);
        uVar4 = FUN_7ffe9bd9f640(lVar1,uVar4,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 2;
        return 1;
      }
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        func_0x7ffe99ce5840(*(longlong *)(lVar1 + 0x20),0);
        if (cRam00007ffe9cad9d04 == '\0') {
          FUN_7ffe9996d590(0x7ffe9c9291e8);
          cRam00007ffe9cad9d04 = '\x01';
        }
        lVar5 = func_0x7ffe99940040(uRam00007ffe9c9291e8);
        func_0x7ffe999c3920(lVar5,0);
        *(longlong *)(lVar5 + 0x20) = lVar1;
        *(undefined4 *)(lVar5 + 0x10) = 0;
        il2cpp_write_barrier_0();
        uVar4 = FUN_7ffe9bd9f640(lVar1,lVar5,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 3;
        return 1;
      }
    }
    break;
  case 2:
  case 4:
  case 6:
  case 8:
  case 10:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    return 0;
  case 3:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar1 != 0) {
      if (*(char *)(lVar1 + 0x30) != '\0') {
        func_0x7ffe999c3920(uRam00007ffe9c8fe118,0);
        uVar4 = FUN_7ffe99a34980(lVar1,uRam00007ffe9c95a0d8,0);
        uVar4 = FUN_7ffe9bd9f640(lVar1,uVar4,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 4;
        return 1;
      }
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        func_0x7ffe99ce5840(*(longlong *)(lVar1 + 0x20),0);
        if (cRam00007ffe9cad9d05 == '\0') {
          FUN_7ffe9996d590(0x7ffe9c929378);
          cRam00007ffe9cad9d05 = '\x01';
        }
        lVar5 = func_0x7ffe99940040(uRam00007ffe9c929378);
        func_0x7ffe999c3920(lVar5,0);
        *(longlong *)(lVar5 + 0x20) = lVar1;
        *(undefined4 *)(lVar5 + 0x10) = 0;
        il2cpp_write_barrier_0();
        uVar4 = FUN_7ffe9bd9f640(lVar1,lVar5,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 5;
        return 1;
      }
    }
    break;
  case 5:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar1 != 0) {
      if (*(char *)(lVar1 + 0x30) != '\0') {
        func_0x7ffe999c3920(uRam00007ffe9c8fe1e8,0);
        uVar4 = FUN_7ffe99a34980(lVar1,uRam00007ffe9c95a1a0,0);
        uVar4 = FUN_7ffe9bd9f640(lVar1,uVar4,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 6;
        return 1;
      }
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        func_0x7ffe99ce5840(*(longlong *)(lVar1 + 0x20),0);
        if (cRam00007ffe9cad9d06 == '\0') {
          FUN_7ffe9996d590(0x7ffe9c9292b0);
          cRam00007ffe9cad9d06 = '\x01';
        }
        lVar5 = func_0x7ffe99940040(uRam00007ffe9c9292b0);
        func_0x7ffe999c3920(lVar5,0);
        *(longlong *)(lVar5 + 0x20) = lVar1;
        *(undefined4 *)(lVar5 + 0x10) = 0;
        il2cpp_write_barrier_0();
        uVar4 = FUN_7ffe9bd9f640(lVar1,lVar5,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 7;
        return 1;
      }
    }
    break;
  case 7:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar1 != 0) {
      if (*(char *)(lVar1 + 0x30) != '\0') {
        func_0x7ffe999c3920(uRam00007ffe9c8fe2b8,0);
        uVar4 = FUN_7ffe99a34980(lVar1,uRam00007ffe9c95a270,0);
        uVar4 = FUN_7ffe9bd9f640(lVar1,uVar4,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 8;
        return 1;
      }
      lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c953f08);
      if (lVar5 != 0) {
        uVar4 = FUN_7ffe99a79bf0(lVar5,0,0);
        uVar4 = FUN_7ffe9bd9f640(lVar1,uVar4,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 9;
        return 1;
      }
    }
    break;
  case 9:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar1 != 0) {
      if (*(char *)(lVar1 + 0x30) != '\0') {
        func_0x7ffe999c3920(uRam00007ffe9c8fe2b8,0);
        uVar4 = FUN_7ffe99a34980(lVar1,uRam00007ffe9c95a270,0);
        uVar4 = FUN_7ffe9bd9f640(lVar1,uVar4,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 10;
        return 1;
      }
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        func_0x7ffe99ce5840(*(longlong *)(lVar1 + 0x20),0);
        if (cRam00007ffe9cad9d07 == '\0') {
          FUN_7ffe9996d590(0x7ffe9c929440);
          cRam00007ffe9cad9d07 = '\x01';
        }
        lVar5 = func_0x7ffe99940040(uRam00007ffe9c929440);
        func_0x7ffe999c3920(lVar5,0);
        *(longlong *)(lVar5 + 0x20) = lVar1;
        *(undefined4 *)(lVar5 + 0x10) = 0;
        il2cpp_write_barrier_0();
        uVar4 = FUN_7ffe9bd9f640(lVar1,lVar5,0);
        *(undefined8 *)(self + 0x18) = uVar4;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 0xb;
        return 1;
      }
    }
    break;
  case 0xb:
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar1 != 0) {
      if (*(char *)(lVar1 + 0x30) != '\0') {
        func_0x7ffe999c3920(uRam00007ffe9c8fe388,0);
      }
      if (*(longlong *)(lVar1 + 0x20) != 0) {
        func_0x7ffe99ce5840(*(longlong *)(lVar1 + 0x20),0);
        if (*(longlong *)(lVar1 + 0x50) != 0) {
          FUN_7ffe99ad12e0(*(longlong *)(lVar1 + 0x50),_DAT_7ffe9c8fddd8,0,0);
          lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c9540a0);
          if (lVar5 != 0) {
            FUN_7ffe99a82b70(lVar5,0);
            lVar5 = FUN_7ffe9b141840(uRam00007ffe9c955618);
            if (lVar5 != 0) {
              FUN_7ffe99ad6920(lVar5,4);
              if (*(longlong *)(lVar1 + 0x58) != 0) {
                func_0x7ffe9a8bb330(*(longlong *)(lVar1 + 0x58),0);
                return 0;
              }
            }
          }
        }
      }
    }
    break;
  default:
    return 0;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar3 = (*pcVar2)();
  return bVar3;
}

