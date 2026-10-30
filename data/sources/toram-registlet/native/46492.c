
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RegistletTextManagerData_set_BaseValue(undefined *self,int value,undefined *methodInfo)

{
  *(int *)(self + 0x28) = value;
  return;
}

