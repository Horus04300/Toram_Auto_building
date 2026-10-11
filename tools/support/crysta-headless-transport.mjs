import { spawn } from 'node:child_process';
import { createInterface } from 'node:readline';

// Lazily launch inside the measured interval, then keep the same service for resumes.
export function createHeadlessTransport(binary) {
  let child, exited, failed, nextId = 0, stderr = '';
  const pending = new Map();
  const metadata = { transport:'stdio-json-lines', commands:{}, hardwareProfile:null };
  function fail(error) {
    failed = error;
    for (const entry of pending.values()) entry.reject(error);
    pending.clear();
  }
  function launch() {
    child = spawn(binary, [], { windowsHide:true, stdio:['pipe','pipe','pipe'] });
    exited = new Promise(resolve => child.once('close', resolve));
    child.on('error', fail);
    child.stdin.on('error', fail);
    child.stderr.on('data', data => { stderr = (stderr + data).slice(-16000); });
    child.on('close', code => {
      if (pending.size) fail(new Error(`Headless service exited (${code}): ${stderr}`));
    });
    createInterface({ input:child.stdout }).on('line', line => {
      try {
        const packet = JSON.parse(line), entry = pending.get(packet.id);
        if (!entry) throw new Error(`Unexpected response id ${packet.id}`);
        if (packet.type === 'progress') { entry.progress?.onmessage?.(packet.value); return; }
        pending.delete(packet.id);
        if (packet.type === 'error') entry.reject(new Error(packet.error));
        else if (packet.type === 'result') {
          if (entry.command === 'crysta_hardware_profile') metadata.hardwareProfile = packet.value;
          entry.resolve(packet.value);
        } else entry.reject(new Error(`Unexpected response type ${packet.type}`));
      } catch (error) { fail(error); child.kill(); }
    });
  }
  return {
    metadata,
    core:{
      Channel:class { onmessage = null; },
      invoke(command, args = {}) {
        return new Promise((resolve, reject) => {
          if (failed) { reject(failed); return; }
          if (!child) launch();
          const id = ++nextId;
          metadata.commands[command] = (metadata.commands[command] || 0) + 1;
          const { progress, ...wireArgs } = args;
          pending.set(id, { resolve, reject, command, progress });
          try { child.stdin.write(JSON.stringify({ id, command, args:wireArgs }) + '\n'); }
          catch (error) { fail(error); }
        });
      }
    },
    async close() {
      if (!child) return;
      child.stdin.end();
      const timer = setTimeout(() => child.kill(), 2000);
      try { await exited; } finally { clearTimeout(timer); }
    }
  };
}
