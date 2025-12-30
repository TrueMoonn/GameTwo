/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** player.hpp
*/

#pragma once

    #include <GameTool.hpp>

enum PlayerAnimations {
    RUN_SIDE = 0,
    RUN_DOWN,
    RUN_UP,
    IDLE_SIDE,
    IDLE_DOWN,
    IDLE_UP
};

#define MOV_SPEED 170.f

#define XP_TO_LVL_UP(level) 10 * level
