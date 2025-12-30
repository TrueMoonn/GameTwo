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

#include "entities.hpp"
#include "weapons.hpp"

void swordWeapon(Game& game, int level, ECS::Entity player) {
    static te::Timestamp delta(1.5f);
    if (!delta.checkDelay())
        return;
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
