# Savage Roar

An AzerothCore module for giving Druids the love they have long deserved.

While all the private servers are infested w/ over-powered Paladins, those of us who actually play a different class continue to get shafted by 20 years of developer blindness.

Nobody cares about imbalance when everybody plays the same class.

This module seeks to rectify that mistake on my private server by giving Druids a passive [Savage Roar](https://www.wowhead.com/wotlk/spell=52610/savage-roar) buff while in Cat or Bear form, granting a totally legit and balancing +30% increase to damage.

This is my first attempt at creating a module.

Basically, this provides a config to adjust the damage taken and damage dealt while in Cat or Bear form.  This module can easily be modified to buff or debuff any class, but I'm only interested in Feral Druid.

## Methodology

There are several methods for how to do this, and each involves adding an aura to the player that effects their damage.

The problem is you either have to use an aura that already exists in the game, or you have to create a new one.  If you create a new one, there is no chance that the aura will have any UI indication of it's presence, as the client won't have that aura in it's records.

Here are the 3 aura-adding methods I found, recorded here for my reference:

```
// if the aura has no requirements
player->AddAura(spellID, player);

// if the aura has some requirements, you can override
player->CastSpell(player, spellID, true); // flag true to pass requirements

// or just use Honey55's custom auras
player->CastCustomSpell(player, DamageDoneTakenSpell, &param1, &param2, &param3, true, NULL, NULL, player->GetGUID());

// When you use CastCustomSpell() you can pass up to 3 params.
// These are the params to pass for each of Honey55's auras:
// https://github.com/55Honey/Acore_ZoneDebuff/blob/master/zoneDebuff.lua
//
// uint32_t HpAuraSpell = 89501;
// uint32_t DamageDoneTakenSpell = 89502;
// uint32_t BaseStatAPSpell = 89503;
// uint32_t RageFromDamageSpell = 89504;
// uint32_t AbsorbSpell = 89505;
// uint32_t HealingDoneSpell = 89506;
// uint32_t PhysicalDamageTakenSpell = 89507;
//
// BaseStatAPSpell: param1=BaseStatModifier, param2=MeleeAPModifier, param3=RangedAPModifier
// DamageDoneTakenSpell: param1=DamageTaken, param2=DamageDoneModifier
// HpAuraSpell: param1=hpModifier
// RageFromDamageSpell: param1=RageFromDamageModifier
// AbsorbSpell: param1=AbsorbModifier
// HealingDoneSpell: param1=HealingDoneModifier
// PhysicalDamageTakenSpell: param1=PhysicalDamageTakenModifier
//
// When you pass the value, be sure to use the & in front of the var name.
// The param value is a range from -100 to 100, and represents a percentage change from normal.
```

This module uses [Honey55's ZoneDebuff](https://github.com/55Honey/Acore_ZoneDebuff/blob/master/zoneDebuff.lua) technique to apply the buff to Druids.

## Testing

Unfortunately, there is no UI icon or combat log to tell you the mod is installed and working.  The way I tested this was I set the config file to take no damage, or to deal no damage, and looked to see what happened in combat.  It all worked perfectly.

Also, if you feel like something is wrong, it could be the custom auras didn't actually get imported into the ``acore_world`` database.  You can check if they did here:

```
SELECT * FROM spell_dbc WHERE ID=89501
```

If this is a problem (due to confusion and changes to how modules are supposed to automatically import MySQL files), you can patch the database manaully like so:

```
$ mysql -uroot -proot acore_world < /path/to/modules/wow-acore-mod-druid-buff/data/sql/db-world/druidbuff_01_addauras.sql
```

## Credits

- ChatGPT
- Honey55

## External Links

- [AzerothCore](https://github.com/azerothcore/azerothcore-wotlk)
- [ZoneDebuff](https://github.com/55Honey/Acore_ZoneDebuff/blob/master/zoneDebuff.lua)