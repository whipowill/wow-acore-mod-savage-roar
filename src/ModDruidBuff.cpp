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
            if (player)
            {
                // from wowhead
                uint32_t aura_savage_roar = 52610;
                uint32_t aura_cat_form = 768;
                uint32_t aura_bear_form = 5487;
                uint32_t aura_dire_bear_form = 9634;

                if (player->getClass() == CLASS_DRUID && (player->HasAura(aura_cat_form) || player->HasAura(aura_bear_form) || player->HasAura(aura_dire_bear_form)))
                {
                    if (!player->HasAura(aura_savage_roar))
                    {
                        int buffDurationSeconds = 60 * 60;
                        uint32_t buffDurationMillis = buffDurationSeconds * 1000;

                        player->AddAura(aura_savage_roar, player);
                        player->GetAura(aura_savage_roar, player)->SetDuration(buffDurationMillis);
                    }
                }
                else
                {
                    if (player->HasAura(aura_savage_roar))
                    {
                        player->RemoveAura(aura_savage_roar);
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