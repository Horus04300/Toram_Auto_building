
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BonusScriptManager_funcEquipTypeLimit(undefined *self,undefined *line,undefined *methodInfo)

{
  short sVar1;
  longlong *plVar2;
  code *pcVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  longlong lVar8;
  uint uVar9;
  bool bVar10;
  
  plVar2 = *(longlong **)(self + 0x18);
  if (plVar2 == (longlong *)0x0) {
    if ((line == (undefined *)0x0) || (lVar8 = *(longlong *)(self + 0x20), lVar8 == 0))
    goto LAB_7fff600032ff;
    sVar1 = *(short *)(line + 0x14);
LAB_7fff600031c3:
    *(int *)(lVar8 + 0x3c) = *(int *)(lVar8 + 0x3c) + (int)sVar1;
  }
  else {
    uVar9 = 0;
    if (line == (undefined *)0x0) goto LAB_7fff600032ff;
    switch(*(int *)(line + 0x10)) {
    case 0x60:
      uVar9 = 0x17;
      break;
    case 0x61:
      uVar9 = 10;
      break;
    case 0x62:
      uVar9 = 0xb;
      break;
    case 99:
      uVar9 = 0xc;
      break;
    case 100:
      uVar9 = 0xd;
      break;
    case 0x65:
      uVar9 = 0xe;
      break;
    case 0x66:
      uVar9 = 0xf;
      break;
    case 0x67:
      uVar9 = 0x10;
      break;
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6e:
    case 0x6f:
    case 0x70:
    case 0x71:
    case 0x72:
      break;
    case 0x6c:
      uVar9 = 10;
LAB_7fff60003137:
      lVar8 = (**(code **)(*plVar2 + 0x1f8))(plVar2,*(undefined8 *)(*plVar2 + 0x200));
      if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x18) == 0)) goto LAB_7fff600032ff;
      uVar5 = func_0x7fff5f72ea30(*(longlong *)(lVar8 + 0x18),0);
      plVar2 = *(longlong **)(self + 0x18);
      if ((plVar2 == (longlong *)0x0) ||
         ((lVar8 = (**(code **)(*plVar2 + 0x1f8))(plVar2,*(undefined8 *)(*plVar2 + 0x200)),
          lVar8 == 0 || (*(longlong *)(lVar8 + 0x20) == 0)))) goto LAB_7fff600032ff;
      uVar6 = func_0x7fff5f72ea30(*(longlong *)(lVar8 + 0x20),0);
      if (uVar5 != uVar9) goto LAB_7fff600031b2;
      goto LAB_7fff600032e2;
    case 0x6d:
      uVar9 = 0x11;
      break;
    case 0x73:
      uVar9 = 9;
      break;
    case 0x74:
      uVar9 = 8;
      break;
    case 0x75:
      uVar9 = 0x13;
      break;
    case 0x76:
      uVar9 = 0x12;
      break;
    case 0x77:
    case 0x78:
      lVar8 = (**(code **)(*plVar2 + 0x1f8))(plVar2,*(undefined8 *)(*plVar2 + 0x200));
      if (lVar8 == 0) goto LAB_7fff600032ff;
      lVar8 = FUN_7fff5f718a50(lVar8,0);
      uVar5 = uVar9;
      if (lVar8 == 0) {
code_r0x7fff60003254:
        bVar10 = false;
        if (uVar5 != 2) goto code_r0x7fff6000325b;
        uVar9 = (uint)(*(int *)(line + 0x10) == 0x78);
code_r0x7fff6000326c:
        if (uVar9 != 0) goto LAB_7fff600032ea;
        goto LAB_7fff600031b2;
      }
      bVar4 = func_0x7fff6007a0d0(lVar8,0);
      uVar5 = (uint)bVar4;
      if (bVar4 != 1) goto code_r0x7fff60003254;
      bVar10 = *(int *)(line + 0x10) == 0x77;
code_r0x7fff6000325b:
      if (!bVar10) goto code_r0x7fff6000326c;
      goto LAB_7fff600032ea;
    default:
      if (*(int *)(line + 0x10) == 0x6c) goto LAB_7fff60003137;
    }
    lVar8 = (**(code **)(*plVar2 + 0x1f8))(plVar2,*(undefined8 *)(*plVar2 + 0x200));
    if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x18) == 0)) goto LAB_7fff600032ff;
    uVar5 = func_0x7fff5f72ea30(*(longlong *)(lVar8 + 0x18),0);
    plVar2 = *(longlong **)(self + 0x18);
    if ((plVar2 == (longlong *)0x0) ||
       ((lVar8 = (**(code **)(*plVar2 + 0x1f8))(plVar2,*(undefined8 *)(*plVar2 + 0x200)), lVar8 == 0
        || (*(longlong *)(lVar8 + 0x20) == 0)))) goto LAB_7fff600032ff;
    uVar6 = func_0x7fff5f72ea30(*(longlong *)(lVar8 + 0x20),0);
    if (uVar5 != uVar9) {
LAB_7fff600032e2:
      if (uVar6 != uVar9) {
LAB_7fff600031b2:
        lVar8 = *(longlong *)(self + 0x20);
        if (lVar8 == 0) goto LAB_7fff600032ff;
        sVar1 = *(short *)(line + 0x14);
        goto LAB_7fff600031c3;
      }
    }
LAB_7fff600032ea:
    if (*(longlong *)(self + 0x20) == 0) {
LAB_7fff600032ff:
      FUN_7fff5f47d660();
      pcVar3 = (code *)swi(3);
      iVar7 = (*pcVar3)();
      return iVar7;
    }
    *(int *)(*(longlong *)(self + 0x20) + 0x74) = (int)*(short *)(line + 0x14);
  }
  return 0;
}

