
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIPlayerStatusDetailPanel_CalcGuardBreakerValue(undefined *thisObject,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  longlong lVar6;
  undefined *puVar7;
  ulonglong uVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  longlong lStackX_8;
  
  if (DAT_7ffe9cadc4cc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92c1e0);
    DAT_7ffe9cadc4cc = '\x01';
  }
  plVar1 = *(longlong **)(thisObject + 0x70);
  iVar9 = 0;
  lStackX_8 = 0;
  if ((plVar1 != (longlong *)0x0) &&
     (lVar6 = (**(code **)(*plVar1 + 0x208))(plVar1,*(undefined8 *)(*plVar1 + 0x210)), lVar6 != 0))
  {
    cVar3 = FUN_7ffe9ab944b0(lVar6,0x91,&lStackX_8,_DAT_7ffe9c92c1e0);
    if (cVar3 != '\0') {
      if (lStackX_8 == 0) goto LAB_7ffe9a090b99;
      iVar9 = (int)*(short *)(lStackX_8 + 0x10);
    }
    plVar1 = *(longlong **)(thisObject + 0x70);
    fVar10 = (float)iVar9;
    if ((plVar1 != (longlong *)0x0) &&
       (puVar7 = (undefined *)
                 (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
       puVar7 != (undefined *)0x0)) {
      bVar4 = GemCartBufferManager_ContainsBuffer(puVar7,0x48,(undefined *)0x0);
      if (bVar4 == 0) {
        return fVar10;
      }
      plVar1 = *(longlong **)(thisObject + 0x70);
      if ((plVar1 != (longlong *)0x0) &&
         (puVar7 = (undefined *)
                   (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
         puVar7 != (undefined *)0x0)) {
        iVar9 = GemCartBufferManager_GetBufferLevel(puVar7,0x48,(undefined *)0x0);
        if (iVar9 < 1) {
          return fVar10;
        }
        plVar1 = *(longlong **)(thisObject + 0x70);
        if ((plVar1 != (longlong *)0x0) &&
           (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
           lVar6 != 0)) {
          uVar8 = FUN_7ffe99c09050(lVar6,0);
          fVar11 = _DAT_7ffe9c049b18;
          if ((uVar8 & 0xffffffef) != 0) {
            return fVar10;
          }
          plVar1 = *(longlong **)(thisObject + 0x70);
          if ((plVar1 != (longlong *)0x0) &&
             (lVar6 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
             lVar6 != 0)) {
            iVar5 = FUN_7ffe99c08f50(lVar6,0);
            if (iVar5 == 0) {
              fVar11 = _DAT_7ffe9c049b74;
            }
            return fVar10 + (float)(int)((float)iVar9 * fVar11);
          }
        }
      }
    }
  }
LAB_7ffe9a090b99:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar10 = (float)(*pcVar2)();
  return fVar10;
}

