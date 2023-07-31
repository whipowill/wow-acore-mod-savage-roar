#include "ModDruidBuff.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Unit.h"
#include "Config.h"

class DruidBuff : public PlayerScript
{
public:
    DruidBuff() : PlayerScript("DruidBuff") {}

    void OnUpdate(Player* player, uint32 diff)
    {
        int is_enabled = sConfigMgr->GetOption<int>("DruidBuff.Enable", 0);

        if (is_enabled)
        {
            uint32_t aura_savage_roar = 52610; // Savage Roar
            uint32_t aura_cat_form = 768;
            uint32_t aura_bear_form = 5487;
            uint32_t aura_dire_bear_form = 9634;

            // if in animal form
            if (player && player->getClass() == CLASS_DRUID && (player->HasAura(aura_cat_form) || player->HasAura(aura_bear_form) || player->HasAura(aura_dire_bear_form)))
            {
                if (!player->HasAura(spellId))
                {
                    int buffDuration = 60 * 60 * 6; // 5 hours (adjust as needed)

                    player->AddAura(spellId, player); // Apply the buff to the player
                    player->SetAuraDuration(spellId, buffDuration); // Set the duration of the buff
                }
            }
            else
            {
                if (player->HasAura(spellId))
                {
                    player->RemoveAura(spellId);
                }
            }
        }
    }
};

void AddDruidBuffScripts()
{
    new DruidBuff();
}