#include "SecondLevelBoardScene.h"


int SecondLevelBoardScene::currentLevel()
{
    return 2;
}

int SecondLevelBoardScene::nextLevel()
{
    return 1;
}

Scene* SecondLevelBoardScene::createScene()
{
    return SecondLevelBoardScene::create();
}


bool SecondLevelBoardScene::init()
{
    auto parent = BoardScene::init();
    
    if ( !parent )
    {
        return false;
    }
    
    this->addObstacles();

    return true;
}


void SecondLevelBoardScene::addObstacles()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("assets/bar.png");
    sprite->setPosition(Vec2(100, 100));
    auto size = sprite->getContentSize();
    
    auto physicsBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT);
    sprite->addComponent(physicsBody);
    this->addChild(sprite);
    
    sprite = Sprite::create("assets/bar.png");
    sprite->setPosition(Vec2(visibleSize.width - 100, 100));
    physicsBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT);
    sprite->addComponent(physicsBody);
    this->addChild(sprite);
    
    sprite = Sprite::create("assets/bar.png");
    sprite->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 100));
    physicsBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT);
    sprite->addComponent(physicsBody);
    this->addChild(sprite);
    
    sprite = Sprite::create("assets/bar.png");
    sprite->setPosition(Vec2(100, visibleSize.height - 100));
    physicsBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT);
    sprite->addComponent(physicsBody);
    
    this->addChild(sprite);
}



