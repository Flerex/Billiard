#include "MainScene.h"
#include "BoardScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}


bool MainScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    auto closeItem = MenuItemLabel::create(
       Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 24),
       CC_CALLBACK_1(MainScene::menuCloseCallback, this)
    );
    
    auto playItem = MenuItemLabel::create(
       Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 24),
       CC_CALLBACK_1(MainScene::menuPlayCallback, this)
    );

    
    auto menu = Menu::create(playItem, closeItem, NULL);
    menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    menu->alignItemsVertically();
    this->addChild(menu);


    return true;
}


void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}


void MainScene::menuPlayCallback(Ref* pSender)
{
    auto scene = BoardScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
}
