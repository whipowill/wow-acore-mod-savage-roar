#include "ModDruidBuff.h"
#include "ScriptMgr.h"
#include "Config.h"
#include "Unit.h"
#include "Player.h"

class DruidBuffCreatureInfo : public DataMap::Base
{
public:
    DruidBuffCreatureInfo() {}

    uint32_t is_altered = 0;
    uint32_t last_form = 0;
};

class DruidBuff : public PlayerScript
{
public:
    DruidBuff() : PlayerScript("DruidBuff") {}

    void OnUpdate(Player* player, uint32 /*p_time*/)
    {
        if (sConfigMgr->GetOption<int>("DruidBuff.Enable", 0))
        {
            if (player)
            {
                uint32_t DamageDoneTakenSpell = 89508;

                if (player->getClass() == CLASS_DRUID)
                {
                    uint32_t aura_cat_form = 768;
                    uint32_t aura_bear_form = 5487;
                    uint32_t aura_dire_bear_form = 9634;
                    uint32_t aura_travel_form = 783;
                    uint32_t aura_aquatic_form = 1066;
                    uint32_t aura_tree_form = 33891;

                    // if in cat or bear form...
                    if (player->HasAura(aura_cat_form) || player->HasAura(aura_bear_form) || player->HasAura(aura_dire_bear_form))
                    {
                        // if doesn't have dmg enhancement
                        if (!player->HasAura(DamageDoneTakenSpell))
                        {
                            int32_t dmg_taken = sConfigMgr->GetOption<int>("DruidBuff.DamageTaken", 0);
                            int32_t dmg_done = sConfigMgr->GetOption<int>("DruidBuff.DamageDone", 0);

                            // if altering damage is enabled...
                            if (dmg_taken || dmg_done)
                            {
                                // increase damage
                                player->CastCustomSpell(player, DamageDoneTakenSpell, &dmg_taken, &dmg_done, NULL, true, NULL, NULL, player->GetGUID());
                            }
                        }
                    }
                    else
                    {
                        // if has aura...
                        if (player->HasAura(DamageDoneTakenSpell))
                        {
                            // reset
                            player->RemoveAura(DamageDoneTakenSpell);
                        }
                    }

                    /////////////////////////////////////////////////

                    // load info
                    DruidBuffCreatureInfo *creatureInfo = player->CustomData.GetDefault<DruidBuffCreatureInfo>("DruidBuffCreatureInfo");

                    // if in any form (excluding flight forms)...
                    if (player->HasAura(aura_cat_form) || player->HasAura(aura_bear_form) || player->HasAura(aura_dire_bear_form) || player->HasAura(aura_travel_form) || player->HasAura(aura_aquatic_form) || player->HasAura(aura_tree_form))
                    {
                        // if altering armor is enabled...
                        int32_t armor_increase = sConfigMgr->GetOption<int>("DruidBuff.ArmorIncrease", 0);
                        if (armor_increase != 0)
                        {
                            // The reason I turned off this conditional is bc
                            // shifting from travel -> travel would lose the armor buff.
                            // I don't like the idea of this firing every frame
                            // but I don't know how else to ensure perfect armor change.

                            // if not already altered (or new form)...
                            //if (!creatureInfo->is_altered || player->GetShapeshiftForm() != creatureInfo->last_form)
                            //{
                                // reset player armor (so number is correct)
                                player->UpdateArmor();

                                // calculate what this armor should be
                                float new_armor = static_cast<float>(player->GetArmor()) * (100 + armor_increase) / 100;

                                // alter armor
                                player->SetArmor(static_cast<uint32>(new_armor));
                                creatureInfo->last_form = player->GetShapeshiftForm();
                                creatureInfo->is_altered = 1;
                            //}
                        }
                    }
                    else
                    {
                        // if we have a new armor set...
                        if (creatureInfo->is_altered)
                        {
                            // reset
                            player->UpdateArmor();
                            creatureInfo->last_form = 0;
                            creatureInfo->is_altered = 0;
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