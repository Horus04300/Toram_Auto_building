
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * GemCartBufferFactory_Create(short id,short lv,undefined *status,undefined *methodInfo)

{
  undefined *puVar1;
  undefined8 uVar2;
  int iVar3;
  double dVar4;
  float fVar5;
  
  iVar3 = (int)id;
  if (DAT_7ffe9cade78d == '\0') {
    FUN_7ffe9996d590(0x7ffe9c92e538);
    FUN_7ffe9996d590(0x7ffe9c930da8);
    FUN_7ffe9996d590(0x7ffe9c9316d8);
    FUN_7ffe9996d590(0x7ffe9c935bc0);
    FUN_7ffe9996d590(0x7ffe9c9364f0);
    FUN_7ffe9996d590(0x7ffe9c936b10);
    FUN_7ffe9996d590(0x7ffe9c936e00);
    FUN_7ffe9996d590(0x7ffe9c937040);
    FUN_7ffe9996d590(0x7ffe9c938c70);
    FUN_7ffe9996d590(0x7ffe9c939f98);
    FUN_7ffe9996d590(0x7ffe9c93bef8);
    FUN_7ffe9996d590(0x7ffe9c93e228);
    FUN_7ffe9996d590(0x7ffe9c940ab8);
    FUN_7ffe9996d590(0x7ffe9c9423f8);
    FUN_7ffe9996d590(0x7ffe9c9424c0);
    FUN_7ffe9996d590(0x7ffe9c943ec8);
    FUN_7ffe9996d590(0x7ffe9c947c08);
    FUN_7ffe9996d590(0x7ffe9c947f18);
    FUN_7ffe9996d590(0x7ffe9c947fd8);
    FUN_7ffe9996d590(0x7ffe9c94acf8);
    FUN_7ffe9996d590(0x7ffe9c94bf58);
    FUN_7ffe9996d590(0x7ffe9c94c4b0);
    FUN_7ffe9996d590(0x7ffe9c94fd58);
    FUN_7ffe9996d590(0x7ffe9c9527d8);
    FUN_7ffe9996d590(0x7ffe9c9575e0);
    FUN_7ffe9996d590(0x7ffe9c9581d0);
    FUN_7ffe9996d590(0x7ffe9c958b60);
    FUN_7ffe9996d590(0x7ffe9c95a1b0);
    FUN_7ffe9996d590(0x7ffe9c95a418);
    FUN_7ffe9996d590(0x7ffe9c95da40);
    FUN_7ffe9996d590(0x7ffe9c95e0a0);
    FUN_7ffe9996d590(0x7ffe9c963510);
    FUN_7ffe9996d590(0x7ffe9c9641d0);
    FUN_7ffe9996d590(0x7ffe9c966c00);
    FUN_7ffe9996d590(0x7ffe9c967ff0);
    FUN_7ffe9996d590(0x7ffe9c968580);
    FUN_7ffe9996d590(0x7ffe9c96f238);
    FUN_7ffe9996d590(0x7ffe9c96f648);
    FUN_7ffe9996d590(0x7ffe9c973748);
    FUN_7ffe9996d590(0x7ffe9c8ef660);
    FUN_7ffe9996d590(0x7ffe9c8f0770);
    FUN_7ffe9996d590(0x7ffe9c8f0b80);
    FUN_7ffe9996d590(0x7ffe9c8f38f8);
    FUN_7ffe9996d590(0x7ffe9c8f4048);
    FUN_7ffe9996d590(0x7ffe9c8f4938);
    FUN_7ffe9996d590(0x7ffe9c8f4a08);
    FUN_7ffe9996d590(0x7ffe9c8fa1c8);
    FUN_7ffe9996d590(0x7ffe9c8fcf48);
    FUN_7ffe9996d590(0x7ffe9c8ff168);
    FUN_7ffe9996d590(0x7ffe9c8ffb28);
    FUN_7ffe9996d590(0x7ffe9c903338);
    FUN_7ffe9996d590(0x7ffe9c903408);
    FUN_7ffe9996d590(0x7ffe9c904e08);
    FUN_7ffe9996d590(0x7ffe9c905148);
    FUN_7ffe9996d590(0x7ffe9c9052e8);
    FUN_7ffe9996d590(0x7ffe9c9057c8);
    FUN_7ffe9996d590(0x7ffe9c909178);
    FUN_7ffe9996d590(0x7ffe9c926490);
    FUN_7ffe9996d590(0x7ffe9c927a70);
    FUN_7ffe9996d590(0x7ffe9c927c00);
    FUN_7ffe9996d590(0x7ffe9c928c68);
    FUN_7ffe9996d590(0x7ffe9c928d30);
    FUN_7ffe9996d590(0x7ffe9c928df8);
    FUN_7ffe9996d590(0x7ffe9c929690);
    FUN_7ffe9996d590(0x7ffe9c929820);
    FUN_7ffe9996d590(0x7ffe9c929d98);
    FUN_7ffe9996d590(0x7ffe9c929e60);
    FUN_7ffe9996d590(0x7ffe9c92b310);
    FUN_7ffe9996d590(0x7ffe9c92b620);
    FUN_7ffe9996d590(0x7ffe9c92bd00);
    FUN_7ffe9996d590(0x7ffe9c934380);
    FUN_7ffe9996d590(0x7ffe9c949d20);
    FUN_7ffe9996d590(0x7ffe9c94e390);
    FUN_7ffe9996d590(0x7ffe9c954a60);
    FUN_7ffe9996d590(0x7ffe9c955a40);
    FUN_7ffe9996d590(0x7ffe9c955b10);
    FUN_7ffe9996d590(0x7ffe9c955bd8);
    FUN_7ffe9996d590(0x7ffe9c956a30);
    FUN_7ffe9996d590(0x7ffe9c957ee8);
    FUN_7ffe9996d590(0x7ffe9c95b848);
    FUN_7ffe9996d590(0x7ffe9c95c908);
    FUN_7ffe9996d590(0x7ffe9c95cc38);
    FUN_7ffe9996d590(0x7ffe9c95d688);
    FUN_7ffe9996d590(0x7ffe9c95db50);
    FUN_7ffe9996d590(0x7ffe9c95e348);
    FUN_7ffe9996d590(0x7ffe9c95e810);
    FUN_7ffe9996d590(0x7ffe9c95ea78);
    FUN_7ffe9996d590(0x7ffe9c95f5a0);
    FUN_7ffe9996d590(0x7ffe9c95f738);
    FUN_7ffe9996d590(0x7ffe9c95f800);
    FUN_7ffe9996d590(0x7ffe9c95f998);
    FUN_7ffe9996d590(0x7ffe9c964ad8);
    FUN_7ffe9996d590(0x7ffe9c968b60);
    FUN_7ffe9996d590(0x7ffe9c968cf8);
    FUN_7ffe9996d590(0x7ffe9c968dc0);
    FUN_7ffe9996d590(0x7ffe9c968f58);
    FUN_7ffe9996d590(0x7ffe9c969028);
    FUN_7ffe9996d590(0x7ffe9c96d3d8);
    FUN_7ffe9996d590(0x7ffe9c96ea68);
    FUN_7ffe9996d590(0x7ffe9c8fc0f0);
    FUN_7ffe9996d590(0x7ffe9c8fc5d0);
    FUN_7ffe9996d590(0x7ffe9c901090);
    FUN_7ffe9996d590(0x7ffe9c903ee0);
    FUN_7ffe9996d590(0x7ffe9c904970);
    FUN_7ffe9996d590(0x7ffe9c9083f0);
    FUN_7ffe9996d590(0x7ffe9c911ca0);
    FUN_7ffe9996d590(0x7ffe9c912800);
    FUN_7ffe9996d590(0x7ffe9c9129a0);
    FUN_7ffe9996d590(0x7ffe9c912c10);
    FUN_7ffe9996d590(0x7ffe9c9150a0);
    FUN_7ffe9996d590(0x7ffe9c91e008);
    FUN_7ffe9996d590(0x7ffe9c91e0d0);
    FUN_7ffe9996d590(0x7ffe9c920bc8);
    FUN_7ffe9996d590(0x7ffe9c9253a8);
    FUN_7ffe9996d590(0x7ffe9c927220);
    FUN_7ffe9996d590(0x7ffe9c9273b0);
    FUN_7ffe9996d590(0x7ffe9c927478);
    FUN_7ffe9996d590(0x7ffe9c928b20);
    FUN_7ffe9996d590(0x7ffe9c929610);
    FUN_7ffe9996d590(0x7ffe9c92b8b0);
    FUN_7ffe9996d590(0x7ffe9c92cd40);
    FUN_7ffe9996d590(0x7ffe9c92d118);
    FUN_7ffe9996d590(0x7ffe9c92e680);
    FUN_7ffe9996d590(0x7ffe9c92f428);
    FUN_7ffe9996d590(0x7ffe9c934240);
    FUN_7ffe9996d590(0x7ffe9c934488);
    FUN_7ffe9996d590(0x7ffe9c934550);
    FUN_7ffe9996d590(0x7ffe9c93e2b0);
    FUN_7ffe9996d590(0x7ffe9c93e370);
    FUN_7ffe9996d590(0x7ffe9c9468a0);
    FUN_7ffe9996d590(0x7ffe9c946ec0);
    FUN_7ffe9996d590(0x7ffe9c947048);
    FUN_7ffe9996d590(0x7ffe9c9482a8);
    FUN_7ffe9996d590(0x7ffe9c949068);
    FUN_7ffe9996d590(0x7ffe9c94c2e8);
    FUN_7ffe9996d590(0x7ffe9c94cc18);
    FUN_7ffe9996d590(0x7ffe9c94d300);
    FUN_7ffe9996d590(0x7ffe9c94f570);
    FUN_7ffe9996d590(0x7ffe9c94f6f8);
    FUN_7ffe9996d590(0x7ffe9c9507d0);
    FUN_7ffe9996d590(0x7ffe9c950d30);
    FUN_7ffe9996d590(0x7ffe9c9541e0);
    FUN_7ffe9996d590(0x7ffe9c955028);
    FUN_7ffe9996d590(0x7ffe9c958728);
    FUN_7ffe9996d590(0x7ffe9c958f20);
    FUN_7ffe9996d590(0x7ffe9c95f448);
    FUN_7ffe9996d590(0x7ffe9c95f5e0);
    FUN_7ffe9996d590(0x7ffe9c9618e8);
    FUN_7ffe9996d590(0x7ffe9c962c08);
    FUN_7ffe9996d590(0x7ffe9c965978);
    FUN_7ffe9996d590(0x7ffe9c965a40);
    FUN_7ffe9996d590(0x7ffe9c966bc0);
    FUN_7ffe9996d590(0x7ffe9c966d58);
    FUN_7ffe9996d590(0x7ffe9c967088);
    FUN_7ffe9996d590(0x7ffe9c96a9e8);
    FUN_7ffe9996d590(0x7ffe9c96d8e8);
    FUN_7ffe9996d590(0x7ffe9c96e6a0);
    FUN_7ffe9996d590(0x7ffe9c96e840);
    FUN_7ffe9996d590(0x7ffe9c8ff6d8);
    FUN_7ffe9996d590(0x7ffe9c900308);
    FUN_7ffe9996d590(0x7ffe9c9003d8);
    FUN_7ffe9996d590(0x7ffe9c904408);
    FUN_7ffe9996d590(0x7ffe9c9044d8);
    DAT_7ffe9cade78d = '\x01';
  }
  if (iVar3 < 0xda) {
    switch(iVar3) {
    case 1:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c938c70);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 2:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c968b60);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 3:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c968cf8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 4:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c968dc0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 5:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c96f648);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 6:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c969028);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 7:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c92b620);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 8:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9052e8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 9:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c936b10);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 10:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9641d0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0xb:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c929610);
      GemCartBuffer_PowerWaveChangeBuff__ctor(puVar1,lv,status,(undefined *)0x0);
      return puVar1;
    case 0xc:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9253a8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0xd:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c94bf58);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0xe:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c901090);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0xf:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9527d8);
      GemCartBuffer_CatEyeBuff__ctor(puVar1,status,(undefined *)0x0);
      return puVar1;
    case 0x10:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c934380);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x11:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c962c08);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x12:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9507d0);
      GemCartBuffer_PowerWaveChangeBuff__ctor(puVar1,lv,status,(undefined *)0x0);
      return puVar1;
    case 0x13:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9541e0);
      GemCartBuffer_PowerWaveChangeBuff__ctor(puVar1,lv,status,(undefined *)0x0);
      return puVar1;
    case 0x14:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c947f18);
      GemCartBuffer_PowerWaveChangeBuff__ctor(puVar1,lv,status,(undefined *)0x0);
      return puVar1;
    case 0x15:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c949068);
      GemCartBuffer_PowerWaveChangeBuff__ctor(puVar1,lv,status,(undefined *)0x0);
      return puVar1;
    case 0x16:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9482a8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x17:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95f998);
      GemCartBuffer_ClearAndSereneConventionalBuff__ctor(puVar1,(undefined *)0x0);
      return puVar1;
    case 0x18:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8fc0f0);
      GemCartBuffer_CoffeeBreakBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x19:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95a1b0);
      GemCartBuffer_CoffeeBreakBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x1a:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c927478);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x1b:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c91e008);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x1c:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c91e0d0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x1d:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8f4938);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x1e:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8f4a08);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x1f:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95f800);
      GemCartBuffer_CatEyeBuff__ctor(puVar1,status,(undefined *)0x0);
      return puVar1;
    case 0x20:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c93e2b0);
      GemCartBuffer_SavingTechniqueBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x21:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c955b10);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x22:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95b848);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x23:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c955028);
      GemCartBuffer_StartDashBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x24:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c940ab8);
      GemCartBuffer_BaskInTheSunBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x25:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c965a40);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x26:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c955bd8);
      GemCartBuffer_LastResistanceBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x27:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c93e228);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x28:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c93e370);
      GemCartBuffer_CatEyeBuff__ctor(puVar1,status,(undefined *)0x0);
      return puVar1;
    case 0x29:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c912800);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x2a:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c96a9e8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x2b:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c929e60);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x2c:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c904970);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x2d:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8ff168);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x2e:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c926490);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x2f:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c92b8b0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x30:
    case 0x31:
    case 0x33:
    case 0x34:
    case 0x3b:
    case 0x3c:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x4f:
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x5f:
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
      goto LAB_7ffe9a5b1859;
    case 0x32:
      uVar2 = uRam00007ffe9c93bef8;
      break;
    case 0x35:
      uVar2 = uRam00007ffe9c903408;
      break;
    case 0x36:
      uVar2 = uRam00007ffe9c9003d8;
      break;
    case 0x37:
      uVar2 = uRam00007ffe9c9044d8;
      break;
    case 0x38:
      uVar2 = uRam00007ffe9c955a40;
      break;
    case 0x39:
      uVar2 = uRam00007ffe9c957ee8;
      break;
    case 0x3a:
      uVar2 = uRam00007ffe9c968580;
      break;
    case 0x3d:
      uVar2 = uRam00007ffe9c9618e8;
      break;
    case 0x3e:
      uVar2 = uRam00007ffe9c956a30;
      break;
    case 0x3f:
      uVar2 = uRam00007ffe9c967ff0;
      break;
    case 0x45:
      uVar2 = uRam00007ffe9c9575e0;
      break;
    case 0x46:
      uVar2 = uRam00007ffe9c954a60;
      break;
    case 0x47:
      uVar2 = uRam00007ffe9c928df8;
      break;
    case 0x48:
      uVar2 = uRam00007ffe9c94e390;
      break;
    case 0x49:
      uVar2 = uRam00007ffe9c8fcf48;
      break;
    case 0x4a:
      uVar2 = uRam00007ffe9c92f428;
      break;
    case 0x4b:
      uVar2 = uRam00007ffe9c947fd8;
      break;
    case 0x4c:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c96ea68);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x4d:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8f4048);
      GemCartBuffer_EatingTooFastBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x4e:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c903ee0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x65:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c927c00);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x66:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c92e538);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x67:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c927220);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x68:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9083f0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x69:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95d688);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x6a:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95f738);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x6b:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c94cc18);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x6c:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c94f6f8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x6d:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c96e840);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x6e:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9150a0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x6f:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c905148);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x70:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c94fd58);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x71:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c904e08);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x72:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c958f20);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    default:
      switch(iVar3) {
      case 0xc9:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c96d8e8);
        GemCartBuffer_ClearAndSereneConventionalBuff__ctor(puVar1,(undefined *)0x0);
        return puVar1;
      case 0xca:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c950d30);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xcb:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9364f0);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xcc:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c912c10);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xcd:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95ea78);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xce:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95db50);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xcf:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9273b0);
        GemCartBuffer_PowerWaveChangeBuff__ctor(puVar1,lv,status,(undefined *)0x0);
        return puVar1;
      case 0xd0:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c946ec0);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xd1:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8f38f8);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xd2:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9316d8);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xd3:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8f0b80);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xd4:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8f0770);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xd5:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c930da8);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xd6:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c966d58);
        GemCartBuffer_ClearAndSereneConventionalBuff__ctor(puVar1,(undefined *)0x0);
        return puVar1;
      case 0xd7:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c966c00);
        GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
        return puVar1;
      case 0xd8:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c958b60);
        GemCartBuffer_ClearAndSereneConventionalBuff__ctor(puVar1,(undefined *)0x0);
        return puVar1;
      case 0xd9:
        puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c94f570);
        GemCartBuffer_ClearAndSereneConventionalBuff__ctor(puVar1,(undefined *)0x0);
        return puVar1;
      default:
        return (undefined *)0x0;
      }
    }
    goto code_r0x7ffe9a5b1118;
  }
  switch(iVar3) {
  case 0x12d:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95f5e0);
    GemCartBuffer_ClearAndSereneConventionalBuff__ctor(puVar1,(undefined *)0x0);
    return puVar1;
  case 0x12e:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c92d118);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x12f:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c94d300);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x130:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c929820);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x131:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c920bc8);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x132:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8ef660);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x133:
LAB_7ffe9a5b1859:
    return (undefined *)0x0;
  case 0x134:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95f5a0);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x135:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c958728);
    GemCartBuffer_ClearAndSereneConventionalBuff__ctor(puVar1,(undefined *)0x0);
    return puVar1;
  }
  switch(iVar3) {
  case 0x191:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9424c0);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x192:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c96f238);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x193:
    uVar2 = uRam00007ffe9c95e810;
    break;
  case 0x194:
    uVar2 = uRam00007ffe9c968f58;
    break;
  case 0x195:
    uVar2 = uRam00007ffe9c966bc0;
    break;
  case 0x196:
    goto LAB_7ffe9a5b1859;
  case 0x197:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95f448);
    GemCartBuffer_ClearAndSereneConventionalBuff__ctor(puVar1,(undefined *)0x0);
    return puVar1;
  case 0x198:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9423f8);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x199:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c963510);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  case 0x19a:
    puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c900308);
    GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
    return puVar1;
  default:
    switch(iVar3) {
    case 0x3e9:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c947048);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3ea:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c937040);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3eb:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c964ad8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3ec:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c936e00);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3ed:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c92bd00);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3ee:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c92e680);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3ef:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c928c68);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f0:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c929690);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f1:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95da40);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f2:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c965978);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f3:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c934550);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f4:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c934240);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f5:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c934488);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f6:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8fa1c8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f7:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c947c08);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f8:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c973748);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3f9:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8ff6d8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3fa:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95a418);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3fb:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c92cd40);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3fc:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c911ca0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3fd:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c943ec8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3fe:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c96d3d8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x3ff:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8ffb28);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x400:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9468a0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x401:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c92b310);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x402:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c928d30);
      GemCartBuffer_HealStockpileBuff__ctor(puVar1,lv,status,(undefined *)0x0);
      return puVar1;
    default:
      goto LAB_7ffe9a5b1859;
    case 0x404:
      uVar2 = uRam00007ffe9c9057c8;
      break;
    case 0x405:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c929d98);
      func_0x7ffe999c3920(puVar1,0);
      *(undefined2 *)(puVar1 + 0x14) = 1;
      return puVar1;
    case 0x406:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c909178);
      func_0x7ffe999c3920(puVar1,0);
      iVar3 = (3 - lv) * 100;
      if (iVar3 < 100) {
        iVar3 = 100;
      }
      *(int *)(puVar1 + 0x18) = iVar3;
      *(short *)(puVar1 + 0x14) = lv;
      return puVar1;
    case 0x407:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c903338);
      func_0x7ffe999c3920(puVar1,0);
      *(short *)(puVar1 + 0x14) = lv;
      if (DAT_7ffe9cad9e25 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c968830);
        DAT_7ffe9cad9e25 = '\x01';
      }
      fVar5 = (float)(int)lv * _DAT_7ffe9c049dc4;
      if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      dVar4 = (double)func_0x7ffe99997768((double)fVar5);
      *(int *)(puVar1 + 0x18) = (int)dVar4;
      return puVar1;
    case 0x40c:
      uVar2 = uRam00007ffe9c928b20;
      break;
    case 0x40d:
      uVar2 = uRam00007ffe9c94acf8;
      break;
    case 0x40e:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c904408);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x40f:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9581d0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x410:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95cc38);
      GemCartBuffer_ClearAndSereneConventionalBuff__ctor(puVar1,(undefined *)0x0);
      return puVar1;
    case 0x411:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c939f98);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x412:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95e348);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x413:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c935bc0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x414:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c94c4b0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x415:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c949d20);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x417:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95c908);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x418:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c96e6a0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x419:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c9129a0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x41a:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c8fc5d0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x41b:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c967088);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x41c:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c95e0a0);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x41d:
      puVar1 = (undefined *)func_0x7ffe99940040(uRam00007ffe9c94c2e8);
      GemCartBuffer_AccelBladeExtensionBuff__ctor(puVar1,lv,(undefined *)0x0);
      return puVar1;
    case 0x41e:
      uVar2 = uRam00007ffe9c927a70;
    }
  }
code_r0x7ffe9a5b1118:
  puVar1 = (undefined *)func_0x7ffe99940040(uVar2);
  func_0x7ffe999c3920(puVar1,0);
  *(short *)(puVar1 + 0x14) = lv;
  return puVar1;
}

