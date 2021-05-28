#include "BoardScene.h"
#include "GameOverScene.h"

#include <math.h>

USING_NS_CC;

#define BALL_TAG 1
#define STICK_TAG 2
#define WHITE_TAG 3
#define HOLE_TAG 4
#define BOARD_TAG 5

Scene* BoardScene::createScene()
{
    return BoardScene::create();
}


bool BoardScene::init()
{
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
    
    scheduleUpdate();
    
    this->createGame();
    this->addScoreboard();
    this->addBoard();
    this->addBall();
    this->addBallSet();
    this->addStick();
    this->addHoles();
    this->setupMouseEvent();
    this->addContactListener();
    
    // this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    return true;
}

int BoardScene::currentLevel()
{
    return 1;
}

int BoardScene::nextLevel()
{
    return 2;
}

void BoardScene::createGame()
{
    this->_game = new Game;
}

void BoardScene::addScoreboard()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto scoreBoard = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
    auto position = Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - scoreBoard->getContentSize().height - 10);
    scoreBoard->setPosition(position);
    
    this->_score = scoreBoard;
    
    this->addChild(scoreBoard, 10);
}

void BoardScene::addBoard()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto width = visibleSize.width / 2;
    auto height = visibleSize.height / 2;
    auto borderSize = 5;
    
    auto rectNode = DrawNode::create();
    
    Vec2 rectangle[4] = {
        Vec2(-width, -height),
        Vec2(width, -height),
        Vec2(width, height),
        Vec2(-width, height)
    };

    Color4F boardColor(118/255.0, 157/255.0, 122/255.0, 1);
    Color4F boardBorderColor(0.616, 0.523, 0.38, 1);
    
    rectNode->drawPolygon(rectangle, 4, boardColor, borderSize, boardBorderColor);
    
    
    auto contentSize = rectNode->getContentSize();
    
    rectNode->setAnchorPoint(Vec2(contentSize.width/2, contentSize.height/2));
    rectNode->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(rectNode);
        
    auto edgeBox = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, borderSize);
    edgeBox->setContactTestBitmask(0xFFFFFFFF);
    
    rectNode->addComponent(edgeBox);
    
    rectNode->setTag(BOARD_TAG);
    
    
    this->_board = rectNode;
}


void BoardScene::addBall()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("balls/white.png");
    
    sprite->setPosition(Vec2(visibleSize.width/2 + 200, visibleSize.height/2 + 25));
    this->addChild(sprite);
    
    sprite->addComponent(this->getBallPhysicsBody());
    sprite->setTag(WHITE_TAG);
    
    this->_whiteBall = sprite;
}

void BoardScene::addHoles()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    Vec2 positions[4] = {
        Vec2(5, 5),
        Vec2(visibleSize.width - 5, 5),
        Vec2(5, visibleSize.height - 5),
        Vec2(visibleSize.width - 5, visibleSize.height - 5)
    };
    
    for (int i = 0; i < sizeof(positions)/sizeof(Vec2); i++)
    {
        auto sprite = Sprite::create("assets/hole.png");
        sprite->setPosition(positions[i]);
        sprite->addComponent(this->getHolePhysicsBody());
        this->addChild(sprite);
        sprite->setTag(HOLE_TAG);
    }
}

void BoardScene::addBallSet()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    for (int i = 0, offsetX = 0, offsetY = 0, currentRow = 1, currentNumber = 1; i < 5; i++)
    {
        offsetY = -(currentRow * 50) / 2;
        for (int j = 0; j < currentRow; j++)
        {
            auto sprite = Sprite::create("balls/" + std::to_string(currentNumber) + ".png");
            sprite->setPosition(Vec2(visibleSize.width/2 + origin.x - offsetX, visibleSize.height/2 + origin.y - offsetY));
            
            this->addChild(sprite);
            sprite->addComponent(this->getBallPhysicsBody());
            sprite->setTag(BALL_TAG);

            this->_balls[currentNumber - 1] = sprite;
            offsetY += 50 + 10;
            currentNumber++;
        }
        
        currentRow++;
        offsetX += 50 + 10;
    }
}

void BoardScene::addStick()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("assets/stick.png");
    
    sprite->setPosition(Vec2(-10, -300));
    sprite->setAnchorPoint(Vec2(1, 0.5));
    
    this->addChild(sprite, 4);
    
    sprite->addComponent(this->getStickPhysicsBody());
    sprite->setTag(STICK_TAG);
    
    this->_stick = sprite;
}

void BoardScene::setupMouseEvent()
{
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(BoardScene::onMouseMove, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this->_board);
}

PhysicsBody* BoardScene::getBallPhysicsBody()
{
    
    auto physicsBody = PhysicsBody::createCircle(25, PHYSICSBODY_MATERIAL_DEFAULT);
    
    physicsBody->setGravityEnable(false);
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    
    return physicsBody;
    
}

PhysicsBody* BoardScene::getHolePhysicsBody()
{
    auto physicsBody = PhysicsBody::createCircle(50, PHYSICSBODY_MATERIAL_DEFAULT);
    
    physicsBody->setGravityEnable(false);
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    physicsBody->setDynamic(false);

    return physicsBody;
}

PhysicsBody* BoardScene::getStickPhysicsBody()
{
    
    auto physicsBody = PhysicsBody::createBox(Size(939.0f, 23.0f), PHYSICSBODY_MATERIAL_DEFAULT);
    
    physicsBody->setGravityEnable(false);
    physicsBody->setDynamic(false);
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    
    return physicsBody;
    
}

void BoardScene::onMouseMove(Event *event)
{
    // to illustrate the event....
    EventMouse* e = (EventMouse*)event;
    
    this->_stick->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
    
}

float BoardScene::getAngleForPoints(Vec2 a, Vec2 b)
{
    auto slope = abs(b.y - a.y) / abs(b.x - a.x);
    
    
    auto angle = atan(slope);
        
    if (b.y > a.y && b.x > a.x) // 3rd quadrant
    {
        angle *= -1;
    } else if (b.y < a.y && b.x > a.x) // 2nd quadrant
    {
    } else if (b.y > a.y && b.x < a.x) // 4th quadrant
        //
    {
        angle += M_PI;
    } else if (b.y < a.y && b.x < a.x) // 1st quadrant
    {
        angle = M_PI - angle;
    }
    
    return angle;
}

void BoardScene::addContactListener()
{
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(BoardScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool BoardScene::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (nodeA && nodeB)
    {
        if ((nodeA->getTag() == BALL_TAG && nodeB->getTag() == STICK_TAG)
            || (nodeB->getTag() == BALL_TAG && nodeA->getTag() == STICK_TAG))
        {
            return false;
        }
        
        if ((nodeA->getTag() == STICK_TAG && nodeB->getTag() == WHITE_TAG)
            || (nodeB->getTag() == STICK_TAG && nodeA->getTag() == WHITE_TAG))
        {
            auto whiteBall = nodeA->getTag() == WHITE_TAG ? nodeA : nodeB;
            auto stick = nodeA->getTag() == STICK_TAG ? nodeA : nodeB;
            
            
            auto stickPosition = stick->getPosition();
            auto whitePosition = whiteBall->getPosition();
            
            auto speedVector = Vec2((stickPosition.x - whitePosition.x) * -60, (stickPosition.y - whitePosition.y) * -60);
            whiteBall->getPhysicsBody()->setVelocity(speedVector);
            //whiteBall->getPhysicsBody()->applyForce(Vec2(2000.5, 2000.5));
            return false;
        }
        

        if ((nodeA->getTag() == HOLE_TAG && nodeB->getTag() == BALL_TAG)
            || (nodeB->getTag() == HOLE_TAG && nodeA->getTag() == BALL_TAG))
        {
            auto ball = nodeA->getTag() == BALL_TAG ? nodeA : nodeB;
            

    
            int ballNumber = 0;
            for (int i = 0; i < sizeof(this->_balls) / sizeof(Node *); i++)
            {
                if (this->_balls[i] == ball) {
                    ballNumber = i;
                    break;
                }
            }
            
            auto gameIsFinished = this->_game->removeBall(ballNumber);
            
            ball->removeFromParentAndCleanup(true);
            this->_score->setString(std::to_string(this->_game->getPoints()));
            
            if (gameIsFinished)
            {
                auto points = this->_game->getPoints();
                
                auto won = this->_game->currentState() == Game::finished;
                Scene* scene = GameOverScene::createScene(points, this->currentLevel(), this->nextLevel(), won);
                
                Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
            }
            
            return false;
        }
    }
    
    return true;
}

void BoardScene::update(float dt)
{
    // We update the stick rotation in game loop instead of in the onMouseMove event
    // to take into account the case where the ball is moving but the stick is not,
    // so that the stick is always correctly positioned.

    auto angle = this->getAngleForPoints(
        this->_stick->getPosition(),
        this->_whiteBall->getPosition()
    );

    this->_stick->setRotation(angle * (180 / M_PI));
}

BoardScene::~BoardScene()
{
    delete _game;
}
