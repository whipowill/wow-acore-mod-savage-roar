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
                uint32_t DamageDoneTakenSpell = 89502;

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