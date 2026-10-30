
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIPlayerStatusDetailPanel_CalcAvoidBreakerValue(undefined *thisObject,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  longlong lVar6;
  undefined *puVar7;
  int iVar8;
  float fVar9;
  float fVar10;
  longlong lStackX_8;
  
  if (DAT_7ffe9cadc4cb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92bfa0);
    DAT_7ffe9cadc4cb = '\x01';
  }
  plVar1 = *(longlong **)(thisObject + 0x70);
  iVar8 = 0;
  lStackX_8 = 0;
  if ((plVar1 != (longlong *)0x0) &&
     (lVar6 = (**(code **)(*plVar1 + 0x208))(plVar1,*(undefined8 *)(*plVar1 + 0x210)), lVar6 != 0))
  {
    cVar3 = FUN_7ffe9ab944b0(lVar6,0x90,&lStackX_8,_DAT_7ffe9c92bfa0);
    if (cVar3 != '\0') {
      if (lStackX_8 == 0) goto LAB_7ffe9a0907a8;
      iVar8 = (int)*(short *)(lStackX_8 + 0x10);
    }
    plVar1 = *(longlong **)(thisObject + 0x70);
    fVar9 = (float)iVar8;
    if ((plVar1 != (longlong *)0x0) &&
       (puVar7 = (undefined *)
                 (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
       puVar7 != (undefined *)0x0)) {
      bVar4 = GemCartBufferManager_ContainsBuffer(puVar7,0x46,(undefined *)0x0);
      if (bVar4 == 0) {
        return fVar9;
      }
      plVar1 = *(longlong **)(thisObject + 0x70);
      if ((plVar1 != (longlong *)0x0) &&
         (puVar7 = (undefined *)
                   (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
         puVar7 != (undefined *)0x0)) {
        iVar8 = GemCartBufferManager_GetBufferLevel(puVar7,0x46,(undefined *)0x0);
        if (iVar8 < 1) {
          return fVar9;
        }
        plVar1 = *(longlong **)(thisObject + 0x70);
        if ((plVar1 != (longlong *)0x0) &&
           (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
           lVar6 != 0)) {
          iVar5 = FUN_7ffe99c09050(lVar6,0);
          fVar10 = _DAT_7ffe9c049b18;
          if (iVar5 != 10) {
            return fVar9;
          }
          plVar1 = *(longlong **)(thisObject + 0x70);
          if ((plVar1 != (longlong *)0x0) &&
             (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
             lVar6 != 0)) {
            iVar5 = FUN_7ffe99c08f50(lVar6,0);
            if (iVar5 == 0x11) {
              fVar10 = _DAT_7ffe9c049b74;
            }
            return fVar9 + (float)(int)((float)iVar8 * fVar10);
          }
        }
      }
    }
  }
LAB_7ffe9a0907a8:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar9 = (float)(*pcVar2)();
  return fVar9;
}

