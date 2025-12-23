/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** player.cpp
*/

#include <events.hpp>
#include <ECS/DenseZipper.hpp>

#include <interaction/components/player.hpp>
#include <display/components/animation.hpp>
#include <physic/components/velocity.hpp>
#include <sfml/components/sprite.hpp>

#include "player.hpp"

static void changeAnim(addon::display::Animation& anim, PlayerAnimations idx) {
    anim.curAnim = idx;
    anim.timestamp.delay = anim.frameInfos[idx].frameDELAY;
}

void playerMovementsSubscription(te::GameTool& gtool) {
    gtool.sub<te::Keys>("key_input", [&gtool](te::Keys keys){
        auto& plays = gtool.getComponent<addon::intact::Player>();
        auto& vels = gtool.getComponent<addon::physic::Velocity2>();
        auto& anims = gtool.getComponent<addon::display::Animation>();
        auto& sps = gtool.getComponent<addon::sfml::Sprite>();

        for (auto &&[_, vel, anim, sp] :
            ECS::DenseZipper(plays, vels, anims, sps)) {
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
    });
}
