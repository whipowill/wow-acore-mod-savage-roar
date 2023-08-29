#include "ModDruidBuff.h"
#include "ScriptMgr.h"
#include "Config.h"
#include "Unit.h"
#include "Player.h"

class DruidBuff : public PlayerScript
{
public:
    DruidBuff() : PlayerScript("DruidBuff") {}

    void OnUpdate(Player* player, uint32 p_time)
    {
        uint32_t is_enabled = sConfigMgr->GetOption<int>("DruidBuff.Enable", 0);

        if (is_enabled)
        {
            if (player)
            {
                uint32_t DamageDoneTakenSpell = 89508;

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