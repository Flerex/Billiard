#include "Game.hpp"


Game::GameState Game::currentState()
{
    auto allBallsRemoved = true;
    
    for (int i = 0; i < sizeof(this->balls) / sizeof(Game::BallState); i++)
    {
        if (i + 1 == 8)
        {
            continue; // We ignore ball 8
        }
        
        if (this->balls[i] == Game::present)
        {
            allBallsRemoved = false;
        }
    }
    
    // Ball eight ends the game
    
    
    
    if (allBallsRemoved)
    {
        
        return Game::finished;
        
    }
    else if (this->balls[7] == Game::removed)
    {
        return Game::lost;
    }
    
    return Game::inProgress;
}


int Game::getPoints()
{
    return this->points;
}


bool Game::removeBall(int i)
{
    this->balls[i] = Game::removed;
    
    
    // If its ball eight, we inform the game has ended
    if (i + 1 == 8) {
        return true;
    }
    
    // If ball 9, then bonus points take into account ball 7 instead of 8
    if (i + 1 != 9) {
        this->points += (this->previousBall == 6) ? 15 : 5;
    } else {
        this->points += (this->previousBall != 0 && this->previousBall == i - 1) ? 15 : 5;
    }

    
    this->previousBall = i;
    return false;
}

Game::Game()
{
    for (int i = 0; i < sizeof(balls) / sizeof(Game::BallState); i++)
    {
        balls[i] = Game::present;
    }
    
    points = 0;
}
