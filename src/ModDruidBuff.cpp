#include "ModDruidBuff.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Unit.h"
#include "Config.h"

class DruidBuff : public PlayerScript
{
public:
    DruidBuff() : PlayerScript("DruidBuff") {}

    void OnUpdate(Player* player, uint32 p_time)
    {
        int is_enabled = sConfigMgr->GetOption<int>("DruidBuff.Enable", 0);

        if (is_enabled)
        {
            if (player)
            {
                Unit* unit = static_cast<Unit*>(player);

                // custom spell ids (taken from Honey55's ZoneBuff codebase)
                // https://github.com/55Honey/Acore_ZoneDebuff/blob/master/zoneDebuff.lua
                uint32_t HpAuraSpell = 89501;
                uint32_t DamageDoneTakenSpell = 89502; // <-- only one I'm using atm
                uint32_t BaseStatAPSpell = 89503;
                uint32_t RageFromDamageSpell = 89504;
                uint32_t AbsorbSpell = 89505;
                uint32_t HealingDoneSpell = 89506;
                uint32_t PhysicalDamageTakenSpell = 89507;

                // what are the custom values
                uint32_t dmg_taken = 0; // -30 would decrease, 0 would nochange, 30 would increase
                uint32_t dmg_done = 30; // -30 would decrease, 0 would nochange, 30 would increase

                if (player->getClass() == CLASS_DRUID)
                {
                    uint32_t aura_cat_form = 768;
                    uint32_t aura_bear_form = 5487;
                    uint32_t aura_dire_bear_form = 9634;

                    if (player->HasAura(aura_cat_form) || player->HasAura(aura_bear_form) || player->HasAura(aura_dire_bear_form))
                    {
                        if (!player->HasAura(DamageDoneTakenSpell))
                        {
                            //int buffDurationSeconds = 60 * 60;
                            //uint32_t buffDurationMillis = buffDurationSeconds * 1000;

                            //player->AddAura(aura_savage_roar, player);
                            //player->GetAura(aura_savage_roar, player->GetGUID())->SetDuration(buffDurationMillis);


                            unit->CastCustomSpell(player, DamageDoneTakenSpell, false, dmg_taken,dmg_done);
                        }
                    }
                    else
                    {
                        if (player->HasAura(DamageDoneTakenSpell))
                        {
                            player->RemoveAura(DamageDoneTakenSpell);
                        }
                    }
                }
            }
        }
    }
};

void AddDruidBuffScripts()
{
    new DruidBuff();
}

/*
Examples of how to pass params to each of the various aura types.

if not player:HasAura(BaseStatAPSpell) then
    player:CastCustomSpell(player, BaseStatAPSpell, false, ConfigMap_baseStatModifier[mapId],ConfigMap_meleeAPModifier[mapId],ConfigMap_rangedAPModifier[mapId])
end
if not player:HasAura(DamageDoneTakenSpell) then
    player:CastCustomSpell(player, DamageDoneTakenSpell, false, ConfigMap_DamageTaken[mapId],ConfigMap_DamageDoneModifier[mapId])
end
if not player:HasAura(HpAuraSpell) then
    player:CastCustomSpell(player, HpAuraSpell, false, ConfigMap_hpModifier[mapId])
end
if not player:HasAura(RageFromDamageSpell) then
    player:CastCustomSpell(player, RageFromDamageSpell, false, ConfigMap_RageFromDamageModifier[mapId])
end
if not player:HasAura(AbsorbSpell) then
    player:CastCustomSpell(player, AbsorbSpell, false, ConfigMap_AbsorbModifier[mapId])
end
if not player:HasAura(HealingDoneSpell) then
    player:CastCustomSpell(player, HealingDoneSpell, false, ConfigMap_HealingDoneModifier[mapId])
end
if not player:HasAura(PhysicalDamageTakenSpell) then
    player:CastCustomSpell(player, PhysicalDamageTakenSpell, false, ConfigMap_PhysicalDamageTakenModifier[mapId])
end
*/