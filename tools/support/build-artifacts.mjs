import {readFile,writeFile,mkdir,readdir,unlink,rmdir,lstat,realpath} from 'node:fs/promises';
import {resolve,relative,dirname,sep} from 'node:path';

async function directory(path) {
  try {
    if(!(await lstat(path)).isDirectory()||await realpath(path)!==path) throw new Error('Artifact directory must be real: '+path);
  } catch(error) {
    if(error.code!=='ENOENT') throw error;
    await directory(dirname(path));await mkdir(path);
  }
}
export async function artifactFiles(root) {
  root=resolve(root);
  if(await realpath(root)!==root) throw new Error('Artifact directory must be real: '+root);
  const files=new Set();
  for(const entry of await readdir(root,{recursive:true,withFileTypes:true})) {
    if(entry.isSymbolicLink()) throw new Error('Artifact must not be a symlink: '+entry.name);
    if(entry.isFile()) files.add(relative(root,resolve(entry.parentPath,entry.name)).split(sep).join('/'));
  }
  return files;
}

// Compare contents and repair outputs; prune only this verified generated directory.
export async function syncArtifacts(root,files,content) {
  root=resolve(root);await directory(root);
  let written=0;
  for(const path of files) {
    const output=resolve(root,path);
    if(!output.startsWith(root+sep)||relative(root,output).split(sep).join('/')!==path) throw new Error('Invalid artifact path: '+path);
    await directory(dirname(output));
    try {if(!(await lstat(output)).isFile()) throw new Error('Artifact target must be a regular file: '+output);}
    catch(error) {if(error.code!=='ENOENT') throw error;}
    const bytes=Buffer.from(await content(path));
    const previous=await readFile(output).catch(error=>{if(error.code!=='ENOENT') throw error;return null;});
    if(!previous?.equals(bytes)) {await writeFile(output,bytes);written++;}
  }
  async function prune(path) {
    for(const entry of await readdir(path,{withFileTypes:true})) {
      const target=resolve(path,entry.name);
      if(entry.isSymbolicLink()) throw new Error('Artifact must not be a symlink: '+target);
      if(entry.isDirectory()) {await prune(target);if(!(await readdir(target)).length) await rmdir(target);}
      else if(entry.isFile()&&!files.has(relative(root,target).split(sep).join('/'))) await unlink(target);
    }
  }
  await prune(root);return written;
}
