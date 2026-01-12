/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** player_mov.cpp
*/

#include <events.hpp>
#include <ECS/DenseZipper.hpp>

#include <interaction/components/player.hpp>
#include <display/components/animation.hpp>
#include <physic/components/velocity.hpp>
#include <sfml/components/sprite.hpp>

#include "Game.hpp"
#include "Game/signals.hpp"
#include "player.hpp"

static void changeAnim(addon::display::Animation& anim, PlayerAnimations idx) {
    anim.curAnim = idx;
    anim.timestamp.delay = anim.frameInfos[idx].frameDELAY;
}

static void applyMovement(const te::Keys& keys, addon::physic::Velocity2& vel,
                         addon::display::Animation& anim, addon::sfml::Sprite& sp) {
    bool xKeys = false;
    bool yKeys = false;

    if (keys[te::Key::Z]) {
        vel.y = -MOV_SPEED;
        yKeys = true;
        changeAnim(anim, RUN_UP);
    } else if (keys[te::Key::S]) {
        vel.y = MOV_SPEED;
        yKeys = true;
        changeAnim(anim, RUN_DOWN);
    } else {
        vel.y = 0.0;
    }

    if (keys[te::Key::Q]) {
        vel.x = -MOV_SPEED;
        xKeys = true;
        auto scale = sp.sp.getScale();
        if (scale.x > 0) {
            scale.x *= -1;
            sp.sp.setScale(scale);
        }
    } else if (keys[te::Key::D]) {
        vel.x = MOV_SPEED;
        xKeys = true;
        auto scale = sp.sp.getScale();
        if (scale.x < 0) {
            scale.x *= -1;
            sp.sp.setScale(scale);
        }
    } else {
        vel.x = 0.0;
    }

    if (xKeys)
        changeAnim(anim, RUN_SIDE);
    else if (!yKeys)
        changeAnim(anim, IDLE_DOWN);

    if (yKeys && xKeys) {
        vel.x *= 0.75;
        vel.y *= 0.75;
    }
}

void playerMovement(Game& game) {
    game.sub<te::Keys>("key_input", [&game](te::Keys keys){
        auto& plays = game.getComponent<addon::intact::Player>();
        auto& vels = game.getComponent<addon::physic::Velocity2>();
        auto& anims = game.getComponent<addon::display::Animation>();
        auto& sps = game.getComponent<addon::sfml::Sprite>();

        if (game.isClient()) {
            game.sendInputsToServer(keys);

        } else if (game.isHost()) {
            for (auto &&[player, vel, anim, sp] :
                ECS::DenseZipper(plays, vels, anims, sps)) {
                if (player.player == 1) { // je considère que c'est l'id du joueur qui joue
                    applyMovement(keys, vel, anim, sp);
                    break;
                }
            }

        } else {
            for (auto &&[player, vel, anim, sp] :
                ECS::DenseZipper(plays, vels, anims, sps)) {
                applyMovement(keys, vel, anim, sp);
            }
        }
    });

    if (game.isHost()) {
        game.sub<std::uint32_t, te::Keys>("network_input",
            [&game](std::uint32_t player_id, te::Keys keys) {
            auto& plays = game.getComponent<addon::intact::Player>();
            auto& vels = game.getComponent<addon::physic::Velocity2>();
            auto& anims = game.getComponent<addon::display::Animation>();
            auto& sps = game.getComponent<addon::sfml::Sprite>();

            for (auto &&[player, vel, anim, sp] :
                ECS::DenseZipper(plays, vels, anims, sps)) {
                if (player.player == player_id) {
                    applyMovement(keys, vel, anim, sp);
                    break;
                }
            }
        });
    }
}
