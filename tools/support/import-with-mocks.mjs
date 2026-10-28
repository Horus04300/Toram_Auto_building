import {registerHooks} from 'node:module';

// Unit tests replace imported collaborators while executing the actual ESM source.
let sequence=0;
export async function importWithMocks(url,mocks) {
  const id=++sequence, key=`__toramModuleTest${id}`;
  globalThis[key]=mocks;
  const hook=registerHooks({resolve(specifier,context,next) {
    const match=Object.keys(mocks).find(path=>specifier.endsWith(path));
    if(!match) return next(specifier,context);
    const source=Object.keys(mocks[match]).map(name=>`export const ${name}=globalThis[${JSON.stringify(key)}][${JSON.stringify(match)}][${JSON.stringify(name)}];`).join('\n');
    return {url:'data:text/javascript,'+encodeURIComponent(source),shortCircuit:true};
  }});
  try {
    const target=new URL(url); target.searchParams.set('unit',id);
    return await import(target.href);
  } finally {hook.deregister(); delete globalThis[key];}
}
