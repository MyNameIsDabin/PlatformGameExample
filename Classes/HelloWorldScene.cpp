#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SolidNode.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();


	//아래 SolidNode 들은 모두 하드코딩으로 맵에 배치한다.
	for (int i = 0; i < 14; i++)
	{
		SolidNode* node = SolidNode::create();
		node->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		node->setPosition(Vec2(18 + (i * 36), 0));
		addChild(node);
	}

	//왼쪽 벽에 하나
	SolidNode* leftWall = SolidNode::create();
	leftWall->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	leftWall->setPosition(Vec2(0, 54));
	addChild(leftWall);

	//오른쪽 벽에 하나
	SolidNode* rightWall = SolidNode::create();
	rightWall->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	rightWall->setPosition(Vec2(visibleSize.width, 54));
	addChild(rightWall);

	//위쪽에 벽 하나
	SolidNode* topWall = SolidNode::create();
	topWall->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	topWall->setPosition(Vec2(18 + (8 * 36), 36*2 + 5));
	addChild(topWall);

	//위쪽에 벽 또 하나
	SolidNode* topOfTopWall = SolidNode::create();
	topOfTopWall->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	topOfTopWall->setPosition(Vec2(18 + (9 * 36), 36 * 3));
	addChild(topOfTopWall);

	//움직이는 플레이어
	player = Player::create();
	player->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	player->setMoveSpeed(6.0f);
	player->setPosition(Vec2(visibleOrigin.x + visibleSize.width/2, visibleOrigin.y + visibleSize.height/2));
	addChild(player);

	inputKey.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_LEFT_ARROW, false));
	inputKey.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, false));
	inputKey.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_UP_ARROW, false));

	EventListenerKeyboard* keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);

	schedule(schedule_selector(HelloWorld::scheduleOnKeyPress));

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	for (auto key : inputKey) {
		if (key.first == keyCode) {
			inputKey[keyCode] = true;
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		player->jump(10.0f);
	}
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	for (auto key : inputKey) {
		if (key.first == keyCode) {
			inputKey[keyCode] = false;
		}
	}
}

void HelloWorld::scheduleOnKeyPress(float dt)
{
	for (auto key : inputKey)
	{
		if (key.second == true) 
		{
			if (key.first == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
				player->moveToDirection(Direction::LEFT);

			if (key.first == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
				player->moveToDirection(Direction::RIGHT);
		}
	}
}
