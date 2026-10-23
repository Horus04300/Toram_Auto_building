
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte _ScriptThread_d__119_MoveNext(undefined *self,undefined *methodInfo)

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
  
  if (DAT_7fff625e7de0 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62436790);
    FUN_7fff5f47d450(&DAT_7fff62464420);
    FUN_7fff5f47d450(&DAT_7fff624640f8);
    FUN_7fff5f47d450(&DAT_7fff624641c8);
    FUN_7fff5f47d450(&DAT_7fff624644f0);
    FUN_7fff5f47d450(&DAT_7fff6243db58);
    FUN_7fff5f47d450(&DAT_7fff6243dc18);
    FUN_7fff5f47d450(&DAT_7fff62439250);
    FUN_7fff5f47d450(&DAT_7fff62446190);
    DAT_7fff625e7de0 = '\x01';
  }
  iVar10 = *(int *)(self + 0x10);
  lVar2 = *(longlong *)(self + 0x20);
  if (iVar10 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar2 == 0) goto LAB_7fff6055912a;
    *(undefined1 *)(lVar2 + 0x48) = 1;
    *(undefined1 *)(lVar2 + 0xac) = 1;
    *(undefined4 *)(lVar2 + 0xb0) = 0;
    lVar8 = FUN_7fff5fe67430(0);
    if (lVar8 == 0) goto LAB_7fff6055912a;
    if (*(char *)(lVar8 + 0x28) != '\0') {
      lVar8 = FUN_7fff5fe67430(0);
      if (lVar8 == 0) goto LAB_7fff6055912a;
      if (*(char *)(lVar8 + 0x29) != '\0') {
        uVar9 = func_0x7fff5f44ff00(_DAT_7fff62446190);
        func_0x7fff5f4d30f0(uVar9,0);
        *(undefined8 *)(self + 0x28) = uVar9;
        thunk_FUN_7fff5f491fd0();
        lVar8 = FUN_7fff5fe67430(0);
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7fff6055912a;
        FUN_7fff5f253010(4,_DAT_7fff6243db58);
        if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff6055912a;
        *(undefined1 *)(*(longlong *)(self + 0x28) + 0x10) = 0;
        uVar9 = *(undefined8 *)(self + 0x28);
        uVar7 = func_0x7fff5f44ff00(_DAT_7fff62436790);
        FUN_7fff5f4f6880(uVar7,uVar9,_DAT_7fff62439250,0);
        *(undefined8 *)(self + 0x38) = uVar7;
        thunk_FUN_7fff5f491fd0();
        lVar8 = FUN_7fff5fe67430(0);
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7fff6055912a;
        FUN_7fff5f252c60(0xe,_DAT_7fff6243dc18,*(longlong *)(lVar8 + 0x10),
                         *(undefined8 *)(self + 0x38));
        goto LAB_7fff60558f1c;
      }
      if (*(int *)(self + 0x30) != 0) {
        lVar8 = FUN_7fff5fe67430(0);
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7fff6055912a;
        FUN_7fff5f253010(4,_DAT_7fff6243db58);
        lVar8 = FUN_7fff5fe67430(0);
        if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7fff6055912a;
        FUN_7fff5f253010(1,_DAT_7fff6243db58);
      }
    }
  }
  else {
    if (iVar10 == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7fff60558f1c:
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff6055912a;
      if (*(char *)(*(longlong *)(self + 0x28) + 0x10) == '\0') {
        *(undefined8 *)(self + 0x18) = 0;
        thunk_FUN_7fff5f491fd0();
        *(undefined4 *)(self + 0x10) = 1;
        return 1;
      }
      lVar8 = FUN_7fff5fe67430(0);
      if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x10) == 0)) goto LAB_7fff6055912a;
      FUN_7fff5f252c60(0xf,_DAT_7fff6243dc18,*(longlong *)(lVar8 + 0x10),
                       *(undefined8 *)(self + 0x38));
      *(undefined8 *)(self + 0x28) = 0;
      thunk_FUN_7fff5f491fd0();
      *(undefined8 *)(self + 0x38) = 0;
      thunk_FUN_7fff5f491fd0();
    }
    else {
      if (iVar10 != 2) {
        return 0;
      }
      *(undefined4 *)(self + 0x10) = 0xffffffff;
    }
    if (lVar2 == 0) goto LAB_7fff6055912a;
  }
  do {
    while( true ) {
      if (*(char *)(lVar2 + 0x48) == '\0') {
        *(undefined4 *)(lVar2 + 0x4c) = 0xffffffff;
        *(undefined1 *)(lVar2 + 0xac) = 0;
        *(undefined1 *)(lVar2 + 0x48) = 0;
        *(undefined4 *)(lVar2 + 0xb0) = 0;
        FUN_7fff60534870(lVar2,*(undefined4 *)(self + 0x30),0);
        if (*(int *)(lVar2 + 0xdc) == 2) {
          return 0;
        }
        *(undefined4 *)(lVar2 + 0xdc) = 0;
        return 0;
      }
      if (*(int *)(self + 0x30) != *(int *)(lVar2 + 0x4c)) {
        return 0;
      }
      if (*(longlong *)(lVar2 + 0x40) == 0) goto LAB_7fff6055912a;
      sVar6 = FUN_7fff60506a30(*(longlong *)(lVar2 + 0x40),0);
      iVar10 = (int)sVar6;
      if (*(longlong *)(lVar2 + 0x120) == 0) goto LAB_7fff6055912a;
      cVar4 = FUN_7fff60869460(*(longlong *)(lVar2 + 0x120),iVar10,_DAT_7fff624640f8);
      if (cVar4 == '\0') break;
      if ((*(longlong *)(lVar2 + 0x120) == 0) ||
         (lVar8 = FUN_7fff6087c780(*(longlong *)(lVar2 + 0x120),iVar10,_DAT_7fff624641c8),
         lVar8 == 0)) goto LAB_7fff6055912a;
      (**(code **)(lVar8 + 0x18))(*(undefined8 *)(lVar8 + 0x40));
    }
    if (*(longlong *)(lVar2 + 0x128) == 0) goto LAB_7fff6055912a;
    cVar4 = FUN_7fff60869460();
  } while (cVar4 == '\0');
  fVar1 = *(float *)(lVar2 + 0xb0);
  fVar11 = (float)FUN_7fff618b0e60(0);
  *(float *)(lVar2 + 0xb0) = fVar11 + fVar1;
  if ((*(longlong *)(lVar2 + 0x128) != 0) &&
     (lVar8 = FUN_7fff6087c780(*(longlong *)(lVar2 + 0x128),iVar10,_DAT_7fff624644f0), lVar8 != 0))
  {
    uVar9 = (**(code **)(lVar8 + 0x18))
                      (*(undefined8 *)(lVar8 + 0x40),iVar10,*(undefined8 *)(lVar8 + 0x28));
    uVar9 = FUN_7fff618a87c0(lVar2,uVar9,0);
    *(undefined8 *)(self + 0x18) = uVar9;
    thunk_FUN_7fff5f491fd0();
    *(undefined4 *)(self + 0x10) = 2;
    return 1;
  }
LAB_7fff6055912a:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  bVar5 = (*pcVar3)();
  return bVar5;
}

