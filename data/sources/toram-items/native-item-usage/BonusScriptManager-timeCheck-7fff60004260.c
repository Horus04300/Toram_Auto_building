
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte BonusScriptManager_timeCheck(undefined *self,byte updateTime,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  byte bVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  
  if (*(longlong *)(self + 0x20) != 0) {
    if (*(char *)(*(longlong *)(self + 0x20) + 0x40) == '\0') {
      return 1;
    }
    fVar6 = 0.0;
    if (updateTime != 0) {
      fVar5 = (float)FUN_7fff618b0ec0();
      lVar1 = *(longlong *)(self + 0x20);
      if (lVar1 == 0) goto LAB_7fff60004455;
      fVar6 = fVar5 - *(float *)(lVar1 + 0x34);
      *(float *)(lVar1 + 0x34) = fVar5;
    }
    lVar1 = *(longlong *)(self + 0x20);
    if (lVar1 != 0) {
      fVar5 = *(float *)(lVar1 + 0x44);
      if (0.0 < fVar5) {
        fVar6 = fVar5 - fVar6;
        *(float *)(lVar1 + 0x44) = fVar6;
        if (fVar6 <= 0.0) {
          *(undefined4 *)(lVar1 + 0x44) = 0;
        }
        else {
          fVar6 = 0.0;
        }
        if (*(longlong *)(self + 0x20) == 0) goto LAB_7fff60004455;
        if (0.0 < *(float *)(*(longlong *)(self + 0x20) + 0x44)) {
          return 0;
        }
      }
      else if (fVar5 < 0.0) {
        fVar6 = fVar6 + fVar5;
        *(undefined4 *)(lVar1 + 0x44) = 0;
      }
      lVar1 = *(longlong *)(self + 0x20);
      if (lVar1 != 0) {
        if ((0.0 < *(float *)(lVar1 + 0x4c)) &&
           (fVar5 = *(float *)(lVar1 + 0x4c) - fVar6, *(float *)(lVar1 + 0x4c) = fVar5, fVar5 <= 0.0
           )) {
          *(undefined4 *)(lVar1 + 0x4c) = 0;
        }
        lVar1 = *(longlong *)(self + 0x20);
        if (lVar1 != 0) {
          if (0.0 < *(float *)(lVar1 + 0x60)) {
            fVar6 = *(float *)(lVar1 + 0x60) - fVar6;
            *(float *)(lVar1 + 0x60) = fVar6;
            if (((fVar6 <= 0.0) &&
                (*(undefined4 *)(lVar1 + 0x68) = 1, 0.0 < *(float *)(lVar1 + 0x4c))) &&
               (*(char *)(lVar1 + 0x50) != '\0')) {
              *(float *)(lVar1 + 0x58) = (float)*(int *)(lVar1 + 0x54) + fVar6;
            }
            bVar3 = 1;
            if (0.0 < fVar6) {
              bVar3 = 0;
            }
          }
          else {
            if (*(char *)(lVar1 + 0x50) == '\0') {
              return 0;
            }
            bVar3 = 0;
            if (0.0 < *(float *)(lVar1 + 0x58)) {
              fVar6 = *(float *)(lVar1 + 0x58) - fVar6;
              *(float *)(lVar1 + 0x58) = fVar6;
              if (fVar6 <= 0.0) {
                *(undefined4 *)(lVar1 + 0x68) = 1;
                *(float *)(lVar1 + 0x58) = (float)*(int *)(lVar1 + 0x54) + fVar6;
                bVar3 = 1;
              }
            }
          }
          lVar1 = *(longlong *)(self + 0x20);
          if (lVar1 != 0) {
            if (*(char *)(lVar1 + 0x50) != '\0') {
              fVar6 = *(float *)(lVar1 + 0x58);
              if (fVar6 <= 0.0) {
                iVar4 = *(int *)(lVar1 + 0x68);
                do {
                  iVar4 = iVar4 + 1;
                  fVar6 = (float)*(int *)(lVar1 + 0x54) + fVar6;
                } while (fVar6 <= 0.0);
                *(float *)(lVar1 + 0x58) = fVar6;
                *(int *)(lVar1 + 0x68) = iVar4;
              }
              iVar4 = *(int *)(lVar1 + 0x68);
              if (*(int *)(lVar1 + 100) <= *(int *)(lVar1 + 0x68)) {
                iVar4 = *(int *)(lVar1 + 100);
              }
              *(int *)(lVar1 + 0x68) = iVar4;
            }
            return bVar3;
          }
        }
      }
    }
  }
LAB_7fff60004455:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  bVar3 = (*pcVar2)();
  return bVar3;
}

