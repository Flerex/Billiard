#ifndef __BOARD_SCENE_H__
#define __BOARD_SCENE_H__

#include "cocos2d.h"
#include "Model/Game.hpp"

class BoardScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(BoardScene);
    
protected:
    cocos2d::Label * _score;
    Node* _board;
    Node* _stick;
    Node* _whiteBall;
    Node* _balls[15];
    Game* _game;
    
    int currentLevel();
    int nextLevel();
    
    void createGame();
    void addScoreboard();
    void addBoard();
    void addBall();
    void addBallSet();
    void addHoles();
    void addStick();
    void setupMouseEvent();
    void addContactListener();
    
    void update(float dt);
    
    float getAngleForPoints(cocos2d::Vec2 a, cocos2d::Vec2 b);
    
    void onMouseMove(cocos2d::Event *event);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    cocos2d::PhysicsBody* getBallPhysicsBody();
    cocos2d::PhysicsBody* getStickPhysicsBody();
    cocos2d::PhysicsBody* getHolePhysicsBody();
    
    ~BoardScene();
};

#endif // __BOARD_SCENE_H__
