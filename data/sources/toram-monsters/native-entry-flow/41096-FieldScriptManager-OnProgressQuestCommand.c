
/* WARNING: Removing unreachable block (ram,0x7ffe999c3920) */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FieldScriptManager_OnProgressQuestCommand
               (undefined *self,undefined *command,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  int iVar6;
  longlong lVar7;
  undefined8 unaff_RDI;
  
  if (*(undefined **)(self + 0x40) != (undefined *)0x0) {
    bVar3 = FieldScriptLoader_ReadByte(*(undefined **)(self + 0x40),(undefined *)0x0);
    if (*(undefined **)(self + 0x40) != (undefined *)0x0) {
      bVar4 = FieldScriptLoader_ReadByte(*(undefined **)(self + 0x40),(undefined *)0x0);
      if (*(undefined **)(self + 0x40) != (undefined *)0x0) {
        iVar6 = FieldScriptLoader_ReadInt(*(undefined **)(self + 0x40),bVar3 & 1,(undefined *)0x0);
        lVar1 = *(longlong *)(self + 0x40);
        if (*(longlong *)(self + 0x20) != 0) {
          lVar7 = FUN_7ffe9a480210(*(longlong *)(self + 0x20),0);
          if (lVar7 != 0) {
            cVar5 = FUN_7ffe9a5bb1b0(lVar7,bVar4 == 0,iVar6,0);
            if (lVar1 != 0) {
              if (DAT_7ffe9cae0533 == '\0') {
                FUN_7ffe9996d590(&DAT_7ffe9c91a918,0,cVar5 != '\0',0,unaff_RDI);
                DAT_7ffe9cae0533 = '\x01';
              }
              lVar1 = *(longlong *)(lVar1 + 0x30);
              if (lVar1 != 0) {
                if (*(int *)(lVar1 + 0x18) == 0) {
                  FUN_7ffe9996d790();
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
                *(uint *)(lVar1 + 0x20) = (uint)(cVar5 != '\0');
                return;
              }
              FUN_7ffe9996d7a0();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

