#include "ModDruidBuff.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Unit.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
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
                // custom spell ids (taken from Honey55's ZoneBuff codebase)
                // https://github.com/55Honey/Acore_ZoneDebuff/blob/master/zoneDebuff.lua
                //uint32_t HpAuraSpell = 89501;
                uint32_t DamageDoneTakenSpell = 89502; // <-- only one I'm using atm
                //uint32_t BaseStatAPSpell = 89503;
                //uint32_t RageFromDamageSpell = 89504;
                //uint32_t AbsorbSpell = 89505;
                //uint32_t HealingDoneSpell = 89506;
                //uint32_t PhysicalDamageTakenSpell = 89507;

                if (player->getClass() == CLASS_DRUID)
                {
                    uint32_t aura_cat_form = 768;
                    uint32_t aura_bear_form = 5487;
                    uint32_t aura_dire_bear_form = 9634;

                    if (player->HasAura(aura_cat_form) || player->HasAura(aura_bear_form) || player->HasAura(aura_dire_bear_form))
                    {
                        if (!player->HasAura(DamageDoneTakenSpell))
                        {
                            int32_t dmg_taken = sConfigMgr->GetOption<int>("DruidBuff.DamageTaken", 0);
                            int32_t dmg_done = sConfigMgr->GetOption<int>("DruidBuff.DamageDone", 30);

                            player->CastCustomSpell(player, DamageDoneTakenSpell, &dmg_taken, &dmg_done, NULL, true, NULL, NULL, player->GetGUID());
                            // https://github.com/azerothcore/azerothcore-wotlk/blob/cef0d6f6527c0fe2abd6b45087f9f5c80c93331d/src/server/game/Entities/Unit/Unit.cpp#L1226
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
BaseStatAPSpell: param1=ConfigMap_baseStatModifier, param2=ConfigMap_meleeAPModifier, param3=ConfigMap_rangedAPModifier
DamageDoneTakenSpell: param1=ConfigMap_DamageTaken, param2=ConfigMap_DamageDoneModifier
HpAuraSpell: param1=ConfigMap_hpModifier
RageFromDamageSpell: param1=ConfigMap_RageFromDamageModifier
AbsorbSpell: param1=ConfigMap_AbsorbModifier
HealingDoneSpell: param1=ConfigMap_HealingDoneModifier
PhysicalDamageTakenSpell: param1=ConfigMap_PhysicalDamageTakenModifier
*/