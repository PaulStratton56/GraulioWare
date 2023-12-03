#ifndef GAMEVARS_H
#define GAMEVARS_H

#define STARTING_LIVES 4
#define MINIGAME_START_TIME 20
#define LETTER_NUMBER 10
#define KEY_SIZE 60

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
