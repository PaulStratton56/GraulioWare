#ifndef GAMEVARS_H
#define GAMEVARS_H

#pragma once

#include <QString>

#define STARTING_LIVES 5
#define MINIGAME_START_TIME 10
#define LETTER_NUMBER 10
#define KEY_SIZE 80
#define WIN_SCORE 8
#define DIFFICULTY_INTERVAL 5
#define POINTS_PER_GAME 1

enum gameStates
{
    START,
    HUB,
    TYPING,
    ARROWS,
    AVOIDANCE,
    LOSS,
    VICTORY
};

#endif // GAMEVARS_H
