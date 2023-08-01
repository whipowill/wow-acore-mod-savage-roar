# Savage Roar

An AzerothCore module for giving Feral Druids the love they have long deserved.

While all the private servers are infested w/ over-powered Paladins, those of us who actually play a different class continue to get shafted by 20 years of developer blindness.

Nobody cares about imbalance when everybody plays the same class.

This module seeks to rectify that mistake on my private server by giving Feral Druids a passive [Savage Roar](https://www.wowhead.com/wotlk/spell=52610/savage-roar) buff while in Cat or Bear form, granting a totally legit and balancing +30% increase to damage.

This is my first attempt at creating a module.

## Methodology

This module uses [55Honey's ZoneDebuff](https://github.com/55Honey/Acore_ZoneDebuff/blob/master/zoneDebuff.lua) technique to apply the buff to Feral Druids.  His custom auras, included in this module's MySQL file, can enable a variety of buffs/debuffs:

```
// use CastCustomSpell() to apply an aura w/ required params
// player->CastCustomSpell(player, spellID, &param1, &param2, &param3, true, NULL, NULL, player->GetGUID());
// When you pass the params be sure to use the "&" in front of the var name.
// The param value is a range from -100 to 100+, and represents a percentage change from normal.

uint32_t HpAura= 89501;
player->CastCustomSpell(player, HpAura, &hpModifier, NULL, NULL, true, NULL, NULL, player->GetGUID());

uint32_t DamageDoneTakenAura = 89502;
player->CastCustomSpell(player, DamageDoneTakenAura, &DamageTakenModifier, &DamageDoneModifier, NULL, true, NULL, NULL, player->GetGUID());

uint32_t BaseStatAPAura = 89503;
player->CastCustomSpell(player, BaseStatAPAura, &BaseStatModifier, &MeleeAPModifier, &RangedAPModifier, true, NULL, NULL, player->GetGUID());

uint32_t RageFromDamageAura = 89504;
player->CastCustomSpell(player, RageFromDamageAura, &RageFromDamageModifier, NULL, NULL, true, NULL, NULL, player->GetGUID());

uint32_t AbsorbAura = 89505;
player->CastCustomSpell(player, AbsorbAura, &AbsorbModifier, NULL, NULL, true, NULL, NULL, player->GetGUID());

uint32_t HealingDoneAura = 89506;
player->CastCustomSpell(player, HealingDoneAura, &HealingDoneModifier, NULL, NULL, true, NULL, NULL, player->GetGUID());

uint32_t PhysicalDamageTakenAura = 89507;
player->CastCustomSpell(player, PhysicalDamageTakenAura, &PhysicalDamageTakenModifier, NULL, NULL, true, NULL, NULL, player->GetGUID());
```

## Testing

Unfortunately, there is no UI icon or combat log to tell you the mod is installed and working.  The way I tested this was I set the config file to take no damage, or to deal no damage, and looked to see what happened in combat.

It all worked perfectly.

Some of these buffs, such as the ``DamageDoneTakenAura`` which I use in this mod, are reflected in your character stats screen.  So in the case of this mod, you can see in Cat or Bear form a 1.30 multiplier to your melee dmg.

If you feel like something is wrong, it could be the custom auras didn't actually get imported into the ``acore_world`` database.  You can check if they did with this query:

```
SELECT * FROM spell_dbc WHERE ID=89501
```

If this is a problem (due to confusion and changes to how modules are supposed to automatically import MySQL files), you can patch the database manaully like so:

```
$ mysql -uroot -proot acore_world < /path/to/modules/wow-acore-mod-druid-buff/data/sql/db-world/druidbuff_01_addauras.sql
```

## Credits

- ChatGPT
- 55Honey

## External Links

- [AzerothCore](https://github.com/azerothcore/azerothcore-wotlk)
- [ZoneDebuff](https://github.com/55Honey/Acore_ZoneDebuff/blob/master/zoneDebuff.lua)