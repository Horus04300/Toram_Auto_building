
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
StageLoginDownloader_GetAssetDecryptData
          (undefined *self,undefined *asset,int key,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if (asset != (undefined *)0x0) {
    puVar2 = (undefined *)FUN_7fff618b0e20(asset,0);
    ResourceManager_AssetDecrypt(puVar2,key,(undefined *)0x0);
    return puVar2;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

