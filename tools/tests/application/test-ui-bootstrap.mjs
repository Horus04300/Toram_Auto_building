import assert from 'node:assert/strict';
const previous=Object.getOwnPropertyDescriptor(globalThis,'document');
Object.defineProperty(globalThis,'document',{configurable:true,get(){throw new Error('Module import must not initialize the DOM');}});
try {
  const first=await import('../../../web/src/ui/ui-bootstrap.js');
  const second=await import('../../../web/src/ui/ui-bootstrap.js');
  assert.equal(first,second,'ESM caches the calculator module');
  assert.equal(typeof first.initializeCalculatorUi,'function');
} finally {if(previous)Object.defineProperty(globalThis,'document',previous);else delete globalThis.document;}
console.log('UI bootstrap: PASS (import without DOM initialization, one cached module; explicit initialization is browser-verified)');
