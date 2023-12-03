#ifndef GAMEVARS_H
#define GAMEVARS_H

#define STARTING_LIVES 1
#define MINIGAME_START_TIME 5
#define LETTER_NUMBER 10
#define KEY_SIZE 80
#define WIN_SCORE 100
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
