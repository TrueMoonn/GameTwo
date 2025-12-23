/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** main.cpp
*/

#include <GameTool.hpp>
#include <events.hpp>
#include <ECS/DenseZipper.hpp>
#include <clock.hpp>

#include <interaction/components/player.hpp>
#include <display/components/animation.hpp>
#include <physic/components/velocity.hpp>
#include <sfml/components/sprite.hpp>

#include "configs.hpp"
#include "entities.hpp"

int main() {
    te::GameTool gtool;
    gtool.loadPlugins();

    for (auto& sys : SYSTEMS_NAME)
        gtool.createSystem(sys);
    for (auto& conf : CONFIG_PATHS)
        gtool.addConfig(conf);
    for (auto& map : MAP_PATHS)
        gtool.addMap(map);

    gtool.createComponent("window", eField::SYSTEM);
    gtool.createMap(MAP_BEGIN, 0);
    gtool.createEntity(PLAYER, "player", {100.f, 100.f});

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
                vel.y = -170.0;
                yKeys = true;
            } else if (keys[te::Key::S]) {
                vel.y = 170.0;
                yKeys = true;
            } else {
                vel.y = 0.0;
            }
            if (keys[te::Key::Q]) {
                vel.x = -170.0;
                xKeys = true;
                auto scale = sp.sp.getScale();
                if (scale.x > 0) {
                    scale.x *= -1;
                    sp.sp.setScale(scale);
                }
            } else if (keys[te::Key::D]) {
                vel.x = 170.0;
                xKeys = true;
                auto scale = sp.sp.getScale();
                if (scale.x < 0) {
                    scale.x *= -1;
                    sp.sp.setScale(scale);
                }
            } else {
                vel.x = 0.0;
            }
            if (yKeys || xKeys) {
                anim.curAnim = 1;
                anim.timestamp.delay = anim.frameInfos[1].frameDELAY;
                anim.timestamp.restart();
            } else {
                anim.curAnim = 0;
                anim.timestamp.delay = anim.frameInfos[0].frameDELAY;
                anim.timestamp.restart();
            }
            if (yKeys && xKeys) {
                vel.x *= 0.75;
                vel.y *= 0.75;
            }
        }
    });

    bool running = true;
    gtool.sub("closed", [&running]() {running = false;});
    te::Timestamp delta(1.0f / 60);
    while (running) {
        if (delta.checkDelay())
            gtool.runSystems();
    }
    return 0;
}
