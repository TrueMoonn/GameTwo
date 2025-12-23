/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** entities.hpp
*/

#pragma  once

    #define MAP_FIELD_SIZE 1000
    #define MOB_FIELD_SIZE 2000

enum eField {
    SYSTEM = 0,
    PLAYER = SYSTEM + 1,
    MAP_BEGIN = PLAYER + 1,
    MAP_END = MAP_BEGIN + MAP_FIELD_SIZE,
    MOB_BEGIN = MAP_END + 1,
    MOB_END = MOB_BEGIN + MOB_FIELD_SIZE,
};
