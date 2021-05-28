#ifndef __SECOND_LEVEL_BOARD_SCENE_H__
#define __SECOND_LEVEL_BOARD_SCENE_H__

#include "BoardScene.h"
#include "cocos2d.h"

USING_NS_CC;

class SecondLevelBoardScene : public BoardScene
{
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(SecondLevelBoardScene);

protected:
    int currentLevel();
    int nextLevel();
    
private:
    void addObstacles();
};

#endif
