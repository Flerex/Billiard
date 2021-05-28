#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>


class Game
{
    
public:
    enum GameState { lost, finished, inProgress };
    enum BallState { removed, present };
    
    Game();
    
    GameState currentState();
    
    int getPoints();
    
    bool removeBall(int i);
    
private:
    BallState balls[15];
    int points;
    int previousBall = 0;
};

#endif
