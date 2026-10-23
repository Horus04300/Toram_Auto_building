
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ResourceManager_AssetDecrypt(undefined *data,int key,undefined *methodInfo)

{
  code *pcVar1;
  uint uVar2;
  longlong lVar3;
  byte bVar4;
  uint uVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  if (data != (undefined *)0x0) {
    uVar2 = *(uint *)(data + 0x18) & 0x80000003;
    if ((int)uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffffc) + 1;
    }
    uVar2 = (*(uint *)(data + 0x18) - uVar2) - 4;
    if (-1 < (int)uVar2) {
      iVar9 = -uVar2;
      do {
        uVar5 = 0;
        uVar8 = 0;
        bVar6 = 0x18;
        uVar7 = uVar2;
        do {
          if (*(uint *)(data + 0x18) <= uVar7) goto LAB_7fff5f5de0b0;
          lVar3 = (longlong)(int)uVar7;
          uVar7 = uVar7 + 1;
          bVar4 = bVar6 & 0x1f;
          bVar6 = bVar6 - 8;
          uVar5 = uVar5 | (uint)(byte)data[lVar3 + 0x20] << bVar4;
        } while ((int)(iVar9 + uVar7) < 4);
        if (0 < (int)uVar2) {
          uVar7 = uVar2 - 4;
          bVar6 = 0x18;
          do {
            if (*(uint *)(data + 0x18) <= uVar7) goto LAB_7fff5f5de0b0;
            lVar3 = (longlong)(int)uVar7;
            uVar7 = uVar7 + 1;
            bVar4 = bVar6 & 0x1f;
            bVar6 = bVar6 - 8;
            uVar8 = uVar8 | (uint)(byte)data[lVar3 + 0x20] << bVar4;
          } while ((int)(iVar9 + uVar7) < 0);
        }
        bVar6 = 0x18;
        uVar7 = uVar2;
        do {
          if (*(uint *)(data + 0x18) <= uVar7) {
LAB_7fff5f5de0b0:
            FUN_7fff5f47d650();
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          bVar4 = bVar6 & 0x1f;
          bVar6 = bVar6 - 8;
          lVar3 = (longlong)(int)uVar7;
          uVar7 = uVar7 + 1;
          data[lVar3 + 0x20] = (char)((int)(uVar8 ^ uVar5 ^ key) >> bVar4);
        } while ((int)(iVar9 + uVar7) < 4);
        iVar9 = iVar9 + 4;
        uVar2 = uVar2 - 4;
      } while (-1 < (int)uVar2);
    }
  }
  return;
}

