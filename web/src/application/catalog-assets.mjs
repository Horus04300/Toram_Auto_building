// One catalog session shares successful reads; failed requests are retryable.
export function createCatalogReader(manifestUrl,fetcher,decode) {
  const base=new URL('.',manifestUrl), pending=new Map();
  function read(path,expected) {
    const url=new URL(path,base);
    if(url.origin!==base.origin||!url.href.startsWith(base.href)) throw new Error('Catalog asset escapes its catalog.');
    if(!pending.has(path)) {
      const request=Promise.resolve().then(()=>fetcher(url)).then(response=>decode(response,path,expected))
        .catch(error=>{if(pending.get(path)===request) pending.delete(path);throw error;});
      pending.set(path,request);
    }
    return pending.get(path);
  }
  return Object.freeze({read,forget:path=>pending.delete(path)});
}
