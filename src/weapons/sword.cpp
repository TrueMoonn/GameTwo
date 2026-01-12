/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** sword.cpp
*/

#include <ECS/DenseSA.hpp>
#include <ECS/Entity.hpp>
#include <maths/Vector.hpp>
#include <clock.hpp>
#include <physic/components/position.hpp>
#include <physic/components/velocity.hpp>
#include <physic/components/hitbox.hpp>
#include <entity_spec/components/damage.hpp>
#include <sfml/components/sprite.hpp>
#include <iostream>
#include <map>

#include "entities.hpp"
#include "weapons.hpp"

void swordWeapon(Game& game, int level, ECS::Entity player) {
    // Use per-player cooldown instead of global static
    static std::map<ECS::Entity, te::Timestamp> player_cooldowns;
    
    // Initialize cooldown for new players
    if (player_cooldowns.find(player) == player_cooldowns.end()) {
        player_cooldowns.emplace(player, te::Timestamp(1.5f));
        std::cout << "[swordWeapon] Initialized cooldown for player " << player << std::endl;
    }
    
    auto& cooldown = player_cooldowns.at(player);
    if (!cooldown.checkDelay())
        return;
    
    std::cout << "[swordWeapon] Player " << player << " using sword" << std::endl;
    auto& dmgs = game.getComponent<addon::eSpec::Damage>();
    auto& ppos = GET_ENTITY_CMPT(
        game.getComponent<addon::physic::Position2>(), player);
    ECS::Entity e1 = game.nextEntity(WEAPON);
    ECS::Entity e2 = 0;
    if (level == 1) {
        game.createEntity(e1, "sword", {ppos.x, ppos.y - 20});
    }
    if (level == 4) {
        e2 = game.nextEntity(WEAPON);
        game.createEntity(e2, "sword", {ppos.x, ppos.y - 20});
        auto& sp = GET_ENTITY_CMPT(
            game.getComponent<addon::sfml::Sprite>(), e2);
        auto& hitbox = GET_ENTITY_CMPT(
            game.getComponent<addon::physic::Hitbox>(), e2);
        auto scale = sp.sp.getScale();
        if (scale.x > 0) {
            scale.x *= -1;
            sp.sp.setScale(scale);
            hitbox.position.x -= 128;
        }
    }
    if (level == 2) {
        if (dmgs.hasComponent(e1)) {
            GET_ENTITY_CMPT(dmgs, e1).amount += 4;
        }
        if (dmgs.hasComponent(e2)) {
            GET_ENTITY_CMPT(dmgs, e2).amount += 4;
        }
    }
    if (level == 3) {
        if (dmgs.hasComponent(e1)) {
            GET_ENTITY_CMPT(dmgs, e1).amount += 5;
        }
        if (dmgs.hasComponent(e2)) {
            GET_ENTITY_CMPT(dmgs, e2).amount += 5;
        }
    }
}
