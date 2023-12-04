#ifndef GAMEVARS_H
#define GAMEVARS_H

#pragma once

#include <QString>

#define STARTING_LIVES 1
#define MINIGAME_START_TIME 8
#define LETTER_NUMBER 10
#define KEY_SIZE 80
#define WIN_SCORE 600
#define POINTS_PER_GAME 100

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
