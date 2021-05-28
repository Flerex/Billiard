#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int points, int currentLevel, int nextLevel, bool won);

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuNextLevelCallback(cocos2d::Ref* pSender);
    
    Scene* getSceneForLevel(int level);
    
    CREATE_FUNC(GameOverScene);
};

#endif
