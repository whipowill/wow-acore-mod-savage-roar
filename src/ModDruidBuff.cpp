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
            uint32_t spellId = 52610; // Savage Roar

            // if in animal form
            if (player && player->GetClass() == CLASS_DRUID && (player->HasAura(AURA_CAT_FORM) || player->HasAura(AURA_BEAR_FORM) || player->HasAura(AURA_DIRE_BEAR_FORM)))
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