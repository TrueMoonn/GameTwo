/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** entities.hpp
*/

#pragma  once

    #include <unordered_map>
    #include <ECS/Entity.hpp>

    #define MAP_FIELD_SIZE 1000
    #define MOB_FIELD_SIZE 2000

enum EntityType {
    SYSTEM = 0,
    PLAYER,
    MAP,
    MOB,
};

enum eField {
    SYSTEM_F = 0,
    PLAYER_F = SYSTEM_F + 1,
    MAP_BEGIN = PLAYER_F + 1,
    MAP_END = MAP_BEGIN + MAP_FIELD_SIZE,
    MOB_BEGIN = MAP_END + 1,
    MOB_END = MOB_BEGIN + MOB_FIELD_SIZE,
};

struct EntityFieldLink {
    std::size_t min;
    std::size_t max;
};

static const std::unordered_map<EntityType, EntityFieldLink> ENTITY_FIELDS {
    {SYSTEM, {
        static_cast<std::size_t>(SYSTEM_F),
        static_cast<std::size_t>(SYSTEM_F)
    }},
    {PLAYER, {
        static_cast<std::size_t>(PLAYER_F),
        static_cast<std::size_t>(PLAYER_F)
    }},
    {MAP, {
        static_cast<std::size_t>(MAP_BEGIN),
        static_cast<std::size_t>(MAP_END)
    }},
    {MOB, {
        static_cast<std::size_t>(MOB_BEGIN),
        static_cast<std::size_t>(MOB_END)
    }}
};
