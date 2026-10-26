const tabs = { builds:'내 빌드', items:'내 아이템', favorites:'즐겨찾기' };

export function createAccountUi(documentRef, account) {
  const root = documentRef.defaultView;
  const launcher = documentRef.getElementById('appAccountButton');
  const dialog = documentRef.createElement('dialog');
  dialog.className = 'account-dialog';
  dialog.setAttribute('aria-labelledby', 'accountTitle');
  dialog.innerHTML = `
    <header class="account-header"><h2 id="accountTitle">계정</h2><button type="button" class="account-close" aria-label="계정 닫기">×</button></header>
    <div class="account-guest">
      <div class="account-avatar" aria-hidden="true"><svg viewBox="0 0 24 24" width="28" height="28" fill="none" stroke="currentColor" stroke-width="1.6"><circle cx="12" cy="8" r="4"/><path d="M4 21v-2a8 8 0 0 1 16 0v2"/></svg></div>
      <h3>내 세팅을 어디서나</h3>
      <button type="button" class="google-login"><svg width="20" height="20" viewBox="0 0 48 48" aria-hidden="true"><path fill="#EA4335" d="M24 9.5c3.54 0 6.71 1.22 9.21 3.6l6.85-6.85C35.9 2.38 30.47 0 24 0 14.62 0 6.51 5.38 2.56 13.22l7.98 6.19C12.43 13.72 17.74 9.5 24 9.5Z"/><path fill="#4285F4" d="M46.98 24.55c0-1.57-.15-3.09-.38-4.55H24v9.02h12.94c-.58 2.96-2.26 5.48-4.78 7.18l7.73 6C44.4 38.03 46.98 31.87 46.98 24.55Z"/><path fill="#FBBC05" d="M10.53 28.59A14.41 14.41 0 0 1 9.75 24c0-1.59.28-3.13.76-4.59l-7.98-6.19A23.87 23.87 0 0 0 0 24c0 3.87.93 7.53 2.56 10.78l7.97-6.19Z"/><path fill="#34A853" d="M24 48c6.48 0 11.93-2.13 15.91-5.8l-7.73-6c-2.15 1.45-4.92 2.3-8.18 2.3-6.26 0-11.57-4.22-13.47-9.91l-7.98 6.19C6.51 42.62 14.62 48 24 48Z"/></svg><span>구글로 로그인</span></button>
      <div class="account-benefits"><span>내 빌드</span><span>내 아이템</span><span>즐겨찾기</span></div>
    </div>
    <div class="account-member" hidden>
      <form class="account-profile"><label>닉네임<input name="nickname" maxlength="40" required autocomplete="nickname"></label><button type="submit">변경</button><button type="button" class="account-logout">로그아웃</button></form>
      <div class="account-tabs" role="tablist" aria-label="계정 보관함">${Object.entries(tabs).map(([id, name]) => `<button type="button" id="accountTab-${id}" role="tab" aria-controls="accountPanel" data-kind="${id}" aria-selected="${id === 'builds'}" tabindex="${id === 'builds' ? '0' : '-1'}">${name}</button>`).join('')}</div>
      <section id="accountPanel" role="tabpanel" aria-labelledby="accountTab-builds">
        <form class="account-save-form"><label>저장 이름<input name="name" placeholder="예: 마법사 빌드" maxlength="80" required></label><label class="account-slot" hidden>장비 부위<select name="slot">${Object.entries(account.slots).map(([id, name]) => `<option value="${id}">${name}</option>`).join('')}</select></label><button type="submit" class="account-primary">현재 빌드 저장</button></form>
        <ul class="account-records" aria-label="저장 목록"></ul><p class="account-empty" hidden>아직 저장한 빌드가 없어요.</p>
      </section>
    </div>
    <p class="account-status" role="status" aria-live="polite"></p><button type="button" class="account-retry" hidden>다시 연결</button>`;
  const find = selector => dialog.querySelector(selector);
  const guest = find('.account-guest'), member = find('.account-member'), status = find('.account-status');
  const loginButton = find('.google-login'), saveForm = find('.account-save-form'), profile = find('.account-profile');
  const list = find('.account-records'), empty = find('.account-empty');
  let kind = 'builds', generation = 0, busy = false, bound = false;
  function message(text = '', error = false) { status.textContent = text; status.classList.toggle('is-error', error); }
  function setMember(user) {
    generation++;
    list.replaceChildren(); empty.hidden = true;
    member.hidden = !user; guest.hidden = Boolean(user);
    profile.elements.nickname.value = user?.nickname || '';
    launcher.classList.toggle('is-signed-in', Boolean(user));
    launcher.setAttribute('aria-label', user ? user.nickname + ' 계정 열기' : '계정 열기');
  }
  async function run(work) {
    if (busy) return;
    busy = true;
    dialog.setAttribute('aria-busy', 'true');
    dialog.querySelectorAll('button:not(.account-close), input, select').forEach(node => { node.disabled = true; });
    message();
    try { await work(); }
    catch (error) {
      if (error.status === 401) setMember(null);
      if (error.name !== 'AbortError') message(error.message, true);
    } finally {
      busy = false;
      dialog.removeAttribute('aria-busy');
      dialog.querySelectorAll('button, input, select').forEach(node => { node.disabled = false; });
    }
  }
  async function refresh() {
    const current = ++generation, selected = kind;
    const records = await account.list(selected);
    if (current !== generation || !dialog.open) return;
    list.replaceChildren();
    empty.textContent = `아직 저장한 ${selected === 'builds' ? '빌드가' : selected === 'items' ? '아이템이' : '즐겨찾기가'} 없어요.`;
    empty.hidden = records.length > 0;
    records.forEach(record => {
      const row = documentRef.createElement('li'), description = documentRef.createElement('div');
      const name = documentRef.createElement('strong'), date = documentRef.createElement('small');
      name.textContent = record.name;
      date.textContent = new Date(record.updatedAt).toLocaleString('ko-KR');
      description.append(name, date);
      const load = documentRef.createElement('button'); load.type = 'button'; load.textContent = '불러오기';
      load.setAttribute('aria-label', record.name + ' 불러오기');
      load.addEventListener('click', () => run(async () => {
        if (!root.confirm('현재 ' + (selected === 'builds' ? '세팅을' : '장비를') + ' “' + record.name + '”' + (selected === 'builds' ? ' 빌드로' : ' 아이템으로') + ' 바꿀까요?')) return;
        await account.load(selected, record.id); message('불러왔습니다.');
      }));
      const remove = documentRef.createElement('button'); remove.type = 'button'; remove.textContent = '삭제'; remove.className = 'account-delete';
      remove.setAttribute('aria-label', record.name + ' 삭제');
      remove.addEventListener('click', () => run(async () => {
        if (!root.confirm('“' + record.name + '”을 계정에서 삭제할까요?')) return;
        await account.remove(selected, record); await refresh(); message('삭제했습니다.');
      }));
      row.append(description, load, remove); list.append(row);
    });
  }
  function selectTab(button) {
    kind = button.dataset.kind;
    dialog.querySelectorAll('[role="tab"]').forEach(tab => { tab.setAttribute('aria-selected', String(tab === button)); tab.tabIndex = tab === button ? 0 : -1; });
    find('#accountPanel').setAttribute('aria-labelledby', button.id);
    find('.account-slot').hidden = kind === 'builds';
    find('.account-primary').textContent = kind === 'builds' ? '현재 빌드 저장' : kind === 'items' ? '선택 부위 저장' : '선택 아이템 즐겨찾기';
    saveForm.elements.name.placeholder = kind === 'builds' ? '예: 마법사 빌드' : '예: 내 지팡이';
    return refresh();
  }
  async function connect() {
    find('.account-retry').hidden = true;
    setMember(null); message('계정을 확인하고 있습니다.');
    try {
      const session = await account.session();
      setMember(session.user);
      if (session.user) { await selectTab(find('#accountTab-builds')); message(); }
      else message(session.configured ? '' : '계정 서버 연결을 준비 중입니다. 로컬 저장은 계속 사용할 수 있습니다.');
    } catch (error) { find('.account-retry').hidden = false; throw error; }
  }
  return { bind() {
    if (bound) return;
    bound = true;
    documentRef.body.append(dialog);
    launcher.addEventListener('click', () => { dialog.showModal(); run(connect); });
    find('.account-close').addEventListener('click', () => dialog.close());
    dialog.addEventListener('click', event => {
      const rect = dialog.getBoundingClientRect();
      if (event.target === dialog && (event.clientX < rect.left || event.clientX > rect.right || event.clientY < rect.top || event.clientY > rect.bottom)) dialog.close();
    });
    dialog.addEventListener('close', () => { generation++; account.cancelLogin(); launcher.focus(); });
    find('.account-retry').addEventListener('click', () => run(connect));
    loginButton.addEventListener('click', () => run(async () => { message('브라우저에서 Google 로그인을 완료해 주세요.'); await account.login(); if (dialog.open) await connect(); }));
    find('.account-logout').addEventListener('click', () => run(async () => { await account.logout(); setMember(null); message('로그아웃했습니다.'); }));
    profile.addEventListener('submit', event => { event.preventDefault(); const nickname = profile.elements.nickname.value; run(async () => {
      const user = await account.nickname(nickname); setMember(user); await refresh(); message('닉네임을 변경했습니다.');
    }); });
    saveForm.addEventListener('submit', event => { event.preventDefault(); const name = saveForm.elements.name.value, slot = saveForm.elements.slot.value; run(async () => {
      await account.save(kind, name, slot); await refresh(); message('계정에 저장했습니다.');
    }); });
    const buttons = Array.from(dialog.querySelectorAll('[role="tab"]'));
    buttons.forEach((button, index) => {
      button.addEventListener('click', () => run(() => selectTab(button)));
      button.addEventListener('keydown', event => {
        const next = event.key === 'ArrowRight' ? (index + 1) % buttons.length : event.key === 'ArrowLeft' ? (index + buttons.length - 1) % buttons.length : event.key === 'Home' ? 0 : event.key === 'End' ? buttons.length - 1 : null;
        if (next === null || busy) return;
        event.preventDefault(); buttons[next].focus(); run(() => selectTab(buttons[next]));
      });
    });
    const url = new URL(root.location.href);
    if (url.searchParams.get('account') === 'connected') {
      url.searchParams.delete('account');
      root.history.replaceState(null, '', url.href);
      launcher.click();
    }
  } };
}
