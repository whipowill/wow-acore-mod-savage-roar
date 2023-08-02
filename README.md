# Savage Roar

An AzerothCore module for giving Feral Druids the love they have long deserved.

While all the private servers are infested w/ over-powered Paladins, those of us who actually play a different class continue to get shafted by 20 years of developer blindness.

Nobody cares about imbalance when everybody plays the same class.

This module seeks to rectify that mistake on my private server by giving Feral Druids a passive [Savage Roar](https://www.wowhead.com/wotlk/spell=52610/savage-roar) buff while in Cat or Bear form, granting a totally legit and balancing +30% increase to damage.

This is my first attempt at creating a module.

## Methodology

This module uses [55Honey's ZoneDebuff](https://github.com/55Honey/Acore_ZoneDebuff/blob/master/zoneDebuff.lua) technique to apply the buff to Feral Druids.  His custom auras, included in this module's MySQL file, can enable a variety of buffs/debuffs.

## Testing

Unfortunately, there is no UI icon or combat log to tell you the mod is installed and working.  The way I tested this was I set the config file to take no damage, or to deal no damage, and looked to see what happened.

It all worked perfectly.

I later discovered that the ``DamageDoneTakenAura`` is reflected in your character stats screen, so you can see in Cat or Bear form a 1.30 multiplier to your melee dmg.

## Credits

- ChatGPT
- 55Honey

## External Links

- [AzerothCore](https://github.com/azerothcore/azerothcore-wotlk)
- [ZoneDebuff](https://github.com/55Honey/Acore_ZoneDebuff/blob/master/zoneDebuff.lua)
- [NerfHerder](https://github.com/whipowill/wow-acore-mod-nerf-herder)