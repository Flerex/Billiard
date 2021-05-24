#ifndef __BOARD_SCENE_H__
#define __BOARD_SCENE_H__

#include "cocos2d.h"

class BoardScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(BoardScene);
    
private:
    Node* _board;
    Node* _stick;
    Node* _whiteBall;
    
    void addScoreboard();
    void addBoard();
    void addBall();
    void addBallSet();
    void addStick();
    void setupMouseEvent();
    void addContactListener();
    
    void update(float dt);
    
    float getAngleForPoints(cocos2d::Vec2 a, cocos2d::Vec2 b);
    
    void onMouseMove(cocos2d::Event *event);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    cocos2d::PhysicsBody* getBallPhysicsBody();
    cocos2d::PhysicsBody* getStickPhysicsBody();
};

#endif // __BOARD_SCENE_H__
