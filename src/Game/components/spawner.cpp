/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob_spawner.cpp
*/

#include "Game/components/spawner.hpp"

Spawner::Spawner(const std::string& name, bool activity) {
    entity_name = name;
    active = activity;
}

void spawnerComponent(Game& game) {
    game.registerComponent<Spawner>("spawner",
        [&game](ECS::Entity e, const toml::table& params){
        const auto& name = params["entity"].value_or("");
        const bool active = params["active"].value_or(false);
        game.createComponent<Spawner>(e, name, active);
    });
}
