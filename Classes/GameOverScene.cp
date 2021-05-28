#include "GameOverScene.h"
#include "BoardScene.h"
#include "SecondLevelBoardScene.h"

USING_NS_CC;

int _points;
int _currentLevel;
int _nextLevel;
bool _won;

Scene* GameOverScene::createScene(int points, int currentLevel, int nextLevel, bool won)
{
    _points = points;
    _currentLevel = currentLevel;
    _nextLevel = nextLevel;
    _won = won;
    
    return GameOverScene::create();
}


bool GameOverScene::init()
{

    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    auto closeItem = MenuItemLabel::create(
       Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 24),
       CC_CALLBACK_1(GameOverScene::menuCloseCallback, this)
    );
    
    
    MenuItemLabel* playItem;
    if (_won)
    {
        playItem = MenuItemLabel::create(
           Label::createWithTTF("Next Level", "fonts/Marker Felt.ttf", 24),
           CC_CALLBACK_1(GameOverScene::menuNextLevelCallback, this)
        );
    }
    else
    {
        playItem = MenuItemLabel::create(
           Label::createWithTTF("Play again", "fonts/Marker Felt.ttf", 24),
           CC_CALLBACK_1(GameOverScene::menuPlayCallback, this)
        );
    }

    
    auto menu = Menu::create(playItem, closeItem, NULL);
    menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    menu->alignItemsVertically();
    this->addChild(menu);
    
    
    auto points = Label::createWithTTF("Points: " + std::to_string(_points), "fonts/Marker Felt.ttf", 34);
    points->setAnchorPoint(Vec2(0.5, 1));
    points->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 10));
    
    this->addChild(points);


    return true;
}


void GameOverScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}


void GameOverScene::menuPlayCallback(Ref* pSender)
{
    auto scene = this->getSceneForLevel(_currentLevel);
    printf("current Level: %d\n", _currentLevel);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
}

void GameOverScene::menuNextLevelCallback(Ref* pSender)
{
    auto scene = this->getSceneForLevel(_nextLevel);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
    
   
}

Scene* GameOverScene::getSceneForLevel(int level)
{
    Scene * scene;
    
    switch (level)
    {
        case 2:
            scene = SecondLevelBoardScene::createScene();
            break;
            
        case 1:
        default:
            scene = BoardScene::createScene();
            break;
    }
    
    return scene;
}
