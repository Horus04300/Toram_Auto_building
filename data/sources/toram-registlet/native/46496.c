
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RegistletTextManagerData__ctor
               (undefined *self,undefined *name,undefined *description,int value,
               undefined *methodInfo)

{
  func_0x7ffe999c3920(self,0);
  *(undefined **)(self + 0x18) = name;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 0x20) = description;
  il2cpp_write_barrier_0();
  *(int *)(self + 0x28) = value;
  return;
}

