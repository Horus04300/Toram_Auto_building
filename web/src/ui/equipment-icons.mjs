const icon = name => `assets/icons/equipment/${name}.png`;

export const EQUIPMENT_ICONS = Object.freeze(Object.fromEntries([
  'equipment','sword','greatsword','bow','bowgun','staff','device','knuckle','halberd','katana',
  'shield','dagger','arrow','scroll','armor','additional','special'
].map(name => [name,icon(name)])));

export const EQUIPMENT_ITEM_ICONS = Object.freeze(Object.fromEntries(Object.entries({
  8:'katana',9:'halberd',10:'sword',11:'greatsword',12:'bow',13:'bowgun',14:'staff',15:'device',
  16:'knuckle',17:'shield',18:'dagger',19:'arrow',20:'armor',21:'additional',22:'special',23:'scroll'
}).map(([type,name]) => [type,EQUIPMENT_ICONS[name]])));

export const EQUIPMENT_SLOT_ICONS = Object.freeze({mainWeapon:EQUIPMENT_ICONS.sword,subWeapon:EQUIPMENT_ICONS.shield,
  armor:EQUIPMENT_ICONS.armor,additional:EQUIPMENT_ICONS.additional,special:EQUIPMENT_ICONS.special});

export const CRYSTA_ICONS = Object.freeze({all:'assets/icons/crystas/empty.png',노말:'assets/icons/crystas/normal.png',
  무기:'assets/icons/crystas/weapon.png',방어구:'assets/icons/crystas/armor.png',추가:'assets/icons/crystas/additional.png',특수:'assets/icons/crystas/special.png'});

export function prependEquipmentIcon(element,src) {
  if (!src) return;
  const image = element.ownerDocument.createElement('img'); image.className = 'equipment-icon';
  image.src = src; image.alt = ''; image.width = image.height = 28; image.setAttribute('aria-hidden','true');
  element.prepend(image);
}
