
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MainPlayer_CalcItemDelay(undefined *self,float time,byte bonus,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  float fVar6;
  float fVar7;
  
  if (DAT_7ffe9cadaef6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f4048);
    DAT_7ffe9cadaef6 = '\x01';
  }
  if (bonus != 0) {
    plVar5 = *(longlong **)(self + 0xd8);
    if (plVar5 != (longlong *)0x0) {
      lVar4 = (**(code **)(*plVar5 + 0x208))(plVar5,*(undefined8 *)(*plVar5 + 0x210));
      if (lVar4 != 0) {
        cVar2 = FUN_7ffe9a51e210(lVar4,0x8c,0);
        fVar7 = time;
        if (cVar2 != '\0') {
          plVar5 = *(longlong **)(self + 0xd8);
          if (plVar5 == (longlong *)0x0) goto LAB_7ffe99cfbf14;
          lVar4 = (**(code **)(*plVar5 + 0x208))(plVar5,*(undefined8 *)(*plVar5 + 0x210));
          if (lVar4 == 0) goto LAB_7ffe99cfbf14;
          iVar3 = FUN_7ffe9a51e120(lVar4,0x8c,0);
          fVar6 = (_DAT_7ffe9c049b18 - ((float)iVar3 / _DAT_7ffe9c049ce4) / _DAT_7ffe9c049cfc) *
                  time;
          fVar7 = _DAT_7ffe9c049ce0;
          if (_DAT_7ffe9c049ce0 <= fVar6) {
            fVar7 = fVar6;
          }
        }
        plVar5 = *(longlong **)(self + 0xd8);
        if (plVar5 != (longlong *)0x0) {
          lVar4 = (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220));
          if (lVar4 != 0) {
            plVar5 = (longlong *)FUN_7ffe9a5b23a0(lVar4,0x4d,0);
            time = fVar7;
            if (plVar5 != (longlong *)0x0) {
              if (((*(byte *)(_DAT_7ffe9c8f4048 + 0x130) <= *(byte *)(*plVar5 + 0x130)) &&
                  (*(longlong *)
                    (*(longlong *)(*plVar5 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c8f4048 + 0x130) * 8) == _DAT_7ffe9c8f4048)) &&
                 ((char)plVar5[3] != '\0')) {
                iVar3 = FUN_7ffe9a5af330(plVar5,2);
                *(undefined1 *)(plVar5 + 3) = 0;
                time = fVar7 - (float)iVar3;
                if (fVar7 - (float)iVar3 <= 0.0) {
                  time = 0.0;
                }
              }
            }
            goto LAB_7ffe99cfbef4;
          }
        }
      }
    }
LAB_7ffe99cfbf14:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
LAB_7ffe99cfbef4:
  *(float *)(self + 0xa8) = time;
  *(float *)(self + 0xac) = time;
  return;
}

