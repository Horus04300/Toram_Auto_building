
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte FieldScriptManager__ScriptThread_d__119_MoveNext(undefined *self,undefined *methodInfo)

{
  float fVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  byte bVar5;
  short sVar6;
  undefined8 uVar7;
  longlong lVar8;
  undefined8 uVar9;
  int iVar10;
  float fVar11;
  
  if (DAT_7ffe9cae068a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92eda0);
    FUN_7ffe9996d590(&DAT_7ffe9c95d540);
    FUN_7ffe9996d590(&DAT_7ffe9c95d218);
    FUN_7ffe9996d590(&DAT_7ffe9c95d2e0);
    FUN_7ffe9996d590(&DAT_7ffe9c95d608);
    FUN_7ffe9996d590(&DAT_7ffe9c9362e8);
    FUN_7ffe9996d590(&DAT_7ffe9c9363a8);
    FUN_7ffe9996d590(&DAT_7ffe9c932608);
    FUN_7ffe9996d590(&DAT_7ffe9c93ece8);
    DAT_7ffe9cae068a = '\x01';
  }
  iVar10 = *(int *)(self + 0x10);
  lVar2 = *(longlong *)(self + 0x20);
  if (iVar10 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar2 == 0) goto LAB_7ffe9aa4ed3a;
    *(undefined1 *)(lVar2 + 0x48) = 1;
    *(undefined1 *)(lVar2 + 0xac) = 1;
    *(undefined4 *)(lVar2 + 0xb0) = 0;
    lVar8 = FUN_7ffe9a35c7f0(0);
    if (lVar8 == 0) goto LAB_7ffe9aa4ed3a;
    if (*(char *)(lVar8 + 0x28) != '\0') {
      lVar8 = FUN_7ffe9a35c7f0(0);
      if (lVar8 == 0) goto LAB_7ffe9aa4ed3a;
      if (*(char *)(lVar8 + 0x29) != '\0') {
        uVar9 = func_0x7ffe99940040(_DAT_7ffe9c93ece8);
        func_0x7ffe999c30f0(uVar9,0);
        *(undefined8 *)(self + 0x28) = uVar9;
        il2cpp_write_barrier_0();
        lVar8 = FUN_7ffe9a35c7f0(0);
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7ffe9aa4ed3a;
        FUN_7ffe99743010(4,_DAT_7ffe9c9362e8);
        if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe9aa4ed3a;
        *(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 0;
        uVar9 = *(undefined8 *)(self + 0x28);
        uVar7 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
        FUN_7ffe999e6880(uVar7,uVar9,_DAT_7ffe9c932608,0);
        *(undefined8 *)(self + 0x38) = uVar7;
        il2cpp_write_barrier_0();
        lVar8 = FUN_7ffe9a35c7f0(0);
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7ffe9aa4ed3a;
        FUN_7ffe99742c60(0xe,_DAT_7ffe9c9363a8,*(longlong *)(lVar8 + 0x10),
                         *(undefined8 *)(self + 0x38));
        goto LAB_7ffe9aa4eb2c;
      }
      if (*(int *)(self + 0x30) != 0) {
        lVar8 = FUN_7ffe9a35c7f0(0);
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7ffe9aa4ed3a;
        FUN_7ffe99743010(4,_DAT_7ffe9c9362e8);
        lVar8 = FUN_7ffe9a35c7f0(0);
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7ffe9aa4ed3a;
        FUN_7ffe99743010(1);
      }
    }
  }
  else {
    if (iVar10 == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7ffe9aa4eb2c:
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe9aa4ed3a;
      if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\0') {
        *(undefined8 *)(self + 0x18) = 0;
        il2cpp_write_barrier_0();
        *(undefined4 *)(self + 0x10) = 1;
        return 1;
      }
      lVar8 = FUN_7ffe9a35c7f0(0);
      if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7ffe9aa4ed3a;
      FUN_7ffe99742c60(0xf,_DAT_7ffe9c9363a8,*(longlong *)(lVar8 + 0x10),
                       *(undefined8 *)(self + 0x38));
      *(undefined8 *)(self + 0x28) = 0;
      il2cpp_write_barrier_0();
      *(undefined8 *)(self + 0x38) = 0;
      il2cpp_write_barrier_0();
    }
    else {
      if (iVar10 != 2) {
        return 0;
      }
      *(undefined4 *)(self + 0x10) = 0xffffffff;
    }
    if (lVar2 == 0) goto LAB_7ffe9aa4ed3a;
  }
  do {
    while( true ) {
      if (*(char *)(lVar2 + 0x48) == '\0') {
        *(undefined4 *)(lVar2 + 0x4c) = 0xffffffff;
        *(undefined1 *)(lVar2 + 0xac) = 0;
        *(undefined1 *)(lVar2 + 0x48) = 0;
        *(undefined4 *)(lVar2 + 0xb0) = 0;
        FUN_7ffe9aa2a480(lVar2,*(undefined4 *)(self + 0x30),0);
        if (*(int *)(lVar2 + 0xdc) == 2) {
          return 0;
        }
        *(undefined4 *)(lVar2 + 0xdc) = 0;
        return 0;
      }
      if (*(int *)(self + 0x30) != *(int *)(lVar2 + 0x4c)) {
        return 0;
      }
      if (*(undefined **)(lVar2 + 0x40) == (undefined *)0x0) goto LAB_7ffe9aa4ed3a;
      sVar6 = FieldScriptLoader_ReadShort(*(undefined **)(lVar2 + 0x40),(undefined *)0x0);
      iVar10 = (int)sVar6;
      if (*(longlong *)(lVar2 + 0x120) == 0) goto LAB_7ffe9aa4ed3a;
      cVar4 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar2 + 0x120),iVar10,_DAT_7ffe9c95d218);
      if (cVar4 == '\0') break;
      if ((*(longlong *)(lVar2 + 0x120) == 0) ||
         (lVar8 = FUN_7ffe9ad723c0(*(longlong *)(lVar2 + 0x120),iVar10,_DAT_7ffe9c95d2e0),
         lVar8 == 0)) goto LAB_7ffe9aa4ed3a;
      (**(code **)(lVar8 + 0x18))(*(undefined8 *)(lVar8 + 0x40));
    }
    if (*(longlong *)(lVar2 + 0x128) == 0) goto LAB_7ffe9aa4ed3a;
    cVar4 = FUN_7ffe9ad5f0a0();
  } while (cVar4 == '\0');
  fVar1 = *(float *)(lVar2 + 0xb0);
  fVar11 = (float)FUN_7ffe9bda7ce0(0);
  *(float *)(lVar2 + 0xb0) = fVar11 + fVar1;
  if ((*(longlong *)(lVar2 + 0x128) != 0) &&
     (lVar8 = FUN_7ffe9ad723c0(*(longlong *)(lVar2 + 0x128),iVar10,_DAT_7ffe9c95d608), lVar8 != 0))
  {
    uVar9 = (**(code **)(lVar8 + 0x18))
                      (*(undefined8 *)(lVar8 + 0x40),iVar10,*(undefined8 *)(lVar8 + 0x28));
    uVar9 = FUN_7ffe9bd9f640(lVar2,uVar9,0);
    *(undefined8 *)(self + 0x18) = uVar9;
    il2cpp_write_barrier_0();
    *(undefined4 *)(self + 0x10) = 2;
    return 1;
  }
LAB_7ffe9aa4ed3a:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  bVar5 = (*pcVar3)();
  return bVar5;
}

