(function (root) {
  'use strict';
  var entries = Object.create(null);
  var aliases = Object.create(null);
  function register(id, config) {
    var key = String(id || '').toUpperCase();
    var entry = Object.freeze(Object.assign({ id:key, aliases:[], unit:'flat', aggregation:'sum', stage:'equipment', role:'notModeled', status:'notModeled', target:null, min:null, max:null }, config || {}, { id:key }));
    entries[key] = entry;
    [key].concat(entry.aliases || []).forEach(function (name) { aliases[String(name).toUpperCase().replace(/\s+/g, '')] = key; });
  }
  function calculated(id, target, config) { register(id, Object.assign({ target:target, role:'objective', status:'calculated' }, config || {})); }
  function utility(id, target, config) { register(id, Object.assign({ target:target, role:'hardConstraint', status:'utility' }, config || {})); }
  function preserved(id, config) { register(id, Object.assign({ role:'future', status:'notModeled' }, config || {})); }

  calculated('ATKP','atkP',{unit:'percent',aliases:['ATK%','ATK_P']}); calculated('ATK','atkF',{aliases:['ATK+']});
  calculated('MATKP','matkP',{unit:'percent',aliases:['MATK%','MATK_P']}); calculated('MATK','matkF',{aliases:['MATK+']});
  [['STR','str'],['DEX','dex'],['AGI','agi'],['INT','int'],['VIT','vit']].forEach(function (item) {
    calculated(item[0] + 'P', item[1] + 'P', {unit:'percent',aliases:[item[0] + '%',item[0] + '_P']});
    calculated(item[0], item[1] + 'F', {aliases:[item[0] + '+']});
  });
  calculated('CDMGP','cdmgP',{unit:'percent',aliases:['CDMG_P','CDMG%','CDMG_PCT']}); calculated('CDMG','cdmgF',{aliases:['CDMG+']});
  calculated('CRITP','critP',{unit:'percent',aliases:['CRIT_P','CRIT%']}); calculated('CRIT','critF',{aliases:['CRIT+']});
  calculated('SRW','srw',{unit:'percent',aliases:['근거리위력']}); calculated('LRW','lrw',{unit:'percent',aliases:['원거리위력']});
  calculated('UNSHEATHEP','unsheatheP',{unit:'percent',aliases:['발도위력%','발도공격%']}); calculated('UNSHEATHE','unsheatheF',{aliases:['발도위력','발도공격','발도위력+','발도공격+']});
  calculated('PHYS_PIERCE','physPierce',{unit:'percent',aliases:['물리관통']}); calculated('MAG_PIERCE','magPierce',{unit:'percent',aliases:['마법관통']});
  calculated('ELEM_P','elemP',{unit:'percent',aliases:['속성데미지','속성에유리']});
  calculated('ELEM_AWAKENING','elementAwakening',{unit:'boolean',aggregation:'or'}); calculated('MAGIC_ELEMENT','magicElement',{unit:'boolean',aggregation:'or'});
  calculated('DAMAGE_P','damageP',{unit:'percent',aliases:['DAMAGE%','스킬데미지']});
  calculated('WATKP','watkP',{unit:'percent',aliases:['무기ATK%']}); calculated('WATK','watkF',{aliases:['무기ATK+']});
  calculated('STABILITY','stability',{unit:'percent',aliases:['안정률']});
  utility('MAXHP','maxHpF',{aliases:['MAX_HP','최대HP']}); utility('MAXHPP','maxHpP',{unit:'percent',aliases:['MAXHP_P','MAX_HP_P','최대HP%']});
  utility('MAXMP','maxMpF',{aliases:['MAX_MP','최대MP']}); utility('AMPR','amprF',{aliases:['공격MP회복']}); utility('AMPRP','amprP',{unit:'percent',aliases:['AMPR_P','AMPR%','공격MP회복%']});
  utility('ASPD','aspdF'); utility('ASPD_P','aspdP',{unit:'percent',aliases:['ASPD%']}); utility('CSPD','cspdF',{role:'utility'}); utility('CSPD_P','cspdP',{unit:'percent',aliases:['CSPD%'],role:'utility'});
  utility('MOTIONSPEED','motionSpeed',{unit:'percent',aliases:['MOTION_SPEED','MS','행동속도'],role:'utility',max:50});
  utility('CAST_RED','castRed',{unit:'percent',aliases:['CAST_TIME','CHARGE_TIME','영창','시전시간','영창감소','시전감소'],role:'utility',max:100});
  ['STR','DEX','INT','AGI','VIT'].forEach(function (stat) { calculated('ATK_UP_' + stat,'atkUp' + stat,{unit:'percent'}); calculated('MATK_UP_' + stat,'matkUp' + stat,{unit:'percent'}); });
  ['ABS_ACC','ABS_DODGE','ACC','ACCP','AGGRO','AILMENT_RES','ANTICIPATE','AOE_RES','AREA_RES','AROUND_RES','AVOID_RATE','AVOID_RECHARGE','BARR_SPEED','BULLET_RES','CHARGE_RED','LINE_RED','DARK_RES','DEF','DEFP','DROP_RATE','EARTH_RES','EXP','FIRE_DMG','FIRE_RES','FLEE','FLEEP','FLOOR_RES','FRAC_BARR','GUARD_BREAK','GUARD_POWER','GUARD_RECHARGE','HP_REGEN','HP_REGENP','ITEM_CD','LIGHT_RES','MAG_BARR','MAG_PURSUIT','MAG_RES','MDEF','MDEFP','MP_REGEN','MP_REGENP','NEUTRAL_DMG','NEUTRAL_RES','PHYS_BARR','PHYS_PURSUIT','PHYS_RES','REFLECT','REVIVE_TIME','WATER_DMG','WATER_RES','WIND_DMG','WIND_RES','EARTH_DMG','LIGHT_DMG','DARK_DMG'].forEach(function (id) { if (!entries[id]) preserved(id); });
  aliases.DEF_P='DEFP'; aliases.MDEF_P='MDEFP'; aliases.HIT='ACC'; aliases.HIT_P='ACCP'; aliases.AVOID='FLEE'; aliases.AVOID_P='FLEEP';
  aliases.GUARD_RECOVERY='GUARD_RECHARGE'; aliases.AVOID_RECOVERY='AVOID_RECHARGE'; aliases.HPR_NONCOMBAT='HP_REGEN'; aliases.HPR_NONCOMBAT_P='HP_REGENP'; aliases.MPR_NONCOMBAT='MP_REGEN'; aliases.MPR_NONCOMBAT_P='MP_REGENP';
  aliases.AGGRO_P='AGGRO'; aliases.EXP_P='EXP'; aliases.HP_REGEN_P='HP_REGENP'; aliases.MP_REGEN_P='MP_REGENP';
  aliases.MAGIC_PIERCE='MAG_PIERCE'; aliases.MOTION_SPEED_P='MOTIONSPEED';

  function normalize(key) { return aliases[String(key || '').toUpperCase().replace(/\s+/g,'')] || null; }
  function get(key) { var id=normalize(key); return id ? entries[id] : null; }
  function apply(ctx,key,value) {
    var amount=Number(value); if(!ctx || !key || !Number.isFinite(amount)) return false;
    var definition=get(key);
    if(!definition) { if(!Array.isArray(ctx.statDiagnostics)) ctx.statDiagnostics=[]; if(!ctx.statDiagnostics.some(function(item){return item.code==='UNKNOWN_STAT'&&item.key===String(key);})) ctx.statDiagnostics.push({code:'UNKNOWN_STAT',key:String(key),message:'등록되지 않은 스탯 키입니다: '+key}); return false; }
    if(definition.target) { if(definition.aggregation==='or') ctx[definition.target]=Boolean(ctx[definition.target])||amount>0; else ctx[definition.target]=(Number(ctx[definition.target])||0)+amount; return true; }
    if(!ctx.preservedStats || typeof ctx.preservedStats!=='object') ctx.preservedStats={}; ctx.preservedStats[definition.id]=(Number(ctx.preservedStats[definition.id])||0)+amount; return true;
  }
  function collectCrystaKeys(list) { var found={}; (Array.isArray(list)?list:[]).forEach(function(item){Object.keys(item&&item.stats||{}).forEach(function(k){found[k]=true;});(item&&item.condStats||[]).forEach(function(c){Object.keys(c&&c.stats||{}).forEach(function(k){found[k]=true;});});}); return Object.keys(found).sort(); }
  function auditKeys(keys) { var result={total:(keys||[]).length,unknown:[],modeled:[],preserved:[]}; (keys||[]).forEach(function(key){var d=get(key);if(!d)result.unknown.push(key);else if(d.status==='notModeled')result.preserved.push(d.id);else result.modeled.push(d.id);}); Object.keys(result).forEach(function(k){if(Array.isArray(result[k]))result[k]=Array.from(new Set(result[k]));}); return result; }
  var api=Object.freeze({normalize:normalize,get:get,apply:apply,entries:function(){return Object.keys(entries).sort().map(function(id){return entries[id];});},collectCrystaKeys:collectCrystaKeys,auditKeys:auditKeys});
  if(typeof module==='object'&&module.exports) module.exports=api;
  if(root) root.ToramStatRegistry=api;
}(typeof window!=='undefined'?window:globalThis));
