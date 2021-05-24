#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void menuPlayCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__
