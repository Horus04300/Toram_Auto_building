export function createBookmarkButton(documentRef,{label,icon,active = false,points,onClick}) {
  const button = documentRef.createElement('button'); button.type = 'button';
  button.className = 'skill-bookmark-button skill-tree-button' + (active ? ' active' : '');
  button.setAttribute('aria-pressed',String(active)); button.title = label;
  if (icon) {const image = documentRef.createElement('img'); image.src = encodeURI(icon); image.alt = ''; button.append(image);}
  const info = documentRef.createElement('span'); info.className = 'bookmark-info';
  const text = documentRef.createElement('span'); text.className = 'bookmark-label'; text.textContent = label; info.append(text);
  if (points !== undefined) {const detail = documentRef.createElement('span'); detail.className = 'bookmark-points'; detail.textContent = points; info.append(detail);}
  button.append(info); button.addEventListener('click',onClick); return button;
}
