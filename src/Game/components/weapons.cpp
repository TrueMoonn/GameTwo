/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** weapons.cpp
*/

#include "Game/components/weapons.hpp"

Weapon::Weapon(const std::string& name, int lvl) :
    name(name), level(lvl) {}

void weaponComponent(Game& game) {
    game.registerComponent<Weapon>("weapon",
        [&game](ECS::Entity e, const toml::table& params) {
        auto name = params["name"].value_or("");
        auto lvl = params["level"].value_or(0);
        game.createComponent<Weapon>(e, name, lvl);
    });
}

Weapons::Weapons(const std::vector<Weapon>& wps) : list(wps) {}

void weaponsComponent(Game& game) {
    game.registerComponent<Weapons>("weapons",
        [&game](ECS::Entity e, const toml::table& params) {
        const auto& weapons = params["list"].as_array();
        std::vector<Weapon> list;
        list.reserve(weapons->size());
        for (std::size_t i = 0; i < weapons->size(); ++i) {
            const auto& weapon = weapons->at(i).as_array();
            list.emplace_back(
                weapon->at(0).value_or(""),
                weapon->at(1).value_or(0)
            );
        }
        game.createComponent<Weapons>(e, list);
    });
}
