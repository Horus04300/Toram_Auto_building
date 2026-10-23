(function (root) {
  'use strict';
  // Source: https://coryn.club/food.php (2026-09-11). Values are totals at each level.
  var basic = [2,4,6,8,10,14,18,22,26,30];
  var hundred = [6,12,18,24,30,44,58,72,86,100];
  var hp = [400,800,1200,1600,2000,2600,3200,3800,4400,5000];
  var resistance = [2,4,6,8,10,13,16,19,22,25];
  var recipes = [];
  function add(id, effect, names, key, values, percent, connected) {
    recipes.push(Object.freeze({ id:id, effect:effect, names:Object.freeze(names.split('|')), key:key,
      values:Object.freeze(values.slice()), percent:Boolean(percent), connected:Boolean(connected), group:key }));
  }
  add('STR','STR','Okaka Rice Ball','STR',basic,false,true);
  add('INT','INT','Umeboshi Rice Ball','INT',basic,false,true);
  add('VIT','VIT','Tuna Mayo Rice Ball','VIT',basic,false,true);
  add('AGI','AGI','Mentaiko Rice Ball','AGI',basic,false,true);
  add('DEX','DEX','Salmon Rice Ball','DEX',basic,false,true);
  add('ACC','Accuracy','Shoyu Ramen','ACC',hundred);
  add('FLEE','Dodge','Shio Ramen','FLEE',hundred);
  add('DEF','DEF','Tonkotsu Ramen','DEF',[20,40,60,80,100,140,180,220,260,300]);
  add('MDEF','MDEF','Miso Ramen','MDEF',[20,40,60,80,100,140,180,220,260,300]);
  add('MATK','MATK','Seafood Pizza','MATK',hundred,false,true);
  add('ATK','ATK','Pizza Diavola','ATK',hundred,false,true);
  add('WATK','Weapon ATK','Pizza Margherita','WATK',hundred,false,true);
  add('PHYS_RES','Physical Resistance','Beef Burger','PHYS_RES',[4,8,12,16,20,26,32,38,44,50],true);
  add('MAG_RES','Magic Resistance','Fish Burger','MAG_RES',[4,8,12,16,20,26,32,38,44,50],true);
  // User-approved single generic advantage; do not sum the seven elemental recipes.
  add('ELEM_P','속성에 유리','Bolognese|Genovese|Vongole|Carbonara|Naporitan|Squid Ink Pasta|Peperoncio','ELEM_P',[1,2,3,4,5,7,9,11,13,15],true,true);
  add('EXP','EXP Gain','Chocolate Parfait','EXP',[1,2,3,4,5,6,7,8,9,10],true);
  add('DROP_RATE','Drop Rate','Fruit Parfait','DROP_RATE',[1,2,3,4,5,6,7,8,9,10],true);
  add('WATER_RES','Water Resistance','Anchovy Toast','WATER_RES',resistance,true);
  add('WIND_RES','Wind Resistance','Cheese Toast','WIND_RES',resistance,true);
  add('EARTH_RES','Earth Resistance','Pudding Toast','EARTH_RES',resistance,true);
  add('FIRE_RES','Fire Resistance','Sunny Side Up Toast','FIRE_RES',resistance,true);
  add('LIGHT_RES','Light Resistance','Honey Toast','LIGHT_RES',resistance,true);
  add('DARK_RES','Dark Resistance','Garlic Toast','DARK_RES',resistance,true);
  add('NEUTRAL_RES','Neutral Resistance','Vanilla Toast','NEUTRAL_RES',resistance,true);
  add('PHYS_BARR','Physical Barrier','Chocolate Cake','PHYS_BARR',hp);
  add('MAG_BARR','Magic Barrier','Cheese Cake','MAG_BARR',hp);
  add('FRAC_BARR','Fractional Barrier','Pancake','FRAC_BARR',basic,true);
  add('CRIT','Critical Rate','Takoyaki','CRIT',basic,false,true);
  add('AMPR','Attack MP Recovery','Yakisoba','AMPR',basic,false,true);
  add('AGGRO','Aggro','Beef Stew','AGGRO',hundred,true);
  add('AGGRO_MINUS','-Aggro','White Stew','AGGRO',hundred.map(function (n) { return -n; }),true);
  add('MAXMP','Max MP','Ankake Fried Rice','MAXMP',[60,120,180,240,300,440,580,720,860,1000],false,true);
  add('MAXHP','Max HP','Golden Stir Fry','MAXHP',hp,false,true);
  function get(id) { return recipes.find(function (recipe) { return recipe.id === id; }) || null; }
  function normalize(slots) {
    var used = new Set();
    return Array.from({ length:5 }, function (_, index) {
      var slot = Array.isArray(slots) && slots[index], recipe = slot && get(slot.id);
      if (!recipe || used.has(recipe.group)) return null;
      used.add(recipe.group);
      var level = Number(slot.level);
      return { id:recipe.id, level:Number.isFinite(level) ? Math.max(1, Math.min(10, Math.floor(level))) : 10 };
    });
  }
  function options(slots) {
    return normalize(slots).filter(Boolean).reduce(function (result, slot) {
      var recipe = get(slot.id);
      if (recipe.connected) result.push({ key:recipe.key, value:recipe.values[slot.level - 1] });
      return result;
    }, []);
  }
  var api = Object.freeze({ recipes:Object.freeze(recipes), get:get, normalize:normalize, options:options });
  root.ToramFoodCatalog = api;
  if (typeof module === 'object' && module.exports) module.exports = api;
}(typeof window !== 'undefined' ? window : globalThis));
